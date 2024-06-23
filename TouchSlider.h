#ifndef TOUCHSLIDER_H
#define TOUCHSLIDER_H

/**
* Additional information can be found here:
* https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/touch_pad.html
*/
/*********************** EXTERNAL LIBRARIES **********************/

#include <Arduino.h>
#include <driver/touch_pad.h>
#include <Ticker.h>
#include "Logger.h"

/*********************** LIBRARY OPTIONS **********************/
#define START_WITH_CALIBRATION                // Initialize the calibration when starting the slider, comment this line to disable
#define START_WITH_SWIPE_FINE                 // Enable swipe fine by default, comment this line to disable
#define START_PRINT_SWIPE_STATUS              // Print the swipe status by default, comment this line to disable
#define START_PRINT_SLIDER_TOUCHED            // Print the slider touched by default, comment this line to disable
// #define START_WITH_TOUCH_BUTTONS              // Enable touch buttons by default, comment this line to disable
// #define START_PRINT_TOUCH_BUTTONS             // Enable print touch buttons by default, comment this line to disable

/*********************** CLASS DEFINITION **********************/


class TouchSlider
{
  public:

    // Constructors
    TouchSlider(gpio_num_t sliderPins[], uint8_t threshold , uint8_t numSliderPins);     // Constructor with a single threshold
    TouchSlider(gpio_num_t sliderPins[], uint8_t threshold[], uint8_t numSliderPins);   // Constructor with an array of thresholds

    // Touch buttons functionalities
    void addTouchButton(gpio_num_t buttonPin, uint8_t thresholdPercent);            // Add a touch button to the slider, automatically enable the touch button 
    void removeTouchButton(gpio_num_t buttonPin);                                   // Remove a touch button from the slider

    // Public functions
    void start();                                                                       // Start the touch slider, use first addTouchButton before calling this function (with start calibration), or use calibrate_thresholds() after to add the buttons
    void stop();                                                                        // Stop the touch slider
    void resume();                                                                      // Resume the touch slider

    //  Enable/Disable functions
    void enableSwipeFine() {_enableSwipeFine = true;};                                  // Enable swipe fine
    void disableSwipeFine() {_enableSwipeFine = false;};                                // Disable swipe fine
    void enableTouchButtons() {_enableTouchButtons = true;};                            // Enable touch buttons
    void disableTouchButtons() {_enableTouchButtons = false;};                          // Disable touch buttons


    // Enable/Disable print functions
    void enablePrintSliderTouched() {_enablePrintSliderTouched = true;};                // Enable print array of pads on slider which were touched
    void disablePrintSliderTouched() {_enablePrintSliderTouched = false;};              // Disable print array of pads on slider which were touched
    void enablePrintSwipeStatus() {_enablePrintSwipeStatus = true;};                    // Enable print swipe status (include swipe fine status)
    void disablePrintSwipeStatus() {_enablePrintSwipeStatus = false;};                  // Disable print swipe status (include swipe fine status)
    void enablePrintButtonTouched() {_enablePrintBottonTouched = true;};                // Enable print array of button touched and the button that was short-pressed
    void disablePrintButtonTouched() {_enablePrintBottonTouched = false;};              // Disable print array of button touched and the button that was short-pressed

    // Calibration
    void calibrate_thresholds();                                                        // Calibrate the thresholds, automatically calibrate when starting the slider

    // Getters
    int8_t getSwipeStatus();                                                            // Get the swipe status
    int8_t getSwipeStatusFine();                                                        // Get the swipe fine status
    gpio_num_t getButtonShortPress();                                                   // Get the button short press 
    bool getSliderRunning() {return _sliderRunning;};                                   // Get the slider running status
    bool isTouchButtonPressed(gpio_num_t buttonPin);                                    // Check if a touch button is pressed
    bool isTouchSliderPressed(gpio_num_t sliderPin);                                    // Check if the touch slider is pressed
    void getSliderTouched(bool sliderTouched[], uint8_t numSliderPins);     // Get the SliderTouched


  private:
    // Configuration
    bool _sliderRunning = false;                                      // Indicates whether the timer is running
    uint8_t TOUCH_THRESHOLD = 0;                                      // (0-100) Higher percentage means more sensitive
    uint8_t TOUCH_THRESHOLD_ARRAY[TOUCH_PAD_MAX];                     // (0-100) Higher percentage means more sensitive
    uint16_t threshold_inactive = 0;                                  // Threshold for inactive touch
    uint8_t filter_period = 10;                                       // Filter period in ms

    // Enums
    enum { NO_CHANGE, SWIPE_UP, SWIPE_DOWN};                          // Swipe status

    // Timers
    Ticker sliderTicker;                                              // Timer for updating the touch pads
    const uint16_t UPDATE_INTERVAL = 50;                              // Update interval in ms to scan the touch pads

    // Static configuration and runtime state
    static uint8_t _padThresholdPercent[TOUCH_PAD_MAX];               // (0-100) Higher percentage means more sensitive
    static bool _padEnabled[TOUCH_PAD_MAX];                           // Indicates whether the touch pad is enabled
    static uint16_t _padFilteredValue[TOUCH_PAD_MAX];                 // Filtered value of the touch pad
    static uint16_t _padThreshold[TOUCH_PAD_MAX];                     // Threshold for touch pad
    int16_t _lastValue, _actualValue;                                 // Last and actual value of the touch pad
    uint8_t _sliderState = NO_CHANGE;                                 // Swipe status in last update

    uint8_t _numSliderPins = 0;                                       // Number of slider pins
    gpio_num_t _arraySliderPins[TOUCH_PAD_MAX];                          // Array of slider pins
    touch_pad_t _arraySliderPads[TOUCH_PAD_MAX];                          // Array of slider pads
    bool _SliderTouched[TOUCH_PAD_MAX];                               // Indicates whether the slider is touched
    static int8_t _sliderValue[TOUCH_PAD_MAX];                       // Value of the slider

    int8_t _swipeCount = 0;                                           // Swipe count
    int8_t _swipeUpCount = 0;                                         // Swipe up count
    int8_t _swipeDownCount = 0;                                       // Swipe down count
    
    int8_t _swipeFineUpCount = 0;                                     // Swipe fine up count
    int8_t _swipeFineDownCount = 0;                                   // Swipe fine down count

    bool firstTouch = true;                                           // Indicates whether the first touch is detected
    bool firstPadTop = false;                                         // Indicates whether the first pad is touched
    bool firstPadBot = false;                                         // Indicates whether the last pad is touched

    bool _enablePrintSwipeStatus = false;                             // Indicates whether to print the swipe status
    bool _enablePrintSliderTouched = false;                           // Indicates whether to print the Slider Touched
    bool _enablePrintBottonTouched = false;                           // Indicates whether to print the Touch Buttons
    bool _enableSwipeFine = false;                                    // Indicates whether to enable Swipe Fine 
    bool _enableTouchButtons = false;                                 // Indicates whether to enable Touch Buttons

    gpio_num_t _arrayButtonPins[TOUCH_PAD_MAX];                       // Array of button pins
    touch_pad_t _arrayButtonPads[TOUCH_PAD_MAX];                      // Array of button pads
    uint8_t _buttonThresholdPercent[TOUCH_PAD_MAX];                   // (0-100) Higher percentage means more sensitive
    bool _ButtonTouched[TOUCH_PAD_MAX];                               // Indicates whether the button is touched
    uint8_t TOUCH_BUTTON_MAX = TOUCH_PAD_MAX;                         // Maximum number of touch buttons
    uint8_t _numTouchButtons = 0;                                     // Number of touch buttons
    gpio_num_t _gpioButtonTouched = GPIO_NUM_NC;                     // Index of the touched button


    void setInput(uint8_t padNumber, uint8_t thresholdPercent);                       // Set the input for the touch pad
    void setDefaultConfiguration();                                                   // Set the configuration
    void begin();                                                                     // Initialize the touch slider
    static void update(TouchSlider* self);                                            // Update the touch slider  
  
    static void filter_read_cb(uint16_t *raw_value, uint16_t *filtered_value);        // Callback function for filtering the touch pads *Filter output reading hook, see ESP-IDF file touch_pad.h for more information
    void printSliderTouched();                                                        // Print the slider touched
    void printButtonTouched();                                                        // Print the button touched
    void analyzeGesture(uint8_t numSliders);                                          // Analyze the gesture
    touch_pad_t mapGpioToTouchPad(gpio_num_t gpioPin);                                // Map the GPIO pin to the touch pad
    void printSliderValues(uint8_t numSliders);                                       // Print the slider values
    void printSliderFilteredValues();                                                 // Print the slider filtered values

    static void checkButtonStatus(TouchSlider* self);                                 // Check the button status
    static void checkSingleButtonTouch(TouchSlider* self);                            // Check the single button touch
    static void checkSliderStatus(TouchSlider* self, bool &padTouchedFound, int8_t &firstTouchedIndex,
                                   int8_t &lastTouchedIndex, uint8_t &touchedPadCount);         // Check the slider status
    static void handleNoTouch(TouchSlider* self);                                               // Handle no touch
    static void handleTouch(TouchSlider* self, int8_t firstTouchedIndex, int8_t lastTouchedIndex, uint8_t touchedPadCount);   // Handle 
    
    static uint8_t getIndexFromGpioSlider(TouchSlider* self, gpio_num_t gpioPin);                              // Get the index from the GPIO pin on the slider array
    static uint8_t getIndexFromGpioButton(TouchSlider* self, gpio_num_t gpioPin);                              // Get the index from the GPIO pin on the button array
    
    void resetFirstTouches();                                                         // Reset the first touches
};
#endif