

#include <I2C.h>
#include <TM1650_STM8.h>

void setup()
{
  I2C_begin();

  TM1650_init();
  TM1650_clearDisplay();
  TM1650_setBrightness(3);
  TM1650_displayOn();
  
  TM1650_sendDigit(0xFF, 1);
  delay(2000);
  
  TM1650_writeNumber(9876, false);
  //TM1650_writeNum(i); //Alternative of TM1650_writeNumber(i, TM1650_ZERO_PREFIX);
  delay(2000);

  int i;
  
  for(i=1; i<9999; ){
    TM1650_writeNumber(i, false);
    i = i*2;
    delay(1000);
  }
  
  TM1650_clearDisplay();
  delay(1000);
  
  for(i=1; i<9999; ){
    TM1650_writeNumber(i, true);
    i = i*2;
    delay(1000);
  }
  
  TM1650_writeNumber(56789, false);
  delay(2000);
  
  TM1650_clearDisplay();
  
  TM1650_sendDigit(94, 0);          //d, 94 === 0x5E
  TM1650_sendDigit(0b00111111, 1);  //0
  TM1650_sendDigit(0x54, 2);        //n, 0b01010100 === 0x54
  TM1650_sendDigit(0x79, 3);        //E
}

void loop()
{
}


/* EOF - HelloWorld.ino */