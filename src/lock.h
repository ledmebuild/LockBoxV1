#ifndef LOCK_H
#define LOCK_H

class Lock {
private:
    // Private member variables if needed
    bool locked; // State of the lock (locked or unlocked)
public:
    // Constructor
    Lock();

    // Destructor
    ~Lock();

    // Public methods
    void lock(); // Lock the lock
    void unlock(); // Unlock the lock
    bool getLocked(); // Check if the lock is currently locked
};

#endif