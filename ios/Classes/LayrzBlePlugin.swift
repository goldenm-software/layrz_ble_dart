import Flutter
import UIKit
import CoreBluetooth

public class LayrzBlePlugin: NSObject, FlutterPlugin, CBCentralManagerDelegate, CBPeripheralDelegate {
    static var channel: FlutterMethodChannel?
    var lastResult: FlutterResult?
    var centralManager: CBCentralManager!
    var discoveredPeripherals: [CBPeripheral] = []
    var isScanning: Bool = false
    var devices: [String: CBPeripheral] = [:]
    var filteredUuid: String?
    var connectedPeripheral: CBPeripheral?
    var discoveredServices: [CBUUID: [CBCharacteristic]] = [:]
    var lastOp: LastOperation?
    
    override init() {
        super.init()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    public static func register(with registrar: FlutterPluginRegistrar) {
        channel = FlutterMethodChannel(name: "com.layrz.layrz_ble", binaryMessenger: registrar.messenger())
        let instance = LayrzBlePlugin()
        registrar.addMethodCallDelegate(instance, channel: channel!)
    }

    public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
        log("Handling method call: \(call.method)")
        switch call.method {
        case "checkCapabilities":
            checkCapabilities(result: result)
        case "startScan":
            startScan(call: call, result: result)
        case "stopScan":
            stopScan(call: call, result: result)
        case "connect":
            connect(call: call, result: result)
        case "disconnect":
            disconnect(call: call, result: result)
        case "discoverServices":
            discoverServices(call: call, result: result)
        case "setMtu":
            setMtu(call: call, result: result)
        case "writeCharacteristic":
            writeCharacteristic(call: call, result: result)
        case "readCharacteristic":
            readCharacteristic(call: call, result: result)
        case "startNotify":
            startNotify(call: call, result: result)
        case "stopNotify":
            stopNotify(call: call, result: result)
        default:
            result(FlutterMethodNotImplemented)
        }
    }
    
    private func checkCapabilities(result: @escaping FlutterResult) {
        let auth = CBCentralManager.authorization
        
        return result([
            "locationPermission": auth == .allowedAlways,
            "bluetoothPermission": auth == .allowedAlways,
            "bluetoothAdminOrScanPermission": auth == .allowedAlways,
            "bluetoothConnectPermissiion": auth == .allowedAlways
            
        ])
    }
    
    private func startScan(call: FlutterMethodCall, result: @escaping FlutterResult) {
        if (isScanning) {
            return result(true)
        }
        
        let auth = CBCentralManager.authorization
        if (auth != .allowedAlways) {
            log("Bluetooth permission denied - \(auth)")
            return result(false)
        }
        if (centralManager.state != .poweredOn) {
            log("Bluetooth is not turned on - \(centralManager.state)")
            return result(false)
        }
        
        let args = call.arguments as? [String: Any] ?? [:]
        filteredUuid = (args["macAddress"] as? String)?.lowercased()
        centralManager.scanForPeripherals(withServices: nil, options: nil)
        isScanning = true
        return result(true)
    }
    
    private func stopScan(call: FlutterMethodCall, result: @escaping FlutterResult) {
        if (!isScanning) {
            return result(true)
        }
        
        centralManager.stopScan()
        isScanning = false
        return result(true)
    }
    
    private func connect(call: FlutterMethodCall, result: @escaping FlutterResult) {
        connectedPeripheral = nil
        let uuid = (call.arguments as? String)?.lowercased()
        if (uuid == nil) {
            log("UUID not defined")
            return result(false)
        }
        
        if let device = devices[uuid!] {
            if (isScanning) {
                centralManager.stopScan()
                isScanning = false
            }
            
            lastResult = result
            centralManager.connect(device)
        } else {
            log("Device not found")
            return result(false)
        }
    }
    
    private func disconnect(call: FlutterMethodCall, result: @escaping FlutterResult) {
        if (connectedPeripheral != nil) {
            centralManager.cancelPeripheralConnection(connectedPeripheral!)
        }
        return result(true)
    }
    
    private func discoverServices(call: FlutterMethodCall, result: @escaping FlutterResult) {
        if (connectedPeripheral == nil) {
            return result(nil)
        }
        
        lastResult = result
        connectedPeripheral!.discoverServices(nil)
    }
    
    private func setMtu(call: FlutterMethodCall, result: @escaping FlutterResult) {
        if connectedPeripheral == nil {
            return result(nil)
        }
        
        let mtu = connectedPeripheral!.maximumWriteValueLength(for: .withResponse)
        return result(mtu)
    }
    
    private func writeCharacteristic(call: FlutterMethodCall, result: @escaping FlutterResult) {
        let args = call.arguments as? [String: Any] ?? [:]
        let serviceUuid = (args["serviceUuid"] as? String)?.lowercased()
        if serviceUuid == nil {
            log("Service UUID not defined")
            return result(false)
        }
        
        let characteristicUuid = (args["characteristicUuid"] as? String)?.lowercased()
        if characteristicUuid == nil {
            log("Characteristic UUID not defined")
            return result(false)
        }
        
        let payload = args["payload"] as? FlutterStandardTypedData
        if payload == nil {
            log("Payload not defined")
            return result(false)
        }
        
        let withResponse = args["withResponse"] as? Bool ?? false
        
        if connectedPeripheral == nil {
            log("Device is not connected")
            return result(false)
        }
        
        guard let service = connectedPeripheral!.services?.first(where: { $0.uuid.uuidString.lowercased() == serviceUuid }) else {
            log("Service not found on the device")
            return result(false)
        }
        
        guard let characteristic = service.characteristics?.first(where: {$0.uuid.uuidString.lowercased() == characteristicUuid}) else {
            log("Characteristic not found on the device")
            return result(false)
        }
        
        lastResult = result
        connectedPeripheral!.writeValue(payload!.data, for: characteristic, type: withResponse ? .withResponse : .withoutResponse)
    }
    
    private func readCharacteristic(call: FlutterMethodCall, result: @escaping FlutterResult) {
        let args = call.arguments as? [String: Any] ?? [:]
        let serviceUuid = (args["serviceUuid"] as? String)?.lowercased()
        if serviceUuid == nil {
            log("Service UUID not defined")
            return result(nil)
        }
        
        let characteristicUuid = (args["characteristicUuid"] as? String)?.lowercased()
        if characteristicUuid == nil {
            log("Characteristic UUID not defined")
            return result(nil)
        }
        
        if connectedPeripheral == nil {
            log("Device is not connected")
            return result(nil)
        }
        
        guard let service = connectedPeripheral!.services?.first(where: { $0.uuid.uuidString.lowercased() == serviceUuid }) else {
            log("Service not found on the device")
            return result(nil)
        }
        
        guard let characteristic = service.characteristics?.first(where: {$0.uuid.uuidString.lowercased() == characteristicUuid}) else {
            log("Characteristic not found on the device")
            return result(nil)
        }
        
        if characteristic.isNotifying {
            log("Characteristic is notifying, cannot read it.")
            return result(nil)
        }
        
        lastResult = result
        connectedPeripheral!.readValue(for: characteristic)
    }
    
    private func startNotify(call: FlutterMethodCall, result: @escaping FlutterResult) {
        let args = call.arguments as? [String: Any] ?? [:]
        let serviceUuid = (args["serviceUuid"] as? String)?.lowercased()
        if serviceUuid == nil {
            log("Service UUID not defined")
            return result(false)
        }
        
        let characteristicUuid = (args["characteristicUuid"] as? String)?.lowercased()
        if characteristicUuid == nil {
            log("Characteristic UUID not defined")
            return result(false)
        }
        
        if connectedPeripheral == nil {
            log("Device is not connected")
            return result(false)
        }
        
        guard let service = connectedPeripheral!.services?.first(where: { $0.uuid.uuidString.lowercased() == serviceUuid }) else {
            log("Service not found on the device")
            return result(false)
        }
        
        guard let characteristic = service.characteristics?.first(where: {$0.uuid.uuidString.lowercased() == characteristicUuid}) else {
            log("Characteristic not found on the device")
            return result(false)
        }
        
        connectedPeripheral!.setNotifyValue(true, for: characteristic)
        log("Notify started")
        return result(true)
    }
    
    private func stopNotify(call: FlutterMethodCall, result: @escaping FlutterResult) {
        let args = call.arguments as? [String: Any] ?? [:]
        let serviceUuid = (args["serviceUuid"] as? String)?.lowercased()
        if serviceUuid == nil {
            log("Service UUID not defined")
            return result(false)
        }
        
        let characteristicUuid = (args["characteristicUuid"] as? String)?.lowercased()
        if characteristicUuid == nil {
            log("Characteristic UUID not defined")
            return result(false)
        }
        
        if connectedPeripheral == nil {
            log("Device is not connected")
            return result(false)
        }
        
        guard let service = connectedPeripheral!.services?.first(where: { $0.uuid.uuidString.lowercased() == serviceUuid }) else {
            log("Service not found on the device")
            return result(false)
        }
        
        guard let characteristic = service.characteristics?.first(where: {$0.uuid.uuidString.lowercased() == characteristicUuid}) else {
            log("Characteristic not found on the device")
            return result(false)
        }
        
        connectedPeripheral!.setNotifyValue(false, for: characteristic)
        return result(true)
    }
    
    // Peripheral delegate
    public func peripheral(_ peripheral: CBPeripheral, didUpdateNotificationStateFor characteristic: CBCharacteristic, error: (any Error)?) {
        if let error = error {
            log("Error updating notification state: \(error.localizedDescription)")
            return
        }
        
        if characteristic.isNotifying {
            log("Notification started")
        } else {
            log("Notification stopped")
        }
    }
    
    public func peripheral(_ peripheral: CBPeripheral, didWriteValueFor characteristic: CBCharacteristic, error: (any Error)?) {
        if let error = error {
            log("Error writing value: \(error.localizedDescription)")
            lastResult?(false)
            lastResult = nil
            return
        }
        
        log("Payload sent successfully")
        lastResult?(true)
        lastResult = nil
    }
    
    public func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: (any Error)?) {
        if let error = error {
            log("Error reading value: \(error.localizedDescription)")
            lastResult?(nil)
            lastResult = nil
            return
        }
        
        if characteristic.isNotifying {
            let notification: [String: Any?] = [
                "serviceUuid": characteristic.service?.uuid.uuidString.lowercased(),
                "characteristicUuid": characteristic.uuid.uuidString.lowercased(),
                "value": characteristic.value
            ]
            
            LayrzBlePlugin.channel!.invokeMethod("onNotify", arguments: notification)
        } else {
            lastResult?(characteristic.value)
            lastResult = nil
        }
    }
    
    public func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: (any Error)?) {
        let uuid = peripheral.identifier.uuidString.lowercased()
        log("Discovering services of \(uuid)")
        if let error = error {
            log("Error discovering services: \(error.localizedDescription)")
            lastResult?(nil)
            return
        }
        
        guard let services = peripheral.services else { return }
        
        for service in services {
            discoveredServices.updateValue([], forKey: service.uuid)
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }
    
    public func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: (any Error)?) {
        if let error = error {
            log("Error discovering services - \(error.localizedDescription)")
            return
        }
        
        let serviceUuid = service.uuid
        if (discoveredServices[serviceUuid] == nil) {
            return
        }
        
        guard let characteristics = service.characteristics else { return }
        
        for characteristic in characteristics {
            discoveredServices[serviceUuid]!.append(characteristic)
        }
        
        log("Checking if all services are discovered")
        for (uuid, characteristics) in discoveredServices {
            if (characteristics.isEmpty) {
                log("Service \(uuid) has not been discovered")
                return
            }
        }
        
        var servicesAndCharacteristics: [[String: Any]] = []
        for (serviceUuid, serviceCharacteristics) in discoveredServices {
            var discoveredCharacteristics: [[String: Any]] = []
            for characteristic in serviceCharacteristics {
                var propertiesList: [String] = []
                let properties = characteristic.properties
                if properties.contains(.read) { propertiesList.append("READ") }
                if properties.contains(.write) { propertiesList.append("WRITE") }
                if properties.contains(.writeWithoutResponse) { propertiesList.append("WRITE_WO_RSP") }
                if properties.contains(.notify) { propertiesList.append("NOTIFY") }
                if properties.contains(.indicate) { propertiesList.append("INDICATE") }
                if properties.contains(.authenticatedSignedWrites) { propertiesList.append("AUTH_SIGN_WRITES") }
                if properties.contains(.broadcast) { propertiesList.append("BROADCAST") }
                if properties.contains(.extendedProperties) { propertiesList.append("EXTENDED_PROP") }
                
                discoveredCharacteristics.append([
                    "uuid": characteristic.uuid.uuidString.lowercased(),
                    "properties": propertiesList,
                ])
            }
            
            servicesAndCharacteristics.append([
                "uuid": serviceUuid.uuidString.lowercased(),
                "characteristics": discoveredCharacteristics
            ])
        }
        
        log("Discovery finished - \(servicesAndCharacteristics)")
        lastResult?(servicesAndCharacteristics)
    }
    
    // Central manager delegate
    public func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: (any Error)?) {
        let uuid = peripheral.identifier.uuidString.lowercased()
        log("Failed to connect to \(uuid) - \(error?.localizedDescription ?? "")")
        connectedPeripheral = nil
        LayrzBlePlugin.channel?.invokeMethod("onEvent", arguments: "DISCONNECTED")
        lastResult?(false)
    }
    
    public func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: (any Error)?) {
        let uuid = peripheral.identifier.uuidString.lowercased()
        log("Disconnected from \(uuid) - \(error?.localizedDescription ?? "")")
        connectedPeripheral = nil
        LayrzBlePlugin.channel?.invokeMethod("onEvent", arguments: "DISCONNECTED")
        lastResult?(false)
    }
    
    public func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        let name = peripheral.name
        let uuid = peripheral.identifier.uuidString.lowercased()
        
        if (devices[uuid] != nil) {
            return
        }
        
        if (filteredUuid != nil && uuid != filteredUuid) {
            return
        }
        
        let manufacturerData = advertisementData[CBAdvertisementDataManufacturerDataKey] as? Data ?? Data()
        
        var serviceData: Data = Data()
        var servicesIdentifiers: [Data] = []
        if let raw = advertisementData[CBAdvertisementDataServiceDataKey] as? [CBUUID: Data] {
            let sorted = raw.sorted { $0.key.uuidString < $1.key.uuidString }
            
            for (key, data) in sorted {
                serviceData.append(data)
                servicesIdentifiers.append(key.data)
            }
        }
        
        devices.updateValue(peripheral, forKey: uuid)
        LayrzBlePlugin.channel!.invokeMethod("onScan", arguments: [
            "name": name ?? "Unknown",
            "macAddress": uuid,
            "rssi": RSSI,
            "manufacturerData": manufacturerData,
            "serviceData": serviceData,
            "servicesIdentifiers": servicesIdentifiers
        ])
    }
    
    public func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        if (isScanning) {
            centralManager.stopScan()
            isScanning = false
            LayrzBlePlugin.channel?.invokeMethod("onEvent", arguments: "SCAN_STOPPED")
        }
        
        peripheral.delegate = self
        lastResult?(true)
        connectedPeripheral = peripheral
        LayrzBlePlugin.channel?.invokeMethod("onEvent", arguments: "CONNECTED")
        lastResult = nil
    }
    
    public func centralManagerDidUpdateState(_ central: CBCentralManager) {
        switch central.state {
        case .poweredOn:
            log("Bluetooth is turned on")
        case .poweredOff:
            if (isScanning) {
                LayrzBlePlugin.channel?.invokeMethod("onEvent", arguments: "SCAN_STOPPED")
                isScanning = false
            }
            log("Bluetooth is turned off")
        case .unsupported:
            log("Bluetooth is unsupported")
        case .unauthorized:
            log("Bluetooth is unauthorized")
        default:
            log("Unknown Bluetooth state \(central.state)")
        }
    }
    
    private func log(_ message: String) {
        NSLog("LayrzBlePlugin/iOS: \(message)")
    }
}
