/*
  Blink Float vs FixedPoints Benchmark
  Changes the state of an LED and performs 
  thousands of fractional calculations
  repeatedly.
 */
#include <FixedPoints.h>
#include <FixedPointsCommon.h>

#define USE_FIXED_POINT
#define MEASURE

#define MASK(x) ((unsigned char)(1<<(x)))

#ifdef USE_FIXED_POINT
  SQ7x8 a, b, c;
#else
  volatile float a, b, c;
#endif

#ifdef MEASURE
uint32_t StartTime, CurrentTime;
#endif

void setup() {                
  DDRB |= MASK(5);   // The LED pin is output. Mask: 00100000  
  Serial.begin(9600);  
  a=2.5;
  b=2.9;
  c=1.1;
}

void loop() {
  PORTB ^= MASK(5);  // Toggle LED 
  uint32_t i = 30000;
  
  #ifdef MEASURE
    StartTime = millis();
  #endif
  
  while (i--){
    a = (a*c+b*c-b/c)*c;
    if(a > 100)
      a = a/10;
    //Serial.println((float)a,3);
    //delay(300);  
  }  

  #ifdef MEASURE
    CurrentTime = millis();
    Serial.print("Took ");
    Serial.print((float)(CurrentTime - StartTime)*0.001,3);
    Serial.print(" seconds\n");
  #endif
}
