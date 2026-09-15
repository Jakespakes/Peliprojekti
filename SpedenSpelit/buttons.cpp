#include "buttons.h"

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


int pressedButton() {   // <-- Turha? | Ei ole kun ollaan tässä määritelty tuo muuttuja "buttonNumber"
  noInterrupts();
  int button = buttonNumber; 
  buttonNumber = -1;
  interrupts();
  return button;
}

/*
bool checkGameStart() {
  if(lednumber == 2) {
    gameStart = true;
  }
} */

extern volatile bool gameStart = false;
volatile bool buttonWasPressed = false;
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30;
                
ISR(PCINT2_vect) {        
  uint8_t pressed = ~PIND;    
  unsigned long now = millis();
  if (now - lastDebounceTime > debounceDelay) {
    lastDebounceTime = now;
    for (int i = 2;i<=6;i++)  {
      if (pressed & ( 1 << i)) {
        buttonNumber = i;

        if (i == 6)  {
          gameStart = true;
        }

        buttonWasPressed = true;
        break;
      }
    }
  }
}

// Alempana on oma prototyyppi mitä käytin kun koitin selvittää miten ylempi koodi toimii

/*
volatile int ledNumber = 0;
ISR(PCINT2_vect) {
  for (int i = 2; i < 7; i++) {
    byte luettu = digitalRead(i);

    if(luettu == LOW) {
      ledNumber = i;
    }
  }

  if(ledNumber == 2) {
    gameStart = true;
  }
}
*/