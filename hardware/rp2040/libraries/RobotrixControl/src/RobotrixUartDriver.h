#pragma once
#include <Arduino.h>
#include <cstdint>

using CallbackCmdRouter = void (*)(void *context, const uint8_t *data,
                                   uint8_t len);

class UartDriver {
public:
  void setup(uint8_t address, unsigned long baud, HardwareSerial *serialPort);
  void write(uint8_t address /*!!Unsused!!*/, uint8_t *data, uint8_t size);
  void debugOn(bool debug = true, Stream *DebugSerial = &Serial);
  void Serial_poll();
  void callbackToCmdRouter(CallbackCmdRouter cb, void *ctx);

private:
  CallbackCmdRouter _CmdRouterCallback = nullptr;
  void *_CmdRouterContext = nullptr;
  
  static UartDriver *_instance;

  void onReceive(uint8_t len);
  bool _DebugOn = false;
  uint8_t _address;
  Stream *_DebugSerial;
  HardwareSerial *_Serial;
};