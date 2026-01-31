#pragma once
#include <stdint.h>

using RemoteCallback = void (*)(uint8_t subcmd,
                                const uint8_t* args,
                                uint8_t arg_len);

class CommandRouter {
public:
  bool registerCommand(uint8_t cmd, RemoteCallback cb);

  void dispatch(const uint8_t* data, uint8_t len);

private:
  struct Entry {
    uint8_t cmd;
    RemoteCallback cb;
  };

  static constexpr uint8_t MAX_CMDS = 16;
  Entry _table[MAX_CMDS];
  uint8_t _count = 0;
};

extern CommandRouter Remote;
