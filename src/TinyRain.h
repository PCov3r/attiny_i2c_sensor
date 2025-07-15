#ifndef TINYRAIN_H
#define TINYRAIN_H

#include <Arduino.h>
#include <Wire.h>

class TinyRain {
  public:
    TinyRain(uint8_t address = 100);   // Default I2C address is 100
    bool begin();
    float read();                      // Returns rainfall in mm

  private:
    uint8_t _address;
    static const uint8_t NUM_BYTES = 4;
};

#endif
