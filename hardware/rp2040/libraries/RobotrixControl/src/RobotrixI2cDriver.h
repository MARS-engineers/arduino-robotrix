#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <cstdint>

using CallbackCmdRouter = void (*)(void *context, const uint8_t *data,
                                   uint8_t len);

class I2cDriver {
public:
  void setup(uint8_t address = 0x55, TwoWire *theWire = &Wire);
  void callbackToCmdRouter(CallbackCmdRouter cb, void *ctx);
  void write(uint8_t address, uint8_t *data, uint8_t size);
  void debugOn(bool debug = true, Stream *DebugSerial = &Serial);

private:
  CallbackCmdRouter _CmdRouterCallback = nullptr;
  void *_CmdRouterContext = nullptr;

  static void onReceiveStatic(int len);
  void onReceive(uint8_t len);

  static I2cDriver *_instance;

  bool _DebugOn = false;
  Stream *_DebugSerial;
  TwoWire *_theWire;
};
