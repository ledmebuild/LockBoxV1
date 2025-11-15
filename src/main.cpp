#include <Arduino.h>
#include "display.h"
#include "encoder.h"
#include "light.h"
#include "lock.h"
#include "pomodoro.h"
#include "timelock.h"
// Create instances of the Hardware
//
Display* display = nullptr;// Pointer to Display instance
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
    */
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
  /*
  // Main Menu
  Encoder encoder;
  Light light; // Create an instance of the Light class
  Display display; // Create an instance of the Display class
  Lock lock; // Create an instance of the Lock class
  lock.unlock(); // Unlock the lock at the start
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
    timelock();
  }

  */

}

void loop() {}



void unlockgame(){
    Display display; // Create an instance of the Display class
    Encoder encoder; // Create an instance of the Encoder class
    display.showheading("Select Target"); // Show the heading for the unlock game
    int pos_target = random(0, 126); // Generate a new target position randomly
    encoder.setPosition(0); // Reset encoder position
    encoder.setbuttonState(false); // Reset button state
    int pos_player = encoder.getPosition(); // Player's current position
    int past_position = pos_player; // Store the previous position of the player
    int num_rounds = 0; // Number of rounds in the game
    int num_max_rounds = 5; // Maximum number of rounds in the game
    
    display.showunlockgame(pos_target, pos_player, num_rounds, num_max_rounds); // Show the game interface
    while(num_rounds <= num_max_rounds) { // Loop until the maximum number of rounds is reached
        if(past_position != encoder.getPosition()) { // Check if the position has changed
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 127) {
                encoder.setPosition(127); // Limit to 127 for the game
            }
            past_position = encoder.getPosition(); // Update the previous position
            pos_player = encoder.getPosition(); // Get the current position of the player
            display.showunlockgame(pos_target, pos_player, num_rounds, num_max_rounds); // Update the game interface
            encoder.setbuttonState(false); // Reset button state after processing
        }
        if((encoder.getPosition() == pos_target) && (encoder.getbuttonState() == true)) { // Check if the player has reached the target position and pressed the button
                encoder.setbuttonState(false); // Reset button state
                num_rounds++; // Increment the number of rounds if the player reaches the target position
                pos_target = random(0, 126); // Generate a new target position randomly
                encoder.setPosition(0); // Reset the player's position
                display.showunlockgame(pos_target, encoder.getPosition(), num_rounds, num_max_rounds); // Update the game interface
        }
    }    
    display.clear(); // Clear the display after the game ends
}