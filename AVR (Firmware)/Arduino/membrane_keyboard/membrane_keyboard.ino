/*
Description:
sample code for Sealed membrane 4*4 nutton pad with sticker, it outputs the ASCII code for keys on the pad.
The general working principle of this key pad is a 4*4 matrix. The sample code scans the 4*4 matrix in a short time
and determines whether there is a signal input( pression on the keypad).
Before reading this sample code, you'd better have a look at the sample connection pic. You may wonder why there are
four resistors. This is because that if there are no such resistors, the data analogRead() gets will be a stochastic value
between 0-1023. It will be impossible to determine whethaer the connection is made by pressing the button on the key pad.  
*/
//Author: Sheng Kaiyu from DFrobot
//Editor: Michael from DFrobot
//Date: 2012/02/23
// Arduino 1.0 or lower
void setup()
{
  DDRD=240;           //binary 11110000, set the digital I/O pin 7-4 as output 
  Serial.begin(9600); // use serial monitor to view the input
  Serial.println("Program Start");
}

unsigned char outputchar(int i, int j)   // output chars on the pad
{
  Serial.println("In output char");
  if (i==0)
  { switch (j)
    {case 0:
           return '1'; break;
     case 1:
           return '2'; break;
     case 2:
           return '3'; break;
     case 3:
           return 'A'; break;
    }
  }
   if (i==1)
  { switch (j)
    {case 0:
           return '4'; break;
     case 1:
           return '5'; break;
     case 2:
           return '6'; break;
     case 3:
           return 'B'; break;
    }
  }
   if (i==2)
  { switch (j)
    {case 0:
           return '7'; break;
     case 1:
           return '8'; break;
     case 2:
           return '9'; break;
     case 3:
           return 'C'; break;
    }
  }
   if (i==3)
  { switch (j)
    {case 0:
           return '*'; break;
     case 1:
           return '0'; break;
     case 2:
           return '#'; break;
     case 3:
           return 'D'; break;
    }
  }
}
unsigned int getC()                   //determine whether there is 5V input on the analog pins 3-0
{
  Serial.println("In getC");
  if (analogRead(3)>512)              // binary 1000, pin 3 has a 5V input
  {   
    return 0x8;                       
  }
  else if (analogRead(2)>512)         // binary 0100, pin 2 has a 5V input
  {
    return 0x4;
  }
  else if (analogRead(1)>512)         // binary 0010, pin 1 has a 5V input
  {
    return 0x2;
  }
  else if (analogRead(0)>512)         // binary 0001, pin 0 has a 5V input
  {
    return 0x1;
  }
  else                                // binary 0000, no pin has 5V input, namely no button is pressed
  {
    return 0x0;
  }
}
unsigned char readdata(void)          //main function
{
  Serial.println("In readdata");
  PORTD=128;                          //binary 10000000, set pin 7 HIGH
  for (int i=0;i<4;i++)               //for loop
  {
    unsigned int temp=0x8;            //temporary integer, binary 1000, to compare with getC() function and determine pression 
    for (int j=0;j<4;j++)
      {  
         if (getC()==temp)
         { return outputchar(i,j);}   // output the char
         temp=temp>>1 ;               // shift right
      }
   PORTD=PORTD>>1;                    //shift right, set the next pin HIGH, set previous one LOW
  }
  return 'E';                         // if no button is pressed, return E
}
int p;
void loop()
{ 
  Serial.println("In loop");
  unsigned char key;  
  do                                  // read and output once until the next pression
  {
    Serial.print("In do time nb:");
    Serial.println(p);
    p++;
    key=readdata();
    if  (key!='E')                 
    {Serial.println(key);} 
    delay(200); 
    while (readdata()==key)
    {}
  }
  while (key!='E'); 
}


