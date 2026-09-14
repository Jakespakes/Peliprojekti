#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler

void setup()
{
  Serial.begin(9600);
  /*
    Initialize here all modules
  */

  //initializeLeds();
  //initButtonsAndButtonInterrupts();
  //initializeDisplay();
  //initializeGame();
  initializeTimer();
}

void loop()
{
  if(buttonNumber>=0)
  {
     // start the game if buttonNumber == 4
     if (buttonNumber == 4) {
      //startGame();
     }
     // check the game if 0<=buttonNumber<4
     if (0 <= buttonNumber < 4) {
      //checkGame();
     }
  } 

  if(newTimerInterrupt == true)
  {
    buttonWasPressed = true;
     // Ilmoitetaan timerille, että uusi numero pitää generoida.
  }
}