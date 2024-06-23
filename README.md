# TouchSlider Library for ESP32
[![PlatformIO](https://img.shields.io/badge/PlatformIO-5.2.1-blue.svg)](https://platformio.org/)
[![Version](https://img.shields.io/badge/Version-1.0.0-brightgreen.svg)](https://github.com/tu_usuario/tu_repositorio)

## Overview
The TouchSlider library is designed for ESP32 modules equipped with touch pins. It leverages these capabilities to create an array of touch pads that act as a slider, detecting the direction and position of a finger slide. The library includes features such as sensitivity adjustment, accurate detection, timer-based updates and readings, pause and resume functionalities, and the ability to detect touch on specific pads for unique functions.

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/449c4ea8-9ca7-4ee6-bcf4-e3a0c1acb749" alt="SwipeUp/SwipeDown">
  <br>
  <em>SwipeUp/SwipeDown</em>
</p>
<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/2be7a1b3-af98-4152-99bd-f215ecb79216" alt="First Touch TopPad/BotPad">
  <br>
  <em>First Touch TopPad/BotPad</em>
</p>
This is an example of the functionality of a touch slider. However, it can also be used to adjust volume, thresholds, brightness, the number of LEDs, timers, etc.

## Supported Modules

<div align="center">
  
| Manufacturer | Series     | Module Part Number      | Touch Pins | Compatible |
|--------------|------------|-------------------------|------------|------------|
| Espressif    | ESP32-S3   | ESP32-S3-MINI-1-N8      | 14         | ✔️         |
| Espressif    | ESP32      | ESP32-MINI-1-N4         | 10         | ✔️         |
| Espressif    | ESP32      | ESP32-WROOM-32E         | 10         | ✔️         |
| Espressif    | ESP32 PICO | ESP32-PICO-MINI-02-N8R2 | 10         | ✔️         |
| Espressif    | ESP32-C3   | ESP32-C3-MINI-1-N4      | 0          |            |
| Espressif    | ESP32-C2   | ESP8684-MINI-1-H4       | 0          |            |
| Espressif    | ESP32-C6   | ESP32-C6-MINI-1-N4      | 0          |            |
| Espressif    | ESP32-H2   | ESP32-H2-MINI-1-N4      | 0          |            |
</div>

</p>
<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/82256c81-857d-4016-a889-9af0f98bc8ba" alt="Touch Slider on the ESP32">
  <br>
  <em>Touch Slider on the ESP32</em>
</p>

For more information, refer to the [Espressif API Reference for Touch Element](https://docs.espressif.com/projects/esp-idf/en/v4.3.2/esp32s2/api-reference/peripherals/touch_element.html).

For additional guidance on designing touch pads and sliders in PCB designs, you can refer to the [Touch Sensor Application Note](https://github.com/ESP32DE/esp-iot-solution-1/blob/master/documents/touch_pad_solution/touch_sensor_design_en.md).

## Features

- **Sensitivity Adjustment:** Configure the sensitivity of the touch pads to detect various touch intensities.
- **Accurate Detection:** Reliable and precise touch detection across the touch slider.
- **Gesture Completion:** Automatically completes gestures even if a touch reading is missed.
- **Timer-Based Updates:** Uses timers for efficient touch data updates and readings.
- **Pause and Resume:** Ability to pause and resume touch detection.
- **Edge Detection:** Detects touches on specific pads (edges) to perform different functions apart from sliding.
- **Enable/Disable Print Data:** Options to enable or disable printing of touch data for debugging and monitoring.
- **Separate Touch Pad Detection:** Detects each touch pad individually for more detailed interaction handling.
- **Touch Buttons:** Basic functionality for detecting touch on pads designated as simple buttons, useful for straightforward actions.
- **Simple Configuration:** Default initial configuration can be modified in the header file to suit specific needs.

## Why This Library

With the ESP32 boards, there are a few libraries that implement touch functionalities, but they are often very basic and lack advanced features. I couldn't find any public libraries that effectively use the touch functions of the ESP32 to implement a touch slider capable of detecting gestures accurately and efficiently.

</p>
<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/e87e2509-c57c-43be-b04b-3cd9d3e12b22" alt="Gesture in the Slider">
  <br>
  <em>Gesture in the Slider</em>
</p>

### Key Challenges Addressed:

- **Detection Issues:** Existing libraries often struggle with gesture detection, especially when the gesture is performed quickly. This library aims to provide reliable and precise touch detection across the touch slider.
  
- **Swipe Fine Functionality:** A unique feature developed during the course of this project is the "Swipe Fine" functionality. If a pad at the edges of the touch slider is touched for the first time, it is detected as a "Swipe Fine" gesture. This can be configured to perform a different set of actions or act as a single "Swipe." This is particularly useful for making fine adjustments on small sliders where accurate value adjustments with a single swipe can be challenging.

### Advantages:

- **Minimal Configuration:** Compared to other libraries, this one requires minimal configuration to get started.
- **Efficient Gesture Detection:** Ensures accurate and efficient gesture detection, even for fast gestures.
- **Comprehensive Touch Functionality:** Beyond basic touch detection, it includes advanced features like edge detection and swipe fine gestures.
- **Dedicated Touch Slider Implementation:** Specifically designed for implementing touch sliders on ESP32, addressing common issues found in other libraries.

This library aims to fill the gap by providing a robust solution for touch slider implementation on ESP32, with advanced features and reliable gesture detection.

## Authors

- [@MarcosCarballoV](https://github.com/MarcosCarballoV)

## Dependencies

This library depends on:

- **Arduino Library for ESP32:** Required for basic functionality and development within the PlatformIO environment for the ESP32.
- **ESP32 Touch Pad Driver:** Provides the necessary functions to work with the touch capabilities of the ESP32.
- **Ticker Library:** Enables the creation of timers, which are essential for periodically reading the touch pads.
- **Logger Library:** An additional library included in this repository. It facilitates the visualization of messages in the serial port with different colors, making it very useful for differentiating messages and debugging the code.

## Setup Instructions

The steps to install this library depend on the IDE you are using. PlatformIO is recommended, but the library can also be used with the plain Arduino IDE.

### PlatformIO (Recommended)

1. **Add the Library:**
   - Open the `platformio.ini` file in your project.
   - Add the following line to include the TouchSlider library:
     ```ini
     lib_deps =
       https://github.com/MarcosCarballoV/TouchSlider_ESP32
     ```

2. **Include the Library in Your Code:**
   - In your main `.cpp` or `.ino` file, include the TouchSlider library:
     ```cpp
     #include <TouchSlider.h>
     ```

3. **Upload Your Code:**
   - Write your code using the TouchSlider library.
   - Connect your ESP32 board to your computer.
   - Click the upload button in PlatformIO to compile and upload your code to the board.

### Arduino IDE

1. **Install the TouchSlider Library:**
   - Download the TouchSlider library from the [GitHub repository](https://github.com/MarcosCarballoV/TouchSlider_ESP32).
   - Open the Arduino IDE.
   - Go to `Sketch` > `Include Library` > `Add .ZIP Library...`.
   - Select the downloaded TouchSlider library ZIP file to install it.

2. **Include the Library in Your Code:**
   - In your `.ino` file, include the TouchSlider library:
     ```cpp
     #include <TouchSlider.h>
     ```

3. **Upload Your Code:**
   - Write your code using the TouchSlider library.
   - Connect your ESP32 board to your computer.
   - Select the correct board and port from `Tools` > `Board` and `Tools` > `Port`.
   - Click the upload button to compile and upload your code to the board.

## Get Started

To use this library in your project, you need to include the following headers and set up the touch slider.

### Includes and Definitions

```cpp
#include "TouchSlider.h"
#include <Ticker.h>

// Define the threshold percentage for the slider
#define THRESHOLD_SLIDER  60

// Define the GPIO pins for the slider
#define SLIDER1_PIN     GPIO_NUM_33 
#define SLIDER2_PIN     GPIO_NUM_27
#define SLIDER3_PIN     GPIO_NUM_14 
#define SLIDER4_PIN     GPIO_NUM_4  

// Array of slider pins
gpio_num_t arraySlidersPins[] = {    
  SLIDER1_PIN,
  SLIDER2_PIN,
  SLIDER3_PIN,
  SLIDER4_PIN
};

// Number of sliders
size_t numSlidersPins = sizeof(arraySlidersPins) / sizeof(arraySlidersPins[0]);

// TouchSlider object
TouchSlider touchSlider(arraySlidersPins, THRESHOLD_SLIDER, numSlidersPins);

// Ticker object for updating touch slider
Ticker _sliderTicker;

// Interval for updating touch slider
const uint8_t SLIDER_INTERVAL = 200;    // It is not recommended to use values ​​less than 100 milliseconds

// Enum for determining slider direction
enum { INCREASE, DECREASE };            // You can change the names, depending on your project, example: AUDIO_UP, AUDIO DOWN, BRIGHTNESS UP, BRIGHTNESS DOWN, etc.
```

### Create Logic/Function for Each Gesture
It is necessary to create a function that will be repeatedly called by a timer configured in the main program.

```cpp
void updateTouchSlider() {                                 // Update touch slider
  // Serial.println("Updating touch slider");              // Debugging

  int8_t swipeStatus = touchSlider.getSwipeStatus();       // Get swipe status
  if (swipeStatus != 0) {
    for (int8_t i = 0; i < abs(swipeStatus); ++i) {        // Convert swipe status to absolute value to determine count of iterations
      if (swipeStatus > 0) 
        updateAction(INCREASE);                            // This function handles the swipe status in the direction of increase
      else 
        updateAction(DECREASE);                            // This function handles the swipe status in the direction of decrease
    }
  }

  int8_t swipeStatusFine = touchSlider.getSwipeStatusFine();      // Get swipe status fine
  if (swipeStatusFine != 0) {
    for (int8_t i = 0; i < abs(swipeStatusFine); ++i) {           // Convert swipe status fine to absolute value to determine count of iterations
      if (swipeStatusFine > 0) 
        updateActionFine(INCREASE);                               // This function handles the fine swipe on the first touch pad on the slider
      else 
        updateActionFine(DECREASE);                               // This function handles the fine swipe on the last touch pad on the slider
    }
  }
}
```

### Configure the TouchSlider and Start
In your setup, or any other part of the main program that only runs once, use the enable/disable functions to configure the features of this library, such as printing messages or using touch buttons. After configuring, start the continuous reading of the touch slider with `touchSlider.start();`. This reading occurs every 50ms by default but can be changed within the library.

```cpp
void setup() {
  Serial.begin(115200);                     // Begin serial communication
  Serial.println("Serial initialized");     // Debugging

  touchSlider.disableTouchButtons();
  touchSlider.disablePrintButtonTouched();
 
  touchSlider.start();                          // Start touch slider
  Serial.println("TouchSlider initialized");    // Debugging
  _sliderTicker.attach_ms(SLIDER_INTERVAL, updateTouchSlider);  // Attach ticker to update touch slider
}
```

### Implement Rest of Your Code
The updateTouchSlider() function will be called every SLIDER_INTERVAL (In this example, 200 ms), independently of the rest of the code

```cpp
void loop() {
  // Rest of the code
  /*
  ...
  ...
  */

  // The updateTouchSlider() function will be called every SLIDER_INTERVAL (In this example, 200 ms), independently of the rest of the code
}

```

## Documentation
### Static Members Initialization
```cpp
/*********************** PUBLIC VARIABLES **********************/
// Static members must be initialized here
bool TouchSlider::_padEnabled[TOUCH_PAD_MAX];               // Array to store the enabled status of each touch pad
uint8_t TouchSlider::_padThresholdPercent[TOUCH_PAD_MAX];   // Array to store the threshold percentage for each touch pad
uint16_t TouchSlider::_padFilteredValue[TOUCH_PAD_MAX];     // Array to store the filtered value of each touch pad
uint16_t TouchSlider::_padThreshold[TOUCH_PAD_MAX];         // Array to store the threshold value for each touch pad
int8_t TouchSlider::_sliderValue[TOUCH_PAD_MAX];           // Array to store the slider value for each touch pad, pad touch is set to 0, pad left is set to -1, pad right is set to 1
```

#### `bool _padEnabled[TOUCH_PAD_MAX]`
- **Description**: This array stores the enabled status of each touch pad.
- **Initialization**: By default, all touch pads are disabled (`false`). When the `TouchSlider` object is initialized in the constructor, this array is updated to `true` for the specified GPIO pins.

<div align="center">

#### GPIO to TouchPad Mapping for ESP32 and ESP32-S3

<table>
  <tr>
    <th colspan="2">ESP32</th>
    <th colspan="2">ESP32-S3</th>
  </tr>
  <tr>
    <th>GPIO</th>
    <th>TouchPan</th>
    <th>GPIO</th>
    <th>TouchPad</th>
  </tr>
  <tr>
    <td>GPIO_NUM_4</td>
    <td>TOUCH_PAD_NUM0</td>
    <td>GPIO_NUM_1</td>
    <td>TOUCH_PAD_NUM1</td>
  </tr>
  <tr>
    <td>GPIO_NUM_0</td>
    <td>TOUCH_PAD_NUM1</td>
    <td>GPIO_NUM_2</td>
    <td>TOUCH_PAD_NUM2</td>
  </tr>
  <tr>
    <td>GPIO_NUM_2</td>
    <td>TOUCH_PAD_NUM2</td>
    <td>GPIO_NUM_3</td>
    <td>TOUCH_PAD_NUM3</td>
  </tr>
  <tr>
    <td>GPIO_NUM_15</td>
    <td>TOUCH_PAD_NUM3</td>
    <td>GPIO_NUM_4</td>
    <td>TOUCH_PAD_NUM4</td>
  </tr>
  <tr>
    <td>GPIO_NUM_13</td>
    <td>TOUCH_PAD_NUM4</td>
    <td>GPIO_NUM_5</td>
    <td>TOUCH_PAD_NUM5</td>
  </tr>
  <tr>
    <td>GPIO_NUM_12</td>
    <td>TOUCH_PAD_NUM5</td>
    <td>GPIO_NUM_6</td>
    <td>TOUCH_PAD_NUM6</td>
  </tr>
  <tr>
    <td>GPIO_NUM_14</td>
    <td>TOUCH_PAD_NUM6</td>
    <td>GPIO_NUM_7</td>
    <td>TOUCH_PAD_NUM7</td>
  </tr>
  <tr>
    <td>GPIO_NUM_27</td>
    <td>TOUCH_PAD_NUM7</td>
    <td>GPIO_NUM_8</td>
    <td>TOUCH_PAD_NUM8</td>
  </tr>
  <tr>
    <td>GPIO_NUM_33</td>
    <td>TOUCH_PAD_NUM8</td>
    <td>GPIO_NUM_9</td>
    <td>TOUCH_PAD_NUM9</td>
  </tr>
  <tr>
    <td>GPIO_NUM_32</td>
    <td>TOUCH_PAD_NUM9</td>
    <td>GPIO_NUM_10</td>
    <td>TOUCH_PAD_NUM10</td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td>GPIO_NUM_11</td>
    <td>TOUCH_PAD_NUM11</td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td>GPIO_NUM_12</td>
    <td>TOUCH_PAD_NUM12</td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td>GPIO_NUM_13</td>
    <td>TOUCH_PAD_NUM13</td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td>GPIO_NUM_14</td>
    <td>TOUCH_PAD_NUM14</td>
  </tr>
</table>

</div>


#### `uint8_t _padThresholdPercent[TOUCH_PAD_MAX]`

- **Description**: This array stores the sensitivity threshold percentage for each touch pad. The sensitivity threshold determines the level at which a touch is detected, with 0 representing the lowest sensitivity and 100 representing the highest sensitivity.
  
- **Initialization**: The user can specify the sensitivity threshold percentage when configuring the touch pads. A value of 0 indicates the lowest sensitivity, while a value of 100 indicates the highest sensitivity. It is recommended to set the threshold between 50 and 70 for pads covered with solder mask. If an acrylic/glass or other material is attached to the pad, increase the value according to the thickness of the material.

#### `uint8_t _padFilteredValue[TOUCH_PAD_MAX]`

- **Description**: This array stores the filtered values for each touch pad. The filtered value represents a processed reading from the touch pad, where noise and other fluctuations have been minimized to provide a more stable and accurate detection of touch events.

- **Initialization**: The filtered values are automatically updated by the library as it processes the raw touch readings. These values help in making touch detection more reliable by reducing false triggers caused by noise. The values in the array depend on the configuration of the touch pins of the selected ESP32 module.

- **Configuration**:
  - First, initialize the touch pad module using `touch_pad_init()`.
  - Set the FSM (Finite State Machine) mode using `touch_pad_set_fsm_mode(touch_fsm_mode_t mode)`.

#### FSM Modes:
| Mode                   | Description                               | When to Use                              |
|------------------------|-------------------------------------------|------------------------------------------|
| `TOUCH_FSM_MODE_TIMER` | To start touch FSM by timer               | Use when periodic touch detection is needed automatically. |
| `TOUCH_FSM_MODE_SW`    | To start touch FSM by software trigger    | Use when touch detection is manually controlled by software. |

 - Set the voltage operation module using  `touch_pad_set_voltage(touch_high_volt_t refh, touch_low_volt_t refl, touch_volt_atten_t atten)`.

**Voltage Parameters:**
| Parameter | Description                  | Recommended Use                              |
|-----------|------------------------------|----------------------------------------------|
| `refh`    | High reference voltage       | Set according to the desired sensitivity and noise resistance. |
| `refl`    | Low reference voltage        | Set according to the desired sensitivity and noise resistance. |
| `atten`   | Voltage attenuation          | Adjust to control the touch sensitivity.     |

**Voltage Configuration Types:**

```cpp
/** Voltage configuration */
typedef enum {
    TOUCH_HVOLT_2V7 = 0,  /*!< High reference voltage 2.7V */
    TOUCH_HVOLT_2V4,      /*!< High reference voltage 2.4V */
    TOUCH_HVOLT_2V1,      /*!< High reference voltage 2.1V */
    TOUCH_HVOLT_1V8,      /*!< High reference voltage 1.8V */
    TOUCH_HVOLT_MAX,
} touch_high_volt_t;

typedef enum {
    TOUCH_LVOLT_0V5 = 0,  /*!< Low reference voltage 0.5V */
    TOUCH_LVOLT_0V6,      /*!< Low reference voltage 0.6V */
    TOUCH_LVOLT_0V7,      /*!< Low reference voltage 0.7V */
    TOUCH_LVOLT_0V8,      /*!< Low reference voltage 0.8V */
    TOUCH_LVOLT_MAX,
} touch_low_volt_t;

typedef enum {
    TOUCH_HVOLT_ATTEN_1 = 0,  /*!< Attenuation of 1 */
    TOUCH_HVOLT_ATTEN_0,      /*!< Attenuation of 0 */
    TOUCH_HVOLT_ATTEN_MAX,
} touch_volt_atten_t;
```

- **Usage Recommendations**:
  - High Reference Voltage (refh): Choose a higher voltage for greater noise immunity but lower sensitivity, or a lower voltage for higher sensitivity in a less noisy environment.
  - Low Reference Voltage (refl): This sets the lower threshold for touch detection and should be set based on the same considerations as the high reference voltage.
  - Voltage Attenuation (atten): Use attenuation to fine-tune the sensitivity of the touch detection system. Higher attenuation reduces sensitivity.
 
- **Filling**:
  - Filling is performed using `touch_pad_filter_start(uint32_t filter_period_ms)`.
  - This filter utilizes the FreeRTOS timer, which is dispatched from a task with priority 1 by default on CPU 0. Therefore, if some application task with higher priority consumes a significant amount of CPU0 time, the quality of data obtained from this filter may be affected.
  - Additionally, `touch_pad_set_filter_read_cb(filter_cb_t read_cb)` is used, where a new function is created for filling according to the activated touch pins. For example:

```cpp
/**
 * @brief  Callback function to get the filtered value of touch pad
 * @param raw_value Array containing raw touch pad values.
 * @param filtered_value Array containing filtered touch pad values.
 */
void TouchSlider::filter_read_cb(uint16_t *raw_value, uint16_t *filtered_value) {
  for (uint8_t i = 0; i < TOUCH_PAD_MAX; ++i) {
    if (_padEnabled[i]) {                         // Check if the touch pad is enabled
      _padFilteredValue[i] = filtered_value[i];   // Update the filtered value for the enabled touch pad
    }
  }
}
```

#### `int8_t _sliderValue[TOUCH_PAD_MAX]`

- **Description**: This array, as long as the number of touch pins in the slider, stores the slider value for each touch pad. When a pad is touched, its value is set to `0`. If the pad is to the left of the touched pad, its value is set to `-1`. If the pad is to the right of the touched pad, its value is set to `1`. By default, all pads start with a value indicating their relative position to the touch.

- **Initialization**: The slider values are updated continuously as the touch interface is used. The values range from `-1` to `1`, where `0` indicates that the pad is touched, `-1` indicates that the pad is to the left of the touched pad, and `1` indicates that the pad is to the right of the touched pad. The code ensures that if two pads are touched and there are one or more pads between them, these intermediate pads will not be considered for processing a swipe up or swipe down. Therefore, if your device stops responding on certain pads, it is advisable to confirm the calibration to rule out the possibility of an erroneous touch signal being sent.

### Constructors

#### `TouchSlider(gpio_num_t sliderPins[], uint8_t threshold[], uint8_t numSliderPins)`

- **Description**: This constructor initializes a `TouchSlider` object with individual thresholds for each touch pad.
- **Parameters**:
  - `sliderPins`: An array of `gpio_num_t` representing the GPIO pins connected to the slider electrodes.
  - `threshold`: An array of `uint8_t` representing the threshold values to determine touch sensitivity for each pad. Values above these thresholds indicate touch.
  - `numSliderPins`: The number of slider electrodes/pins.
- **Notes**: 
  - Limits the number of slider pins to 10 for ESP32 and 14 for ESP32-S3 to prevent array overflow.
  - Initializes the touch pad peripheral and sets the reference voltage for charging/discharging.

#### `TouchSlider(gpio_num_t sliderPins[], uint8_t threshold, uint8_t numSliderPins)`

- **Description**: This constructor initializes a `TouchSlider` object with a general threshold for all touch pads.
- **Parameters**:
  - `sliderPins`: An array of `gpio_num_t` representing the GPIO pins connected to the slider electrodes.
  - `threshold`: A `uint8_t` value representing the general threshold to determine touch sensitivity. Values above this threshold indicate touch.
  - `numSliderPins`: The number of slider electrodes/pins.
- **Notes**: 
  - Limits the number of slider pins to 10 for ESP32 and 14 for ESP32-S3 to prevent array overflow.
  - Initializes the touch pad peripheral and sets the reference voltage for charging/discharging.

### Initial Configuration

By default, an initial configuration is set when creating the `TouchSlider` object. This initial configuration can be edited in the header file (`TouchSlider.h`):

```cpp
/*********************** LIBRARY OPTIONS **********************/
#define START_WITH_CALIBRATION                // Initialize the calibration when starting the slider, comment this line to disable
#define START_WITH_SWIPE_FINE                 // Enable swipe fine by default, comment this line to disable
#define START_PRINT_SWIPE_STATUS              // Print the swipe status by default, comment this line to disable
#define START_PRINT_SLIDER_TOUCHED            // Print the slider touched by default, comment this line to disable
// #define START_WITH_TOUCH_BUTTONS              // Enable touch buttons by default, comment this line to disable
// #define START_PRINT_TOUCH_BUTTONS             // Enable print touch buttons by default, comment this line to disable
```

### Public Functions
### Enable/Disable Functions

#### Enable/Disable Functions

- `void enableSwipeFine() {_enableSwipeFine = true;};`
  Enables the fine swipe detection feature.

- `void disableSwipeFine() {_enableSwipeFine = false;};`
  Disables the fine swipe detection feature.

- `void enableTouchButtons() {_enableTouchButtons = true;};`
  Enables the touch buttons feature.

- `void disableTouchButtons() {_enableTouchButtons = false;};`
  Disables the touch buttons feature.

### Enable/Disable Print Functions

- `void enablePrintSliderTouched() {_enablePrintSliderTouched = true;};`
  Enables printing when the slider is touched.

- `void disablePrintSliderTouched() {_enablePrintSliderTouched = false;};`
  Disables printing when the slider is touched.

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/56531ab0-d2e4-4557-abae-a691a1926588" alt="Serial Print Swipe Up">
  <br>
  <em>Serial Print Swipe Up</em>
</p>

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/a9c92547-2aaf-4f80-b8ef-74de89d3f47d" alt="Serial Print Swipe Down">
  <br>
  <em>Serial Print Swipe Down</em>
</p>


- `void enablePrintSwipeStatus() {_enablePrintSwipeStatus = true;};`
  Enables printing the swipe status, including fine swipe status.

- `void disablePrintSwipeStatus() {_enablePrintSwipeStatus = false;};`
  Disables printing the swipe status, including fine swipe status.

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/e5b5de23-77df-4473-93aa-1cd599fabfce" alt="Serial Print First Touch Bot">
  <br>
  <em>Serial Print First Touch Bot</em>
</p>

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/575d27f9-27fe-4838-b182-4ccd18fe21ed" alt="Serial Print First Touch Top">
  <br>
  <em>Serial Print First Touch Top</em>
</p>


- `void enablePrintButtonTouched() {_enablePrintButtonTouched = true;};`
  Enables printing the array of buttons touched and the button that was short-pressed.

- `void disablePrintButtonTouched() {_enablePrintButtonTouched = false;};`
  Disables printing the array of buttons touched and the button that was short-pressed.

### Touch Button Functions
These functionalities are basic and primarily used to detect the press of a touch pad separate from the touch slider. They are not intended to replace more complex functions or libraries dedicated solely to button operations, such as double press, short press, long press, or even press duration measurement. Utilize these functions in this library if you need a simple touch button to perform a straightforward action.These functionalities are basic and primarily used to detect the press of a touch pad separate from the touch slider. They are not intended to replace more complex functions or libraries dedicated solely to button operations, such as double press, short press, long press, or even press duration measurement. Utilize these functions in this library if you need a simple touch button to perform a straightforward action.

#### `void addTouchButton(gpio_num_t buttonPin, uint8_t thresholdPercent)`

- **Description**: Adds a touch button to the `TouchSlider` if there is available space and the button is not already in the list of touch buttons or sliders.
- **Parameters**:
  - `buttonPin`: The GPIO pin connected to the touch button.
  - `thresholdPercent`: The threshold percentage for the touch button.
- **Notes**:
  - Checks if there is space available to add more touch buttons.
  - Checks if the button is already in the list of touch buttons or sliders.

#### `void removeTouchButton(gpio_num_t buttonPin)`

- **Description**: Removes a touch button from the `TouchSlider` if it is in the list of touch buttons.
- **Parameters**:
  - `buttonPin`: The GPIO pin connected to the touch button.
- **Notes**:
  - Checks if there are touch buttons to remove.
  - Shifts the remaining buttons in the list one position to the left after removal.

### Start/Stop/Resume Functions

#### `void start()`

- **Description**: Initializes and starts the touch slider by setting up the touch pads and beginning the slider operation.
- **Notes**:
  - Sets the touch threshold for each slider pad based on the configuration.
  - Configures the touch pads for buttons using `_buttonThresholdPercent`.
  - Begins the touch slider operation.
  - This function should be called after all touch buttons are added.

#### `void stop()`

- **Description**: Stops the timer responsible for updating the touch slider.
- **Notes**:
  - Stops the timer if it is running.
  - Detaches the timer, marking that the slider is not currently running.

#### `void resume()`

- **Description**: Resumes the timer for updating the touch slider.
- **Notes**:
  - Attaches the timer if it is not currently running.
  - Marks that the timer is running, resuming the slider operation.

### Calibration Thresholds

#### `void calibrate_thresholds()`

- **Description**: Calibrates the touch pad thresholds by reading the filtered touch values and calculating the thresholds based on a specified percentage.
- **Parameters**: None.
- **Notes**:
  - Iterates over all touch pads and reads the filtered touch value for each enabled touch pad.
  - Calculates and stores the threshold for each touch pad based on a percentage of the touch value.
  - Logs the calibrated threshold for reference.

  ### Getters

#### `int8_t getSwipeStatus()`

- **Description**: Retrieves the swipe status, calculated as the difference between the counts of swipe-down and swipe-up gestures, and resets the swipe counts after retrieval.
- **Returns**: 
  - An `int8_t` value representing the swipe status.
  - Positive values indicate swipe-down gestures.
  - Negative values indicate swipe-up gestures.
  - `0` indicates no swipe.

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/3deb8406-5ad6-4c2e-92e4-4006fb7e913b" alt="SwipeUp">
  <br>
  <em>SwipeUp</em>
</p>
<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/5694b665-06cd-4d10-ae8c-2245c9769ffe" alt="SwipeDown">
  <br>
  <em>SwipeDown</em>
</p>

#### `int8_t getSwipeStatusFine()`

- **Description**: Retrieves the fine swipe status, calculated as the difference between the counts of fine swipe-down and fine swipe-up gestures, and resets the swipe counts after retrieval.
- **Returns**: 
  - An `int8_t` value representing the fine swipe status.
  - Positive values indicate fine swipe-down gestures.
  - Negative values indicate fine swipe-up gestures.
  - `0` indicates no fine swipe.
- **Notes**: 
  - If fine swipe is disabled, it returns `0` and prints a message to enable fine swipe using `enableSwipeFine()`.

<p align="center">
  <img src="https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/2be7a1b3-af98-4152-99bd-f215ecb79216" alt="SwipeFine">
  <br>
  <em>SwipeFine</em>
</p>

#### `gpio_num_t getButtonShortPress()`

- **Description**: Retrieves the GPIO pin of the button that was short-pressed and resets the flag.
- **Returns**: 
  - The `gpio_num_t` of the button that was short-pressed.
  - `GPIO_NUM_NC` if no button was short-pressed.
- **Notes**: 
  - If touch buttons are disabled, it returns `GPIO_NUM_NC` and prints a message to enable touch buttons using `enableTouchButtons()`.

#### `bool getSliderRunning()`

- **Description**: Retrieves the running status of the slider.
- **Returns**: 
  - `true` if the slider is running.
  - `false` if the slider is not running.

#### `bool isTouchButtonPressed(gpio_num_t buttonPin)`

- **Description**: Checks if a touch button is pressed.
- **Parameters**:
  - `buttonPin`: The `gpio_num_t` of the button.
- **Returns**: 
  - `true` if the button pin is pressed.
  - `false` if the button pin is not in the list of touch buttons or is not pressed.

#### `bool isTouchSliderPressed(gpio_num_t sliderPin)`

- **Description**: Checks if a touch slider pin is pressed.
- **Parameters**:
  - `sliderPin`: The `gpio_num_t` of the slider.
- **Returns**: 
  - `true` if the slider pin is touched.
  - `false` if the slider pin is not in the list of touch sliders or is not touched.

#### `void getSliderTouched(bool sliderTouched[], uint8_t numSliderPins)`

- **Description**: Retrieves the slider touched status and stores it in the provided array.
- **Parameters**:
  - `sliderTouched`: The array to store the slider touched status.
  - `numSliderPins`: The number of slider pins.


