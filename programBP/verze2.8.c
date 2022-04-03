#include<IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <Inputs.h>
//Definujte analogove piny vyuzite ind senzorem (1) a IR cidly (6), 
//prahovou hodnotu detekce IR cidly, prahovou hodnotu detekce indukcnim cidlem, ochrannou dobu  mezi rozepnutim/ sepnutim tlacitka, ochrannou dobu  mezi prerusenim/ neprerusenim senzoru,
//piny: modraLED indukcniho senzoru, 7.,8.bila led na OP, piny mikrospinacu na OP(8) + na prechodu (2)
Inputs inputs(A7,A4,A1,A2,A3,A5,A6,
100,550,200,500,
33,34,35,36,37,38,39,40,41,42,43,2,3);

#include <Traffic_light_control.h>
//Definujte zelene LED (6), zlute LED (6), cervene LED (6), doplnujici sipky (3), cervena a zelena signalizace pro chodce (2), 
//dobu trvani zlute, cervene, zlute a cervene soucasne, zelene na prechodu a interval proti opakovani prechodu
Traffic_light_control trlc(
4,52,49,27,31,24,5,53,47,28,30,25,6,50,48,26,32,23,
51,46,29,8,7,3000,1000,2000,5000,10000);

#include <VO.h>
//Definujte 3 piny LED, analogovy vstup fotorezistoru, detekcni hranici pro sepnutí VO a dobu ujistovaciho stavu v ms
VO vo(22,44,45,A0,200,4000);



//vlastně definované charaktery pro načítání na displeji
byte L_1[8] = {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,};
byte L_2[8] = {0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,};
byte L_3[8] = {0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,};
byte L_4[8] = {0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,};
byte L_5[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,};


byte aa;
byte b;
byte bb;
byte c;
byte cc;
byte d;
byte dd;
byte e;
byte ee;
byte xx;
byte ii;
byte jj;

byte g;
byte h;
byte k;
byte l;
byte m;
byte n;

byte loading = 1;
byte stop_loading;
byte loading_state = 2;
byte load_pos;
byte clck_down = 1;
byte clck_up;
byte mins;
byte sec;
byte sec2;
byte tens = 10;
byte tens2;
byte sec_pos;
byte sec_pos2;
byte min_pos = 10;
int countdown = 10;
int time_loading;
unsigned long t_l1;
unsigned long t_l2;
unsigned long tc1;
unsigned long tc2;


byte priority;


byte flashing;
byte Reset;

float percentage_A;float percentage_B;float percentage_C;
byte sum;

float count_A_f;float count_B_f;float count_C_f;
int interval_A;
int interval_B;
int interval_C;
float interval_A_f;float interval_B_f;float interval_C_f;


byte refresh = 1;
byte refresh_ready = 1;
unsigned long ref_1;
unsigned long ref_2;

unsigned long fl_t1;
unsigned long fl_t2;
unsigned long fl_t3;
unsigned long fl_t4;




void setup() {

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  IrReceiver.begin(9);

  trlc.PinSetup();
  inputs.PinSetup();
  vo.PinSetup();

  digitalWrite(trlc.G12, HIGH);
  digitalWrite(trlc.SR12, HIGH);
  
  //symboly nacitani config
  lcd.createChar(0, L_1);
  lcd.createChar(1, L_2);
  lcd.createChar(2, L_3);
  lcd.createChar(3, L_4);
  lcd.createChar(4, L_5);
}

void loop() {
                                                   
//veřejné osvětlení (VO) --------------------------------------------------------------------------------------------------------------
vo.Sequence();

//nutne aktualizovat  pro pripad zapnuti necinneho stavu behem prepinani na prioritizaci
inputs.priority=priority;

//VYPIS INFORMACI NA DISPLEJ -----------------------------------------------------------------------------------------------------------------------------------------------------------------
//aktualizace displeje maximálně každych 300ms:
if(refresh_ready==0){  
  ref_2=millis();
  if(ref_2-ref_1>300){refresh_ready=1;}
}

  //zadost o refresh displeje od vstupnich periferii  
  if(inputs.refresh!=0){
  refresh=inputs.refresh;
  inputs.refresh=0;}

  //zadost o refresh displeje od hlavni sekvence rizeni SSZ
  if(trlc.refresh!=0){
  refresh=trlc.refresh;
  trlc.refresh=0;}

  // refresh: jen kdyz je treba aktualizovat data na displeji:-----------------------------------------------------------------------------------------------------------------
  if (refresh != 0 && priority == 0 && refresh_ready==1 && inputs.idle==0) { //idle==0 kvůli přechodu, který může přetrvat do idle stavu a spustí refresh (nechceme)

    sum = inputs.count_A + inputs.count_B + inputs.count_C;

    //DIRECTION A:------------------------------------------------------------------------------------------------------
    count_A_f = inputs.count_A;
    if (sum != 0) { //osetreni pro deleni nulou
      percentage_A = (count_A_f / sum) * 100;
    }
    else {
      percentage_A = (count_A_f / 1) * 100;
    }
    interval_A_f = percentage_A / 10;
    if (trlc.completed_A == 1) {
      interval_A = interval_A_f + 10;
    } else {
      interval_A = 10;
    }//minimum (10s)

    if (trlc.traffic_light == 1 && inputs.emergency == 0 ) {
      
      if (aa==1 && sec != 0) {
        sec += (interval_A - countdown); //nutné zde, před počítáním cooldownu
      }
   
      countdown = countdown + (interval_A - countdown); //nutné počítat zde, až po předešlém příkazu
  
        if (sec == 0 && countdown != 0 && aa==0) { //proměnná aa kvůli opakování odpočítávání při registraci vozidla v daném směru
          load_pos = 0;  
          tens = 10;
          sec = countdown - 1; //-1 kvuli desetinam
          lcd.setCursor ( 0, 3 );
          lcd.print("                    ");
          cc=0;bb=0;aa=1; 
          }
      
      
      lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
      lcd.setCursor ( 0, 0 ); lcd.print(">A:");
      lcd.setCursor ( 3, 0 ); lcd.print("     ");
      lcd.setCursor ( 3, 0 ); lcd.print(percentage_A);
      lcd.setCursor ( 8, 0 ); lcd.print("%");
      lcd.setCursor ( 10, 0 ); lcd.print("Cn:");
      lcd.setCursor ( 13, 0 ); lcd.print("   ");
      lcd.setCursor ( 13, 0 ); lcd.print(inputs.count_A);
      lcd.setCursor ( 15, 0 ); lcd.print("I:");
      lcd.setCursor ( 17, 0 ); lcd.print("  ");
      lcd.setCursor ( 17, 0 ); lcd.print(interval_A);
      lcd.setCursor ( 19, 0 ); lcd.print("s");

    }
    //DIRECTION B:------------------------------------------------------------------------------------------------------
    count_B_f = inputs.count_B;
    if (sum != 0) {
      percentage_B = (count_B_f / sum) * 100;
    }
    else {
      percentage_B = (count_B_f / 1) * 100;
    }
    interval_B_f = percentage_B / 10;
    if (trlc.completed_B == 1) {
      interval_B = interval_B_f + 10;
    } else {
      interval_B = 10;
    }//minimum (10s)
    if (trlc.traffic_light == 4 && inputs.emergency == 0) {

      if (sec != 0 && bb==1) {
        sec += (interval_B - countdown);
      }
      
      countdown = countdown + (interval_B - countdown);
      
        if (sec == 0 && countdown != 0 && bb==0) {
          load_pos = 0;
          tens = 10;
          sec = countdown - 1;
          lcd.setCursor ( 0, 3 );
          lcd.print("                    ");
          aa=0;cc=0;bb=1;
          }
      
      lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
      lcd.setCursor ( 0, 0 ); lcd.print(">B:");
      lcd.setCursor ( 3, 0 ); lcd.print("     ");
      lcd.setCursor ( 3, 0 ); lcd.print(percentage_B);
      lcd.setCursor ( 8, 0 ); lcd.print("%");
      lcd.setCursor ( 10, 0 ); lcd.print("Cn:");
      lcd.setCursor ( 13, 0 ); lcd.print("   ");
      lcd.setCursor ( 13, 0 ); lcd.print(inputs.count_B);
      lcd.setCursor ( 15, 0 ); lcd.print("I:");
      lcd.setCursor ( 17, 0 ); lcd.print("  ");
      lcd.setCursor ( 17, 0 ); lcd.print(interval_B);
      lcd.setCursor ( 19, 0 ); lcd.print("s");

    }
    //DIRECTION C:------------------------------------------------------------------------------------------------------
    count_C_f = inputs.count_C;
    if (sum != 0) {
      percentage_C = (count_C_f / sum) * 100;
    }
    else {
      percentage_C = (count_C_f / 1) * 100;
    }
    interval_C_f = percentage_C / 10; //minimum (10s)
    if (trlc.completed_C == 1) {
      interval_C = interval_C_f + 10;
    } else {
      interval_C = 10;
    }
    if (trlc.traffic_light == 8 && inputs.emergency == 0) {

      if (sec != 0 && cc==1) {
        sec += (interval_C - countdown);
      }

      countdown = countdown + (interval_C - countdown);
  
        if (sec == 0 && countdown != 0 && cc==0) {
          load_pos = 0;
          tens = 10;
          sec = countdown - 1;
          lcd.setCursor ( 0, 3 );
          lcd.print("                    ");
          aa=0;bb=0;cc=1;
          }
      
      lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
      lcd.setCursor ( 0, 0 ); lcd.print(">C:");
      lcd.setCursor ( 3, 0 ); lcd.print("     ");
      lcd.setCursor ( 3, 0 ); lcd.print(percentage_C);
      lcd.setCursor ( 8, 0 ); lcd.print("%");
      lcd.setCursor ( 10, 0 ); lcd.print("Cn:");
      lcd.setCursor ( 13, 0 ); lcd.print("   ");
      lcd.setCursor ( 13, 0 ); lcd.print(inputs.count_C);
      lcd.setCursor ( 15, 0 ); lcd.print("I:");
      lcd.setCursor ( 17, 0 ); lcd.print("  ");
      lcd.setCursor ( 17, 0 ); lcd.print(interval_C);
      lcd.setCursor ( 19, 0 ); lcd.print("s");

    }
    //dodatečný výpis------------------------------------------------------------------------------------------------------
    if (inputs.emergency == 0) {
      lcd.setCursor ( 0, 1 ); lcd.print("A:");
      lcd.setCursor ( 2, 1 ); lcd.print(inputs.reg_A);
      if (trlc.traffic_light == 1) {
        lcd.setCursor ( 2, 1 );
        lcd.print("G");
      }
      lcd.setCursor ( 4, 1 ); lcd.print("B:");
      lcd.setCursor ( 6, 1 ); lcd.print(inputs.reg_B);
      if (trlc.traffic_light == 4) {
        lcd.setCursor ( 6, 1 );
        lcd.print("G");
      }
      lcd.setCursor ( 8, 1 ); lcd.print("C:");
      lcd.setCursor ( 10, 1 ); lcd.print(inputs.reg_C);
      if (trlc.traffic_light == 8) {
        lcd.setCursor ( 10, 1 );
        lcd.print("G");
      }
      lcd.setCursor ( 12, 1 ); lcd.print("cross:");
      lcd.setCursor ( 18, 1 ); lcd.print(inputs.crossing_active);
      //lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
    } else {
      lcd.setCursor ( 7, 2 );
      lcd.print(inputs.crossing_active);
    }
    refresh_ready=0;
    ref_1=millis();
    refresh = 0;
  }
//vypisování pro emergency stav---------------------------------------------------------------------------------------

  if (inputs.emergency == 1 && priority == 0) {
    if (trlc.traffic_light == 1 && aa == 0) {
      if (sec == 0) {
        sec = 9;stop_loading=0;
        load_pos = 0;
        tens = 10;
        lcd.setCursor ( 0, 3 );
        lcd.print("                    ");
      }
      lcd.setCursor ( 0, 1 ); lcd.print("Prujezdny stav: >A ");
      lcd.setCursor ( 0, 2 ); lcd.print("         ");
      lcd.setCursor ( 0, 2 ); lcd.print("cross:"); lcd.setCursor ( 7, 2 ); lcd.print(inputs.crossing_active); lcd.setCursor ( 14, 2 ); lcd.print("z"); lcd.setCursor ( 16, 2 ); lcd.print(countdown); lcd.setCursor ( 19, 2 ); lcd.print("s");
      ee = 0; cc = 0; bb = 0; aa = 1;
    }
    if (trlc.traffic_light == 4 && bb == 0) {
      if (sec == 0) {
        sec = 9;stop_loading=0;
        load_pos = 0;
        tens = 10;
        lcd.setCursor ( 0, 3 );
        lcd.print("                    ");
      }
      lcd.setCursor ( 0, 1 ); lcd.print("Prujezdny stav: >B ");
      lcd.setCursor ( 0, 2 ); lcd.print("         ");
      lcd.setCursor ( 0, 2 ); lcd.print("cross:"); lcd.setCursor ( 7, 2 ); lcd.print(inputs.crossing_active); lcd.setCursor ( 14, 2 ); lcd.print("z"); lcd.setCursor ( 16, 2 ); lcd.print(countdown); lcd.setCursor ( 19, 2 ); lcd.print("s");
      ee = 0; cc = 0; aa = 0; bb = 1;
    }
    if (trlc.traffic_light == 8 && cc == 0) {
      if (sec == 0) {
        sec = 9;stop_loading=0;
        load_pos = 0;
        tens = 10;
        lcd.setCursor ( 0, 3 );
        lcd.print("                    ");
      }
      lcd.setCursor ( 0, 1 ); lcd.print("Prujezdny stav: >C ");
      lcd.setCursor ( 0, 2 ); lcd.print("         ");
      lcd.setCursor ( 0, 2 ); lcd.print("cross:"); lcd.setCursor ( 7, 2 ); lcd.print(inputs.crossing_active); lcd.setCursor ( 14, 2 ); lcd.print("z"); lcd.setCursor ( 16, 2 ); lcd.print(countdown); lcd.setCursor ( 19, 2 ); lcd.print("s");
      ee = 0; aa = 0; bb = 0; cc = 1;
    }
    if (trlc.traffic_light != 1 && trlc.traffic_light != 4 && trlc.traffic_light != 8 && inputs.idle == 0 && ee == 0) {
      lcd.setCursor ( 0, 1 );
      lcd.print("Prujezdny stav: -  "); ee = 1;
    }
  }
 
  //SYMBOL NACITANI---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  switch (loading)
  {
    case 1:
      if (time_loading == 0) {
        loading_state = 2;
        load_pos = 0;
      }
      if (inputs.idle == 0 && stop_loading == 0 && priority == 0) {
        if (trlc.traffic_light == 1 || trlc.traffic_light == 4 || trlc.traffic_light == 8) {
          time_loading = ((countdown-1) * 1000) / 100; //100 stavů na displeji a *1000 milisec, 2 ctverecky nestíhá proto /110
          t_l1 = millis(); loading = 2;
        }
      }

      break;
    case 2:
      t_l2 = millis();
      if (t_l2 - t_l1 > time_loading) {
        if (load_pos < 20) {
          loading_state++;
          loading = loading_state;
        }
      }
      break;
    case 3:
      lcd.setCursor ( load_pos, 3 ); lcd.write(byte(0));
      loading = 1;
      break;
    case 4:
      lcd.setCursor ( load_pos, 3 ); lcd.write(byte(1));
      loading = 1;
      break;
    case 5:
      lcd.setCursor ( load_pos, 3 ); lcd.write(byte(2));
      loading = 1;
      break;
    case 6:
      lcd.setCursor ( load_pos, 3 ); lcd.write(byte(3));
      loading = 1;
      break;
    case 7:
      lcd.setCursor ( load_pos, 3 ); lcd.write(byte(4));
      loading_state = 2; if (load_pos < 20) {
        load_pos++;
      } time_loading = ((countdown-1) * 1000) / 100; loading = 1;
      break;
  }
  //ODPOCITAVANI CASU------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  switch (clck_down)
  {
    case 1:
      if (sec != 0) {
        tc1 = millis();
        clck_down = 2;
      }
      break;

    case 2:
      tc2 = millis();
      if (tc2 - tc1 > 100) {
        tens--;
        if (tens == 0) {
          sec--;
          if (sec != 0) {
            tens = 10;
          }
        } clck_down = 1;
      }
      break;
  }

  //PRICITANI CASU------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  if (trlc.prioritisation == 5 || inputs.idle == 1) {
    switch (clck_up)
    {
      case 1:
        tc1 = millis();
        clck_up = 2;
        break;

      case 2:
        tc2 = millis();
        if (tc2 - tc1 > 1000) {
          lcd.setCursor ( sec_pos2 - 1, 3 ); lcd.print("   ");
          sec++;
          if (sec > 59) {
            lcd.setCursor ( min_pos - 1, 3 ); lcd.print("   ");
            mins++; sec = 0;
          }

          clck_up = 1;
        }

        break;
    }
  }
  //uvedení do nouzového stavu SP1-----------------------------------------------------------------------------------------------------------------------------------
  //fáze semaforu jdou postupne: A->B->C
  //pouze pokud prave neprobiha prioritizace IZS
//odpocitavani na displeji jen pokud neprobihaji priority ani necinny stav
  if (inputs.idle == 0 && priority == 0 && stop_loading==0) {
    if (sec2 != sec) {
      if (inputs.emergency == 1) {
        if (sec < 10) {
          sec_pos = 11; //4 3
        } else {
          sec_pos = 10;
        } 
        lcd.setCursor ( 10, 2 ); lcd.print("  ");
        lcd.setCursor ( sec_pos, 2 ); lcd.print(sec);
      } 

       if(inputs.emergency==0){ 
        if (sec < 10) {
          sec_pos = 5; //4 3
        } else {
          sec_pos = 4;
        }
        lcd.setCursor ( 4, 2 ); lcd.print("  "); 
        lcd.setCursor ( sec_pos, 2 ); lcd.print(sec);
      }
    sec2 = sec;} 

    //zakomentovana moznost zobrazovani desetin: (sec_pos2 zabrana!)
    //if(tens2!=tens){lcd.setCursor ( 6, 2 );lcd.print("  ");
    //if(tens<10){sec_pos2=7;}else{sec_pos2=6;}lcd.setCursor ( sec_pos2, 2 );lcd.print(tens);}
    //tens2=tens;
  }
  
  
  
  if (inputs.emergency > 1) {
    lcd.setCursor ( 0, 0 ); lcd.print("                    ");//aby byl zachován loading bar nečistím celý displej
    lcd.setCursor ( 0, 1 ); lcd.print("                    ");
    lcd.setCursor ( 0, 2 ); lcd.print("                    ");
    trlc.reset_priority_all=1;
    aa = 0; bb = 0; cc = 0; ee = 0; //reset vypisu
    
    refresh = 1; e = 0;
    if (inputs.crossing_active == 0) {
      digitalWrite(trlc.G12, HIGH); digitalWrite(trlc.SR12, HIGH);
    }
    inputs.emergency=0;
  }
  //emergency je dulezitejsi nez idle -> premuze jej: idle=0...
  //aa,bb,cc,ee jsou ochrany proti nekonecnemu vypisovani na lcd
  //take se zde nuluje odpocitavani(time_loading, load_pos, sec, loading_state) a odpocitavani primarne nastaveno na 10s
  if (inputs.emergency == 1) {
    if (e == 0) {
      aa = 0; bb = 0; cc = 0; ee = 0;
      //time_loading = 0; load_pos = 0; sec = 0; loading_state = 2; tens=10;
      inputs.idle = 0; countdown = 10; 
      lcd.setCursor ( 0, 0 ); lcd.print("                    ");//aby byl zachovan loading bar necistim cely displej
      lcd.setCursor ( 0, 1 ); lcd.print("                    ");
      lcd.setCursor ( 0, 2 ); lcd.print("                    ");
      lcd.setCursor ( 4, 0 ); lcd.print("NOUZOVY STAV");
      //lcd.setCursor( 5, 2 );lcd.print(".");
      //lcd.setCursor( 9, 2 );lcd.print("s");
      refresh = 1;e = 1;
    }
    if (inputs.crossing_active == 1 && trlc.traffic_light == 1) {time_loading = 0; load_pos = 0; loading_state=2;
      lcd.setCursor ( 0, 3 ); lcd.print("preruseno prechodem "); stop_loading = 1; lcd.setCursor ( 10, 2 ); lcd.print("--"); 
    }    
  }
//stop loading se spousti jen ve volnem stavu ve smeru A:
if (trlc.traffic_light == 4 && stop_loading ==1) {
  stop_loading = 0;
      }
    
  //RESET-------------------------------------------------------------------------------------------------------------------------------------------
  //dulezity pri prechod do/z idle stavu
  if (Reset == 1) {
    
    inputs.count_A = 0; inputs.count_B = 0; inputs.count_C = 0;
    count_A_f = 0; count_B_f = 0; count_C_f = 0;
    interval_A = 0; interval_B = 0; interval_C = 0;
    interval_A_f = 0; interval_B_f = 0; interval_C_f = 0;
    trlc.waiting_A = 0; trlc.waiting_B = 0; trlc.waiting_C = 0;
    inputs.reg_A = 0; inputs.reg_B = 0; inputs.reg_C = 0; 
    
    if (inputs.idle == 0) {
    trlc.traffic_light = 0;
    }
    aa = 0; bb = 0; cc = 0; ee = 0; xx = 0;countdown=10;
    time_loading = 0; load_pos = 0; sec_pos = 0; sec_pos2 = 0; sec = 0; //sec=0 kvůli použití proměnné pro počítání doby trvaní idle stavu
    loading_state = 2; loading=1;
    tens=10;
    clck_down = 1; clck_up = 0; mins = 0;
    trlc.everything_off=1;
   
    refresh=1;
    Reset = 0;
  }

  //uvedení do necinneho stavu------------------------------------------------------------------------------------------------------
  //tlacitka 7 a 8, ktera uvadi do emergency a idle stavu
  inputs.Sequence_in_idle();
  if (inputs.idle > 1) {
    inputs.idle = 0;
  }

  if (inputs.idle == 1) {
    b = 0; //nulovani jednoho opakovani prikazu u idle=0
    
      if (inputs.crossing_active == 0) {
        if(d==0){
        trlc.crosswalk_off=1;d=1;}
      }
    
    if (c == 0) {
      trlc.traffic_light = 12; Reset = 1; lcd.clear(); lcd.setCursor(4, 1 ); lcd.print("NECINNY STAV");
      fl_t1 = millis(); flashing = 1; c = 1;
    }
    //dve promenne pro ochranu opakovani z duvodu cekani na prechod (d)
  }

  //blikání žluté signalizace------------------------------------------------------------------------------------------------------

  switch (flashing) {
    case 0:
      break;
    case 1:
      trlc.all_yellow_high=1;
      if (inputs.crossing_active == 0 && priority==0) {
        digitalWrite(trlc.Y12, HIGH);
      }
      fl_t2 = millis();
      if (fl_t2 - fl_t1 > 500) {
        fl_t3 = millis();
        flashing = 2;
      }
      break;
    case 2:
      trlc.all_yellow_low=1;
      if (inputs.crossing_active == 0) {
        digitalWrite(trlc.Y12, LOW);
      }
      fl_t4 = millis();
      if (fl_t4 - fl_t3 > 500) {
        fl_t1 = millis();
        flashing = 1;
      }
      break;
  }

  

  //Činný stav, čtení senzorů------------------------------------------------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  if (inputs.idle == 0) {
    //čtení senzorů a tlačítek------------------------------------------------------------------------------------------------------
     inputs.Sequence_out_of_idle();
    if (b == 0) {
      if (inputs.crossing_active == 0) {
        digitalWrite(trlc.G12, HIGH);
        digitalWrite(trlc.SR12, HIGH);
      }
      lcd.clear(); refresh = 1; trlc.waiting_A = 1;
      trlc.all_yellow_low=1;
      flashing = 0; c = 0; d = 0; e = 0; Reset = 1; b = 1;
    }

    //c...ochrana proti opakovani disp: necinny
    //d...ochrana proti opakovani zhasnuti LED
    //e...pro spravny prepis disp, pokud nastane: z necinneho do nouzoveho
    //b...ochrana proti opakovani nastaveni pro cinny mod
    
  }
  

  //snímání požadavku z jiných směrů...-----------------------------------------------------------------------------------------------------------------------
//...spínači i čidly -> jsou zohledněné doplňkové šipky -> kde v jiných směrech projíždějí vozidla na zelenou, není registrován požadavek
//tímto způsobem se získávájí nejaktuálnější data
inputs.Sequence_change_free_state_reg();
inputs.traffic_light=trlc.traffic_light;
inputs.priority=priority;

//sekvence řízení ----------------------------------------------------------------------------------------------------------------------------------------------------
trlc.Sequence_main();
 //v trlc knihovne dochazi k pricteni jednicky pri registraci (musi byt minimalne jedno vozidlo...) a nulovani pri ukonceni volneho stavu

if(trlc.count_A_0==1){
  inputs.count_A=0;
  trlc.count_A_0=0;}
if(trlc.count_A_1==1){
  inputs.count_A=1;
  trlc.count_A_1=0;}
  
if(trlc.count_B_0==1){
  inputs.count_B=0;
  trlc.count_B_0=0;}
if(trlc.count_B_1==1){
  inputs.count_B=1;
  trlc.count_B_1=0;}

if(trlc.count_C_0==1){
  inputs.count_C=0;
  trlc.count_C_0=0;}
if(trlc.count_C_1==1){
  inputs.count_C=1;
  trlc.count_C_1=0;}


trlc.reg_A=inputs.reg_A;
if(trlc.reg_A_done==1){
  inputs.reg_A=0;
  trlc.reg_A=0;
  trlc.reg_A_done=0;}
trlc.reg_B=inputs.reg_B;
if(trlc.reg_B_done==1){
  inputs.reg_B=0;
  trlc.reg_B=0;
  trlc.reg_B_done=0;}
trlc.reg_C=inputs.reg_C;
if(trlc.reg_C_done==1){
  inputs.reg_C=0;
  trlc.reg_C=0;
  trlc.reg_C_done=0;}

trlc.emergency=inputs.emergency;
trlc.idle=inputs.idle;
trlc.priority=priority;

trlc.interval_A=interval_A;
trlc.interval_B=interval_B;
trlc.interval_C=interval_C;

//Prioritizace IZS--------------------------------------------------------------------------------------------------------------------------------------------------------------
trlc.Prioritisation_IES();
 
//sekvence řízení/ prechod pro chodce----------------------------------------------------------------------------------------------------------------------------------------------------
trlc.Sequence_crosswalk();
trlc.crossing_active=inputs.crossing_active;

if(inputs.crossing_active!=0 && trlc.crossing_noactive==1){
  trlc.crossing_active=0;
  inputs.crossing_active=0;
  trlc.crossing_noactive=0;}

//tlacitka prechodu, jimi navolena data se vynuluji az skonci sekvence prechodu
if(inputs.sw_cross1_output!=0 && trlc.sw_cross1_output==1){
  inputs.sw_cross1_output=0;
  trlc.sw_cross1_output=0;}
if(inputs.sw_cross2_output!=0 && trlc.sw_cross2_output==1){
  inputs.sw_cross2_output=0;
  trlc.sw_cross2_output=0;}
//cross_reg_not_repeat proti neustalemu prepisovani displeje
if(inputs.cross_reg_not_repeat!=0 && trlc.cross_reg_not_repeat==1){
  inputs.cross_reg_not_repeat=0;
  trlc.cross_reg_not_repeat=0;}
  //umozneno preskakovat mezi jednotlivými stavy, zohlednovat prechod pres skutecnost zadne detekce vozidel, prizpusobeny interval aktualnimu provozu
  
  //KONFIGURACE OVLADAČE---------------------------------------------------------------------------------------------------------------------------------------

  if (IrReceiver.decode()) {
    IrReceiver.resume();
    //vypinani/ preruseni priority, muze pokracovat jen pokud vse dokonano
    if (IrReceiver.decodedIRData.command == 0x45) {
      if (trlc.prioritisation == 5 && priority != 0) {
       trlc.prioritisation = 6;
      }
    }
    //pouze pokud prave neprobiha prioritizace...
    if (trlc.prioritisation == 5 && inputs.idle == 0 && priority == 0) {
      if (IrReceiver.decodedIRData.command == 0xC) {
        refresh = 1; trlc.prioritisation = 0; priority = 1;
        lcd.clear();lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru A");
      }
      if (IrReceiver.decodedIRData.command == 0x18) {
        refresh = 1; trlc.prioritisation = 0; priority = 2;
        lcd.clear();lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru B");
      }
      if (IrReceiver.decodedIRData.command == 0x5E) {
        refresh = 1; trlc.prioritisation = 0; priority = 3;
        lcd.clear();lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru C");
      }
    }
  }

  if (priority != 0 || inputs.idle == 1) {
    if (xx == 0) {
      loading=1; clck_down = 0; clck_up = 1; sec = 0;
      if (inputs.idle == 0) {
        lcd.setCursor ( 6, 2 ); lcd.print("cross:"); lcd.setCursor ( 13, 2 ); lcd.print(inputs.crossing_active);
         lcd.setCursor ( 2, 0 ); lcd.print("Prioritizace IZS");
      }
      lcd.setCursor ( 0, 3 ); lcd.print("po dobu:");
      sec_pos2 = 10;
      xx = 1;
    }
    //stav prechodu zobrazujeme jen kdyz neni necinny stav
    if (refresh != 0) {
      if(inputs.idle==0){
      lcd.setCursor ( 6, 2 ); lcd.print("cross:"); lcd.setCursor ( 13, 2 ); lcd.print(inputs.crossing_active);
      }
      refresh = 0; 
    }

    if (sec < 10 && mins == 0) {
      sec_pos2 = 10;
      lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
      lcd.setCursor ( 12, 3 ); lcd.print("s");
    }
    if (sec > 9 && mins == 0) {
      sec_pos2 = 9;
      lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
      lcd.setCursor ( 12, 3 ); lcd.print("s");
    }
    if (sec > 9 && mins != 0) {
      sec_pos2 = 16;
      lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
      lcd.setCursor ( 19, 3 ); lcd.print("s");
    }
    if (sec < 10 && mins != 0) {
      sec_pos2 = 17;
      lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
      lcd.setCursor ( 19, 3 ); lcd.print("s");
    }
    if (mins > 9) {
      min_pos = 9;
    }
    if (mins != 0) {
      lcd.setCursor ( min_pos, 3 ); lcd.print(mins);
      lcd.setCursor ( 12, 3 ); lcd.print("min");
    }
  }

  //PRIORITIZACE IZS------------------------------------------------------------------------------------------------------------------------------------------
  //nejprve se navaze, potom se prispusobuji led tak aby byl prujezdny stav pouze v jednom smeru

    //konecny stav
    if(trlc.reset_priority==1){
      clck_down = 1; clck_up = 0; xx = 0; mins = 0; min_pos = 10; sec_pos2 = 10;
      time_loading = 0; load_pos = 0; loading_state = 2;
      sec=0; //proměnná byla použita pro dobu trvani prioritizace -> nutne vynulovat
      
      aa = 0; bb = 0; cc = 0; ee = 0; //reset vypisu
      
      priority = 0; lcd.clear(); refresh = 1;//reset displeje
      //kdyz nastane prioritizace behem nouzoveho stavu je treba znovu vypsat:
      if (inputs.emergency == 1) {
        lcd.setCursor ( 4, 0 ); lcd.print("NOUZOVY STAV");
      }
    trlc.reset_priority=0;}
}
