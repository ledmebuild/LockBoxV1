#include <Arduino.h>
#include "display.h"
// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.flush(); // diese Zeile ist vom Surface
  int result = myFunction(2, 3);
  Serial.println("Result of myFunction(2, 3): ");
  Serial.println(result);
  Serial.println("Setup complete.");
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}