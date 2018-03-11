
#include <Servo.h>
#include <EEPROM.h>

#define MAX_ADDR  0
#define MIN_ADDR  1


Servo servo;

int min = 30;
int max = 155;

void setup() {
  int val = 0;
  
  servo.attach(9, 900, 2000);  // attaches the servo on pin 9 to the servo object, and set the operating frequency
  servo.write(90);

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
}


void loop() {
  int i = 0;
  for(i = min; i < max + 1; i++) {
    servo.write(i);
    delay(10);
  }
  for(i = max; i > min-1; i--) {
    servo.write(i);
    delay(10);
  }
}

