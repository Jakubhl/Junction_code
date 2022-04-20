
#include "Arduino.h"
#include "VO.h"

VO::VO(byte led_W1, byte led_W2, byte led_W3, char analog_pin_fotoresistor, int foto_detect, int convince_time){
    foto_det=foto_detect;
    analog_foto=analog_pin_fotoresistor;
    convince=convince_time;
    W1=led_W1;
    W2=led_W2;
    W3=led_W3;
    }


void VO::PinSetup(){
    pinMode(W1, OUTPUT);
    pinMode(W2, OUTPUT);
    pinMode(W3, OUTPUT);   
	
}

void VO::Sequence(){

switch (foto) {
    case 0:
      if (a == 0) { 
    //a proti opakovani
        digitalWrite(W1, LOW);
        digitalWrite(W2, LOW);
        digitalWrite(W3, LOW);
      } a = 1;
      foto_sensor = analogRead(analog_foto);
      if (foto_sensor < foto_det) {
        foto_t1 = millis();
        foto = 1;
      }
      break;
    case 1:
      a = 0;
      foto_sensor = analogRead(analog_foto);
      if (foto_sensor > foto_det) {
        foto = 0;
      }
      foto_t2 = millis();
      if (foto_t2 - foto_t1 > convince) {
        foto = 2;
      }
      break;
    //3 s overovani 
    case 2:
      if (a == 0) {
        digitalWrite(W1,HIGH); 
        digitalWrite(W2,HIGH);
        digitalWrite(W3,HIGH);
      } a = 1;
      foto_sensor = analogRead(analog_foto);
      if (foto_sensor > foto_det) {
        foto_t3 = millis();
        foto = 3;
      }
      break;
    case 3:
      a = 0;
      foto_sensor = analogRead(analog_foto);
      if (foto_sensor < foto_det) {
        foto = 2;
      }
      foto_t4 = millis();
      if (foto_t4 - foto_t3 > convince) {
        foto = 0;
      }
      break;
  }

}
