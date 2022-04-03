#ifndef Inputs_h
#define Inputs_h
#include "Arduino.h"

class Inputs{
    private:

        
        int sensor1;
        int sensor2;
        int sensor3;
        int sensor4;
        int sensor5;
        int sensor6;
        int sensor_det;
        int time_sw;
        int time_se;
        int ind_det;
        int ind_sensor;
        byte BOP;
        byte L7OP;
        byte L8OP;

        byte se1s;
        byte se2s;
        byte se3s;
        byte se4s;
        byte se5s;
        byte se6s;
        byte sw1s;
        byte sw2s;
        byte sw3s;
        byte sw4s;
        byte sw5s;
        byte sw6s;
        byte sw7s;
        byte sw8s;
        byte swcross1s;
        byte swcross2s;
        byte sw1;
        byte sw2;
        byte sw3;
        byte sw4;
        byte sw5;
        byte sw6;
        byte sw7;
        byte sw8;
        byte sw_cross1;
        byte sw_cross2;
        char s1_pin;
        char s2_pin;
        char s3_pin;
        char s4_pin;
        char s5_pin;
        char s6_pin;
        char sind_pin;
        
        unsigned long sw1t1;
        unsigned long sw1t2;
        unsigned long sw2t1;
        unsigned long sw2t2;
        unsigned long sw3t1;
        unsigned long sw3t2;
        unsigned long sw4t1;
        unsigned long sw4t2;
        unsigned long sw5t1;
        unsigned long sw5t2;
        unsigned long sw6t1;
        unsigned long sw6t2;
        unsigned long sw7t1;
        unsigned long sw7t2;
        unsigned long sw8t1;
        unsigned long sw8t2;
        unsigned long swcross1t1;
        unsigned long swcross1t2;
        unsigned long swcross2t1;
        unsigned long swcross2t2;

        unsigned long se1t1;
        unsigned long se1t2;
        unsigned long se2t1;
        unsigned long se2t2;
        unsigned long se3t1;
        unsigned long se3t2;
        unsigned long se4t1;
        unsigned long se4t2;
        unsigned long se5t1;
        unsigned long se5t2;
        unsigned long se6t1;
        unsigned long se6t2;
        
    public:

        Inputs(char ind_sensor_pin, char sensor1_pin, char sensor2_pin, char sensor3_pin, char sensor4_pin, char sensor5_pin, char sensor6_pin, 
        int sensor_detect, int ind_sensor_detect, int time_switches, int time_sensors, byte ind_LED_OP, byte L7OP_pin, byte L8OP_pin,
        byte sw1_pin,byte sw2_pin,byte sw3_pin,byte sw4_pin,byte sw5_pin,byte sw6_pin,byte sw7_pin,byte sw8_pin, byte sw_cross1_pin, byte sw_cross2_pin);
        
        //public promenne jen zde
        byte count_A;
        byte count_B;
        byte count_C;
        byte reg_A;
        byte reg_B;
        byte reg_C;
        byte sw_cross1_output;//i
        byte sw_cross2_output;//j
        byte idle;
        byte emergency;
        byte refresh;
        byte crossing_active;
        

        //promenne, z kterych si bereme
        byte traffic_light;
        byte priority;

        byte cross_reg_not_repeat;
        
        void PinSetup();
        void Sequence_in_idle();
        void Sequence_out_of_idle();
        void Sequence_change_free_state_reg();
        
};
#endif  