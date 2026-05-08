#include "./RobotrixCommand.h"
#include "Arduino.h"
#include <cstdint>

CommandRouter Remote;

bool CommandRouter::registerCommand(uint8_t cmd, RemoteCallback cb) {
  if (_count >= MAX_CMDS || cb == nullptr)
    return false;

  _table[_count++] = {cmd, cb};
  return true;
}

bool CommandRouter::registerOnReceive(RemoteCallback cb) {
  everyCmdCb = cb;
  return true;
}

void CommandRouter::dispatch(const uint8_t *data, uint8_t len) {
  if (len < 2)
    return;
  uint8_t cmd = data[0];
  uint8_t subcmd = data[1];

  everyCmdCb(data, len);

  /*  Serial.printf("I2C Cmd: 0x%02x, SubCmd: 0x%02x, Arg1: 0x%02x, Arg2:
    0x%02x, " "Arg3: 0x%02x", data[0], data[1], data[2], data[3], data[4]);

    Serial.printf("bytes: %i, data: ", len);
    for (uint8_t i = 0; i <= len; i++) {
      Serial.printf(" %02x", data[i]);
    }
    Serial.println("");
  */

  for (uint8_t i = 0; i < _count; i++) {
    if (_table[i].cmd == cmd) {
      _table[i].cb(data, len);
      return;
    }
  }
}

CommandRouter::dataFormat CommandRouter::convertData(const uint8_t *data,
                                                     uint8_t len) {
  CommandRouter::dataFormat df;
  if (len == 0)
    return df;

  uint8_t dfp = 0;

  df.command = data[dfp++];

  if (len >= 1)
    df.subCommand = data[dfp++];

  for (uint8_t i = 0; i < len - 2; i++) {
    df.arg[i] = data[dfp++];
  }

  return df;
}