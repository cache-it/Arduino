#include "my_joystick.h"

const int ANALOG_MAX = 1023;           // Maximum analog value
const int ANALOG_AVG = ANALOG_MAX / 2; // Average analog value
const int MAP_MAX = 255;               // Maximum mapped value
const int SPEED_TIER = 10;             // Speed tier for joystick movement
const int DEBOUNCE_TIME = 1500;        // (ms) Debounce time for switch press

// Check your analog joystick. The error margin is different for each joystick.
// Adjust these values based on your joystick's characteristics.
// These values are used to filter out starter noise in the analog readings.
const int ANALOG_X_START = 522;
const int ANALOG_Y_START = 518;

MyJoystick::MyJoystick(uint8_t xPin, uint8_t yPin, uint8_t switchPin)
    : _xPin(xPin), _yPin(yPin), _switchPin(switchPin) {}

// Reads the joystick values and returns them as an array
void MyJoystick::readJoystick(uint8_t _xPin, uint8_t _yPin)
{
    // Read analogic values in a range of 0 to 1023
    _xValue = (analogRead(_xPin) - ANALOG_X_START);
    _yValue = (analogRead(_yPin) - ANALOG_Y_START);

    // Ensure the values are positive to be mapped correctly
    setMappedVoltage(abs(_xValue), abs(_yValue));

    // Set the angle based on the joystick position
    setAngle(_xValue, _yValue);

    // Set the speed based on the mapped values
    setSpeed(_xMap, _yMap);

    // Set the switch state based on the switch pin
    setSwitchState();
}

void MyJoystick::setSwitchState()
{
    int switchState = digitalRead(_switchPin);
    if (switchState == LOW)
    {
        if (_switchState == IDLE)
        {
            _currTime = millis();
            _switchState = PRES; // Joystick pressed
        }
        else if (millis() - _currTime > DEBOUNCE_TIME)
        {
            _currTime = millis();
            _switchState = HOLD; // Joystick held
        }
    }
    else if (_switchState != IDLE)
    {
        _switchState = IDLE;
    }
}

// Sets the mapped voltage for the joystick based on the input positions
// Maps the input positions to a range of 0 to MAP_MAX
void MyJoystick::setMappedVoltage(int xPosition, int yPosition)
{
    // Map the values to a certain range
    if (ANALOG_AVG > MAP_MAX)
    {
        _xMap = map(xPosition, 0, ANALOG_MAX, 0, MAP_MAX);
        _yMap = map(yPosition, 0, ANALOG_MAX, 0, MAP_MAX);
    }
    else
    {
        _xMap = xPosition;
        _yMap = yPosition;
    }
}

// Get speed based on a circumference of radius MAP_MAX
void MyJoystick::setSpeed(int xAxe, int yAxe)
{
    int xRadius = abs(_xValue * SPEED_TIER) / ANALOG_X_START;
    int yRadius = abs(_yValue * SPEED_TIER) / ANALOG_Y_START;
    _speed = max(xRadius, yRadius);
}

// Sets the angle based on the joystick position
void MyJoystick::setAngle(int xPosition, int yPosition)
{
    _angle = atan2(yPosition, xPosition) * 180 / PI; // Convert radians to degrees
}
