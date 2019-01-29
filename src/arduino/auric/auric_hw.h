// This header file contains the hardware definitions

#ifdef _NODEMCU
#define PWMA    D1  // Motor A PWM Pin
#define PWMB    D2  // Motor B PWM
#define DIRA    D3  // Motor A Direction Pin
#define DIRB    D4  // Motor B Direction
#endif

#ifdef _UNO
#define DIRA    12  // Motor A Direction
#define BRKA    9   // Motor A Brake
#define PWMA    3

#define DIRB    13  // Motor A Direction
#define BRKB    8   // Motor A Brake
#define PWMB    11
#endif
