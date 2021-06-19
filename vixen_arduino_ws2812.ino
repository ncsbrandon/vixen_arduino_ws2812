#include <FastLED.h>

// serial settings
#define SerialComm SerialUSB
#define BAUD 921600

// string settings
#define LEDS_PER_STRING 300
#define STRING_COUNT 4
#define STRING1_INDEX 0
#define STRING1_PIN 3
#define STRING2_INDEX 1
#define STRING2_PIN 5
#define STRING3_INDEX 2
#define STRING3_PIN 6
#define STRING4_INDEX 3
#define STRING4_PIN 8

// other settings
#define STATUS_LED_PIN LED_BUILTIN
// on the SAMD21 Mini Breakout this is the blue

const char start_char = '>';
CRGB leds[STRING_COUNT][LEDS_PER_STRING];
unsigned int pos = 0;

void setup() {
  // serial init
  SerialComm.begin(BAUD);
  
  // wakeup blink
  pinMode(STATUS_LED_PIN, OUTPUT);
  for (int i = 0; i < 8; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(50);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(50);
  }

  // initialize each string's memory and pin
  FastLED.addLeds<WS2812B, STRING1_PIN, GRB>(leds[STRING1_INDEX], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, STRING2_PIN, GRB>(leds[STRING2_INDEX], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, STRING3_PIN, GRB>(leds[STRING3_INDEX], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, STRING4_PIN, GRB>(leds[STRING4_INDEX], LEDS_PER_STRING);
}

void loop() {
  while (true) {
    // wait for start character
    while (!SerialComm.available());
    if (SerialComm.read() != start_char) {
      digitalWrite(STATUS_LED_PIN, LOW);
      continue;
    }
    digitalWrite(STATUS_LED_PIN, HIGH);
	
    // read the string from serial
    loadLEDs(STRING1_INDEX);
    loadLEDs(STRING2_INDEX);
    loadLEDs(STRING3_INDEX);
    loadLEDs(STRING4_INDEX);
    
    // show
    FastLED.show();
  }
}

void loadLEDs(unsigned int string) {
  // Loop through each of the pixels and read the values for each color
  pos = 0;
  do {
    while (!SerialComm.available());
    leds[string][pos].r = SerialComm.read();
    while (!SerialComm.available());
    leds[string][pos].g = SerialComm.read();
    while (!SerialComm.available());
    leds[string][pos].b = SerialComm.read();
    pos++;
  }
  while (pos < LEDS_PER_STRING);
}
