#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile bool RX_RCV = false;

class Bluetooth {
  private:
    bool conn;
    unsigned char msg;
  public:
    Bluetooth() {
      conn = false;
    }
    void set_conn(bool X) {
      conn = X;
    }
    bool CONNECTION() {
      return conn;
    }
    void set_msg(unsigned char ch) {
      msg = ch;
    }
    unsigned char MSG() {
      return msg;
    }
};

class Braille_buffer {
  private:
    unsigned char cells[60];
    bool buffer_empty = true;
    int char_count;
    int index;
  public:
    Braille_buffer() {
      buffer_empty = true;
      char_count = 0;
      index = 0;
    }
    void load(unsigned char ch) {
      cells[index] = ch;
      index++;
      char_count++;
    }
    void reset_index(){
      index = 0;
      char_count = 0;
    }
    int count() {
      return char_count;
    }
};

Braille_buffer Cells;
Bluetooth BT;

ISR(USART_RX_vect) {
  unsigned char rcv = UDR0;
  BT.set_msg(rcv);
  RX_RCV = true;
}

void usart_int(void) {
  UCSR0A = 0x00;
  UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0); //TRANSMIT AND RECEIVE ENABLE,  RX Interrupt
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //ASYNCHRONOUS, 8 BIT TRANSFER
  UBRR0L = 103 ; //BAUD RATE 9600
}

void usart_send(int ch )
{
  PORTB = 0xFF;
  while (UCSR0A != (UCSR0A | (1 << UDRE0))); //waiting for UDRE to become high
  UDR0 = ch;
  PORTB = 0x00;
}

void try_connect(unsigned char ch) {
  if (ch == '#') {
    BT.set_conn(true);
    usart_send('@');
  }
  else {
    BT.set_conn(false);
    usart_send('#');
  }
}

void process_msg() {
  static bool loading = false;
  uint8_t ch = (uint8_t)BT.MSG();               // Get the recieved msg from MASTER
  if (loading) {
    if (ch == 0x03) {
      loading = false;
      usart_send(ch);                 //Acknowledgement with EOF
    }
    else {
      Cells.load(ch);
      usart_send(0b00000110);         //Acknowledgement
    }
    return;
  }
  if (ch == 0x00) {                   // Pi checking the cells count Nano has.
    if(Cells.count()<9)
      usart_send(Cells.count() + 48);
    else
      usart_send(57);
  }
  else if (ch == 0x02) {              // Start of text received.
    Cells.reset_index();
    usart_send(0b00000110);           // Ack by sending 06H
    loading = true;                   //Flag to track loading
  }
}

int main(void)
{
  cli();
  DDRB = 0xFF;
  PORTB = 0x00;
  usart_int();
  sei();
  while (1) {
    if (RX_RCV) {

      if (BT.MSG() == '#' && BT.CONNECTION()) {      // Connection was interrupted
        BT.set_conn(false);
      }
      if (BT.CONNECTION()) {                        // Already connected
        process_msg();
      }
      else {
        try_connect(BT.MSG());                      // Try connecting
      }
      RX_RCV = false;
    }
  }
  return 0;
}
