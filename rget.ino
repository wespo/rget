#include "Audio.h"
#include "rget.h"

void rgetTest(Uint16 page, Uint16 registerPoint)
{
  Uint16 value = 0;
  int status = rget(page, registerPoint, &value); //rget takes the page and address of register to be read as well as a pointer to store the result.
  Serial.println("Page\tRegister\tValue");
  Serial.print(page);
  Serial.print('\t');
  Serial.print(registerPoint);
  Serial.print("\t\t");
  Serial.print(value);
  Serial.print(" (");
  Serial.print(value, HEX);
  Serial.println(")");
  
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  AudioC.Audio(TRUE);
  rgetTest(1,51); // Should be set to 0x48 (72 decimal) by audio library initialization.
  rgetTest(0,20); // Should be set to 0x80 (128 decimal) by audio library initialization.
  rgetTest(1,9);  // Should be set to 0x3C (60 decimal) by audio library initialization.
}

void loop()
{
  // put your main code here, to run repeatedly:
  
}
