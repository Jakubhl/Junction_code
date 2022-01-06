```c

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte a;
byte b;
byte g;
byte h;
byte i;
byte j;

byte OFF;
byte flashing;

int sensor1;
int sensor2;
int sensor3;
int sensor4;
int sensor5;
int sensor6;
int ind_sensor;
int foto_sensor;

byte traffic_light =0;
byte crossing_active =0;
byte cross=6;
byte finish_cross4;
byte finish_A;
byte foto=0;


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
byte refresh =1;
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

byte W1 = 22;
byte R7 = 23;
byte G7 = 24; 
byte Y7 = 25;
byte R5 = 26;
byte G5 = 27;
byte Y5 = 28;
byte SG7 = 29;
byte Y6 = 30;
byte G6 = 31;
byte R6 = 32;
byte BOP = 33;
byte L7OP = 34;
byte L8OP = 35;
byte sw1 = 36;
byte sw2 = 37;
byte sw3 = 38;
byte sw4 = 39;
byte sw5 = 40;
byte sw6 = 41;
byte sw7 = 42;
byte sw8 = 43;
byte W2 = 44;
byte W3 = 45;
byte SG4 = 46;
byte Y4= 47;
byte R4 = 48;
byte G4 = 49;
byte R3 = 50;
byte SG3 = 51;
byte G3 = 52;
byte Y3 = 53;
byte swcross1 = 2;
byte swcross2 = 3;
byte G12 = 4;
byte Y12 = 5;
byte R12 = 6;
byte SG12 = 7;
byte SR12 = 8;

byte time_sw = 200;
byte time_se = 500;

void setup() {

pinMode(W1,OUTPUT);
pinMode(R7,OUTPUT);
pinMode(G7,OUTPUT);
pinMode(Y7,OUTPUT);
pinMode(SG7,OUTPUT);
pinMode(R5,OUTPUT);
pinMode(G5,OUTPUT);
pinMode(Y5,OUTPUT);
pinMode(Y6,OUTPUT);
pinMode(G6,OUTPUT);
pinMode(R6,OUTPUT);
pinMode(BOP,OUTPUT);
pinMode(L7OP,OUTPUT);
pinMode(L8OP,OUTPUT);
pinMode(W2,OUTPUT);
pinMode(W3,OUTPUT);
pinMode(SG4,OUTPUT);
pinMode(Y4,OUTPUT);
pinMode(R4,OUTPUT);
pinMode(G4,OUTPUT);
pinMode(R3,OUTPUT);
pinMode(SG3,OUTPUT);
pinMode(G3,OUTPUT);
pinMode(Y3,OUTPUT);
pinMode(G12,OUTPUT);
pinMode(R12,OUTPUT);
pinMode(Y12,OUTPUT);
pinMode(SG12,OUTPUT);
pinMode(SR12,OUTPUT);
pinMode(sw1,INPUT_PULLUP);
pinMode(sw2,INPUT_PULLUP);
pinMode(sw3,INPUT_PULLUP);
pinMode(sw4,INPUT_PULLUP);
pinMode(sw5,INPUT_PULLUP);
pinMode(sw6,INPUT_PULLUP);
pinMode(sw7,INPUT_PULLUP);
pinMode(sw8,INPUT_PULLUP);
pinMode(swcross1,INPUT_PULLUP);
pinMode(swcross2,INPUT_PULLUP);

lcd.init();
lcd.backlight();
Serial.begin(9600);

digitalWrite(G12,HIGH);
digitalWrite(SR12,HIGH);


}

void loop() {

 switch(foto){
  case 0:
    if(aa==0){
    digitalWrite(W1,LOW);
    digitalWrite(W2,LOW);
    digitalWrite(W3,LOW);}
    foto_sensor = analogRead(A0); 
    if(foto_sensor<200){aa=0;foto_t1=millis();foto=1;}
break;
  case 1:
    foto_sensor = analogRead(A0); 
    if(foto_sensor>200){foto=0;}
    foto_t2=millis();
    if(foto_t2-foto_t1>3000){foto=2;}
break;
  case 2:
    if(aa==0){
    digitalWrite(W1,HIGH);
    digitalWrite(W2,HIGH);
    digitalWrite(W3,HIGH);}
    foto_sensor = analogRead(A0);
    if(foto_sensor>200){aa=0;foto_t3=millis();foto=3;}
break;
  case 3:
    foto_sensor = analogRead(A0); 
    if(foto_sensor<200){foto=2;}
    foto_t4=millis();
    if(foto_t4-foto_t3>3000){foto=0;}   
break;
}

ind_sensor = analogRead(A7);

if(ind_sensor>550){
   digitalWrite(BOP,HIGH);}
   else{digitalWrite(BOP,LOW);}

switch(sw7s){
  case 0:if(digitalRead(sw7)==LOW){sw7t1=millis();g++;digitalWrite(L7OP, HIGH);sw7s=1;} 
break;
  case 1:sw7t2=millis();if(sw7t2-sw7t1>time_sw){sw7s=2;}
break;
  case 2:if(digitalRead(sw7)==HIGH){digitalWrite(L7OP, LOW);sw7s=0;}
break;
}

if(g>1){g=0;}
if(g==1){OFF=1;}
if(g==0){OFF=0;}
if(OFF==1){
if(crossing_active==0){digitalWrite(R12,LOW);digitalWrite(G12,LOW);digitalWrite(Y12,LOW);digitalWrite(SR12,LOW);digitalWrite(SG12,LOW);}
if(b==0){fl_t1=millis();flashing=1;
AtoC=0;BtoA=0;CtoB=0;
count_A=0;count_B=0;count_C=0;
count_A_f=0;count_B_f=0;count_C_f=0;
interval_A=0;interval_B=0;interval_C=0;
interval_A_f=0;interval_B_f=0;interval_C_f=0;
interval_A2=0;interval_B2=0;interval_C2=0;
completed_A=0;completed_B=0;completed_C=0;
waiting_A=0;waiting_B=0;waiting_C=0;
reg_A=0;reg_B=0;reg_C=0;traffic_light=0;finish_A=0;
lcd.clear();lcd.setCursor ( 4, 1 );lcd.print("necinny stav");
digitalWrite(R3,LOW);digitalWrite(Y3,LOW);digitalWrite(G3,LOW);digitalWrite(SG3,LOW);
digitalWrite(R4,LOW);digitalWrite(Y4,LOW);digitalWrite(G4,LOW);digitalWrite(SG4,LOW);
digitalWrite(R5,LOW);digitalWrite(Y5,LOW);digitalWrite(G5,LOW);
digitalWrite(R6,LOW);digitalWrite(Y6,LOW);digitalWrite(G6,LOW);
digitalWrite(R7,LOW);digitalWrite(Y7,LOW);digitalWrite(G7,LOW);digitalWrite(SG7,LOW);
b=1;}}

switch(flashing){
  case 0:
break;  
  case 1:
  digitalWrite(Y3,HIGH);digitalWrite(Y4,HIGH);digitalWrite(Y5,HIGH);digitalWrite(Y6,HIGH);digitalWrite(Y7,HIGH);
  if(crossing_active==0){digitalWrite(Y12,HIGH);}
  fl_t2=millis();
  if(fl_t2-fl_t1>500){fl_t3=millis();flashing=2;}
break;
  case 2:
  digitalWrite(Y3,LOW);digitalWrite(Y4,LOW);digitalWrite(Y5,LOW);digitalWrite(Y6,LOW);digitalWrite(Y7,LOW);
  if(crossing_active==0){digitalWrite(Y12,LOW);}
  fl_t4=millis();
  if(fl_t4-fl_t3>500){fl_t1=millis();flashing=1;}
break;
}

if(OFF==0){
if(b!=0){if(crossing_active==0){digitalWrite(G12,HIGH);digitalWrite(SR12,HIGH);}
lcd.clear();refresh=1;
digitalWrite(Y3,LOW);digitalWrite(Y4,LOW);digitalWrite(Y5,LOW);digitalWrite(Y6,LOW);digitalWrite(Y7,LOW);digitalWrite(Y12,LOW);flashing=0;b=0;}
sensor1 = analogRead(A4);//1
sensor2 = analogRead(A1);//2
sensor3 = analogRead(A2);//3
sensor4 = analogRead(A3);//4
sensor5 = analogRead(A5);//5
sensor6 = analogRead(A6);//6

//jen kdyz je treba aktualizovat display:
if(refresh!=0){
sum=count_A+count_B+count_C;
count_A_f=count_A;

//DIRECTION A:
//osetreni pro deleni nulou
if(sum!=0){
percentage_A=(count_A_f/sum)*100;}
else {percentage_A=(count_A_f/1)*100;};
interval_A_f=percentage_A/10;
//minimum (10s)
if(completed_A==1){interval_A=interval_A_f+10;}else{interval_A=10;}
lcd.setCursor ( 0, 0 );lcd.print(">A:");
lcd.setCursor ( 3, 0 );lcd.print("     ");
lcd.setCursor ( 3, 0 );lcd.print(percentage_A);
lcd.setCursor ( 8, 0 );lcd.print("%");
lcd.setCursor ( 10, 0 );lcd.print("C:");
lcd.setCursor ( 12, 0 );lcd.print("   ");
lcd.setCursor ( 12, 0 );lcd.print(count_A);
lcd.setCursor ( 15, 0 );lcd.print("I:");
lcd.setCursor ( 17, 0 );lcd.print("  ");
lcd.setCursor ( 17, 0 );lcd.print(interval_A);
lcd.setCursor ( 19, 0 );lcd.print("s");

//DIRECTION B:
count_B_f=count_B;
if(sum!=0){
percentage_B=(count_B_f/sum)*100;}
else{percentage_B=(count_B_f/1)*100;}
if(completed_B==1){interval_B_f=percentage_B/10;}else{interval_B=10;}
//minimum (10s)
interval_B=interval_B_f+10;
lcd.setCursor ( 0, 1 );lcd.print(">B:");
lcd.setCursor ( 3, 1 );lcd.print("     ");
lcd.setCursor ( 3, 1 );lcd.print(percentage_B);
lcd.setCursor ( 8, 1 );lcd.print("%");
lcd.setCursor ( 10, 1 );lcd.print("C:");
lcd.setCursor ( 12, 1 );lcd.print("   ");
lcd.setCursor ( 12, 1 );lcd.print(count_B);
lcd.setCursor ( 15, 1 );lcd.print("I:");
lcd.setCursor ( 17, 1 );lcd.print("  ");
lcd.setCursor ( 17, 1 );lcd.print(interval_B);
lcd.setCursor ( 19, 1 );lcd.print("s");


//DIRECTION C:
count_C_f=count_C;
if(sum!=0){
percentage_C=(count_C_f/sum)*100;}
else{percentage_C=(count_C_f/1)*100;};
interval_C_f=percentage_C/10;
//minimum (10s)
if(completed_C==1){interval_C=interval_C_f+10;}else{interval_C=10;}
lcd.setCursor ( 0, 2 );lcd.print(">C:");
lcd.setCursor ( 3, 2 );lcd.print("     ");
lcd.setCursor ( 3, 2 );lcd.print(percentage_C);
lcd.setCursor ( 8, 2 );lcd.print("%");
lcd.setCursor ( 10, 2 );lcd.print("C:");
lcd.setCursor ( 12, 2 );lcd.print("   ");
lcd.setCursor ( 12, 2 );lcd.print(count_C);
lcd.setCursor ( 15, 2 );lcd.print("I:");
lcd.setCursor ( 17, 2 );lcd.print("  ");
lcd.setCursor ( 17, 2 );lcd.print(interval_C);
lcd.setCursor ( 19, 2 );lcd.print("s");


lcd.setCursor ( 0, 3 );lcd.print("A:");
lcd.setCursor ( 2, 3 );lcd.print(reg_A);
if(traffic_light==1){lcd.setCursor ( 2, 3 );lcd.print("G");}
lcd.setCursor ( 4, 3 );lcd.print("B:");
lcd.setCursor ( 6, 3 );lcd.print(reg_B);
if(traffic_light==4){lcd.setCursor ( 6, 3 );lcd.print("G");}
lcd.setCursor ( 8, 3 );lcd.print("C:");
lcd.setCursor ( 10, 3 );lcd.print(reg_C);
if(traffic_light==8){lcd.setCursor ( 10, 3 );lcd.print("G");}
lcd.setCursor ( 12, 3 );lcd.print("cross:");
lcd.setCursor ( 18, 3 );lcd.print(crossing_active);

refresh=0;}


switch(se1s){
  case 0:if(sensor1<120){se1t1=millis();if(traffic_light==1){count_A++;}refresh=1;se1s=1;} 
break;
  case 1:se1t2=millis();if(se1t2-se1t1>time_se){se1s=2;}
break;
  case 2:if(sensor1>120){se1s=0;}
break;  
}
switch(se2s){
  case 0:if(sensor2<120){se2t1=millis();if(traffic_light==1 && crossing_active==0){count_A++;}refresh=1;se2s=1;} 
break;
  case 1:se2t2=millis();if(se2t2-se2t1>time_se){se2s=2;}
break;
  case 2:if(sensor2>120){se2s=0;}
break;
}
switch(se3s){
  case 0:if(sensor3<120){se3t1=millis();if(traffic_light==4){count_B++;}refresh=1;se3s=1;} 
break;
  case 1:se3t2=millis();if(se3t2-se3t1>time_se){se3s=2;}
break;
  case 2:if(sensor3>120){se3s=0;}
break;
}
switch(se4s){
  case 0:if(sensor4<120){se4t1=millis();if(traffic_light==4){count_B++;}refresh=1;se4s=1;} 
break;
  case 1:se4t2=millis();if(se4t2-se4t1>time_se){se4s=2;}
break;
  case 2:if(sensor4>120){se4s=0;}
break;
}
switch(se5s){
  case 0:if(sensor5<120){se5t1=millis();if(traffic_light==8){count_C++;}refresh=1;se5s=1;} 
break;
  case 1:se5t2=millis();if(se5t2-se5t1>time_se){se5s=2;}
break;
  case 2:if(sensor5>120){se5s=0;}
break;
}
switch(se6s){
  case 0:if(sensor6<120){se6t1=millis();if(traffic_light==8){count_C++;}refresh=1;se6s=1;} 
         if(ind_sensor>550){se6t1=millis();if(traffic_light==8){count_C++;}refresh=1;se6s=3;}
break;
  case 1:se6t2=millis();if(se6t2-se6t1>time_se){se6s=2;}
break;
  case 2:if(sensor6>120){se6s=0;}
break;
  case 3:se6t2=millis();if(se6t2-se6t1>time_se){se6s=4;}
break;
//ceka se az vozidlo opusti obe cidla aby se nepricetlo dvakrat
  case 4:if(ind_sensor<550 && sensor6>120){se6s=0;}
break;
}

switch(sw1s){
  case 0:if(digitalRead(sw1)==LOW){sw1t1=millis();if(traffic_light==1){count_A++;};refresh=1;sw1s=1;} 
break;
  case 1:sw1t2=millis();if(sw1t2-sw1t1>time_sw){sw1s=2;}
break;
  case 2:if(digitalRead(sw1)==HIGH){sw1s=0;}
break;
}

switch(sw2s){
  case 0:if(digitalRead(sw2)==LOW){sw2t1=millis();if(traffic_light==1 && crossing_active==0){count_A++;};refresh=1;sw2s=1;} 
break;
  case 1:sw2t2=millis();if(sw2t2-sw2t1>time_sw){sw2s=2;}
break;
  case 2:if(digitalRead(sw2)==HIGH){sw2s=0;}
break;
}
switch(sw3s){
  case 0:if(digitalRead(sw3)==LOW){sw3t1=millis();if(traffic_light==4){count_B++;}refresh=1;sw3s=1;} 
break;
  case 1:sw3t2=millis();if(sw3t2-sw3t1>time_sw){sw3s=2;}
break;
  case 2:if(digitalRead(sw3)==HIGH){sw3s=0;}
break;
}
switch(sw4s){
  case 0:if(digitalRead(sw4)==LOW){sw4t1=millis();if(traffic_light==4){count_B++;}refresh=1;sw4s=1;} 
break;
  case 1:sw4t2=millis();if(sw4t2-sw4t1>time_sw){sw4s=2;}
break;
  case 2:if(digitalRead(sw4)==HIGH){sw4s=0;}
break;
}
switch(sw5s){
  case 0:if(digitalRead(sw5)==LOW){sw5t1=millis();if(traffic_light==8){count_C++;}refresh=1;sw5s=1;} 
break;
  case 1:sw5t2=millis();if(sw5t2-sw5t1>time_sw){sw5s=2;}
break;
  case 2:if(digitalRead(sw5)==HIGH){sw5s=0;}
break;
}
switch(sw6s){
  case 0:if(digitalRead(sw6)==LOW){sw6t1=millis();if(traffic_light==8){count_C++;}refresh=1;sw6s=1;} 
break;
  case 1:sw6t2=millis();if(sw6t2-sw6t1>time_sw){sw6s=2;}
break;
  case 2:if(digitalRead(sw6)==HIGH){sw6s=0;}
break;
}
//sw7 je mimo podminku vypnuti rizeni SSZ
switch(sw8s){
  case 0:if(digitalRead(sw8)==LOW){sw8t1=millis();h++;digitalWrite(L8OP, HIGH);sw8s=1;} 
break;
  case 1:sw8t2=millis();if(sw8t2-sw8t1>time_sw){sw8s=2;}
break;
  case 2:if(digitalRead(sw8)==HIGH){digitalWrite(L8OP, LOW);sw8s=0;}
break;
}
switch(swcross1s){
  case 0:if(digitalRead(swcross1)==LOW){swcross1t1=millis();i++;swcross1s=1;} 
break;
  case 1:swcross1t2=millis();if(swcross1t2-swcross1t1>time_sw){swcross1s=2;}
break;
  case 2:if(digitalRead(swcross1)==HIGH){swcross1s=0;}
break;
}
switch(swcross2s){
  case 0:if(digitalRead(swcross2)==LOW){swcross2t1=millis();j++;swcross2s=1;} 
break;
  case 1:swcross2t2=millis();if(swcross2t2-swcross2t1>time_sw){swcross2s=2;}
break;
  case 2:if(digitalRead(swcross2)==HIGH){swcross2s=0;}
break;
}

switch(traffic_light){
  //SMER A: 
case 0:
  trl01=millis();
  if(reg_A==0){count_A=0;}else{count_A=1;}
  refresh=1;
  traffic_light=1;
break;
case 1: //GREEN DIRECTION A-----------------------------------------------------------------------------------------------------------------------

  //osetreni pro vykonani jen jednou (protoze vypinam SSZ6 s prechodem)
  if(finish_A==0){
  reg_A=0;
 
  digitalWrite(G7,HIGH);digitalWrite(SG4,HIGH);digitalWrite(SG3,HIGH);
  if(crossing_active==0){digitalWrite(G6,HIGH);digitalWrite(R6,LOW);}else{digitalWrite(G6,LOW);if(BtoA==1){digitalWrite(R6,HIGH);}}
  digitalWrite(Y7,LOW);digitalWrite(Y6,LOW);
  digitalWrite(R7,LOW);digitalWrite(R3,HIGH);digitalWrite(R4,HIGH);digitalWrite(R5,HIGH);
  finish_A=1;
  }
  if(crossing_active==0){BtoA=0;}

//registrovani vozidel z jiných směrů
  if(reg_B==0){
  //if(sensor3<120){reg_B=1;refresh=1;}
  if(sensor4<120){reg_B=1;refresh=1;}
  //if(digitalRead(sw3)==LOW){reg_B=1;refresh=1;}
  if(digitalRead(sw4)==LOW){reg_B=1;refresh=1;}
  }
  if(reg_C==0){
  //if(sensor5<120){reg_C=1;refresh=1;}
  if(sensor6<120){reg_C=1;refresh=1;}
  if(ind_sensor>550){reg_C=1;refresh=1;}
  //if(digitalRead(sw5)==LOW){reg_C=1;refresh=1;}
  if(digitalRead(sw6)==LOW){reg_C=1;refresh=1;}
  }
  if(crossing_active==0){
  trl02=millis();
  //osetreni proti maximalnimu intervalu na zacatku
  if(completed_A==1){interval_A2=(interval_A*1000);}else{interval_A2=10000;}
  if(trl02-trl01>interval_A2){waiting_A=1;}
     
   }
  if(waiting_A==1){
  if(reg_C==1 && reg_B==0){if(crossing_active==0){completed_A=1;BtoA=0;waiting_A=0;trl41=millis();AtoC=1;count_B=0;refresh=1;traffic_light=5;}}
  if(reg_B==1 && reg_C==0){if(crossing_active==0){completed_A=1;BtoA=0;waiting_A=0;trl11=millis();AtoC=0;traffic_light=2;}}
  if(reg_B==1 && reg_C==1){if(crossing_active==0){completed_A=1;BtoA=0;waiting_A=0;trl11=millis();AtoC=0;traffic_light=2;}}
  }
   
break;
case 2: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  finish_A=0;
  if(CtoB==1){
    digitalWrite(G6,LOW);digitalWrite(G5,LOW);
    digitalWrite(Y6,HIGH);digitalWrite(Y5,HIGH);
  }
  if(CtoB==0){
    digitalWrite(G7,LOW);digitalWrite(G6,LOW);
    digitalWrite(Y7,HIGH);digitalWrite(Y6,HIGH);
  }
  
  trl12=millis();
  if(trl12-trl11>3000){trl21=millis();traffic_light=3;}
break;
  case 3: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  if(CtoB==1){
    digitalWrite(Y6,LOW);digitalWrite(Y5,LOW);
    digitalWrite(R6,HIGH);digitalWrite(R5,HIGH);
  }
  if(CtoB==0){
    digitalWrite(Y7,LOW);digitalWrite(Y6,LOW);//digitalWrite(SG3,LOW);digitalWrite(SG4,LOW);
    digitalWrite(R7,HIGH);digitalWrite(R6,HIGH);
  }
  //pocita to s jednim autem kdyz bylo zaregistrovano
  trl22=millis();
  if(trl22-trl21>1000){trl441=millis();traffic_light=44;}
break;
case 44://RED + YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------
  
  if(CtoB==1){   
  digitalWrite(Y4,HIGH);
  }
  if(CtoB==0){
  digitalWrite(Y4,HIGH);digitalWrite(Y3,HIGH);  
  }
  trl442=millis();
  if(trl442-trl441>2000){trl31=millis();if(reg_B==0){count_B=0;}else{count_B=1;};
  refresh=1;traffic_light=4;}

break;
case 4: //GREEN DIRECTION B-----------------------------------------------------------------------------------------------------------------------
  CtoB=0;
  reg_B=0;
  if(reg_A==0){
  if(sensor1<120){reg_A=1;refresh=1;}
  if(sensor2<120){reg_A=1;refresh=1;}
  if(digitalRead(sw1)==LOW){reg_A=1;refresh=1;}
  if(digitalRead(sw2)==LOW){reg_A=1;refresh=1;}
  }
  if(reg_C==0){
  //if(sensor5<120){reg_C=1;refresh=1;}
  if(sensor6<120){reg_C=1;refresh=1;}
  if(ind_sensor>550){reg_C=1;refresh=1;}
  //if(digitalRead(sw5)==LOW){reg_C=1;refresh=1;}
  if(digitalRead(sw6)==LOW){reg_C=1;refresh=1;}
  }
  if(CtoB==0){digitalWrite(SG3,LOW);digitalWrite(SG4,LOW);}
  digitalWrite(G4,HIGH);digitalWrite(G3,HIGH);digitalWrite(SG7,HIGH); 
  digitalWrite(Y4,LOW);digitalWrite(Y3,LOW);
  digitalWrite(R4,LOW);digitalWrite(R3,LOW);
  trl32=millis();

  if(completed_B==1){interval_B2=(interval_B*1000);}else{interval_B2=10000;};
  if(trl32-trl31>interval_B2){waiting_B=1;}
  
   if(waiting_B==1){
  if(reg_A==1 && reg_C==0){completed_B=1;waiting_B=0;trl91=millis();BtoA=1;count_C=0;refresh=1;traffic_light=9;}
  if(crossing_active==1 && reg_C==0){completed_B=1;waiting_B=0;trl91=millis();BtoA=1;count_C=0;refresh=1;traffic_light=9;}
  if(reg_C==1 && reg_A==0){completed_B=1;waiting_B=0;trl41=millis();BtoA=0;traffic_light=5;}
  if(reg_C==1 && reg_A==1){completed_B=1;waiting_B=0;trl41=millis();BtoA=0;traffic_light=5;}
  }
  
break;
case 5: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  finish_A=0;
  
  if(AtoC==1){
    digitalWrite(G7,LOW);
    digitalWrite(Y7,HIGH);
  }
  //BtoC
  if(AtoC==0){
    digitalWrite(SG7,LOW);
    digitalWrite(G4,LOW);
    digitalWrite(Y4,HIGH);
  }
  trl42=millis();
  if(trl42-trl41>3000){trl61=millis();traffic_light=6;}
break;
case 6: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  if(AtoC==1){
    digitalWrite(SG4,LOW);
    digitalWrite(Y7,LOW);
    digitalWrite(R7,HIGH);
  }
  if(AtoC==0){
    
    digitalWrite(Y4,LOW);
    digitalWrite(R4,HIGH);
  }
  trl62=millis();
  if(trl62-trl61>1000){trl71=millis();traffic_light=7;}


break;
case 7: //YELLOW + RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  if(AtoC==1){
  digitalWrite(Y5,HIGH);
  digitalWrite(Y3,HIGH);
  }
  if(AtoC==0){
  digitalWrite(Y5,HIGH);
  digitalWrite(Y6,HIGH);
  }
  trl72=millis();
  if(trl72-trl71>2000){trl81=millis();if(reg_C==0){count_C=0;}else{count_C=1;};
  refresh=1;traffic_light=8;}
  
break;
case 8: //GREEN DIRECTION C-----------------------------------------------------------------------------------------------------------------------

  reg_C=0;
  AtoC=0;
  if(reg_A==0){
  if(sensor1<120){reg_A=1;refresh=1;}
  //if(sensor2<120){reg_A=1;refresh=1;}
  if(digitalRead(sw1)==LOW){reg_A=1;refresh=1;}
  //if(digitalRead(sw2)==LOW){reg_A=1;refresh=1;}
  }
  if(reg_B==0){
  if(sensor3<120){reg_B=1;refresh=1;}
  if(sensor4<120){reg_B=1;refresh=1;}
  if(digitalRead(sw3)==LOW){reg_B=1;refresh=1;}
  if(digitalRead(sw4)==LOW){reg_B=1;refresh=1;}
  }
  
    digitalWrite(G6,HIGH);digitalWrite(G5,HIGH);digitalWrite(G3,HIGH);digitalWrite(SG3,LOW);
    digitalWrite(Y6,LOW);digitalWrite(Y5,LOW);digitalWrite(Y3,LOW);
    digitalWrite(R6,LOW);digitalWrite(R5,LOW);digitalWrite(R3,LOW);
  
  trl82=millis();
  if(completed_C==1){interval_C2=(interval_C*1000);}else{interval_C2=10000;};
  if(trl82-trl81>interval_C2){waiting_C=1;}
    
  if(waiting_C==1){
  if(reg_B==1 && reg_A==0){completed_C=1;waiting_C=0;trl11=millis();CtoB=1;count_A=0;refresh=1;traffic_light=2;}
  if(reg_A==1 && reg_B==0){completed_C=1;waiting_C=0;trl91=millis();CtoB=0;traffic_light=9;}
  if(reg_A==1 && reg_B==1){completed_C=1;waiting_C=0;trl91=millis();CtoB=0;traffic_light=9;}
  if(crossing_active==1){completed_C=1;waiting_C=0;trl91=millis();CtoB=0;traffic_light=9;}
  }
break;
case 9: //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  if(BtoA==1){
    digitalWrite(G4,LOW);digitalWrite(G3,LOW);digitalWrite(SG4,HIGH);digitalWrite(SG3,HIGH);
    digitalWrite(Y4,HIGH);digitalWrite(Y3,HIGH);
    }
  if(BtoA==0){
    digitalWrite(G5,LOW);digitalWrite(G3,LOW);digitalWrite(SG3,HIGH);
    digitalWrite(Y5,HIGH);digitalWrite(Y3,HIGH);
    }
  trl92=millis();
  if(trl92-trl91>3000){trl101=millis();traffic_light=10;}
break;
case 10: //RED SEQUENCE-----------------------------------------------------------------------------------------------------------------------

  if(BtoA==1){
    digitalWrite(Y4,LOW);digitalWrite(Y3,LOW);digitalWrite(SG7,LOW);
    digitalWrite(R4,HIGH);digitalWrite(R3,HIGH);
  } 
  if(BtoA==0){
    digitalWrite(Y5,LOW);digitalWrite(Y3,LOW);
    digitalWrite(R5,HIGH);digitalWrite(R3,HIGH);
  }
  trl102=millis();
  if(trl102-trl101>1000){trl111=millis();traffic_light=11;}
  
break;
case 11://RED + YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------
  if(BtoA==1){
  digitalWrite(Y7,HIGH);if(crossing_active==0){digitalWrite(Y6,HIGH);}
  } 
  if(BtoA==0){
  digitalWrite(Y7,HIGH);
  }  
    
trl112=millis();
if(trl112-trl111>2000){traffic_light=0;}
break;
}
}

//CROSSING-----------------------------------------------------------------------------------------------------------------------------


if(i!=0){crossing_active=1;if(a==0){refresh=1;a=1;}}
if(j!=0){crossing_active=1;if(a==0){refresh=1;a=1;}}

if(crossing_active==1 && traffic_light==1 && cross==6 && finish_A==1 && finish_cross4==0){tc01=millis();cross=0;};   

switch(cross){
  //YELLOW SEQUENCE-----------------------------------------------------------------------------------------------------------------------------
  case 0:
    if(OFF==0 && BtoA==0){digitalWrite(G6,LOW);digitalWrite(Y6,HIGH);}
    digitalWrite(G12,LOW);
    digitalWrite(Y12,HIGH);
    tc02=millis();
    if(tc02-tc01>3000){tc11=millis();cross=1;}
    
  break;
  //RED SEQUENCE--------------------------------------------------------------------------------------------------------------------------
  case 1:
  
    digitalWrite(Y12,LOW);if(OFF==0 && BtoA==0){digitalWrite(Y6,LOW);digitalWrite(R6,HIGH);}
    digitalWrite(R12,HIGH);
    tc12=millis();
    if(tc12-tc11>3000){tc21=millis();cross=2;}
    
  break;
  //GREEN SEQUENCE-----------------------------------------------------------------------------------------------------------------------
  case 2:
    
    digitalWrite(SG12,HIGH);
    digitalWrite(SR12,LOW);
    tc22=millis();
    if(tc22-tc21>5000){tc31=millis();cross=3;}
    //real = 10s
    
  break;
  //YELLOW SEQUENCE------------------------------------------------------------------------------------------------------------------------
  case 3:
   
    digitalWrite(SG12,LOW);
    digitalWrite(SR12,HIGH);
    
    tc32=millis();
    if(tc32-tc31>2000){tc41=millis();cross=4;}
    
  break;
  //RED, STAND-BY-----------------------------------------------------------------------------------------------------------------------
  //aby se nespustil přechod hned znovu, čekání 5s:
  case 4:
  digitalWrite(Y12,HIGH);if(OFF==0){digitalWrite(Y6,HIGH);}
  tc42=millis();   
    if(tc42-tc41>2000){tc51=millis();cross=5;}
  break;
  
  case 5:
  if(finish_cross4==0){   
  if(OFF==0){digitalWrite(G6,HIGH);digitalWrite(Y6,LOW);digitalWrite(R6,LOW);waiting_A=1;}
  digitalWrite(G12,HIGH);
  digitalWrite(Y12,LOW);
  digitalWrite(R12,LOW);
  //trl01 je cas od zacatku trvání zelene sekvence A
  trl01=millis();i=0;j=0;BtoA=0;crossing_active=0;refresh=1;a=0;
  finish_cross4=1;}
  //osetreni proti opakovani
  tc52=millis();
  if(tc52-tc51>10000){cross=6;}
  break;

  case 6:
  finish_cross4=0;
  //stand-by
  break;
}
}

```
