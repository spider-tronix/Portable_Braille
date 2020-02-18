#include "SIPO.h"
#include "BT.h"

SipoClass Reg;
Braille_buffer Cells;
Bluetooth BT;

volatile bool RX_RCV = false;
bool data[80];
bool flag=1;

void serialEvent() {
    unsigned char rcv = (unsigned char)Serial.read();
    BT.set_msg(rcv);
    RX_RCV = true;
}

void motd() {
  Serial.println("Intialising........");
  delay(100);
  Serial.println("==================================================================================================================");
  delay(50);
  Serial.println(" _____   ____  _____ _______       ____  _      ______         ____  _____            _____ _      _      ______  ");
  delay(50);
  Serial.println("|  __ \ / __ \|  __ \__   __|/\   |  _ \| |    |  ____|       |  _ \|  __ \     /\   |_   _| |    | |    |  ____| ");
  delay(50);
  Serial.println("| |__) | |  | | |__) | | |  /  \  | |_) | |    | |__          | |_) | |__) |   /  \    | | | |    | |    | |__    ");
  delay(50);
  Serial.println("|  ___/| |  | |  _  /  | | / /\ \ |  _ <| |    |  __|         |  _ <|  _  /   / /\ \   | | | |    | |    |  __|   ");
  delay(50);
  Serial.println("| |    | |__| | | \ \  | |/ ____ \| |_) | |____| |____        | |_) | | \ \  / ____ \ _| |_| |____| |____| |____  "); 
  delay(50);
  Serial.println("|_|     \____/|_|  \_\ |_/_/    \_\____/|______|______|       |____/|_|  \_\/_/    \_\_____|______|______|______| ");
  delay(50);
  Serial.println("");
  Serial.println("==================================================================================================================");
  delay(50);
}

void setup()
{
  cli();
  Serial.begin(9600);
  motd();
  sei();
}

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
}
