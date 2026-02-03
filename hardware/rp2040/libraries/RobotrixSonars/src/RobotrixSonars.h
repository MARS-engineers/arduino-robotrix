#pragma once
#include <Arduino.h>

class SonarsClass {
  using IRQEvent = void (*)();

private:
  bool _sonarsEnable = false;
  IRQEvent RaiseEvent;
  void _sendPing();
  void _startPulse();
  void _endPulse();
  void dispatchCallback();

public:
  void begin(void);
  void enable();
  void disable();
  void setMinMaxRange(uint8_t min, uint8_t max);
  void regitsterCallbackIRQ(IRQEvent Event); // Call Event when sonar echo is triggered
  void doSonar();
  uint8_t readSonar(SonarDirections d);
};

extern SonarsClass Sonars;