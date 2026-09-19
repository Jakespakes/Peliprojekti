#include "Arduino.h"
#include "leds.h"

void initializeLeds() {
  for (int i = 2;i<=5;i++) { // Laitetaan pinnit A2-A5 output tilaan että saadaan virta ledeihin
    pinMode(A0 + i, OUTPUT);
  }
  clearAllLeds();
}

void setLed(byte ledNumber) { // Sammuttaa ledit ja sytyttää käsketyn ledin.
  clearAllLeds();
  int pin = A0 + ledNumber + 2;
  digitalWrite(pin, HIGH);
}

static void setLed2(byte ledNumber) { // Sama kuin setLed, muttei sammuta kaikkia ledejä alussa
  int pin = A0 + ledNumber + 2;
  digitalWrite(pin, HIGH);
}

void setAllLeds() {       // Sytyttää jokaisen ledin
  for (int i = 0;i<=3;i++)  {
    int pin = A0 + i + 2;
    digitalWrite(pin, HIGH);
  }
}

void clearAllLeds() { // Sammuttaa jokaisen ledin
  for (int i = 0;i<=3;i++) {
    int pin = A0 + i + 2;
    digitalWrite(pin, LOW);
  }
}

/* Show toimintojen alkeelliset versiot, non blocking ajastus työn alla..(jos tarvii?)*/

void show1()  {               // show1 eli tämä esittää binäärit 1-15 ledeillä
  for (int i = 0;i<=15;i++)  {
    clearAllLeds();
    for (int j = 0;j<4;j++) {
      if (i & (1 << j)) {
        setLed2(j);
      }
    }
    delay(1000);
  }
  clearAllLeds();
}

void show2(int rounds)  { // show2 eli nopeutuva 1-2-3-4...1-2-3.4.. Tämän ajastuksiin tulee vielä säätöä.
  int show2Delay = rounds * 35;
  for (int i = 0;i<=rounds;i++) {
    for (int j = 0;j<=4;j++) {
      setLed2(j);
      delay(show2Delay);
    }
    clearAllLeds();
    delay(show2Delay);
    show2Delay -= (show2Delay / rounds + 35);
    if (show2Delay < 80) {
      show2Delay = 80;
    }
  }
}