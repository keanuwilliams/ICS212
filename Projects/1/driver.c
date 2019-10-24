/***********************************************************
 *
 * NAME:          Keanu Williams
 * 
 * HOMEWORK:      Project 1
 *
 * CLASS:         ICS 212
 *
 * INSTRUCTOR:    Ravi Narayan
 *
 * DATE:          March 9, 2018
 *
 * FILE:          driver.c
 *
 * DESCRIPTION:   File used to run the program
 *
 **********************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"

int debug = 0;

void interface(int, char * []);

/***********************************************************
 *
 * FUNCTION NAME:  main
 * 
 * DESCRIPTION:    The function used to check if in debug
 *                 mode and to run the user-interface.
 *
 * PARAMETERS:     argc - argument count, the number of 
 *                 strings pointed to argv
 *                 argv - argument vector, the array of 
 *                 arguments
 *
 * RETURN VALUES:  0
 *
 **********************************************************/

int main(int argc, char * argv [])
{
    if (argc == 2)
    {
        if (strncmp(argv[1], "debug", 5) == 0)
        {
            debug = 1;
        }
    }

    interface(argc, argv);

    return 0;
}
