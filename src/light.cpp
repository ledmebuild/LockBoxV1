#include "light.h"

// Constructor
Light::Light() {
    // TODO: Initialize light settings and hardware
}

// Destructor
Light::~Light() {
    // TODO: Cleanup light resources
}

// Get the current RGB color values
RGB Light::getColor() {
    // TODO: Return current RGB color values
    return color;
}

// Get the current brightness level
int Light::getBrightness() {
    // TODO: Return current brightness level
    return brightness;
}

// Set the RGB color values
void Light::setColor(RGB color) {
    // TODO: Set RGB color values to hardware
    this->color = color;
}

// Set the brightness level (0-255)
void Light::setBrightness(int brightness) {
    // TODO: Set brightness level to hardware
    this->brightness = brightness;
}

// Turn on the light
void Light::turnOn() {
    // TODO: Turn on the light with current color and brightness
}

// Turn off the light
void Light::turnOff() {
    // TODO: Turn off the light
}