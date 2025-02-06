//Reads time and does time related tasks

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Adds delay in execution of milliseconds.
void delay_ms(int number_of_milliseconds)
{
    // Converting time into milli_seconds
    //int milli_seconds = 1000 * number_of_milliseconds;
    
    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + number_of_milliseconds)
        ;
}

//Read ISO:8601 format time (Zulu format time)
char* get_Zulu_time (char* timestring)
{
    time_t anytime;
    struct tm *current;

    time(&anytime);
    current = localtime(&anytime);
    strftime(timestring, 128, "%Y-%m-%dT%H:%M:%SZ", current);

    return (char*)timestring;
}