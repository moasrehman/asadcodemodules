#include "mbed.h"
#include "math.h"

#define THRESH_HI               15
#define THRESH_LO               -15
#define MOUSE_THRESH_UP         5//6
#define MOUSE_THRESH_FORWARD    -1//-3 
#define MOUSE_THRESH_RIGHT      4
#define MOUSE_THRESH_LEFT       -3
#define MOUSE_THRESH_LEFT_CLICK -9
#define MOUSE_THRESH_RIGHT_CLICK 10

#define dev 1
#define mouse 0

char step_nb = true;
#define TIME_OUT 2000

bool z_circ_flag1, z_circ_flag2;


Serial pc(USBTX, USBRX);
Serial sense(p9,p10);

AnalogIn x_read(p18);
AnalogIn y_read(p19);
AnalogIn z_read(p20);

DigitalIn sw_1(p5);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
PwmOut motor(p6);
 /*
int main() {
    // specify period first, then everything else
    motor.period(1.0f);  // 1 second period
    motor.write(0.50f);  // 50% duty cycle
    wait(0.5)          // led flashing
    motor.write(0.00f);  // 0% duty cycle
}
*/
float x=0.00,y=0.00,z=0.00, rho=0.00;
int n, x_val, loc;
//bool x_hi,x_lo,y_hi,y_lo,z_hi,z_lo;
char orient, ot;
char thresh_detect;
int x_clip, y_clip, z_clip;
int arb_var_1, arb_var_2, arb_var_3;
int btn_nb;

char comb_gest_word;
bool conn_flag = false;
bool sw_state, dev_sw;

char orientation(int,int,int);
char gest_word_z_180;
void clip_for_z_180_orientation(void);
void get_accel_data(void);
void gest_detect (int, int, int);
//void gest_decision_tree(int, int, int);
void computer_decision_tree(int, int, int);
void mouse_control(int, int,int);
void device_control (void);
void motor_vibr(float, int);
void dev_vibr(void);
void computer_control(void);
void device_decision_tree (int,int,int);


/* Instruction:
        1. Switch on Sensor unit
        2. After that switch on application unit
        3. Wait for all 4 sensor unit lights to start blinking before doing any gesture
        End of instruction
        */