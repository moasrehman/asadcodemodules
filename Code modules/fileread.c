/* Reads text from text files*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//read a line from text file
char read_line(char given_file_name)
{
    return given_file_name;
}

//read a single value from the text file
double read_value_at_line(char* filename, int linecount)
{   
    FILE* file = fopen ((char*)filename, "r");
    double i = 0;

    for (int p=0; p<linecount; p++)
    {
        int k =0;
        
        fscanf (file, "%d", &k);
        
        i = k; //convert value to double from integer
    }
    fclose (file);

    return i;
}