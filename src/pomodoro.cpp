#include "display.h"
#include "encoder.h"
#include "lock.h"
#include "light.h"

void unlockgame();

void pomodoro(){
    Display display;
    Encoder encoder;
    Light light; // Create an instance of the Light class
    //set color and brightness for the light
    light.setColor({255, 255, 0}); // Set the color of the light yellow
    light.setBrightness(255); // Set the brightness to 100%
    light.turnOn(); // Turn on the light
    short hours_interval= 0; // Initialize hours_interval
    short minutes_interval = 0; // Initialize minutes_interval
    short seconds_interval = 0; // Initialize seconds_interval
    encoder.setPosition(0); // Reset encoder position
    display.showheading("Pomodoro Timer");
    int past_position = encoder.getPosition(); // Get the current position of the encoder
    display.headline_time_footnote("set lock interval", encoder.getPosition(), minutes_interval, seconds_interval, 0, "set hours");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            display.headline_time_footnote("set lock interval", encoder.getPosition(), minutes_interval, seconds_interval, 0, "set hours");
            past_position = encoder.getPosition(); // Update past position
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 99) {
                encoder.setPosition(99); // Limit to 99 hours_interval
            }
        }
    }
    hours_interval = encoder.getPosition(); // Get the selected hours_interval
    encoder.setPosition(0); // Reset encoder position for minutes_interval
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for minutes_interval
    display.headline_time_footnote("set lock interval", hours_interval, minutes_interval, seconds_interval, 1, "set minutes");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set lock interval", hours_interval, encoder.getPosition(), seconds_interval, 1, "set minutes");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 minutes_interval
            }
        }
    }
    minutes_interval = encoder.getPosition(); // Get the selected minutes_interval
    encoder.setPosition(0); // Reset encoder position for confirmation
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for confirmation
    display.headline_time_footnote("set lock interval", hours_interval, minutes_interval, encoder.getPosition(), 2, "set seconds");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set lock interval", hours_interval, minutes_interval, encoder.getPosition(), 2, "set seconds");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 seconds_interval
            }
        }
    }
    seconds_interval = encoder.getPosition(); // Get the selected seconds_interval
    encoder.setPosition(0); // Reset encoder position for confirmation
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for confirmation
    short hours_pause = 0; // Initialize hours_pause
    short minutes_pause = 0; // Initialize minutes_pause
    short seconds_pause = 0; // Initialize seconds_pause
    display.headline_time_footnote("set pause", hours_pause, minutes_pause, seconds_pause, 0, "set hours");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set pause", encoder.getPosition(), minutes_pause, seconds_pause, 0, "set hours");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 99) {
                encoder.setPosition(99); // Limit to 99 hours_pause
            }
        }
    }
    hours_pause = encoder.getPosition(); // Get the selected hours_pause
    encoder.setPosition(0); // Reset encoder position for minutes_pause
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for minutes_pause
    display.headline_time_footnote("set pause", hours_pause, encoder.getPosition(), seconds_pause, 1, "set minutes");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set pause", hours_pause, encoder.getPosition(), seconds_pause, 1, "set minutes");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 minutes_pause
            }
        }
    }
    minutes_pause = encoder.getPosition(); // Get the selected minutes_pause
    encoder.setPosition(0); // Reset encoder position for seconds_pause
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    past_position = encoder.getPosition(); // Reset past position for seconds_pause
    display.headline_time_footnote("set pause", hours_pause, minutes_pause, encoder.getPosition(), 2, "set seconds");
    while(encoder.getbuttonState() == false) { // Wait for button press
        if(past_position != encoder.getPosition()){
            past_position = encoder.getPosition(); // Update past position
            display.headline_time_footnote("set pause", hours_pause, minutes_pause, encoder.getPosition(), 2, "set seconds");
            if(encoder.getPosition() < 0) {
                encoder.setPosition(0); // Prevent negative position
            } else if(encoder.getPosition() > 59) {
                encoder.setPosition(59); // Limit to 59 seconds_pause
            }
        }
    }
    seconds_pause = encoder.getPosition(); // Get the selected seconds_pause
    encoder.setPosition(0); // Reset encoder position for confirmation
    display.clear(); // Clear the display
    encoder.setbuttonState(false);
    display.showheading("Time seleted:"); // Show Pomodoro Timer heading
    String info_text = "Interval: " + String(hours_interval) + "h " + String(minutes_interval) + "m " + String(seconds_interval) + "s\nPause: " + String(hours_pause) + "h " + String(minutes_pause) + "m " + String(seconds_pause) + "s"; // Create info text
    display.info(info_text.c_str()); // Show the selected interval and pause time
    display.showlistfootnote("continue", "cancel", 0); // Show options to continue or cancel
    past_position = encoder.getPosition(); // Reset past position for confirmation
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
    encoder.setbuttonState(false); // Reset button state
    if(encoder.getPosition() % 2 == 0){
        //continue with the pomodoro timer
    } else {
        ESP.restart(); // Restart the ESP32 if Cancel is selected
    }
    while(true){
        display.clear(); // Clear the display
        encoder.setPosition(0); // Reset encoder position for confirmation
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
        //calculate total time in milliseconds_interval
        unsigned long totalTime_interval = (hours_interval * 3600 + minutes_interval * 60 + seconds_interval) * 1000; // Convert hours_interval, minutes_interval, and seconds_interval to milliseconds_interval
        unsigned long startTime = millis(); // Get the current time in milliseconds_interval
        unsigned long elapsedTime = 0; // Initialize elapsed time
        display.clear(); // Clear the display
        display.headline_time_footnote("Pomodoro Timer", hours_interval, minutes_interval, seconds_interval, -1, "press for emergency"); // Show initial time
        short past_hours_interval = hours_interval; // Store past hours_interval for comparison
        short past_minutes_interval = minutes_interval; // Store past minutes_interval for comparison
        short past_seconds_interval = seconds_interval; // Store past seconds_interval for comparison
        while(millis() - startTime < totalTime_interval) { // Loop until the total time is reached
            elapsedTime = millis() - startTime; // Calculate elapsed time
            //calculate remaining hours_interval
            short remaininghours_interval = (totalTime_interval - elapsedTime) / 3600000; // Calculate remaining hours_interval
            short remainingminutes_interval = (totalTime_interval - elapsedTime) / 60000; // Calculate remaining minutes_interval
            short remainingseconds_interval = ((totalTime_interval - elapsedTime) % 60000) / 1000; // Calculate remaining seconds_interval
            if(remaininghours_interval != past_hours_interval || remainingminutes_interval != past_minutes_interval || remainingseconds_interval != past_seconds_interval) { // Check if time has changed
                past_hours_interval = remaininghours_interval; // Update past hours_interval
                past_minutes_interval = remainingminutes_interval; // Update past minutes_interval
                past_seconds_interval = remainingseconds_interval; // Update past seconds_interval
                display.showtime(remaininghours_interval, remainingminutes_interval, remainingseconds_interval, -1); // Show updated time on the display
            }
            if(encoder.getbuttonState() == true) { // Check if the button is pressed
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
        
        display.clear(); // Clear the display
        light.setColor({0, 255, 0}); // Set the color to green
        light.setBrightness(255); // Set the brightness to 100%
        light.turnOn(); // Turn on the light to indicate completion
        display.showunlocking(); // Show unlocking screen
        lock.unlock(); // Unlock the lock

        unsigned long totalTime_pause = (hours_pause * 3600 + minutes_pause * 60 + seconds_pause) * 1000; // Convert hours_pause, minutes_pause, and seconds_pause to milliseconds
        startTime = millis(); // Get the current time in milliseconds
        elapsedTime = 0; // Initialize elapsed time
        display.clear(); // Clear the display
        display.headline_time_footnote("Pause Timer", hours_pause, minutes_pause, seconds_pause, -1, "press to go back to menu"); // Show initial time
        short past_hours_pause = hours_pause; // Store past hours_pause for comparison
        short past_minutes_pause = minutes_pause; // Store past minutes_pause for comparison
        short past_seconds_pause = seconds_pause; // Store past seconds_pause for comparison
        while(millis() - startTime < totalTime_pause) { // Loop until the total time is reached
            elapsedTime = millis() - startTime; // Calculate elapsed time
            //calculate remaining hours_interval
            short remaininghours_pause = (totalTime_pause - elapsedTime) / 3600000; // Calculate remaining hours_pause
            short remainingminutes_pause = (totalTime_pause - elapsedTime) / 60000; // Calculate remaining minutes_pause
            short remainingseconds_pause = ((totalTime_pause - elapsedTime) % 60000) / 1000; // Calculate remaining seconds_pause
            if(remaininghours_pause != past_hours_pause || remainingminutes_pause != past_minutes_pause || remainingseconds_pause != past_seconds_pause) { // Check if time has changed
                past_hours_pause = remaininghours_pause; // Update past hours_pause
                past_minutes_pause = remainingminutes_pause; // Update past minutes_pause
                past_seconds_pause = remainingseconds_pause; // Update past seconds_pause
                display.showtime(remaininghours_pause, remainingminutes_pause, remainingseconds_pause, -1); // Show updated time on the display
            }
            if(encoder.getbuttonState() == true) { // Check if the button is pressed
                encoder.setbuttonState(false); // Reset button state
                display.clear(); // Clear the display
                ESP.restart(); // Restart the ESP32
            }
        }
    }
}

