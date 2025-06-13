#include "display.h"
#include <Wire.h>
#include "SH1106Wire.h"

// Constructor
Display::Display(): dis(0x3c, SDA, SCL) { // Initialize display with I2C address and pins
    Serial.println("Display constructor called");
    
    // TODO: Initialize display settings
    dis.init();
    dis.flipScreenVertically();    
}

void Display::intro(){
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
    // Clear the menu area
    dis.setColor(BLACK);
    dis.fillRect(0, 22, 128, 50); // Clear middle area (y between 22 and 50)
    dis.setColor(WHITE);
    
    // Set font for menu items
    dis.setFont(ArialMT_Plain_16);
    
    // Calculate positions
    int yPos = 22; // Starting y position within the specified range
    int xIndent = 10; // Left margin
    int xOption = 20; // Position where the option text starts
    
    // Draw option A with or without selection marker
    if (selectedOption == 0) {
        dis.drawString(xIndent, yPos, ">");
        dis.drawString(xOption, yPos, String(optionA.c_str()));
    } else {
        dis.drawString(xOption, yPos, String(optionA.c_str()));
    }
    
    // Draw option B with or without selection marker
    if (selectedOption == 1) {
        dis.drawString(xIndent, yPos + 16, ">");
        dis.drawString(xOption, yPos + 16, String(optionB.c_str()));
    } else {
        dis.drawString(xOption, yPos + 16, String(optionB.c_str()));
    }
    
    // Update the display
    dis.display();
}

// Display current time
void Display::showtime(short hours, short minutes) {
    dis.setFont(ArialMT_Plain_24);
    
    // Zuererst Berreich löschen
    dis.setColor(BLACK);
    dis.fillRect(0, 22, 128, 28); // Clear the entire display area
    dis.display(); // Update the display to show the cleared area
    dis.setColor(WHITE); // Set color for the digits
    
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
    // Display heading at top of screen
    dis.setFont(ArialMT_Plain_16);
    dis.setColor(BLACK);
    dis.fillRect(0, 0, 128, 18); // Clear the top area for the heading
    dis.setColor(WHITE);
    
    // Center the heading text
    int textWidth = dis.getStringWidth(heading.c_str());
    int x = (128 - textWidth) / 2;
    
    // Draw the heading text
    dis.drawString(x, 0, String(heading.c_str()));
    dis.display();
  
}

// Show footnote text
void Display::showfootnote(const std::string& footnote) {
    // Display footnote at bottom of screen
    dis.setFont(ArialMT_Plain_10); // Small font for footnote
    dis.setColor(BLACK);
    dis.fillRect(0, 52, 128, 12); // Clear the bottom area for the footnote
    dis.setColor(WHITE);
    
    // Center the footnote text
    int textWidth = dis.getStringWidth(footnote.c_str());
    int x = (128 - textWidth) / 2;
    
    // Draw the footnote text
    dis.drawString(x, 52, String(footnote.c_str()));
    dis.display();
}

// Show locking animation/message
void Display::showlocking() {
    // TODO: Display locking status or animation
    dis.drawXbm(0, 0, 128, 64, locked_bitmap); // assuming your bitmap is 128x64
    dis.display();
    showfootnote("Locking...");
}


// Show unlocking animation/message
void Display::showunlocking() {
    // TODO: Display unlocking status or animation
    dis.drawXbm(0, 0, 128, 64, unlocked_bitmap); // assuming your bitmap is 128x64
    dis.display();
    showfootnote("Unlocking...");
}

// Show game selection interface
void Display::showunlockgame(int pos_target, int pos_player, int num_rounds, int num_max_rounds) {
    // Clear the game area
    dis.setColor(BLACK);
    dis.fillRect(0, 22, 128, 64); // Clear the game area (y between 22 and 50)
    dis.setColor(WHITE);
    
    // Draw rectangular outline for the game area
    dis.drawRect(0, 22, 128, 28); // Rectangle from (0,22) to (128,50)
    
    // Draw dotted line for target position (ensuring it stays within bounds)
    int target_x = constrain(pos_target, 0, 127); // Ensure target is within bounds
    for (int y = 23; y < 49; y += 2) { // Draw dotted vertical line
        dis.setPixel(target_x, y); // Draw pixel at target position
    }
    
    // Draw solid line for player position (ensuring it stays within bounds)
    int player_x = constrain(pos_player, 0, 127); // Ensure player is within bounds
    dis.drawVerticalLine(player_x, 23, 26); // Draw solid vertical line
    
    // Display round information at the bottom of the game area
    dis.setFont(ArialMT_Plain_10);
    String roundText = "Round: " + String(num_rounds) + "/" + String(num_max_rounds);
    dis.drawString(5, 52, roundText);
    
    // Update display
    dis.display();
}

// Show put back phone message
void Display::showputbackphone() {
    // TODO: Display message to put phone back in lock box
    dis.drawXbm(0, 0, 128, 64, phone_box_bitmap); // assuming your bitmap is 128x64
    dis.display();
}

// Show list footnote with options
void Display::showlistfootnote(const std::string& optionA, const std::string& optionB, int selectedOption) {
    dis.setFont(ArialMT_Plain_10); // Small font for footnote
    dis.setColor(BLACK);
    dis.fillRect(0, 52, 128, 12); // Clear the bottom area for the footnote
    dis.setColor(WHITE);

    std::string combinedText;
    if(selectedOption == 0) {
        combinedText = ">" + optionA + "  " + "  " + optionB;
    } else {
        combinedText = "  " + optionA + "  " + ">" + optionB;
    }
    // Center the footnote text
    int textWidth = dis.getStringWidth(combinedText.c_str());
    int x = (128 - textWidth) / 2;
    
    // Draw the footnote text
    dis.drawString(x, 52, String(combinedText.c_str()));
    dis.display();
}

// Show heading, time, and footnote together
void Display::headline_time_footnote(const std::string& headline, short hours, short minutes, const std::string& footnote) {
    showheading(headline);
    showtime(hours, minutes);
    showfootnote(footnote);
}

// Show put back phone with list footnote
void Display::putbackphone_listfootnote(const std::string& optionA, const std::string& optionB, int selectedOption) {
    showputbackphone();
    showlistfootnote(optionA, optionB, selectedOption);
}