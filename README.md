

```c

#include<IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte L_1[8] = {0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,};
byte L_2[8] = {0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,};
byte L_3[8] = {0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,};
byte L_4[8] = {0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,};
byte L_5[8] = {0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,};

byte a;
byte b;
byte bb;
byte c;
byte cc;
byte d;
byte dd;
byte e;
byte ee;
byte xx;

byte g;
byte h;
byte i;
byte j;
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
byte sec=10;
byte sec2;
byte tens = 10;
byte tens2;
byte sec_pos;
byte sec_pos2;
byte min_pos =10;
int countdown=10;
int time_loading;
unsigned long t_l1;
unsigned long t_l2;
unsigned long tc1;
unsigned long tc2;

byte prioritisation = 5;
byte priority;
byte p1_A;
byte p1_B;
byte p1_C;
byte p2_A;
byte p2_B;
byte p2_C;
byte p3_A;
byte p3_B;
byte p3_C;

byte idle;
byte flashing;
byte Reset;
byte emergency;

int sensor1;
int sensor2;
int sensor3;
int sensor4;
int sensor5;
int sensor6;
int ind_sensor;
int foto_sensor;

byte traffic_light = 0;
byte crossing_active = 0;
byte cross = 6;
byte finish_cross4;
byte finish_A;
byte foto = 0;


float percentage_A;
float percentage_B;
float percentage_C;
byte sum;
byte count_A;
byte count_B;
byte count_C;
float count_A_f;
float count_B_f;
float count_C_f;
byte interval_A;
int interval_A2;
byte interval_B;
int interval_B2;
byte interval_C;
int interval_C2;
float interval_A_f;
float interval_B_f;
float interval_C_f;
byte refresh = 1;
byte completed_A;
byte completed_B;
byte completed_C;

byte aa;
byte ii;
byte jj;

byte reg_A;
byte reg_B;
byte reg_C;
byte waiting_A;
byte waiting_B;
byte waiting_C;
byte AtoC;
byte BtoA;
byte CtoB;

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

byte se1s;
byte se2s;
byte se3s;
byte se4s;
byte se5s;
byte se6s;

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

unsigned long foto_t1;
unsigned long foto_t2;
unsigned long foto_t3;
unsigned long foto_t4;

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

unsigned long fl_t1;
unsigned long fl_t2;
unsigned long fl_t3;
unsigned long fl_t4;

unsigned long tp1;
unsigned long tp2;
unsigned long tp3;
unsigned long tp4;
unsigned long tp5;
unsigned long tp6;
unsigned long tp7;
unsigned long tp8;

//konfigurace pinu

byte G[]={0,4,4,52,49,27,31,24};
byte R[]={0,6,6,50,48,26,32,23};
byte Y[]={0,5,5,53,47,28,30,25};
byte W[]={22,44,45};
byte sw[]={0,36,37,38,39,40,41,42,43};
byte SG7 = 29;
byte BOP = 33;
byte L7OP = 34;
byte L8OP = 35;
byte SG4 = 46;
byte SG3 = 51;
byte swcross1 = 2;
byte swcross2 = 3;
byte SG12 = 7;
byte SR12 = 8;

//casy pro aktualizaci dat ze spinacu(sw) a senzorů(se)
byte time_sw = 200;
byte time_se = 500;

void setup() {

  
  pinMode(W[0], OUTPUT);
  pinMode(W[1], OUTPUT);
  pinMode(W[2], OUTPUT);
  
  for(k=0;k<8;k++){
  pinMode(R[k], OUTPUT);
  pinMode(G[k], OUTPUT);
  pinMode(Y[k], OUTPUT);
  }
  pinMode(SG7, OUTPUT);
  pinMode(BOP, OUTPUT);
  pinMode(L7OP, OUTPUT);
  pinMode(L8OP, OUTPUT);
  pinMode(SG4, OUTPUT);
  pinMode(SG3, OUTPUT);
  pinMode(SG12, OUTPUT);
  pinMode(SR12, OUTPUT);
  
  for(l=0;l<9;l++){
    pinMode(sw[l], INPUT_PULLUP);
    }
  pinMode(swcross1, INPUT_PULLUP);
  pinMode(swcross2, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  IrReceiver.begin(9);

  digitalWrite(G[1], HIGH);
  digitalWrite(SR12, HIGH);
//symboly nacitani config
  lcd.createChar(0, L_1);
  lcd.createChar(1, L_2);
  lcd.createChar(2, L_3);
  lcd.createChar(3, L_4);
  lcd.createChar(4, L_5);
}

void loop() {
  
//Serial.print("sec:");
  //Serial.print(sec);
  //Serial.print("tens:");
  //Serial.print(tens);
//Serial.print("\n");
  //veřejné osvětlení------------------------------------------------------------------------------------------------------

  switch (foto) {
    case 0:
      if (aa == 0) {
        digitalWrite(W[0], LOW);
        digitalWrite(W[1], LOW);
        digitalWrite(W[2], LOW);
      } aa = 1;
      foto_sensor = analogRead(A0);
      if (foto_sensor < 200) {
        foto_t1 = millis();
        foto = 1;
      }
      break;
    case 1:
      aa = 0;
      foto_sensor = analogRead(A0);
      if (foto_sensor > 200) {
        foto = 0;
      }
      foto_t2 = millis();
      if (foto_t2 - foto_t1 > 3000) {
        foto = 2;
      }
      break;
    case 2:
      if (dd == 0) {
        //digitalWrite(W[0],HIGH);
        //digitalWrite(W[1],HIGH);
        //digitalWrite(W[2],HIGH);
      } dd = 1;
      foto_sensor = analogRead(A0);
      if (foto_sensor > 200) {
        foto_t3 = millis();
        foto = 3;
      }
      break;
    case 3:
      aa = 0;
      foto_sensor = analogRead(A0);
      if (foto_sensor < 200) {
        foto = 2;
      }
      foto_t4 = millis();
      if (foto_t4 - foto_t3 > 3000) {
        foto = 0;
      }
      break;
  }
  //modra led u ind. senzoru...
  ind_sensor = analogRead(A7);
  if (ind_sensor > 550) {
    digitalWrite(BOP, HIGH);
  }
  else {
    digitalWrite(BOP, LOW);
  }

  // refresh: jen kdyz je treba aktualizovat data na displeji:-----------------------------------------------------------------------------------------------------------------

  if (refresh != 0 && priority == 0) {
    //lcd.setCursor( 5, 2 );lcd.print("."); v pripade zobrazovani desetin...
    //lcd.setCursor( 9, 2 );lcd.print("s");
    sum = count_A + count_B + count_C;

    //DIRECTION A:------------------------------------------------------------------------------------------------------
    count_A_f = count_A;
    if (sum != 0) { //osetreni pro deleni nulou
      percentage_A = (count_A_f / sum) * 100;
    }
    else {
      percentage_A = (count_A_f / 1) * 100;
    }
    interval_A_f = percentage_A / 10;
    if (completed_A == 1) {
      interval_A = interval_A_f + 10;
    } else {
      interval_A = 10;
    }//minimum (10s)
    
    if (traffic_light == 1 && emergency==0) {   
        if(aa==1 && sec!=0){
        sec+=(interval_A-countdown); 
        }
      countdown=countdown+(interval_A-countdown);
      if (countdown != 0 && aa==0) {
          load_pos=0;tens=10;sec = countdown - 1;lcd.setCursor ( 0, 3 ); lcd.print("                    ");//-1 kvuli desetinam
          cc=0;bb=0;aa=1;
        }
        if (crossing_active == 0) {
          lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
        }
         
      lcd.setCursor ( 0, 0 ); lcd.print(">A:");
      lcd.setCursor ( 3, 0 ); lcd.print("     ");
      lcd.setCursor ( 3, 0 ); lcd.print(percentage_A);
      lcd.setCursor ( 8, 0 ); lcd.print("%");
      lcd.setCursor ( 10, 0 ); lcd.print("Cn:");
      lcd.setCursor ( 13, 0 ); lcd.print("   ");
      lcd.setCursor ( 13, 0 ); lcd.print(count_A);
      lcd.setCursor ( 15, 0 ); lcd.print("I:");
      lcd.setCursor ( 17, 0 ); lcd.print("  ");
      lcd.setCursor ( 17, 0 ); lcd.print(interval_A);
      lcd.setCursor ( 19, 0 ); lcd.print("s");
             
    }
    //DIRECTION B:------------------------------------------------------------------------------------------------------
    count_B_f = count_B;
    if (sum != 0) {
      percentage_B = (count_B_f / sum) * 100;
    }
    else {
      percentage_B = (count_B_f / 1) * 100;
    }
    interval_B_f = percentage_B / 10;
    if (completed_B == 1) {
      interval_B = interval_B_f + 10;
    } else {
      interval_B = 10;
    }//minimum (10s)
    if (traffic_light == 4 && emergency==0) {  
        if(bb==1 && sec!=0){
        sec+=(interval_B-countdown);
        }
      countdown=countdown+(interval_B-countdown);
      if (countdown != 0 && bb==0) {
          load_pos=0;tens=10;sec = countdown - 1;lcd.setCursor ( 0, 3 ); lcd.print("                    ");
          cc=0;aa=0;bb=1;
        }
        if (crossing_active == 0) {
          lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
 }
      lcd.setCursor ( 0, 0 ); lcd.print(">B:");
      lcd.setCursor ( 3, 0 ); lcd.print("     ");
      lcd.setCursor ( 3, 0 ); lcd.print(percentage_B);
      lcd.setCursor ( 8, 0 ); lcd.print("%");
      lcd.setCursor ( 10, 0 ); lcd.print("Cn:");
      lcd.setCursor ( 13, 0 ); lcd.print("   ");
      lcd.setCursor ( 13, 0 ); lcd.print(count_B);
      lcd.setCursor ( 15, 0 ); lcd.print("I:");
      lcd.setCursor ( 17, 0 ); lcd.print("  ");
      lcd.setCursor ( 17, 0 ); lcd.print(interval_B);
      lcd.setCursor ( 19, 0 ); lcd.print("s");
    
    }
    //DIRECTION C:------------------------------------------------------------------------------------------------------
    count_C_f = count_C;
    if (sum != 0) {
      percentage_C = (count_C_f / sum) * 100;
    }
    else {
      percentage_C = (count_C_f / 1) * 100;
    }
    interval_C_f = percentage_C / 10; //minimum (10s)
    if (completed_C == 1) {
      interval_C = interval_C_f + 10;
    } else {
      interval_C = 10;
    }
    if (traffic_light == 8 && emergency==0) {     
        if(cc==1 && sec!=0){
        sec+=(interval_C-countdown);
        }
      countdown=countdown+(interval_C-countdown); 
      
      if (countdown != 0 && cc==0) {
          load_pos=0;tens=10;sec = countdown - 1;lcd.setCursor ( 0, 3 ); lcd.print("                    ");
          bb=0;aa=0;cc=1;
        }  
        if (crossing_active == 0) {
          lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");

       }
      lcd.setCursor ( 0, 0 ); lcd.print(">C:");
      lcd.setCursor ( 3, 0 ); lcd.print("     ");
      lcd.setCursor ( 3, 0 ); lcd.print(percentage_C);
      lcd.setCursor ( 8, 0 ); lcd.print("%");
      lcd.setCursor ( 10, 0 ); lcd.print("Cn:");
      lcd.setCursor ( 13, 0 ); lcd.print("   ");
      lcd.setCursor ( 13, 0 ); lcd.print(count_C);
      lcd.setCursor ( 15, 0 ); lcd.print("I:");
      lcd.setCursor ( 17, 0 ); lcd.print("  ");
      lcd.setCursor ( 17, 0 ); lcd.print(interval_C);
      lcd.setCursor ( 19, 0 ); lcd.print("s");
    
    }
    //dodatečný výpis------------------------------------------------------------------------------------------------------
    if(emergency==0){
    lcd.setCursor ( 0, 1 ); lcd.print("A:");
    lcd.setCursor ( 2, 1 ); lcd.print(reg_A);
    if (traffic_light == 1) {
      lcd.setCursor ( 2, 1 );
      lcd.print("G");
    }
    lcd.setCursor ( 4, 1 ); lcd.print("B:");
    lcd.setCursor ( 6, 1 ); lcd.print(reg_B);
    if (traffic_light == 4) {
      lcd.setCursor ( 6, 1 );
      lcd.print("G");
    }
    lcd.setCursor ( 8, 1 ); lcd.print("C:");
    lcd.setCursor ( 10, 1 ); lcd.print(reg_C);
    if (traffic_light == 8) {
      lcd.setCursor ( 10, 1 );
      lcd.print("G");
    }
    lcd.setCursor ( 12, 1 ); lcd.print("cross:");
    lcd.setCursor ( 18, 1 ); lcd.print(crossing_active);
    //lcd.setCursor ( 8, 2 ); lcd.print("z"); lcd.setCursor ( 10, 2 ); lcd.print(countdown); lcd.setCursor ( 13, 2 ); lcd.print("s");
    }else{lcd.setCursor ( 7, 2 ); lcd.print(crossing_active);}
    
    refresh = 0;
  }

if (emergency == 1 && priority==0) {
  if(traffic_light==1 && aa==0){if(sec==0){sec=9;load_pos=0;tens=10;lcd.setCursor ( 0, 3 ); lcd.print("                    ");}
        lcd.setCursor ( 0, 1 ); lcd.print("Prujezdny stav: >A ");
        lcd.setCursor ( 0, 2 ); lcd.print("         ");
        lcd.setCursor ( 0, 2 ); lcd.print("cross:");lcd.setCursor ( 7, 2 ); lcd.print(crossing_active);lcd.setCursor ( 14, 2 ); lcd.print("z"); lcd.setCursor ( 16, 2 ); lcd.print(countdown); lcd.setCursor ( 19, 2 ); lcd.print("s");
  ee=0;cc=0;bb=0;aa=1;
  }
  if(traffic_light==4 && bb==0){if(sec==0){sec=9;load_pos=0;tens=10;lcd.setCursor ( 0, 3 ); lcd.print("                    ");}
        lcd.setCursor ( 0, 1 ); lcd.print("Prujezdny stav: >B ");
        lcd.setCursor ( 0, 2 ); lcd.print("         ");
        lcd.setCursor ( 0, 2 ); lcd.print("cross:");lcd.setCursor ( 7, 2 ); lcd.print(crossing_active);lcd.setCursor ( 14, 2 ); lcd.print("z"); lcd.setCursor ( 16, 2 ); lcd.print(countdown); lcd.setCursor ( 19, 2 ); lcd.print("s");
  ee=0;cc=0;aa=0;bb=1;
  }
  if(traffic_light==8 && cc==0){if(sec==0){sec=9;load_pos=0;tens=10;lcd.setCursor ( 0, 3 ); lcd.print("                    ");}
        lcd.setCursor ( 0, 1 ); lcd.print("Prujezdny stav: >C ");
        lcd.setCursor ( 0, 2 ); lcd.print("         ");
        lcd.setCursor ( 0, 2 ); lcd.print("cross:");lcd.setCursor ( 7, 2 ); lcd.print(crossing_active);lcd.setCursor ( 14, 2 ); lcd.print("z"); lcd.setCursor ( 16, 2 ); lcd.print(countdown); lcd.setCursor ( 19, 2 ); lcd.print("s");
  ee=0;aa=0;bb=0;cc=1;    
      }
      if (traffic_light != 1 && traffic_light != 4 && traffic_light != 8 && idle == 0 && ee==0) {
      lcd.setCursor ( 0, 1 );
      lcd.print("Prujezdny stav: -  ");ee=1;    
  }
  if(traffic_light==1 && crossing_active==1){
        sec=0;
        }
  }
//odpocitavani na displeji jen pokud neprobihaji priority ani necinny stav
  if (idle == 0 && priority==0) {
    if (sec2 != sec) {
      if(emergency==1){
      lcd.setCursor ( 10, 2 ); lcd.print("  "); //3
      if (sec < 10) {
        sec_pos = 11; //4 3
      } else {
        sec_pos = 10;
      } lcd.setCursor ( sec_pos, 2 ); lcd.print(sec);
      }else{
        lcd.setCursor ( 4, 2 ); lcd.print("  "); //3
      if (sec < 10) {
        sec_pos = 5; //4 3
      } else {
        sec_pos = 4;
      } lcd.setCursor ( sec_pos, 2 ); lcd.print(sec);
      }
    }sec2 = sec;
    
    //zakomentovana moznost zobrazovani desetin:
    //if(tens2!=tens){lcd.setCursor ( 6, 2 );lcd.print("  ");
    //if(tens<10){sec_pos2=7;}else{sec_pos2=6;}lcd.setCursor ( sec_pos2, 2 );lcd.print(tens);}
    //tens2=tens;
  }
//SYMBOL NACITANI---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
switch (loading)
  {
    case 1:
      if (time_loading == 0) {
        loading_state = 2;
        load_pos = 0;
      }       
         if (idle == 0 && stop_loading == 0 && priority==0) {
          if(traffic_light==1 || traffic_light==4 || traffic_light==8){
          time_loading = ((countdown-1) * 1000) / 100;//100 stavů na displeji a *1000 milisec, 2 ctverecky nestíhá proto /110
          t_l1 = millis();loading = 2;
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
  if(prioritisation==5 || idle==1){
  switch (clck_up)
  {
    case 1:
        tc1 = millis();
        clck_up = 2;
      break;

    case 2:
      tc2 = millis();
      if (tc2 - tc1 > 1000) {
        lcd.setCursor ( sec_pos2-1, 3 ); lcd.print("   ");
          sec++;
          if(sec>59){lcd.setCursor ( min_pos-1, 3 ); lcd.print("   ");
          mins++;sec=0;}
          
         clck_up = 1;}
      
      break;
  }
  }
  //uvedení do nouzového stavu SP1-----------------------------------------------------------------------------------------------------------------------------------
  //fáze semaforu jdou postupne: A->B->C
  //pouze pokud prave neprobiha prioritizace IZS
  
  switch (sw8s) {
    case 0: if (digitalRead(sw[8]) == LOW) {
        sw8t1 = millis(); if(priority==0){emergency++;} digitalWrite(L8OP, HIGH); sw8s = 1;
      }
      break;
    case 1: sw8t2 = millis();
      if (sw8t2 - sw8t1 > time_sw) {
        sw8s = 2;
      }
      break;
    case 2: if (digitalRead(sw[8]) == HIGH) {
        digitalWrite(L8OP, LOW);
        sw8s = 0;
      }
      break;
  }

  if (emergency > 1) {
    lcd.setCursor ( 0, 0 ); lcd.print("                    ");//aby byl zachovan loading bar necistim cely displej
    lcd.setCursor ( 0, 1 ); lcd.print("                    ");
    lcd.setCursor ( 0, 2 ); lcd.print("                    "); 
     waiting_A=0;waiting_B=0;waiting_C=0;finish_A=0;
      aa = 0; bb = 0; cc = 0; ee = 0; //reset vypisu
      p1_A = 0; p1_B = 0; p1_C = 0;
      p2_A = 0; p2_B = 0; p2_C = 0;
      p3_A = 0; p3_B = 0; p3_C = 0;
      completed_A=0;completed_B=0;completed_C=0;
    refresh = 1; e = 0; 
    if (crossing_active == 0) {
      digitalWrite(G[1], HIGH); digitalWrite(SR12, HIGH);
    }
    emergency = 0;
  }
//emergency je dulezitejsi nez idle -> premuze jej: idle=0...
//aa,bb,cc,ee jsou ochrany proti nekonecnemu vypisovani na lcd
//take se zde nuluje odpocitavani(time_loading, load_pos, sec, loading_state) a odpocitavani primarne nastaveno na 10s
  if (emergency == 1) {
    if (e == 0) {
      aa = 0; bb = 0; cc = 0; ee = 0;
      //time_loading = 0; load_pos = 0; sec = 0; loading_state = 2; tens=10;     
      idle = 0; countdown = 10;refresh=1;
      lcd.setCursor ( 0, 0 ); lcd.print("                    ");//aby byl zachovan loading bar necistim cely displej
      lcd.setCursor ( 0, 1 ); lcd.print("                    ");
      lcd.setCursor ( 0, 2 ); lcd.print("                    ");
      lcd.setCursor ( 4, 0 ); lcd.print("NOUZOVY STAV");
      //lcd.setCursor( 5, 2 );lcd.print(".");
      //lcd.setCursor( 9, 2 );lcd.print("s");
      e = 1;
    }
    if (crossing_active == 1 && traffic_light == 1) {
      lcd.setCursor ( 0, 3 ); lcd.print("preruseno prechodem "); stop_loading = 1;
    }
    else {
      if (traffic_light == 4) {
        stop_loading = 0;
      }
    }
  }

  //RESET-------------------------------------------------------------------------------------------------------------------------------------------
  //dulezity pri idle stavu
  if (Reset == 1) {
    AtoC = 0; BtoA = 0; CtoB = 0;
    count_A = 0; count_B = 0; count_C = 0;
    count_A_f = 0; count_B_f = 0; count_C_f = 0;
    interval_A = 0; interval_B = 0; interval_C = 0;
    interval_A_f = 0; interval_B_f = 0; interval_C_f = 0;
    interval_A2 = 0; interval_B2 = 0; interval_C2 = 0;
    completed_A = 0; completed_B = 0; completed_C = 0;
    waiting_A = 0; waiting_B = 0; waiting_C = 0;
    reg_A = 0; reg_B = 0; reg_C = 0; finish_A = 0;
    if (idle == 0) {
      traffic_light = 0;
    }
    aa = 0; bb = 0; cc = 0; ee = 0;xx=0;
    time_loading = 0; load_pos = 0;sec_pos = 0; sec_pos2 = 0; sec = 0; loading_state = 2; //tens=10;
    loading = 1; clck_down = 1;clck_up = 0; mins=0;
    for(m=3;m<8;m++){
    digitalWrite(R[m], LOW); digitalWrite(Y[m], LOW); digitalWrite(G[m], LOW); 
    }
    digitalWrite(SG3, LOW);
    digitalWrite(SG4, LOW);
    digitalWrite(SG7, LOW);
    Reset = 0;
  }

  //uvedení do necinneho stavu------------------------------------------------------------------------------------------------------

  switch (sw7s) {
    case 0: if (digitalRead(sw[7]) == LOW) {
        sw7t1 = millis();
        if (emergency == 0 && priority==0) {
          idle++;
        } digitalWrite(L7OP, HIGH);
        sw7s = 1;
      }
      break;
    case 1: sw7t2 = millis(); if (sw7t2 - sw7t1 > time_sw) {
        sw7s = 2;
      }
      break;
    case 2: if (digitalRead(sw[7]) == HIGH) {
        digitalWrite(L7OP, LOW);
        sw7s = 0;
      }
      break;
  }
  if (idle > 1) {
    idle = 0;
  }

  if (idle == 1) {
    b = 0;
    if (d == 0) {
      if (crossing_active == 0) {
        digitalWrite(R[1], LOW);
        digitalWrite(G[1], LOW);
        digitalWrite(Y[1], LOW);
        digitalWrite(SR12, LOW);
        digitalWrite(SG12, LOW);
        d = 1;
      }
    }
    if (c == 0) {
      traffic_light = 12; Reset = 1; lcd.clear(); lcd.setCursor(4, 1 ); lcd.print("NECINNY STAV");
      fl_t1 = millis(); flashing = 1; c = 1;
    }
  }

  //blikání žluté signalizace------------------------------------------------------------------------------------------------------

  switch (flashing) {
    case 0:
      break;
    case 1:
    for(m=3;m<8;m++){
      digitalWrite(Y[m], HIGH);
    }
      if (crossing_active == 0) {
        digitalWrite(Y[1], HIGH);
      }
      fl_t2 = millis();
      if (fl_t2 - fl_t1 > 500) {
        fl_t3 = millis();
        flashing = 2;
      }
      break;
    case 2:
    for(n=3;n<8;n++){
      digitalWrite(Y[n], LOW);
    }
      if (crossing_active == 0) {
        digitalWrite(Y[1], LOW);
      }
      fl_t4 = millis();
      if (fl_t4 - fl_t3 > 500) {
        fl_t1 = millis();
        flashing = 1;
      }
      break;
  }

  //Činný stav, čtení senzorů------------------------------------------------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  if (idle == 0) {

    if (b == 0) {
      if (crossing_active == 0) {
        digitalWrite(G[1], HIGH);
        digitalWrite(SR12, HIGH);
      }
      lcd.clear(); refresh = 1; waiting_A = 1;
      for(m=1;m<8;m++){
      digitalWrite(Y[m], LOW);
      }
      flashing = 0; c = 0; d = 0; e = 0; Reset = 1; b = 1;
    }

    //c...ochrana proti opakovani disp: necinny
    //d...ochrana proti opakovani zhasnuti LED
    //e...pro spravny prepis disp, pokud nastane: z necinneho do nouzoveho
    //b...ochrana proti opakovani nastaveni pro cinny mod

    sensor1 = analogRead(A4);//1
    sensor2 = analogRead(A1);//2
    sensor3 = analogRead(A2);//3
    sensor4 = analogRead(A3);//4
    sensor5 = analogRead(A5);//5
    sensor6 = analogRead(A6);//6



    //čtení senzorů a tlačítek------------------------------------------------------------------------------------------------------

    switch (se1s) {
      case 0: if (sensor1 < 120) {
          se1t1 = millis();
          if (traffic_light == 1 && crossing_active == 0) {
            count_A++;
          }
          refresh = 1;
          se1s = 1;
        }
        break;
      case 1: se1t2 = millis(); if (se1t2 - se1t1 > time_se) {
          se1s = 2;
        }
        break;
      case 2: if (sensor1 > 120) {
          se1s = 0;
        }
        break;
    }
    switch (se2s) {
      case 0: if (sensor2 < 120) {
          se2t1 = millis();
          if (traffic_light == 1 && crossing_active == 0) {
            count_A++;
          } refresh = 1;
          se2s = 1;
        }
        break;
      case 1: se2t2 = millis(); if (se2t2 - se2t1 > time_se) {
          se2s = 2;
        }
        break;
      case 2: if (sensor2 > 120) {
          se2s = 0;
        }
        break;
    }
    switch (se3s) {
      case 0: if (sensor3 < 120) {
          se3t1 = millis();
          if (traffic_light == 4) {
            count_B++;
          } refresh = 1;
          se3s = 1;
        }
        break;
      case 1: se3t2 = millis(); if (se3t2 - se3t1 > time_se) {
          se3s = 2;
        }
        break;
      case 2: if (sensor3 > 120) {
          se3s = 0;
        }
        break;
    }
    switch (se4s) {
      case 0: if (sensor4 < 120) {
          se4t1 = millis();
          if (traffic_light == 4) {
            count_B++;
          } refresh = 1;
          se4s = 1;
        }
        break;
      case 1: se4t2 = millis(); if (se4t2 - se4t1 > time_se) {
          se4s = 2;
        }
        break;
      case 2: if (sensor4 > 120) {
          se4s = 0;
        }
        break;
    }
    switch (se5s) {
      case 0: if (sensor5 < 120) {
          se5t1 = millis();
          if (traffic_light == 8) {
            count_C++;
          } refresh = 1;
          se5s = 1;
        }
        break;
      case 1: se5t2 = millis(); if (se5t2 - se5t1 > time_se) {
          se5s = 2;
        }
        break;
      case 2: if (sensor5 > 120) {
          se5s = 0;
        }
        break;
    }
    switch (se6s) {
      case 0: if (sensor6 < 120) {
          se6t1 = millis();
          if (traffic_light == 8) {
            count_C++;
          } refresh = 1;
          se6s = 1;
        }
        if (ind_sensor > 550) {
          se6t1 = millis();
          if (traffic_light == 8) {
            count_C++;
          } refresh = 1;
          se6s = 3;
        }
        break;
      case 1: se6t2 = millis(); if (se6t2 - se6t1 > time_se) {
          se6s = 2;
        }
        break;
      case 2: if (sensor6 > 120) {
          se6s = 0;
        }
        break;
      case 3: se6t2 = millis(); if (se6t2 - se6t1 > time_se) {
          se6s = 4;
        }
        break;
      //ceka se az vozidlo opusti obe cidla aby se nepricetlo dvakrat
      case 4: if (ind_sensor < 550 && sensor6 > 120) {
          se6s = 0;
        }
        break;
    }

    switch (sw1s) {
      case 0: if (digitalRead(sw[1]) == LOW) {
          sw1t1 = millis();
          if (traffic_light == 1) {
            count_A++;
          };
          refresh = 1;
          sw1s = 1;
        }
        break;
      case 1: sw1t2 = millis(); if (sw1t2 - sw1t1 > time_sw) {
          sw1s = 2;
        }
        break;
      case 2: if (digitalRead(sw[1]) == HIGH) {
          sw1s = 0;
        }
        break;
    }

    switch (sw2s) {
      case 0: if (digitalRead(sw[2]) == LOW) {
          sw2t1 = millis();
          if (traffic_light == 1 && crossing_active == 0) {
            count_A++;
          };
          refresh = 1;
          sw2s = 1;
        }
        break;
      case 1: sw2t2 = millis(); if (sw2t2 - sw2t1 > time_sw) {
          sw2s = 2;
        }
        break;
      case 2: if (digitalRead(sw[2]) == HIGH) {
          sw2s = 0;
        }
        break;
    }
    switch (sw3s) {
      case 0: if (digitalRead(sw[3]) == LOW) {
          sw3t1 = millis();
          if (traffic_light == 4) {
            count_B++;
          } refresh = 1;
          sw3s = 1;
        }
        break;
      case 1: sw3t2 = millis(); if (sw3t2 - sw3t1 > time_sw) {
          sw3s = 2;
        }
        break;
      case 2: if (digitalRead(sw[3]) == HIGH) {
          sw3s = 0;
        }
        break;
    }
    switch (sw4s) {
      case 0: if (digitalRead(sw[4]) == LOW) {
          sw4t1 = millis();
          if (traffic_light == 4) {
            count_B++;
          } refresh = 1;
          sw4s = 1;
        }
        break;
      case 1: sw4t2 = millis(); if (sw4t2 - sw4t1 > time_sw) {
          sw4s = 2;
        }
        break;
      case 2: if (digitalRead(sw[4]) == HIGH) {
          sw4s = 0;
        }
        break;
    }
    switch (sw5s) {
      case 0: if (digitalRead(sw[5]) == LOW) {
          sw5t1 = millis();
          if (traffic_light == 8) {
            count_C++;
          } refresh = 1;
          sw5s = 1;
        }
        break;
      case 1: sw5t2 = millis(); if (sw5t2 - sw5t1 > time_sw) {
          sw5s = 2;
        }
        break;
      case 2: if (digitalRead(sw[5]) == HIGH) {
          sw5s = 0;
        }
        break;
    }
    switch (sw6s) {
      case 0: if (digitalRead(sw[6]) == LOW) {
          sw6t1 = millis();
          if (traffic_light == 8) {
            count_C++;
          } refresh = 1;
          sw6s = 1;
        }
        break;
      case 1: sw6t2 = millis(); if (sw6t2 - sw6t1 > time_sw) {
          sw6s = 2;
        }
        break;
      case 2: if (digitalRead(sw[6]) == HIGH) {
          sw6s = 0;
        }
        break;
    }
    //sw7, 8 je mimo podminku necinneho stavu

    switch (swcross1s) {
      case 0: if (digitalRead(swcross1) == LOW) {
          swcross1t1 = millis();
          i++;
          swcross1s = 1;
        }
        break;
      case 1: swcross1t2 = millis(); if (swcross1t2 - swcross1t1 > time_sw) {
          swcross1s = 2;
        }
        break;
      case 2: if (digitalRead(swcross1) == HIGH) {
          swcross1s = 0;
        }
        break;
    }
    switch (swcross2s) {
      case 0: if (digitalRead(swcross2) == LOW) {
          swcross2t1 = millis();
          j++;
          swcross2s = 1;
        }
        break;
      case 1: swcross2t2 = millis(); if (swcross2t2 - swcross2t1 > time_sw) {
          swcross2s = 2;
        }
        break;
      case 2: if (digitalRead(swcross2) == HIGH) {
          swcross2s = 0;
        }
        break;
    }
  }
  //sekvence řízení ------------------------------------------------------------------------------------------------------

  switch (traffic_light) {
    //SMER A:
    case 0:
      trl01 = millis();
      if (reg_A == 0) {
        count_A = 0;
      } else {
        count_A = 1;
      }
      refresh = 1;
      traffic_light = 1;
      break;
    case 1: //GREEN DIRECTION A-----------------------------------------------------------------------------------------------------------------------

      //zakomentované pro vypmuni semaforu 6 s prechodem (zbytecne)
      if (finish_A == 0) {
        reg_A = 0;
        //if(crossing_active==0){digitalWrite(G6,HIGH);digitalWrite(R6,LOW);}else{digitalWrite(G6,LOW);if(BtoA==1){digitalWrite(R6,HIGH);}}
        digitalWrite(G[6], HIGH);digitalWrite(G[7], HIGH); digitalWrite(SG4, HIGH); digitalWrite(SG3, HIGH);
        digitalWrite(Y[6], LOW);digitalWrite(Y[7], LOW);
        digitalWrite(R[3], HIGH);digitalWrite(R[4], HIGH);digitalWrite(R[5], HIGH);
        digitalWrite(R[6], LOW);digitalWrite(R[7], LOW);
        finish_A = 1;
      }
      if (crossing_active == 0) {
        BtoA = 0;
      }

      //registrovani vozidel z jiných směrů, zakomentované senzory mají vyklizovací šipkou zelenou

      if (reg_B == 0) {
        //if(sensor3<120){reg_B=1;refresh=1;}
        if (sensor4 < 120) {
          reg_B = 1;
          refresh = 1;
        }
        //if(digitalRead(sw3)==LOW){reg_B=1;refresh=1;}
        if (digitalRead(sw[4]) == LOW) {
          reg_B = 1;
          refresh = 1;
        }
      }
      if (reg_C == 0) {
        //if(sensor5<120){reg_C=1;refresh=1;}
        if (sensor6 < 120) {
          reg_C = 1;
          refresh = 1;
        }
        if (ind_sensor > 550) {
          reg_C = 1;
          refresh = 1;
        }
        //if(digitalRead(sw5)==LOW){reg_C=1;refresh=1;}
        if (digitalRead(sw[6]) == LOW) {
          reg_C = 1;
          refresh = 1;
        }
      }
      if (crossing_active == 0) {
        trl02 = millis();
        //osetreni proti maximalnimu intervalu na zacatku (první zelená v danem smeru, krizovatka se jeste uci)
        if (completed_A == 1 && emergency == 0) {
          interval_A2 = (interval_A * 1000);
        } else {
          interval_A2 = 10000;
        }
        if (trl02 - trl01 > interval_A2) {
          if (emergency == 1) {
            trl11 = millis();
            traffic_light = 2;
          }
          else {
            waiting_A = 1;
          }
        }
      }
      //setrvání v daném stavu, než bude registrováno vozidlo z jinych smeru
      if (waiting_A == 1) {
        if (reg_C == 1 && reg_B == 0) {
          if (crossing_active == 0) {
            completed_A = 1;
            BtoA = 0;
            waiting_A = 0;
            trl41 = millis();
            AtoC = 1;
            count_B = 0;
            refresh = 1;
            traffic_light = 5;
          }
        }
        if (reg_B == 1 && reg_C == 0) {
          if (crossing_active == 0) {
            completed_A = 1;
            BtoA = 0;
            waiting_A = 0;
            trl11 = millis();
            AtoC = 0;
            traffic_light = 2;
          }
        }
        if (reg_B == 1 && reg_C == 1) {
          if (crossing_active == 0) {
            completed_A = 1;
            BtoA = 0;
            waiting_A = 0;
            trl11 = millis();
            AtoC = 0;
            traffic_light = 2;
          }
        }
      }

      break;
    case 2: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------
      //mohu dvěma směry bud z A do B (CtoB==0) nebo z C preskocit A do B (CtoB==1)

      finish_A = 0;
      if (CtoB == 1) {
        digitalWrite(G[5], LOW);digitalWrite(G[6], LOW);
        digitalWrite(Y[5], HIGH);digitalWrite(Y[6], HIGH);
      }
      if (CtoB == 0) {
        digitalWrite(G[6], LOW);digitalWrite(G[7], LOW);
        digitalWrite(Y[6], HIGH);digitalWrite(Y[7], HIGH);
      }

      trl12 = millis();
      if (trl12 - trl11 > 3000) {
        trl21 = millis();
        traffic_light = 3;
      }
      break;
    case 3: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (CtoB == 1) {
        digitalWrite(Y[5], LOW);digitalWrite(Y[6], LOW);
        digitalWrite(R[5], HIGH);digitalWrite(R[6], HIGH);
      }
      if (CtoB == 0) {
        digitalWrite(Y[6], LOW);digitalWrite(Y[7], LOW);
        digitalWrite(R[6], HIGH);digitalWrite(R[7], HIGH);
      }
      //pocita to s jednim autem kdyz bylo zaregistrovano
      trl22 = millis();
      if (trl22 - trl21 > 1000) {
        trl441 = millis();
        traffic_light = 44;
      }
      break;
    case 44://RED + YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (CtoB == 1) {
        digitalWrite(Y[4], HIGH);
      }
      if (CtoB == 0) {
        digitalWrite(Y[3], HIGH);digitalWrite(Y[4], HIGH);
      }
      trl442 = millis();
      if (trl442 - trl441 > 2000) {
        trl31 = millis(); if (reg_B == 0) {
          count_B = 0;
        } else {
          count_B = 1;
        };
        refresh = 1; traffic_light = 4;
      }

      break;
    case 4: //GREEN DIRECTION B-----------------------------------------------------------------------------------------------------------------------
      CtoB = 0;
      reg_B = 0;
      if (reg_A == 0) {
        if (sensor1 < 120) {
          reg_A = 1;
          refresh = 1;
        }
        if (sensor2 < 120) {
          reg_A = 1;
          refresh = 1;
        }
        if (digitalRead(sw[1]) == LOW) {
          reg_A = 1;
          refresh = 1;
        }
        if (digitalRead(sw[2]) == LOW) {
          reg_A = 1;
          refresh = 1;
        }
      }
      if (reg_C == 0) {
        //if(sensor5<120){reg_C=1;refresh=1;}
        if (sensor6 < 120) {
          reg_C = 1;
          refresh = 1;
        }
        if (ind_sensor > 550) {
          reg_C = 1;
          refresh = 1;
        }
        //if(digitalRead(sw5)==LOW){reg_C=1;refresh=1;}
        if (digitalRead(sw[6]) == LOW) {
          reg_C = 1;
          refresh = 1;
        }
      }
      if (CtoB == 0) {
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);
      }
      digitalWrite(G[3], HIGH);digitalWrite(G[4], HIGH); digitalWrite(SG7, HIGH);
      digitalWrite(Y[3], LOW);digitalWrite(Y[4], LOW);
      digitalWrite(R[3], LOW);digitalWrite(R[4], LOW);
      trl32 = millis();

      if (completed_B == 1 && emergency == 0) {
        interval_B2 = (interval_B * 1000);
      } else {
        interval_B2 = 10000;
      };
      if (trl32 - trl31 > interval_B2) {
        if (emergency == 1) {
          trl41 = millis();
          traffic_light = 5;
        }
        else {
          waiting_B = 1;
        }
      }

      if (waiting_B == 1) {
        if (reg_A == 1 && reg_C == 0) {
          completed_B = 1;
          waiting_B = 0;
          trl91 = millis();
          BtoA = 1;
          count_C = 0;
          refresh = 1;
          traffic_light = 9;
        }
        if (crossing_active == 1 && reg_C == 0) {
          completed_B = 1;
          waiting_B = 0;
          trl91 = millis();
          BtoA = 1;
          count_C = 0;
          refresh = 1;
          traffic_light = 9;
        }
        if (reg_C == 1 && reg_A == 0) {
          completed_B = 1;
          waiting_B = 0;
          trl41 = millis();
          BtoA = 0;
          traffic_light = 5;
        }
        if (reg_C == 1 && reg_A == 1) {
          completed_B = 1;
          waiting_B = 0;
          trl41 = millis();
          BtoA = 0;
          traffic_light = 5;
        }
      }

      break;
    case 5: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      finish_A = 0;

      if (AtoC == 1) {
        digitalWrite(G[7], LOW);
        digitalWrite(Y[7], HIGH);
      }
      //BtoC
      if (AtoC == 0) {
        digitalWrite(SG7, LOW);
        digitalWrite(G[4], LOW);
        digitalWrite(Y[4], HIGH);
      }
      trl42 = millis();
      if (trl42 - trl41 > 3000) {
        trl61 = millis();
        traffic_light = 6;
      }
      break;
    case 6: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (AtoC == 1) {
        digitalWrite(SG4, LOW);
        digitalWrite(Y[7], LOW);
        digitalWrite(R[7], HIGH);
      }
      if (AtoC == 0) {

        digitalWrite(Y[4], LOW);
        digitalWrite(R[4], HIGH);
      }
      trl62 = millis();
      if (trl62 - trl61 > 1000) {
        trl71 = millis();
        traffic_light = 7;
      }

      break;
    case 7: //YELLOW + RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (AtoC == 1) {
        digitalWrite(Y[3], HIGH);digitalWrite(Y[5], HIGH);

      }
      if (AtoC == 0) {
        digitalWrite(Y[5], HIGH);digitalWrite(Y[6], HIGH);
      }
      trl72 = millis();
      if (trl72 - trl71 > 2000) {
        trl81 = millis(); if (reg_C == 0) {
          count_C = 0;
        } else {
          count_C = 1;
        };
        refresh = 1; traffic_light = 8;
      }

      break;
    case 8: //GREEN DIRECTION C-----------------------------------------------------------------------------------------------------------------------

      reg_C = 0;
      AtoC = 0;
      if (reg_A == 0) {
        if (sensor1 < 120) {
          reg_A = 1;
          refresh = 1;
        }
        //if(sensor2<120){reg_A=1;refresh=1;}
        if (digitalRead(sw[1]) == LOW) {
          reg_A = 1;
          refresh = 1;
        }
        //if(digitalRead(sw2)==LOW){reg_A=1;refresh=1;}
      }
      if (reg_B == 0) {
        if (sensor3 < 120) {
          reg_B = 1;
          refresh = 1;
        }
        if (sensor4 < 120) {
          reg_B = 1;
          refresh = 1;
        }
        if (digitalRead(sw[3]) == LOW) {
          reg_B = 1;
          refresh = 1;
        }
        if (digitalRead(sw[4]) == LOW) {
          reg_B = 1;
          refresh = 1;
        }
      }

      digitalWrite(G[3], HIGH);digitalWrite(G[5], HIGH);digitalWrite(G[6], HIGH); digitalWrite(SG3, LOW);
      digitalWrite(Y[3], LOW);digitalWrite(Y[5], LOW);digitalWrite(Y[6], LOW);
      digitalWrite(R[3], LOW);digitalWrite(R[5], LOW);digitalWrite(R[6], LOW);

      trl82 = millis();
      if (completed_C == 1 && emergency == 0) {
        interval_C2 = (interval_C * 1000);
      } else {
        interval_C2 = 10000;
      };
      if (trl82 - trl81 > interval_C2) {
        if (emergency == 1) {
          trl91 = millis();
          traffic_light = 9;
        }
        else {
          waiting_C = 1;
        }
      }


      if (waiting_C == 1) {
        if (reg_B == 1 && reg_A == 0) {
          completed_C = 1;
          waiting_C = 0;
          trl11 = millis();
          CtoB = 1;
          count_A = 0;
          refresh = 1;
          traffic_light = 2;
        }
        if (reg_A == 1 && reg_B == 0) {
          completed_C = 1;
          waiting_C = 0;
          trl91 = millis();
          CtoB = 0;
          traffic_light = 9;
        }
        if (reg_A == 1 && reg_B == 1) {
          completed_C = 1;
          waiting_C = 0;
          trl91 = millis();
          CtoB = 0;
          traffic_light = 9;
        }
        if (crossing_active == 1) {
          completed_C = 1;
          waiting_C = 0;
          trl91 = millis();
          CtoB = 0;
          traffic_light = 9;
        }
      }
      break;
    case 9: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (BtoA == 1) {
        digitalWrite(G[3], LOW);digitalWrite(G[4], LOW); digitalWrite(SG4, HIGH);
        digitalWrite(Y[3], HIGH);digitalWrite(Y[4], HIGH);
      }
      if (BtoA == 0) {
        digitalWrite(G[3], LOW);digitalWrite(G[5], LOW);
        digitalWrite(Y[3], HIGH);digitalWrite(Y[5], HIGH);
      }
      trl92 = millis();
      if (trl92 - trl91 > 3000) {
        trl101 = millis();
        traffic_light = 10;
      }
      break;
    case 10: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

      if (BtoA == 1) {
        digitalWrite(Y[3], LOW);digitalWrite(Y[4], LOW); digitalWrite(SG7, LOW);
        digitalWrite(R[3], HIGH);digitalWrite(R[4], HIGH);
      }
      if (BtoA == 0) {
        digitalWrite(Y[3], LOW);digitalWrite(Y[5], LOW);  
        digitalWrite(R[3], HIGH);digitalWrite(R[5], HIGH);
      }
      trl102 = millis();
      if (trl102 - trl101 > 1000) {
        trl111 = millis();
        traffic_light = 11;
      }

      break;
    case 11://RED + YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------
      if (BtoA == 1) {
        digitalWrite(Y[6], HIGH);digitalWrite(Y[7], HIGH);
      }
      if (BtoA == 0) {
        digitalWrite(Y[7], HIGH);
      }

      trl112 = millis();
      if (trl112 - trl111 > 2000) {
        traffic_light = 0;
      }
      break;
    case 12:
      //idle state
      break;
  }
//KONFIGURACE OVLADAČE---------------------------------------------------------------------------------------------------------------------------------------

  if (IrReceiver.decode()) {
    IrReceiver.resume();
//vypinani/ preruseni priority, muze pokracovat jen pokud vse dokonano
    if (IrReceiver.decodedIRData.command == 0x45) { 
      if(prioritisation==5 && priority !=0){
      prioritisation = 6;
      }     
    }
//pouze pokud prave neprobiha prioritizace...
    if (prioritisation == 5 && idle==0 && priority==0) { 
      if (IrReceiver.decodedIRData.command == 0xC) {
        refresh=1;loading = 1; prioritisation = 0; priority = 1;
      }
      if (IrReceiver.decodedIRData.command == 0x18) {
        refresh=1;loading = 1; prioritisation = 0; priority = 2;
      }
      if (IrReceiver.decodedIRData.command == 0x5E) {
        refresh=1;loading = 1; prioritisation = 0; priority = 3;
      }
    }
  }

  if(priority!=0 || idle==1){
    if(xx==0){
      clck_down=0;clck_up=1;sec=0;
      if(idle==0){
      lcd.setCursor ( 6, 2 ); lcd.print("cross:");lcd.setCursor ( 13, 2 ); lcd.print(crossing_active);
      lcd.clear(); lcd.setCursor ( 2, 0 ); lcd.print("Prioritizace IZS");
      }
      lcd.setCursor ( 0, 3 ); lcd.print("po dobu:");
      sec_pos2=10;
      xx=1;
      }
    if(refresh!=0){
      lcd.setCursor ( 6, 2 ); lcd.print("cross:");lcd.setCursor ( 13, 2 ); lcd.print(crossing_active);
      refresh=0;
      }

    if(sec<10 && mins==0){sec_pos2=10;
    lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
    lcd.setCursor ( 12, 3 ); lcd.print("s");
    }
    if(sec>9 && mins==0){sec_pos2=9;
    lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
    lcd.setCursor ( 12, 3 ); lcd.print("s");
    }
    if(sec>9 && mins!=0){sec_pos2=16;
    lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
    lcd.setCursor ( 19, 3 ); lcd.print("s");
    }
    if(sec<10 && mins!=0){sec_pos2=17;
    lcd.setCursor ( sec_pos2, 3 ); lcd.print(sec);
    lcd.setCursor ( 19, 3 ); lcd.print("s");
    }
    if(mins>9){min_pos=9;}
    if(mins!=0){
    lcd.setCursor ( min_pos, 3 ); lcd.print(mins);
    lcd.setCursor ( 12, 3 ); lcd.print("min");
    }
    }

  //PRIORITIZACE IZS------------------------------------------------------------------------------------------------------------------------------------------
  //nejprve se navaze, potom se prispusobuji led tak aby byl prujezdny stav pouze v jednom smeru
  switch (prioritisation) {
    case 0:
      
      if (priority == 1 && traffic_light == 1) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru A");
        tp1 = millis(); p1_A = 1; traffic_light = 12; prioritisation = 1;
      }//A
      if (priority == 1 && traffic_light == 4) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru A");
        tp1 = millis(); p1_B = 1; traffic_light = 12; prioritisation = 1;
      }//B
      if (priority == 1 && traffic_light == 8) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru A");
        tp1 = millis(); p1_C = 1; traffic_light = 12; prioritisation = 1;
      }//C

      if (priority == 2 && traffic_light == 1) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru B");
        tp1 = millis(); p2_A = 1; traffic_light = 12; prioritisation = 1;
      }
      if (priority == 2 && traffic_light == 4) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru B");
        tp1 = millis(); p2_B = 1; traffic_light = 12; prioritisation = 1;
      }
      if (priority == 2 && traffic_light == 8) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru B");
        tp1 = millis(); p2_C = 1; traffic_light = 12; prioritisation = 1;
      }

      if (priority == 3 && traffic_light == 1) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru C");
        tp1 = millis(); p3_A = 1; traffic_light = 12; prioritisation = 1;
      }
      if (priority == 3 && traffic_light == 4) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru C");
        tp1 = millis(); p3_B = 1; traffic_light = 12; prioritisation = 1;
      }
      if (priority == 3 && traffic_light == 8) {
        lcd.setCursor ( 1, 1 ); lcd.print("Prijezd ze smeru C");
        tp1 = millis(); p3_C = 1; traffic_light = 12; prioritisation = 1;
      }

      break;
    case 1:
      if (p1_A == 1) {
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);
      }
      if (p1_B == 1) {
        digitalWrite(G[3], LOW);digitalWrite(G[4], LOW);
        digitalWrite(SG7, LOW);
        digitalWrite(Y[3], HIGH);digitalWrite(Y[4], HIGH);
      }
      if (p1_C == 1) {
        digitalWrite(G[3], LOW);digitalWrite(G[5], LOW);
        digitalWrite(Y[3], HIGH);digitalWrite(Y[5], HIGH);
      }
      if (p2_A == 1) {
        digitalWrite(G[6], LOW);digitalWrite(G[7], LOW);
        digitalWrite(Y[6], HIGH);digitalWrite(Y[7], HIGH);
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);
        
      }
      if (p2_B == 1) {
        digitalWrite(G[3], LOW);
        digitalWrite(Y[3], HIGH);
      }
      if (p2_C == 1) {
        digitalWrite(G[3], LOW);digitalWrite(G[5], LOW);digitalWrite(G[6], LOW);
        digitalWrite(Y[3], HIGH);digitalWrite(Y[5], HIGH);digitalWrite(Y[6], HIGH);
      }
      if (p3_A == 1) {
        digitalWrite(SG3, LOW);
        digitalWrite(SG4, LOW);
        digitalWrite(G[6], LOW);digitalWrite(G[7], LOW);
        digitalWrite(Y[6], HIGH);digitalWrite(Y[7], HIGH);
      }
      if (p3_B == 1) {
        digitalWrite(SG7, LOW);
        digitalWrite(G[4], LOW);
        digitalWrite(Y[4], HIGH);
      }
      if (p3_C == 1) {
        digitalWrite(G[6], LOW);
        digitalWrite(Y[6], HIGH);
      }
      tp2 = millis();
      if (tp2 - tp1 > 3000) {
        tp3 = millis();
        prioritisation = 2;
      }
      break;

    case 2:
      //if(p1_A==1){}
      if (p1_B == 1) {
        digitalWrite(Y[3], LOW);digitalWrite(Y[4], LOW);
        digitalWrite(R[3], HIGH);digitalWrite(R[4], HIGH);
      }
      if (p1_C == 1) {
        digitalWrite(Y[3], LOW);digitalWrite(Y[5], LOW);
        digitalWrite(R[3], HIGH);digitalWrite(R[5], HIGH);
      }
      if (p2_A == 1) {
        digitalWrite(Y[6], LOW);digitalWrite(Y[7], LOW);
        digitalWrite(R[6], HIGH);digitalWrite(R[7], HIGH);
      }
      if (p2_B == 1) {
        digitalWrite(Y[3], LOW);
        digitalWrite(R[3], HIGH);
      }
      if (p2_C == 1) {
        digitalWrite(Y[3], LOW);digitalWrite(Y[5], LOW);digitalWrite(Y[6], LOW);
        digitalWrite(R[3], HIGH);digitalWrite(R[5], HIGH);digitalWrite(R[6], HIGH);
      }
      if (p3_A == 1) {
        digitalWrite(Y[6], LOW);digitalWrite(Y[7], LOW);
        digitalWrite(R[6], HIGH);digitalWrite(R[7], HIGH);
      }
      if (p3_B == 1) {
        digitalWrite(Y[4], LOW);
        digitalWrite(R[4], HIGH);
      }
      if (p3_C == 1) {
        digitalWrite(Y[6], LOW);
        digitalWrite(R[6], HIGH);
      }
      tp4 = millis();
      if (tp4 - tp3 > 1000) {
        tp5 = millis();
        prioritisation = 3;
      }
      break;

    case 3:
      //if(p1_A==1){}
      if (p1_B == 1) {
        digitalWrite(Y[6], HIGH); digitalWrite(Y[7], HIGH);
      }
      if (p1_C == 1) {
        digitalWrite(Y[7], HIGH);
      }
      if (p2_A == 1) {
        digitalWrite(Y[4], HIGH);
      }
      //if(p2_B==1){}
      if (p2_C == 1) {
        digitalWrite(Y[4], HIGH);
      }
      if (p3_A == 1) {
        digitalWrite(Y[3], HIGH);digitalWrite(Y[5], HIGH);
      }
      if (p3_B == 1) {
        digitalWrite(Y[5], HIGH);
      }
      //if(p3_C==1){}
      tp6 = millis();
      if (tp6 - tp5 > 2000) {
        prioritisation = 4;
      }
      break;

    case 4:
      //if(p1_A==1){}
      if (p1_B == 1) {
        digitalWrite(G[6], HIGH);digitalWrite(G[7], HIGH);
        digitalWrite(Y[6], LOW);digitalWrite(Y[7], LOW);
        digitalWrite(R[6], LOW);digitalWrite(R[7], LOW);
      }
      if (p1_C == 1) {
        digitalWrite(G[7], HIGH);
        digitalWrite(Y[7], LOW);
        digitalWrite(R[7], LOW);
      }
      if (p2_A == 1) {
        digitalWrite(G[4], HIGH);
        digitalWrite(SG7, HIGH);
        digitalWrite(Y[4], LOW);
        digitalWrite(R[4], LOW);
      }
      //if(p2_B==1){}
      if (p2_C == 1) {
        digitalWrite(G[4], HIGH);
        digitalWrite(SG7, HIGH);
        digitalWrite(Y[4], LOW);
        digitalWrite(R[4], LOW);
      }
      if (p3_A == 1) {
        digitalWrite(G[3], HIGH);digitalWrite(G[5], HIGH);
        digitalWrite(Y[3], LOW);digitalWrite(Y[5], LOW);
        digitalWrite(R[3], LOW);digitalWrite(R[5], LOW);
      }
      if (p3_B == 1) {
        digitalWrite(G[5], HIGH);
        digitalWrite(Y[5], LOW);
        digitalWrite(R[5], LOW);
      }
      //if(p3_C==1){}
      prioritisation = 5;
      break;
      
      //idle state, cekani na ukonceni priority:
    case 5:
      
      break;
      //navazani zpet z priority do bezneho provozu:
    case 6:
      if(p1_A || p1_B || p1_C){
        digitalWrite(SG3,HIGH);digitalWrite(SG4,HIGH);AtoC = 0; BtoA = 0; CtoB = 0;waiting_A=0;trl01 = millis();traffic_light=1;prioritisation = 8;
      }
      if(p2_A || p2_B || p2_C){
        digitalWrite(Y[3],HIGH);tp7=millis();prioritisation = 7;
      }
      if(p3_A || p3_B || p3_C){
        digitalWrite(Y[6],HIGH);tp7=millis();prioritisation = 7;
      }
      break;

    case 7:
      tp8=millis();
      if(tp8-tp7>2000){
        if(p2_A || p2_B || p2_C){
        digitalWrite(Y[3],LOW);digitalWrite(R[3],LOW);AtoC = 0; BtoA = 0; CtoB = 0;waiting_B=0;trl31=millis();traffic_light=4;prioritisation = 8;
          }
        if(p3_A || p3_B || p3_C){
        digitalWrite(Y[6],LOW);digitalWrite(R[6],LOW);AtoC = 0; BtoA = 0; CtoB = 0;waiting_C=0;trl81=millis();traffic_light=8;prioritisation = 8;
          }
        }
      break;
//konecny stav
    case 8: 
      clck_down=1;clck_up=0;sec=10;xx=0;mins=0;min_pos=10;sec_pos2=10;   
      priority = 0; lcd.clear();refresh=1; //reset displeje
      waiting_A=0;waiting_B=0;waiting_C=0;finish_A=0;
      aa = 0; bb = 0; cc = 0; ee = 0; //reset vypisu
      p1_A = 0; p1_B = 0; p1_C = 0; //reset nastaveni priority
      p2_A = 0; p2_B = 0; p2_C = 0;
      p3_A = 0; p3_B = 0; p3_C = 0;
      completed_A=0;completed_B=0;completed_C=0;
      
      //kdyz nastane prioritizace behem nouzoveho stavu je treba znovu vypsat:
      if(emergency==1){
        lcd.setCursor ( 4, 0 ); lcd.print("NOUZOVY STAV");
        }
        prioritisation = 5;
      break;
  }

  //CROSSING-----------------------------------------------------------------------------------------------------------------------------
  //vypis pozadavku na prechod (i,j jsou tlačítka na prechodu), osetreni proti neustalemu vypisovani na display

  if (i != 0) {
    crossing_active = 1;
    if (a == 0) {
      refresh = 1;
      a = 1;
    }
  }
  if (j != 0) {
    crossing_active = 1;
    if (a == 0) {
      refresh = 1;
      a = 1;
    }
  }

  //podminka pro umozneni spusteni prechodu: (muselo být: spusteno tlacitko prechodu, musi být: rizeni v jednicce(smerA), instrukce pro směr A musely být vykonány, prechod musel byt dokoncen minimalne pred 10s)
  if (crossing_active == 1 && traffic_light == 1 && cross == 6 && finish_A == 1 && finish_cross4 == 0 && priority == 0) {
    tc01 = millis();
    cross = 0;
  };

  switch (cross) {
    //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------------
    case 0:
      //if(idle==0 && BtoA==0){digitalWrite(G6,LOW);digitalWrite(Y6,HIGH);}
      digitalWrite(G[1], LOW);
      digitalWrite(Y[1], HIGH);
      tc02 = millis();
      if (tc02 - tc01 > 3000) {
        tc11 = millis();
        cross = 1;
      }

      break;
    //RED SEQUENCE--------------------------------------------------------------------------------------------------------------------------
    case 1:
      //if(idle==0 && BtoA==0){digitalWrite(Y6,LOW);digitalWrite(R6,HIGH);}
      digitalWrite(Y[1], LOW);
      digitalWrite(R[1], HIGH);
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
      if (priority!=0) {
        cross = 3; //preskoceni zelene na prechodu kdyz projizdi IZS
      }
      tc22 = millis();
      if (tc22 - tc21 > 5000) {
        tc31 = millis();
        cross = 3;
      }
      //real = 10s

      break;
    //YELLOW SEQUENCE------------------------------------------------------------------------------------------------------------------------
    case 3:
      digitalWrite(SG12, LOW);
      digitalWrite(SR12, HIGH);
      tc32 = millis();
      if (tc32 - tc31 > 2000) {
        tc41 = millis();
        cross = 4;
      }

      break;
    case 4:
      //if(idle==0){digitalWrite(Y6,HIGH);}
      digitalWrite(Y[1], HIGH);
      tc42 = millis();
      if (tc42 - tc41 > 2000) {
        tc51 = millis();
        cross = 5;
      }

      break;
    case 5:
      if (finish_cross4 == 0) {
        //if(idle==0){digitalWrite(G6,HIGH);digitalWrite(Y6,LOW);digitalWrite(R6,LOW);waiting_A=1;}
        if (idle == 0) {
          waiting_A = 1;
        }
        digitalWrite(G[1], HIGH);
        digitalWrite(Y[1], LOW);
        digitalWrite(R[1], LOW);
        BtoA = 0; i = 0; j = 0; a = 0; refresh = 1; crossing_active = 0;
        finish_cross4 = 1;
      }
      //osetreni proti opakovani, aby se nespustil přechod hned znovu, čekání 10s:
      tc52 = millis();
      if (tc52 - tc51 > 10000) {
        cross = 6;
      }

      break;
    case 6:

      finish_cross4 = 0;
      //umozneno dalsi spusteni
      //stand-by
      break;
  }
}

```
