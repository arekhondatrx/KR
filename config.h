// CONFIG //

// STEPER CONFIG //

#define STEP_DELAY 30 // time between changing state STEP_PIN (3000)
#define STEPS_FOR_ONE_MOVE 50 // amount of steps per one move

// stepper 1 pins
#define STEP1 9
#define DIR1 8

// stepper 2 pins
#define STEP2 6
#define DIR2 7

// stepper 3 pins
#define STEP3 A1
#define DIR3 A0

// stepper 4 pins
#define STEP4 A3
#define DIR4 A2


// SERVOS CONFIG //

#define SERVO_DELAY 10 // time needed to complete move by servo (500 - 800)

// servo 1 pin
#define S0 20 // A6 it does not work, PWM does not work on this pin :(, on A7 too :(

// servo 2 pin
#define S1 4 //150-180 angle

// servo 3 pin
#define S2 19 // A5 150-180 angle

// servo 4 pin
#define S3 2 //140-180 angle

// servo 5 pin
#define S4 3//148-180 angle

// servos open and close angles
#define SERVO_OPEN 150 // angle, when servo is opening the manipulator
#define SERVO_CLOSE 114 // angle, when servo is closing the manipulator

// OTHER CONSTANTLY //

#define TERMINATOR ':'
#define END_DATA '^'
#define DATA_SIGNS 58
#define UP_NUMBER 58
#define DOWN_NUMBER 47
#define TO_INT 48
#define START '^'
#define PAUSE '@'
#define STOP '~'
#define GET_COLOR '<'
#define MAX_SIZE_TAB_MOVES 150
#define GET_COLOR_DELAY 3500
