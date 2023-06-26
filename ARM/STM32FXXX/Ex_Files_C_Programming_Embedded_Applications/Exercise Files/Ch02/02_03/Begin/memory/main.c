#include <stdint.h>

#define SIZE (4000)

int x;
int sensor_data[SIZE];


int main(){

	for(x=0; x<SIZE; x++)
	  sensor_data[x] = x;
	
	while(1);
	return 0;
}


void SystemInit(){}
