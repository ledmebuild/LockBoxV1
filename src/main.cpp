#include <Arduino.h>
#include "display.h"
#include "encoder.h"
#include "light.h"
#include "lock.h"
#include "pomodoro.h"
// Create instances of the Hardware
//
Display* display = nullptr;// Pointer to Display instance
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup complete.");
  
  //------------ Display Test---------------------
  /*
  display = new Display(); // Initialize the display
  
  display->showheading("Headline"); // Show heading
  display->showlistfootnote("OptionA", "OptionB", 1); // Show list footnote with options
  display->clear();
  display->showlocking(); // Show locking animation/message
  delay(2000); // Wait for 2 seconds
  display->clear(); // Clear the display
  display->showunlocking(); // Show unlocking animation/message
  delay(2000); // Wait for 2 seconds
  display->clear(); // Clear the display
  display->showputbackphone(); // Show put back phone message
  delay(2000); // Wait for 2 seconds
  display->clear(); // Clear the display
  display->showheading("Menu"); // Show heading
  display->showmenulist("Pomodoro", "Time Lock", 0); // Show list footnote with options
  delay(2000); // Wait for 2 seconds
  display->clear(); // Clear the display
  display->showheading("Unlock Game"); // Show heading
  

  delay(2000); // Wait for 2 seconds
  /*
  //display->showfootnote("footnote"); // Show footnote
  for(int i = 0; i < 10; i++) {
    display->showtime(19, i); // Display the time
    delay(500); // Wait for 1 second
  }
  */

  //------------Ende Display Test-----------------
/*
  //------------ Light Test---------------------
  
  Light light; // Create an instance of the Light class
  RGB color = {255, 0, 0}; // Set the color to red
  light.setColor(color); // Set the color of the light
  Serial.print("Red value: ");
  Serial.println(light.getColor().red); // Print the red value to serial
  light.setBrightness(128); // Set the brightness to 50%
  Serial.print("Brightness: ");
  Serial.println(light.getBrightness()); // Print the brightness to serial
  light.turnOn(); // Turn on the light
  delay(2000); // Wait for 2 seconds
  light.turnOff(); // Turn off the light
  delay(2000); // Wait for 2 seconds
  color = {0, 255, 0}; // Set the color to green
  light.setColor(color); // Set the color of the light
  light.setBrightness(255); // Set the brightness to 100%
  light.turnOn(); // Turn on the light
  delay(2000); // Wait for 2 seconds
  light.turnOff(); // Turn off the light
  delay(2000); // Wait for 2 seconds
  
  //------------ Ende Light Test----------------
    
  //------------ Lock Test---------------------
  Lock lock; // Create an instance of the Lock class
  lock.lock(); // Lock the lock
  Serial.print("getPosition: ");
  Serial.println(lock.getPosition()); // Print the current position of the lock
  Serial.print("getLocked: ");
  Serial.println(lock.getLocked()); // Print the current lock state
  delay(2000); // Wait for 2 seconds
  lock.unlock(); // Unlock the lock
  Serial.print("getPosition after unlock: ");
  Serial.println(lock.getPosition()); // Print the current position of the lock after unlocking
  Serial.print("getLocked after unlock: ");
  Serial.println(lock.getLocked()); // Print the current lock state after unlocking
  delay(2000); // Wait for 2 seconds

  //------------ Ende Lock Test----------------
  */

  // Main Menu
  Encoder encoder;
  Light light; // Create an instance of the Light class
  Display display; // Create an instance of the Display class
  light.setColor({0, 255, 0}); // Set the color of the light to green
  light.setBrightness(255); // Set the brightness to 100%
  light.turnOn(); // Turn on the light
  display.intro(); // Show the introduction screen
  display.showheading("Main Menu"); // Show main menu heading
  int past_position = encoder.getPosition(); // Get the current position of the encoder
  while(encoder.getbuttonState() == false) { // Wait for button press
    if(encoder.getPosition() %2 == 0){
      display.showmenulist("Pomodoro", "Time Lock", 0); // Show Pomodoro and Time Lock options
    }else{
      display.showmenulist("Pomodoro", "Time Lock", 1); // Show Time Lock and Pomodoro options
    }
  }
  encoder.setbuttonState(false); // Reset button state
  if(encoder.getPosition() %2 == 0){
    pomodoro(); // Call the pomodoro function if even position
  }else{
    // Call the time lock function if odd position
  }

}

void loop() {
  /*
  //------------ Encoder Test---------------------
  Encoder encoder; // Create an instance of the Encoder class
  if(encoder.getbuttonState()) {
    Serial.println("Button is pressed");
    encoder.setbuttonState(false); // Set the button state to false
    encoder.setPosition(0); // Reset the encoder position
  }

  static int lastCounter = 0;
  int currentPosition = encoder.getPosition(); // Get the current position of the encoder
  // If count has changed print the new value to serial
  if(currentPosition != lastCounter){
    Serial.println(currentPosition);
    lastCounter = currentPosition;
    if(currentPosition%2 == 0){
      display->showunlockgame(10, currentPosition, 3, 5); // Show game selection interface
    }else{
      display->showunlockgame(10, currentPosition, 3, 5); // Show game selection interface
    }
  }
    */
  //-------------Ende Encoder Test-----------------

  
}