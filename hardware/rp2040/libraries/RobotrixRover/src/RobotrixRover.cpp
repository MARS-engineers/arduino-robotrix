#include "./RobotrixRover.h"

#include <RobotrixMotors.h>
#include <cstdint>

Motor motorFL(PIN_MOT_2_E, PIN_MOT_2_A, PIN_MOT_2_B);
Motor motorFR(PIN_MOT_3_E, PIN_MOT_3_A, PIN_MOT_3_B);
Motor motorRL(PIN_MOT_1_E, PIN_MOT_1_A, PIN_MOT_1_B);
Motor motorRR(PIN_MOT_4_E, PIN_MOT_4_A, PIN_MOT_4_B);

void RoverClass::setupMotors() {
  pinMode(PIN_MOT_STBY, OUTPUT);
  // Setup all motors
  motorFL.setup();
  motorFR.setup();
  motorRL.setup();
  motorRR.setup();
}

void RoverClass::stop() {
  motorFL.SetSpeed(0);
  motorFR.SetSpeed(0);
  motorRL.SetSpeed(0);
  motorRR.SetSpeed(0);
}
void RoverClass::setMaxSpeed(uint8_t speed) {
  motorFL.setMaxSpeed(speed);
  motorFR.setMaxSpeed(speed);
  motorRL.setMaxSpeed(speed);
  motorRR.setMaxSpeed(speed);
}
void RoverClass::MotorRun(uint8_t motor, int8_t speed) {
  switch (motor) {
  case 1:
    motorFL.SetSpeed(speed);
    break;
  case 2:
    motorFR.SetSpeed(speed);
    break;
  case 3:
    motorRL.SetSpeed(speed);
    break;
  case 4:
    motorRR.SetSpeed(speed);
    break;
  }
}

void RoverClass::motorsEnable() { digitalWrite(PIN_MOT_STBY, HIGH); }
void RoverClass::motorsDisable() { digitalWrite(PIN_MOT_STBY, LOW); }

void RoverClass::moveXYR(int8_t x, int8_t y, int8_t r) {
  // 1. Compute raw wheel speeds
  int16_t fl = y + x - r;
  int16_t fr = y - x + r;
  int16_t rl = y - x - r;
  int16_t rr = y + x + r;

  // 2. Find maximum magnitude
  int16_t maxVal = max(max(abs(fl), abs(fr)), max(abs(rl), abs(rr)));
  // Serial.printf("fl: %d, fr: %d, rl: %d, rr: %d, Magnitude: %d\n", fl, fr,
  // rl,                rr, maxVal);

  // 3. Normalize to fit -127..127

  if (maxVal > Rover.maxSpeedValue) {
    fl = fl * Rover.maxSpeedValue / maxVal;
    fr = fr * Rover.maxSpeedValue / maxVal;
    rl = rl * Rover.maxSpeedValue / maxVal;
    rr = rr * Rover.maxSpeedValue / maxVal;
  }

  //  4. Send to motors
  motorFL.SetSpeed(fl);
  motorFR.SetSpeed(fr);
  motorRL.SetSpeed(rl);
  motorRR.SetSpeed(rr);
}

void RoverClass::move(Direction dir, uint8_t speed) {
  int8_t s = map(speed, 0, 100, 0, 100);

  switch (dir) {
  case FORWARD:
    moveXYR(s, 0, 0);
    break;
  case BACKWARD:
    moveXYR(-s, 0, 0);
    break;
  case SLIDE_LEFT:
    moveXYR(0, -s, 0);
    break;
  case SLIDE_RIGHT:
    moveXYR(0, s, 0);
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