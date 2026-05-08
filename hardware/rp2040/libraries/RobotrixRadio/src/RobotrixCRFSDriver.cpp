#include "RobotrixCRFSDriver.h"
#include "RobotrixCommand.h"
#include <cstddef>
#include <cstdint>

CRFSBus CRFSDriver;
CRSFforArduino *crsfRadio = nullptr;

void CRFSBus::setup(uint32_t baudRate) {

  // Initialise CRSF for Arduino.
  crsfRadio = new CRSFforArduino(CRFSUart);
  if (!crsfRadio->begin(baudRate)) {
    crsfRadio->end();
    delete crsfRadio;
    crsfRadio = nullptr;
    crfsOK = false;
    return;
  }
  crsfRadio->setRcChannelsCallback(onReceiveStatic);
  crfsOK = true;
}

void CRFSBus::update(void) { crsfRadio->update(); }

void CRFSBus::onReceiveStatic(serialReceiverLayer::rcChannels_t *rcChannels) {
  CRFSDriver.onReceive(rcChannels);
}

void CRFSBus::onReceive(serialReceiverLayer::rcChannels_t *rcChannels) {
  // Update channels array
  for (uint8_t i = 1; i <= rcChannelCount; i++) {
    ch[i] = crsfRadio->rcToUs(crsfRadio->getChannel(i));
  }

  if (rcChannels->failsafe == false)
    ch[0] = 0;
  else
    ch[0] = 1;
}

//void CRFSBus::write(const uint8_t *p, size_t len) {}
void CRFSBus::sendBat(float voltage, float current, uint8_t remaining) {
  uint8_t buf[16];
  uint8_t i = 0;

  buf[i++] = 0xC8; // device address

  uint8_t payload_len = 6;
  buf[i++] = payload_len + 2; // type + payload + crc

  buf[i++] = 0x08; // battery frame type

  uint16_t v = voltage * 10; // e.g. 12.3V → 123
  uint16_t c = current * 10; // e.g. 1.5A → 15

  buf[i++] = v >> 8;
  buf[i++] = v & 0xFF;

  buf[i++] = c >> 8;
  buf[i++] = c & 0xFF;

  buf[i++] = 0;         // capacity (optional)
  buf[i++] = remaining; // %

  uint8_t crc = crsf_crc8(&buf[2], payload_len + 1);
  buf[i++] = crc;

  //CRFSUart.write(buf, i);
}

// Vibecoded shit
uint8_t CRFSBus::crsf_crc8(const uint8_t *ptr, uint8_t len) {
    uint8_t crc = 0;
    while (len--) {
        crc ^= *ptr++;
        for (uint8_t i = 0; i < 8; i++) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0xD5;
            else
                crc <<= 1;
        }
    }
    return crc;
}