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

void SipoClass::print_data(){
  Serial.print("\nSIPO array Content: ");
  for(int i=0;i<80;i++){
    Serial.print(Data[i]);
    Serial.print(" ");
    if((i+1)%8==0)
      Serial.print("\n");
  }
  Serial.print("\n");
}
void SipoClass::set_data(unsigned char cell[], int pos[]){
  int start_index=1;
  int last_index=1;
  if(pos[0]==1){
    start_index=2;
  }
  else if(pos[1]==1){
    start_index=3;
  }
  else if(pos[2]==1){
    start_index=4;
  }
  else if(pos[3]==1){
    start_index=5;
  }
  else if(pos[4]==1){
    start_index=6;
  }
  else if(pos[5]==1){
    start_index=7;
  }
  last_index=start_index+3;
  //Overwriting 0 before starting cells
  for(int i=0;i<(start_index-1)*8;i++){
    Data[i]=0;
  }
  //Putting the reuired content
  for(int i=(start_index-1)*8;i<(last_index)*8;i++){
    Data[i]=cell[i]-48;
  }
  //Overwriting 0 after the last cell
  for(int i=(last_index)*8;i<80;i++){
    Data[i]=0;
  }
}
