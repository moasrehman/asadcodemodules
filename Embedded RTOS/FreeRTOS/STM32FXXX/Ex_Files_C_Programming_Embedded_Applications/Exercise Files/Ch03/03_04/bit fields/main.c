#include <stdint.h>


/* Special Register Type Definition */
typedef union {
  uint8_t Byte;
  struct {
    uint8_t PS0       :1;  // Prescale Divisor Select Bit 0 
    uint8_t PS1       :1;  // Prescale Divisor Select Bit 1 
    uint8_t PS2       :1;  // Prescale Divisor Select Bit 2 
    uint8_t CLKSA     :1;  // Clock Source Select A 
    uint8_t CLKSB     :1;  // Clock Source Select B 
    uint8_t CPWMS     :1;  // Center-Aligned PWM Select 
    uint8_t TOIE      :1;  // Timer Overflow Interrupt Enable 
    uint8_t TOF       :1;  // Timer Overflow Flag 
  } Bits;
  struct {
    uint8_t PS        :3;
    uint8_t CLKS      :2;
    uint8_t           :3;
  } MergedBits;
} MultiFieldByte;

MultiFieldByte reg;
uint32_t x;

int main(){
	for(x=0; x<10; x++)
	  reg.Bits.CPWMS = 1;
	while(1);
	return 0;
}


void SystemInit(){}
