/*
    Copyright (C) 2018, by Christopher F. Moran and Emergent Technology
    This is original work contains products developed by other organisations
    including, but not limited to:
    Adafruit
 */
#include "features.h"
#include "auric_hw.h"

int ledState = 0;
int speedL = 0;
int speedR = 0;


int Speed(String buffer) {
  int speed = 0;
  int idx = buffer.indexOf(":");
  if(idx > 0)
    return buffer.substring(idx+1).toInt();
  else
    return -1;
}

/*
 * It is probably not necessary to go through such
 * drama to find the side, but better to be sure
 */
char Channel(String buffer) {
  int idx = buffer.indexOf(":");
  if(idx > 0) {
    if(buffer.substring(0, idx) == "R")
      return 'R';
    if(buffer.substring(0, idx) == "L")
      return 'L';
  }
}

void setup()
{
  Serial.begin(19200);
#ifdef _NODEMCU  
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
#endif
#ifdef _UNO
  pinMode(DIRA, OUTPUT);
  pinMode(BRKA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(BRKB, OUTPUT);
#endif
  pinMode(LED_BUILTIN, OUTPUT);
  Stop();
}

void loop()
{
#ifdef BURN_IN
  Forward(255);
  delay(2000);
  Stop();
  delay(1000);
  Reverse(255);
  delay(2000);
  Stop();
  delay(1000);
  Left(255);
  delay(2000);
  Stop();
  delay(1000);
  Right(255);
  delay(2000);
  Stop();
  delay(1000);
#endif
  if(Serial.available() > 0)
  {
    String buffer = Serial.readString();
    switch(Channel(buffer)) {
      case 'L':
        speedL = Speed(buffer);
        ledState = 1;
        break;
      case 'R':
        speedR = Speed(buffer);
        ledState = 1;
        break;
      default:
        ledState = 0;
        break;
    }
    if(ledState)
    {
      DiffFwd(speedL, speedR);
      Serial.println("0");
    }
    else
      Serial.println("1");
    Serial.flush();
  }
  digitalWrite(LED_BUILTIN, ledState);
}
#ifdef _NODEMCU
void Stop()
{
  digitalWrite(PWMA,0);
  digitalWrite(PWMB, 0);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

void DiffFwd(int leftVal, int rightVal)
{
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,HIGH);
  analogWrite(PWMA, leftVal);
  analogWrite(PWMB, rightVal);
}

void DiffRev(int leftVal, int rightVal)
{
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,LOW);
  analogWrite(PWMA, leftVal);
  analogWrite(PWMB, rightVal);
}

void Forward(int speedVal)
{
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void Reverse(int speedVal)
{
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void Left(int speedVal)
{
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,HIGH);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void Right(int speedVal)
{
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,LOW);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}
#endif
#ifdef _UNO
void Stop()
{
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(BRKA, HIGH);
  digitalWrite(BRKB, HIGH);
}

void DiffFwd(int leftVal, int rightVal)
{
  digitalWrite(BRKA, LOW);  // Disengage braking
  digitalWrite(BRKB, LOW);
  digitalWrite(DIRA, HIGH); // Forward
  digitalWrite(DIRB, HIGH);
  analogWrite(PWMA,leftVal);
  analogWrite(PWMB,rightVal);
}

void DiffRev(int leftVal, int rightVal)
{
  digitalWrite(BRKA, LOW);  // Disengage braking
  digitalWrite(BRKB, LOW);
  digitalWrite(DIRA, LOW); // Reverse
  digitalWrite(DIRB, LOW);
  analogWrite(PWMA,leftVal);
  analogWrite(PWMB,rightVal);
}

void Forward(int speedVal)
{
  digitalWrite(BRKA, LOW);  // Disengage braking
  digitalWrite(BRKB, LOW);
  analogWrite(PWMA,speedVal);
  analogWrite(PWMB,speedVal);
  digitalWrite(DIRA, HIGH); // Forward
  digitalWrite(DIRB, HIGH);
}

void Reverse(int speedVal)
{
  digitalWrite(BRKA, LOW);  // Disengage braking
  digitalWrite(BRKB, LOW);
  analogWrite(PWMA,speedVal);
  analogWrite(PWMB,speedVal);
  digitalWrite(DIRA, LOW);  // Reverse
  digitalWrite(DIRB, LOW);
}

void Right(int speedVal)
{
  digitalWrite(BRKA, LOW);  // Disengage braking
  digitalWrite(BRKB, LOW);
  analogWrite(PWMA,speedVal);
  analogWrite(PWMB,speedVal);
  digitalWrite(DIRA, LOW);  // Reverse
  digitalWrite(DIRB, HIGH); // Forward
}

void Left(int speedVal)
{
  digitalWrite(BRKA, LOW);  // Disengage braking
  digitalWrite(BRKB, LOW);
  analogWrite(PWMA,speedVal);
  analogWrite(PWMB,speedVal);
  digitalWrite(DIRA, HIGH);  // Reverse
  digitalWrite(DIRB, LOW); // Forward
}
#endif
