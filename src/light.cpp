#include "light.h"

#define PIN_NEO_PIXEL  16  // The ESP32 pin GPIO16 connected to NeoPixel
#define NUM_PIXELS     1  // The number of LEDs (pixels) on NeoPixel

// Constructor
Light::Light():NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800) {
    NeoPixel.begin();  // initialize NeoPixel strip object (REQUIRED)
    NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
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
    NeoPixel.setBrightness(brightness);  // Set brightness level (0-255)
    NeoPixel.setPixelColor(0, NeoPixel.Color(color.red, color.green, color.blue));  // Erste Variable für Pixelpositon, da ich nur einen habe hier 0, it only takes effect if pixels.show() is called
    NeoPixel.show();
}

// Turn off the light
void Light::turnOff() {
    // TODO: Turn off the light
    NeoPixel.clear();  // Set all pixel colors to 'off'. It only takes effect if pixels.show() is called
    NeoPixel.show();
}