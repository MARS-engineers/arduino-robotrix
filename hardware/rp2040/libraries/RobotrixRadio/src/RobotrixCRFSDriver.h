#pragma once
#include "CRSFforArduino.hpp"
#include <Arduino.h>
#include <cstdint>

class CRFSBus {
public:
  void setup(uint32_t baudRate = 420000);
  void update(void);
  static const uint32_t rcChannelCount = crsfProtocol::RC_CHANNEL_COUNT;
  uint16_t ch[rcChannelCount + 1];  // Channel value in us, ch[0] is not used
  void write(const uint8_t *p, size_t len);
  void sendBat(float voltage, float current, uint8_t remaining);
private:
  void onReceive(serialReceiverLayer::rcChannels_t* rcChannels);
  static void onReceiveStatic(serialReceiverLayer::rcChannels_t* rcChannels);
  uint8_t crsf_crc8(const uint8_t *ptr, uint8_t len);
  
  bool crfsOK = false;
};

extern CRFSBus CRFSDriver;
