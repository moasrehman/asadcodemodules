/*
  Runtime Library Float vs Floating Point Unit Benchmark
  Changes the state of a variable and performs 
  thousands of fractional calculations repeatedly.
 */
#include <stdint.h>
#include <math.h>
//#include "stm32f3xx.h"
#include "stm32f1xx.h"

#define MEASURE

#define MASK(x) ((unsigned char)(1<<(x)))

volatile float a, b, c;

#ifdef MEASURE
  volatile uint8_t computing = 0;
#endif

int main() {
  a = 2.5f;
  b = 2.9f;
  c = 1.1f;
  
  while(1){
    uint32_t i = 30000;
    
    #ifdef MEASURE
      computing = 1;
    #endif
    
    while (i--){
      a = (a*c+b*c-b/c)*c;
      if(a > 100)
        a = a/10;
    }  
    #ifdef MEASURE
      computing = 0;
    #endif
  }
}


void SystemInit(){ 
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  
  #endif
}
