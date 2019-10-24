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
 * FILE:          ui.c
 *
 * DESCRIPTION:   File contains the user-interaface which
 *                allows the user a menu of choices for a
 *                bank database application.
 *
 **********************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"

extern int debug;

void interface(int, char *[]);
void getaddress(char [], int);
void pCommands();
void clearBuffer();

/***********************************************************
*
* FUNCTION NAME:  getaddress
*
* DESCRIPTION:    function to obtain the address information from the user
*
* PARAMETERS:     x[] - address of the account address to input
*                 z - starting point of the array (zero)
*
* RETURN VALUES:  -
*
**********************************************************/

void getaddress(char x[], int z)
{
    int i = 0;
    char * start = x;

    while (z > 0)
    {
        fgets(x, z, stdin);
        z = z - strlen(x);
        x = &x[strlen(x)];

        while (start[i] != '\0')
	{
            if (start[i] == '\n')
            {
                if (start[i + 1] == '\n')
                {
                     z = 0;
                }
            }

	    i++;

        }
	
        i = 0;

    }

    x[i-2] = '\0';

}

/***********************************************************
*
* FUNCTION NAME:  removeNewLine
*
* DESCRIPTION:    Removes new line character from character array
*
* PARAMETERS:     a - character array address
*
* RETURN VALUES:  -
*
**********************************************************/

void removeNewLine(char * a)
{
    int count = 0;
    char c = a[0];

    while (c != '\0')
    {
        c = a[count];
        if (c == '\n')
        {
            a[count] = '\0';
        }

        count++;

    }

}

/***************************************************************
*
* FUNCTION NAME:  pCommands
*
* DESCRIPTION:    Function to print out user-interface commands
*
* PARAMETERS:     argc - argument count, the number of
*                 strings pointed to argv
*                 argv - argument vector, the array of
*                 arguments
*
* RETURN VALUES:  -
*
**********************************************************/

void pCommands()
{
    printf("\nCommands: \n(1) 'c' to get commands\n(2) 'a' to add a record\n(3) 'd' to delete a record\n(4) 'p' to print a record\n(5) 'pa' to print all records\n(6) 'q' to quit\n\n");
}

/***************************************************************
*
* FUNCTION NAME:  clearBuffer
*
* DESCRIPTION:    clears the buffer
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
**********************************************************/

void clearBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/***************************************************************
 *
 * FUNCTION NAME:  interface
 * 
 * DESCRIPTION:    A user-interface which allows the user a
 *                 menu of choices for a data base application
 *
 * PARAMETERS:     argc - argument count, the number of 
 *                 strings pointed to argv
 *                 argv - argument vector, the array of 
 *                 arguments 
 *
 * RETURN VALUES:  -
 *
 **********************************************************/

void interface(int argc, char * argv [])
{
    char input[12];
    int quit = 0; int quitMenu = 0; int quitSubMenu = 0;
    int accountno; char name[25]; char address[80];

    struct record * start = NULL;

    if(readfile(&start, "file.txt") == -1)
    {
        printf("File not found. New file will be created.\n");
    }
    else
    {
        printf("File Loaded.\n");
    }

    printf("----------Bank Database----------\n");
    if (debug)
    {
        printf("**********DEBUG MODE**********");
    }
        pCommands();

    while (quit != 1)
    {
        printf("Please enter a command: ");
        fgets(input, 10, stdin);

        if (strcmp(input, "c\n") == 0 || strcmp(input, "1\n") == 0)
        {
            printf("------------------------------\n");
            pCommands();
        }
        else if (strcmp(input, "a\n") == 0 || strcmp(input, "2\n") == 0)
        {
            printf("------------------------------\n");
            printf("//Add a Record//\n");

            while (quitMenu != 1)
            {
                printf("Do you want to add a record?\n");
                printf("'y' for yes or 'n' for no: ");
                fgets(input, 10, stdin);

                if (strcmp(input, "n\n") == 0)
                {
                    quitMenu = 1;
                }
                else if (strcmp(input, "y\n") == 0)
                {
                    printf("Please enter an account number: ");
                    scanf("%d", &accountno);
                    clearBuffer();
                    while (accountno < 0)
                    {
                        printf("Error: negative number entered.\n");
                        printf("Please enter a valid account number: ");
                        scanf("%d", &accountno);
                        clearBuffer();
                    }
                    while (quitSubMenu != 1)
                    {
                        printf("Is %d correct?\n", accountno);
                        printf("'y' for yes or 'n' for no: ");
                        fgets(input, 10, stdin);

                        if (strcmp(input, "y\n") == 0)
                        {
                            quitSubMenu = 1;
                        }
                        else if (strcmp(input, "n\n") == 0)
                        {
                            printf("Please enter an account number: ");
                            scanf("%d", &accountno);
                            clearBuffer();
                        }
                        else
                        {
                            printf("Error: invalid command.\n");
                        }
                    }
                    quitSubMenu = 0;
                    printf("Please enter a name: ");
                    fgets(name, 25, stdin);
                    removeNewLine(name);
                    while (quitSubMenu != 1)
                    {
                        printf("Is %s correct?\n", name);
                        printf("'y' for yes or 'n' for no: ");
                        fgets(input, 10, stdin);

                        if (strcmp(input, "y\n") == 0)
                        {
                            quitSubMenu = 1;
                        }
                        else if (strcmp(input, "n\n") == 0)
                        {
                            printf("Please enter a name: ");
                            fgets(name, 25, stdin);
                            removeNewLine(name);
                        }
                        else
                        {
                            printf("Error: invalid command.\n");
                        }
                    }

                    quitSubMenu = 0;
                    printf("(Allowed to use multiple lines//Press enter twice when finished)\nPlease enter an address : ");
                    getaddress(address, 80);
                    while (quitSubMenu != 1)
                    {
                        printf("Is %s correct?\n", address);
                        printf("'y' for yes or 'n' for no: ");
                        fgets(input, 10, stdin);

                        if (strcmp(input, "y\n") == 0)
                        {
                            quitSubMenu = 1;
                        }
                        else if (strcmp(input, "n\n") == 0)
                        {
                            printf("(Allowed to use multiple lines//Press enter twice when finished)\nPlease enter an address : ");
                            getaddress(address, 80);
                        }
                        else
                        {
                            printf("Error: invalid command.\n");
                        }
                    }
                    quitSubMenu = 0;
                    printf("Account #%d successfully added.\n", addRecord(&start, accountno, name, address));
                }
                else
                {
                    printf("Error: invalid command.\n");
                }
            }

            quitMenu = 0; /* reset flag */
        }
        else if (strcmp(input, "d\n") == 0 || strcmp(input, "3\n") == 0)
        {
            printf("------------------------------\n");
            printf("//Delete a Record//\n");

            while (quitMenu != 1)
            {
                printf("Do you want to delete a record?\n");
                printf("'y' for yes or 'n' for no: ");
                fgets(input, 10, stdin);
                if (strcmp(input, "n\n") == 0)
                {
                    quitMenu = 1;
                }
                else if (strcmp(input, "y\n") == 0)
                {
                    printf("Please enter an account number: ");
                    scanf("%d", &accountno);
                    clearBuffer();
                    while (quitSubMenu != 1)
                    {
                        printf("Is %d correct?\n", accountno);
                        printf("'y' for yes or 'n' for no: ");
                        fgets(input, 10, stdin);

                        if (strcmp(input, "y\n") == 0)
                        {
                            quitSubMenu = 1;
                        }
                        else if (strcmp(input, "n\n") == 0)
                        {
                            printf("Please enter an account number: ");
                            scanf("%d", &accountno);
                            clearBuffer();
                        }
                        else
                        {
                            printf("Error: invalid command.\n");
                        }
                    }
                    quitSubMenu = 0;
                    if (deleteRecord(&start, accountno) == -1)
                    {
                        printf("Account #%d not found.\n", accountno);
                    }
                    else
                    {
                        printf("Account #%d was deleted.\n", accountno);
                    }
                }
                else
                {
                    printf("Error: invalid command.\n");
                }
            }

            quitMenu = 0; /* reset flag */
        }
        else if (strcmp(input, "p\n") == 0 || strcmp(input, "4\n") == 0)
        {
            printf("------------------------------\n");
            printf("//Print a Record//\n");

            while (quitMenu != 1)
            {
                printf("Do you want to print a record?\n");
                printf("'y' for yes or 'n' for no: ");
                fgets(input, 10, stdin);
                if (strcmp(input, "n\n") == 0)
                {
                    quitMenu = 1;
                }
                else if (strcmp(input, "y\n") == 0)
                {
                    printf("Please enter an account number: ");
                    scanf("%d", &accountno);
                    clearBuffer();
                    while (quitSubMenu != 1)
                    {
                        printf("Is %d correct?\n", accountno);
                        printf("'y' for yes or 'n' for no: ");
                        fgets(input, 10, stdin);

                        if (strcmp(input, "y\n") == 0)
                        {
                            quitSubMenu = 1;
                        }
                        else if (strcmp(input, "n\n") == 0)
                        {
                            printf("Please enter an account number: ");
                            scanf("%d", &accountno);
                            clearBuffer();
                        }
                        else
                        {
                            printf("Error: invalid command.\n");
                        }
                    }
                    quitSubMenu = 0;
                    if (printRecord(start, accountno) == -1)
                    {
                        printf("Account #%d not found.\n", accountno);
                    }
                    else
                    {
                        printf("Account #%d was printed.\n", accountno);
                    }
                }
                else
                {
                    printf("Error: invalid command.\n");
                }
            }

            quitMenu = 0;
        }
        else if (strcmp(input, "pa\n") == 0 || strcmp(input, "5\n") == 0)
        {
            printf("------------------------------\n");
            printf("//Print All Records//\n");
            printAllRecords(start);
        }
        else if (strcmp(input, "q\n") == 0 || strcmp(input, "6\n") == 0)
        {
            quit = 1;
        }
        else if(strcmp(input, "clear\n") == 0)
        {
            system("clear");
            printf("------------------------------\n");
            pCommands();
        }
        else if(strcmp(input, "DA\n") == 0) /* Secret Function */
        {
            printf("------------------------------\n");
            printf("//Delete All Records//\n");

            while(quitMenu != 1)
            {
                printf("Do you want to delete all records?\n");
                printf("'y' for yes or 'n' for no: ");
                fgets(input, 10, stdin);
                if (strcmp(input, "n\n") == 0)
                {
                    quitMenu = 1;
                }
                else if (strcmp(input, "y\n") == 0)
                {
                    printf("\nPlease type 'DELETE ALL' to confirm: ");
                    fgets(input, 12, stdin);
                    if(strcmp(input, "DELETE ALL\n") == 0)
                    {
                        deleteAllRecords(&start);
                        quitMenu = 1;
                    }
                    else
                    {
                        printf("Failed to delete all records.\n");
                        quitMenu = 1;
                    }
                }
                else
                {
                    printf("Error: invalid command.\n");
                }
            }

            quitMenu = 0;
        }
        else
        {
            printf("Error: invalid command.\n");
        }

        printf("------------------------------\n");
    }

    printf("\nThank you! Have a Good Day!\n\n");

    writefile(start, "file.txt");

}

