#include "Arduino.h"
#include "Traffic_light_control.h"


Traffic_light_control::Traffic_light_control(
        byte led_G12, byte led_G3, byte led_G4, byte led_G5, byte led_G6, byte led_G7,
        byte led_Y12, byte led_Y3, byte led_Y4, byte led_Y5, byte led_Y6, byte led_Y7,
        byte led_R12, byte led_R3, byte led_R4, byte led_R5, byte led_R6, byte led_R7,
        byte led_SG3, byte led_SG4, byte led_SG7, byte led_SR12, byte led_SG12, int yellow_time_set, int red_time_set, int redandyellow_time_set, int green_time_cross_set, int cross_repeat_timeout_set){

    G12=led_G12;
    G3=led_G3;
    G4=led_G4;
    G5=led_G5;
    G6=led_G6;
    G7=led_G7;
    Y12=led_Y12;
    Y3=led_Y3;
    Y4=led_Y4;
    Y5=led_Y5;
    Y6=led_Y6;
    Y7=led_Y7;
    R12=led_R12;
    R3=led_R3;
    R4=led_R4;
    R5=led_R5;
    R6=led_R6;
    R7=led_R7;
    SG3=led_SG3;
    SG4=led_SG4;
    SG7=led_SG7;
    SR12=led_SR12;
    SG12=led_SG12;
    yellow_time=yellow_time_set;
    red_time=red_time_set;
    redandyellow_time=redandyellow_time_set;
    green_time_cross=green_time_cross_set;
    cross_repeat_timeout=cross_repeat_timeout_set;

    };


void Traffic_light_control::PinSetup(){
    pinMode(G12, OUTPUT);
    pinMode(G3, OUTPUT);
    pinMode(G4, OUTPUT); 
    pinMode(G5, OUTPUT); 
    pinMode(G6, OUTPUT); 
    pinMode(G7, OUTPUT); 
    pinMode(R12, OUTPUT);
    pinMode(R3, OUTPUT);
    pinMode(R4, OUTPUT);
    pinMode(R5, OUTPUT);
    pinMode(R6, OUTPUT);
    pinMode(R7, OUTPUT);
    pinMode(Y12, OUTPUT);
    pinMode(Y3, OUTPUT); 
    pinMode(Y4, OUTPUT); 
    pinMode(Y5, OUTPUT); 
    pinMode(Y6, OUTPUT);
    pinMode(Y7, OUTPUT);  
    pinMode(SG3,OUTPUT);
    pinMode(SG4,OUTPUT);
    pinMode(SG7,OUTPUT);
    pinMode(SG12,OUTPUT);
    pinMode(SR12,OUTPUT);

    //prechod je treba manualne sepnout pri sepnuti
    //digitalWrite(G12,HIGH);
    //digitalWrite(SR12,HIGH);
	
}

void Traffic_light_control::Sequence_main(){

  if(all_yellow_high==true){
    digitalWrite(Y3, HIGH);
    digitalWrite(Y4, HIGH);
    digitalWrite(Y5, HIGH);
    digitalWrite(Y6, HIGH);
    digitalWrite(Y7, HIGH);
    all_yellow_high=false;
  }

  if(all_yellow_low==true){
    digitalWrite(Y3, LOW);
    digitalWrite(Y4, LOW);
    digitalWrite(Y5, LOW);
    digitalWrite(Y6, LOW);
    digitalWrite(Y7, LOW);
    all_yellow_low=false;
  }
  if(everything_off==true){
    digitalWrite(G3, LOW);
    digitalWrite(G4, LOW);
    digitalWrite(G5, LOW);
    digitalWrite(G6, LOW);
    digitalWrite(G7, LOW);
    digitalWrite(Y12, LOW); //reset po idle stavu musim i zlutou na prechodu vynulovat
    digitalWrite(Y3, LOW);
    digitalWrite(Y4, LOW);
    digitalWrite(Y5, LOW);
    digitalWrite(Y6, LOW);
    digitalWrite(Y7, LOW);
    digitalWrite(R3, LOW);
    digitalWrite(R4, LOW);
    digitalWrite(R5, LOW);
    digitalWrite(R6, LOW);
    digitalWrite(R7, LOW);
    digitalWrite(SG3, LOW);
    digitalWrite(SG4, LOW);
    digitalWrite(SG7, LOW);
    AtoC=false;
    BtoA=false;
    CtoB=false;
    completed_A = false; completed_B = false; completed_C = false;
    interval_A2 = 0; interval_B2 = 0; interval_C2 = 0;
    finish_A = false;finish_B = false;finish_C = false;
    everything_off=false;
  }


  //sekvence řízení ----------------------------------------------------------------------------------------------------------------------------------------------------
  //umozneno preskakovat mezi jednotlivými stavy, zohlednovat prechod pres skutecnost zadne detekce vozidel, prizpusobeny interval aktualnimu provozu
  switch (traffic_light) {
    //SMER A:
    case 0:
      trl01 = millis();
      if (reg_A == false) {
        count_A_0 = 1;
      } else {
        count_A_1 = 1;
      }
      refresh = true;
      traffic_light = 1;
      break;
    case 1: //GREEN DIRECTION A-----------------------------------------------------------------------------------------------------------------------

      if (finish_A == false) {
        refresh=true;
        reg_A = false;reg_A_done=true;
        digitalWrite(G6, HIGH); digitalWrite(G7, HIGH); digitalWrite(SG4, HIGH); digitalWrite(SG3, HIGH);
        digitalWrite(Y6, LOW); digitalWrite(Y7, LOW);
        digitalWrite(R3, HIGH); digitalWrite(R4, HIGH); digitalWrite(R5, HIGH);
        digitalWrite(R6, LOW); digitalWrite(R7, LOW);
        finish_A = true;
      }
      if (crossing_active == false) {
        BtoA = false;
      }

      if (crossing_active == false) {
        trl02 = millis();
        //osetreni proti maximalnimu intervalu na zacatku (první zelená v danem smeru, krizovatka se jeste uci)
        if (completed_A == true && emergency == 0) {
          interval_A2 = (interval_A * 1000);
        } else {
          interval_A2 = 10000;
        }
        if (trl02 - trl01 > interval_A2) {
          if (emergency == 1) {
            trl11 = millis();
            finish_A=false;traffic_light = 2;
          }
          else {
            waiting_A = true;
          }
        }
      }
      //setrvání v daném stavu, než bude registrováno vozidlo z jinych smeru
      if (waiting_A == true) {
        if (reg_C == true && reg_B == false) {
          if (crossing_active == false) {
            completed_A = true;
            BtoA = false;
            waiting_A = false;
            trl41 = millis();
            AtoC = true;
            count_B_0 = 1;
            refresh = true;
            finish_A = false;traffic_light = 5;
          }
        }
        if (reg_B == true && reg_C == false) {
          if (crossing_active == false) {
            completed_A = true;
            BtoA = false;
            waiting_A = false;
            trl11 = millis();
            AtoC = false;
            finish_A = false;traffic_light = 2;
          }
        }
        if (reg_B == true && reg_C == true) {
          if (crossing_active == false) {
            completed_A = true;
            BtoA = false;
            waiting_A = false;
            trl11 = millis();
            AtoC = false;
            finish_A = false;traffic_light = 2;
          }
        }
      }

      break;
    case 2: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------
      //mohu dvěma směry bud z A do B (CtoB==0) nebo z C preskocit A do B (CtoB==1)

      
      if (CtoB == true) {
        digitalWrite(G5, LOW); digitalWrite(G6, LOW);
        digitalWrite(Y5, HIGH); digitalWrite(Y6, HIGH);
      }
      if (CtoB == false) {
        digitalWrite(G6, LOW); digitalWrite(G7, LOW);
        digitalWrite(Y6, HIGH); digitalWrite(Y7, HIGH);
      }

      trl12 = millis();
      if (trl12 - trl11 > yellow_time) {
        trl21 = millis();
        traffic_light = 3;
      }
      break;
    case 3: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (CtoB == true) {
        digitalWrite(Y5, LOW); digitalWrite(Y6, LOW);
        digitalWrite(R5, HIGH); digitalWrite(R6, HIGH);
      }
      if (CtoB == false) {
        digitalWrite(Y6, LOW); digitalWrite(Y7, LOW);
        digitalWrite(R6, HIGH); digitalWrite(R7, HIGH);
      }
      //pocita to s jednim autem kdyz bylo zaregistrovano
      trl22 = millis();
      if (trl22 - trl21 > red_time) {
        trl441 = millis();
        traffic_light = 44;
      }
      break;
    case 44://RED + YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (CtoB == true) {
        digitalWrite(Y4, HIGH);
      }
      if (CtoB == false) {
         digitalWrite(Y3, HIGH); digitalWrite(Y4, HIGH);
      }
      trl442 = millis();
      if (trl442 - trl441 > redandyellow_time) {
        trl31 = millis(); if (reg_B == false) {
          count_B_0 = 1;
        } else {
          count_B_1 = 1;
        };
        refresh = true; traffic_light = 4;
      }

      break;
    case 4: //GREEN DIRECTION B-----------------------------------------------------------------------------------------------------------------------
      CtoB = false;
      reg_B = false;reg_B_done=true;
      if(finish_B==false){
      if (CtoB == false) {
        digitalWrite(SG4, LOW);digitalWrite(SG3, LOW);
      }
      digitalWrite(G3, HIGH); digitalWrite(G4, HIGH); digitalWrite(SG7, HIGH);
      digitalWrite(Y3, LOW); digitalWrite(Y4, LOW);
      digitalWrite(R3, LOW); digitalWrite(R4, LOW);
      finish_B=true;}
      
      trl32 = millis();
      if (completed_B == true && emergency == 0) {
        interval_B2 = (interval_B * 1000);
      } else {
        interval_B2 = 10000;
      };
      if (trl32 - trl31 > interval_B2) {
        if (emergency == 1) {
          trl41 = millis();
          finish_B=false;traffic_light = 5;
        }
        else {
          waiting_B = true;
        }
      }

      if (waiting_B == true) {
        if (reg_A == true && reg_C == false) {
          completed_B = true;
          waiting_B = false;
          trl91 = millis();
          BtoA = true;
          count_C_0 = 1;
          refresh = true;
          finish_B=false;traffic_light = 9;
        }
        if (crossing_active == true && reg_C == false) {
          completed_B = true;
          waiting_B = false;
          trl91 = millis();
          BtoA = true;
          count_C_0 = 1;
          refresh = true;
          finish_B=false;traffic_light = 9;
        }
        if (reg_C == true && reg_A == false) {
          completed_B = true;
          waiting_B = false;
          trl41 = millis();
          BtoA = false;
          finish_B=false;traffic_light = 5;
        }
        if (reg_C == true && reg_A == true) {
          completed_B = true;
          waiting_B = false;
          trl41 = millis();
          BtoA = false;
          finish_B=false;traffic_light = 5;
        }
      }

      break;
    case 5: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      

      if (AtoC == true) {
        digitalWrite(G7, LOW);
        digitalWrite(Y7, HIGH);
        digitalWrite(SG4, LOW);

      }
      //BtoC
      if (AtoC == false) {
        digitalWrite(SG4, LOW);
        digitalWrite(SG7, LOW);
        digitalWrite(G4, LOW);
        digitalWrite(Y4, HIGH);
      }
      trl42 = millis();
      if (trl42 - trl41 > yellow_time) {
        trl61 = millis();
        traffic_light = 6;
      }
      break;
    case 6: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (AtoC == true) {

        digitalWrite(Y7, LOW);
        digitalWrite(R7, HIGH);
      }
      if (AtoC == false) {

        digitalWrite(Y4, LOW);
        digitalWrite(R4, HIGH);
      }
      trl62 = millis();
      if (trl62 - trl61 > red_time) {
        trl71 = millis();
        traffic_light = 7;
      }

      break;
    case 7: //YELLOW + RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (AtoC == true) {
        digitalWrite(SG3, LOW);
        digitalWrite(Y3, HIGH); digitalWrite(Y5, HIGH);

      }
      if (AtoC == false) {
        digitalWrite(Y5, HIGH); digitalWrite(Y6, HIGH);
      }
      trl72 = millis();
      if (trl72 - trl71 > redandyellow_time) {
        trl81 = millis(); if (reg_C == false) {
          count_C_0 = 1;
        } else {
          count_C_1 = 1;
        };
        refresh = true; traffic_light = 8;
      }

      break;
    case 8: //GREEN DIRECTION C-----------------------------------------------------------------------------------------------------------------------

      reg_C = false;reg_C_done=true;
      AtoC = false;
      if(finish_C==false){
      digitalWrite(G3, HIGH); digitalWrite(G5, HIGH); digitalWrite(G6, HIGH); digitalWrite(SG3, LOW);
      digitalWrite(Y3, LOW); digitalWrite(Y5, LOW); digitalWrite(Y6, LOW);
      digitalWrite(R3, LOW); digitalWrite(R5, LOW); digitalWrite(R6, LOW);
      finish_C=true;}
      
      trl82 = millis();
      if (completed_C == true && emergency == 0) {
        interval_C2 = (interval_C * 1000);
      } else {
        interval_C2 = 10000;
      };
      if (trl82 - trl81 > interval_C2) {
        if (emergency == 1) {
          trl91 = millis();
          finish_C=false;traffic_light = 9;
        }
        else {
          waiting_C = true;
        }
      }

      if (waiting_C == true) {
        if (reg_B == true && reg_A == false) {
          completed_C = true;
          waiting_C = false;
          trl11 = millis();
          CtoB = true;
          count_A_0 = 1;
          refresh = true;
          finish_C=false;traffic_light = 2;
        }
        if (reg_A == true && reg_B == false) {
          completed_C = true;
          waiting_C = false;
          trl91 = millis();
          CtoB = false;
          finish_C=false;traffic_light = 9;
        }
        if (reg_A == true && reg_B == true) {
          completed_C = true;
          waiting_C = false;
          trl91 = millis();
          CtoB = false;
          finish_C=false;traffic_light = 9;
        }
        if (crossing_active == true) {
          completed_C = true;
          waiting_C = false;
          trl91 = millis();
          CtoB = false;
          finish_C=false;traffic_light = 9;
        }
      }
      break;
    case 9: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (BtoA == true) {
        digitalWrite(SG7, LOW);
        digitalWrite(G3, LOW); digitalWrite(G4, LOW);
        digitalWrite(Y3, HIGH); digitalWrite(Y4, HIGH);
      }
      if (BtoA == false) {
        digitalWrite(G3, LOW); digitalWrite(G5, LOW);
        digitalWrite(Y3, HIGH); digitalWrite(Y5, HIGH);
      }
      trl92 = millis();
      if (trl92 - trl91 > yellow_time) {
        trl101 = millis();
        traffic_light = 10;
      }
      break;
    case 10: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (BtoA == true) {
        digitalWrite(Y3, LOW); digitalWrite(Y4, LOW); digitalWrite(SG3, HIGH); digitalWrite(SG4, HIGH);
        digitalWrite(R3, HIGH); digitalWrite(R4, HIGH);
      }
      if (BtoA == false) {
        digitalWrite(Y3, LOW); digitalWrite(Y5, LOW); digitalWrite(SG3, HIGH);
        digitalWrite(R3, HIGH); digitalWrite(R5, HIGH);
      }
      trl102 = millis();
      if (trl102 - trl101 > red_time) {
        trl111 = millis();
        traffic_light = 11;
      }

      break;
    case 11://RED + YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------
      if (BtoA == true) {
        digitalWrite(Y6, HIGH); digitalWrite(Y7, HIGH); digitalWrite(SG7, LOW);
      }
      if (BtoA == false) {
        digitalWrite(Y7, HIGH); digitalWrite(SG7, LOW);
      }

      trl112 = millis();
      if (trl112 - trl111 > redandyellow_time) {
        traffic_light = 0;
      }
      break;
    case 12:
      //neutral state
      break;
  }

}

void Traffic_light_control::Sequence_crosswalk(){

    //CROSSING----------------------------------------------------------------------------------------------------------------------------
if(crosswalk_off==true){
  digitalWrite(R12, LOW);
  digitalWrite(G12, LOW);
  digitalWrite(Y12, LOW);
  digitalWrite(SR12, LOW);
  digitalWrite(SG12, LOW);
  crosswalk_off=false;}

  //podminka pro umozneni spusteni prechodu: (muselo být: spusteno tlacitko prechodu, musi být: rizeni v jednicce(smerA), instrukce pro směr A musely být vykonány, prechod musel byt dokoncen minimalne pred 10s a nesmí probíhat prioritizace)
  if (crossing_active == true && traffic_light == 1 && cross == 6 && finish_A == true && finish_cross4 == false && priority == 0) {
    tc01 = millis();
    cross = 0;
  };

  switch (cross) {
    //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------------
    case 0:
      //if(idle==0 && BtoA==0){digitalWrite(G6,LOW);digitalWrite(Y6,HIGH);}
      digitalWrite(G12, LOW);
      digitalWrite(Y12, HIGH);
      tc02 = millis();
      if (tc02 - tc01 > yellow_time) {
        tc11 = millis();
        cross = 1;
      }

      break;
    //RED SEQUENCE--------------------------------------------------------------------------------------------------------------------------
    //na prechodu je red sequence delsi kvuli bezpecnosti
    case 1:
      //if(idle==0 && BtoA==0){digitalWrite(Y6,LOW);digitalWrite(R6,HIGH);}
      digitalWrite(Y12, LOW);
      digitalWrite(R12, HIGH);
      tc12 = millis();
      if (tc12 - tc11 > 3000) {
        tc21 = millis();
        cross = 2;
      }

      break;
    //GREEN SEQUENCE-----------------------------------------------------------------------------------------------------------------------
    case 2:

      digitalWrite(SG12, HIGH);
      digitalWrite(SR12, LOW);
      if (priority != 0) {
        cross = 3; //preskoceni zelene na prechodu kdyz projizdi IZS
      }
      tc22 = millis();
      if (tc22 - tc21 > green_time_cross) {
        tc31 = millis();
        cross = 3;
      }
      //real = 10s

      break;
    //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------
    case 3:
      digitalWrite(SG12, LOW);
      digitalWrite(SR12, HIGH);
      tc32 = millis();
      if (tc32 - tc31 > 2000) {
        tc41 = millis();
        cross = 4;
      }

      break;
      
    //YELLOW SEQUENCE------------------------------------------------------------------------------------------------------------------------
    case 4:
      //if(idle==0){digitalWrite(Y6,HIGH);}
      digitalWrite(Y12, HIGH);
      tc42 = millis();
      if (tc42 - tc41 > yellow_time) {
        tc51 = millis();
        cross = 5;
      }

      break;
    case 5:
      if (finish_cross4 == false) {
        //if(idle==0){digitalWrite(G6,HIGH);digitalWrite(Y6,LOW);digitalWrite(R6,LOW);waiting_A=1;}
        if (idle == 0) {
          waiting_A = true;
        }
        digitalWrite(G12, HIGH);
        digitalWrite(Y12, LOW);
        digitalWrite(R12, LOW);
        BtoA = false; sw_cross1_output = 1; sw_cross2_output = 1; cross_reg_not_repeat = true; refresh = true; crossing_active = false;crossing_noactive=true;
        finish_cross4 = true;
      }
      //osetreni proti opakovani, aby se nespustil přechod hned znovu, čekání (cross_repeat_timeout)
      tc52 = millis();
      if (tc52 - tc51 > cross_repeat_timeout) {
        cross = 6;
      }

      break;
    case 6:

      finish_cross4 = false;
      //umozneno dalsi spusteni
      //stand-by
      break;
  }

}

void Traffic_light_control::Prioritisation_IES(){
//PRIORITIZACE IZS------------------------------------------------------------------------------------------------------------------------------------------
//nejprve se navaze na aktualni situaci, potom se prispusobuji SSZ tak aby byl prujezdny stav pouze v jednom smeru
  switch (prioritisation) {
    case 0:

      if (priority == 1 && traffic_light == 1) {
        tp1 = millis(); p1_A = true;  if(finish_A==true){traffic_light = 12;prioritisation = 1;} //když nebyla tato podmínka nestihly se přepnout LEDky
      }
      if (priority == 1 && traffic_light == 4) {
        tp1 = millis(); p1_B = true;  if(finish_B==true){traffic_light = 12;prioritisation = 1;}
      }
      if (priority == 1 && traffic_light == 8) {
        tp1 = millis(); p1_C = true;  if(finish_C==true){traffic_light = 12;prioritisation = 1;}
      }

      if (priority == 2 && traffic_light == 1) {
        tp1 = millis(); p2_A = true;  if(finish_A==true){traffic_light = 12;prioritisation = 1;}
      }
      if (priority == 2 && traffic_light == 4) {
        tp1 = millis(); p2_B = true;  if(finish_B==true){traffic_light = 12;prioritisation = 1;}
      }
      if (priority == 2 && traffic_light == 8) {
        tp1 = millis(); p2_C = true;  if(finish_C==true){traffic_light = 12;prioritisation = 1;}
      }

      if (priority == 3 && traffic_light == 1) {
        tp1 = millis(); p3_A = true;  if(finish_A==true){traffic_light = 12;prioritisation = 1;}
      }
      if (priority == 3 && traffic_light == 4) {
        tp1 = millis(); p3_B = true;  if(finish_B==true){traffic_light = 12;prioritisation = 1;}
      }
      if (priority == 3 && traffic_light == 8) {
        tp1 = millis(); p3_C = true;  if(finish_C==true){traffic_light = 12;prioritisation = 1;}
      }

      break;
      //YELLOW SEQUENCE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    case 1:
      if (p1_A == true) {
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);
      }
      if (p1_B == true) {
        digitalWrite(G3, LOW); digitalWrite(G4, LOW);
        digitalWrite(SG7, LOW);
        digitalWrite(Y3, HIGH); digitalWrite(Y4, HIGH);
      }
      if (p1_C == true) {
        digitalWrite(G3, LOW); digitalWrite(G5, LOW);
        digitalWrite(Y3, HIGH); digitalWrite(Y5, HIGH);
      }
      if (p2_A == true) {
        digitalWrite(G6, LOW); digitalWrite(G7, LOW);
        digitalWrite(Y6, HIGH); digitalWrite(Y7, HIGH);
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);

      }
      if (p2_B == true) {
        digitalWrite(G3, LOW);
        digitalWrite(Y3, HIGH);
      }
      if (p2_C == true) {
        digitalWrite(G3, LOW); digitalWrite(G5, LOW); digitalWrite(G6, LOW);
        digitalWrite(Y3, HIGH); digitalWrite(Y5, HIGH); digitalWrite(Y6, HIGH);
      }
      if (p3_A == true) {
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);
        digitalWrite(G6, LOW); digitalWrite(G7, LOW);
        digitalWrite(Y6, HIGH); digitalWrite(Y7, HIGH);
      }
      if (p3_B == true) {
        digitalWrite(SG7, LOW);
        digitalWrite(SG4, LOW);
        digitalWrite(G4, LOW);
        digitalWrite(Y4, HIGH);
      }
      if (p3_C == true) {
        digitalWrite(G6, LOW);
        digitalWrite(Y6, HIGH);
      }
      tp2 = millis();
      if (tp2 - tp1 > yellow_time) {
        tp3 = millis();
        prioritisation = 2;
      }
      break;
    //RED SEQUENCE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    case 2:
      //if(p1_A==1){}
      if (p1_B == true) {
        digitalWrite(Y3, LOW); digitalWrite(Y4, LOW);
        digitalWrite(R3, HIGH); digitalWrite(R4, HIGH);
      }
      if (p1_C == true) {
        digitalWrite(Y3, LOW); digitalWrite(Y5, LOW);
        digitalWrite(R3, HIGH); digitalWrite(R5, HIGH);
      }
      if (p2_A == true) {
        digitalWrite(Y6, LOW); digitalWrite(Y7, LOW);
        digitalWrite(R6, HIGH); digitalWrite(R7, HIGH);
      }
      if (p2_B == true) {
        digitalWrite(Y3, LOW);
        digitalWrite(R3, HIGH);
      }
      if (p2_C == true) {
        digitalWrite(Y3, LOW); digitalWrite(Y5, LOW); digitalWrite(Y6, LOW);
        digitalWrite(R3, HIGH); digitalWrite(R5, HIGH); digitalWrite(R6, HIGH);
      }
      if (p3_A == true) {
        digitalWrite(Y6, LOW); digitalWrite(Y7, LOW);
        digitalWrite(R6, HIGH); digitalWrite(R7, HIGH);
      }
      if (p3_B == true) {
        digitalWrite(Y4, LOW);
        digitalWrite(R4, HIGH);
      }
      if (p3_C == true) {
        digitalWrite(Y6, LOW);
        digitalWrite(R6, HIGH);
      }
      tp4 = millis();
      if (tp4 - tp3 > red_time) {
        tp5 = millis();
        prioritisation = 3;
      }
      break;
    //RED and YELLOW SEQUENCE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    case 3:
      //if(p1_A==1){}
      if (p1_B == true) {
        digitalWrite(Y6, HIGH); digitalWrite(Y7, HIGH);
      }
      if (p1_C == true) {
        digitalWrite(Y7, HIGH);
      }
      if (p2_A == true) {
        digitalWrite(Y4, HIGH);
      }
      //if(p2_B==1){}
      if (p2_C == true) {
        digitalWrite(Y4, HIGH);
      }
      if (p3_A == true) {
        digitalWrite(Y3, HIGH); digitalWrite(Y5, HIGH);
      }
      if (p3_B == true) {
        digitalWrite(Y5, HIGH);
      }
      //if(p3_C==1){}
      tp6 = millis();
      if (tp6 - tp5 > redandyellow_time) {
        prioritisation = 4;
      }
      break;
    //GREEN SEQUENCE -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    case 4:
      //if(p1_A==1){}
      if (p1_B == true) {
        digitalWrite(G6, HIGH); digitalWrite(G7, HIGH);
        digitalWrite(Y6, LOW); digitalWrite(Y7, LOW);
        digitalWrite(R6, LOW); digitalWrite(R7, LOW);
      }
      if (p1_C == true) {
        digitalWrite(G7, HIGH);
        digitalWrite(Y7, LOW);
        digitalWrite(R7, LOW);
      }
      if (p2_A == true) {
        digitalWrite(G4, HIGH);
        digitalWrite(SG7, HIGH);
        digitalWrite(Y4, LOW);
        digitalWrite(R4, LOW);
      }
      //if(p2_B==1){}
      if (p2_C == true) {
        digitalWrite(G4, HIGH);
        digitalWrite(SG7, HIGH);
        digitalWrite(Y4, LOW);
        digitalWrite(R4, LOW);
      }
      if (p3_A == true) {
        digitalWrite(G3, HIGH); digitalWrite(G5, HIGH);
        digitalWrite(Y3, LOW); digitalWrite(Y5, LOW);
        digitalWrite(R3, LOW); digitalWrite(R5, LOW);
      }
      if (p3_B == true) {
        digitalWrite(G5, HIGH);
        digitalWrite(Y5, LOW);
        digitalWrite(R5, LOW);
      }
      //if(p3_C==1){}
      prioritisation = 5;
      break;

    //idle state, cekani na ukonceni priority:
    case 5:

      break;
    //navazani zpet z priority do bezneho provozu:
    case 6:
      if (p1_A || p1_B || p1_C) {
        digitalWrite(SG3, HIGH); digitalWrite(SG4, HIGH); AtoC = false; BtoA = false; CtoB = false; waiting_A = false; trl01 = millis(); traffic_light = 1; reset_priority=true;reset_priority_all=true;prioritisation = 8;
      }
      if (p2_A || p2_B || p2_C) {
        digitalWrite(Y3, HIGH); tp7 = millis(); prioritisation = 7;
      }
      if (p3_A || p3_B || p3_C) {
        digitalWrite(Y6, HIGH); tp7 = millis(); prioritisation = 7;
      }
      break;

    case 7:
      tp8 = millis();
      if (tp8 - tp7 > 2000) {
        if (p2_A || p2_B || p2_C) {
          digitalWrite(Y3, LOW); digitalWrite(R3, LOW); AtoC = false; BtoA = false; CtoB = false; waiting_B = false; trl31 = millis(); traffic_light = 4; reset_priority=true;reset_priority_all=true;prioritisation = 8;
        }
        if (p3_A || p3_B || p3_C) {
          digitalWrite(Y6, LOW); digitalWrite(R6, LOW); AtoC = false; BtoA = false; CtoB = false; waiting_C = false; trl81 = millis(); traffic_light = 8; reset_priority=true;reset_priority_all=true;prioritisation = 8;
        }
      }
      break;
    //konecny stav
    case 8:
      
      if(reset_priority_all==false && reset_priority==false){prioritisation = 5;}
      break;
  }
  if(reset_priority_all==true){
      waiting_A = false; waiting_B = false; waiting_C = false; 
      finish_A = false;finish_B = false;finish_C = false;
      p1_A = false; p1_B = false; p1_C = false; //reset nastaveni priority
      p2_A = false; p2_B = false; p2_C = false;
      p3_A = false; p3_B = false; p3_C = false;
      completed_A = false; completed_B = false; completed_C = false;
      reset_priority_all=false;
  }

}