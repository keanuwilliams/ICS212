/*********************************************************************************
 *
 * NAME:          Keanu Williams
 * 
 * HOMEWORK:      Project 2
 *
 * CLASS:         ICS 212
 *
 * INSTRUCTOR:    Ravi Narayan
 *
 * DATE:          April 27, 2018
 *
 * FILE:          driver.cpp
 *
 * DESCRIPTION:   driver that calls the user-interface
 *
 ********************************************************************************/

#include <iostream>
#include "menu.h"
using namespace std;

/********************************************************************************
 *
 * FUNCTION NAME:  main
 * 
 * DESCRIPTION:    simply calls the user-interface     
 *
 * PARAMETERS:     argc - argument count, the number of strings pointed to argv
 *                 argv - argument vector, the array of arguments 
 *
 * RETURN VALUES:  0
 *
 *******************************************************************************/

int main(int argc, char * argv [])
{
    interface(); // the user-interface
    return 0;
}

