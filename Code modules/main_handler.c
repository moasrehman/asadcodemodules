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
double read_value_at_line(char*, int);
// int send_http_post(const char *url, const char *);
void create_json_payload(char* , char* , float , float , float , char *);
void delay_ms(int );
void get_Zulu_time (char* );

void handler(void)
{
    double val = 0;
    val = read_value_at_line("temperature2.txt",LINE_NB_OF_FILE); // {OR -->} read_value_at_line(name_of_file, LINE_NB_OF_FILE);
    
    printf("\nRead from file: %.02f",val);
    
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