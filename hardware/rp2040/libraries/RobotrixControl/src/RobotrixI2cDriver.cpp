#include "RobotrixI2cDriver.h"
#include "RobotrixCommand.h"
#include <cstddef>
#include <cstdint>

I2cDriver *I2cDriver::_instance = nullptr;

void I2cDriver::setup(uint8_t address, TwoWire *theWire) {
  _instance = this;
  _theWire = theWire;
  _theWire->begin(address);
  _theWire->onReceive(onReceiveStatic);
}

void I2cDriver::callbackToCmdRouter(CallbackCmdRouter cb, void *ctx) {
  _CmdRouterCallback = cb;
  _CmdRouterContext = ctx;
}

void I2cDriver::write(uint8_t address, uint8_t *data, uint8_t size) {
  if (_instance) {
    _theWire->writeAsync(address, data, size);
  }
}

void I2cDriver::onReceiveStatic(int len) {

  if (_instance) {
    _instance->onReceive(len);
  }
}

void I2cDriver::debugOn(bool debug, Stream *DebugSerial) {
  _DebugSerial = DebugSerial;
  _DebugOn = debug;
}

void I2cDriver::onReceive(uint8_t len) {
  uint8_t buf[16];
  uint8_t i = 0;

  while (_theWire->available() && i < sizeof(buf))
    buf[i++] = _theWire->read();

  if (_CmdRouterCallback) {
    _CmdRouterCallback(_CmdRouterContext, buf, i);
  }

  if (_DebugOn) {
    _DebugSerial->printf("bytes: %i, data: ", len);
    for (uint8_t i = 0; i <= len; i++) {
      _DebugSerial->printf(" %02x", buf[i]);
    }
    _DebugSerial->println("");
  }
}