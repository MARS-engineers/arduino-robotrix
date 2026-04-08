#include "./RobotrixRover.h"

#include <RobotrixMotors.h>

Motor motorFL(PIN_MOT_1_E, PIN_MOT_1_A, PIN_MOT_1_B);
Motor motorFR(PIN_MOT_3_E, PIN_MOT_3_A, PIN_MOT_3_B);
Motor motorRL(PIN_MOT_2_E, PIN_MOT_2_A, PIN_MOT_2_B);
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

void RoverClass::moveXYR(uint8_t x, uint8_t y, uint8_t r) {
  // 1. Compute raw wheel speeds
  int16_t fl = y + x + r;
  int16_t fr = y - x - r;
  int16_t rl = y - x + r;
  int16_t rr = y + x - r;

  // 2. Find maximum magnitude
  int16_t maxVal = max(max(abs(fl), abs(fr)), max(abs(rl), abs(rr)));

  // 3. Normalize to fit -127..127
  if (maxVal > 127) {
    fl = fl * 127 / maxVal;
    fr = fr * 127 / maxVal;
    rl = rl * 127 / maxVal;
    rr = rr * 127 / maxVal;
  }

  // 4. Send to motors
  motorFL.SetSpeed((int8_t)fl);
  motorFR.SetSpeed((int8_t)fr);
  motorRL.SetSpeed((int8_t)rl);
  motorRR.SetSpeed((int8_t)rr);
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