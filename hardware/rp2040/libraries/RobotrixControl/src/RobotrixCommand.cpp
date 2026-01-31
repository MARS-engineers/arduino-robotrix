#include "./RobotrixCommand.h"

CommandRouter Remote;

bool CommandRouter::registerCommand(uint8_t cmd, RemoteCallback cb) {
  if (_count >= MAX_CMDS || cb == nullptr)
    return false;

  _table[_count++] = {cmd, cb};
  return true;
}

void CommandRouter::dispatch(const uint8_t* data, uint8_t len) {
  if (len < 2) return;

  uint8_t cmd    = data[0];
  uint8_t subcmd = data[1];

  for (uint8_t i = 0; i < _count; i++) {
    if (_table[i].cmd == cmd) {
      _table[i].cb(subcmd, data + 2, len - 2);
      return;
    }
  }
}
