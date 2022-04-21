#ifndef VO_h
#define VO_h
#include "Arduino.h"

class VO{
    private:

        bool VO_switched;
        byte W1;
        byte W2;
        byte W3;
        byte foto;
        int foto_det;
        int foto_sensor;
        int analog_foto;
        int convince;
        unsigned long foto_t1;
        unsigned long foto_t2;
        unsigned long foto_t3;
        unsigned long foto_t4;


    public:

        VO(byte led_W1, byte led_W2, byte led_W3, char analog_pin_fotoresistor, int foto_detect, int convince_time);
	    void PinSetup();
        void Sequence();
        
};
#endif  

