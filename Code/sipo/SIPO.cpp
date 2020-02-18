#include "SIPO.h"

#define RCLK 5
#define SER 4
#define SRCLK 6
#define EN 3

void setEnable_PWM(int val){
  analogWrite(EN,val);
}

SipoClass::SipoClass(){
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
    pinMode(EN, OUTPUT);
    ClearBuffer();
    setEnable_PWM(255);
}

void SipoClass::ClearBuffer()
{
  for (int i = TotalICPins - 1; i >=  0; i--)
  {
    Data[i] = LOW;
  }
  UpdateReg();
}

void SipoClass::UpdateReg(){
    digitalWrite(RCLK, LOW);
    for (int i = TotalICPins - 1; i >=  0; i--)
    {
        digitalWrite(SRCLK, LOW);
        digitalWrite(SER, Data[i]);
        digitalWrite(SRCLK, HIGH);
    }
    digitalWrite(RCLK, HIGH);
}

void SipoClass::LoadData(bool dat[]){
    for (int i = TotalICPins - 1; i >=  0; i--)
    {
        Data[i]=dat[i];
    }
}
