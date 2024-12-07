# layrz_ble

A simple way to interact with BLE devices in Flutter.

## Motivation
Our goal is to provide a simple and easy-to-use library for Flutter developers to interact with BLE devices, and support as many platforms as possible.

## Usage
To use this plugin, add `layrz_ble` as a [dependency in your pubspec.yaml file](https://flutter.dev/docs/development/packages-and-plugins/using-packages).

```yaml
dependencies:
  flutter:
    sdk: flutter
  layrz_ble: ^latest_version
```

Then you can import the package in your Dart code:

```dart
import 'package:layrz_ble/layrz_ble.dart';

/// ...

final ble = LayrzBle();

/// Listen for events
///
/// `BleEvent` is from this package
ble.onEvent.listen((BleEvent event) {
  debugPrint(event);
});

/// Listen for device discovery
///
/// `BleDevice` is from `layrz_models` package, but we exported it here for convenience
ble.onScan.listen((BleDevice device) {
  debugPrint(device);
});

/// Check capabilities
///
/// `BleCapabilities` is from this package
final BleCapabilities capabilities = await ble.checkCapabilities();

/// Scan for BLE devices
final bool startResult = await ble.startScan();

/// Stop scanning
final bool stopResult = await ble.stopScan();
```

## Goals
### Capabilities
- [x] Scan for BLE devices
- [ ] Connect to BLE devices (Work in progress)
- [ ] Disconnect from BLE devices
- [ ] Read and write characteristics
- [ ] Subscribe to characteristic notifications

## Platforms
- [ ] Support for Android (Work in progress)
- [ ] Support for iOS
- [ ] Support for Web
- [ ] Support for macOS
- [ ] Support for Windows

## Permissions

Before getting into the platform specific permissions, always raises the question "How can I handle the permissions on my Flutter app?". Well, you can use the [`permission_handler`](https://pub.dev/packages/permission_handler) package to handle the permissions on your Flutter app, or you can handle them manually with native code, the choice is yours.

### Android
```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android">
  <!-- Location is required for BLE scan -->
  <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
  <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />

  <!-- Of course, Bluetooth -->
  <uses-permission android:name="android.permission.BLUETOOTH" />

  <!--
  Required for BLE scan 
  
  Uses or BLUETOOTH_SCAN or BLUETOOTH_ADMIN permission depending on the API level.
  If your app has a minSdkVersion of 31 or above, you should use BLUETOOTH_SCAN permission only,
  otherwise we strongly recommend using both as shown below.
  -->
  <uses-permission
    android:name="android.permission.BLUETOOTH_SCAN"
    android:usesPermissionFlags="neverForLocation"
    android:minSdkVersion="31" /> <!-- This permission is only for API level 31 or above -->
  <uses-permission
    android:name="android.permission.BLUETOOTH_ADMIN"
    android:maxSdkVersion="30" /> <!-- This permission is only for API level 30 or below -->

  <!-- Required for BLE connection -->
  <uses-permission android:name="android.permission.BLUETOOTH_CONNECT" />

  <!-- ... -->
</manifest>
```

### iOS
To be added.

### Web
To be added.

### macOS
To be added.

### Windows
To be added.

## FAQ

### Why is this package called `layrz_ble`?
All packages developed by [Layrz](https://layrz.com) are prefixed with `layrz_`, check out our other packages on [pub.dev](https://pub.dev/publishers/goldenm.com/packages).

### I need to pay to use this package?
<b>No!</b> This library is free and open source, you can use it in your projects without any cost, but if you want to support us, give us a thumbs up here in [pub.dev](https://pub.dev/packages/layrz_ble) and star our [Repository](https://github.com/goldenm-software/layrz_ble)!

### Can I contribute to this package?
<b>Yes!</b> We are open to contributions, feel free to open a pull request or an issue on the [Repository](https://github.com/goldenm-software/layrz_ble)!

### I have a question, how can I contact you?
If you need more assistance, you open an issue on the [Repository](https://github.com/goldenm-software/layrz_ble) and we're happy to help you :)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

This project is maintained by [Golden M](https://goldenm.com) with authorization of [Layrz LTD](https://layrz.com).

## Who are you? / Want to work with us?
<b>Golden M</b> is a software and hardware development company what is working on a new, innovative and disruptive technologies. For more information, contact us at [sales@goldenm.com](mailto:sales@goldenm.com) or via WhatsApp at [+(507)-6979-3073](https://wa.me/50769793073?text="From%20layrz_ble%20flutter%20library.%20Hello").
