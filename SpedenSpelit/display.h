#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

void initializeDisplay(void);
void writeByte(uint8_t bits,bool last);
void writeHighAndLowNumber(uint8_t tens,uint8_t ones);
void showResult(byte number);

#endif