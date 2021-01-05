#include <FastLED.h>

/*

  Vixen Lights 3.x - Arduino Generic Serial for Addressable Pixels

  Using this code is pretty straight forward, simply hookup your one wire (WS2811 or WS2812) data line to pin 6 of your Arduino
  and upload this code.  Make sure you have properly installed the FastLED library from http://fastled.io Once you are done, simply
  power your Pixel strips from an external power supply.  Next configure a Generic Serial Controller inside of Vixen Lights 3.x and
  add 3 x pixels for the number of channels.  Configure the Generic Serial Controller to use 115200, 8, none, and 1.  Then create
  your element and add "Multiple Items (1 x number of pixels).  Finally select your pixel elements and set them as RGB pixels before
  patching them to the controler outputs.  You should now be ready to begin testing.

  For a complete tutorial check out blog.huntgang.com

  Created   November 8th, 2014
  By        Richard Sloan - www.themindfactory.com
  And       David Hunt - blog.huntgang.com
  Version   1.4

*/

#define MAX_NUM_LEDS 300

CRGB leds[MAX_NUM_LEDS];

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Set some counter / temporary storage variables
  unsigned int num_leds;
  unsigned int d1, d2, d3, d4;

  // Begin an endless loop to receive and process serial data
  for (;;) {

    //Begin waiting for the header to be received on the serial bus
    //1st character
    while (!Serial.available());
    if (Serial.read() != '>') {
      continue;
    }
    //second character
    while (!Serial.available());
    if (Serial.read() != '>') {
      continue;
    }
    //get the first digit from the serial bus for the number of pixels to be used
    while (!Serial.available());
    d1 = Serial.read();
    //get the second digit from the serial bus for the number of pixels to be used
    while (!Serial.available());
    d2 = Serial.read();
    //get the third digit from the serial bus for the number of pixels to be used
    while (!Serial.available());
    d3 = Serial.read();
    //get the fourth digit from the serial bus for the number of pixels to be used
    while (!Serial.available());
    d4 = Serial.read();
    //get the end of the header
    while (!Serial.available());
    if (Serial.read() != '<') {
      continue;
    }
    while (!Serial.available());
    if (Serial.read() != '<') {
      continue;
    }
    // calculate the number of pixels based on the characters provided in the header digits
    num_leds = (d1 - '0') * 1000 + (d2 - '0') * 100 + (d3 - '0') * 10 + (d4 - '0');
    // ensure the number of pixels does not exceed the number allowed
    if (num_leds > MAX_NUM_LEDS) {
      continue;
    }

    FastLED.addLeds<WS2812B, 6, GRB>(leds, num_leds);
    ledString(6, num_leds);
    FastLED.show();
  
    FastLED.addLeds<WS2812B, 3, GRB>(leds, num_leds);
    ledString(3, num_leds);
    FastLED.show();
  }
}

void ledString(int pin, unsigned int nleds) {
    unsigned int cnt = 0;
    
    // Loop through each of the pixels and read the values for each color
    do {
      while (!Serial.available());
      leds[cnt].r = Serial.read();
      while (!Serial.available());
      leds[cnt].g = Serial.read();
      while (!Serial.available());
      leds[cnt].b = Serial.read();
      cnt++;
    }
    while (--nleds);   
}
