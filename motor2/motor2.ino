#include "Motor.h"
#include <NewPing.h>

#define L_TRIG 5
#define L_ECHO 4
#define R_TRIG 52
#define R_ECHO 50
#define M_TRIG 7
#define M_ECHO 6

#define MAX_DISTANCE 200

NewPing M_sensor(M_TRIG, M_ECHO, MAX_DISTANCE);
NewPing R_sensor(R_TRIG, R_ECHO, MAX_DISTANCE);
NewPing L_sensor(L_TRIG, L_ECHO, MAX_DISTANCE);
Motor motor;

int L_cm = 0, M_cm = 0, R_cm = 0;

void sensorRead(void) {
  M_cm = M_sensor.ping_cm();
  R_cm = R_sensor.ping_cm();
  L_cm = L_sensor.ping_cm();

  if (M_cm == 0)
    M_cm = 120;
  if (R_cm == 0)
    R_cm = 120;
  if (L_cm == 0)
    L_cm = 120;
}

void setup() {
  motor.begin();
  Serial.begin(9600);
  Serial.setTimeout(10);
  delay(2500);
  sensorRead();
}

void loop() {

  // motor.setSpeed(100, 100);

  sensorRead();

  Serial.print("Left Distance: ");
  Serial.println(L_cm);
  Serial.print("Middle Distance: ");
  Serial.println(M_cm);
  Serial.print("Right Distance: ");
  Serial.println(R_cm); 

  if (motor.R_count >= 3) {
    while (motor.R_count != 0) {
      if (M_cm <= 3 && (R_cm < 3 || L_cm < 3)) {
        break;
      } else {
        motor.turn_left(100, 3);
      }
      sensorRead();
    }
    motor.R_count = 0;
    motor.L_count = 0;
  } else if (motor.L_count >= 3) {
    while (motor.L_count != 0) {
      if (M_cm <= 3 && (R_cm < 3 || L_cm < 3)) {
        break;
      } else {
        motor.turn_right(100, 3);
      }
      sensorRead();
    }
    motor.R_count = 0;
    motor.L_count = 0;
  }

  if (M_cm > 80) {
    if (L_cm <= 2 || R_cm <= 2) {
      motor.brake();
      if (L_cm < R_cm) {
        motor.turn_right(60, 9);
      } else {
        motor.turn_left(60, 9);
      }
      motor.brakeState = true;
    }
    else if (L_cm <= 15 || R_cm <= 15){
      if (L_cm < R_cm) {
        motor.turn_right(100, 3);
      } else {
        motor.turn_left(100, 3);
      }
      motor.brakeState = true;
    }
    else {
      motor.setSpeed(120, 120);
      motor.brakeState = true;
    } 
  }

  else if (M_cm > 10) {
    if (L_cm <= 3 || R_cm <= 3) {
      motor.brake();
      motor.setSpeed(0, 0);
      delay(100);
      if (L_cm >= R_cm) {
        motor.turn_left(60, 9);
      } else {
        motor.turn_right(60, 9);
      }
    } else if (L_cm <= 6 || R_cm <= 6) {
      if (L_cm >= R_cm) {
        motor.turn_left(120, 6);
      } else {
        motor.turn_right(120, 6);
      }
      motor.brakeState = true;
    } else if (L_cm <= 20 || R_cm <= 20){
      if(L_cm >= R_cm){
        motor.turn_left(120, 3);
      } else {
        motor.turn_right(120, 3);
      }
      motor.brakeState = true;
    } else {
      if (M_cm <= 40)
        motor.setSpeed(M_cm, M_cm);
      else
        motor.setSpeed((M_cm + 20), (M_cm + 20));
      motor.brakeState = true;
    }
  }

  else if (M_cm > 4) {
    motor.brake();
    motor.setSpeed(0, 0);
    if (R_cm <= 3 || L_cm <= 3) {
      if (L_cm < R_cm) {
        motor.turn_right(50, 10);
      } else {
        motor.turn_left(50, 10);
      }
    } else if (R_cm <= 6 || L_cm <= 6) {
      if (L_cm >= R_cm) {
        motor.turn_left(50, 6);
      } else {
        motor.turn_right(50, 6);
      }
    } else  {
      if (L_cm >= R_cm) {
        motor.turn_left(80, 5);
      } else {
        motor.turn_right(80, 5);
      }
    }
    motor.brakeState = true;
  }

  else if (M_cm > 0) {
    motor.brake();
    motor.setSpeed(0,0);
    if (L_cm < R_cm) {
      motor.turn_right(60, 10);
    } else {
      motor.turn_left(60, 10);
    }
    motor.brakeState = true;
  }
}
