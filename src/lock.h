#ifndef LOCK_H
#define LOCK_H

#include <ESP32Servo.h>

class Lock {
private:
    // Private member variables if needed
    bool locked; // State of the lock (locked or unlocked)
    Servo myservo;
    int pos;
public:
    // Constructor
    Lock();

    // Destructor
    ~Lock();

    // Public methods
    void lock(); // Lock the lock
    void unlock(); // Unlock the lock
    int getPosition(); // Get the current position of the servo
    bool getLocked(); // Check if the lock is currently locked
};

#endif