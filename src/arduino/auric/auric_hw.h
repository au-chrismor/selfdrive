// This header file contains the hardware definitions

#ifdef _NODEMCU
#define PWMA    D1  // Motor A PWM Pin
#define PWMB    D2  // Motor B PWM
#define DIRA    D3  // Motor A Direction Pin
#define DIRB    D4  // Motor B Direction
#endif

#ifdef _UNO
#define PWMA    10  // Motor A PWM Pin
#define PWMB    5  // Motor B PWM
#define DIRA1   9  // Motor A Direction Pin
#define DIRA2   8  // Motor A Direction Pin
#define DIRB1   7  // Motor B Direction
#define DIRB2   6  // Motor B Direction
#endif
