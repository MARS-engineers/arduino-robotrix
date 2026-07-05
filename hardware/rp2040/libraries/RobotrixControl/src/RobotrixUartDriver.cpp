#include "RobotrixUartDriver.h"
#include "RobotrixCommand.h"
#include <cstddef>
#include <cstdint>

UartDriver *UartDriver::_instance = nullptr;

void UartDriver::setup(unsigned long baud, HardwareSerial *serialPort) {
  _instance = this;
  _Serial = serialPort;
  _Serial->begin(baud);
}

void UartDriver::callbackToCmdRouter(CallbackCmdRouter cb, void *ctx) {
  _CmdRouterCallback = cb;
  _CmdRouterContext = ctx;
}

void UartDriver::serial_poll() {
  int bytes = _Serial->available();

  if (bytes) {
    onReceive(bytes);
  }
}

void UartDriver::debugOn(bool debug, Stream *DebugSerial) {
  _DebugSerial = DebugSerial;
  _DebugOn = debug;
}

void UartDriver::write(uint8_t address /*!!Unsused!!*/, const uint8_t *data,
                       uint8_t size) {
  if (_instance) {
    _Serial->write(data, size);
  }
}

void UartDriver::onReceive(uint8_t len) {
  uint8_t buf[16];
  uint8_t i = 0;

  while (_Serial->available() && i < sizeof(buf)) {
    buf[i++] = _Serial->read();
  }

  if (_DebugOn) {
    _DebugSerial->printf("bytes: %i, data: ", len);
    for (uint8_t i = 0; i <= len; i++) {
      _DebugSerial->printf(" %02x", buf[i]);
    }
    _DebugSerial->println("");
  }

  if (_CmdRouterCallback) {
    _CmdRouterCallback(_CmdRouterContext, buf, i);
  }
}