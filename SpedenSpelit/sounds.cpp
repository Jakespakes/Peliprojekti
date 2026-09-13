#include "Arduino.h"
#include "sounds.h"


const int buzzerPin = 7;

static const int buttonNotes[4] = {262, 294, 330, 349};
static const int successNotes[3] = {880, 1175, 1568};
static const int failureNotes[3] = {440, 330, 220};

void initializeSound() {
  pinMode(buzzerPin, OUTPUT);
}

void buttonSound(int x)  {
  for (int i = 0;i<5;i++)  {
    if (x - 2 == i) {
      tone(buzzerPin, buttonNotes[i], 100);
      delay(100);
    }
  }
  noTone(buzzerPin);
}

void successSound() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, successNotes[i], 120);
    delay(140);
  }
  noTone(buzzerPin);
}

void failureSound() {
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, failureNotes[i], 200);
    delay(140);
  }
  noTone(buzzerPin);
}

