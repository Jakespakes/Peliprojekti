#include "Arduino.h"
#include "sounds.h"
#include <ezBuzzer.h> // Lisätään ezBuzzer jotta voidaan soittaa melodiaa helposti loopissa

const int buzzerPin = 7;

extern bool playMelody;
static const int buttonNotes[4] = {262, 294, 330, 349};
static const int successNotes[3] = {880, 1175, 1568};
static const int failureNotes[3] = {440, 330, 220};

ezBuzzer buzzer(buzzerPin, BUZZER_TYPE_PASSIVE, HIGH);

static const int song[] = {
  NOTE_C4, NOTE_F4, NOTE_DS4, NOTE_GS4,
  NOTE_G4, NOTE_C4, NOTE_CS4, NOTE_C4,
};

// Melodia on mitä toistetaan pelinä pelatessa kunnes peli päättyy

const int noteDurations[] = {
  2, 4, 4, 3,
  2, 6, 4, 3,
};
// Nuottien pituudet, että melodia kuulostaa musiikilta

// Melodian pituus määritellään melodian koko jaettuna melodian ekalla nuotilla
// Tämä tehdään jotta voidaan käydä koko melodia läpi yksinkertaisella loopilla

void initSound() {
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

void melody() {
  int noteLength = sizeof(noteDurations) / sizeof(int);

  buzzer.loop();

  if (playMelody) {
    if (buzzer.getState() == BUZZER_IDLE) {
      buzzer.playMelody(song, noteDurations, noteLength);
    }
  }
}