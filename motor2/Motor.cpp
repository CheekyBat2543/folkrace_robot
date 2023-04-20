#include "Motor.h"
#include "Arduino.h"


#define L_TRIG 5
#define L_ECHO 4
#define R_TRIG 52
#define R_ECHO 50
#define M_TRIG 7
#define M_ECHO 6
#define L_IN1 22
#define L_IN2 24
#define L_ENA 10
#define L_IN3 26
#define L_IN4 28
#define L_ENB 11
#define R_IN1 42
#define R_IN2 44
#define R_ENA 8
#define R_IN3 38
#define R_IN4 40
#define R_ENB 9

Motor::Motor() {
  _L_in1 = L_IN1;
  _L_in2 = L_IN2;
  _L_enA = L_ENA;
  _L_in3 = L_IN3;
  _L_in4 = L_IN4;
  _L_enB = L_ENB;
  _R_in1 = R_IN1;
  _R_in2 = R_IN2;
  _R_enA = R_ENA;
  _R_in3 = R_IN3;
  _R_in4 = R_IN4;
  _R_enB = R_ENB;
  R_count = 0;
  L_count = 0;
  brakeState = true;
}

void Motor::begin(void) {
  pinMode(_L_in1, OUTPUT);
  pinMode(_L_in2, OUTPUT);
  pinMode(_L_enA, OUTPUT);

  pinMode(_L_in3, OUTPUT);
  pinMode(_L_in4, OUTPUT);
  pinMode(_L_enB, OUTPUT);

  pinMode(_R_in1, OUTPUT);
  pinMode(_R_in2, OUTPUT);
  pinMode(_R_enA, OUTPUT);

  pinMode(_R_in3, OUTPUT);
  pinMode(_R_in4, OUTPUT);
  pinMode(_R_enB, OUTPUT);
}
void Motor::setSpeed(int Lspeed, int Rspeed) {

  if (Lspeed >= 0) {
    digitalWrite(_L_in1, LOW);
    digitalWrite(_L_in2, HIGH);
    analogWrite(_L_enA, Lspeed); // Left front,

    digitalWrite(_L_in3, LOW);
    digitalWrite(_L_in4, HIGH);
    analogWrite(_L_enB, Lspeed); // Left back,
  } else {
    Lspeed *= -1;
    digitalWrite(_L_in1, HIGH);
    digitalWrite(_L_in2, LOW);
    analogWrite(_L_enA, Lspeed);

    digitalWrite(_L_in3, HIGH);
    digitalWrite(_L_in4, LOW);
    analogWrite(_L_enB, Lspeed);
  }

  if (Rspeed >= 0) {
    digitalWrite(_R_in1, LOW);
    digitalWrite(_R_in2, HIGH);
    analogWrite(_R_enA, Rspeed); // Right front ,

    digitalWrite(_R_in3, HIGH);
    digitalWrite(_R_in4, LOW);
    analogWrite(_R_enB, Rspeed); // Right Back,

  } else {
    Rspeed *= -1;
    digitalWrite(_R_in1, HIGH);
    digitalWrite(_R_in2, LOW);
    analogWrite(_R_enA, Rspeed);

    digitalWrite(_R_in3, LOW);
    digitalWrite(_R_in4, HIGH);
    analogWrite(_R_enB, Rspeed);
  }
}

void Motor::turn_left(int speed, int amount) {
  setSpeed(amount * -10, speed);
  delay(250);
  L_count++;
  R_count--;
}
void Motor::turn_right(int speed, int amount) {
  setSpeed(speed, amount * -10);
  delay(250);
  R_count++;
  L_count--;
}

void Motor::brake(void) {
  if (!brakeState)
    return;
  setSpeed(-80, -80);
  delay(250);
  setSpeed(0, 0);
  delay(200);
  brakeState = false;
}

Motor::~Motor() { setSpeed(0, 0); }
