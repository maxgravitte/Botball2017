#include <kipr/botball.h>
#include "lib.h"


typedef struct{
    int gametime;
}Gamestate;

// Constants
double PI = 3.14159;
double TICKDEGREE = 5.688; //Was 5.6861
double TICKS_PER_INCH = 211; //was 165; // ticks per inch
double TICKS_PER_CM = 64.96;
int BLACK = 1500;
#define ssp set_servo_position
#define gsp get_servo_position

// Motors
int RIGHT_MOTOR = 0;
int LEFT_MOTOR =  1;


// Servos
int JUMPER = 0;
int WRANGLER = 1;
int BOTGRAB = 2;

// Analog Sensors
int LINE_R = 1;
int LINE_L = 0;

// Servo Positions
int JUMPER_DOWN = 2047;
int JUMPER_CLIMB = 1300;
int JUMPER_COW = 800;
int JUMPER_UP = 0;
int JUMPER_BCLIMB= 600;

int WRANGLER_CLOSED = 950;//was 850, changed
int WRANGLER_OPEN = 1600;

int BOTGRAB_OPEN = 1500; //was 1900, toooo far
int BOTGRAB_CLOSED =600;//was 700

// Globals for hhs_run_for
int game_time; // global flag for time left in game
int _func_over; // flag so hhs_run_for knows when to return

void test()
{
 /*
  enable_servos();
  ssp(JUMPER, JUMPER_UP);
  msleep(1000);
  backward(-13, 85, 10, 40);
  jumpWall();
  */
   //forward(40, 70, 10, 20);
  //backward(-40, 70, 10, 20);
  //initRobot();
  //findCow();
  initRobot();
  ssp(JUMPER, JUMPER_COW);
  int area;
  while(1){
  	camera_refresh();
    //point2 cow = get_object_center(0,1);
    //int area = get_object_area(0, 1);
    //printf("%d\n", get_object_count(0));
      //camera_refresh();
      //ow = get_object_center(0,0);
      area = get_object_area(0, 0);
      printf("Area: %d\n", area);
    //printf("X: %d and Y: %d \n", cow.x, cow.y);

    msleep(500);
  }
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void wrangleCowOne()
{
  backward(-8, 90, 10, 20);
  anticlockwise_turn(9, 50, 10, 40);//10 worked before
  ssp(JUMPER, JUMPER_UP);
  backward(-49, 100, 20, 20);
  ssp(WRANGLER, WRANGLER_OPEN);
  findCow1();
  msleep(1500);
  ssp(JUMPER, JUMPER_UP);
  msleep(500);
  forward(19, 75, 10, 20); //was 17
  anticlockwise_turn(115, 60, 10, 40);
  backward(-16, 85, 10, 40);
  jumpWall_1();
}

void wrangleBotGuy()
{

  setServoSlow(JUMPER, JUMPER_UP, 5);
  //msleep(1000);
  turn_until_line(1);
  backward(-14, 75, 10, 20);//-10
  ssp(BOTGRAB, BOTGRAB_OPEN);
  turn_until_line(-1);
  line_follow(11, 65);
  botGrab();
  line_follow(18, 70);
  ssp(JUMPER, JUMPER_UP);
  anticlockwise_turn(115, 60, 10, 40);
  backward(-7, 75, 10, 40);
  jumpWall();
}

void wrangleCowTwo()
{
  backward(-6, 75, 10, 40);
  anticlockwise_turn(120, 65, 10, 40);
  ssp(JUMPER, JUMPER_COW);
  backward(-6, 85, 10, 20);
  ssp(WRANGLER, WRANGLER_OPEN);
  backward(-12, 85, 10, 20);
  ssp(WRANGLER, (WRANGLER_CLOSED-150));
  msleep(1000);
}

void climbTerrace()
{

  //At the wall, following 2nd blue cow pickup
  ssp(JUMPER, JUMPER_UP);
  backward(-19, 100, 10, 20);//was -22

  //At the midline align
  forward(35, 90, 10,20);


  anticlockwise_turn(120,70,10,40);
  backward(-20,90,10,40);

  //At pipe on other side
  forward(12,90,10,20);
  anticlockwise_turn(120,70,10,40);

  backward(-58,95,10,20); //THIS WOULD BE A -58 IF ADDING THE ALIGNMENT

  //Preparing to climb
  forward(6, 90, 10, 20);
  anticlockwise_turn(120, 95, 10, 40);
  ssp(JUMPER, JUMPER_UP);
  backward(-30, 100, 10, 40);



  //Ready to climb
  ssp(JUMPER, JUMPER_UP);
  forward(3, 100, 10, 20);
  clockwise_turn(125, 65, 10, 40);
  ssp(JUMPER, JUMPER_BCLIMB);
  forward(10, 100, 10, 20);
  line_follow(3, 95);
  ssp(JUMPER, JUMPER_COW);
  line_follow(33, 95);
  forward(5, 95, 10, 20);
  line_follow(15, 90); //This was originally 20, but changed to hardcode so that if a tribble got caught, wouldnt mess up
  ssp(JUMPER, JUMPER_UP);

}

void placePieces()
{
 clockwise_turn(55,70,10,40);
  ssp(BOTGRAB, 2047); //This is the max
  msleep(300);
  anticlockwise_turn(110,40,10,40); //90 was a little too little
  ssp(JUMPER, JUMPER_DOWN);
  ssp(WRANGLER, WRANGLER_OPEN);


}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void driveUntilLine(int spd)
{
  while(analog(LINE_L) < BLACK && analog(LINE_R < BLACK))
  {
    motor(RIGHT_MOTOR, spd);
    motor(LEFT_MOTOR, spd);
    msleep(100);
    f();
  }
}

void camera_refresh()
{
  camera_update();
  camera_update();
  camera_update();
  camera_update();
  camera_update();
  camera_update();
  camera_update();
}
void findCow1()
{
  int yVal = 100;
  ssp(JUMPER, JUMPER_COW);
  camera_refresh();
  point2 cow = get_object_center(0,0);
  printf("X: %d and Y: %d \n", cow.x, cow.y);
  while((cow.x > 70 || cow.x < 55) || cow.y < yVal)
  {
  	printf("X: %d and Y: %d \n", cow.x, cow.y);
    if(cow.x < 55)
    {
      motor(LEFT_MOTOR, -55);
      motor(RIGHT_MOTOR, -35);
    }
    else if(cow.x > 70)
    {
      motor(LEFT_MOTOR, -35);
      motor(RIGHT_MOTOR, -55);
    }
    else
    {
      motor(LEFT_MOTOR, -60);
      motor(RIGHT_MOTOR, -60);
    }
  	msleep(500);
    f();
    //msleep(500);
    camera_refresh();
    cow = get_object_center(0,0);
    while(cow.x == 0 && cow.y == 0)
    {
      camera_update();
      cow = get_object_center(0,0);
    }
    printf("X: %d and Y: %d \n", cow.x, cow.y);
    if(cow.y > yVal){
      break;
    }
  }
  backward(-2, 75, 10, 40);
  ssp(WRANGLER, WRANGLER_CLOSED);
}

void findCow2()
{
  ssp(JUMPER, JUMPER_COW);
  camera_refresh();
  int area = get_object_area(0, 0);
  point2 cow = get_object_center(0,1);
  //printf("X: %d and Y: %d \n", cow.x, cow.y);
  while(area < 11000)
  {
  	//printf("X: %d and Y: %d \n", cow.x, cow.y);
    if(cow.x < 55)
    {
      motor(LEFT_MOTOR, -55);
      motor(RIGHT_MOTOR, -35);
    }
    else if(cow.x > 70)
    {
      motor(LEFT_MOTOR, -35);
      motor(RIGHT_MOTOR, -55);
    }
    else
    {
      motor(LEFT_MOTOR, -60);
      motor(RIGHT_MOTOR, -60);
    }
  	msleep(500);
    f();
    msleep(500);
    camera_refresh();
    cow = get_object_center(0,1);
    area = get_object_area(0, 0);
    while(cow.x == 0 && cow.y == 0)
    {
      camera_update();
      cow = get_object_center(0,1);
      area = get_object_area(0,0);
    }
    //printf("X: %d and Y: %d \n", cow.x, cow.y);
    if(area > 11000){
      break;
    }
  }
  backward(-6, 75, 10, 40);
  ssp(WRANGLER, WRANGLER_CLOSED);
}

void anticlockwise_turn(int deg, int spd, int comp, int thresh)
{
	//This is an attempt to use motor control for turning
	float fDeg = (float) deg;
	float fThresh=(float)thresh * .01; //Thresh is in 100ts of a rotation
	float wheelBase = 16.5; ///this is the distance between the wheels in cm
	int error = 0;
	int lCount = 0;
	int rCount = 0;
	int lTicks = 1436;
	int rTicks = 1436;
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	int dis = (int)((PI* wheelBase) * (abs(fDeg)/360.0) * TICKS_PER_CM);
	while(get_absolute_average_motor_position_counter(LEFT_MOTOR, RIGHT_MOTOR) < dis)
    {
		lCount =(int) (get_motor_position_counter(LEFT_MOTOR) * (1.0/lTicks)); //convert to rotations
		rCount =(int) (get_motor_position_counter(RIGHT_MOTOR) * (1.0/rTicks)); //convert to rotations
		error += (rCount - lCount);
        if(error>fThresh)
        {
			printf("arcing left, correcting right\n");
			motor(LEFT_MOTOR, -(spd));
			motor(RIGHT_MOTOR, (spd-comp));
		}
		else if(error < -fThresh)
        {
			printf("arcing right, correcting left\n");
			motor(LEFT_MOTOR, -(spd-comp));
			motor(RIGHT_MOTOR, (spd));
		}
		else
        {
			printf("on track, no correction\n");
			motor(LEFT_MOTOR, -(spd));
			motor(RIGHT_MOTOR, (spd));
		}
		msleep(50);
	}
	f();
}

// Error compensation driving backward
void backward(int dis, int spd, int comp, int thresh)
{
  clear_motor_position_counter(LEFT_MOTOR);
  clear_motor_position_counter(RIGHT_MOTOR);
  dis *= TICKS_PER_INCH;
  while(get_average_motor_position_counter() > dis){
    //printf("Position: %d \t Dis: %d \n", get_average_motor_position_counter(), dis);
    if(get_motor_position_counter(LEFT_MOTOR) > get_motor_position_counter(RIGHT_MOTOR) + thresh){
      motor(LEFT_MOTOR, -(spd+comp));
      motor(RIGHT_MOTOR, -(spd-comp));
    }
    else if(get_motor_position_counter(RIGHT_MOTOR) > get_motor_position_counter(LEFT_MOTOR) + thresh){
      motor(LEFT_MOTOR, -(spd-comp));
      motor(RIGHT_MOTOR, -(spd+comp));
    }
    else{
      motor(LEFT_MOTOR, -spd);
      motor(RIGHT_MOTOR, -spd);
    }
    msleep(50);
  }
  f();
}

void botGrab()
{
  ssp(BOTGRAB, BOTGRAB_CLOSED);
  msleep(1500);
}

void clockwise_turn(int deg, int spd, int comp, int thresh)
{
	float fDeg = (float) deg;
	float fThresh= (float) thresh *.01;
	float wheelBase = 15.875;
	int error = 0;
	int lCount = 0;
	int rCount = 0;
	int lTicks = 1525;
	int rTicks = 1580;
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	int dis = (int)((PI* wheelBase) * (abs(fDeg)/360.0) * TICKS_PER_CM);
	while(get_absolute_average_motor_position_counter(LEFT_MOTOR, RIGHT_MOTOR) < dis)
    {
		lCount = (int) (get_motor_position_counter(LEFT_MOTOR) * (1.0/lTicks));
		rCount = (int) (get_motor_position_counter(RIGHT_MOTOR) * (1.0/rTicks));
		error += (rCount - lCount);
		if(error>fThresh)
        {
			printf("arcing left, correcting right\n");
			motor(LEFT_MOTOR, (spd));
			motor(RIGHT_MOTOR, -(spd-comp));
		}
		else if(error < -fThresh)
        {
			printf("arcing right, correcting left\n");
			motor(LEFT_MOTOR, (spd-comp));
			motor(RIGHT_MOTOR, -(spd));
		}
		else
        {
			printf("on track, no correction\n");
			motor(LEFT_MOTOR, (spd));
			motor(RIGHT_MOTOR, -(spd));
		}
		msleep(50);
	}
	f();
}

void f()
{
  freeze(LEFT_MOTOR);
  freeze(RIGHT_MOTOR);
}

void forward(int dis, int spd, int comp, int thresh)
{
  clear_motor_position_counter(LEFT_MOTOR);
  clear_motor_position_counter(RIGHT_MOTOR);
  dis *= TICKS_PER_INCH;
  while(get_average_motor_position_counter() < dis){
    //printf("Position: %d \t Dis: %d \n", get_average_motor_position_counter(), dis);
    printf("L: %d\tR: %d\n", get_motor_position_counter(LEFT_MOTOR), get_motor_position_counter(RIGHT_MOTOR));
    if(get_motor_position_counter(LEFT_MOTOR) < (get_motor_position_counter(RIGHT_MOTOR) - thresh)){
      //printf("CORRECT RIGHT\n");
      motor(LEFT_MOTOR, spd+comp);
      motor(RIGHT_MOTOR, spd-comp);
    }
    else if(get_motor_position_counter(RIGHT_MOTOR) < (get_motor_position_counter(LEFT_MOTOR) - thresh)){
      //printf("CORRECT LEFT\n");
      motor(LEFT_MOTOR, spd-comp);
      motor(RIGHT_MOTOR, spd+comp);
    }
    else{
      //printf("STRAIGHT\n");
      motor(LEFT_MOTOR, spd);
      motor(RIGHT_MOTOR, spd);
    }
    msleep(50);
  }
  f();
}

void forward_alt(int dis, int spd, int comp, int thresh)
{
	float fThresh = (float) .001 * thresh;
	int error = 0;
	int lCount = 0;
	int rCount = 0;
	int lTicks = 1436;
	int rTicks = 1436;
	clear_motor_position_counter(LEFT_MOTOR);
	clear_motor_position_counter(RIGHT_MOTOR);
	dis*= TICKS_PER_CM;
	while(get_average_motor_position_counter(LEFT_MOTOR, RIGHT_MOTOR) < dis)
    {
		lCount =(int) (get_motor_position_counter(LEFT_MOTOR) * (1.0/lTicks));
		rCount =(int) (get_motor_position_counter(RIGHT_MOTOR) * (1.0/rTicks));
		error += (rCount - lCount);
		if(error>fThresh)
        {
			printf("arcing left, correcting right\n");
			motor(LEFT_MOTOR, spd);
			motor(RIGHT_MOTOR, spd-comp);
		}
		else if(error < -fThresh)
        {
			printf("arcing right, correcting left\n");
			motor(LEFT_MOTOR, spd-comp);
			motor(RIGHT_MOTOR, spd);
		}
		else
        {
			printf("on track, no correction\n");
			motor(LEFT_MOTOR, spd);
			motor(RIGHT_MOTOR, spd);
		}
		msleep(50);
	}
	freeze(RIGHT_MOTOR);
	freeze(LEFT_MOTOR);
}

int get_absolute_average_motor_position_counter()
{
	return ((abs(get_motor_position_counter(LEFT_MOTOR)) + abs(get_motor_position_counter(RIGHT_MOTOR)))/2);
}

int get_average_motor_position_counter()
{
  return((get_motor_position_counter(LEFT_MOTOR) + get_motor_position_counter(RIGHT_MOTOR))/2);
}

// Alternative to KIPR run_for
void hhs_run_for(int delay,void (*func))
{
    thread tid;
    tid =thread_create(func);
    thread_start(tid);
    _func_over=0;
    game_time=delay;
    while(delay>=1.0 && _func_over!=1){
        msleep(1000);
        delay=delay-1.0;
        printf("%d left in game\n", delay);
        game_time=delay;
    }
    msleep(delay*1000);
    game_time=0;
    thread_destroy(tid);
    ao();
    create_stop();off(0);off(1);off(2);off(3);
    return;
}

void initRobot()
{
  enable_servos();
  ssp(JUMPER, JUMPER_COW);
  ssp(WRANGLER, WRANGLER_CLOSED);
  ssp(BOTGRAB, BOTGRAB_CLOSED);

  camera_close();
  while(!camera_open())
  {
    msleep(50);
  }

  camera_refresh();

  printf("Initialized Successfully!\n");
}

void jumpWall_1()
{
  ssp(JUMPER, JUMPER_DOWN);
  msleep(1000);
  backward(-8, 85, 10, 40);
  setServoSlow(JUMPER, JUMPER_UP, 3);
  msleep(1000);
  backward(-7, 85, 10, 40);
  ssp(JUMPER, JUMPER_DOWN);
  msleep(1500);
  ssp(JUMPER, JUMPER_UP);
  forward(3,75, 10, 40);
}

void jumpWall()
{
  ssp(JUMPER, JUMPER_DOWN);
  msleep(1000);
  backward(-8, 85, 10, 40);
  setServoSlow(JUMPER, JUMPER_UP, 3);
  msleep(1000);
  backward(-7, 85, 10, 40);
  ssp(JUMPER, JUMPER_DOWN);
  msleep(1500);
  ssp(JUMPER, JUMPER_UP);
  forward(3,75, 10, 40);
}

void line_follow(int dis, int spd)
{
  clear_motor_position_counter(LEFT_MOTOR);
  clear_motor_position_counter(RIGHT_MOTOR);
  dis *= TICKS_PER_INCH;
  while(get_average_motor_position_counter() < dis)
  {
    if(analog(LINE_L) < BLACK && analog(LINE_R > BLACK))
    {
      //printf("LEFT\n");
      motor(LEFT_MOTOR, spd);
      motor(RIGHT_MOTOR, (spd/4));
      msleep(50);
    }
    else if(analog(LINE_R) < BLACK && analog(LINE_L > BLACK))
    {
      //printf("RIGHT\n");
      motor(LEFT_MOTOR, (spd/4));
      motor(RIGHT_MOTOR, spd);
      msleep(50);
    }
    else
    {
      //printf("GOOD GOOD GOOD\n");
      motor(LEFT_MOTOR, spd);
      motor(RIGHT_MOTOR, spd);
      msleep(50);
    }

  }
  f();
}

void setServoSlow(int servo, int target, int steps)
{
  int current = get_servo_position(servo);
  int changePerStep = (target - current) / steps;
  int i = 0;
  while(i < steps){
    current = get_servo_position(servo);
    if(changePerStep >=0)
    {
      ssp(servo, current + changePerStep);
        msleep(200);
        i++;
    }
    else
    {
        ssp(servo, current - (abs(changePerStep)));
        msleep(200);
        i++;
    }
  }
  ssp(servo, target);
}

void turn_until_line(int dir)
{
  while(analog(LINE_L) < BLACK && analog(LINE_R) < BLACK)
  {
    if(dir > 0)
    {
      motor(LEFT_MOTOR, 50);
      motor(RIGHT_MOTOR, -50);
      msleep(50);
    }
    else
    {
      motor(RIGHT_MOTOR, 50);
      motor(LEFT_MOTOR, -50);
      msleep(50);
    }
  }
  f();
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
int main()
{
    Gamestate state = {119};
    hhs_run_for(state.gametime, game);
  	//test();
    return 0;
}

void game()
{
  initRobot();
	wrangleCowOne();
	wrangleBotGuy();
  wrangleCowTwo();
  climbTerrace();
  placePieces();
}
