#ifndef S9706_h
#define S9706_h

#include "Arduino.h"

#define S9706_MODE_HIGH 1
#define S9706_MODE_LOW  2

#define S9706_RGB_MAX   4095
#define S9706_RGB_MIN   0

class S9706 {
  private:
    uint8_t _dataPin;
    uint8_t _rangePin;
    uint8_t _clockPin;
    uint8_t _gatePin;

    uint16_t _rgb[3];

    uint16_t shiftInBits(uint8_t bitOrder, uint8_t bitLength);

  public:
    S9706(uint8_t dataPin, uint8_t rangePin, uint8_t clockPin, uint8_t gatePin);
    void begin();
    void update(uint8_t mode, unsigned long durationMs, unsigned long durationUs = 0L);
    uint16_t getRed();
    uint16_t getGreen();
    uint16_t getBlue();
};

#endif
