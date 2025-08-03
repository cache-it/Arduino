#ifndef MY_JOYSTICK_H
#define MY_JOYSTICK_H

#include <Arduino.h>

#define IDLE 0 // Default
#define PRES 1
#define HOLD 2

class MyJoystick
{
public:
  MyJoystick(uint8_t xPin, uint8_t yPin, uint8_t switchPin);
  void readJoystick(uint8_t _xPin, uint8_t _yPin);
  byte getSwitchState() { return _switchState; }
  int getXValue() { return _xValue; }
  int getYValue() { return _yValue; }
  byte getSpeed() { return _speed; }
  int getAngle() { return _angle; }
  int getXMap() { return _xMap; }
  int getYMap() { return _yMap; }

private:
  void setMappedVoltage(int xPosition, int yPosition);
  void setAngle(int xPosition, int yPosition);
  void setSpeed(int xAxe, int yAxe);
  void setSwitchState();

  byte _switchState = IDLE;
  int _currTime = millis();
  int _xValue, _yValue;
  byte _debounceTime;
  byte _xPin, _yPin;
  int _xMap, _yMap;
  byte _switchPin;
  byte _speed;
  int _angle;
};

#endif