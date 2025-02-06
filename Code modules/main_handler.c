//contain handles for all the functions.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*************************************** 
 * variables used in handler funcion
 * 
 ***************************************/
#define LINE_NB_OF_FILE 69
// static char name_of_file[] = "temperature2.txt";

/*************************************** 
 * prototype declaration of handler functions
 * 
 ***************************************/

/* Read a single value from the text file. */
double read_value_at_line(char*, int);
// int send_http_post(const char *url, const char *);
void create_json_payload(char* , char* , float , float , float , char *);
/* Adds delay in execution of milliseconds. */
void delay_ms(int );
/*Read ISO:8601 format time (Zulu format time)*/
char* get_Zulu_time (char* );

void handler(void)
{
    printf("\nWait 3 seconds...");
    delay_ms(1000);
    printf("\nWait 2 seconds...");
    delay_ms(1000);
    printf("\nWait 1 second...");
    delay_ms(1000);

    double val = 0;
    char* timeinformation[128];

    val = read_value_at_line("temperature2.txt",LINE_NB_OF_FILE); // {OR -->} read_value_at_line(name_of_file, LINE_NB_OF_FILE);
    
    get_Zulu_time(timeinformation); //read zulu time


    printf("\nTime: %s. Read from file: %.02f", timeinformation,val);

    //Alternat usage:
    printf("\nTime: %s. Read from file: %.02f", get_Zulu_time(timeinformation), read_value_at_line("temperature2.txt",LINE_NB_OF_FILE));
    
    }

/***TEST CODE***
 * 
 * static char name_of_file[] = "temperature2.txt";
 * 
 * 
 * //(name_of_file, 10));//(fname, 10));
 * 
 * // char* fname = name_of_file;
 */

int main (void)
{
    handler();

    return 0;
}