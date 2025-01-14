#include "layrz_ble.g.h"

#include <flutter/basic_message_channel.h>
#include <flutter/binary_messenger.h>
#include <flutter/encodable_value.h>
#include <flutter/standard_message_codec.h>

#include <map>
#include <optional>
#include <string>

namespace universal_ble {
using flutter::BasicMessageChannel;
using flutter::CustomEncodableValue;
using flutter::EncodableList;
using flutter::EncodableMap;
using flutter::EncodableValue;

FlutterError CreateConnectionError(const std::string channel_name) {
  return FlutterError(
      "channel-error",
      "Unable to establish connection on channel: '" + channel_name + "'.",
      EncodableValue(""));
}

// UniversalBleScanResult

UniversalBleScanResult::UniversalBleScanResult(const std::string& device_id)
 : device_id_(device_id) {}

UniversalBleScanResult::UniversalBleScanResult(
  const std::string& device_id,
  const std::string* name,
  const bool* is_paired,
  const int64_t* rssi,
  const EncodableList* manufacturer_data_list,
  const EncodableList* services)
 : device_id_(device_id),
    name_(name ? std::optional<std::string>(*name) : std::nullopt),
    is_paired_(is_paired ? std::optional<bool>(*is_paired) : std::nullopt),
    rssi_(rssi ? std::optional<int64_t>(*rssi) : std::nullopt),
    manufacturer_data_list_(manufacturer_data_list ? std::optional<EncodableList>(*manufacturer_data_list) : std::nullopt),
    services_(services ? std::optional<EncodableList>(*services) : std::nullopt) {}

const std::string& UniversalBleScanResult::device_id() const {
  return device_id_;
}

void UniversalBleScanResult::set_device_id(std::string_view value_arg) {
  device_id_ = value_arg;
}


const std::string* UniversalBleScanResult::name() const {
  return name_ ? &(*name_) : nullptr;
}

void UniversalBleScanResult::set_name(const std::string_view* value_arg) {
  name_ = value_arg ? std::optional<std::string>(*value_arg) : std::nullopt;
}

void UniversalBleScanResult::set_name(std::string_view value_arg) {
  name_ = value_arg;
}


const bool* UniversalBleScanResult::is_paired() const {
  return is_paired_ ? &(*is_paired_) : nullptr;
}

void UniversalBleScanResult::set_is_paired(const bool* value_arg) {
  is_paired_ = value_arg ? std::optional<bool>(*value_arg) : std::nullopt;
}

void UniversalBleScanResult::set_is_paired(bool value_arg) {
  is_paired_ = value_arg;
}


const int64_t* UniversalBleScanResult::rssi() const {
  return rssi_ ? &(*rssi_) : nullptr;
}

void UniversalBleScanResult::set_rssi(const int64_t* value_arg) {
  rssi_ = value_arg ? std::optional<int64_t>(*value_arg) : std::nullopt;
}

void UniversalBleScanResult::set_rssi(int64_t value_arg) {
  rssi_ = value_arg;
}


const EncodableList* UniversalBleScanResult::manufacturer_data_list() const {
  return manufacturer_data_list_ ? &(*manufacturer_data_list_) : nullptr;
}

void UniversalBleScanResult::set_manufacturer_data_list(const EncodableList* value_arg) {
  manufacturer_data_list_ = value_arg ? std::optional<EncodableList>(*value_arg) : std::nullopt;
}

void UniversalBleScanResult::set_manufacturer_data_list(const EncodableList& value_arg) {
  manufacturer_data_list_ = value_arg;
}


const EncodableList* UniversalBleScanResult::services() const {
  return services_ ? &(*services_) : nullptr;
}

void UniversalBleScanResult::set_services(const EncodableList* value_arg) {
  services_ = value_arg ? std::optional<EncodableList>(*value_arg) : std::nullopt;
}

void UniversalBleScanResult::set_services(const EncodableList& value_arg) {
  services_ = value_arg;
}


EncodableList UniversalBleScanResult::ToEncodableList() const {
  EncodableList list;
  list.reserve(6);
  list.push_back(EncodableValue(device_id_));
  list.push_back(name_ ? EncodableValue(*name_) : EncodableValue());
  list.push_back(is_paired_ ? EncodableValue(*is_paired_) : EncodableValue());
  list.push_back(rssi_ ? EncodableValue(*rssi_) : EncodableValue());
  list.push_back(manufacturer_data_list_ ? EncodableValue(*manufacturer_data_list_) : EncodableValue());
  list.push_back(services_ ? EncodableValue(*services_) : EncodableValue());
  return list;
}

UniversalBleScanResult UniversalBleScanResult::FromEncodableList(const EncodableList& list) {
  UniversalBleScanResult decoded(
    std::get<std::string>(list[0]));
  auto& encodable_name = list[1];
  if (!encodable_name.IsNull()) {
    decoded.set_name(std::get<std::string>(encodable_name));
  }
  auto& encodable_is_paired = list[2];
  if (!encodable_is_paired.IsNull()) {
    decoded.set_is_paired(std::get<bool>(encodable_is_paired));
  }
  auto& encodable_rssi = list[3];
  if (!encodable_rssi.IsNull()) {
    decoded.set_rssi(std::get<int64_t>(encodable_rssi));
  }
  auto& encodable_manufacturer_data_list = list[4];
  if (!encodable_manufacturer_data_list.IsNull()) {
    decoded.set_manufacturer_data_list(std::get<EncodableList>(encodable_manufacturer_data_list));
  }
  auto& encodable_services = list[5];
  if (!encodable_services.IsNull()) {
    decoded.set_services(std::get<EncodableList>(encodable_services));
  }
  return decoded;
}

// UniversalBleService

UniversalBleService::UniversalBleService(const std::string& uuid)
 : uuid_(uuid) {}

UniversalBleService::UniversalBleService(
  const std::string& uuid,
  const EncodableList* characteristics)
 : uuid_(uuid),
    characteristics_(characteristics ? std::optional<EncodableList>(*characteristics) : std::nullopt) {}

const std::string& UniversalBleService::uuid() const {
  return uuid_;
}

void UniversalBleService::set_uuid(std::string_view value_arg) {
  uuid_ = value_arg;
}


const EncodableList* UniversalBleService::characteristics() const {
  return characteristics_ ? &(*characteristics_) : nullptr;
}

void UniversalBleService::set_characteristics(const EncodableList* value_arg) {
  characteristics_ = value_arg ? std::optional<EncodableList>(*value_arg) : std::nullopt;
}

void UniversalBleService::set_characteristics(const EncodableList& value_arg) {
  characteristics_ = value_arg;
}


EncodableList UniversalBleService::ToEncodableList() const {
  EncodableList list;
  list.reserve(2);
  list.push_back(EncodableValue(uuid_));
  list.push_back(characteristics_ ? EncodableValue(*characteristics_) : EncodableValue());
  return list;
}

UniversalBleService UniversalBleService::FromEncodableList(const EncodableList& list) {
  UniversalBleService decoded(
    std::get<std::string>(list[0]));
  auto& encodable_characteristics = list[1];
  if (!encodable_characteristics.IsNull()) {
    decoded.set_characteristics(std::get<EncodableList>(encodable_characteristics));
  }
  return decoded;
}

// UniversalBleCharacteristic

UniversalBleCharacteristic::UniversalBleCharacteristic(
  const std::string& uuid,
  const EncodableList& properties)
 : uuid_(uuid),
    properties_(properties) {}

const std::string& UniversalBleCharacteristic::uuid() const {
  return uuid_;
}

void UniversalBleCharacteristic::set_uuid(std::string_view value_arg) {
  uuid_ = value_arg;
}


const EncodableList& UniversalBleCharacteristic::properties() const {
  return properties_;
}

void UniversalBleCharacteristic::set_properties(const EncodableList& value_arg) {
  properties_ = value_arg;
}


EncodableList UniversalBleCharacteristic::ToEncodableList() const {
  EncodableList list;
  list.reserve(2);
  list.push_back(EncodableValue(uuid_));
  list.push_back(EncodableValue(properties_));
  return list;
}

UniversalBleCharacteristic UniversalBleCharacteristic::FromEncodableList(const EncodableList& list) {
  UniversalBleCharacteristic decoded(
    std::get<std::string>(list[0]),
    std::get<EncodableList>(list[1]));
  return decoded;
}

// UniversalScanFilter

UniversalScanFilter::UniversalScanFilter(
  const EncodableList& with_services,
  const EncodableList& with_name_prefix,
  const EncodableList& with_manufacturer_data)
 : with_services_(with_services),
    with_name_prefix_(with_name_prefix),
    with_manufacturer_data_(with_manufacturer_data) {}

const EncodableList& UniversalScanFilter::with_services() const {
  return with_services_;
}

void UniversalScanFilter::set_with_services(const EncodableList& value_arg) {
  with_services_ = value_arg;
}


const EncodableList& UniversalScanFilter::with_name_prefix() const {
  return with_name_prefix_;
}

void UniversalScanFilter::set_with_name_prefix(const EncodableList& value_arg) {
  with_name_prefix_ = value_arg;
}


const EncodableList& UniversalScanFilter::with_manufacturer_data() const {
  return with_manufacturer_data_;
}

void UniversalScanFilter::set_with_manufacturer_data(const EncodableList& value_arg) {
  with_manufacturer_data_ = value_arg;
}


EncodableList UniversalScanFilter::ToEncodableList() const {
  EncodableList list;
  list.reserve(3);
  list.push_back(EncodableValue(with_services_));
  list.push_back(EncodableValue(with_name_prefix_));
  list.push_back(EncodableValue(with_manufacturer_data_));
  return list;
}

UniversalScanFilter UniversalScanFilter::FromEncodableList(const EncodableList& list) {
  UniversalScanFilter decoded(
    std::get<EncodableList>(list[0]),
    std::get<EncodableList>(list[1]),
    std::get<EncodableList>(list[2]));
  return decoded;
}

// UniversalManufacturerDataFilter

UniversalManufacturerDataFilter::UniversalManufacturerDataFilter(int64_t company_identifier)
 : company_identifier_(company_identifier) {}

UniversalManufacturerDataFilter::UniversalManufacturerDataFilter(
  int64_t company_identifier,
  const std::vector<uint8_t>* data,
  const std::vector<uint8_t>* mask)
 : company_identifier_(company_identifier),
    data_(data ? std::optional<std::vector<uint8_t>>(*data) : std::nullopt),
    mask_(mask ? std::optional<std::vector<uint8_t>>(*mask) : std::nullopt) {}

int64_t UniversalManufacturerDataFilter::company_identifier() const {
  return company_identifier_;
}

void UniversalManufacturerDataFilter::set_company_identifier(int64_t value_arg) {
  company_identifier_ = value_arg;
}


const std::vector<uint8_t>* UniversalManufacturerDataFilter::data() const {
  return data_ ? &(*data_) : nullptr;
}

void UniversalManufacturerDataFilter::set_data(const std::vector<uint8_t>* value_arg) {
  data_ = value_arg ? std::optional<std::vector<uint8_t>>(*value_arg) : std::nullopt;
}

void UniversalManufacturerDataFilter::set_data(const std::vector<uint8_t>& value_arg) {
  data_ = value_arg;
}


const std::vector<uint8_t>* UniversalManufacturerDataFilter::mask() const {
  return mask_ ? &(*mask_) : nullptr;
}

void UniversalManufacturerDataFilter::set_mask(const std::vector<uint8_t>* value_arg) {
  mask_ = value_arg ? std::optional<std::vector<uint8_t>>(*value_arg) : std::nullopt;
}

void UniversalManufacturerDataFilter::set_mask(const std::vector<uint8_t>& value_arg) {
  mask_ = value_arg;
}


EncodableList UniversalManufacturerDataFilter::ToEncodableList() const {
  EncodableList list;
  list.reserve(3);
  list.push_back(EncodableValue(company_identifier_));
  list.push_back(data_ ? EncodableValue(*data_) : EncodableValue());
  list.push_back(mask_ ? EncodableValue(*mask_) : EncodableValue());
  return list;
}

UniversalManufacturerDataFilter UniversalManufacturerDataFilter::FromEncodableList(const EncodableList& list) {
  UniversalManufacturerDataFilter decoded(
    std::get<int64_t>(list[0]));
  auto& encodable_data = list[1];
  if (!encodable_data.IsNull()) {
    decoded.set_data(std::get<std::vector<uint8_t>>(encodable_data));
  }
  auto& encodable_mask = list[2];
  if (!encodable_mask.IsNull()) {
    decoded.set_mask(std::get<std::vector<uint8_t>>(encodable_mask));
  }
  return decoded;
}

// UniversalManufacturerData

UniversalManufacturerData::UniversalManufacturerData(
  int64_t company_identifier,
  const std::vector<uint8_t>& data)
 : company_identifier_(company_identifier),
    data_(data) {}

int64_t UniversalManufacturerData::company_identifier() const {
  return company_identifier_;
}

void UniversalManufacturerData::set_company_identifier(int64_t value_arg) {
  company_identifier_ = value_arg;
}


const std::vector<uint8_t>& UniversalManufacturerData::data() const {
  return data_;
}

void UniversalManufacturerData::set_data(const std::vector<uint8_t>& value_arg) {
  data_ = value_arg;
}


EncodableList UniversalManufacturerData::ToEncodableList() const {
  EncodableList list;
  list.reserve(2);
  list.push_back(EncodableValue(company_identifier_));
  list.push_back(EncodableValue(data_));
  return list;
}

UniversalManufacturerData UniversalManufacturerData::FromEncodableList(const EncodableList& list) {
  UniversalManufacturerData decoded(
    std::get<int64_t>(list[0]),
    std::get<std::vector<uint8_t>>(list[1]));
  return decoded;
}


PigeonInternalCodecSerializer::PigeonInternalCodecSerializer() {}

EncodableValue PigeonInternalCodecSerializer::ReadValueOfType(
  uint8_t type,
  flutter::ByteStreamReader* stream) const {
  switch (type) {
    case 129: {
        return CustomEncodableValue(UniversalBleScanResult::FromEncodableList(std::get<EncodableList>(ReadValue(stream))));
      }
    case 130: {
        return CustomEncodableValue(UniversalBleService::FromEncodableList(std::get<EncodableList>(ReadValue(stream))));
      }
    case 131: {
        return CustomEncodableValue(UniversalBleCharacteristic::FromEncodableList(std::get<EncodableList>(ReadValue(stream))));
      }
    case 132: {
        return CustomEncodableValue(UniversalScanFilter::FromEncodableList(std::get<EncodableList>(ReadValue(stream))));
      }
    case 133: {
        return CustomEncodableValue(UniversalManufacturerDataFilter::FromEncodableList(std::get<EncodableList>(ReadValue(stream))));
      }
    case 134: {
        return CustomEncodableValue(UniversalManufacturerData::FromEncodableList(std::get<EncodableList>(ReadValue(stream))));
      }
    default:
      return flutter::StandardCodecSerializer::ReadValueOfType(type, stream);
    }
}

void PigeonInternalCodecSerializer::WriteValue(
  const EncodableValue& value,
  flutter::ByteStreamWriter* stream) const {
  if (const CustomEncodableValue* custom_value = std::get_if<CustomEncodableValue>(&value)) {
    if (custom_value->type() == typeid(UniversalBleScanResult)) {
      stream->WriteByte(129);
      WriteValue(EncodableValue(std::any_cast<UniversalBleScanResult>(*custom_value).ToEncodableList()), stream);
      return;
    }
    if (custom_value->type() == typeid(UniversalBleService)) {
      stream->WriteByte(130);
      WriteValue(EncodableValue(std::any_cast<UniversalBleService>(*custom_value).ToEncodableList()), stream);
      return;
    }
    if (custom_value->type() == typeid(UniversalBleCharacteristic)) {
      stream->WriteByte(131);
      WriteValue(EncodableValue(std::any_cast<UniversalBleCharacteristic>(*custom_value).ToEncodableList()), stream);
      return;
    }
    if (custom_value->type() == typeid(UniversalScanFilter)) {
      stream->WriteByte(132);
      WriteValue(EncodableValue(std::any_cast<UniversalScanFilter>(*custom_value).ToEncodableList()), stream);
      return;
    }
    if (custom_value->type() == typeid(UniversalManufacturerDataFilter)) {
      stream->WriteByte(133);
      WriteValue(EncodableValue(std::any_cast<UniversalManufacturerDataFilter>(*custom_value).ToEncodableList()), stream);
      return;
    }
    if (custom_value->type() == typeid(UniversalManufacturerData)) {
      stream->WriteByte(134);
      WriteValue(EncodableValue(std::any_cast<UniversalManufacturerData>(*custom_value).ToEncodableList()), stream);
      return;
    }
  }
  flutter::StandardCodecSerializer::WriteValue(value, stream);
}

/// The codec used by UniversalBlePlatformChannel.
const flutter::StandardMessageCodec& UniversalBlePlatformChannel::GetCodec() {
  return flutter::StandardMessageCodec::GetInstance(&PigeonInternalCodecSerializer::GetInstance());
}

// Sets up an instance of `UniversalBlePlatformChannel` to handle messages through the `binary_messenger`.
void UniversalBlePlatformChannel::SetUp(
  flutter::BinaryMessenger* binary_messenger,
  UniversalBlePlatformChannel* api) {
  UniversalBlePlatformChannel::SetUp(binary_messenger, api, "");
}

void UniversalBlePlatformChannel::SetUp(
  flutter::BinaryMessenger* binary_messenger,
  UniversalBlePlatformChannel* api,
  const std::string& message_channel_suffix) {
  const std::string prepended_suffix = message_channel_suffix.length() > 0 ? std::string(".") + message_channel_suffix : "";
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.getBluetoothAvailabilityState" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          api->GetBluetoothAvailabilityState([reply](ErrorOr<int64_t>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.enableBluetooth" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          api->EnableBluetooth([reply](ErrorOr<bool>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.disableBluetooth" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          api->DisableBluetooth([reply](ErrorOr<bool>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.startScan" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_filter_arg = args.at(0);
          const auto* filter_arg = encodable_filter_arg.IsNull() ? nullptr : &(std::any_cast<const UniversalScanFilter&>(std::get<CustomEncodableValue>(encodable_filter_arg)));
          std::optional<FlutterError> output = api->StartScan(filter_arg);
          if (output.has_value()) {
            reply(WrapError(output.value()));
            return;
          }
          EncodableList wrapped;
          wrapped.push_back(EncodableValue());
          reply(EncodableValue(std::move(wrapped)));
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.stopScan" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          std::optional<FlutterError> output = api->StopScan();
          if (output.has_value()) {
            reply(WrapError(output.value()));
            return;
          }
          EncodableList wrapped;
          wrapped.push_back(EncodableValue());
          reply(EncodableValue(std::move(wrapped)));
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.connect" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          std::optional<FlutterError> output = api->Connect(device_id_arg);
          if (output.has_value()) {
            reply(WrapError(output.value()));
            return;
          }
          EncodableList wrapped;
          wrapped.push_back(EncodableValue());
          reply(EncodableValue(std::move(wrapped)));
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.disconnect" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          std::optional<FlutterError> output = api->Disconnect(device_id_arg);
          if (output.has_value()) {
            reply(WrapError(output.value()));
            return;
          }
          EncodableList wrapped;
          wrapped.push_back(EncodableValue());
          reply(EncodableValue(std::move(wrapped)));
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.setNotifiable" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          const auto& encodable_service_arg = args.at(1);
          if (encodable_service_arg.IsNull()) {
            reply(WrapError("service_arg unexpectedly null."));
            return;
          }
          const auto& service_arg = std::get<std::string>(encodable_service_arg);
          const auto& encodable_characteristic_arg = args.at(2);
          if (encodable_characteristic_arg.IsNull()) {
            reply(WrapError("characteristic_arg unexpectedly null."));
            return;
          }
          const auto& characteristic_arg = std::get<std::string>(encodable_characteristic_arg);
          const auto& encodable_ble_input_property_arg = args.at(3);
          if (encodable_ble_input_property_arg.IsNull()) {
            reply(WrapError("ble_input_property_arg unexpectedly null."));
            return;
          }
          const int64_t ble_input_property_arg = encodable_ble_input_property_arg.LongValue();
          api->SetNotifiable(device_id_arg, service_arg, characteristic_arg, ble_input_property_arg, [reply](std::optional<FlutterError>&& output) {
            if (output.has_value()) {
              reply(WrapError(output.value()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue());
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.discoverServices" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          api->DiscoverServices(device_id_arg, [reply](ErrorOr<EncodableList>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.readValue" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          const auto& encodable_service_arg = args.at(1);
          if (encodable_service_arg.IsNull()) {
            reply(WrapError("service_arg unexpectedly null."));
            return;
          }
          const auto& service_arg = std::get<std::string>(encodable_service_arg);
          const auto& encodable_characteristic_arg = args.at(2);
          if (encodable_characteristic_arg.IsNull()) {
            reply(WrapError("characteristic_arg unexpectedly null."));
            return;
          }
          const auto& characteristic_arg = std::get<std::string>(encodable_characteristic_arg);
          api->ReadValue(device_id_arg, service_arg, characteristic_arg, [reply](ErrorOr<std::vector<uint8_t>>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.requestMtu" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          const auto& encodable_expected_mtu_arg = args.at(1);
          if (encodable_expected_mtu_arg.IsNull()) {
            reply(WrapError("expected_mtu_arg unexpectedly null."));
            return;
          }
          const int64_t expected_mtu_arg = encodable_expected_mtu_arg.LongValue();
          api->RequestMtu(device_id_arg, expected_mtu_arg, [reply](ErrorOr<int64_t>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.writeValue" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          const auto& encodable_service_arg = args.at(1);
          if (encodable_service_arg.IsNull()) {
            reply(WrapError("service_arg unexpectedly null."));
            return;
          }
          const auto& service_arg = std::get<std::string>(encodable_service_arg);
          const auto& encodable_characteristic_arg = args.at(2);
          if (encodable_characteristic_arg.IsNull()) {
            reply(WrapError("characteristic_arg unexpectedly null."));
            return;
          }
          const auto& characteristic_arg = std::get<std::string>(encodable_characteristic_arg);
          const auto& encodable_value_arg = args.at(3);
          if (encodable_value_arg.IsNull()) {
            reply(WrapError("value_arg unexpectedly null."));
            return;
          }
          const auto& value_arg = std::get<std::vector<uint8_t>>(encodable_value_arg);
          const auto& encodable_ble_output_property_arg = args.at(4);
          if (encodable_ble_output_property_arg.IsNull()) {
            reply(WrapError("ble_output_property_arg unexpectedly null."));
            return;
          }
          const int64_t ble_output_property_arg = encodable_ble_output_property_arg.LongValue();
          api->WriteValue(device_id_arg, service_arg, characteristic_arg, value_arg, ble_output_property_arg, [reply](std::optional<FlutterError>&& output) {
            if (output.has_value()) {
              reply(WrapError(output.value()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue());
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.isPaired" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          api->IsPaired(device_id_arg, [reply](ErrorOr<bool>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.pair" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          api->Pair(device_id_arg, [reply](ErrorOr<bool>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.unPair" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          std::optional<FlutterError> output = api->UnPair(device_id_arg);
          if (output.has_value()) {
            reply(WrapError(output.value()));
            return;
          }
          EncodableList wrapped;
          wrapped.push_back(EncodableValue());
          reply(EncodableValue(std::move(wrapped)));
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.getSystemDevices" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_with_services_arg = args.at(0);
          if (encodable_with_services_arg.IsNull()) {
            reply(WrapError("with_services_arg unexpectedly null."));
            return;
          }
          const auto& with_services_arg = std::get<EncodableList>(encodable_with_services_arg);
          api->GetSystemDevices(with_services_arg, [reply](ErrorOr<EncodableList>&& output) {
            if (output.has_error()) {
              reply(WrapError(output.error()));
              return;
            }
            EncodableList wrapped;
            wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
            reply(EncodableValue(std::move(wrapped)));
          });
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
  {
    BasicMessageChannel<> channel(binary_messenger, "dev.flutter.pigeon.universal_ble.UniversalBlePlatformChannel.getConnectionState" + prepended_suffix, &GetCodec());
    if (api != nullptr) {
      channel.SetMessageHandler([api](const EncodableValue& message, const flutter::MessageReply<EncodableValue>& reply) {
        try {
          const auto& args = std::get<EncodableList>(message);
          const auto& encodable_device_id_arg = args.at(0);
          if (encodable_device_id_arg.IsNull()) {
            reply(WrapError("device_id_arg unexpectedly null."));
            return;
          }
          const auto& device_id_arg = std::get<std::string>(encodable_device_id_arg);
          ErrorOr<int64_t> output = api->GetConnectionState(device_id_arg);
          if (output.has_error()) {
            reply(WrapError(output.error()));
            return;
          }
          EncodableList wrapped;
          wrapped.push_back(EncodableValue(std::move(output).TakeValue()));
          reply(EncodableValue(std::move(wrapped)));
        } catch (const std::exception& exception) {
          reply(WrapError(exception.what()));
        }
      });
    } else {
      channel.SetMessageHandler(nullptr);
    }
  }
}

EncodableValue UniversalBlePlatformChannel::WrapError(std::string_view error_message) {
  return EncodableValue(EncodableList{
    EncodableValue(std::string(error_message)),
    EncodableValue("Error"),
    EncodableValue()
  });
}

EncodableValue UniversalBlePlatformChannel::WrapError(const FlutterError& error) {
  return EncodableValue(EncodableList{
    EncodableValue(error.code()),
    EncodableValue(error.message()),
    error.details()
  });
}

// Generated class from Pigeon that represents Flutter messages that can be called from C++.
UniversalBleCallbackChannel::UniversalBleCallbackChannel(flutter::BinaryMessenger* binary_messenger)
 : binary_messenger_(binary_messenger),
    message_channel_suffix_("") {}

UniversalBleCallbackChannel::UniversalBleCallbackChannel(
  flutter::BinaryMessenger* binary_messenger,
  const std::string& message_channel_suffix)
 : binary_messenger_(binary_messenger),
    message_channel_suffix_(message_channel_suffix.length() > 0 ? std::string(".") + message_channel_suffix : "") {}

const flutter::StandardMessageCodec& UniversalBleCallbackChannel::GetCodec() {
  return flutter::StandardMessageCodec::GetInstance(&PigeonInternalCodecSerializer::GetInstance());
}

void UniversalBleCallbackChannel::OnAvailabilityChanged(
  int64_t state_arg,
  std::function<void(void)>&& on_success,
  std::function<void(const FlutterError&)>&& on_error) {
  const std::string channel_name = "dev.flutter.pigeon.universal_ble.UniversalBleCallbackChannel.onAvailabilityChanged" + message_channel_suffix_;
  BasicMessageChannel<> channel(binary_messenger_, channel_name, &GetCodec());
  EncodableValue encoded_api_arguments = EncodableValue(EncodableList{
    EncodableValue(state_arg),
  });
  channel.Send(encoded_api_arguments, [channel_name, on_success = std::move(on_success), on_error = std::move(on_error)](const uint8_t* reply, size_t reply_size) {
    std::unique_ptr<EncodableValue> response = GetCodec().DecodeMessage(reply, reply_size);
    const auto& encodable_return_value = *response;
    const auto* list_return_value = std::get_if<EncodableList>(&encodable_return_value);
    if (list_return_value) {
      if (list_return_value->size() > 1) {
        on_error(FlutterError(std::get<std::string>(list_return_value->at(0)), std::get<std::string>(list_return_value->at(1)), list_return_value->at(2)));
      } else {
        on_success();
      }
    } else {
      on_error(CreateConnectionError(channel_name));
    } 
  });
}

void UniversalBleCallbackChannel::OnPairStateChange(
  const std::string& device_id_arg,
  bool is_paired_arg,
  const std::string* error_arg,
  std::function<void(void)>&& on_success,
  std::function<void(const FlutterError&)>&& on_error) {
  const std::string channel_name = "dev.flutter.pigeon.universal_ble.UniversalBleCallbackChannel.onPairStateChange" + message_channel_suffix_;
  BasicMessageChannel<> channel(binary_messenger_, channel_name, &GetCodec());
  EncodableValue encoded_api_arguments = EncodableValue(EncodableList{
    EncodableValue(device_id_arg),
    EncodableValue(is_paired_arg),
    error_arg ? EncodableValue(*error_arg) : EncodableValue(),
  });
  channel.Send(encoded_api_arguments, [channel_name, on_success = std::move(on_success), on_error = std::move(on_error)](const uint8_t* reply, size_t reply_size) {
    std::unique_ptr<EncodableValue> response = GetCodec().DecodeMessage(reply, reply_size);
    const auto& encodable_return_value = *response;
    const auto* list_return_value = std::get_if<EncodableList>(&encodable_return_value);
    if (list_return_value) {
      if (list_return_value->size() > 1) {
        on_error(FlutterError(std::get<std::string>(list_return_value->at(0)), std::get<std::string>(list_return_value->at(1)), list_return_value->at(2)));
      } else {
        on_success();
      }
    } else {
      on_error(CreateConnectionError(channel_name));
    } 
  });
}

void UniversalBleCallbackChannel::OnScanResult(
  const UniversalBleScanResult& result_arg,
  std::function<void(void)>&& on_success,
  std::function<void(const FlutterError&)>&& on_error) {
  const std::string channel_name = "dev.flutter.pigeon.universal_ble.UniversalBleCallbackChannel.onScanResult" + message_channel_suffix_;
  BasicMessageChannel<> channel(binary_messenger_, channel_name, &GetCodec());
  EncodableValue encoded_api_arguments = EncodableValue(EncodableList{
    CustomEncodableValue(result_arg),
  });
  channel.Send(encoded_api_arguments, [channel_name, on_success = std::move(on_success), on_error = std::move(on_error)](const uint8_t* reply, size_t reply_size) {
    std::unique_ptr<EncodableValue> response = GetCodec().DecodeMessage(reply, reply_size);
    const auto& encodable_return_value = *response;
    const auto* list_return_value = std::get_if<EncodableList>(&encodable_return_value);
    if (list_return_value) {
      if (list_return_value->size() > 1) {
        on_error(FlutterError(std::get<std::string>(list_return_value->at(0)), std::get<std::string>(list_return_value->at(1)), list_return_value->at(2)));
      } else {
        on_success();
      }
    } else {
      on_error(CreateConnectionError(channel_name));
    } 
  });
}

void UniversalBleCallbackChannel::OnValueChanged(
  const std::string& device_id_arg,
  const std::string& characteristic_id_arg,
  const std::vector<uint8_t>& value_arg,
  std::function<void(void)>&& on_success,
  std::function<void(const FlutterError&)>&& on_error) {
  const std::string channel_name = "dev.flutter.pigeon.universal_ble.UniversalBleCallbackChannel.onValueChanged" + message_channel_suffix_;
  BasicMessageChannel<> channel(binary_messenger_, channel_name, &GetCodec());
  EncodableValue encoded_api_arguments = EncodableValue(EncodableList{
    EncodableValue(device_id_arg),
    EncodableValue(characteristic_id_arg),
    EncodableValue(value_arg),
  });
  channel.Send(encoded_api_arguments, [channel_name, on_success = std::move(on_success), on_error = std::move(on_error)](const uint8_t* reply, size_t reply_size) {
    std::unique_ptr<EncodableValue> response = GetCodec().DecodeMessage(reply, reply_size);
    const auto& encodable_return_value = *response;
    const auto* list_return_value = std::get_if<EncodableList>(&encodable_return_value);
    if (list_return_value) {
      if (list_return_value->size() > 1) {
        on_error(FlutterError(std::get<std::string>(list_return_value->at(0)), std::get<std::string>(list_return_value->at(1)), list_return_value->at(2)));
      } else {
        on_success();
      }
    } else {
      on_error(CreateConnectionError(channel_name));
    } 
  });
}

void UniversalBleCallbackChannel::OnConnectionChanged(
  const std::string& device_id_arg,
  bool connected_arg,
  const std::string* error_arg,
  std::function<void(void)>&& on_success,
  std::function<void(const FlutterError&)>&& on_error) {
  const std::string channel_name = "dev.flutter.pigeon.universal_ble.UniversalBleCallbackChannel.onConnectionChanged" + message_channel_suffix_;
  BasicMessageChannel<> channel(binary_messenger_, channel_name, &GetCodec());
  EncodableValue encoded_api_arguments = EncodableValue(EncodableList{
    EncodableValue(device_id_arg),
    EncodableValue(connected_arg),
    error_arg ? EncodableValue(*error_arg) : EncodableValue(),
  });
  channel.Send(encoded_api_arguments, [channel_name, on_success = std::move(on_success), on_error = std::move(on_error)](const uint8_t* reply, size_t reply_size) {
    std::unique_ptr<EncodableValue> response = GetCodec().DecodeMessage(reply, reply_size);
    const auto& encodable_return_value = *response;
    const auto* list_return_value = std::get_if<EncodableList>(&encodable_return_value);
    if (list_return_value) {
      if (list_return_value->size() > 1) {
        on_error(FlutterError(std::get<std::string>(list_return_value->at(0)), std::get<std::string>(list_return_value->at(1)), list_return_value->at(2)));
      } else {
        on_success();
      }
    } else {
      on_error(CreateConnectionError(channel_name));
    } 
  });
}

}  // namespace universal_ble
