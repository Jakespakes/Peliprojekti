#include "Arduino.h"
#include "sounds.h"

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define REST     0

const int buzzerPin = 7;

static const int buttonNotes[4] = {262, 294, 330, 349};
static const int successNotes[3] = {880, 1175, 1568};
static const int failureNotes[3] = {440, 330, 220};
static const int song[] = {
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4,

  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_C4, NOTE_C4
};
// Melodia on mitä toistetaan pelinä pelatessa kunnes peli päättyy
// Pitäisi olla Beethoven - Ode to Joy

const int noteDurations[] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 2,

  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 2
};
// Nuottien pituudet, että melodia kuulostaa musiikilta

const int melodyLength = sizeof(melody) / sizeof(melody[0]);
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
  for (int i = 0; i < melodyLength; i++) {
    int noteDuration = 1000 / noteDurations[i];

    tone(buzzerPin, song[i], noteDuration);

    // Tehään pieni paussi niin nuotit ei kuulosta yhdeltä mössöltä
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(buzzerPin);
  }
}