#include<avr/io.h>
#include<util/delay.h>
#include "I2CSlave.h"

#define SLAVE_ADDRESS 0x04

volatile uint8_t data;

void I2C_received(uint8_t received_data)
{
  data = received_data;
  Serial.print("Data Received: ");
  Serial.println(data);
}

void I2C_requested()
{
  Serial.print("Data Acknwledged: ");
  Serial.println(data);
  I2C_transmitByte(data);
}

void setup()
{
  I2C_init(SLAVE_ADDRESS);
  I2C_setCallbacks(I2C_received, I2C_requested);
  Serial.println("Ready.........");
}

int main()
{
  Serial.begin(9600);
  setup();
  while(1);
}

