#include "Motor.h"
#include "Arduino.h"
#include "digitalWriteFast.h"

// #define PORTA *( (volatile byte*)0x22)
// #define PORTD *( (volatile byte*)0x2B)
// #define PORTG *( (volatile byte*)0x34)
// #define PORTL *( (volatile byte*)0x10B)

#define L_IN1 22 // PA0 (AD0) - Port A
#define L_IN2 24 // PA2 (AD2) - Port A
#define L_ENA 10 
#define L_IN3 26 // PA4 (AD4) - Port A
#define L_IN4 28 // PA6 (AD6) - Port A
#define L_ENB 11
#define R_IN1 42 // PL7       - Port L
#define R_IN2 44 // PL5 (OC5C)- Port L
#define R_ENA 8  
#define R_IN3 38 // PD7 (T0)  - Port D
#define R_IN4 40 // PG1 (RD)  - Port G
#define R_ENB 9



Motor::Motor() : R_count(0), L_count(0), brakeState(true) {}

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
// void Motor::setSpeed(int Lspeed, int Rspeed) {

//   if(Lspeed == Rspeed) {
//     L_count = 0;
//     R_count = 0;
//   }

//   if (Lspeed >= 0) {
//     PORTA &= ~(0x01 << 0);  
//     PORTA |= 0x01 << 2;  
//     analogWrite(L_ENA, Lspeed); // Left front,

//     PORTA &= ~(0x01 << 4);
//     PORTA |= 0x01 << 6;
//     analogWrite(L_ENB, Lspeed); // Left back,
//   } else {
//     Lspeed *= -1;

//     PORTA |= 0x01 << 0;
//     PORTA &= ~(0x01 << 2);    
//     analogWrite(L_ENA, Lspeed);

//     PORTA |= 0x01 << 4;
//     PORTA &= ~(0x01 << 6);
//     analogWrite(L_ENB, Lspeed);
//   }

//   if (Rspeed >= 0) {
//     PORTL &= ~(0x01 << 7);
//     PORTL |= 0x01 << 5;
//     analogWrite(R_ENA, Rspeed); // Right front ,

//     PORTD |= 0x01 << 7;
//     PORTG &= ~(0x01 << 1);
//     analogWrite(R_ENB, Rspeed); // Right Back,

//   } else {
//     Rspeed *= -1;

//     PORTL |= 0x01 << 7;
//     PORTL &= ~(0x01 << 5);    
//     analogWrite(R_ENA, Rspeed);

//     PORTD &= ~(0x01 << 7);
//     PORTG |= 0x01 << 1;
//     analogWrite(R_ENB, Rspeed);
//   }
//   delay(50);
// }

void Motor::setSpeed(int Lspeed, int Rspeed) {

  if(Lspeed == Rspeed) {
    L_count = 0;
    R_count = 0;
  }

  if (Lspeed >= 0) {
    digitalWriteFast(L_IN1, LOW);
    digitalWriteFast(L_IN2, HIGH);
    analogWrite(L_ENA, Lspeed); // Left front,

    digitalWriteFast(L_IN3, LOW);
    digitalWriteFast(L_IN4, HIGH);
    analogWrite(L_ENB, Lspeed); // Left back,
  } else {
    Lspeed *= -1;
    digitalWriteFast(L_IN1, HIGH);
    digitalWriteFast(L_IN2, LOW);
    analogWrite(L_ENA, Lspeed);

    digitalWriteFast(L_IN3, HIGH);
    digitalWriteFast(L_IN4, LOW);
    analogWrite(L_ENB, Lspeed);
  }

  if (Rspeed >= 0) {
    digitalWriteFast(R_IN1, LOW);
    digitalWriteFast(R_IN2, HIGH);
    analogWrite(R_ENA, Rspeed); // Right front ,

    digitalWriteFast(R_IN3, HIGH);
    digitalWriteFast(R_IN4, LOW);
    analogWrite(R_ENB, Rspeed); // Right Back,

  } else {
    Rspeed *= -1;
    digitalWriteFast(R_IN1, HIGH);
    digitalWriteFast(R_IN2, LOW);
    analogWrite(R_ENA, Rspeed);

    digitalWriteFast(R_IN3, LOW);
    digitalWriteFast(R_IN4, HIGH);
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
