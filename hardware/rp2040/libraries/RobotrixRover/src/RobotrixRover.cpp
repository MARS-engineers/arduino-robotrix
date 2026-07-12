#include "./RobotrixRover.h"

#include <RobotrixMotors.h>
#include <cstdint>

Motor motorFL(PIN_MOT_2_E, PIN_MOT_2_A, PIN_MOT_2_B);
Motor motorFR(PIN_MOT_3_E, PIN_MOT_3_A, PIN_MOT_3_B);
Motor motorRL(PIN_MOT_1_E, PIN_MOT_1_A, PIN_MOT_1_B);
Motor motorRR(PIN_MOT_4_E, PIN_MOT_4_A, PIN_MOT_4_B);

void RoverClass::setupMotors() {
  pinMode(_pin_stby, OUTPUT);
  // Setup all motors
  motorFL.setup();
  motorFR.setup();
  motorRL.setup();
  motorRR.setup();
}

void RoverClass::stop() {
  motorFL.setSpeed(0);
  motorFR.setSpeed(0);
  motorRL.setSpeed(0);
  motorRR.setSpeed(0);
}
void RoverClass::setMaxSpeed(uint8_t speed) {
  maxSpeedValue = speed;
  motorFL.setMaxSpeed(speed);
  motorFR.setMaxSpeed(speed);
  motorRL.setMaxSpeed(speed);
  motorRR.setMaxSpeed(speed);
}
void RoverClass::motorRun(uint8_t motor, int8_t speed) {
  switch (motor) {
  case 1:
    motorFL.setSpeed(speed);
    break;
  case 2:
    motorFR.setSpeed(speed);
    break;
  case 3:
    motorRL.setSpeed(speed);
    break;
  case 4:
    motorRR.setSpeed(speed);
    break;
  }
}

void RoverClass::motorsEnable() { digitalWrite(_pin_stby, HIGH); }
void RoverClass::motorsDisable() { digitalWrite(_pin_stby, LOW); }

void RoverClass::moveXYR(int16_t x, int16_t y, int16_t r) {
  // 1. Compute raw wheel speeds
  int32_t fl = y + x - r;
  int32_t fr = y - x + r;
  int32_t rl = y - x - r;
  int32_t rr = y + x + r;

  // 2. Find maximum magnitude
  int16_t maxVal = max(max(abs(fl), abs(fr)), max(abs(rl), abs(rr)));
  //Serial.printf("fl: %d, fr: %d, rl: %d, rr: %d, Magnitude: %d\n", fl, fr, rl,
    //            rr, maxVal);

  // 3. Normalize to fit -127..127

  if (maxVal > Rover.maxSpeedValue) {
    fl = fl * Rover.maxSpeedValue / maxVal;
    fr = fr * Rover.maxSpeedValue / maxVal;
    rl = rl * Rover.maxSpeedValue / maxVal;
    rr = rr * Rover.maxSpeedValue / maxVal;
  }

  //  4. Send to motors
  motorFL.setSpeed(fl);
  motorFR.setSpeed(fr);
  motorRL.setSpeed(rl);
  motorRR.setSpeed(rr);
}

void RoverClass::move(Direction dir, uint8_t speed) {
  // int8_t s = map(speed, 0, 100, 0, 100);
  int8_t s = speed;

  switch (dir) {
  case FORWARD:
    moveXYR(0, s, 0);
    break;
  case BACKWARD:
    moveXYR(0,s, 0);
    break;
  case SLIDE_LEFT:
    moveXYR(-s, 0, 0);
    break;
  case SLIDE_RIGHT:
    moveXYR(s, 0, 0);
    break;
  case ROTATE_LEFT:
    moveXYR(0, 0, -s);
    break;
  case ROTATE_RIGHT:
    moveXYR(0, 0, s);
    break;
  case STOP:
    moveXYR(0, 0, 0);
    break;

  case DIAG_FWD_LEFT:
  case DIAG_FWD_RIGHT:
  case DIAG_BACK_LEFT:
  case DIAG_BACK_RIGHT:
    break;
  }
}

RoverClass Rover;