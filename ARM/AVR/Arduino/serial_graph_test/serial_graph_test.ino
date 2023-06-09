void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
Serial.begin(9600);
}
bool state;
int x, y, z;
// the loop function runs over and over again forever
void loop() {
  x=0;
  for(x= 0; x<500; x++){
  digitalWrite(13, state);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  state = !state;
  y = 10*x;
  z = 20*x;
  serial.println("%d, %d, %d",x, y, z);
  }
  x = 500;
  for(x= 500; x>0; x--){
  digitalWrite(13, state);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  state = !state;
  serial.println("%d, %d, %d",x, y, z);
  }
  // wait for a second
}
