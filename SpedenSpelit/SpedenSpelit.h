#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include "buttons.h"
#include "display.h"
#include "sounds.h"
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

byte randomNumber = 0;
unsigned int index = 0;
unsigned int value = 62499;
extern volatile bool newTimerInterrupt;
volatile bool newNumberReady = false;

// Introduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.

ISR(TIMER1_COMPA_vect) 
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */

  if (newTimerInterrupt) {
    // Tehdään timerissa satunnainen luku 0-3 välillä, joka sitten annetaan ledille
    randomNumber = random(0, 4); // Tämä ei ole täysin satunnainen tapa joka kerta eka luku on 0
    newNumberReady = true;

    index++;

    /*
      Kun interrupti on tapahtunut kymmenen kertaa aletaan nopeuttamaan timeria
      laskemalla keskeytyslipun arvoa
    */

    if (index == 10) {
      value *= 0.9;
      OCR1A = value;
      TCNT1 = 0;
      index = 0;
    }
    newTimerInterrupt = false;
  }
}

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
*/

void initializeTimer()
{
  cli();                                  // Disable interrupts
  TCCR1B = B00000000;                     // Stop Timer/Counter1 clock by setting the clock source to none.
  TCCR1A = B00000000;                     // Set Timer/Counter1 to normal mode.
  TCNT1  = 0;                             // Set Timer/Counter1 to 0

  OCR1A = 62499;                          // Set prescaler as the wanted value
  TCCR1A = B01000100;                     // Set Timer/Counter1 to CTC mode. Set OC1A to toggle.
  TCCR1B = B00001010;                     // Start Timer/Counter1 clock by setting the source to CPU source. Set prescalar to 1/8 (2Mhz).
  TCCR1B |= (1 << WGM12);                 // Start Timer/Counter1 clock by setting the source to CPU source.
  TCCR1B = (1 << CS12);                   // Set CTC mode (WGM12 = 1), Set prescaler value to 256
  DDRB |= B00000010;                      // Set OCR1A as an Output.
}

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
*/

/*
void initializeGame() {
  Mitä tällä tehdään ??
}
*/

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is indecesed
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
*/

bool checkGame(byte lastButtonPress) {
  buttonNumber = lastButtonPress; // buttonNumber määritellään nappikeskeytyksessä
  lastButtonPress -= 2; 
  
  // Luetut napit ovat 2-5 niin vähennetään 2 jotta se olisi 0-3

  /*
  Serial.print("Viimeksi painettu nappi: ");
  Serial.println(lastButtonPress);

      // NÄMÄ OVAT TÄSSÄ VAIN DEBUGGAUSTA VARTEN KOSKA EN OSAA TEHDÄ OIKEAA TESTAUSJÄRJESTELMÄÄ

  Serial.print("Mitä pitäisi painaa: ");
  Serial.println(randomNumber);
  */

  if (lastButtonPress == randomNumber) {
    return true;
  } 
  else {
    return false;
  }
}

/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game
*/

void startTheGame(void) {
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 Output Compare Match A interrupt enable
  PCMSK2 |= (0 << 6); // Otetaan pinni 6 eli aloitusnappi pois käytöstä pelin ajaksi
  startSound();
  newTimerInterrupt = true;
}

// Helppo tapa aloittaa peli uudestaan kun se hävitään.
void resetGame() {
  asm volatile ("jmp 0"); // Tämä pätkä hyppää suoraan koodin alkuun. Vähän niinkuin C:n return 0;
  //gameStart = false;
  PCMSK2 |= (1 << 6); // Laitetaan pinni 6 käyttöön
}

#endif