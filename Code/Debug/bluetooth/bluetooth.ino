#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void usart_int(void) {
  UCSR0A=0x00;
  UCSR0B=(1<< RXEN0)|(1<< TXEN0);//TRANSMIT AND RECEIVE ENABLE
  UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//ASYNCHRONOUS, 8 BIT TRANSFER
  UBRR0L= 103 ; //BAUD RATE 9600 
}

void usart_send(int ch )
{
  while(UCSR0A!=(UCSR0A|(1<<UDRE0)));//waiting for UDRE to become high
  UDR0= ch;
}

int main(void)
{
  DDRB=0xFF;
  DDRD=0b11110000;
  usart_int();
  unsigned int ch;
  while(1){
    while(UCSR0A!= (UCSR0A|(1<<RXC0))); 
    ch=UDR0;
    usart_send(ch);
    usart_send('\n');
    _delay_ms(100);
   }
      
}
  
