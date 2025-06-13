#include "lock.h"

#define servoPin 17 // Pin for the servo motor
// Constructor
Lock::Lock() {
    pinMode(servoPin, OUTPUT);
}

// Destructor
Lock::~Lock() {
    // TODO: Cleanup lock resources
}

// Lock the lock
void Lock::lock() {
    // TODO: Engage locking mechanism
    locked = true;
    pos = 90; // Reset position to 0 degrees
    setServoAngle(pos);
    /*
    for (pos = 0; pos < 90; pos += 10) { // goes from 0 degrees to 90 degrees
        // in steps of 1 degree
        setServoAngle(pos);    // tell servo to go to position in variable 'pos'
    }*/
}

// Unlock the lock
void Lock::unlock() {
    // TODO: Disengage locking mechanism
    locked = false;
    pos = 0; // Reset position to 0 degrees
    setServoAngle(pos);
    /*
    for (pos = 90; pos > 0; pos -= 10) { // goes from 90 degrees to 0 degrees
        setServoAngle(pos);    // tell servo to go to position in variable 'pos'
    }*/
}

// Check if the lock is currently locked
bool Lock::getLocked() {
    // TODO: Return current lock state
    return locked;
}

int Lock::getPosition() {
    return pos; 
}

void Lock::setServoAngle(int angle) {
  // Convert angle (0-180) to pulse width (500-2500 µs)
  int pulseWidth = map(angle, 0, 180, 500, 2500);
  
  // Manual PWM generation - each cycle is 20ms (50Hz)
  for (int i = 0; i < 20; i++) {  // Send several pulses to ensure servo moves
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servoPin, LOW);
    
    // Calculate remaining time in the 20ms cycle
    delayMicroseconds(20000 - pulseWidth);
  }
}
