#include "TinyRain.h"

TinyRain::TinyRain(uint8_t address) {
  _address = address;
}

bool TinyRain::begin() {
  Wire.begin();
  Wire.beginTransmission(_address);
  uint8_t error = Wire.endTransmission();

  return (error == 0);  // 0 = success (ACK), others = error
}

float TinyRain::read() {
  uint8_t data[NUM_BYTES] = {0};
  Wire.requestFrom(_address, NUM_BYTES);

  for (uint8_t i = 0; i < NUM_BYTES && Wire.available(); i++) {
    data[i] = Wire.read();
  }

  float rainfall = 0.0f;
  memcpy(&rainfall, data, sizeof(rainfall));
  return rainfall;
}
