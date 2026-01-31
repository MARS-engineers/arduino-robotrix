#pragma once

#include <Arduino.h>

class CarClass {
private:
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
  void moveXYR(uint8_t x, uint8_t y, uint8_t r);
  void motorsEnable();
  void motorsDisable();
  void MotorRun(uint8_t motor, int8_t speed);
};

extern CarClass Car;