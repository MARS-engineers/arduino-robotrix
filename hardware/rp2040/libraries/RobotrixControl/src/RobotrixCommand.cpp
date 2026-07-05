#include "./RobotrixCommand.h"
#include "Arduino.h"
#include <cstdint>

CommandRouter Remote;

void CommandRouter::setDeviceAddress(uint8_t address) {
  _deviceAddress = address;
}

uint8_t CommandRouter::getDeviceAddress() { return _deviceAddress; }

bool CommandRouter::registerCommand(uint8_t cmd, RemoteCallback cb) {
  if (_count >= MAX_CMDS || cb == nullptr)
    return false;

  _table[_count++] = {cmd, cb};
  return true;
}

bool CommandRouter::registerOnReceive(RemoteCallback cb) {
  everyCmdCb = cb;
  return true;
}

void CommandRouter::dispatch(const uint8_t *data, uint8_t len) {
  if (len < 2)
    return;

  // parsePacket(data, len);

  everyCmdCb(data, len);

  for (uint8_t i = 0; i < _count; i++) {
    if (_table[i].cmd == data[0]) {
      _table[i].cb(data, len);
      return;
    }
  }
}

uint8_t CommandRouter::parsePacket(const uint8_t *data, uint8_t len) {
  uint8_t address = data[0];
  uint8_t data_len = data[1];
  uint8_t telemetry_type = data[2];
  uint8_t crc = data[data_len - 1];

  uint8_t payload[60];

  for (uint8_t i = 0; i < data_len - 1; i++) {
    payload[i] = data[i + 3];
  }

  if (_checkCrc) {
    uint8_t calc = crc8(&data[2], data_len +1);

    if (crc != calc) {
      return 0;
    }
  }

  for (uint8_t i = 0; i < _count; i++) {
    if (_table[i].cmd == telemetry_type) {
      _table[i].cb(payload, len);
    }
  }

  return data_len;
}

uint8_t CommandRouter::makePacket(
    uint8_t *payload, uint8_t len, uint8_t telemetry_type, uint8_t dest_address,
    void callbackToWrite(uint8_t address, const uint8_t *p, uint8_t len)) {

  uint8_t buf[64]; // Init bufer
  uint8_t i = 0;   // Init pointer

  buf[i++] = _deviceAddress; // Add device address

  uint8_t len_index = i++; // Reserve length (fill later)

  buf[i++] = telemetry_type; // custom telemetry type

  if (len > 60)
    return 0; // Exit if payload len is > 60 bytes

  for (uint8_t y = 0; y < len; y++) { // Add payload
    buf[i++] = payload[y];
  }

  uint8_t payload_len = i - 2;      // type + payload
  buf[len_index] = payload_len + 1; // + CRC

  buf[i++] = crc8(&buf[2], payload_len + 1); // Add CRC

  callbackToWrite(dest_address, buf, i);
  return i;
}

CommandRouter::dataFormat CommandRouter::convertData(const uint8_t *data,
                                                     uint8_t len) {
  CommandRouter::dataFormat df;
  if (len == 0)
    return df;

  uint8_t dfp = 0;

  df.command = data[dfp++];

  if (len >= 1)
    df.subCommand = data[dfp++];

  for (uint8_t i = 0; i < len - 2; i++) {
    df.arg[i] = data[dfp++];
  }

  return df;
}

// Vibecoded shit
uint8_t CommandRouter::crc8(const uint8_t *ptr, uint8_t len) {
  uint8_t crc = 0;
  while (len--) {
    crc ^= *ptr++;
    for (uint8_t i = 0; i < 8; i++) {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0xD5;
      else
        crc <<= 1;
    }
  }
  return crc;
}