/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-neopixel-led-strip
 * 
 * Required Libraries (Tools -> Manage Libraries):
 * - Adafruit NeoPixel (by Adafruit)
 * 
 * Specify the pin and number of pixels, then upload the sketch
 * I have only tested a single WS2812B neopixel on 3v3, but that seems to work.
 * The SK6812 is not likely to work due to the higher voltage requirement.
 */

#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL 19  // The ESP32 pin connected to NeoPixel
#define NUM_PIXELS 1     // The number of LEDs (pixels) on NeoPixel LED strip

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  NeoPixel.begin();  // initialize NeoPixel strip object (REQUIRED)
}

void loop() {
  NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

  // turn pixels to green one-by-one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
    NeoPixel.show();                                           // update to the NeoPixel Led Strip

    delay(500);  // 500ms pause between each pixel
  }

  // turn off all pixels for two seconds
  NeoPixel.clear();
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(2000);      // 2 seconds off time

  // turn pixels to green one-by-one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 0, 255));  // it only takes effect if pixels.show() is called
    NeoPixel.show();                                           // update to the NeoPixel Led Strip

    delay(500);  // 500ms pause between each pixel
  }

  // turn off all pixels for two seconds
  NeoPixel.clear();
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(2000);      // 2 seconds off time

  // turn on all pixels to red at the same time for two seconds
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
  }
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(1000);      // 1 second on time

  // turn off all pixels for two seconds
  NeoPixel.clear();
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(2000);      // 2 seconds off time

  // turn on all pixels to red at the same time for two seconds
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {           // for each pixel
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 255, 255));  // it only takes effect if pixels.show() is called
  }
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(1000);      // 1 second on time

  // turn off all pixels for one seconds
  NeoPixel.clear();
  NeoPixel.show();  // update to the NeoPixel Led Strip
  delay(1000);      // 1 second off time
}
