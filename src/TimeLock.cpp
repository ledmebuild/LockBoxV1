#include "display.h"
#include "encoder.h"
#include "lock.h"
#include "light.h"

void unlockgame();

void timelock(){
    Display display;
    Encoder encoder;
    Light light; // Create an instance of the Light class
    Lock lock;
    // Set color and brightness for the light
    light.setColor({255, 255, 0}); // Set the color of the light yellow
    light.setBrightness(255); // Set the brightness to 100%
    light.turnOn(); // Turn on the light

    short hours_lock = 0; // Initialize hours_lock
    short minutes_lock = 0; // Initialize minutes_lock
    short seconds_lock = 0; // Initialize seconds_lock
    encoder.setPosition(0); // Reset encoder position
    int past_position = encoder.getPosition(); // Get the current position of the encoder
    display.headline_time_footnote("Time Lock", encoder.getPosition(), minutes_lock, seconds_lock, 0, "set hours");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            display.headline_time_footnote("Time Lock", encoder.getPosition(), minutes_lock, seconds_lock, 0, "set hours");
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 99) {
                encoder.setPosition(99); // Limit to 99 hours_lock
            }
        }
    }
    hours_lock = encoder.getPosition(); // Get the selected hours_lock
    encoder.setPosition(0); // Reset encoder position for minutes_lock
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for minutes_lock
    display.headline_time_footnote("Time Lock", hours_lock, encoder.getPosition(), seconds_lock, 1, "set minutes");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("Time Lock", hours_lock, encoder.getPosition(), seconds_lock, 1, "set minutes");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 minutes_lock
            }
        }
    }
    minutes_lock = encoder.getPosition(); // Get the selected minutes_lock
    encoder.setPosition(0); // Reset encoder position for seconds_lock
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for seconds_lock
    display.headline_time_footnote("Time Lock", hours_lock, minutes_lock, encoder.getPosition(), 2, "set seconds");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("Time Lock", hours_lock, minutes_lock, encoder.getPosition(), 2, "set seconds");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 seconds_lock
            }
        }
    }
    seconds_lock = encoder.getPosition(); // Get the selected seconds_lock
    encoder.setPosition(0); // Reset encoder position for confirmation
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for confirmation
    display.showheading("Time selected:"); // Show Time Lock heading
    String info_text = "Lock: " + String(hours_lock) + "h " + String(minutes_lock) + "m " + String(seconds_lock) + "s"; // Create info text
    display.info(info_text.c_str()); // Show the selected lock time
    display.showlistfootnote("continue", "cancel", 0); // Show options to continue or cancel
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() % 2 == 0) {
                display.showlistfootnote("continue", "cancel", 0); // Highlight continue
            } else {
                display.showlistfootnote("continue", "cancel", 1); // Highlight cancel
            }
        }
    }
    if(encoder.getPosition() % 2 == 0){
        //continue with the time lock
    }
    else{
        ESP.restart(); // Restart the ESP32 if Cancel is selected
    }
    display.clear(); // Clear the display
    encoder.setPosition(0); // Reset encoder position for confirmation
    display.putbackphone_listfootnote("Start Time Lock", "Cancel", 0); // Show options to start or cancel
    past_position = encoder.getPosition(); // Reset past position for confirmation
    encoder.setbuttonState(false);
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() % 2 == 0) {
                display.putbackphone_listfootnote("Start Time Lock", "Cancel", 0); // Highlight Start Pomodoro
            } else {
                display.putbackphone_listfootnote("Start Time Lock", "Cancel", 1); // Highlight Cancel
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
    lock.lock(); // Lock the lock
    light.turnOff(); // Turn off the light after locking
    unsigned long totalTime_lock = (hours_lock * 3600 + minutes_lock * 60 + seconds_lock) * 1000; // Convert hours_lock, minutes_lock, and seconds_lock to milliseconds
    unsigned long startTime = millis(); // Get the current time in milliseconds
    unsigned long elapsedTime = 0; // Initialize elapsed time
    display.clear(); // Clear the display
    display.headline_time_footnote("Time Lock", hours_lock, minutes_lock, seconds_lock, -1, "press for emergency"); // Show initial time
    short past_hours_lock = hours_lock; // Store past hours_lock for comparison
    short past_minutes_lock = minutes_lock; // Store past minutes_lock for comparison
    short past_seconds_lock = seconds_lock; // Store past seconds_lock for comparison
    bool display_on = true; // Flag to control display updates
    int time_till_sleep = 10000; // Time in milliseconds to turn off the display
    unsigned long last_sleep_time = millis(); // Initialize last display update time
    while(millis() - startTime < totalTime_lock) { // Loop until the total time is reached
        elapsedTime = millis() - startTime; // Calculate elapsed time
        //calculate remaining hours_lock
        short remaininghours_lock = (totalTime_lock - elapsedTime) / 3600000; // Calculate remaining hours_lock
        short remainingminutes_lock = (totalTime_lock - elapsedTime) / 60000; // Calculate remaining minutes_lock
        short remainingseconds_lock = ((totalTime_lock - elapsedTime) % 60000) / 1000; // Calculate remaining seconds_lock
        if(remaininghours_lock != past_hours_lock || remainingminutes_lock != past_minutes_lock || remainingseconds_lock != past_seconds_lock && display_on == true) { // Check if time has changed
            past_hours_lock = remaininghours_lock; // Update past hours_lock
            past_minutes_lock = remainingminutes_lock; // Update past minutes_lock
            past_seconds_lock = remainingseconds_lock; // Update past seconds_lock
            display.showtime(remaininghours_lock, remainingminutes_lock, remainingseconds_lock, -1); // Show updated time on the display
        }
        if(millis() - last_sleep_time > time_till_sleep) { // Check if it's time to turn off the display
            display_on = false; // Set display_on to false
            display.clear(); // Clear the display
        }
        if(encoder.getbuttonState() == true && display_on == false) { // Check if the button is pressed and display is off
            display_on = true; // Set display_on to true
            last_sleep_time = millis(); // Update last display update time
            display.headline_time_footnote("Time Lock", remaininghours_lock, remainingminutes_lock, remainingseconds_lock, -1, "press for emergency"); // Show initial time
            encoder.setbuttonState(false); // Reset button state
        }
        if(encoder.getbuttonState() == true && display_on == true) { // Check if the button is pressed
            display.clear(); // Clear the display
            encoder.setbuttonState(false); // Reset button state
            unlockgame(); // Call the unlockgame function
            display.clear(); // Clear the display
            display.showunlocking(); // Show unlocking screen
            light.setColor({0, 255, 0}); // Set the color to green
            light.setBrightness(255); // Set the brightness to 100%
            light.turnOn(); // Turn on the light to indicate completion
            lock.unlock(); // Unlock the lock
            ESP.restart(); // Restart the ESP32
        }
    }
    encoder.setbuttonState(false); // Reset button state
    while(display_on == false){
        if(encoder.getbuttonState() == true) { // Check if the button is pressed
            display_on = true; // Set display_on to true
        }
    }
    display.clear(); // Clear the display
    display.showunlocking(); // Show unlocking screen
    light.setColor({0, 255, 0}); // Set the color to green
    light.setBrightness(255); // Set the brightness to 100%
    light.turnOn(); // Turn on the light to indicate completion
    lock.unlock(); // Unlock the lock
    ESP.restart(); // Restart the ESP32
}