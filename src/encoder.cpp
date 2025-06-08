#include "encoder.h"

// Constructor
Encoder::Encoder() {
    // TODO: Initialize encoder pins and variables
}

// Destructor
Encoder::~Encoder() {
    // TODO: Cleanup encoder resources
}

// Get current encoder position
int Encoder::getPosition() {
    // TODO: Read and return current encoder position
    return position;
}

// Get button state and return it
int Encoder::setbuttonState() {
    // TODO: Read button state from hardware and update buttonState
    return buttonState;
}

// Set encoder position
void Encoder::setPosition(int position) {
    // TODO: Set the encoder position to given value
    this->position = position;
}