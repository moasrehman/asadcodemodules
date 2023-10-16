/*
  Data types demo for uint32_t and uint8_t.
 */
 
#define SIZE (1000)

int x;
int sensor_data[SIZE];

void setup(){
}

void loop(){
  sensor_data[x] = x;
  x = x<SIZE-1 ? x+1 : 0;
  digitalWrite(LED_BUILTIN,sensor_data[x]);
}
