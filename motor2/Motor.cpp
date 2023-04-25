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
  R_count = 0;
  L_count = 0;
  brakeState = true;
}

void Motor::begin(void) {
  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(L_ENA, OUTPUT);

  pinMode(L_IN3, OUTPUT);
  pinMode(L_IN4, OUTPUT);
  pinMode(L_ENB, OUTPUT);

  pinMode(R_IN2, OUTPUT);
  pinMode(R_IN2, OUTPUT);
  pinMode(R_ENA, OUTPUT);

  pinMode(R_IN3, OUTPUT);
  pinMode(R_IN4, OUTPUT);
  pinMode(R_ENB, OUTPUT);
}
void Motor::setSpeed(int Lspeed, int Rspeed) {

  if(Lspeed == Rspeed) {
    L_count = 0;
    R_count = 0;
  }

  if (Lspeed >= 0) {
    digitalWrite(L_IN1, LOW);
    digitalWrite(L_IN2, HIGH);
    analogWrite(L_ENA, Lspeed); // Left front,

    digitalWrite(L_IN3, LOW);
    digitalWrite(L_IN4, HIGH);
    analogWrite(L_ENB, Lspeed); // Left back,
  } else {
    Lspeed *= -1;
    digitalWrite(L_IN1, HIGH);
    digitalWrite(L_IN2, LOW);
    analogWrite(L_ENA, Lspeed);

    digitalWrite(L_IN3, HIGH);
    digitalWrite(L_IN4, LOW);
    analogWrite(L_ENB, Lspeed);
  }

  if (Rspeed >= 0) {
    digitalWrite(R_IN2, LOW);
    digitalWrite(R_IN2, HIGH);
    analogWrite(R_ENA, Rspeed); // Right front ,

    digitalWrite(R_IN3, HIGH);
    digitalWrite(R_IN4, LOW);
    analogWrite(R_ENB, Rspeed); // Right Back,

  } else {
    Rspeed *= -1;
    digitalWrite(R_IN2, HIGH);
    digitalWrite(R_IN2, LOW);
    analogWrite(R_ENA, Rspeed);

    digitalWrite(R_IN3, LOW);
    digitalWrite(R_IN4, HIGH);
    analogWrite(R_ENB, Rspeed);
  }
  delay(50);
}

void Motor::turn_left(int speed, int amount) {
  setSpeed(amount * -10, speed);
  delay(200);
  L_count++;
  R_count--;
}
void Motor::turn_right(int speed, int amount) {
  setSpeed(speed, amount * -10);
  delay(200);
  R_count++;
  L_count--;
}

void Motor::brake(void) {
  if (!brakeState)
    return;
  setSpeed(-80, -80);
  delay(200);
  setSpeed(0, 0);
  delay(150);
  brakeState = false;
}

Motor::~Motor() { setSpeed(0, 0); }
