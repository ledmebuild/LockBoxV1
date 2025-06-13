#include "encoder.h"
#include <Arduino.h>

// Statische Variablen initialisieren Button und Position
volatile bool Encoder::buttonState=false;
volatile int Encoder::position=0;
volatile unsigned long Encoder::lastButtonPress = 0;
volatile unsigned long Encoder::_lastIncReadTime = micros(); 
volatile unsigned long Encoder::_lastDecReadTime = micros();  
volatile int Encoder::_pauseLength = 25000;
volatile int Encoder::_fastIncrement = 10;
volatile int Encoder::counter = 0;
volatile const unsigned long Encoder::debounceDelay = 100; // 100ms Entprellzeit für Button

// Constructor
Encoder::Encoder() {
    // TODO: Initialize encoder pins and variables
    pinMode(ENC_A, INPUT_PULLUP);
    pinMode(ENC_B, INPUT_PULLUP);
    pinMode(ENC_PUSH, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ENC_A), Encoder::read_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_B), Encoder::read_encoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_PUSH), Encoder::read_button, RISING);
}

// Destructor
Encoder::~Encoder() {
    // TODO: Cleanup encoder resources
}

// Read button state and update buttonState variable
void Encoder::read_button(){
    unsigned long currentMillis = millis();
    if (currentMillis - lastButtonPress > debounceDelay) {
        if(digitalRead(ENC_PUSH)==0){
            buttonState = true;
        }
        lastButtonPress = currentMillis;
    }
}


// Read encoder state and update position variable
void Encoder::read_encoder(){
      // Encoder interrupt routine for both pins. Updates position
      // if they are valid and have rotated a full indent
 
      static uint8_t old_AB = 3;  // Lookup table index
      static int8_t encval = 0;   // Encoder value  
      static const int8_t enc_states[]  = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0}; // Lookup table

      old_AB <<=2;  // Remember previous state

      if (digitalRead(ENC_A)) old_AB |= 0x02; // Add current state of pin A
      if (digitalRead(ENC_B)) old_AB |= 0x01; // Add current state of pin B
  
      encval += enc_states[( old_AB & 0x0f )];

      // Update position if encoder has rotated a full indent, that is at least 4 steps
      if( encval > 3 ) {        // Four steps forward
        int changevalue = 1;
        if((micros() - _lastIncReadTime) < _pauseLength) {
          changevalue = _fastIncrement * changevalue; 
        }
        _lastIncReadTime = micros();
        position = position + changevalue;              // Update position
        encval = 0;
      }
      else if( encval < -3 ) {        // Four steps backward
        int changevalue = -1;
        if((micros() - _lastDecReadTime) < _pauseLength) {
          changevalue = _fastIncrement * changevalue; 
        }
        _lastDecReadTime = micros();
        position = position + changevalue;              // Update position
        encval = 0;
      }
}


// Get current encoder position
int Encoder::getPosition() {
    // TODO: Read and return current encoder position
    return position;
}

// Get button state and return it
bool Encoder::getbuttonState() {
    // TODO: Read button state from hardware and update buttonState
    return buttonState;
}

// Set button state to given value
void Encoder::setbuttonState(bool state) {
    buttonState = state;
}

// Set encoder position
void Encoder::setPosition(int pos) {
    // TODO: Set the encoder position to given value
    position = pos;
}