#ifndef LIGHT_H
#define LIGHT_H

#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library
struct RGB {
    int red;   // Red component (0-255)
    int green; // Green component (0-255)
    int blue;  // Blue component (0-255)
};

class Light {
private:
    RGB color; // RGB values for the light
    int brightness; // Brightness level of the light (0-255)
    Adafruit_NeoPixel NeoPixel;
public:
    // Constructor
    Light();

    // Destructor
    ~Light();

    // Public methods
    RGB getColor(); // Get the current RGB color values
    void setColor(RGB color); // Set the RGB color values
    int getBrightness(); // Get the current brightness level
    void setBrightness(int brightness); // Set the brightness level (0-255)
    void turnOn(); // Turn on the light
    void turnOff(); // Turn off the light
};
#endif