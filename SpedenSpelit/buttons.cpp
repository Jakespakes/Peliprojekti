#include "buttons.h"

void testButtons()  {
  int command = Serial.parseInt();
  if (command == 1) {
    int nappi = pressedButton();
    Serial.print("NAPPI");
    Serial.print(nappi);
    Serial.println("painettu");
    command = 0;
  }
}

void initButtonsAndButtonInterrupts() {
  for (int i = firstPin;i<=lastPin;i++) { 
    pinMode(i, INPUT_PULLUP);
  }

  PCICR |= (1 << PCIE2);       // Keskeytykset porttiin D

  for (int i = firstPin;i<=lastPin;i++) {     // Pinnit 2-6 auki keskeytyksille
    PCMSK2 |= (1 << i);
  }
}

int pressedButton() {          
  noInterrupts();
  int button = buttonNumber; 
  buttonNumber = -1;
  interrupts();
  return button;
}

volatile bool buttonWasPressed = false;
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30;
                 
ISR(PCINT2_vect) {        
  uint8_t pressed = ~PIND;    
  unsigned long now = millis();
  if (now - lastDebounceTime > debounceDelay) {
    for (int i = firstPin;i<=lastPin;i++)  {
      if (pressed & ( 1 << i)) {
        lastDebounceTime = now;
        buttonNumber = i;
        buttonWasPressed = true;
        break;
      }
    }
  }
}