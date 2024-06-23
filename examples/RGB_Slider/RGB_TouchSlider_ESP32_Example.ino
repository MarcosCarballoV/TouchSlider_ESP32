#include <Arduino.h>              // Arduino library
#include "Logger.h"               // Logger library
#include "TouchSlider.h"          // TouchSlider library
#include <Ticker.h>               // Ticker library
#include "Adafruit_NeoPixel.h"    // NeoPixel library you can install with `platformio lib install adafruit/Adafruit NeoPixel@^1.12.2

// Pins designed for sliders, edit according to your setup
#define THRESHOLD_SLIDER  75              // Threshold slider on percentage
#define SLIDER1_PIN     GPIO_NUM_33
#define SLIDER2_PIN     GPIO_NUM_27
#define SLIDER3_PIN     GPIO_NUM_14 
#define SLIDER4_PIN     GPIO_NUM_4    

// Pins designed for NeoPixels, edit according to your setup
#define NEOPIXEL_PIN          GPIO_NUM_9  // NeoPixel pin
#define NEOPIXEL_COUNT        1
#define NEOPIXEL_BRIGHTNESS   255

gpio_num_t arraySlidersPins[] = {         // Array of slider pins
  SLIDER1_PIN,
  SLIDER2_PIN,
  SLIDER3_PIN,
  SLIDER4_PIN
};

size_t numSlidersPins = sizeof(arraySlidersPins) / sizeof(arraySlidersPins[0]);   // Number of sliders
TouchSlider touchSlider(arraySlidersPins, THRESHOLD_SLIDER, numSlidersPins);      // TouchSlider object
Ticker _sliderTicker;                                                             // Ticker object for updating touch slider
const uint8_t SLIDER_INTERVAL = 200;                                              // Interval for updating touch slider
enum { INCREASE, DECREASE };                                                      // Enum for determining slider direction

Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);        // NeoPixel object
uint8_t r = 255, g = 0, b = 0;                                                                // Initial RGB values (Red)

void updateNeoPixel(bool increase) {
  uint8_t transfer = 15;    // Step by step rgb transfer
  if (increase) {
    if (r > 0 && b == 0) {
      // R -> G
      if (r >= transfer) {
        r -= transfer;
        g += transfer;
      } else {
        g += r;
        r = 0;
      }
    } else if (g > 0 && r == 0) {
      // G -> B
      if (g >= transfer) {
        g -= transfer;
        b += transfer;
      } else {
        b += g;
        g = 0;
      }
    } else if (b > 0 && g == 0) {
      // B -> R
      if (b >= transfer) {
        b -= transfer;
        r += transfer;
      } else {
        r += b;
        b = 0;
      }
    }
  } else {
    if (r > 0 && g == 0) {
      // R -> B
      if (r >= transfer) {
        r -= transfer;
        b += transfer;
      } else {
        b += r;
        r = 0;
      }
    } else if (g > 0 && b == 0) {
      // G -> R
      if (g >= transfer) {
        g -= transfer;
        r += transfer;
      } else {
        r += g;
        g = 0;
      }
    } else if (b > 0 && r == 0) {
      // B -> G
      if (b >= transfer) {
        b -= transfer;
        g += transfer;
      } else {
        g += b;
        b = 0;
      }
    }
  }

  neopixel.setPixelColor(0, neopixel.Color(r, g, b));   // Set RGB values to NeoPixel
  neopixel.show();                                      // Show NeoPixel
}

void updateNeoPixelFine(bool increase) {
  if (increase) {
    neopixel.setBrightness(min(neopixel.getBrightness() + 15, 255));    // Increase brightness
  } else {
    neopixel.setBrightness(max(neopixel.getBrightness() - 15, 0));      // Decrease brightness
  }

  neopixel.setPixelColor(0, neopixel.Color(r, g, b));                   // Set RGB values to NeoPixel
  neopixel.show();                                                      // Show NeoPixel
}

void updateTouchSlider() {                                 // Update touch slider
  // Serial.println("Updating touch slider");              // Logging

  int8_t swipeStatus = touchSlider.getSwipeStatus();       // Get swipe status
  if (swipeStatus != 0) {
    for (int8_t i = 0; i < abs(swipeStatus); ++i) {        // Convert swipe status to absolute value to determine count of iterations
      if (swipeStatus > 0) 
        updateNeoPixel(INCREASE);                          // This function will the swipe status in the direction of increase
      else 
        updateNeoPixel(DECREASE);                          // This function will the swipe status in the direction of decrease
    }
  }

  int8_t swipeStatusFine = touchSlider.getSwipeStatusFine();      // Get swipe status fine
  if (swipeStatusFine != 0) {
    for (int8_t i = 0; i < abs(swipeStatusFine); ++i) {           // Convert swipe status fine to absolute value to determine count of iterations
      if (swipeStatusFine > 0) 
        updateNeoPixelFine(INCREASE);                             // This function will the only touch the first touch pad on the slider
      else 
        updateNeoPixelFine(DECREASE);                             // This function will the only touch the last touch pad on the slider
    }
  }
}

void setup() {
  neopixel.begin();                         // Begin NeoPixel
  neopixel.clear();                         // Clear NeoPixel
  Serial.begin(115200);                     // Begin serial communication
  Serial.println("NeoPixel initialized");   // Logging

  touchSlider.enableSwipeFine();            // Enable swipe fine
  touchSlider.disableTouchButtons();        // Disable touch buttons
  touchSlider.disablePrintSliderTouched();   // Disable print slider touched
  touchSlider.enablePrintSwipeStatus();      // Enable print swipe status

  touchSlider.start();                          // Start touch slider
  Serial.println("TouchSlider initialized");    // Logging
  _sliderTicker.attach_ms(SLIDER_INTERVAL, updateTouchSlider);  // Attach ticker to update touch slider
}

void loop() {
  delay(200);   // Delay for 200ms

  // Rest of the code
  /*
  ...
  ...
  */

  // The updateTouchSlider() function will be called every SLIDER_INTERVAL, independently of the rest of the code
}