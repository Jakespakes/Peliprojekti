#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.

ISR(TIMER1_COMPA_vect) 
{

}


/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
*/

void initializeTimer(void)
{
  uint8_t s, ss;

  cli();                                  // Stop interrupts while we set up the timer
  TCCR1B = B00000000;                     // Stop Timer/Counter1 clock by setting the clock source to none.
  TCCR1A = B00000000;                     // Set Timer/Counter1 to normal mode.
  TCNT1  = 0;                             // Set Timer/Counter1 to 0

  OCR1A = 62499;                          // Set the Output Compare A for Timer/Counter1
  TCCR1A = B01000100;                     // Set Timer/Counter1 to CTC mode. Set OC1A to toggle.
  TCCR1B = B00001010;                     // Start Timer/Counter1 clock by setting the source to CPU source. Set prescalar to 1/8 (2Mhz).
  TCCR1B |= (1 << WGM12);                 // Set CTC mode (WGM12 = 1)
  TCCR1B = (1 << CS12)                    // Set prescaler value to 256
  TIMSK1 |= (1 << OCIE1A);                // Enable Timer1 Compare Match A interrupt
  ss = 0;
  s = 0;
}

/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame(void) {
  uint8_t score = 0;
  uint8_t increment = 0;
  uint8_t button_press = true;
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
  
}


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame(void) {
  initializeGame();
  sei();
}

#endif