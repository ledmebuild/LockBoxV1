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
void Display::showtime(short hours, short minutes, short seconds, short marked = -1) {
    dis.setFont(ArialMT_Plain_16); // Smaller font for better fit
    
    // Clear the area
    dis.setColor(BLACK);
    dis.fillRect(0, 22, 128, 28); // Clear the display area
    dis.display();
    dis.setColor(WHITE);
    
    // Helper function to draw a digit with background
    auto drawDigit = [&](int digit, int x, int y, bool isDashed) {
        String digitStr = String(digit);
        int digitWidth = dis.getStringWidth(digitStr);
        int rectWidth = 14; // Smaller rectangle width
        int rectHeight = 20; // Smaller rectangle height
        int padding = (rectWidth - digitWidth) / 2;

        if (isDashed) {
            // Draw dashed rectangle
            for (int i = 0; i < rectWidth; i += 2) {
                dis.setPixel(x + i, y);                     // Top horizontal line
                dis.setPixel(x + i, y + rectHeight - 1);    // Bottom horizontal line
            }
            for (int i = 0; i < rectHeight; i += 2) {
                dis.setPixel(x, y + i);                     // Left vertical line
                dis.setPixel(x + rectWidth - 1, y + i);     // Right vertical line
            }
        } else {
            // Draw solid rectangle
            dis.drawRect(x, y, rectWidth, rectHeight);
        }

        // Draw the digit centered in the rectangle
        dis.drawString(x + padding, y + 1, digitStr); // +1 for vertical centering
    };

    // Extract digits for hours, minutes, seconds
    int hourTens = hours / 10;
    int hourOnes = hours % 10;
    int minuteTens = minutes / 10;
    int minuteOnes = minutes % 10;
    int secondTens = seconds / 10;
    int secondOnes = seconds % 10;
    
    // Calculate starting position to center the entire time display
    int totalWidth = 114; // Total width of all elements
    int startX = (128 - totalWidth) / 2;
    
    // Draw hours with dashed rectangles if marked = 0
    bool hoursAreDashed = (marked == 0);
    drawDigit(hourTens, startX, 26, hoursAreDashed);
    drawDigit(hourOnes, startX + 16, 26, hoursAreDashed);

    // Draw first colon
    dis.drawString(startX + 32, 26, ":");

    // Draw minutes with dashed rectangles if marked = 1
    bool minutesAreDashed = (marked == 1);
    drawDigit(minuteTens, startX + 40, 26, minutesAreDashed);
    drawDigit(minuteOnes, startX + 56, 26, minutesAreDashed);
    
    // Draw second colon
    dis.drawString(startX + 72, 26, ":");
    
    // Draw seconds with dashed rectangles if marked = 2
    bool secondsAreDashed = (marked == 2);
    drawDigit(secondTens, startX + 80, 26, secondsAreDashed);
    drawDigit(secondOnes, startX + 96, 26, secondsAreDashed);

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
    dis.clear(); // Clear the display before showing locking
    dis.display();
    dis.drawXbm(0, 0, 128, 64, locked_bitmap); // assuming your bitmap is 128x64
    dis.display();
    showfootnote("Locking...");
}


// Show unlocking animation/message
void Display::showunlocking() {
    // TODO: Display unlocking status or animation
    dis.clear(); // Clear the display before showing unlocking
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
void Display::headline_time_footnote(const std::string& headline, short hours, short minutes, short seconds, short marked, const std::string& footnote) {
    showheading(headline);
    showtime(hours, minutes, seconds, marked);
    showfootnote(footnote);
}

// Show put back phone with list footnote
void Display::putbackphone_listfootnote(const std::string& optionA, const std::string& optionB, int selectedOption) {
    showputbackphone();
    showlistfootnote(optionA, optionB, selectedOption);
}

void Display::info(const std::string& infoText) {
    // Display information text
    dis.setFont(ArialMT_Plain_10);
    dis.setColor(BLACK);
    dis.fillRect(0, 22, 128, 42); // Clear the middle area for the info text
    dis.setColor(WHITE);
    
    // Center the info text
    int textWidth = dis.getStringWidth(infoText.c_str());
    int x = (128 - textWidth) / 2;
    
    // Draw the info text
    dis.drawString(x, 22, String(infoText.c_str()));
    dis.display();
}   