#include <ESP32Servo.h>
#include "lock.h"

#define PIN_SG90 17 // Pin for the servo motor

// Constructor
Lock::Lock() {
  sg90.setPeriodHertz(50); // PWM frequency for SG90
  sg90.attach(PIN_SG90, 500, 2400); // Minimum and maximum pulse width (in µs) to go from 0° to 180
}

// Destructor
Lock::~Lock() {
    // TODO: Cleanup lock resources
}

// Lock the lock
void Lock::lock() {
    locked = true;
    pos = 90;

    for (int pos = 0; pos <= 180; pos += 1) {
        sg90.write(pos);
        delay(10);
    }
    /*
    for (pos = 0; pos < 90; pos += 10) { // goes from 0 degrees to 90 degrees
        // in steps of 1 degree
        setServoAngle(pos);    // tell servo to go to position in variable 'pos'
    }*/
}

// Unlock the lock
void Lock::unlock() {
    locked = false;
    pos = 0;
    // Rotation from 180° to 0
    for (int pos = 180; pos >= 0; pos -= 1) {
        sg90.write(pos);
        delay(10);
    }
}

// Check if the lock is currently locked
bool Lock::getLocked() {
    // TODO: Return current lock state
    return locked;
}

int Lock::getPosition() {
    return pos; 
}