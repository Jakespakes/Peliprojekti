#include "display.h"
#include <Arduino.h>

//Annetaan pinneille ohjeiden mukaiset arvot

const int resetPin = 12;
const int shiftClockPin = 11;
const int latchClockPin = 10;
const int outEnablePin = 9;
const int serialInputPin = 8;

// 7-segmenttinäytön mukaiset numeroita vastaavat bittiarvot

const uint8_t numberBits[] = {
  0b00111111, // Numero 0
  0b00000110, // Numero 1
  0b01011011, // Numero 2
  0b01001111, // Numero 3
  0b01100110, // Numero 4
  0b01101101, // Numero 5
  0b01111101, // Numero 6
  0b00000111, // Numero 7
  0b01111111, // Numero 8
  0b01101111, // Numero 9
};

//Valmistellaan pinnit käyttöä varten
void initializeDisplay(void)
{
  pinMode(resetPin, OUTPUT);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(outEnablePin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);

  //Reset laitetaan pois päältä
  digitalWrite(resetPin, HIGH);

  //Resetoidaan kaikki varmuuden vuoksi
  digitalWrite(outEnablePin, HIGH);
  digitalWrite(latchClockPin, LOW);

  //Laitetaan outti päälle.
  digitalWrite(outEnablePin, LOW);
}

void writeByte(uint8_t bits,bool last)
{
  for (int i = 7; i>=0; i--) //Otetaan kahdeksan bitin bittijono alkaen suurimmasta bitistä.
  {
    int bitValue = bitRead(bits, i); //Luetaan bitin tila
    digitalWrite(serialInputPin, bitValue); //Annetaan sirulle yksi bittiarvo.
    digitalWrite(shiftClockPin, HIGH); //Nostetaan pinni ja otetaan bitti sisään.
    digitalWrite(shiftClockPin, LOW); //Lasketaan pinni ja laitetaan kello takaisin odottamaan.
  }

  if (last) { //Jos tämä on viimeinen tavu niin laita bittijono eteenpäin.
    digitalWrite(latchClockPin, HIGH); //Nostetaan salpa ja ulostulossa nyt bittijono.
    digitalWrite(latchClockPin, LOW); //Lasketaan salpa, koska bittijono valmis.
  }
}

void writeHighAndLowNumber(uint8_t tens,uint8_t ones)
{
  writeByte(numberBits[ones], false);
  writeByte(numberBits[tens], true); 
}

void showResult(byte number)
{
  writeHighAndLowNumber(number/10, number%10);
}