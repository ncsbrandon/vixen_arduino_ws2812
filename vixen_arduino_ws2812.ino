#include <FastLED.h>

#define BAUD 115200
#define STRINGS 1
#define STRING1 0
#define STRING2 1
#define STRING3 2
#define STRING4 3
#define LEDS_PER_STRING 300
const char start_char = '>';

#define SerialComm SerialUSB
#define STATUS_LED_PIN LED_BUILTIN
// on the SAMD21 Mini Breakout this is the blue

CRGB leds[STRINGS][LEDS_PER_STRING];
unsigned int cnt = 0;

void setup() {
  SerialComm.begin(BAUD);
  
  // wakeup blink
  pinMode(STATUS_LED_PIN, OUTPUT);
  for (int i = 0; i < 8; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(50);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(50);
  }

  // map strings to pins
  FastLED.addLeds<WS2812B, 3, GRB>(leds[STRING1], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 5, GRB>(leds[STRING2], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 6, GRB>(leds[STRING3], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 8, GRB>(leds[STRING4], LEDS_PER_STRING);
}

void loop() {
  while (true) {
    digitalWrite(STATUS_LED_PIN, HIGH);

    // wait for start character
    while (!SerialComm.available());
    if (SerialComm.read() != start_char) {
      digitalWrite(STATUS_LED_PIN, LOW);
      continue;
    }
    
    // read from serial
    loadLEDs(STRING1, LEDS_PER_STRING);
    //loadLEDs(STRING2, LEDS_PER_STRING);
    //loadLEDs(STRING3, LEDS_PER_STRING);
    //loadLEDs(STRING4, LEDS_PER_STRING);
    
    // load into the strings
    FastLED.show();
  }
}

void loadLEDs(unsigned int string, unsigned int nleds) {
  cnt = 0;
  // Loop through each of the pixels and read the values for each color
  do {
    while (!SerialComm.available());
    leds[string][cnt].r = SerialComm.read();
    while (!SerialComm.available());
    leds[string][cnt].g = SerialComm.read();
    while (!SerialComm.available());
    leds[string][cnt].b = SerialComm.read();
    cnt++;
  }
  while (cnt < nleds);
}
