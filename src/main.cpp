#include <Arduino.h>
#include "display.h"
#include "encoder.h"
#include "light.h"
#include "lock.h"
// Create instances of the Hardware
//
Display* display = nullptr;// Pointer to Display instance
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setup complete.");
  
  //------------ Display Test---------------------
  display = new Display(); // Initialize the display
  for(int i = 0; i < 10; i++) {
    display->clear(); // Clear the display
    display->showtime(19, i); // Display the time
    delay(1000); // Wait for 1 second
  }
  //------------Ende Display Test-----------------
}

void loop() {
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
  }
  //-------------Ende Encoder Test-----------------

  
}