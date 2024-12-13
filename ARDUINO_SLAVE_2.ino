#include <Wire.h>

// Define button pin and interrupt vector
#define BUTTON_PIN 2
volatile bool buttonPressed = false;

void setup() {
  // Configure the button pin as an input with an internal pull-up resistor
  DDRD &= ~(1 << PD2);  // Clear the PD2 bit to set it as input
  PORTD |= (1 << PD2);  // Enable the pull-up resistor on PD2 (button)

  // Attach interrupt to button pin (on rising edge)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonInterrupt, RISING);
  
  Wire.begin(9); // Join I2C bus as Slave 2 with address 9
  Wire.onRequest(requestEvent); // Register event for master requests
}

void loop() {
  // Main loop does nothing, actions are taken in `requestEvent`
}

void buttonInterrupt() {
  buttonPressed = true; // Set button state to true on interrupt
}

void requestEvent() {
  Wire.write(buttonPressed ? 1 : 0); // Send button state to master
  buttonPressed = false; // Reset button state after sending
}
