/*
  Blink:
  Blinks an LED by bit masking.
  The on-board LED on the Arduino UNO is at PortB 5.
 */

#define MASK(x) ((unsigned char) (1<<(x)))

void setup(){                
  DDRB |= MASK(5);   // The LED pin is output. Mask: 00100000
}
  
void loop(){
  PORTB |= MASK(5);  // Turn LED on
  delay(500);
  PORTB &= ~MASK(5); // Turn LED off
  delay(500);
}
