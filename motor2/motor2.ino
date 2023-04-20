#include <NewPing.h>
#include "Motor.h"

#define L_TRIG 5
#define L_ECHO 4
#define R_TRIG 52
#define R_ECHO 50
#define M_TRIG 7
#define M_ECHO 6

NewPing M_sensor(M_TRIG, M_ECHO, 1000);
NewPing R_sensor(R_TRIG, R_ECHO, 1000);
NewPing L_sensor(L_TRIG, L_ECHO, 1000);

Motor motor;

bool brakeState = true;

int L_cm = 0;
int M_cm = 0;
int R_cm = 0;

int R_count = 0;
int L_count = 0;

int i = 0;

void sensorRead(void){
  M_cm = M_sensor.ping_cm();
  R_cm = R_sensor.ping_cm();
  L_cm = L_sensor.ping_cm();
  
  if(M_cm == 0) M_cm = 100;
  if(R_cm == 0) R_cm = 100;
  if(L_cm == 0) L_cm = 100;
}

void setup() {

  motor.begin();
  Serial.begin(9600);
  Serial.setTimeout(10);
  delay(2500);
  sensorRead();
}

void loop() {
  sensorRead();

  Serial.print("Left Distance: ");
  Serial.println(L_cm);
  Serial.print("Middle Distance: ");
  Serial.println(M_cm);
  Serial.print("Right Distance: ");
  Serial.println(R_cm); /*
  delay(1000);
  motor.setSpeed(-50,-50);*/

  //motor.setSpeed(0, -100);
 /* motor.setSpeed(80, 0);
  delay(500);
  motor.setSpeed(0,0);
  delay(500);
  motor.setSpeed(0, 80);
  delay(500);
  while (1){
    motor.setSpeed(0,0);
  } */
  
  if(R_count >= 4){
    while (R_count != 0){
      if(M_cm <= 4 && (R_cm <4 || L_cm < 4)){
        break;
      } else {
        motor.setSpeed(-30, 120);
        delay(200);
        R_count--;
      }
      sensorRead();      
    }
  }  
  if(L_count >= 4){
    while (L_count != 0){
      if(M_cm < 4 && (R_cm < 4 || L_cm < 4)){
        break;
      } else {
        motor.setSpeed(120, -30);
        delay(200);
        L_count--;
      }
      sensorRead();      
    }
  }

  if (M_cm > 80){ 

    if (L_cm <= 4 || R_cm <= 4){
      if (brakeState == true) motor.brake();
      if (L_cm < R_cm){
        motor.setSpeed(60, -120);
        delay(200);
        motor.setSpeed(0, 0);
        delay(200);
      } else {
        motor.setSpeed(-120, 60);
        delay(200); 
        motor.setSpeed(0, 0);
        delay(200);       
      }
      R_count = 0;
      L_count = 0;
      brakeState = true;
    }
    else if ((L_cm > 4 && L_cm <= 10)||(R_cm > 4 && R_cm <= 10)){
      if (L_cm < R_cm){
        motor.setSpeed(100, -50);
        delay(200);
        R_count++;
      } else {
        motor.setSpeed(-50, 100);
        delay(200);
        L_count++;        
      }
      brakeState = true;
    } 
    else if ((R_cm > 10 && R_cm <= 20) || (L_cm > 10 && L_cm <= 20)){
      if (L_cm < R_cm){
        motor.setSpeed(120, -30);
        delay(250);
        R_count++;
      } else {
        motor.setSpeed(-30, 120);
        delay(250);
        L_count++;
      }
      brakeState = true;
    }
    else if ((R_cm > 20 && R_cm <= 30) || (L_cm > 20 && L_cm <= 30)){
      if (L_cm < R_cm){
        motor.setSpeed(120, 0);
        delay(250);
        R_count++;
      } else {
        motor.setSpeed(0, 120);
        delay(250);
        L_count++;
      }
      brakeState = true;
    } 
    else if (L_cm > 30 && R_cm > 30){
      motor.setSpeed(100,100);
      delay(50);
      brakeState = true;
    }
  } 

  else if (M_cm > 35 && M_cm <= 80) {

    if ((L_cm >= 0 && L_cm <= 4) || (R_cm >= 0 && R_cm <= 4)){
      if (brakeState == true) motor.brake();
      motor.setSpeed(0,0);
      delay(100);
      if (L_cm >= R_cm) {
        motor.setSpeed(-120, 60);
        delay(250);
        motor.setSpeed(0, 0);
        delay(200);
      } else {
        motor.setSpeed(60, -120);
        delay(250);
        motor.setSpeed(0, 0);
        delay(200);
      }
      R_count = 0;
      L_count = 0;
      brakeState = true;
    }
    else if ((L_cm > 4 && L_cm <=10) || (R_cm > 4 && R_cm <= 10)){    
      if (L_cm >= R_cm) {
        motor.setSpeed(-60, 120);
        delay(200);
        L_count++;
      } else {
        motor.setSpeed(120, -60);
        delay(200);
        R_count++;
      }
      brakeState = true;
    }
    else if ((L_cm > 10 && L_cm <=20) || (R_cm > 10 && R_cm <= 20)){     
      if (L_cm >= R_cm) {
        motor.setSpeed(-30, 120);
        delay(200);
        L_count++;
      } else {
        motor.setSpeed(120, -30);
        delay(200);
        R_count++;
      }
      brakeState = true;
    }
    else if ((L_cm > 20 && L_cm <=30) || (R_cm > 20 && R_cm <= 30)){
      if (L_cm >= R_cm) {
        motor.setSpeed(0, 120);
        delay(250);
        L_count++;
      } else {
        motor.setSpeed(120, 0);
        delay(250);
        R_count++;        
      }
      brakeState = true;
    }
    else if (L_cm > 30 && R_cm > 30) {
      if (M_cm <= 40) motor.setSpeed(M_cm+5, M_cm+5);
      else motor.setSpeed((M_cm+20), (M_cm+20));
      delay(50);
      brakeState = true;
    }
  }

  else if(7 < M_cm && M_cm <= 35){

    if (brakeState == true) motor.brake();

    if (R_cm <= 5 || L_cm <= 5){
      if (L_cm < R_cm){
        motor.setSpeed(60, -120);
        delay(200);
        motor.setSpeed(0, 0);
        delay(200);
      } else {
        motor.setSpeed(-120, 60);
        delay(200);
        motor.setSpeed(0, 0);
        delay(200);
      }
      L_count = 0;
      R_count = 0;
    } 
    else if ((R_cm > 6 && R_cm <= 15) || (L_cm > 6 && L_cm <= 15)){
        if (L_cm >= R_cm) {
        motor.setSpeed(-30, 120);
        delay(200);
      } else {
        motor.setSpeed(120, -30);
        delay(200);
      }
    }
    else if (R_cm > 15 && L_cm > 15){
      if (L_cm >= R_cm) {
        motor.setSpeed(-20, 120);
        delay(200);
        L_count++;
      } else {
        motor.setSpeed(120, -20);
        delay(200);
        R_count++;
      }
    }
    brakeState = true;   
  }

  else if(M_cm > 0 && M_cm <= 7){
    if (brakeState == true) motor.brake();
    if (L_cm < R_cm){
      motor.setSpeed(60, -120);
      delay(200);
      motor.setSpeed(0, 0);
      delay(200);
      } else {
      motor.setSpeed(-120, 60);
      delay(200);
      motor.setSpeed(0,0);
      delay(200);
    }
    L_count = 0;
    R_count = 0;
    brakeState = true;
  }
}