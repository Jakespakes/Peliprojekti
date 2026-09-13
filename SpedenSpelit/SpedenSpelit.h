#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include "buttons.h"
#include "display.h"
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.

extern byte randomNumber = 0;
unsigned int increment;
unsigned int value = 62499;

ISR(TIMER1_COMPA_vect) 
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  if (buttonWasPressed == true) {
    randomNumber = random(0, 4);        // Palautetaan muttuja niin ledi funktio voi lukea sen
    increment++;
  }

  /*
  Kun interrupti on tapahtunut kymmenen kertaa aletaan nopeuttamaan timeria
  Laskemalla prescalerin arvoa
  */
  if (increment == 10) {
    value *= 0.9;
    //initializeTimer(value);
  }
}

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
*/

void initializeTimer(unsigned int ocr1a_value)
{
  cli();                                  // Disable interrupts
  TCCR1B = B00000000;                     // Stop Timer/Counter1 clock by setting the clock source to none.
  TCCR1A = B00000000;                     // Set Timer/Counter1 to normal mode.
  TCNT1  = 0;                             // Set Timer/Counter1 to 0

  OCR1A = ocr1a_value;                    // Set prescaler as the wanted value
  TCCR1A = B01000100;                     // Set Timer/Counter1 to CTC mode. Set OC1A to toggle.
  TCCR1B = B00001010;                     // Start Timer/Counter1 clock by setting the source to CPU source. Set prescalar to 1/8 (2Mhz).
  TCCR1B |= (1 << WGM12);                 // Start Timer/Counter1 clock by setting the source to CPU source.
  TCCR1B = (1 << CS12);                   // Set CTC mode (WGM12 = 1), Set prescaler value to 256

  TIMSK1 |= (1 << OCIE1A);                // Enable Timer1 Output Compare Match A interrupt enable
  DDRB |= B00000010;                      //Set OCR1A as an Output.
}

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void) {
  uint8_t score = 0;
  uint8_t increment = 0;
  uint8_t button_press = false;
}

/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/

void checkGame(byte lastButtonPress) {
  if (buttonWasPressed == true) {
    buttonNumber = lastButtonPress;
    /*number++;
    result++;
    return number, result; */
  }
}


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void) 
{
  initializeGame();
  sei();              // Enable interrupts
}

#endif