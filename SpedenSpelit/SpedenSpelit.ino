#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "sounds.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool gameIsOn = false;
bool playMelody = false;

void setup()
{
  /*
    Initialize here all modules
  */

  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initSound();
  initializeTimer();
  sei();

  Serial.begin(9600);
}

void loop()
{
  // Nappi moduuli kuuntelee kunnes aloitusnapia on painettu
  if (gameStart) {
    startTheGame();
    Serial.println("Aloitetaan");
    gameStart = false;
    gameIsOn = true;
    playMelody = true;
  }
  
  melody();
  // Soitetaan musiikkia kunhan playMelody = true

  // Kun jotain nappia on painettu sen jälkeen kun peli on aloitettu
  // aletaan vertaamaan timerin lukuja ja painettuja nappeja

  if(newNumberReady) {
    setLed(randomNumber);
    newNumberReady = false;
  }

  if(buttonWasPressed && gameIsOn) {
    volatile bool check = checkGame(buttonNumber);

    if(check) {
      buttonSound(buttonNumber);
      newTimerInterrupt = true;
    }
    else {
      failureSound();
      resetGame();
      playMelody = false;
    }

    buttonWasPressed = false;
  }
}