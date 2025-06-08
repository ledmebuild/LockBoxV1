#ifndef ENCODER_H
#define ENCODER_H

class Encoder {
private:
    // Private member variables if needed
    int position; // Current position of the encoder
    bool buttonState; // State of the button (pressed or not)
public:
    // Constructor
    Encoder();

    // Destructor
    ~Encoder();

    // Public methods
    int getPosition();
    int setbuttonState(); // Returns the state of the button (pressed or not)
    void setPosition(int position);
};

#endif