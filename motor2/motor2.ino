#include <NewPing.h>

const int L_trig = 5;
const int L_echo = 4;

const int R_trig =52;
const int R_echo =50;

const int M_trig = 7;
const int M_echo = 6;

const int L_in1 = 22;
const int L_in2 = 24;

const int L_enA = 10;
const int L_in3 = 26;

const int L_in4 = 28;
const int L_enB = 11;

const int R_in1 = 42;
const int R_in2 = 44;
const int R_enA = 8;

const int R_in3 = 38;
const int R_in4 = 40;
const int R_enB = 9;

int L_cm = 0;
int M_cm = 0;
int R_cm = 0;

NewPing M_sensor(M_trig, M_echo, 1000);
NewPing R_sensor(R_trig, R_echo, 1000);
NewPing L_sensor(L_trig, L_echo, 1000);

bool brakeState = true;
int R_count = 0;
int L_count = 0;

int i = 0;

void initializeMotors(void){
  pinMode(L_in1, OUTPUT);
  pinMode(L_in2, OUTPUT);
  pinMode(L_enA, OUTPUT);

  pinMode(L_in3, OUTPUT);
  pinMode(L_in4, OUTPUT);
  pinMode(L_enB, OUTPUT);

  pinMode(R_in1, OUTPUT);
  pinMode(R_in2, OUTPUT);
  pinMode(R_enA, OUTPUT);

  pinMode(R_in3, OUTPUT);
  pinMode(R_in4, OUTPUT);
  pinMode(R_enB, OUTPUT);
}

void setSpeed(int Lspeed, int Rspeed){

  if (Lspeed >= 0){
    digitalWrite(L_in1, LOW);
    digitalWrite(L_in2, HIGH);
    analogWrite(L_enA, Lspeed*1.3); // Left front,

    digitalWrite(L_in3, LOW);
    digitalWrite(L_in4, HIGH);
    analogWrite(L_enB, Lspeed*1.3); // Left back, 
  } else {
    Lspeed *= -1;
    digitalWrite(L_in1, HIGH);
    digitalWrite(L_in2, LOW);
    analogWrite(L_enA, Lspeed*1.3);

    digitalWrite(L_in3, HIGH);
    digitalWrite(L_in4, LOW);
    analogWrite(L_enB, Lspeed*1.3);
  }
  if (Rspeed >= -15 && Rspeed <=  15){
    analogWrite(R_enA, 0);
    analogWrite(R_enB, 0);
  }
  else if (Rspeed > 15){
    digitalWrite(R_in1, LOW);
    digitalWrite(R_in2, HIGH);
    analogWrite(R_enA, Rspeed*1.45); // Right front , 

    digitalWrite(R_in3, HIGH);
    digitalWrite(R_in4, LOW);
    analogWrite(R_enB, Rspeed*1.45); //Right Back, 
  }
  else if (Rspeed < -15) {
    Rspeed *= -1;
    digitalWrite(R_in1, HIGH);
    digitalWrite(R_in2, LOW);
    analogWrite(R_enA, Rspeed*1.45);

    digitalWrite(R_in3, LOW);
    digitalWrite(R_in4, HIGH);
    analogWrite(R_enB, Rspeed*1.45);
  }
}  

void brake(void){
  setSpeed(-80, -80);
  delay(250);
  setSpeed(0,0);
  delay(200);
}

void setup() {

  initializeMotors();
  Serial.begin(9600);
  Serial.setTimeout(10);
  delay(2500);
  sensorRead();
}

void sensorRead(void){
  M_cm = M_sensor.ping_cm();
  R_cm = R_sensor.ping_cm();
  L_cm = L_sensor.ping_cm();
  
  if(M_cm == 0) M_cm = 100;
  if(R_cm == 0) R_cm = 100;
  if(L_cm == 0) L_cm = 100;
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
  setSpeed(-50,-50);*/

  //setSpeed(0, -100);
 /* setSpeed(80, 0);
  delay(500);
  setSpeed(0,0);
  delay(500);
  setSpeed(0, 80);
  delay(500);
  while (1){
    setSpeed(0,0);
  } */
  
  if(R_count >= 4){
    while (R_count != 0){
      if(M_cm <= 4 && (R_cm <4 || L_cm < 4)){
        break;
      } else {
        setSpeed(-30, 120);
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
        setSpeed(120, -30);
        delay(200);
        L_count--;
      }
      sensorRead();      
    }
  }

  if (M_cm > 80){ 

    if (L_cm <= 4 || R_cm <= 4){
      if (brakeState == true) brake();
      if (L_cm < R_cm){
        setSpeed(60, -120);
        delay(200);
        setSpeed(0, 0);
        delay(200);
      } else {
        setSpeed(-120, 60);
        delay(200); 
        setSpeed(0, 0);
        delay(200);       
      }
      R_count = 0;
      L_count = 0;
      brakeState = true;
    }
    else if ((L_cm > 4 && L_cm <= 10)||(R_cm > 4 && R_cm <= 10)){
      if (L_cm < R_cm){
        setSpeed(100, -50);
        delay(200);
        R_count++;
      } else {
        setSpeed(-50, 100);
        delay(200);
        L_count++;        
      }
      brakeState = true;
    } 
    else if ((R_cm > 10 && R_cm <= 20) || (L_cm > 10 && L_cm <= 20)){
      if (L_cm < R_cm){
        setSpeed(120, -30);
        delay(250);
        R_count++;
      } else {
        setSpeed(-30, 120);
        delay(250);
        L_count++;
      }
      brakeState = true;
    }
    else if ((R_cm > 20 && R_cm <= 30) || (L_cm > 20 && L_cm <= 30)){
      if (L_cm < R_cm){
        setSpeed(120, 0);
        delay(250);
        R_count++;
      } else {
        setSpeed(0, 120);
        delay(250);
        L_count++;
      }
      brakeState = true;
    } 
    else if (L_cm > 30 && R_cm > 30){
      setSpeed(100,100);
      delay(50);
      brakeState = true;
    }
  } 

  else if (M_cm > 35 && M_cm <= 80) {

    if ((L_cm >= 0 && L_cm <= 4) || (R_cm >= 0 && R_cm <= 4)){
      if (brakeState == true) brake();
      setSpeed(0,0);
      delay(100);
      if (L_cm >= R_cm) {
        setSpeed(-120, 60);
        delay(250);
        setSpeed(0, 0);
        delay(200);
      } else {
        setSpeed(60, -120);
        delay(250);
        setSpeed(0, 0);
        delay(200);
      }
      R_count = 0;
      L_count = 0;
      brakeState = true;
    }
    else if ((L_cm > 4 && L_cm <=10) || (R_cm > 4 && R_cm <= 10)){    
      if (L_cm >= R_cm) {
        setSpeed(-60, 120);
        delay(200);
        L_count++;
      } else {
        setSpeed(120, -60);
        delay(200);
        R_count++;
      }
      brakeState = true;
    }
    else if ((L_cm > 10 && L_cm <=20) || (R_cm > 10 && R_cm <= 20)){     
      if (L_cm >= R_cm) {
        setSpeed(-30, 120);
        delay(200);
        L_count++;
      } else {
        setSpeed(120, -30);
        delay(200);
        R_count++;
      }
      brakeState = true;
    }
    else if ((L_cm > 20 && L_cm <=30) || (R_cm > 20 && R_cm <= 30)){
      if (L_cm >= R_cm) {
        setSpeed(0, 120);
        delay(250);
        L_count++;
      } else {
        setSpeed(120, 0);
        delay(250);
        R_count++;        
      }
      brakeState = true;
    }
    else if (L_cm > 30 && R_cm > 30) {
      if (M_cm <= 40) setSpeed(M_cm+5, M_cm+5);
      else setSpeed((M_cm+20), (M_cm+20));
      delay(50);
      brakeState = true;
    }
  }

  else if(7 < M_cm && M_cm <= 35){

    if (brakeState == true) brake();

    if (R_cm <= 5 || L_cm <= 5){
      if (L_cm < R_cm){
        setSpeed(60, -120);
        delay(200);
        setSpeed(0, 0);
        delay(200);
      } else {
        setSpeed(-120, 60);
        delay(200);
        setSpeed(0, 0);
        delay(200);
      }
      L_count = 0;
      R_count = 0;
    } 
    else if ((R_cm > 6 && R_cm <= 15) || (L_cm > 6 && L_cm <= 15)){
        if (L_cm >= R_cm) {
        setSpeed(-30, 120);
        delay(200);
      } else {
        setSpeed(120, -30);
        delay(200);
      }
    }
    else if (R_cm > 15 && L_cm > 15){
      if (L_cm >= R_cm) {
        setSpeed(-20, 120);
        delay(200);
        L_count++;
      } else {
        setSpeed(120, -20);
        delay(200);
        R_count++;
      }
    }
    brakeState = true;   
  }

  else if(M_cm > 0 && M_cm <= 7){
    if (brakeState == true) brake();
    if (L_cm < R_cm){
      setSpeed(60, -120);
      delay(200);
      setSpeed(0, 0);
      delay(200);
      } else {
      setSpeed(-120, 60);
      delay(200);
      setSpeed(0,0);
      delay(200);
    }
    L_count = 0;
    R_count = 0;
    brakeState = true;
  }
}
