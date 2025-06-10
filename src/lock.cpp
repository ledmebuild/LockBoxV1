#include "lock.h"

#define servoPin 17 // Pin for the servo motor
// Constructor
Lock::Lock() {
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    myservo.setPeriodHertz(50);    // standard 50 hz servo
    myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object
}

// Destructor
Lock::~Lock() {
    // TODO: Cleanup lock resources
}

// Lock the lock
void Lock::lock() {
    // TODO: Engage locking mechanism
    locked = true;
    for (pos = 0; pos < 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);    // tell servo to go to position in variable 'pos'
        delay(15);             // waits 15ms for the servo to reach the position
    }
}

// Unlock the lock
void Lock::unlock() {
    // TODO: Disengage locking mechanism
    locked = false;
    for (pos = 180; pos > 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);    // tell servo to go to position in variable 'pos'
        delay(15);             // waits 15ms for the servo to reach the position
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
