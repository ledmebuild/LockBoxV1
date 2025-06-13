#include "display.h"
#include "encoder.h"
#include "lock.h"
void pomodoro(){
    Display display;
    Encoder encoder;
    encoder.setPosition(0); // Reset encoder position
    display.showheading("Pomodoro Timer");
    int past_position = encoder.getPosition(); // Get the current position of the encoder
    display.headline_time_footnote("set hours", encoder.getPosition(), 0, "press to select");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            display.headline_time_footnote("set hours", encoder.getPosition(), 0, "press to select");
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 99) {
                encoder.setPosition(99); // Limit to 99 hours
            }
        }
    }
    display.clear(); // Clear the display
    delay(1000); // Short delay to show the selection
    display.headline_time_footnote("set hours", encoder.getPosition(), 0, "press to select");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            display.headline_time_footnote("set minutes", encoder.getPosition(), 0, "press to select");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 minutes
            }
        }
    }
    display.clear(); // Clear the display
    display.showlocking(); // Show locking screen
    Lock lock; // Create an instance of the Lock class
    lock.lock(); // Lock the lock
    delay(2000); // Simulate locking time
    display.clear(); // Clear the display
    display.showunlocking(); // Show unlocking screen
    lock.unlock(); // Unlock the lock

}