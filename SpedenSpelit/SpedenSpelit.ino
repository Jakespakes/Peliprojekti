#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "sounds.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
extern bool gameIsOn = false;

void setup()
{
  Serial.begin(9600);
  /*
    Initialize here all modules
  */

  initializeLeds();
  initButtonsAndButtonInterrupts();
  //initializeDisplay();
  //initSound();
  initializeTimer();
  sei();
}

void loop()
{
  if (gameStart == true) {
    startTheGame();
    gameStart = false;
    gameIsOn = true;
  }

  /*while(gameIsOn == true) { // Pitää tehdä while looppi, että saadaan pyöritettyä musiikkia pelin aikana
    
    setLed();
  }*/

  /*if(newTimerInterrupt == true)
  {
    buttonWasPressed = true;
     // Ilmoitetaan timerille, että uusi numero pitää generoida.
  }*/
}