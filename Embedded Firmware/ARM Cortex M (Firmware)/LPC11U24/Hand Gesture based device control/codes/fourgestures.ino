/*****************************************************************************/
//Introduction:this sketch can be used to test gesture recognition.3-Axis Digital 
//   Accelerometer(16g) is in need. Start to test, you should press the button and
//   draw your graphics in the air.Matching results will be seen in serial output.
//   Any problems, please feel free to contact me !
//   now we only support 15 kinds of gestures. It is as follow
//
/*********************************************************************************************************************************************
 *|   0   |   1   |   2	 |   3   |    4   | 	  5   |	6    |    7  |    8  |    9    |    10   |   11  |   12  |   13      |    14   |   15  |*
 *|   *   |   *   |  *   |   *   |  * * * | 	    * |* * *   |*      | *     |* * * *  |  * * * *|    *  |*      |  *      |      *  |      *|*
 *|  ***  |   *   | *    |    *  | * *	  |	    *  |   * *  | *     |* * * *|      *  |  *      |* * * *|*       |* * *     |    * * *|      *|*
 *| * * * | * * * |******|****** |*   *	  |  *   *   |  *   * |  *   *| *    *|      *  |  *      |*   *  |*   * |  *     |      *  |  *   *|*
 *|   *   |  ***  | *    |    *  |     *  |  * *    | *      |   * * |      *|    * * *|* * *    |*      |* * * *|  *      |      *  |* * * *|*
 *|   *   |   *   |  *   |   *   |      * |   * * * |*       |* * *  |      *|      *  |  *      |*      |    *  |  * * * *|* * * *  |  *    |*
 *********************************************************************************************************************************************
//
//  Hardware:3-Axis Digital Accelerometer(16g)
//  Arduino IDE: Arduino-1.0
//  Author:lawliet.zou(lawliet.zou@gmail.com)		
//  Date: Dec 24,2013
//  Version: v1.0
//  by www.seeedstudio.com
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//ge
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
/*******************************************************************************/
#include <gesture.h>
#include <Wire.h>
#include <ADXL345.h>
#include <IRremote.h>

IRsend irsend;

int button = 2;
Gesture gesture;

int gesNum = -1, prevGesNum = -1 ;
int gesRec[4]= {0,0,0,0};
int index = -1;
int txNum = 0;

const int buttonLED = 7;
const int laser = 6;
void setup(){
    Serial.begin(9600);
    pinMode(button,INPUT);
    pinMode(buttonLED, OUTPUT);
    pinMode(laser, OUTPUT);
    gesture.init();
}

void loop(){
    if(HIGH == digitalRead(button)){
        digitalWrite(buttonLED, HIGH);
	delay(200);//debug
	if(!gesture.samplingAccelerateData){       
	    gesture.checkMoveStart();
        }
	if(gesture.samplingAccelerateData){
            if(0 != gesture.getAccelerateData()){
                Serial.print("\r\n get accelerate data error.");
            }
	}
	if(gesture.calculatingAccelerateData)
        {
	    gesture.calculateAccelerateData();
            
            prevGesNum = gesNum;
            gesNum = gesture.getGestureNumber();
           
            if(prevGesNum != gesNum)
            {
                Serial.print("\n gesNum = ");
                Serial.print(gesNum);
                txNum = gesNum + 1; 
                trasmitIR(txNum);
                 prevGesNum = -1;
                 
            }
        }   
          
        
    }
   else
      {     prevGesNum = -1;
            digitalWrite(buttonLED, LOW); 
      }  
}

void trasmitIR(int codeNum)
{    
    laserON();
    switch(codeNum)
    {
        case 1:
         for(int j = 0; j<2; j++ )
                  {
                   for (int i = 0; i < 3; i++) 
                    {
                      irsend.sendSony(0xa90, 12); // Sony TV power code
                     delay(40);
                    }
                  
                    delay(200);
                  }
        break;
        
        case 2:
         for(int j = 0; j<5; j++ )
                  {
                      for (int i = 0; i < 3; i++) 
                        {
                          irsend.sendSony(0xa70, 12); // Sony TV power code
                         
                          delay(40);
                        }
                         
                        // bluetooth.print("80");
                         delay(200);           
                   }
         break;
        
        case 3:
          for(int j = 0; j<5; j++ )
                  {
                      for (int i = 0; i < 3; i++) 
                        {
                          irsend.sendSony(0xa50, 12); // Sony TV power code
                         
                          delay(40);
                        }
                        
                        // bluetooth.print("50");
                         delay(200);        
                  }
        break;
        
        case 4:
         for(int j = 0; j<5; j++ )
                  {
                      for (int i = 0; i < 3; i++) 
                        {
                          irsend.sendSony(0xa30, 12); // Sony TV power code
                         
                          delay(40);
                        }
                         
                        // bluetooth.print("30");
                         delay(200);           
                   }
        break;
        
        default:
        break; //Do nothing
    
    }
    laserOFF();
}
void laserON()
  {
      digitalWrite(laser, HIGH);
      delay(100);
     }
     
void laserOFF()
  {
    delay(200);
    digitalWrite(laser, LOW);
    
  }


