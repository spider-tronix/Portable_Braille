#include "BT.h"

Bluetooth::Bluetooth() {
  conn = false;
}

void Bluetooth::set_conn(bool X) {
  conn = X;
}

bool Bluetooth::CONNECTION() {
  return conn;
}

void  Bluetooth::set_msg(unsigned char ch) {
  msg = ch;
}

unsigned char  Bluetooth::MSG() {
  return msg;
}


Braille_buffer::Braille_buffer() {
  buffer_empty = true;
  char_count = 0;
  index = 0;
}

void Braille_buffer::load(unsigned char ch) {
  cells[index] = ch;
  index++;
  char_count++;
}

void Braille_buffer::reset_index() {
  index = 0;
  char_count = 0;
}

int Braille_buffer::count() {
  return char_count;
}

void Braille_buffer::print_cells() {
  Serial.print("\nCells Content: ");
  for(int i=0;i<80;i++){
    Serial.print(cells[i]-48);
    Serial.print(" ");
    if((i+1)%8==0)
      Serial.print("\n");
  }
  Serial.print("\n");
}

unsigned char * Braille_buffer::get_cells(){
  return cells;  
}

void try_connect(unsigned char ch) {
  if (ch == '#') {
    BT.set_conn(true);
    Serial.print('@');
  }
  else {
    BT.set_conn(false);
    Serial.print('#');
  }
}

void process_msg() {
  static bool loading = false;
  static int ind_count=1;
  uint8_t ch = (uint8_t)BT.MSG();               // Get the recieved msg from MASTER
  if (loading) {
    if (ch == 0x03) {
      loading = false;
      Serial.print(ch);                         //Acknowledgement with EOF
      Cells.print_cells();
    }
    else {
      Cells.load(ch);
      Serial.print(6, HEX);                     //Acknowledgement
      ind_count++;
      if(ind_count%7==0){                       //Append two 0's at the end to make 8 chracters for SIPO
        Cells.load('0');
        Cells.load('0');
        ind_count=1;
      }
    }
    return;
  }
  if (ch == 0x00) {                             // Pi checking the cells count Nano has.
    if (Cells.count() < 9)
      Serial.print(Cells.count(), HEX);
    else{
      Cells.s_trap();
      Serial.print(9, HEX);
    }
  }
  else if (ch == 0x02) {                        // Start of text received.
    Cells.reset_index();
    Serial.print(6, HEX);                       // Ack by sending 06H
    loading = true;                             //Flag to track loading
  }
}
