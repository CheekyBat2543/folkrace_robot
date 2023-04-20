
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

#define L_TRIG  5
#define L_ECHO  4
#define R_TRIG 52
#define R_ECHO 50
#define M_TRIG  7
#define M_ECHO  6
#define L_IN1  22
#define L_IN2  24
#define L_ENA  10
#define L_IN3  26
#define L_IN4  28
#define L_ENB  11
#define R_IN1  42
#define R_IN2  44
#define R_ENA  8
#define R_IN3  38
#define R_IN4  40
#define R_ENB  9

class Motor{
public:
  Motor();
  void begin(void); // sets motor pins as OUTPUT
  void setSpeed(int Lspeed, int Rspeed); // sets pwm signal sent to motor shied
  void brake(void); // brake in case of urgent stop
  void turn_left(int speed, int amount); // amount stands for 10 degrees per number
  void turn_right(int speed, int amount); // amount stands for 10 degrees per number 
  int R_count;
  int L_count; 
  bool brakeState;
  ~Motor();


private:  
  int _L_in1;
  int _L_in2;
  int _L_enA;
  int _L_in3;
  int _L_in4;
  int _L_enB;
  int _R_in1;
  int _R_in2;
  int _R_enA;
  int _R_in3;
  int _R_in4;
  int _R_enB;
};

#endif
