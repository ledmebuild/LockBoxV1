#ifndef DISPLAY_H
#define DISPLAY_H

#include "SH1106Wire.h" // Include header here
#include <Arduino.h>

class Display {
private:
  //Display library instance
  SH1106Wire dis; // Make dis a private member
  // Breite und Höhe des Displays
  int screenWidth = 128;
  int screenHeight = 64;
    
public:
    // Constructor
    Display();
    
    // Destructor
    ~Display();
    
    // Public methods
    void clear();
    void showmenulist(const std::string& optionA, const std::string& optionB, int selectedOption);
    void showtime(short hours, short minutes);
    void showheading(const std::string& heading);
    void showfootnote(const std::string& footnote);
    void showlocking();
    void showunlocking();
    void showselectgame(int pos_traget, int pos_player, int num_rounds, int num_max_rounds);
    void showputbackphone();
    void showlistfootnote(const std::string& optionA, const std::string& optionB, int selectedOption);
    
};

#endif
