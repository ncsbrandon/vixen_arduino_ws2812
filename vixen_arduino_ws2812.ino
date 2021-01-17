#include <FastLED.h>

#define STRINGS 2
#define LEDS_PER_STRING 300
//#define SerialUSB Serial
#define STATUS_LED_PIN LED_BUILTIN

CRGB leds[STRINGS][LEDS_PER_STRING];
unsigned int cnt = 0;
char start_char = '>';

void setup() {
  Serial.begin(115200);
  pinMode(STATUS_LED_PIN, OUTPUT);
  
  // TODO: try updating each string to see if the performance
  // is any better.  I'm guessing there may be some jerkiness
  // loading all LEDs before showing
  //CLEDController* one = &

  FastLED.addLeds<WS2812B, 3, GRB>(leds[0], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, 5, GRB>(leds[1], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 27, GRB>(leds[2], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 29, GRB>(leds[3], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 11, GRB>(leds[4], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 13, GRB>(leds[5], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 15, GRB>(leds[6], LEDS_PER_STRING);
  //FastLED.addLeds<WS2812B, 17, GRB>(leds[7], LEDS_PER_STRING);
}

void loop() {
  while(true) {
    // wait for data
    while (!Serial.available());
    if (Serial.read() != start_char) {
      continue;
    }
    
    // read from serial
    digitalWrite(STATUS_LED_PIN, HIGH);
    for(int string=0; string<STRINGS; string++) {
      loadLEDs(string, LEDS_PER_STRING);
    }
    digitalWrite(STATUS_LED_PIN, LOW);
    
    // load into the strings
    FastLED.show();
  }
}

void loadLEDs(unsigned int string, unsigned int nleds) {
  cnt = 0;
  // Loop through each of the pixels and read the values for each color
  do {
    while (!Serial.available());
    leds[string][cnt].r = Serial.read();
    while (!Serial.available());
    leds[string][cnt].g = Serial.read();
    while (!Serial.available());
    leds[string][cnt].b = Serial.read();
    cnt++;
  }
  while (cnt < nleds);
}
