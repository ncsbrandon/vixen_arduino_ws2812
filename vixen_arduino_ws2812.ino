#include <FastLED.h>

#define STRINGS 4
#define LEDS_PER_STRING 30

CRGB leds[STRINGS][LEDS_PER_STRING];

void setup() {
  Serial.begin(115200);
  
  // TODO: try upldating each string to see if the performance
  // is any better.  I'm guessing there may be some jerkiness
  // loading all LEDs before showing
  //CLEDController* one = &
  
  FastLED.addLeds<WS2812B, 3, GRB>(leds[0], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, 5, GRB>(leds[1], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, 6, GRB>(leds[2], LEDS_PER_STRING);
  FastLED.addLeds<WS2812B, 9, GRB>(leds[3], LEDS_PER_STRING);
}

void loop() {
  while (!Serial.available());
  while (Serial.read() != '>') {
    continue;
  }

  loadLEDs(0, LEDS_PER_STRING);
  loadLEDs(1, LEDS_PER_STRING);
  loadLEDs(2, LEDS_PER_STRING);
  loadLEDs(3, LEDS_PER_STRING);
  FastLED.show();
}

void loadLEDs(unsigned int index, unsigned int nleds) {
  unsigned int cnt = 0;
  // Loop through each of the pixels and read the values for each color
  do {
    while (!Serial.available());
    leds[index][cnt].r = Serial.read();
    while (!Serial.available());
    leds[index][cnt].g = Serial.read();
    while (!Serial.available());
    leds[index][cnt].b = Serial.read();
    cnt++;
  }
  while (cnt < nleds);
}
