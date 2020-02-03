#include "BT.h"
volatile bool RX_RCV = false;

Braille_buffer Cells;
Bluetooth BT;

void serialEvent() {
    unsigned char rcv = (unsigned char)Serial.read();
    BT.set_msg(rcv);
    RX_RCV = true;
}

void setup() {
  cli();
  Serial.begin(9600);
  sei();
}

void loop() {
  if (RX_RCV) {
    if (BT.MSG() == '#' && BT.CONNECTION()) {      // Connection was interrupted
      BT.set_conn(false);
      try_connect(BT.MSG()); 
    }
    else if (BT.CONNECTION()) {                    // Already connected
      process_msg();
    }
    else {
      try_connect(BT.MSG());                       // Try connecting
    }
    RX_RCV = false;
  }
}
