#include <Arduino.h>
#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
private:
    // Private member variables if needed
    
public:
    // Constructor
    Display();
    
    // Destructor
    ~Display();
    
    // Public methods
    void clear();
    void showmenulist(const std::string& optionA, const std::string& optionB, int selectedOption);
    void showtime(short hours, short minutes, short seconds);
    void showheading(const std::string& heading);
    void showfootnote(const std::string& footnote);
    void showlocking();
    void showunlocking();
    void showselectgame(int pos_traget, int pos_player, int num_rounds, int num_max_rounds);
    void showputbackphone();
    void showlistfootnote(const std::string& optionA, const std::string& optionB, int selectedOption);
    
    // Additional utility methods
    void init();
};

#endif
