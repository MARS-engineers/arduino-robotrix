#pragma once

#include <Arduino.h>
#include <cstdint>

#ifndef RoverOne
#error "This code is intended to run on MARS-Engineers Robotrix Rover board and compilled using https://github.com/MARS-engineers/arduino-boards/ pacakge"
#endif





class RoverClass {
private:
  pin_size_t _pin_stby = PIN_MOT_STBY;
public:
  enum Direction : uint8_t {
    STOP = 0x00,
    FORWARD = 0x01,
    BACKWARD = 0x02,
    SLIDE_RIGHT = 0x03,
    SLIDE_LEFT = 0x04,
    DIAG_FWD_LEFT = 0x05,
    DIAG_FWD_RIGHT = 0x06,
    DIAG_BACK_LEFT = 0x07,
    DIAG_BACK_RIGHT = 0x08,
    ROTATE_LEFT = 0x09,
    ROTATE_RIGHT = 0x0A
  };

  void setupMotors(void);

  void stop(void);
  void stopSlow(void);
  void move(Direction dir, uint8_t speed);
  void moveXYR(int16_t x, int16_t y, int16_t r);
  void motorsEnable();
  void motorsDisable();
  void motorRun(uint8_t motor, int8_t speed);
  void setMaxSpeed(uint8_t speed);
  uint8_t maxSpeedValue = 255;
};

extern RoverClass Rover;