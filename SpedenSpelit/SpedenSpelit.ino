#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "sounds.h"

volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool gameIsOn = false;           // for indicating main loop game has started
bool playMelody = false;                  // for melody player function

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
    playMelody = true;
  }
  
  melody();  // Soitetaan musiikkia niin kauan kun playMelody = true

  // Kun jotain nappia on painettu sen jälkeen kun peli on aloitettu
  // aletaan vertaamaan timerin lukuja ja painettuja nappeja
  if(newNumberReady) {
    setLed(randomNumber);
    newNumberReady = false;
  }

  if(buttonWasPressed && gameIsOn) {  // Pitää käyttää kahta muuttujaa, että saadaan peli alkamaan oikeissa termeissä
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