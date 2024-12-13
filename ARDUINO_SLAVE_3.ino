#include <Wire.h>

#define SMOKE_SENSOR_PIN A0  // Pin connected to the smoke sensor
#define SLAVE3_ADDRESS 10    // Slave 3 I2C address

void setup() {
  Wire.begin(SLAVE3_ADDRESS); // Set this device as Slave 3
  Wire.onRequest(requestData); // Register event to handle master requests
  pinMode(SMOKE_SENSOR_PIN, INPUT); // Set smoke sensor pin as input
}

void loop() {
  // Nothing to do here, as data is sent in the requestData handler
}

void requestData() {
  int smokeValue = analogRead(SMOKE_SENSOR_PIN); // Read smoke sensor value (0-1023)
  Wire.write(smokeValue & 0xFF);       // Send lower 8 bits
  Wire.write((smokeValue >> 8) & 0xFF); // Send upper 8 bits
}
