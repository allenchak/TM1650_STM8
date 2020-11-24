

#ifndef TM1650_STM8_H
#define TM1650_STM8_H


#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif


#define TM1650_DISPLAY_BASE    0x34
#define TM1650_CONTROL_BASE    0x24
#define TM1650_NUM_DIGIT          4  //TM1650 / FD650 support up to 4 digits
#define TM1650_MEMORY_SAVER       0  //How the library to save your Flash Memory, 0..1
                                     //[0]  (Default) Suggest using TM1650_writeNumber() function
                                     //[1]  Sketch size reduce 67 Bytes, Zero Fill depends on `TM1650_ZERO_PREFIX`
#define TM1650_ZERO_PREFIX    false


void TM1650_init();

void TM1650_sendControl(unsigned char data, uint8_t segment);

void TM1650_sendDigit(unsigned char data, uint8_t segment);

void TM1650_displayOn();

void TM1650_displayOff();

void TM1650_colonOn();

void TM1650_colonOff();

void TM1650_setBrightness(unsigned char b);

void TM1650_clearDisplay();

void TM1650_test(char pos);

void TM1650_setDot(char pos, bool onoff);

void TM1650_writeNumber(unsigned int num, boolean zeroFill);

void TM1650_writeNum(unsigned int num);


#endif  /* TM1650_STM8_H */
