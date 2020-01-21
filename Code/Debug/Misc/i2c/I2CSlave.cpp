#include <util/twi.h>
#include <avr/interrupt.h>

#include "I2CSlave.h"

static void (*I2C_recv)(uint8_t);
static void (*I2C_req)();

ISR(TWI_vect)
{
  switch(TW_STATUS)
  {
    case TW_SR_DATA_ACK:                                        // received data from master, call the receive callback
      I2C_recv(TWDR); 
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_ST_SLA_ACK:                                         // master is requesting data, call the request callback
      I2C_req();
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_ST_DATA_ACK:                                        // master is requesting data, call the request callback
      I2C_req();
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
    case TW_BUS_ERROR:                                          // some sort of erroneous state, readdressing prep
      TWCR = 0;
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
      break;
    default:
      TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
      break;
  }
} 

void I2C_init(uint8_t address)
{
  cli();                                                    // Clear interrupts
  TWAR = address << 1;                                      // Loading slave address in the register
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);    // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
  sei();                                                    // Set interrupts
}

void I2C_setCallbacks(void (*recv)(uint8_t), void (*req)())
{
  I2C_recv = recv;
  I2C_req = req;
}

void I2C_stop(void)
{
  cli();
  TWCR = 0;                 // Stop communication
  TWAR = 0;                 // Removing Slave from the bus
  sei();
}


