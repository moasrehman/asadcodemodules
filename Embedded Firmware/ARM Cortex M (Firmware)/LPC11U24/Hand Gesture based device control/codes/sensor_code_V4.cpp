	/*

Version: 
Sensor Unit code V4.0, development over V3.2:

Version Notes
Final code(Only tweaking)

Description:
This code determines orinetatin of inertial mass int sensor and based on the orientation provides commands over bluetooth.
Expected trigger patterns of movement:
1. Up and Left
2. Up and right
3. down and left
4. down and right
5. Shake detection
6. move front
7. move back

Author: Mohammed Asad Rehman

Created: 10AUG2016
*/
#include "mbed.h"
#include "math.h"
#include "gest_tree.h"

Timer t;

char g_detect_wd;
bool g_detect;
int l;
bool btn_flag;
int main()
{
    sense.baud(38400);  // Set buad rate to 38400bps
    sw_1.mode(PullUp);  // Set internal pull up resistor for switch
    motor.period(1.0f); // vibrator motor : 1 second period
    wait(1);
    while(1) {
        if (conn_flag==false) sense.printf("#");

        get_accel_data();
        //pc.printf("%c",orientation(x,y,z));
        clip_for_z_180_orientation();

        //=========shake detection
        if (x_clip >  45) g_detect_wd |= 0x01;
        if (x_clip < -45) g_detect_wd |= 0x10;
        if (g_detect_wd == 0x11) {
            g_detect = !g_detect;
            g_detect_wd = 0x00;
            sense.printf("9321:%d\r\n",g_detect);
            dev_vibr();
            wait(1);            // to undetect any strays
        }
        //========= single point triple action switch
        if ((g_detect == 1)&&(sw_1 == 0)) {
            do {
                btn_nb++;
                wait(0.001);
            } while (sw_1 == 0);
            btn_flag = true;
        }
        if (btn_flag == true) {
            if (btn_nb>2000) {
                dev_sw = 1;
                btn_nb=0;
            } else if (btn_nb<2000) {
                sw_state = !sw_state;
                dev_sw = 0;
                btn_nb = 0;
            }
            btn_flag = false;
        }

        if  ((dev_sw == 1)&&(g_detect == 1)) {
            //pc.printf("0");
            //pc.printf("%d\t%d\t%d\t\r\n",x_clip, y_clip, z_clip); // for plotting
            device_control();
            sense.printf("%c\r\n",208);  // dev
        } else if((sw_state==0)&&(g_detect == 1)&&(dev_sw==0)) {
            //pc.printf("1");
            //pc.printf("%d\t%d\t%d\t\r\n",x_clip, y_clip, z_clip); // for plotting
            //motor_vibr(0.05,2);
            computer_control();
            sense.printf("%c\r\n",135);  // computer
        } else if((sw_state==1)&&(g_detect == 1)&&(dev_sw==0)) {
            mouse_control(x_clip, y_clip, z_clip);
            sense.printf("%c\r\n",220);  // mouse
        }

        //===printfs========================================================================================
        //------------Switch states
        //pc.printf("sw_state : %d, g_detect : %d, dev_sw : %d\r\n", sw_state, g_detect, dev_sw);

        //------------clipped values
        //pc.printf("Clipped\tX:%d\tY:%d\tZ:%d\t\r\n",x_clip, y_clip, z_clip);
        //sense.printf("Clipped\tX:%d\tY:%d\tZ:%d\t\r\n",x_clip, y_clip, z_clip);
        //pc.printf("Gesture word %d\r\n",gest_word_z_180);
        //pc.printf("%d\t%d\t%d\t\r\n",x_clip, y_clip, z_clip); // for plotting
        //pc.printf("%d\r\n",gest_word_z_180);

        //pc.printf("X: %f\tY: %f\tZ: %f\tRho: %f\t",x,y,z, sqrt((double)((x*x)+(y*y)+(z*z))) );
        //pc.printf("%f\t%f\t%f\t%f\t",x,y,z, sqrt((double)((x*x)+(y*y)+(z*z))) );
        //ot = orientation((int)x,(int)y,(int)z);
        //pc.printf("Orientation = %c\r\n",ot);

        //pc.printf("X: %d\tY: %d\tZ: %d\tRho: %d\r\n",(gx*100), (gy*100), (gz*100), std::sqrt(static_cast<float>(gx*gx)+(gy*gy)+(gz*gz)) );
        //pc.printf("%f %f %f %f\r\n",(x*100), (y*100), (z*100), (sqrt((x*x)+(y*y)+(z*z)))*10 );

        x = 0.00;
        y = 0.00;
        z = 0.00;
        wait(0.05);
    }
}

void device_control (void)
{
    device_decision_tree (x_clip, y_clip, z_clip);
}
void device_decision_tree (int x_cl,int y_cl,int z_cl)
{
    motor.write(0.00f); // vibr off
    t.start();                          //'TIME_OUT' duration timer implemented
    if (t.read_ms() < TIME_OUT) {
        //=========Gesture detect step 1
        if (step_nb == 0x01) {
            if (x_cl > THRESH_HI) {
                gest_word_z_180 |= 0b10000; // 16 detection in x
                gest_word_z_180 |= 0b00010; // 2 detection in hi    //FORWARD
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 1 fwd\r\n");
            } else if (x_cl < THRESH_LO) {
                gest_word_z_180 |= 0b10000; // 16 detection in x
                gest_word_z_180 |= 0b00001; // 1 detection in LO    //REVERSE
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 1 rev\r\n");
            } else if (y_cl > THRESH_HI) {
                gest_word_z_180 |= 0b01000; // 8
                gest_word_z_180 |= 0b00010; // 2                  //LEFT
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 1 left\r\n");
            } else if (y_cl < THRESH_LO) {
                gest_word_z_180 |= 0b01000; // 8
                gest_word_z_180 |= 0b00001; // 1                  //RIGHT
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 1 RIGHT\r\n");
            } else if (z_cl > THRESH_HI) {
                gest_word_z_180 |= 0b00100; // 4
                gest_word_z_180 |= 0b00010; // 2                  //DOWN
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 1 down\r\n");
            } else if (z_cl < THRESH_LO) {
                gest_word_z_180 |= 0b00100; // 4
                gest_word_z_180 |= 0b00001; // 1                  //UP
                t.reset();
                step_nb++;
                //pc.printf("In step 1 up\r\n");
            }
        }
        //pc.printf("gest_word_z_180 = %d, step nb = %d\r\n",gest_word_z_180, step_nb);
        //=========Gesture detect step 2
        if (step_nb==0x02) {
            if ((gest_word_z_180 == 5)&&(y_cl > THRESH_HI)) {   //up and left
                comb_gest_word |= 0b00000001;
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 2: up left\r\n");
            } else if ((gest_word_z_180 == 5)&&(y_cl < THRESH_LO)) { //up and right
                comb_gest_word |= 0b00000010;                       // door open
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 2: up right\r\n");
            } else if((gest_word_z_180 == 6)&&(y_cl > THRESH_HI)) { //down and left
                comb_gest_word |= 0b00000100;
                t.reset();
                wait(0.2);
                step_nb++;
                // pc.printf("In step 2: down left\r\n");
            } else if((gest_word_z_180 == 6)&&(y_cl < THRESH_LO)) { //down and right
                comb_gest_word |= 0b00001000;
                t.reset();
                wait(0.2);
                step_nb++;
                // pc.printf("In step 2: down right\r\n");
            } else if((gest_word_z_180 == 9)&&(z_cl < THRESH_LO)) { //right and up
                comb_gest_word |= 0b00010000;
                t.reset();
                wait(0.2);
                step_nb++;
                //   pc.printf("In step 2: right up\r\n");
            } else if((gest_word_z_180 == 9)&&(z_cl > THRESH_HI)) { //right and down
                comb_gest_word |= 0b00100000;
                t.reset();
                wait(0.2);
                step_nb++;
                // pc.printf("In step 2: right down\r\n");
            } else if((gest_word_z_180 == 10)&&(z_cl < THRESH_LO)) { //left and up
                comb_gest_word |= 0b01000000;
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 2: left up\r\n");
            } else if((gest_word_z_180 == 10)&&(z_cl > THRESH_HI)) { //left and down
                comb_gest_word |= 0b10000000;                       // door close
                t.reset();
                wait(0.2);
                step_nb++;
                //pc.printf("In step 2: left down\r\n");
            }
        }
//    pc.printf("comb_gest_word = %d, step number = %d\r\n",comb_gest_word, step_nb);

        if (step_nb==0x03) {
            switch(comb_gest_word) {
                case 128:       // up and left
//                       pc.printf("Up and left detected\r\n");
                    sense.printf("a");
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 64:       // up and right
//                         pc.printf("Up and right detected\r\n");
                    sense.printf("b");
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 32:       // down and left
//                        pc.printf("Down and left detected\r\n");
                    sense.printf("c");
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 16:       // down and right
//                     pc.printf("Down and left detected\r\n");
                    sense.printf("d");
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 8:       // right and up
//                     pc.printf("Down and left detected\r\n");
                    sense.printf("e");
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 4:       // right and down
//                    pc.printf("Down and left detected\r\n");
                    sense.printf("f");
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 2:       // left and down
//                    pc.printf("Down and left detected\r\n");
                    sense.printf("r");          // g replaced for rhythmbox testing
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                case 1:       // left and up
//                     pc.printf("Down and left detected\r\n");
                    sense.printf("t");          // h replaced for totem testing
                    gest_word_z_180 = 0x00;
                    comb_gest_word = 0x00;
                    dev_vibr();
                    t.stop();
                    t.reset();
                    step_nb=0x01;
                    break;
                default :
                    break;
            }
        }
    } else if (t.read_ms() > TIME_OUT) {
        t.stop();
//        pc.printf("The time taken was %d milli seconds\n", t.read_ms());
        sense.printf("%c%c\r\n",170,174);    // timer rst
        t.reset();
        step_nb=0x01;
        gest_word_z_180 = 0x00;
        comb_gest_word = 0x00;
    }
}

void computer_control(void)
{
    computer_decision_tree(x_clip, y_clip, z_clip);
}
//----------------New:
void computer_decision_tree(int x_cl, int y_cl, int z_cl)
{
    //pc.printf("%d\t%d\t%d\t\r\n",x_clip, y_clip, z_clip); // for plotting
    motor.write(0.00f); //vibr off
    conn_flag=true;
    //media controls
    if (/*(x_cl > 8)&&(z_cl > 7)&&*/(y_cl < -30)) { //if (y_cl < THRESH_LO) { // media track neXt
        sense.printf("x");
        wait(0.2);
    } else if (/*(x_cl > 9)&&(z_cl > 9)&&*/(y_cl > 30)) { // media track preVious
        sense.printf("v");
        wait(0.2);
    } else if ((z_cl > 15)/*&&(abs(x_cl) < 8)&&(abs(y_cl) < 8)*/) { // Media volume Hi
        sense.printf("l");
        wait(0.2);
    } else if((z_cl < -15)/*&&(abs(x_cl) < 8)&&(abs(y_cl) < 8)*/) {  // Media volume Lo
        sense.printf("h");
        wait(0.2);
    } else if( (abs(z_cl) > 9)&&(abs(x_cl) <2)&&(abs(y_cl) > 9) ) { // Media pause
        sense.printf("u");
        wait(1);
    }
    /*
    else if ((z_cl>3)&&(x_cl<1)&&(y_cl<1)) z_circ_flag1 =1; // Fast FWD/REV
    if ((z_circ_flag1 ==1)&&(y_cl>3)&&(x_cl <1)) {
        z_circ_flag1 = 0;
        sense.printf("f");
    }//circ_motion_1 = 1;}
    else if ((z_cl>1)&&(x_cl<1)&&(y_cl<3)) z_circ_flag2 =1;  // Compl. Fast FWD/REV
    if ((z_circ_flag2 ==1)&&(z_cl>3)&&(x_cl <1)) {
        z_circ_flag2 = 0;
        sense.printf("r");
    }//circ_motion_2 = 1;}
    */
}
void mouse_control(int x_cl, int y_cl, int z_cl)
{
    //pc.printf("%d\t%d\t%d\t\r\n",x_cl, y_cl, z_cl); // for plotting
    motor.write(1.00f);  // 50% duty cycle
    //motor_vibr(0.05,2);
    conn_flag= true;
    //sense.baud(38400);
    if(x_cl >= MOUSE_THRESH_UP) {   //if((x_cl >= 4)&&(x_cl < 9)) {
        sense.printf("N");    //U
        led1=!led1;
        //wait(0.002);//wait(0.2);
    }
    if(x_cl <= MOUSE_THRESH_FORWARD)  {
        sense.printf("S");    //  F
        led2=!led2;
        //wait(0.002);//wait(0.2);
    }
    if(y_cl >= MOUSE_THRESH_RIGHT)  {
        if(y_cl >= MOUSE_THRESH_RIGHT_CLICK) {
            sense.printf("4");    //  R
            led4=!led4;
            //  wait(0.002);//wait(0.2);
            led4=!led4;
        } else {
            sense.printf("E");
            led3=!led3;
        }
        //wait(0.002);//wait(0.2);
    }
    if(y_cl <= MOUSE_THRESH_LEFT) {
        if(y_cl <= MOUSE_THRESH_LEFT_CLICK) {
            sense.printf("6");
            led1=!led1;
            //  wait(0.002);//wait(0.2);
            led1=!led1;
        } else {
            sense.printf("W");    //L
            led4=!led4;
        }
        //wait(0.002);//wait(0.2);
    }
    wait(0.050);//wait(0.2);
    //motor.write(0.00f);  // 0% duty cycle
}
void dev_vibr(void)
{
    motor_vibr(0.2,2);
}

void motor_vibr(float dla, int vib_nb)
{
    motor.period(1.0f);  // 1 second period
    for (l=0; l<vib_nb; l++) {
        motor.write(0.50f);  // 50% duty cycle
        wait(dla);
        motor.write(0.00f);  // 0% duty cycle
        wait(dla);
    }
}

/*
//----------Old:
void gest_decision_tree(int x_cl, int y_cl, int z_cl)
{
    conn_flag= true;
    //z-180 gesture decision tree
    //if ((rho<0.85)&&(x_clip > THRESH_HI)) {
    if (x_cl > THRESH_HI) {
        gest_word_z_180 |= 0b10000; // 16 detection in x
        gest_word_z_180 |= 0b00010; // 2 detection in hi
    } else if (x_cl < THRESH_LO) {
        gest_word_z_180 |= 0b10000; // 16 detection in x
        gest_word_z_180 |= 0b00001; // 1 detection in LO
    } else if (y_cl > THRESH_HI) {
        gest_word_z_180 |= 0b01000; // 8
        gest_word_z_180 |= 0b00010; // 2
    } else if (y_cl < THRESH_LO) {
        gest_word_z_180 |= 0b01000; // 8
        gest_word_z_180 |= 0b00001; // 1
    } else if (z_cl > THRESH_HI) {
        gest_word_z_180 |= 0b00100; // 4
        gest_word_z_180 |= 0b00010; // 2
    } else if (z_cl < THRESH_LO) {
        gest_word_z_180 |= 0b00100; // 4
        gest_word_z_180 |= 0b00001; // 1
    } else gest_word_z_180 |= 0xFF;

    switch(gest_word_z_180) {
        case 180:   //off
            //pc.printf("Forward detected\r\n");
            //fwd = true;
            //comb_gest_word =   <-------------------- use this....... combinational gesture word
            sense.printf("a");
            wait(0.2);
            break;
        case 170:   //off
            //pc.printf("Reverse detected\r\n");
            sense.printf("b");
            wait(0.2);
            break;
        case 10:
            //pc.printf("Left detected\r\n");
            sense.printf("c");
            wait(0.2);
            break;
        case 9:
            //pc.printf("Right detected\r\n");
            //if(fwd==true) {pc.print("t"); fwd = false;}
            sense.printf("d");
            wait(0.2);
            break;
        case 6:
            //pc.printf("Down detected\r\n");
            sense.printf("e");
            wait(0.2);
            break;
        case 5:
            //pc.printf("Up detected\r\n");
            sense.printf("f");
            wait(0.2);
            break;
        default :
            break;
    }

    if ((gest_word_z_180&0b11) == 0b11)gest_word_z_180 = 0;

    //if(arb_var_1 >= 100){pc.printf("Rho = %d\r\n",sqrt((double)((x_clip*x_clip)+(y_clip*y_clip)+(z_clip*z_clip)))); arb_var_1=0;}
    //arb_var_1++;
}
*/

void get_accel_data(void)
{
    conn_flag= true;
    while(n<10) {   //cumulative averaging filter
        wait(0.00002); //20 u sec delay for smoother readings
        //pc.printf("Accummulated accelero value:%f\r\n",x);
        x+=x_read.read();
        y+=y_read.read();
        z+=z_read.read();
        n++;
    }
    n = 0;
    x=x*10;//x=x/10; <-- Scaled to 100 //pc.printf("x=%f\r\n",x);
    y=y*10;//y=y/10; <-- Scaled to 100
    z=z*10;//z=z/10; <-- Scaled to 100
}

void clip_for_z_180_orientation(void)
{
    conn_flag= true;
    x_clip=x-51;
    y_clip=y-51;
    z_clip=z-41;
}
//------ NOTE: merge these two /\ and \/
char orientation(int x,int y,int z)
{
    conn_flag= true;
    if((z<43)&&((x>47)&&(x<53))&&((y>47)&&(y<53))) { //z 180
        //pc.printf("z_180\r\n");
        orient = 2;
        //pc.printf("%c\n\r",'o');
        //oreint_z = 1;
        return 'r';
    } else if((z>55)&&((x>47)&&(x<53))&&((y>47)&&(y<53))) { //z 0
        //pc.printf("z_0\r\n");
        orient = 1;
        //pc.printf("%c\n\r",'o');
        //oreint_z = 1;
        return 'o';
    } else if((y<43)&&((z>47)&&(z<53))&&((x>47)&&(x<53))) { //y 180
        //pc.printf("y_180\r\n");
        orient = 6;
        //pc.printf("%c\n\r",'o');
        //oreint_z = 1;
        return 'e';
    } else if((y>55)&&((z>47)&&(z<53))&&((x>47)&&(x<53))) { //y 0
        //pc.printf("y_0\r\n");
        orient = 5;
        //pc.printf("%c\n\r",'o');
        //oreint_z = 1;
        return 'g';
    }

    else if((x<43)&&((y>47)&&(y<53))&&((z>47)&&(z<53))) { //x 180
        //pc.printf("x_180\r\n");
        orient = 4;
        //pc.printf("%c\n\r",'o');
        //oreint_z = 1;
        return 'n';
    } else if((x>55)&&((y>47)&&(y<53))&&((z>47)&&(z<53))) { //x 0
        //pc.printf("y_0\r\n");
        orient = 3;
        //pc.printf("%c\n\r",'o');
        //oreint_z = 1;
        return 'a';
    }
    return;
}
