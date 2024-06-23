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

size_t numSlidersPins = sizeof(arraySlidersPins) / sizeof(arraySlidersPins[0]);   // Number of sliders
TouchSlider touchSlider(arraySlidersPins, THRESHOLD_SLIDER, numSlidersPins);      // TouchSlider object
Ticker _sliderTicker;                                                             // Ticker object for updating touch slider
const uint8_t SLIDER_INTERVAL = 200;                                              // Interval for updating touch slider
enum { DOWNFILE, UPFILE };                                                        // Enum for determining slider direction
enum { BACKOPTION, SELECTOPTION };                                                // Enum for determining selecting options

// Define the menu structure
typedef struct MenuItem {
  const char *name;
  struct MenuItem *parent;
  struct MenuItem *children;
  int childCount;
} MenuItem;

// Define menu items
MenuItem sensorsMenu[] = {
  {"Light", NULL, NULL, 0},
  {"Humidity", NULL, NULL, 0},
  {"Battery", NULL, NULL, 0}
};

MenuItem displayMenu[] = {
  {"Brightness", NULL, NULL, 0},
  {"TurnOn", NULL, NULL, 0}
};

MenuItem alarmMenu[] = {
  {"TurnOn", NULL, NULL, 0}
};

MenuItem mainMenu[] = {
  {"Sensors", NULL, sensorsMenu, 3},
  {"Volume", NULL, NULL, 0},
  {"Display", NULL, displayMenu, 2},
  {"Alarm", NULL, alarmMenu, 1}
};

// Set parents
// Function to set parent structure recursively
void setParents(MenuItem *menu, int size, MenuItem *parent) {
  for (int i = 0; i < size; i++) {
    menu[i].parent = parent;
    if (menu[i].children != NULL) {
      setParents(menu[i].children, menu[i].childCount, &menu[i]);
    }
  }
}

// Initialize parents
void initializeMenu() {
  setParents(mainMenu, 4, NULL);
}

// Global variables for menu navigation
MenuItem *currentMenu = mainMenu;
int currentMenuSize = 4;
int currentIndex = 0;

void displayMenuConsole() {                                 // Function to display the current menu
  Serial.printf("<------------------------------>\n");    // Print the current menu
  for (int i = 0; i < currentMenuSize; i++) {
    if (i == currentIndex) {
      Serial.printf("> %s\n", currentMenu[i].name);
    } else {
      Serial.printf("  %s\n", currentMenu[i].name);
    }
  }
  Serial.printf("<------------------------------>\n");
}

void navigateMenu(bool direction) {                                             // Function to navigate the menu
  if (direction) {                                                            // If direction is true
    // Navigate down
    currentIndex = (currentIndex + 1) % currentMenuSize;                    // Wrap around if necessary
  } else {                                                                    // If direction is false
    // Navigate up
    currentIndex = (currentIndex - 1 + currentMenuSize) % currentMenuSize;  // Wrap around if necessary
  }
  displayMenuConsole();                                                         // Display the current menu
}


// Function to go back to the parent directory
// Returns true if successfully moved back, false if already at the root
bool backToParent() {
  if (currentMenu->parent != NULL) {
    currentMenu = currentMenu->parent; // Move to the parent menu
    currentIndex = 0; // Reset index to start at the parent's menu

    // Update parents if necessary
    if (currentMenu->parent == NULL) {
      // If we are at the root menu (mainMenu), reset parent structure from scratch
      setParents(mainMenu, 4, NULL);
      currentMenu = mainMenu; // Move to the parent menu
      currentMenuSize = 4; // Update currentMenuSize to match mainMenu size
    } else {
      // Ensure parents are correctly configured
      MenuItem *parent = currentMenu->parent;
      setParents(parent->children, parent->childCount, parent);
      currentMenuSize = parent->childCount; // Update currentMenuSize to parent's child count
    }

    currentIndex = 0; // Reset index to start at the parent's menu
    displayMenuConsole();
    return true;
  } else {
    Serial.printf("Already at the root.\n");
    return false;
  }
}

// Function to select a directory
// Returns true if selection was successful, false if not (e.g., if no children)
bool selectDirectory(bool select) {     // Function to select a directory
  if(!select) {
    backToParent();                     // Go back to the parent directory
    return true;
  }

  if (currentIndex >= currentMenuSize || currentIndex < 0) {      // Check if the selected index is valid
    Serial.printf("Invalid index.\n");
    return false;
  }
  
  MenuItem *selectedItem = &currentMenu[currentIndex];            // Get the selected item
  
  // Check if the selected item has children
  if (selectedItem->children != NULL && selectedItem->childCount > 0) {
    // Update current menu to the selected item's children
    currentMenu = selectedItem->children;
    currentMenuSize = selectedItem->childCount;
    currentIndex = 0; // Reset index to start at the first item of the new menu
    displayMenuConsole();           // Display the current menu
    return true;
  } else {
    // Handle case where the selected directory is a final directory (no children)
    // Here, you can return a unique number to identify the final directory
    // For simplicity, return the index as a unique identifier
    Serial.printf("Selected: %s\n", currentMenu[currentIndex].name);
    displayMenuConsole();               // Display the current menu
    return false; // No children to select
  }
}


void updateTouchSlider() {                                 // Update touch slider
  // Serial.println("Updating touch slider");              // Logging
  int8_t swipeStatus = touchSlider.getSwipeStatus();       // Get swipe status
  if (swipeStatus != 0) {
    for (int8_t i = 0; i < abs(swipeStatus); ++i) {        // Convert swipe status to absolute value to determine count of iterations
      if (swipeStatus > 0) 
        navigateMenu(DOWNFILE);                          // This function will the swipe status in the direction of increase
      else 
        navigateMenu(UPFILE);                          // This function will the swipe status in the direction of decrease
    }
  }

  int8_t swipeStatusFine = touchSlider.getSwipeStatusFine();      // Get swipe status fine
  if (swipeStatusFine != 0) {
    for (int8_t i = 0; i < abs(swipeStatusFine); ++i) {           // Convert swipe status fine to absolute value to determine count of iterations
      if (swipeStatusFine > 0) 
        backToParent();
      else 
        selectDirectory(SELECTOPTION);                             // This function will the only touch the last touch pad on the slider
    }
  }
}

void setup() {
  Serial.begin(115200);                     // Begin serial communication

  touchSlider.enableSwipeFine();            // Enable swipe fine
  touchSlider.disableTouchButtons();        // Disable touch buttons
  touchSlider.disablePrintSliderTouched();   // Disable print slider touched
  touchSlider.disablePrintSwipeStatus();      // Enable print swipe status

  touchSlider.start();                          // Start touch slider
  Serial.println("TouchSlider initialized");    // Logging
  _sliderTicker.attach_ms(SLIDER_INTERVAL, updateTouchSlider);  // Attach ticker to update touch slider

  initializeMenu();
  displayMenuConsole();             
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