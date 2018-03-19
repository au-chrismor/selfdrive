/*
 * Steering controller
 * Christopher F. Moran, March 2018
 */
 
#include <Servo.h>
#include <EEPROM.h>

#include "steering-hw.h"

void setSteering(int val);
void ledFlash(void);

Servo servo;
int min;        // Contains limit values to avoid
int max;        // damage to servo motor

int pos = 0;    // variable to store the servo position

int ledState = 0;

void setSteering(int val) {
  servo.write(val);
}

void ledFlash(void) {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void moveForward(void) {
  digitalWrite(MOTOR_A, HIGH);
  digitalWrite(MOTOR_B, LOW);
}

void moveReverse(void) {
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, HIGH);
}

void moveStop(void) {
  digitalWrite(MOTOR_A, LOW);
  digitalWrite(MOTOR_B, LOW);
}

void setup() {
  int val = 0;

  // Set up the on-board LED
  pinMode(LED_PIN, OUTPUT);

  // Init the serial line
  Serial.begin(115200);
  
  servo.attach(SERVO_PIN, 900, 2000);   // Instantiate a servo object.  For the big servo we need to
                                  // Set pulse width values.  These were determined experimentally
  pos = 90;
  setSteering(90);

  
  // Check and see if there are calibration values stored
  val=EEPROM.read(MAX_ADDR);
  if(val == 0 || val > 180)
      max = 155;
  else
      max = val;

  val=EEPROM.read(MIN_ADDR);
  if(val == 0 || val > 180 || val > max)
      min = 30;
  else
      min = val;

  // Set up the motor control
  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  // Stop everything
  moveStop();
}

// loop waits for a command and acts appropriately
void loop() {
  if(Serial.available() > 0) {
    switch(Serial.read()) {
      case '.':
        if(pos < max) {
          pos++;
          ledFlash();
        }
        break;
      case '>':
        if(pos < max - 5) {
          pos+=5;
          ledFlash();
        }
        break;
      case ',':
        if(pos > min) {
          pos--;
          ledFlash();
        }
        break;
      case '<':
        if(pos > min + 5) {
          pos-=5;
          ledFlash();
        }
        break;
      case 'f':
      case 'F':
        moveForward();
        break;
      case 'r':
      case 'R':
        moveReverse();
        break;
      case 's':
      case 'S':
        moveStop();
        break;
      default:
        break;
    }
    setSteering(pos);
  }
}

