#include "Arduino.h"
#include "leds.h"

void initializeLeds() {
  for (int i = 2;i<=5;i++) {
    pinMode(A0 + i, OUTPUT);
  }
}


void setLed(byte ledNumber) {
  clearAllLeds();
  int pin = A0 + ledNumber + 2;
  digitalWrite(pin, HIGH);
}

static void setLed2(byte ledNumber) {
  int pin = A0 + ledNumber + 2;
  digitalWrite(pin, HIGH);
}



void clearAllLeds() {
for (int i = 0;i<=3;i++)  {
  int pin = A0 + i + 2;
  digitalWrite(pin, LOW);
  }
}