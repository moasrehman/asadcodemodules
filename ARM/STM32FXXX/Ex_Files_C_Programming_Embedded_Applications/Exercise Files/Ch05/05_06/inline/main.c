/*
  Regular Functions vs Inline Functions Benchmark
  Changes the state of a variable and performs 
  thousands of fractional calculations repeatedly.
 */
#include <stdint.h>
#include "stm32f3xx.h"

#define MEASURE

#define MASK(x) ((unsigned char)(1<<(x)))

volatile uint32_t a, b, c;

uint32_t wsum(uint32_t x, uint32_t y)__attribute__((always_inline));

uint32_t wsum(uint32_t x, uint32_t y){
  return (2 * x - y);
}

#ifdef MEASURE
  volatile uint8_t computing = 0;
#endif

int main() {
  a = 10;
  b = 20;
  c = 30;
  
  while(1){
    uint32_t i = 30000;
    
    #ifdef MEASURE
      computing = 1;
    #endif
    
    while (i--){
      a = wsum(b,c);
      b = wsum(a,10);
      c = wsum(b,100);
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
