#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "sounds.h"

volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool gameIsOn = false;           // for indicating main loop game has started
bool playMelody = false;                  // for melody player function
unsigned int score = 0;

void setup()
{
  // Alustetaan kaikki moduulit setupissa

  initializeLeds();
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initSound();
  initializeTimer();

  sei();  // Enabloidaan keskeytykset <avr/interrupt.h> -kirjastosta

  Serial.begin(9600);
}

void loop()
{
  // Nappi moduuli kuuntelee kunnes aloitusnapia on painettu
  if (gameStart) {
    startTheGame();
    gameStart = false;
    gameIsOn = true;
    score = 0;
  }

  // Käytetään while looppia, niin ei tarvitse laittaa montaa muuttujaan kaikkiin if lausekkeisiin
  while(gameIsOn) {
    melody();  // Soitetaan musiikkia niin kauan kunhan gameIsOn = true

    if(buttonWasPressed) {
      buttonWasPressed = false;
      bool check = checkGame(buttonNumber);

      if(check) {
        buttonSound(buttonNumber);
        score += 1;
      } 
      else { 
        failureSound();
        gameIsOn = false;
        buttonWasPressed = false;
        resetGame();
      }
      showResult(score);
      Serial.println(score);
    }

    /*
      Kun jotain nappia on painettu sen jälkeen kun peli on aloitettu
      aletaan vertaamaan timerin lukuja ja painettuja nappeja
      Käytetään kahta muuttujaa koska muuten ohjelma laskee vaikka peli oltaisiin hävitty 
    */

    if(newNumberReady) {
      setLed(randomNumber);
      newNumberReady = false;
      newTimerInterrupt = true;
    }
  }
}