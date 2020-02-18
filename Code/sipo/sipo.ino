#include "SIPO.h"

SipoClass Reg;

bool data[80];
bool flag=1;

void setup()
{
  Serial.begin(9600);
  for(int i=0;i<80;i++){
    flag^=flag;
    data[i]=flag;
  }
}

void loop()
{
  Reg.LoadData(data);
  Reg.UpdateReg();
  delay(1000);
  Reg.ClearBuffer();
}
