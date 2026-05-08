#pragma once
#include <cstdint>
#include <stdint.h>

using RemoteCallback = void (*)(const uint8_t *data,
                                uint8_t data_len);

class CommandRouter {
public:
  bool registerCommand(uint8_t cmd, RemoteCallback cb);
  bool registerOnReceive(RemoteCallback cb);

  void dispatch(const uint8_t *data, uint8_t len);

  struct dataFormat {
    uint8_t command;
    uint8_t subCommand;
    uint8_t arg[4];
  };

  dataFormat convertData(const uint8_t *data, uint8_t len);

private:
  struct Entry {
    uint8_t cmd;
    RemoteCallback cb;
  };
  RemoteCallback everyCmdCb;

  static constexpr uint8_t MAX_CMDS = 16;
  Entry _table[MAX_CMDS];
  uint8_t _count = 0;
};

extern CommandRouter Remote;
