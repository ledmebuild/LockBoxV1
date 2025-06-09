#include "display.h"
#include <Wire.h>
#include "SH1106Wire.h"

// Constructor
Display::Display(): dis(0x3c, SDA, SCL) { // Initialize display with I2C address and pins
    Serial.println("Display constructor called");
    
    // TODO: Initialize display settings
    dis.init();
    dis.flipScreenVertically();
    dis.setFont(ArialMT_Plain_24); // Große Schrift setzen
      String text = "LockBoxV1!";

      // Breite und Höhe des Displays
      int screenWidth = 128;
      int screenHeight = 64;

      // Textbreite berechnen
      int textWidth = dis.getStringWidth(text);

      // Position berechnen (zentriert)
      int x = (screenWidth - textWidth) / 2;
      int y = (screenHeight - 24) / 2; // 24 ist die Schriftgröße in Pixeln
    dis.drawString(x, y, text);
    dis.display();
    delay(1000);
    
}

// Destructor
Display::~Display() {
    // TODO: Cleanup display resources
}

// Clear the display
void Display::clear() {
    // TODO: Clear display content
    dis.clear();
}

// Show menu list with two options and highlight selected one
void Display::showmenulist(const std::string& optionA, const std::string& optionB, int selectedOption) {
    // TODO: Display menu with options A and B, highlight selectedOption
}

// Display current time
void Display::showtime(short hours, short minutes) {
    dis.setFont(ArialMT_Plain_24);

    // Helper function to draw a digit with background
    auto drawDigit = [&](int digit, int x, int y) {
        String digitStr = String(digit);
        int digitWidth = dis.getStringWidth(digitStr);
        int rectWidth = 20; // Width of the rectangle
        int rectHeight = 28; // Height of the rectangle
        int padding = (rectWidth - digitWidth) / 2; // Calculate padding to center the digit

        // Draw the background rectangle
        dis.drawRect(x, y, rectWidth, rectHeight);

        // Draw the digit centered in the rectangle
        dis.drawString(x + padding, y, digitStr);
    };

    // Extract digits for hours
    int hourTens = hours / 10;
    int hourOnes = hours % 10;

    // Extract digits for minutes
    int minuteTens = minutes / 10;
    int minuteOnes = minutes % 10;
    
    // Draw hours
    drawDigit(hourTens, 20, 22); // Adjusted X and Y
    drawDigit(hourOnes, 42, 22); // Adjusted X and Y

    // Draw colon
    dis.drawString(66, 22, ":");

    // Draw minutes
    drawDigit(minuteTens, 74, 22); // Adjusted X and Y
    drawDigit(minuteOnes, 96, 22); // Adjusted X and Y

    dis.display();
    
}

// Show heading text
void Display::showheading(const std::string& heading) {
    // TODO: Display heading at top of screen
}

// Show footnote text
void Display::showfootnote(const std::string& footnote) {
    // TODO: Display footnote at bottom of screen
}

// Show locking animation/message
void Display::showlocking() {
    // TODO: Display locking status or animation
}

// Show unlocking animation/message
void Display::showunlocking() {
    // TODO: Display unlocking status or animation
}

// Show game selection interface
void Display::showselectgame(int pos_target, int pos_player, int num_rounds, int num_max_rounds) {
    // TODO: Display game interface with positions and round info
}

// Show put back phone message
void Display::showputbackphone() {
    // TODO: Display message to put phone back in lock box
}

// Show list footnote with options
void Display::showlistfootnote(const std::string& optionA, const std::string& optionB, int selectedOption) {
    // TODO: Display footnote with navigation options
}