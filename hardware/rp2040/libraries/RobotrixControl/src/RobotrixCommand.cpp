#include "./RobotrixCommand.h"
#include "Arduino.h"
#include <cstdint>
#include <cstring>

CommandRouter Remote;

void CommandRouter::setDeviceAddress(uint8_t address) {
  _deviceAddress = address;
}
void CommandRouter::debugOn(uint8_t debug, Stream *DebugSerial) {
  _DebugSerial = DebugSerial;
  _Debug = debug;
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

  parsePacket(data, len);

  everyCmdCb(data, len);
  /*
    for (uint8_t i = 0; i < _count; i++) {
      if (_table[i].cmd == data[0]) {
        _table[i].cb(data, len);
        return;
      }
    }*/
}

uint8_t CommandRouter::parsePacket(const uint8_t *data, uint8_t len) {
  uint8_t address = data[0];
  uint8_t data_len = data[1];
  if (data_len > 60 || data_len < 2)
    return 0;

  uint8_t telemetry_type = data[2];
  uint8_t crc = data[len - 1];
  uint8_t crc_calc = crc8(&data[2], data_len);

  uint8_t payload[60];

  uint8_t payload_len = data_len - 2;
  for (uint8_t i = 0; i < payload_len; i++) {
    payload[i] = data[i + 3]; // Address + len + type
  }

  if (_Debug >= 1) {
    _DebugSerial->printf("Address: 0x%02x, type: 0x%02x, crc: %i, crc_calc: "
                         "%i, bytes: %i, data: ",
                         address, telemetry_type, crc, crc_calc, payload_len);

    for (uint8_t i = 0; i < payload_len; i++) {
      _DebugSerial->printf(" %02x", payload[i]);
    }

    _DebugSerial->println("");
  }

  if (_checkCrc) {

    if (crc != crc_calc) {
      return 0;
    }
  }

  for (uint8_t i = 0; i < _count; i++) {
    if (_table[i].cmd == telemetry_type) {
      _table[i].cb(payload, payload_len);
    }
  }

  return payload_len;
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

void CommandRouter::poll(HardwareSerial *serialPort) {
  if (serialPort->available()) {
    onReceive(serialPort);
  }
}

void CommandRouter::onReceive(HardwareSerial *serialPort) {

  uint8_t rxBuf[128];
  uint8_t rxLen = 0;

  while (serialPort->available()) {
    if (rxLen < sizeof(rxBuf)) {
      uint8_t b = serialPort->read();
      rxBuf[rxLen++] = b;
    }
  }

  while (rxLen >= 2) {

    uint8_t packetLen = rxBuf[1];

    if (packetLen > 60 || packetLen < 2) {
      // invalid length
      memmove(rxBuf, rxBuf + 1, --rxLen);
      continue;
    }

    uint8_t totalLen = packetLen + 2;

    if (rxLen < totalLen) {
      break; // wait for more bytes
    }

    if (_Debug >= 2) {
      _DebugSerial->printf("bytes: %i, data: ", totalLen);
      for (uint8_t i = 0; i < totalLen; i++) {
        _DebugSerial->printf(" %02x", rxBuf[i]);
      }
      _DebugSerial->println("");
    }

    dispatch(rxBuf, totalLen);

    memmove(rxBuf, rxBuf + totalLen, rxLen - totalLen);

    rxLen -= totalLen;
  }
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