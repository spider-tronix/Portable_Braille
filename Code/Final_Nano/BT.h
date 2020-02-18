#ifndef BT_H
#define BT_H
#include<Arduino.h>

class Bluetooth {
  private:
    bool conn;                                  // Status of bluetooth connection
    unsigned char msg;                          // Msg last recieved
  public:
    Bluetooth();
    void set_conn(bool X);                      // To alter the connection state
    bool CONNECTION();                          // To get the status of the connection
    void set_msg(unsigned char ch);             // To update the latest msg.
    unsigned char MSG();                        // To return the msg.
};

class Braille_buffer {
  private:
    unsigned char cells[60];                    // Char array to store the braille cells
    bool buffer_empty = true;                   //
    int char_count;                             // Counter to keep track of cells recieved
    int index;                                  // Counter to keep track of cells recieved
  public:
    Braille_buffer();
    void load(unsigned char ch);                // To load the data into the cells
    void reset_index();                         // Reset the inde back to zero
    int count();                                // Return the count of the braille cells data currently present
};

void try_connect(unsigned char ch);
void process_msg();

extern Braille_buffer Cells;
extern Bluetooth BT;

#endif
