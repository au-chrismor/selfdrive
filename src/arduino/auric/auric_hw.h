// This header file contains the hardware definitions

#ifdef _NODEMCU
#define PWMA    D1  // Motor A PWM Pin
#define PWMB    D2  // Motor B PWM
#define DIRA    D3  // Motor A Direction Pin
#define DIRB    D4  // Motor B Direction
#endif

#ifdef _UNO
#include <AFMotor.h>
AF_DCMotor motorLeft(1, MOTOR12_1KHZ);
AF_DCMotor motorRight(3, MOTOR12_1KHZ);
#endif
