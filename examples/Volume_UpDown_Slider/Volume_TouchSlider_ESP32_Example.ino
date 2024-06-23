#include <Arduino.h>              // Arduino library
#include "Logger.h"               // Logger library
#include "TouchSlider.h"          // TouchSlider library
#include <Ticker.h>               // Ticker library

// Pins designed for sliders, edit according to your setup
#define THRESHOLD_SLIDER  75              // Threshold slider on percentage
#define SLIDER1_PIN     GPIO_NUM_33
#define SLIDER2_PIN     GPIO_NUM_27
#define SLIDER3_PIN     GPIO_NUM_14 
#define SLIDER4_PIN     GPIO_NUM_4 

gpio_num_t arraySlidersPins[] = {         // Array of slider pins
  SLIDER1_PIN,
  SLIDER2_PIN,
  SLIDER3_PIN,
  SLIDER4_PIN
};

// Define the limits for the volume values.
#define MIN_VALUE  0
#define MAX_VALUE  100
#define HIGH_VOLUME_STEP 5
#define DEFAULT_VOLUME_VALUE 50
uint8_t volume = DEFAULT_VOLUME_VALUE;        // Global variable to store the current volume value. Change a local variable if you application needs it

size_t numSlidersPins = sizeof(arraySlidersPins) / sizeof(arraySlidersPins[0]);   // Number of sliders
TouchSlider touchSlider(arraySlidersPins, THRESHOLD_SLIDER, numSlidersPins);      // TouchSlider object
Ticker _sliderTicker;                                                             // Ticker object for updating touch slider
const uint8_t SLIDER_INTERVAL = 200;                                              // Interval for updating touch slider
enum { INCREASE, DECREASE };                                                      // Enum for determining slider direction

void stepHighVolume(bool increase) {
  if (increase) {
    if (volume + HIGH_VOLUME_STEP > MAX_VALUE) {    // Check if the volume is already at the maximum value
      volume = MAX_VALUE;
    } else {                                        // If not, increase the volume
      volume += HIGH_VOLUME_STEP;
    }
  } else {
    if (volume < HIGH_VOLUME_STEP) {                // Check if the volume is already at the minimum value
      volume = MIN_VALUE;
    } else {                                        // If not, decrease the volume
      volume -= HIGH_VOLUME_STEP;
    }
  }
}

void stepLowVolume(bool increase) {
  if (increase) {
    if (volume + 1 > MAX_VALUE) {                   // Check if the volume is already at the maximum value
      volume = MAX_VALUE;
    } else {                                        // If not, increase the volume
      volume += 1;
    }
  } else {
    if (volume == MIN_VALUE) {                      // Check if the volume is already at the minimum value
      volume = MIN_VALUE;
    } else {                                        // If not, decrease the volume
      volume -= 1;
    }
  }
}

void updateTouchSlider() {                                 // Update touch slider
  // Serial.println("Updating touch slider");              // Logging
  int8_t swipeStatus = touchSlider.getSwipeStatus();       // Get swipe status
  if (swipeStatus != 0) {
    for (int8_t i = 0; i < abs(swipeStatus); ++i) {        // Convert swipe status to absolute value to determine count of iterations
      if (swipeStatus > 0) 
        stepHighVolume(INCREASE);                          // This function will the swipe status in the direction of increase
      else 
        stepHighVolume(DECREASE);                          // This function will the swipe status in the direction of decrease
    }
  }

  int8_t swipeStatusFine = touchSlider.getSwipeStatusFine();      // Get swipe status fine
  if (swipeStatusFine != 0) {
    for (int8_t i = 0; i < abs(swipeStatusFine); ++i) {           // Convert swipe status fine to absolute value to determine count of iterations
      if (swipeStatusFine > 0) 
        stepLowVolume(INCREASE);                             // This function will the only touch the first touch pad on the slider
      else 
        stepLowVolume(DECREASE);                             // This function will the only touch the last touch pad on the slider
    }
  }

  static uint8_t lastVolume = volume;
  if (lastVolume != volume) {             // Print the current volume value if it has changed
    lastVolume = volume;
    Serial.println("Actual volume: %d", volume);
  }
}

void setup() {
  Serial.begin(115200);                     // Begin serial communication

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