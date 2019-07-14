/***************************
 * Library for WranglerBot *
 ***************************/
extern double PI;
extern double TICKDEGREE;
extern double INCH;
extern int BLACK;

// Motors
extern int RIGHT;
extern int LEFT;


// Servos
extern int JUMPER;
extern int WRANGLER;
extern int BOTGRAB;

// Analog Sensors
extern int LINE_R;
extern int LINE_L;

// Servo Positions
extern int JUMPER_DOWN;
extern int JUMPER_CLIMB;
extern int JUMPER_COW;
extern int JUMPER_UP;
extern int JUMPER_BCLIMB;

extern int WRANGLER_CLOSED;
extern int WRANGLER_OPEN;

// Game Task Library
void initRobot();
void wrangleCowOne();
void wrangleCowTwo();
void wrangleBotGuy();
void climbTerrace();
void placePieces();

// Function Library
void driveUntilLine(int spd);
void camera_refresh();
void findCow1();
void findCow2();
void forward_alt(int dis, int spd, int comp, int thresh);

void anticlockwise_turn(int deg, int spd, int comp, int thresh);
void botGrab();
void clockwise_turn(int deg, int spd, int comp, int thresh);
void backward(int dis, int spd, int comp, int thresh);
void forward(int dis, int spd, int comp, int thresh);
void f();
int get_absolute_average_motor_position_counter();
int get_average_motor_position_counter();
void initRobot();
void jumpWall();
void jumpWall_1();
void line_follow(int dis, int spd);
void setServoSlow(int servo, int target, int steps);
void turn_until_line(int dir);

void test();

void game();
