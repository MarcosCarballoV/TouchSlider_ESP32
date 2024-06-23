# TouchSlider Library for ESP32
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

## Features

- **Sensitivity Adjustment:** Configure the sensitivity of the touch pads to detect various touch intensities.
- **Accurate Detection:** Reliable and precise touch detection across the touch slider.
- **Timer-Based Updates:** Uses timers for efficient touch data updates and readings.
- **Pause and Resume:** Ability to pause and resume touch detection.
- **Edge Detection:** Detects touches on specific pads (edges) to perform different functions apart from sliding.


## Authors

- [@MarcosCarballoV](https://github.com/MarcosCarballoV)


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
// #define START_WITH_TOUCH_BUTTONS              // Disable touch buttons by default, comment this line to enable
```

### Public Functions

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

- `void enablePrintSwipeStatus() {_enablePrintSwipeStatus = true;};`
  Enables printing the swipe status, including fine swipe status.

- `void disablePrintSwipeStatus() {_enablePrintSwipeStatus = false;};`
  Disables printing the swipe status, including fine swipe status.

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

  

![ezgif-6-d856cbd844](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/449c4ea8-9ca7-4ee6-bcf4-e3a0c1acb749)

![ezgif-1-a3cf8d0dc4](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/2be7a1b3-af98-4152-99bd-f215ecb79216)

![ezgif-1-b48388dd4f](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/3deb8406-5ad6-4c2e-92e4-4006fb7e913b)

![ezgif-1-6feeaae81e](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/5694b665-06cd-4d10-ae8c-2245c9769ffe)

![ezgif-6-544cf5d29b](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/e5b5de23-77df-4473-93aa-1cd599fabfce)

![ezgif-6-c68d5f4a55](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/575d27f9-27fe-4838-b182-4ccd18fe21ed)

![ezgif-6-c09614a6ef](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/56531ab0-d2e4-4557-abae-a691a1926588)

![ezgif-6-7ddadf4589](https://github.com/MarcosCarballoV/TouchSlider_TouchButton_Functionalities/assets/139102752/a9c92547-2aaf-4f80-b8ef-74de89d3f47d)


## Screenshots

![App Screenshot](hhttps://drive.google.com/file/d/1sY6Vhcrc-_1MmUfvtkOrQRgmqNd5wrY2/view?usp=sharing)
