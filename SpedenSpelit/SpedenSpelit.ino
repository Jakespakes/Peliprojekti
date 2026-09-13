#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler

unsigned int ocr1a_value = 62499;

void setup()
{
  Serial.begin(9600);
  /*
    Initialize here all modules
  */

  //initializeLeds();
  //initializeButtons();
  //initializeDisplay();
  //initializeGame();
  initializeTimer(ocr1a_value);
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
     // new random number must be generated
     // and corresponding let must be activated
  }
}

//void initializeTimer(void);
	// see requirements for the function from SpedenSpelit.h

//void checkGame(byte nbrOfButtonPush);
	// see requirements for the function from SpedenSpelit.h

//void initializeGame();
	// see requirements for the function from SpedenSpelit.h

//void startGame();
   // see requirements for the function from SpedenSpelit.h

