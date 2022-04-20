#ifndef Traffic_light_control_h
#define Traffic_light_control_h
#include "Arduino.h"

class Traffic_light_control{
    private:

    //byte G12;
    byte G3;
    byte G4;
    byte G5;
    byte G6;
    byte G7;
    byte SG3;
    byte SG4;
    byte SG7;
    byte SG12;
    //byte SR12;
    byte R12;
    byte R3;
    byte R4;
    byte R5;
    byte R6;
    byte R7;
    //byte Y12;
    byte Y3;
    byte Y4;
    byte Y5;
    byte Y6;
    byte Y7;
    int interval_A2;
    int interval_B2;
    int interval_C2;

    bool AtoC;
    bool BtoA;
    bool CtoB;
    bool finish_A;
    bool finish_B;
    bool finish_C;
    
    int yellow_time;
    int red_time;
    int redandyellow_time;

    bool finish_cross4;
    byte cross=6;
    int green_time_cross;
    int cross_repeat_timeout;

    unsigned long trl01;
    unsigned long trl02;
    unsigned long trl11;
    unsigned long trl12;
    unsigned long trl21;
    unsigned long trl22;
    unsigned long trl31;
    unsigned long trl32;
    unsigned long trl41;
    unsigned long trl42;
    unsigned long trl51;
    unsigned long trl52;
    unsigned long trl61;
    unsigned long trl62;
    unsigned long trl71;
    unsigned long trl72;
    unsigned long trl81;
    unsigned long trl82;
    unsigned long trl91;
    unsigned long trl92;
    unsigned long trl101;
    unsigned long trl102;
    unsigned long trl111;
    unsigned long trl112;
    unsigned long trl441;
    unsigned long trl442;
    unsigned long tc01;
    unsigned long tc02;
    unsigned long tc11;
    unsigned long tc12;
    unsigned long tc21;
    unsigned long tc22;
    unsigned long tc31;
    unsigned long tc32;
    unsigned long tc41;
    unsigned long tc42; 
    unsigned long tc51;
    unsigned long tc52;

    
    bool p1_A;
    bool p1_B;
    bool p1_C;
    bool p2_A;
    bool p2_B;
    bool p2_C;
    bool p3_A;
    bool p3_B;
    bool p3_C;

    unsigned long tp1;
    unsigned long tp2;
    unsigned long tp3;
    unsigned long tp4;
    unsigned long tp5;
    unsigned long tp6;
    unsigned long tp7;
    unsigned long tp8;



    public:

        Traffic_light_control(byte led_G12, byte led_G3, byte led_G4, byte led_G5, byte led_G6, byte led_G7,
        byte led_Y12, byte led_Y3, byte led_Y4, byte led_Y5, byte led_Y6, byte led_Y7,
        byte led_R12, byte led_R3, byte led_R4, byte led_R5, byte led_R6, byte led_R7,
        byte led_SG3, byte led_SG4, byte led_SG7, byte led_SR12, byte led_SG12, int yellow_time_set, int red_time_set, int redandyellow_time_set, int green_time_cross_set, int cross_repeat_timeout_set);

        
        byte G12;
        byte SR12;
        byte Y12;
        bool refresh;
        byte priority;
        byte traffic_light;
        bool waiting_A;
        bool waiting_B;
        bool waiting_C;
        bool reset_priority;
        bool crosswalk_off;
        bool all_yellow_high;
        bool all_yellow_low;
        bool everything_off;
        byte prioritisation=5;
        bool reset_priority_all;
        bool completed_A;
        bool completed_B;
        bool completed_C;
        int interval_A;
        int interval_B;
        int interval_C;
        bool reg_A_done;
        bool reg_B_done;
        bool reg_C_done;

        //promenne z inputs:
        //dochazi ke zmene, zde v cpp, k vynulovani:
        byte count_A_0;
        byte count_A_1;
        byte count_B_0;
        byte count_B_1;
        byte count_C_0;
        byte count_C_1;

        //zaroven se ovlivnuji: 
        byte sw_cross1_output; //++
        byte sw_cross2_output;
        bool cross_reg_not_repeat;

        //beru z:
        bool reg_A;
        bool reg_B;
        bool reg_C;
        byte emergency;
        byte idle;
        bool crossing_active;
        bool crossing_noactive;
        
        
      
        void PinSetup();
        void Sequence_main();
        void Sequence_crosswalk();
        void Prioritisation_IES();
};
#endif  