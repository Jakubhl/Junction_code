
#include "Arduino.h"
#include "Inputs.h"

Inputs::Inputs(char ind_sensor_pin, char sensor1_pin, char sensor2_pin, char sensor3_pin, char sensor4_pin, char sensor5_pin, char sensor6_pin, 
int sensor_detect, int ind_sensor_detect, int time_switches, int time_sensors, byte ind_LED_OP, byte L7OP_pin, byte L8OP_pin,
byte sw1_pin,byte sw2_pin,byte sw3_pin,byte sw4_pin,byte sw5_pin,byte sw6_pin,byte sw7_pin,byte sw8_pin, byte sw_cross1_pin, byte sw_cross2_pin){

    s1_pin=sensor1_pin;
    s2_pin=sensor2_pin;
    s3_pin=sensor3_pin;
    s4_pin=sensor4_pin;
    s5_pin=sensor5_pin;
    s6_pin=sensor6_pin;
    sind_pin=ind_sensor_pin;
    sensor_det=sensor_detect;
    time_sw=time_switches;
    time_se=time_sensors;
    ind_det=ind_sensor_detect;
    BOP=ind_LED_OP;
    L7OP=L7OP_pin;
    L8OP=L8OP_pin;
    sw1=sw1_pin;
    sw2=sw2_pin;
    sw3=sw3_pin;
    sw4=sw4_pin;
    sw5=sw5_pin;
    sw6=sw6_pin;
    sw7=sw7_pin;
    sw8=sw8_pin;
    sw_cross1=sw_cross1_pin;
    sw_cross2=sw_cross2_pin;
    
    }

void Inputs::PinSetup(){

    pinMode(BOP, OUTPUT);
    pinMode(L7OP, OUTPUT);
    pinMode(L8OP, OUTPUT);

    pinMode(sw_cross1, INPUT_PULLUP);
    pinMode(sw_cross2, INPUT_PULLUP);
    pinMode(sw1, INPUT_PULLUP);
    pinMode(sw2, INPUT_PULLUP);
    pinMode(sw3, INPUT_PULLUP);
    pinMode(sw4, INPUT_PULLUP);
    pinMode(sw5, INPUT_PULLUP);
    pinMode(sw6, INPUT_PULLUP);
    pinMode(sw7, INPUT_PULLUP);
    pinMode(sw8, INPUT_PULLUP);
}

void Inputs::Sequence_change_free_state_reg(){

//snímání požadavku z jiných směrů...-----------------------------------------------------------------------------------------------------------------------
  //spínači i čidly -> jsou zohledněné doplňkové šipky -> kde projíždějí vozidla na zelenou, není registrován požadavek
  //zakomentované senzory mají vyklizovací šipkou zelenou
  //tímto způsobem se získávájí nejaktuálnější data
  //pro směr A:

  if (traffic_light == 0 || traffic_light == 1 || traffic_light == 9 || traffic_light == 10 || traffic_light == 11) {
    if (reg_B == false) {
      //if(sensor3<sensor_detect){reg_B=1;refresh=1;}
      if (sensor4 < sensor_det) {
        reg_B = true;
        refresh = true;
      }
      //if(digitalRead(sw3)==LOW){reg_B=1;refresh=1;}
      if (digitalRead(sw4) == LOW) {
        reg_B = true;
        refresh = true;
      }
    }
    if (reg_C == false) {
      //if(sensor5<sensor_detect){reg_C=1;refresh=1;}
      if (sensor6 < sensor_det) {
        reg_C = true;
        refresh = true;
      }
      if (ind_sensor > ind_det) {
        reg_C = true;
        refresh = true;
      }
      //if(digitalRead(sw5)==LOW){reg_C=1;refresh=1;}
      if (digitalRead(sw6) == LOW) {
        reg_C = true;
        refresh = true;
      }
    }
  }
  //detekce pro směr B
  if (traffic_light == 2 || traffic_light == 3 || traffic_light == 4 || traffic_light == 44) {
    if (reg_A == false) {
      if (sensor1 < sensor_det) {
        reg_A = true;
        refresh = true;
      }
      if (sensor2 < sensor_det) {
        reg_A = true;
        refresh = true;
      }
      if (digitalRead(sw1) == LOW) {
        reg_A = true;
        refresh = true;
      }
      if (digitalRead(sw2) == LOW) {
        reg_A = true;
        refresh = true;
      }
    }
    if (reg_C == false) {
      //if(sensor5<sensor_detect){reg_C=1;refresh=1;}
      if (sensor6 < sensor_det) {
        reg_C = true;
        refresh = true;
      }
      if (ind_sensor > ind_det) {
        reg_C = true;
        refresh = true;
      }
      //if(digitalRead(sw5)==LOW){reg_C=1;refresh=1;}
      if (digitalRead(sw6) == LOW) {
        reg_C = true;
        refresh = true;
      }
    }
  }
  //detekce pro směr C
  if (traffic_light == 5 || traffic_light == 6 || traffic_light == 7 || traffic_light == 8) {
    if (reg_A == false) {
      if (sensor1 < sensor_det) {
        reg_A = true;
        refresh = true;
      }
      //if(sensor2<sensor_detect){reg_A=1;refresh=1;}
      if (digitalRead(sw1) == LOW) {
        reg_A = true;
        refresh = true;
      }
      //if(digitalRead(sw2)==LOW){reg_A=1;refresh=1;}
    }
    if (reg_B == false) {
      if (sensor3 < sensor_det) {
        reg_B = true;
        refresh = true;
      }
      if (sensor4 < sensor_det) {
        reg_B = true;
        refresh = true;
      }
      if (digitalRead(sw3) == LOW) {
        reg_B = true;
        refresh = true;
      }
      if (digitalRead(sw4) == LOW) {
        reg_B = true;
        refresh = true;
      }
    }
  }

}


void Inputs::Sequence_in_idle(){

//čtení tlačítek nastavujicich idle a emergency stav------------------------------------------------------------------------------------------------------

switch (sw7s) {
    case 0: if (digitalRead(sw7) == LOW) {
        sw7t1 = millis();
        if (emergency == 0 && priority == 0) {
          idle++;
        } digitalWrite(L7OP, HIGH);
        sw7s = 1;
      }
      break;
    case 1: sw7t2 = millis(); if (sw7t2 - sw7t1 > time_sw) {
        sw7s = 2;
      }
      break;
    case 2: if (digitalRead(sw7) == HIGH) {
        digitalWrite(L7OP, LOW);
        sw7s = 0;
      }
      break;
  }

  switch (sw8s) {
    case 0: if (digitalRead(sw8) == LOW) {
        sw8t1 = millis(); if (priority == 0) {
          emergency++;
        } digitalWrite(L8OP, HIGH); sw8s = 1;
      }
      break;
    case 1: sw8t2 = millis();
      if (sw8t2 - sw8t1 > time_sw) {
        sw8s = 2;
      }
      break;
    case 2: if (digitalRead(sw8) == HIGH) {
        digitalWrite(L8OP, LOW);
        sw8s = 0;
      }
      break;
  }
}

void Inputs::Sequence_out_of_idle(){

//čtení senzorů a tlačítek------------------------------------------------------------------------------------------------------

    sensor1 = analogRead(s1_pin);
    sensor2 = analogRead(s2_pin);
    sensor3 = analogRead(s3_pin);
    sensor4 = analogRead(s4_pin);
    sensor5 = analogRead(s5_pin);
    sensor6 = analogRead(s6_pin); 

      ind_sensor = analogRead(sind_pin);
  if (ind_sensor > ind_det) {
    digitalWrite(BOP, HIGH);
  }
  else {
    digitalWrite(BOP, LOW);
  }
	
    switch (se1s) {
      case 0: if (sensor1 < sensor_det) {
          se1t1 = millis();
          if (traffic_light == 1 && crossing_active == false) {
            count_A++;refresh = true;
          }
          
          se1s = 1;
        }
        break;
      case 1: se1t2 = millis(); if (se1t2 - se1t1 > time_se) {
          se1s = 2;
        }
        break;
      case 2: if (sensor1 > sensor_det) {
          se1s = 0;
        }
        break;
    }
    switch (se2s) {
      case 0: if (sensor2 < sensor_det) {
          se2t1 = millis();
          if (traffic_light == 1 && crossing_active == false) {
            count_A++;refresh = true;
          } 
          se2s = 1;
        }
        break;
      case 1: se2t2 = millis(); if (se2t2 - se2t1 > time_se) {
          se2s = 2;
        }
        break;
      case 2: if (sensor2 > sensor_det) {
          se2s = 0;
        }
        break;
    }
    switch (se3s) {
      case 0: if (sensor3 < sensor_det) {
          se3t1 = millis();
          if (traffic_light == 4) {
            count_B++;refresh = true;
          } 
          se3s = 1;
        }
        break;
      case 1: se3t2 = millis(); if (se3t2 - se3t1 > time_se) {
          se3s = 2;
        }
        break;
      case 2: if (sensor3 > sensor_det) {
          se3s = 0;
        }
        break;
    }
    switch (se4s) {
      case 0: if (sensor4 < sensor_det) {
          se4t1 = millis();
          if (traffic_light == 4) {
            count_B++;refresh = true;
          } 
          se4s = 1;
        }
        break;
      case 1: se4t2 = millis(); if (se4t2 - se4t1 > time_se) {
          se4s = 2;
        }
        break;
      case 2: if (sensor4 > sensor_det) {
          se4s = 0;
        }
        break;
    }
    switch (se5s) {
      case 0: if (sensor5 < sensor_det) {
          se5t1 = millis();
          if (traffic_light == 8) {
            count_C++;refresh = true;
          } 
          se5s = 1;
        }
        break;
      case 1: se5t2 = millis(); if (se5t2 - se5t1 > time_se) {
          se5s = 2;
        }
        break;
      case 2: if (sensor5 > sensor_det) {
          se5s = 0;
        }
        break;
    }
    switch (se6s) {
      case 0: if (sensor6 < sensor_det) {
          se6t1 = millis();
          if (traffic_light == 8) {
            count_C++;refresh = true;
          } 
          se6s = 1;
        }
        if (ind_sensor > ind_det) {
          se6t1 = millis();
          if (traffic_light == 8) {
            count_C++;refresh = true;
          } 
          se6s = 3;
        }
        break;
      case 1: se6t2 = millis(); if (se6t2 - se6t1 > time_se) {
          se6s = 2;
        }
        break;
      case 2: if (sensor6 > sensor_det) {
          se6s = 0;
        }
        break;
      case 3: se6t2 = millis(); if (se6t2 - se6t1 > time_se) {
          se6s = 4;
        }
        break;
      //ceka se az vozidlo opusti obe cidla aby se nepricetlo dvakrat
      case 4: if (ind_sensor < ind_det && sensor6 > sensor_det) {
          se6s = 0;
        }
        break;
    }

    switch (sw1s) {
      case 0: if (digitalRead(sw1) == LOW) {
          sw1t1 = millis();
          if (traffic_light == 1) {
            count_A++;refresh = true;
          };
          
          sw1s = 1;
        }
        break;
      case 1: sw1t2 = millis(); if (sw1t2 - sw1t1 > time_sw) {
          sw1s = 2;
        }
        break;
      case 2: if (digitalRead(sw1) == HIGH) {
          sw1s = 0;
        }
        break;
    }

    switch (sw2s) {
      case 0: if (digitalRead(sw2) == LOW) {
          sw2t1 = millis();
          if (traffic_light == 1 && crossing_active == false) {
            count_A++;refresh = true;
          };
          
          sw2s = 1;
        }
        break;
      case 1: sw2t2 = millis(); if (sw2t2 - sw2t1 > time_sw) {
          sw2s = 2;
        }
        break;
      case 2: if (digitalRead(sw2) == HIGH) {
          sw2s = 0;
        }
        break;
    }
    switch (sw3s) {
      case 0: if (digitalRead(sw3) == LOW) {
          sw3t1 = millis();
          if (traffic_light == 4) {
            count_B++;refresh = true;
          } 
          sw3s = 1;
        }
        break;
      case 1: sw3t2 = millis(); if (sw3t2 - sw3t1 > time_sw) {
          sw3s = 2;
        }
        break;
      case 2: if (digitalRead(sw3) == HIGH) {
          sw3s = 0;
        }
        break;
    }
    switch (sw4s) {
      case 0: if (digitalRead(sw4) == LOW) {
          sw4t1 = millis();
          if (traffic_light == 4) {
            count_B++;refresh = true;
          } 
          sw4s = 1;
        }
        break;
      case 1: sw4t2 = millis(); if (sw4t2 - sw4t1 > time_sw) {
          sw4s = 2;
        }
        break;
      case 2: if (digitalRead(sw4) == HIGH) {
          sw4s = 0;
        }
        break;
    }
    switch (sw5s) {
      case 0: if (digitalRead(sw5) == LOW) {
          sw5t1 = millis();
          if (traffic_light == 8) {
            count_C++;refresh = true;
          } 
          sw5s = 1;
        }
        break;
      case 1: sw5t2 = millis(); if (sw5t2 - sw5t1 > time_sw) {
          sw5s = 2;
        }
        break;
      case 2: if (digitalRead(sw5) == HIGH) {
          sw5s = 0;
        }
        break;
    }
    switch (sw6s) {
      case 0: if (digitalRead(sw6) == LOW) {
          sw6t1 = millis();
          if (traffic_light == 8) {
            count_C++;refresh = true;
          } 
          sw6s = 1;
        }
        break;
      case 1: sw6t2 = millis(); if (sw6t2 - sw6t1 > time_sw) {
          sw6s = 2;
        }
        break;
      case 2: if (digitalRead(sw6) == HIGH) {
          sw6s = 0;
        }
        break;
    }
    //sw7, 8 je mimo podminku: "pouze pokud neni necinny stav"

    switch (swcross1s) {
      case 0: if (digitalRead(sw_cross1) == LOW) {
          swcross1t1 = millis();
          sw_cross1_output++;
          swcross1s = 1;
        }
        break;
      case 1: swcross1t2 = millis(); if (swcross1t2 - swcross1t1 > time_sw) {
          swcross1s = 2;
        }
        break;
      case 2: if (digitalRead(sw_cross1) == HIGH) {
          swcross1s = 0;
        }
        break;
    }
    switch (swcross2s) {
      case 0: if (digitalRead(sw_cross2) == LOW) {
          swcross2t1 = millis();
          sw_cross2_output++;
          swcross2s = 1;
        }
        break;
      case 1: swcross2t2 = millis(); if (swcross2t2 - swcross2t1 > time_sw) {
          swcross2s = 2;
        }
        break;
      case 2: if (digitalRead(sw_cross2) == HIGH) {
          swcross2s = 0;
        }
        break;
    }
  //CROSSING-----------------------------------------------------------------------------------------------------------------------------
  //registrace pozadavku na prechod, osetreni proti neustalemu vypisovani na display

  if (sw_cross1_output  != 0) {
    crossing_active = true;
    if (cross_reg_not_repeat == false) {
      refresh = true;
      cross_reg_not_repeat = true;
    }
  }
  if (sw_cross2_output  != 0) {
    crossing_active = true;
    if (cross_reg_not_repeat == false) {
      refresh = true;
      cross_reg_not_repeat = true;
    }
  }
}