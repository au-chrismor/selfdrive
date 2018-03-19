
#include <Servo.h>
#include <EEPROM.h>

#define MAX_ADDR  0
#define MIN_ADDR  1

void setSteering(int val);
void saveMax(void);
void saveMin(void);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(9, 900, 2000);  // attaches the servo on pin 9 to the servo object
  pos = 90;
  myservo.write(90);
}

void setSteering(int val) {
  myservo.write(val);
}

void saveMax(void) {
  EEPROM.write(MAX_ADDR, pos);
}

void saveMin(void) {
  EEPROM.write(MIN_ADDR, pos);
}

void loop() {
  if(Serial.available() > 0) {
    switch(Serial.read()) {
      case '.':
      case '>':
        pos+=5;
        break;
      case ',':
      case '<':
        pos-=5;
        break;
      case 'x':
      case 'X':
        saveMax();
        break;
      case 'n':
      case 'N':
        saveMin();
        break;
      default:
        break;
    }
    Serial.println(pos, DEC);
    setSteering(pos);
  }
}

