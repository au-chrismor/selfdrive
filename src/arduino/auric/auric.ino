
#include "features.h"
#include "rover_hw.h"

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
  Serial.begin(9600);
#ifdef _NODEMCU  
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
#endif
#ifdef _UNO
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA1, OUTPUT);
  pinMode(DIRA2, OUTPUT);
  pinMode(DIRB1, OUTPUT);
  pinMode(DIRB2, OUTPUT);
#endif  
  pinMode(LED_BUILTIN, OUTPUT);
  Stop();
}

void loop()
{
#ifdef BURN_IN
  Forward();
  delay(2000);
  stop();
  delay(1000);
  Reverse();
  delay(2000);
  stop();
  delay(1000);
  Left();
  delay(2000);
  stop();
  delay(1000);
  Right();
  delay(2000);
  stop();
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
  digitalWrite(PWMA,LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

void DiffFwd(int leftVal, int rightVal)
{
  digitalWrite(DIRA,LOW);
  digitalWrite(DIRB,HIGH);
  analogWrite(PWMA, leftVal);
  analogWrite(PWMB, rightVal);
}

void DiffRev(int leftVal, int rightVal)
{
  digitalWrite(DIRA,HIGH);
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
  digitalWrite(DIRA1, LOW);
  digitalWrite(DIRA2, LOW);
  digitalWrite(DIRB1, LOW);
  digitalWrite(DIRB2, LOW);
}

void DiffFwd(int leftVal, int rightVal)
{
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRA2,LOW);
  digitalWrite(DIRB1,HIGH);
  digitalWrite(DIRB2,LOW);
  analogWrite(PWMA, leftVal);
  analogWrite(PWMB, rightVal);
}

void DiffRev(int leftVal, int rightVal)
{
  digitalWrite(DIRA1,LOW);
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRB1,LOW);
  digitalWrite(DIRB1,HIGH);
  analogWrite(PWMA, leftVal);
  analogWrite(PWMB, rightVal);
}

void Forward(int speedVal)
{
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRA2,LOW);
  digitalWrite(DIRB1,HIGH);
  digitalWrite(DIRB2,LOW);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void Reverse(int speedVal)
{
  digitalWrite(DIRA1,LOW);
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRB1,LOW);
  digitalWrite(DIRB1,HIGH);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void Left(int speedVal)
{
  digitalWrite(DIRA1,LOW);
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRB1,HIGH);
  digitalWrite(DIRB2,LOW);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}

void Right(int speedVal)
{
  digitalWrite(DIRA1,HIGH);
  digitalWrite(DIRA2,LOW);
  digitalWrite(DIRB1,LOW);
  digitalWrite(DIRB1,HIGH);
  analogWrite(PWMA, speedVal);
  analogWrite(PWMB, speedVal);
}
#endif
