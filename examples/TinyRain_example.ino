#include <TinyRain.h>

TinyRain sensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting sensor.");
  delay(500);
  bool status = sensor.begin();
  delay(500);
  if (!status) {
    Serial.println(status);
    Serial.println("Rain sensor not found!");
    while (1);  // Stop execution
  }

  Serial.println("Rain sensor initialized.");
}

void loop() {
  uint32_t rain = sensor.read();
  Serial.print("Rain: ");
  Serial.print(rain);
  Serial.println(" mm");
  delay(1000);
}
