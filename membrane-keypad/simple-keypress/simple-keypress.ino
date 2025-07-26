// Simple Keypad Matrix Example

/* @author Mauro Mercuri 
|| @contact cache.it.service@gmail.com
|| @date 2025-07-26
|| @description
|| | How to read a simple 4x4 keypad matrix without using any library.
|| | Rows and colums are dynamically set, you must check if the electrical panel
|| | is similar to the one used in this example.
*/

// Awaited time until next scan key
const byte debounceTime = 1000;  // 10 millis
// Awaited time to recognize a scan key as pressed one
const byte pressedTime = 1000;  // 1 second
// Number of rows and cols of the eletric panel keypad
const byte ROWS = 4;
const byte COLS = 4;

// Keypad matrix template
byte keymap[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Structure of eletric panel
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

/*  ===========================================  */

// Avoiding fast printing
unsigned long flagTime = 0;
unsigned long startTime;

void setup() {
  // Data rate in bits per second
  Serial.begin(9600);
  Serial.println("Ready for some input:");

  // Set only rows in pullup mode
  for (byte rPin : rowPins)
    pinMode(rPin, INPUT_PULLUP);
}


void loop() {
  startTime = millis();

  // Altern signal on cols to get volt variation
  for (byte j = 0; j <= COLS; j++) {
    byte cPin = colPins[j];

    // Enable cols signal
    pinMode(cPin, OUTPUT);
    digitalWrite(cPin, LOW);

    bool response = (startTime - flagTime) > debounceTime;

    // Reading bit and return ASCII code
    for (byte i = 0; i <= ROWS; i++)
      if (!digitalRead(rowPins[i]) && response) {
        flagTime = startTime;
        Serial.println(char(keymap[i][j]));
      }

    // disable cols from emitting signal
    pinMode(cPin, INPUT);
  }
}

