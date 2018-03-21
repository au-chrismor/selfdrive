/*
 * Steering and drive controller
 * Christopher F. Moran, March 2018
 */
 
/*
 * PORT ALLOCATIONS
 * PORT     DESGINATION     DIRECTION     TYPE      DESCRIPTION
 * D13      LED_PIN         OUT           DIGITAL   On-Board LED
 * D12      ECHO_PIN        IN            DIGITAL   Ultrasonic Receive
 * D11
 * D10      TRIG_PIN        OUT           DIGITAL   Ultrasonic Trigger
 * D09      SERVO_PIN       OUT           PWM       Steering Servo Control
 * D08
 * D07
 * D06
 * D05
 * D04      MOTOR_A         OUT           DIGITAL   Drive Motor Control
 * D03      MOTOR_B         OUT           DIGITAL   Drive Motor Control
 * D02
 * D01      SERIAL
 * D00      SERIAL
 * A05      SCK             OUT           I2C       I2C Clock
 * A04      SDA             I/O           I2C       I2C Data
 * A03
 * A02
 * A01
 * A00      IBATT           IN            ANALOGUE  Battery Current Sensor
 */ 
#include <Servo.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "steering-hw.h"

void setSteering(int val);
void ledFlash(void);

Servo servo;
int min;        // Contains limit values to avoid
int max;        // damage to servo motor

int pos = 0;    // variable to store the servo position

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

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

double readCurrent(void) {
  double mV = (double)analogRead(IBATT) / 1024 * 5000;

  return ((mV - AC_OFFSET) / MV_PER_AMP);
}

void setup() {
  int val = 0;

  // Set up the LCD Display
  lcd.begin();
  lcd.backlight();

  // Set up the on-board LED
  pinMode(LED_PIN, OUTPUT);

  // Set up host interface
  pinMode(US_OUT, OUTPUT);
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

  lcd.print("Release 0.5.1");
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

    // Update the dashboard
    lcd.clear();

    lcd.print("iBatt: ");
    lcd.print(readCurrent(), 3);
    lcd.print(" A");
  }
}

