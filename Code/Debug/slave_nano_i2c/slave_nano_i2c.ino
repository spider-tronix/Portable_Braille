#include<avr/io.h>
#include<util/delay.h>
#include "I2CSlave.h"

#define SLAVE_ADDRESS 0x04
// #define SLAVE_ADDRESS 0x14

volatile uint8_t data = 0x00;

void take_action() {
  if ( (data & 0xC0) == 0xC0 ) {      // Signal Pin change
    uint8_t ext_data = (data & 0x3F) << 2;
    PORTD = ext_data;
    Serial.print("Signal: ");
    Serial.println(PIND,BIN);
  }
  else if ((data & 0xC0) == 0x40 ) {  // Select line change
    uint8_t ext_data = (data & 0x03);
    PORTD = PORTD || ext_data;
    PORTB = (ext_data << 6) || (ext_data << 4) || (ext_data << 2) || (ext_data);
    PORTC = (ext_data << 2) || (ext_data);
    Serial.println("Select: PORTD   PORTB   PORTC ");
    Serial.print("        ");Serial.print(PIND,BIN);Serial.print("\t");Serial.print(PINB,BIN);Serial.print("\t");Serial.println(PINC,BIN);
  }
  else {
    return;
  }
}

void I2C_received(uint8_t received_data)
{
  data = received_data;
  take_action();
}

void I2C_requested()
{
  Serial.print("Data Acknwledged: ");
  Serial.println(data);
  I2C_transmitByte(data);
}

void init()
{
  Serial.println("Initialising I2C Communication.......");
  I2C_init(SLAVE_ADDRESS);
  I2C_setCallbacks(I2C_received, I2C_requested);
  Serial.println("Communication link established....");
  Serial.print("Listening on PORT ");
  Serial.println(SLAVE_ADDRESS, HEX);
}

int main()
{
  DDRB = 0xFF;
  DDRC = 0xFF;
  DDRD = 0xFF;
  PORTB = 0x00;
  PORTC = 0x00;
  PORTD = 0x00;
  Serial.begin(9600);
  init();
  while (1);
}

