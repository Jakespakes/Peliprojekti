#include "buttons.h"
#include "sounds.h"

volatile bool gameStart = false;

void testButtons()  { // Nappien ja painallus äänien testausta varten
if (buttonWasPressed == true) {
  int nappi = pressedButton();
  buttonSound(nappi);
  Serial.print(nappi);
  buttonWasPressed = false;
  }
}

void initButtonsAndButtonInterrupts() {
  for (int i = 2;i<=6;i++) {  // Laitetaan pinnit 2-6 pullup tilaan
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


bool buttonWasPressed = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 1000;   

ISR(PCINT2_vect) {        
  uint8_t pressed = ~PIND; // Otetaan D portin pinnien tilat talteen
  unsigned long now = millis(); // Debounce

  if (now - lastDebounceTime > debounceDelay) { // Tarkistetaan onko edellisestä painalluksesta kulunut riittävästi aikaa
    for (int i = 2;i<=6;i++)  { // Käydään talteen otetut pinnien tilat läpi ja katsotaan mitä nappi painettiin

      if (pressed & ( 1 << i)) {
        lastDebounceTime = now; // Päivitetään debounce aika jos on
        buttonNumber = i; // buttonNumber = painettu nappi

        if (buttonNumber == 6) { // Tarkistetaan oliko aloitusnappi pelin aloitusta varten
          gameStart = true;
          buttonNumber = 0;
        }
    
        else 
          buttonWasPressed = true; // Yleinen "nappia painettiin" flagi

        break;
      }
    }
  }
}