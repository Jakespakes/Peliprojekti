#include "buttons.h"
#include "sounds.h"

extern volatile bool gameStart = false;

void testButtons()  {
if (buttonWasPressed == true) {
  int nappi = pressedButton();
  buttonSound(nappi);
  Serial.print(nappi);
  buttonWasPressed = false;
  }
}

void initButtonsAndButtonInterrupts() {
  for (int i = 2;i<=6;i++) { 
    pinMode(i, INPUT_PULLUP);
  }

  PCICR |= (1 << PCIE2);       // Keskeytykset porttiin D

  for (int i = 2;i<=6;i++) {     // Pinnit 2-6 auki keskeytyksille
    PCMSK2 |= (1 << i);
  }
}


int pressedButton() {         // Tällä voi tsekata ja nollata viimeksi painetun napin    
  noInterrupts();             // keskeytykset pois päältä
  int button = buttonNumber;  // otetaan talteen viimeksi painettu nappi
  buttonNumber = -1;          // nollataan buttonNumber
  interrupts();               // keskeytykset takaisin päälle
  return button;              // palautetaan napin arvo
}

volatile bool buttonWasPressed = false;
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 100;   

ISR(PCINT2_vect) {        
  uint8_t pressed = ~PIND;    
  unsigned long now = millis();
  if (now - lastDebounceTime > debounceDelay) {
    lastDebounceTime = now;
    for (int i = 2;i<=6;i++)  {
      if (pressed & ( 1 << i)) {
        buttonNumber = i;

        if (buttonNumber == 6) {
          gameStart = true;
          buttonNumber = 0;
        }
        else 
          buttonWasPressed = true;
        break;
      }
    }
  }
}