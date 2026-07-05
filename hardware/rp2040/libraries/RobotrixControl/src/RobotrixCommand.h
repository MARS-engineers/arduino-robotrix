#pragma once
#include <cstdint>
#include <stdint.h>
#include <Arduino.h>

using RemoteCallback = void (*)(const uint8_t *data, uint8_t data_len);

class CommandRouter {
public:
  void debugOn(bool debug = true, Stream *DebugSerial = &Serial);

  void setDeviceAddress(uint8_t address);
  uint8_t getDeviceAddress();

  bool registerCommand(uint8_t cmd, RemoteCallback cb);
  bool registerOnReceive(RemoteCallback cb);

  void dispatch(const uint8_t *data, uint8_t len);
  static void dispatchCallback(void *context, const uint8_t *data,
                               uint8_t len) {
    static_cast<CommandRouter *>(context)->dispatch(data, len);
  }

  void setCheckCrc(bool b) { _checkCrc = b; }

  uint8_t parsePacket(const uint8_t *data, uint8_t len);

  uint8_t makePacket(uint8_t *payload, uint8_t len, uint8_t telemetry_type,
                     uint8_t dest_address,
                     void callbackToWrite(uint8_t address, const uint8_t *p,
                                          uint8_t len));
  struct dataFormat {
    uint8_t command;
    uint8_t subCommand;
    uint8_t arg[4];
  };

  dataFormat convertData(const uint8_t *data, uint8_t len);

private:
  bool _DebugOn = false;
  Stream *_DebugSerial;

  bool _checkCrc = true;
  uint8_t crc8(const uint8_t *ptr, uint8_t len);
  struct Entry {
    uint8_t cmd;
    RemoteCallback cb;
  };
  RemoteCallback everyCmdCb;

  uint8_t _deviceAddress;
  static constexpr uint8_t MAX_CMDS = 16;
  Entry _table[MAX_CMDS];
  uint8_t _count = 0;
};

extern CommandRouter Remote;
