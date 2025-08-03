// #include <Arduino_BuiltIn.h>
#include "my_joystick.h"

// Digital pin for switcher
const byte SW_PIN = 2;

// Analogic pins for axis
const uint8_t X_PIN = 0;
const uint8_t Y_PIN = 1;

// Init joystick
MyJoystick joystick(X_PIN, Y_PIN, SW_PIN);

void setup() {
  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  joystick.readJoystick(Y_PIN, X_PIN);
  
  Serial.print("Speed: " + String(joystick.getSpeed()));
  Serial.print("  Angle: " + String(joystick.getAngle()) + "°");

  // X e Y position
  Serial.print("  X:" + String(joystick.getXValue()));
  Serial.print("  Y:" + String(joystick.getYValue()));

  // X and Y value mapped for voltage
  Serial.print("  X-Map:" + String(joystick.getXMap()));
  Serial.print("  Y-Map:" + String(joystick.getYMap()));

  Serial.print("  SwitchState:" + String(joystick.getSwitchState()));

  Serial.println();
  delay(1000);
}
