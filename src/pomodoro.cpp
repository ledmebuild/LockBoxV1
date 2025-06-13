#include "display.h"
#include "encoder.h"
#include "lock.h"
#include "light.h"

void pomodoro(){
    Display display;
    Encoder encoder;
    Light light; // Create an instance of the Light class
    //set color and brightness for the light
    light.setColor({255, 255, 0}); // Set the color of the light yellow
    light.setBrightness(255); // Set the brightness to 100%
    light.turnOn(); // Turn on the light
    short hours = 0; // Initialize hours
    short minutes = 0; // Initialize minutes
    short seconds = 0; // Initialize seconds
    encoder.setPosition(0); // Reset encoder position
    display.showheading("Pomodoro Timer");
    int past_position = encoder.getPosition(); // Get the current position of the encoder
    display.headline_time_footnote("set lock interval", encoder.getPosition(), minutes, seconds, 0, "set hours");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            display.headline_time_footnote("set lock interval", encoder.getPosition(), minutes, seconds, 0, "set hours");
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 99) {
                encoder.setPosition(99); // Limit to 99 hours
            }
        }
    }
    hours = encoder.getPosition(); // Get the selected hours
    encoder.setPosition(0); // Reset encoder position for minutes
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for minutes
    display.headline_time_footnote("set lock interval", hours, minutes, seconds, 1, "set minutes");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set lock interval", hours, encoder.getPosition(), seconds, 1, "set minutes");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 minutes
            }
        }
    }
    minutes = encoder.getPosition(); // Get the selected minutes
    encoder.setPosition(0); // Reset encoder position for confirmation
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for confirmation
    display.headline_time_footnote("set lock interval", hours, minutes, encoder.getPosition(), 2, "set seconds");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set lock interval", hours, minutes, encoder.getPosition(), 2, "set seconds");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 seconds
            }
        }
    }
    seconds = encoder.getPosition(); // Get the selected seconds
    display.clear(); // Clear the display
    display.putbackphone_listfootnote("Start Pomodoro", "Cancel", 0); // Show options to start or cancel
    past_position = encoder.getPosition(); // Reset past position for confirmation
    encoder.setbuttonState(false);
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() % 2 == 0) {
                display.putbackphone_listfootnote("Start Pomodoro", "Cancel", 0); // Highlight Start Pomodoro
            } else {
                display.putbackphone_listfootnote("Start Pomodoro", "Cancel", 1); // Highlight Cancel
            }
        }
    }
    if(encoder.getPosition() % 2== 0){
        //continue with the pomodoro timer
    }else{
        ESP.restart(); // Restart the ESP32 if Cancel is selected
    }
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    light.setColor({255, 0, 0}); // Set the color of the light red
    light.setBrightness(255); // Set the brightness to 100%
    light.turnOn(); // Turn on the light
    display.showlocking(); // Show locking screen
    Lock lock; // Create an instance of the Lock class
    lock.lock(); // Lock the lock
    light.turnOff(); // Turn off the light after locking
    //calculate total time in milliseconds
    unsigned long totalTime = (hours * 3600 + minutes * 60 + seconds) * 1000; // Convert hours, minutes, and seconds to milliseconds
    unsigned long startTime = millis(); // Get the current time in milliseconds
    unsigned long elapsedTime = 0; // Initialize elapsed time
    display.clear(); // Clear the display
    display.headline_time_footnote("Pomodoro Timer", hours, minutes, seconds, -1, "press for emergency"); // Show initial time
    short past_hours = hours; // Store past hours for comparison
    short past_minutes = minutes; // Store past minutes for comparison
    short past_seconds = seconds; // Store past seconds for comparison
    while(millis() - startTime < totalTime) { // Loop until the total time is reached
        elapsedTime = millis() - startTime; // Calculate elapsed time
        //calculate remaining hours
        short remainingHours = (totalTime - elapsedTime) / 3600000; // Calculate remaining hours
        short remainingMinutes = (totalTime - elapsedTime) / 60000; // Calculate remaining minutes
        short remainingSeconds = ((totalTime - elapsedTime) % 60000) / 1000; // Calculate remaining seconds
        if(remainingHours != past_hours || remainingMinutes != past_minutes || remainingSeconds != past_seconds) { // Check if time has changed
            past_hours = remainingHours; // Update past hours
            past_minutes = remainingMinutes; // Update past minutes
            past_seconds = remainingSeconds; // Update past seconds
            display.showtime(remainingHours, remainingMinutes, remainingSeconds, -1); // Show updated time on the display
        }
    }
    
    display.clear(); // Clear the display
    light.setColor({0, 255, 0}); // Set the color to green
    light.setBrightness(255); // Set the brightness to 100%
    light.turnOn(); // Turn on the light to indicate completion
    display.showunlocking(); // Show unlocking screen
    lock.unlock(); // Unlock the lock
    ESP.restart(); // Restart the ESP32 after completion
}