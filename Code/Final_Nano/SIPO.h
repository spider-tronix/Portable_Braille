#ifndef SIPO_H
#define SIPO_H
#include<Arduino.h>

#define TotalIC 10  
#define TotalICPins TotalIC * 8

class SipoClass {
    private:
        bool Data[TotalICPins];
    public:
        SipoClass();
        void ClearBuffer();
        void UpdateReg();
        void print_data();
        void set_data(unsigned char cell[], int pos[]);
};

void setEnable_PWM(int val);

extern SipoClass SIPO;
#endif
