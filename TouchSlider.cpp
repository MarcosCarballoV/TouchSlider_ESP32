#include "TouchSlider.h"

/*********************** VARIABLES **********************/
// Static members must be initialized here
bool TouchSlider::_padEnabled[TOUCH_PAD_MAX];               // Array to store the enabled status of each touch pad
uint8_t TouchSlider::_padThresholdPercent[TOUCH_PAD_MAX];   // Array to store the threshold percentage for each touch pad
uint16_t TouchSlider::_padFilteredValue[TOUCH_PAD_MAX];     // Array to store the filtered value of each touch pad
uint16_t TouchSlider::_padThreshold[TOUCH_PAD_MAX];         // Array to store the threshold value for each touch pad
int8_t TouchSlider::_sliderValue[TOUCH_PAD_MAX];           // Array to store the slider value for each touch pad, pad touch is set to 0, pad left is set to -1, pad right is set to 1

/*********************** CONSTRUCTORS **********************/
/**
 * @brief Constructor for TouchSlider class
 * 
 * This constructor initializes a TouchSlider object with a single overall threshold for all pads.
 * 
 * @param sliderPins An array of gpio_num_t representing the GPIO pins connected to the slider electrodes.
 * @param threshold The threshold value to determine touch sensitivity. Values above this threshold indicate touch.
 * @param numSliderPins The number of slider electrodes/pins.
 **/
TouchSlider::TouchSlider(gpio_num_t sliderPins[], uint8_t threshold, uint8_t numSliderPins) {
  _numSliderPins = numSliderPins;  
  
  if (_numSliderPins > 10)      // Limit the number of slider pins to 10 to prevent array overflow
    _numSliderPins = 10;

  for (uint8_t i = 0; i < _numSliderPins; ++i) {   // Initialize arrays to store slider pins and corresponding touch pads
    _arraySliderPins[i] = sliderPins[i];
    _arraySliderPads[i] = mapGpioToTouchPad(sliderPins[i]);
    if(_arraySliderPads[i] == TOUCH_PAD_MAX) {
      Serial.printf("Error: GPIO pin %d is not a valid touch pad.\n", sliderPins[i]);
      return;
    }
  }

  TOUCH_THRESHOLD = threshold;
  TOUCH_BUTTON_MAX = TOUCH_PAD_MAX - _numSliderPins;

  touch_pad_init();                                 // Initialize touch pad peripheral
  touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);     // If use interrupt trigger mode, should set TOUCH_FSM_MODE_TIMER
                                                    // Set reference voltage for charging/discharging
                                                    // For most usage scenarios, we recommend using the following combination:
                                                    // the high reference valtage will be 2.7V - 1V = 1.7V, The low reference voltage will be 0.5V.
  touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V5);

  setDefaultConfiguration();
}

/**
 * @brief Constructor for TouchSlider class
 * 
 * This constructor initializes a TouchSlider object with multiple individual thresholds for each pad.
 * 
 * @param sliderPins An array of gpio_num_t representing the GPIO pins connected to the slider electrodes.
 * @param threshold The threshold value to determine touch sensitivity. Values above this threshold indicate touch.
 * @param numSliderPins The number of slider electrodes/pins.
 **/
TouchSlider::TouchSlider(gpio_num_t sliderPins[], uint8_t threshold[], uint8_t numSliderPins) {
  _numSliderPins = numSliderPins;
  
  if (_numSliderPins > 10)      // Limit the number of slider pins to 10 to prevent array overflow
    _numSliderPins = 10;

  for (uint8_t i = 0; i < _numSliderPins; ++i) {    // Initialize arrays to store slider pins and corresponding touch pads
    _arraySliderPins[i] = sliderPins[i];
    _arraySliderPads[i] = mapGpioToTouchPad(sliderPins[i]);
    if(_arraySliderPads[i] == TOUCH_PAD_MAX) {
      Serial.printf("Error: GPIO pin %d is not a valid touch pad.\n", sliderPins[i]);
      return;
    }
    TOUCH_THRESHOLD_ARRAY[i] = threshold[i];
  }

  TOUCH_BUTTON_MAX = TOUCH_PAD_MAX - _numSliderPins;

  touch_pad_init();                                 // Initialize touch pad peripheral
  touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);     // If use interrupt trigger mode, should set TOUCH_FSM_MODE_TIMER
                                                    // Set reference voltage for charging/discharging
                                                    // For most usage scenarios, we recommend using the following combination:
                                                    // the high reference valtage will be 2.7V - 1V = 1.7V, The low reference voltage will be 0.5V.
                                                    
  touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V5);

  setDefaultConfiguration();
}

/*********************** PUBLIC FUNCTIONS **********************/
/**
 * @brief Add a touch button to the TouchSlider.
 *
 * This function adds a touch button to the TouchSlider if there is available space and the button is not already in the list of touch buttons or sliders.
 *
 * @param buttonPin The GPIO pin connected to the touch button.
 * @param thresholdPercent The threshold percentage for the touch button.
 */
void TouchSlider::addTouchButton(gpio_num_t buttonPin, uint8_t thresholdPercent)
{
  if (_numTouchButtons >= TOUCH_BUTTON_MAX) {   // Check if there is space available to add more touch buttons
    return; // No space available, exit the function
  }

  for (uint8_t i = 0; i < _numTouchButtons; ++i) {    // Check if the button is already in the list of touch buttons
    if (_arrayButtonPins[i] == buttonPin) {
      Serial.printf("Button %d is already in the list of touch buttons.\n", buttonPin);
      return; // The button is already in the list of buttons, exit the function
    }
  }

  for (uint8_t i = 0; i < _numSliderPins; ++i) {      // Check if the button is already in the list of sliders
    if (_arraySliderPins[i] == buttonPin) {
      Serial.printf("Button %d is already in the list of sliders.\n", buttonPin);
      return; // The button is already in the list of sliders, exit the function
    }
  }
  
  _arrayButtonPins[_numTouchButtons] = buttonPin;     // Add the touch button
  _arrayButtonPads[_numTouchButtons] = mapGpioToTouchPad(buttonPin);
  if(_arrayButtonPads[_numTouchButtons] == TOUCH_PAD_MAX) {
    Serial.printf("Error: GPIO pin %d is not a valid touch pad.\n", buttonPin);
    return;
  }

  Serial.printf("Added Button %d successfully with TouchPin %d.", _numTouchButtons + 1, mapGpioToTouchPad(buttonPin));
  enableTouchButtons();
  _buttonThresholdPercent[_numTouchButtons] = thresholdPercent;
  _numTouchButtons++;
}

/**
 * @brief Remove a touch button from the TouchSlider
 *
 * This function removes a touch button from the TouchSlider if it is in the list of touch buttons.
 * @note  If the button is not in the list of touch buttons, the function will return without removing the button.
 * @param  buttonPin: The GPIO pin connected to the touch button.
 */
void TouchSlider::removeTouchButton(gpio_num_t buttonPin)
{
  if(_numTouchButtons == 0) {
    Serial.println("No touch buttons to remove.");
    return;
  }

  for (uint8_t i = 0; i < _numTouchButtons; ++i) {          // Check if the button is already in the list of touch buttons
    if (_arrayButtonPins[i] == buttonPin) {
      for(uint8_t j = i; j < _numTouchButtons - 1; ++j) {   // Shift the remaining buttons in the list one position to the left
        _arrayButtonPins[j] = _arrayButtonPins[j + 1];
        _arrayButtonPads[j] = _arrayButtonPads[j + 1];
        _buttonThresholdPercent[j] = _buttonThresholdPercent[j + 1];
      }
      Serial.printf("Removing Button %d from the list of touch buttons.\n", buttonPin);
      return;
    }
  }

  Serial.printf("Button %d is not in the list of touch buttons.\n", buttonPin);
}


/**
 * @brief Start the touch slider.
 *
 * This function initializes and starts the touch slider by setting up the touch pads and beginning the slider operation.
 */
void TouchSlider::start() {
  for (uint8_t i = 0; i < _numSliderPins; ++i) {
    if (TOUCH_THRESHOLD != 0)   // Set the touch threshold for each slider pad based on the configuration
      setInput(_arraySliderPads[i], TOUCH_THRESHOLD);
    else
      setInput(_arraySliderPads[i], TOUCH_THRESHOLD_ARRAY[i]);
  }

  // Configure the touch pads for buttons using _buttonThresholdPercent
  for (uint8_t i = 0; i < _numTouchButtons; ++i) {
    setInput(_arrayButtonPads[i], _buttonThresholdPercent[i]);  // Set the touch threshold for buttons
  }

  begin();  // Begin the touch slider operation
}

/**
 * @brief Stop the touch slider timer.
 *
 * This function stops the timer responsible for updating the touch slider. It detaches the timer, marking that the slider is not currently running.
 */
void TouchSlider::stop() {
  if (_sliderRunning) {
    touch_pad_filter_stop();
    sliderTicker.detach();  // Stop the timer if it is running
    _sliderRunning = false;  // Mark that the timer is not running
  }
}

/**
 * @brief Resume the touch slider timer.
 *
 * This function resumes the timer for updating the touch slider. If the timer is not currently running, it attaches the timer and marks that the slider is in operation.
 */
void TouchSlider::resume() {
  if (!_sliderRunning) {
    touch_pad_filter_start(filter_period);
    sliderTicker.attach_ms(UPDATE_INTERVAL, update, this);  // Restart the timer if it is not running
    _sliderRunning = true;  // Mark that the timer is running
  }
}


/**
 * @brief Calibrate the touch pads thresholds.
 *
 * This function calibrates the touch pad thresholds by reading the filtered touch values and calculating the thresholds based on a specified percentage.
 * It logs the calibrated thresholds for each enabled touch pad.
 */
void TouchSlider::calibrate_thresholds() {
  uint16_t touch_value;
  for (uint8_t i = 0; i < TOUCH_PAD_MAX; ++i) {
    if (_padEnabled[i]) {   
      touch_pad_read_filtered(static_cast<touch_pad_t>(i), &touch_value);   // Read the filtered touch value for the touch pad (i)
      _padThreshold[i] = static_cast<uint32_t>(touch_value) * _padThresholdPercent[i] / 100;  // Calculate and store the threshold based on a percentage of the touch value
      log_i("T%u: %u - Threshold: %u", i, touch_value, _padThreshold[i]);   // Log the calibrated threshold for reference
    }
  }
}

/**
 * @brief Get the swipe status of the TouchSlider.
 *
 * This function calculates and returns the swipe status, which is the difference between the counts of swipe-down and swipe-up gestures.
 * It resets the swipe counts after retrieving the swipe status.
 *
 * @return An int8_t value representing the swipe status.
 *   - Positive values indicate swipe-down gestures.
 *   - Negative values indicate swipe-up gestures.
 *   - 0 indicates no swipe.
 */
int8_t TouchSlider::getSwipeStatus() {
  int8_t swipeStatus = _swipeDownCount - _swipeUpCount;   // Calculate the swipe status as the difference between swipe-down and swipe-up counts

  // Reset the swipe counts after retrieving the swipe status
  _swipeUpCount = 0;
  _swipeDownCount = 0;
  return swipeStatus;
}

/**
 * @brief Get the swipe status fine of the TouchSlider.
 *
 * This function calculates and returns the swipe status fine, which is the difference between the counts of swipe-down and swipe-up gestures.
 * It resets the swipe counts after retrieving the swipe status.
 *
 * @return An int8_t value representing the swipe status fine.
 *   - Positive values indicate swipe-down gestures.
 *   - Negative values indicate swipe-up gestures.
 *   - 0 indicates no swipe.
 */
int8_t TouchSlider::getSwipeStatusFine() {
  if(!_enableSwipeFine) {
    Serial.println("Swipe Fine is disable, to active this function use enableSwipeFine()");   // Debugging
    return 0;
  } else {
    int8_t swipeFineStatus = _swipeFineDownCount - _swipeFineUpCount;   // Calculate the swipe status as the difference between swipe-down and swipe-up counts

    // Reset the swipe counts after retrieving the swipe status
    _swipeFineUpCount = 0;
    _swipeFineDownCount = 0;

    return swipeFineStatus;
  }
}

/**
 * @brief Get the index of the button that was short-pressed and reset the flag.
 *
 * This function gets the gpio_num_t of the button that was short-pressed and resets the flag.
 *
 * @return The gpio_num_t of the button that was short-pressed and the flag is reset, or 0 if no button was short-pressed.
 */
gpio_num_t TouchSlider::getButtonShortPress() {
  if(!_enableTouchButtons) {
    Serial.println("Touch Buttons is disable, to active this function use enableTouchButtons()");   // Debugging
    return GPIO_NUM_NC;
  }
  gpio_num_t gpioButtonTouched = _gpioButtonTouched;    // Temporary variable to store the button that was short-pressed
  _gpioButtonTouched = GPIO_NUM_NC;                     // Reset the flag for button press

  return gpioButtonTouched;                             // Return the button that was short-pressed
}

/**
 * @brief Get the button pin pressed status.
 * @note  If the button pin is not in the list of touch buttons, the function will return false.
 * @param  buttonPin: The gpio_num_t of the button
 * @retval true: The button pin is pressed
 */
bool TouchSlider::isTouchButtonPressed(gpio_num_t buttonPin)
{
  return _ButtonTouched[getIndexFromGpioButton(this, buttonPin)];
}

/**
 * @brief Get the slider pin touched status.
 * @note  If the slider pin is not in the list of touch sliders, the function will return false.
 * @param sliderPin: The gpio_num_t of the slider
 * @retval true: The slider pin is touched
 */
bool TouchSlider::isTouchSliderPressed(gpio_num_t sliderPin)
{
  return _SliderTouched[getIndexFromGpioSlider(this, sliderPin)];
}

/**
 * @brief Get the slider touched status.
 * 
 * @param sliderTouched: The array to store the slider touched status
 * @param numSliderPins: The number of slider pins
 * 
 * This function gets the slider touched status and stores it in the provided array. 
 */
void TouchSlider::getSliderTouched(bool sliderTouched[], uint8_t numSliderPins)
{
  for (uint8_t i = 0; i < numSliderPins; ++i) {
    sliderTouched[i] = _SliderTouched[i];
  }
}


/*********************** PRIVATE FUNCTIONS **********************/
/**
 * @brief  Set a touch pad input
 * @param  padNumber: The touch pad number
 * @param  thresholdPercent: Percent to detect as touched
 */
void TouchSlider::setInput(uint8_t padNumber, uint8_t thresholdPercent) {
  _padEnabled[padNumber] = true;
  _padThresholdPercent[padNumber] = thresholdPercent;
}

void TouchSlider::setDefaultConfiguration()
{
  #ifdef START_PRINT_SWIPE_STATUS
    enablePrintSwipeStatus();         // Enable print swipe status
  #endif
  #ifdef START_PRINT_SLIDER_TOUCHED
    enablePrintSliderTouched();       // Enable print slider touched
  #endif
  #ifdef START_WITH_SWIPE_FINE
    enableSwipeFine();                // Enable swipe fine
  #endif
  #ifdef START_WITH_TOUCH_BUTTONS
    enableTouchButtons();             // Enable touch buttons
  #endif 

}

/**
 * @brief Initialize the touch slider.
 *
 * This function initializes the touch slider by configuring the touch pads, setting up a software filter for capacitance change detection,
 * calibrating thresholds, and starting the slider update process.
 */
void TouchSlider::begin() {
  log_i("Initializing touch slider...");

  for (uint8_t i = 0; i < TOUCH_PAD_MAX; ++i) {     // Configure enabled touch pads with the specified inactive threshold
    if (_padEnabled[i]) {
      touch_pad_config(static_cast<touch_pad_t>(i), threshold_inactive);    // (touch_pad_t) i
    }
  }
  // Initialize and start a software filter to detect slight change of capacitance.
  touch_pad_filter_start(filter_period);
  touch_pad_set_filter_read_cb(filter_read_cb);

  #ifdef START_WITH_CALIBRATION    // Start calibration if enabled (Check TouchSlider.h on LIBRARY OPTIONS)
    calibrate_thresholds();   // Calibrate the touch thresholds
  #endif
  sliderTicker.attach_ms(UPDATE_INTERVAL, update, this);    // Attach a timer interrupt to periodically update the slider
  log_i("Touch slider initialized!");
}

/**
 * @brief  Update the touch pads states
 * This method is called periodically by a ticker
 */
void TouchSlider::update(TouchSlider* self) {
  bool padTouchedFound = false;
  int8_t firstTouchedIndex = -1;
  int8_t lastTouchedIndex = -1;
  uint8_t touchedPadCount = 0;

  // Check touch status and count touched pads
  checkSliderStatus(self, padTouchedFound, firstTouchedIndex, lastTouchedIndex, touchedPadCount);

  if (!padTouchedFound) { // Handle the cases when no pad is touched
    handleNoTouch(self);
  } else {  // Handle the case when at least one pad is touched
    handleTouch(self, firstTouchedIndex, lastTouchedIndex, touchedPadCount);
  }

  if(self->_enableTouchButtons) {     // Check if touch buttons are enabled
    checkButtonStatus(self);          // Check if touch buttons are touched
    checkSingleButtonTouch(self);     // Check for a single touch and release of a button
  }
}

/**
 * @brief Check the touch status of touch buttons.
 *
 * This function checks the touch status of the touch buttons based on the filtered values and thresholds.
 *
 * @param self Pointer to the TouchSlider instance.
 */
void TouchSlider::checkButtonStatus(TouchSlider* self) {
  for (uint8_t i = 0; i < self->_numTouchButtons; ++i) {  // Loop through the button pins to check their touch status
    if (_padEnabled[self->_arrayButtonPads[i]]) {
      // Check if the touch pad is touched based on the filtered value and threshold
      self->_ButtonTouched[i] = _padFilteredValue[self->_arrayButtonPads[i]] < _padThreshold[self->_arrayButtonPads[i]];  
    }
  }
}

/**
 * @brief Check for a single touch and release of a button.
 *
 * This function checks if a single button is touched and released without any other buttons being touched in between.
 * If such an event is detected, it returns the index of the button (i+1) that was touched and released.
 * If no such event is detected, it returns 0.
 *
 * @param self Pointer to the TouchSlider instance.
 * @return The index of the button (i+1) that was touched and released, or 0 if no such event occurred.
 */
void TouchSlider::checkSingleButtonTouch(TouchSlider* self) {
  static bool buttonTouched = false;
  static bool printedOnce = false;
  static gpio_num_t gpioButtonTouched = GPIO_NUM_NC;
  uint8_t countButtonsTouched = 0;


  if (buttonTouched && !self->_ButtonTouched[getIndexFromGpioButton(self, gpioButtonTouched)]) {      // If a single button touch is detected and that button is released
    
    self->_gpioButtonTouched = gpioButtonTouched;                                                     // Set the touched button index

    if(self->_enablePrintBottonTouched) 
      LOGIG("GPIO Button Touched: %s", String(self->_gpioButtonTouched).c_str());        // Print the gpio pin of the button that was touched

    buttonTouched = false;                                                                            // Reset the state
    gpioButtonTouched = GPIO_NUM_NC;                                                                  // Reset the gpio pin of the button that was touched
    printedOnce = false; // Reset the printed 
    return;
  }

  for (uint8_t i = 0; i < self->_numTouchButtons; ++i) {          // Check the status of each button
    if (self->_ButtonTouched[i]) {
      ++countButtonsTouched;
      gpioButtonTouched = self->_arrayButtonPins[i];              // Copy the gpio pin of the button that was
    }
  }

   if(countButtonsTouched == 0) {
    gpioButtonTouched = GPIO_NUM_NC;
    buttonTouched = false;
    printedOnce = false;                                        // Reset the printed flag
    return;
  } else if (countButtonsTouched == 1) {
    buttonTouched = true;
    if (self->_enablePrintBottonTouched && !printedOnce) {
        self->printButtonTouched();                             // Print the array of touched buttons
        printedOnce = true;                                     // Ensure that printing only happens once
      }
  } else {
    gpioButtonTouched = GPIO_NUM_NC;
    buttonTouched = false;
    printedOnce = false;                                        // Reset the printed flag
    return;
  }
}

/**
 * @brief Check the touch status of the slider pads.
 *
 * @param self Pointer to the TouchSlider instance.
 * @param padTouchedFound Variable to indicate if any pad is touched.
 * @param firstTouchedIndex Index of the first touched pad.
 * @param lastTouchedIndex Index of the last touched pad.
 * @param touchedPadCount Count of touched pads.
 */
void TouchSlider::checkSliderStatus(TouchSlider* self, bool& padTouchedFound, int8_t& firstTouchedIndex,
                                   int8_t& lastTouchedIndex, uint8_t& touchedPadCount) {
  for (uint8_t i = 0; i < self->_numSliderPins; ++i) {  // Loop through the slider pins to check their touch status
    if (_padEnabled[self->_arraySliderPads[i]]) {
      // Check if the touch pad is touched based on the filtered value and threshold
      self->_SliderTouched[i] = _padFilteredValue[self->_arraySliderPads[i]] < _padThreshold[self->_arraySliderPads[i]];  
      if (self->_SliderTouched[i]) {
        touchedPadCount++; // Increment the touched pad count if this pad is touched
      }
    }
  }

  for (uint8_t i = 0; i < self->_numSliderPins; ++i) {  // Determine the first and last touched pad indices
    if (self->_SliderTouched[i]) {
      padTouchedFound = true;
      if (firstTouchedIndex == -1) {
        firstTouchedIndex = i;
      }
      lastTouchedIndex = i;
    }
    self->_lastValue = self->_actualValue;  // Store the last value for reference
  }
}

/**
 * @brief Handle cases when no pad is touched.
 *
 * @param self Pointer to the TouchSlider instance.
 */
void TouchSlider::handleNoTouch(TouchSlider* self) {
  for (uint8_t i = 0; i < self->_numSliderPins; ++i) {
    self->_sliderValue[i] = 0;  // Reset slider values and set actual value to 0
  }
  self->_actualValue = 0;
  self->firstTouch = true;

  if(self->_enableSwipeFine) {    // Check if that functionality Swipe Fine is active 
    // Increment swipe counts if the first pad touched was top or bottom
    if(self->firstPadTop) {
      self->_swipeFineUpCount++;
      if(self->_enablePrintSwipeStatus) LOGIB("SWIPE FINE UP");
    }
    if(self->firstPadBot) {
      self->_swipeFineDownCount++;
      if(self->_enablePrintSwipeStatus) LOGIR("SWIPE FINE DOWN");
    }
  }
  
  self->resetFirstTouches();
}

/**
 * @brief Handle cases when at least one pad is touched.
 *
 * @param self Pointer to the TouchSlider instance.
 * @param firstTouchedIndex Index of the first touched pad.
 * @param lastTouchedIndex Index of the last touched pad.
 * @param touchedPadCount Count of touched pads.
 */
void TouchSlider::handleTouch(TouchSlider* self, int8_t firstTouchedIndex, int8_t lastTouchedIndex, uint8_t touchedPadCount) {
  if(self->firstTouch == true) {  // Check if this is the first entry into this condition block
  if(self->_enablePrintSliderTouched) self->printSliderTouched();       // Check if _enablePrintSliderTouched is true for a Print SliderTouched[] 
    if(touchedPadCount == 1) {    // Check if only one pad is touched
      if (self->_SliderTouched[0] == true) {  
        self->firstPadBot = true;
        if(self->_enablePrintSwipeStatus) LOGIR("FIRST TOUCH BOT");
      }
      if(self->_SliderTouched[self->_numSliderPins - 1] == true) {
        self->firstPadTop = true;
        if(self->_enablePrintSwipeStatus) LOGIB("FIRST TOUCH TOP");
      }
    }
  }

  // Calculate slider values based on touched pads
  for (uint8_t i = 0; i < self->_numSliderPins; ++i) {
    if (i >= firstTouchedIndex && i <= lastTouchedIndex) {
      self->_sliderValue[i] = 0;
    } else if (i < firstTouchedIndex) {
      self->_sliderValue[i] = -1;
    } else if (i > lastTouchedIndex) {
      self->_sliderValue[i] = 1;
    }
  }
  self->analyzeGesture(self->_numSliderPins);   // Analyze the gesture based on the slider values
  self->firstTouch = false;
}

/**
 * @brief Get the index of a slider pin based on its GPIO pin number.
 *
 * @param self Pointer to the TouchSlider instance
 * @param gpioPin The GPIO pin number of the slider pin
 * @return The index of the slider pin, or UINT8_MAX if not found
 */
uint8_t TouchSlider::getIndexFromGpioSlider(TouchSlider* self, gpio_num_t gpioPin) {
  for (uint8_t i = 0; i < TOUCH_PAD_MAX; ++i) {
        if (self->_arraySliderPins[i] == gpioPin) {
            return i; 
        }
    }
    return UINT8_MAX; 
}

/**
 * @brief Get the index of a button pin based on its GPIO pin number.
 *
 * @param self Pointer to the TouchSlider instance
 * @param gpioPin The GPIO pin number of the button pin
 * @return The index of the button pin, or UINT8_MAX if not found
 */
uint8_t TouchSlider::getIndexFromGpioButton(TouchSlider* self, gpio_num_t gpioPin)
{
  for(uint8_t i = 0; i < TOUCH_PAD_MAX; ++i) {
    if(self->_arrayButtonPins[i] == gpioPin) {
      return i;
    }
  }
  return UINT8_MAX;
}


/**
 * @brief Analyze the slider touch pad states to detect a swipe up or down gesture.
 *
 * This function analyzes the states of the slider touch pads to detect swipe gestures (up or down).
 * It calculates the actual value based on slider values and compares it to the previous value to determine the gesture.
 * Detected gestures are logged for monitoring purposes.
 *
 * @param numSliders The number of slider touch pads to analyze.
 */
void TouchSlider::analyzeGesture(uint8_t numSliders) {
  _actualValue = 0;
  for (uint8_t i = 0; i < numSliders; ++i) {    // Calculate the actual value by summing slider values
    _actualValue += _sliderValue[i];
  }

  if (_actualValue != _lastValue && !firstTouch) {            // Check if there is no change or it's the first touch
    if(_enablePrintSliderTouched) printSliderTouched();       // Check if _enablePrintSliderTouched is true for a Print SliderTouched[] 
    _swipeCount = _actualValue - _lastValue;                  // Calculate the swipe count and determine the gesture
    if (_swipeCount > 0) {
      _sliderState = SWIPE_DOWN;
      _swipeDownCount++;
      resetFirstTouches();
      if(_enablePrintSwipeStatus) LOGIR("SWIPE DOWN");
    } else if (_swipeCount < 0) {
      _sliderState = SWIPE_UP;
      _swipeUpCount++;
      resetFirstTouches();
      if(_enablePrintSwipeStatus) LOGIB("SWIPE_UP");
    } else {
      _sliderState = NO_CHANGE;
    }
  } else {
    _sliderState = NO_CHANGE;
  }
}

/**
 * @brief Reset first touch flags.
 */
void TouchSlider::resetFirstTouches() {
  firstPadBot = false;
  firstPadTop = false;
}

/**
 * @brief Print the states of the touch buttons.
 *
 * This function prints the status of the touch buttons, indicating whether each button is currently touched or not.
 */
void TouchSlider::printButtonTouched() {
  String touchedStatus;
  for (uint8_t i = 0; i < _numTouchButtons; i++) {
    touchedStatus += " " + String(_ButtonTouched[i]);
  }

  log_i("Button Touched Status: %s", touchedStatus.c_str());
}

/**
 * @brief Print the states of the slider touch pads based on _padFilteredValue.
 *
 * This function prints the status of the slider touch pads using _padFilteredValue,
 * indicating whether each touch pad is currently touched or not.
 */
void TouchSlider::printSliderFilteredValues() {
  String touchedStatus;
  for (uint8_t i = 0; i < _numSliderPins; i++) {
    touchedStatus += " " + String(_padFilteredValue[_arraySliderPads[i]]);
  }

  log_i("Slider Touched Status (Using Pad Values): %s", touchedStatus.c_str());
}

/**
 * @brief Print the states of the slider touch pads.
 *
 * This function prints the status of the slider touch pads, indicating whether each touch pad is currently touched or not.
 */
void TouchSlider::printSliderTouched() {
  String touchedStatus;
  for (uint8_t i = 0; i < _numSliderPins; i++) {
    touchedStatus += " " + String(_SliderTouched[i]);
  }

  log_i("Slider Touched Status: %s", touchedStatus.c_str());
}

/**
 * @brief Print the slider values.
 *
 * This function prints the values of the slider pins to the log. It generates a string representation
 * of the slider values and logs it for debugging or monitoring purposes.
 *
 * @param numSliders The number of slider values to print.
 */
void TouchSlider::printSliderValues(uint8_t numSliders) {
  String values;
  for (uint8_t i = 0; i < numSliders; ++i) {
    values += " " + String(_sliderValue[i]);
  }
  log_i("Slider values:%s", values.c_str());
}


/**
 * @brief  Callback function to get the filtered value of touch pad
 * @param raw_value Array containing raw touch pad values.
 * @param filtered_value Array containing filtered touch pad values.
 */
void TouchSlider::filter_read_cb(uint16_t *raw_value, uint16_t *filtered_value) {
  for (uint8_t i = 0; i < TOUCH_PAD_MAX; ++i) {
    if (_padEnabled[i]) {       // Check if the touch pad is enabled
      _padFilteredValue[i] = filtered_value[i];   // Update the filtered value for the enabled touch pad
    }
  }
}

/**
 * @brief Map a GPIO pin to its corresponding touch pad on ESP32 or ESP8266.
 *
 * This function maps a GPIO pin to its corresponding touch pad number based on the microcontroller used.
 *
 * @param gpioPin The GPIO pin number to be mapped.
 * @return The corresponding touch pad number or TOUCH_PAD_MAX if not found.
 */
touch_pad_t TouchSlider::mapGpioToTouchPad(gpio_num_t gpioPin) {
#ifdef ESP32
    if (gpioPin == GPIO_NUM_4) return TOUCH_PAD_NUM0;
    else if (gpioPin == GPIO_NUM_0) return TOUCH_PAD_NUM1;
    else if (gpioPin == GPIO_NUM_2) return TOUCH_PAD_NUM2;
    else if (gpioPin == GPIO_NUM_15) return TOUCH_PAD_NUM3;
    else if (gpioPin == GPIO_NUM_13) return TOUCH_PAD_NUM4;
    else if (gpioPin == GPIO_NUM_12) return TOUCH_PAD_NUM5;
    else if (gpioPin == GPIO_NUM_14) return TOUCH_PAD_NUM6;
    else if (gpioPin == GPIO_NUM_27) return TOUCH_PAD_NUM7;
    else if (gpioPin == GPIO_NUM_33) return TOUCH_PAD_NUM8;
    else if (gpioPin == GPIO_NUM_32) return TOUCH_PAD_NUM9;
#else
    if (gpioPin == GPIO_NUM_1) return TOUCH_PAD_NUM1;
    else if (gpioPin == GPIO_NUM_2) return TOUCH_PAD_NUM2;
    else if (gpioPin == GPIO_NUM_3) return TOUCH_PAD_NUM3;
    else if (gpioPin == GPIO_NUM_4) return TOUCH_PAD_NUM4;
    else if (gpioPin == GPIO_NUM_5) return TOUCH_PAD_NUM5;
    else if (gpioPin == GPIO_NUM_6) return TOUCH_PAD_NUM6;
    else if (gpioPin == GPIO_NUM_7) return TOUCH_PAD_NUM7;
    else if (gpioPin == GPIO_NUM_8) return TOUCH_PAD_NUM8;
    else if (gpioPin == GPIO_NUM_9) return TOUCH_PAD_NUM9;
    else if (gpioPin == GPIO_NUM_10) return TOUCH_PAD_NUM10;
    else if (gpioPin == GPIO_NUM_11) return TOUCH_PAD_NUM11;
    else if (gpioPin == GPIO_NUM_12) return TOUCH_PAD_NUM12;
    else if (gpioPin == GPIO_NUM_13) return TOUCH_PAD_NUM13;
    else if (gpioPin == GPIO_NUM_14) return TOUCH_PAD_NUM14;
#endif
    return TOUCH_PAD_MAX;
}