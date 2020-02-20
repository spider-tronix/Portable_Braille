#include "SIPO.h"
#include "BT.h"

SipoClass Reg;
Braille_buffer Cells;
Bluetooth BT;

volatile bool RX_RCV = false;

void serialEvent() {
    unsigned char rcv = (unsigned char)Serial.read();
    BT.set_msg(rcv);
    RX_RCV = true;
}

void motd() {
  Serial.println("Intialising...");
  delay(100);
  Serial.println("==================================================");
  delay(50);
  Serial.println("                PORTABLE BRAILLE");
  Serial.println("Version: 2.0");
  Serial.println("Made By: Aditya Kumar Singh, Ruphan S");
  Serial.println("==================================================");
  delay(50);
}

void setup()
{
  cli();
  Serial.begin(9600);
  motd();
  sei();
}

int pos[]={0,0,0,0,0,1};
int flag=1;
void loop()
{
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
  
  if(Cells.r_trap()==2 && flag){
    Reg.set_data(Cells.get_cells(),pos);
    Reg.print_data();
    
    flag=0;
  }
}
