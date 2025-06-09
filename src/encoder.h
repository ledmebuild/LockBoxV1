#ifndef ENCODER_H
#define ENCODER_H

// Define rotary encoder pins
#define ENC_A A0
#define ENC_B A1
#define ENC_PUSH A2

class Encoder {
private:
    // Private member variables if needed
    static volatile int position; // Current position of the encoder
    static volatile bool buttonState; // State of the button (pressed or not)

    // Variables for calculating the position
    static volatile unsigned long _lastIncReadTime; 
    static volatile unsigned long _lastDecReadTime;  
    static volatile int _pauseLength;
    static volatile int _fastIncrement;
    static volatile int counter;
    // Variables for the button state on the encoder
    static volatile unsigned long lastButtonPress;
    static volatile const unsigned long debounceDelay; // 50ms Entprellzeit für Button
    // Private methods
    //Methoden zum Lesen des Encoders und des Buttons vom Encoder
    static void read_button();
    static void read_encoder();
public:
    // Constructor
    Encoder();

    // Destructor
    ~Encoder();

    // Public methods
    int getPosition();
    void setPosition(int position);
    bool getbuttonState();
    void setbuttonState(bool state);
    
};

#endif