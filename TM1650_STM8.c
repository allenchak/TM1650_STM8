
#include "TM1650_STM8.h"

#if(ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <I2C.h>


byte  iCtrl[TM1650_NUM_DIGIT];
byte  iData[TM1650_NUM_DIGIT];
char  iMode = 0;

static char tm1650_Digit_Table[] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F, // 9

  0x77, // A
  0x7C, // b
  0x39, // C
  0x5E, // d
  0x79, // E
  0x71, // F
  0x00  // (OFF)
};

void TM1650_init(){
  I2C_write(TM1650_DISPLAY_BASE,0x00);
  char dig = TM1650_NUM_DIGIT;
  while( dig ){
    dig--;
    iCtrl[dig] = 0x00;
    iData[dig] = 0x00;
  }
}

void TM1650_sendControl(unsigned char data, uint8_t segment){
  segment = segment % TM1650_NUM_DIGIT;
  I2C_write(TM1650_CONTROL_BASE + segment, data);
  delay(1); //optional
}

void TM1650_sendDigit(unsigned char data, uint8_t segment){
  segment = segment % TM1650_NUM_DIGIT;
  I2C_write(TM1650_DISPLAY_BASE + segment, data);
  delay(1); //optional
}

void TM1650_displayOn(){
  for(char i=0; i< TM1650_NUM_DIGIT; i++){
    TM1650_sendControl(((iCtrl[i] & 0b11111110) | 0b00000001), i);
  }
}

void TM1650_displayOff(){
  for(char i=0; i< TM1650_NUM_DIGIT; i++){
    TM1650_sendControl((iCtrl[i] & 0b11111110), i);
  }
}

void TM1650_colonOn(){
  TM1650_sendControl(((iCtrl[0] & 0b11110111) | 0b00001000), 0);
}

void TM1650_colonOff(){
  TM1650_sendControl((iCtrl[0] & 0b11110111), 0);
}

void TM1650_setBrightness(unsigned char b){
  if( b > 0x07){
    b = 0x07;
  }
  for(char i=0; i< TM1650_NUM_DIGIT; i++){
    iCtrl[i] = ((iCtrl[i] & 0b11111110) | (b << 4));
    TM1650_sendControl(iCtrl[i], i); // Bright ..... Dim; 0, 7, 6, 5, 4, 3, 2, 1
  }
}

void TM1650_clearDisplay(){
  for(char i=0; i< TM1650_NUM_DIGIT; i++){
    TM1650_sendDigit(0x00, i);
    iData[i] = 0x00;
  }
}


void TM1650_test(char pos){
  for(char i=0; i< TM1650_NUM_DIGIT; i++){
    if( pos == i)
      TM1650_sendDigit(0xff, i);
    else
      TM1650_sendDigit(0x00, i);
  }
}

void TM1650_setDot(char pos, bool onoff){
  pos = pos % TM1650_NUM_DIGIT;
  uint8_t data = iData[pos];
  data = onoff ? (data | 0x80) : (data & 0x7F);
  TM1650_sendDigit( data, pos );
}



#if TM1650_MEMORY_SAVER == 0
void TM1650_writeNumber(unsigned int num, boolean zeroFill){
  unsigned int onum = num;
  uint8_t digit;
  digit = num % 10;
  TM1650_sendDigit( tm1650_Digit_Table[digit], 3 );
  iData[3] = digit;
  num = num / 10;
  digit = num % 10;
  if( zeroFill == false && onum < 10U && digit == 0 ){
    TM1650_sendDigit( tm1650_Digit_Table[0x10], 2 );
  }else{
    TM1650_sendDigit( tm1650_Digit_Table[digit], 2 );
  }
  iData[2] = digit;
  num = num / 10;
  digit = num % 10;
  if( zeroFill == false && onum < 100U && digit == 0 ){
    TM1650_sendDigit( tm1650_Digit_Table[0x10], 1 );
  }else{
    TM1650_sendDigit( tm1650_Digit_Table[digit], 1 );
  }
  iData[1] = digit;
  num = num / 10;
  digit = num % 10;
  if( zeroFill == false && onum < 1000U && digit == 0 ){
    TM1650_sendDigit( tm1650_Digit_Table[0x10], 0 );
  }else{
    TM1650_sendDigit( tm1650_Digit_Table[digit], 0 );
  }
  iData[0] = digit;
}

void TM1650_writeNum(unsigned int num){
  TM1650_writeNumber(num, TM1650_ZERO_PREFIX);
}


#else

void TM1650_writeNumber(unsigned int num, boolean zeroFill){
  TM1650_writeNum(num);
}

void TM1650_writeNum(unsigned int num){
#if TM1650_ZERO_PREFIX == false
  unsigned int onum = num;
#endif
  uint8_t digit;
  digit = num % 10;
  TM1650_sendDigit( tm1650_Digit_Table[digit], 3 );
  iData[3] = digit;
  num = num / 10;
  digit = num % 10;
#if TM1650_ZERO_PREFIX == false
  if( onum < 10U && digit == 0) digit = 0x10;
#endif
  TM1650_sendDigit( tm1650_Digit_Table[digit], 2 );
  iData[2] = digit;
  num = num / 10;
  digit = num % 10;
#if TM1650_ZERO_PREFIX == false
  if( onum < 100U && digit == 0) digit = 0x10;
#endif
  TM1650_sendDigit( tm1650_Digit_Table[digit], 1 );
  iData[1] = digit;
  num = num / 10;
  digit = num % 10;
#if TM1650_ZERO_PREFIX == false
  if( onum < 1000U && digit == 0) digit = 0x10;
#endif
  TM1650_sendDigit( tm1650_Digit_Table[digit], 0 );
  iData[0] = digit;
}
#endif  /* TM1650_MEMORY_SAVER */

