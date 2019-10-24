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
 * FILE:          dbfunctions.c
 *
 * DESCRIPTION:   Contains all the functions required for 
 *                the database
 *
 **********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

extern int debug;

/*****************************************************************
 *
 * FUNCTION NAME:  addRecord
 * 
 * DESCRIPTION:    adds a new record to the database
 *
 * PARAMETERS:     file - first file in database
 *                 accountno - account number to add to account
 *                 name - name to be added to account
 *                 address - address to be added to account
 *
 * RETURN VALUES:  int - the account number
 *
 ****************************************************************/

int addRecord(struct record ** file, int accountno, char name [], char address [])
{

    struct record * temp;
    struct record * newAccount = (struct record *) malloc(sizeof(struct record));
    int valid = 0;
    
    if (debug)
    {
        printf("*****ENTERING addRecord*****\n");
        printf("*****(1) %d, (2) %s, (3) %s*****\n", accountno, name, address);
    }

    temp = *file;
    newAccount->accountno = accountno;
    strcpy(newAccount->name, name);
    strcpy(newAccount->address, address);
    newAccount->next = NULL;

    if(*file == NULL)
    {
        if(debug)
        {
            printf("*** *file == NULL***\n");
        }
        *file = newAccount;
    }
    else if(temp->accountno > newAccount->accountno)
    {
        if(debug)
        {
            printf("***temp->accountno > newAccount->accountno***\n");
        }
        newAccount->next = temp;
        *file = newAccount;
    }
    else
    {
        while(valid == 0)
        {
            if(newAccount->accountno == temp->accountno)
            {
                if(debug)
                {
                    printf("***newAccount->accountno==temp->accountno***\n");
                }
                newAccount->accountno = ++accountno;
            }
            if(temp->next == NULL)
            {
                if(debug)
                {
                    printf("***temp-> == NULL***\n");
                }
                temp->next = newAccount;
                valid = 1;
            }
            if(newAccount->accountno > temp->accountno && newAccount->accountno < temp->next->accountno)
            {
                if(debug)
                {
                    printf("***THE LONG ONE***\n");
                }
                newAccount->next = temp->next;
                temp->next = newAccount;
                valid = 1;
            }

            temp = temp->next;
        }
    }

    if (debug)
    {
        printf("*****EXITING addRecord*****\n");
    }

    return newAccount->accountno;
}

/***********************************************************
*
* FUNCTION NAME:  deleteRecord
*
* DESCRIPTION:    deletes the record of given account number
*
* PARAMETERS:     file - first file in database
*                 accountno - account number to delete
*
* RETURN VALUES:  int - successful
*                 -1 - no such account
*
**********************************************************/

int deleteRecord(struct record ** file, int accountno)
{
    struct record * prev = NULL;
    struct record * temp = *file;
    int success = -1;

    if (debug)
    {
        printf("*****ENTERING deleteRecord*****\n");
        printf("*****(1) %d*****\n", accountno);
    } 

    if(temp == NULL)
    {
        success = -1;
    }
    else
    {
        if(temp->accountno == accountno)
        {
            prev = temp;
            temp = temp->next;
            free(prev);
            *file = temp;
            success = accountno;
        }
        else
        {
            prev = temp;
            temp = temp->next;
            while(temp != NULL)
            {
                if(temp->accountno == accountno)
                {
                    prev->next = temp->next;
                    free(temp);
                    success = accountno;
                }
                prev = temp;
                temp = temp->next;
            }
        }
    }

    if (debug)
    {
        printf("*****EXITING deleteRecord*****\n");
    }

    return success;
}

/***********************************************************
*
* FUNCTION NAME:  deleteAllRecords
*
* DESCRIPTION:    deletes all the records in the list
*                 (this function is not listed on the
*                 command list, but can be accessed using
*                 'DA' command)
*
* PARAMETERS:     file - first file in database
*
* RETURN VALUES:  -
*
**********************************************************/

void deleteAllRecords(struct record ** file)
{
    struct record * current = *file;

    if (debug)
    {
        printf("*****ENTERING deleteAllRecords*****\n");
    }
 
    if(current == NULL)
    {
        if(debug)
        {
            printf("***LIST IS EMPTY***\n");
        }
        printf("There are no records to delete.\n");

    }
    else
    {
        while(current != NULL)
        {
            deleteRecord(file, current->accountno);
            current = *file;
        }
    
        *file = NULL;

        printf("All records were deleted.\n");
    
    }
    
    if (debug)
    {
        printf("*****EXITING deleteAllRecords*****\n");
    }

}


/***********************************************************
*
* FUNCTION NAME:  printRecord
*
* DESCRIPTION:    prints the record of given account number
*
* PARAMETERS:     file - first file in database
*                 accountno - account number to print
*
* RETURN VALUES:  int - successful
*                 -1 - no such account
*
**********************************************************/

int printRecord(struct record * file, int accountno)
{
     struct record * current = file;
     int found = 0;
     
     if (debug)
     {
          printf("*****ENTERING printRecord*****\n");
          printf("*****(1) %d*****\n", accountno);
     }

     if(current == NULL)
     {
         printf("There are no records to print.\n");
         accountno = -1;
     }

     while(current != NULL)
     {
         if(current->accountno == accountno)
         {
             printf("------------------------------\n");
             printf("Account Number: \n%d\n", current->accountno);
             printf("Name: \n%s\n", current->name);
             printf("Address: \n%s\n", current->address);
             printf("------------------------------\n");
             found = 1;
         }

         current = current->next;
     }

     if(found == 0)
     {
         accountno = -1;
     }

     if (debug)
     {
          printf("*****EXITING printRecord*****\n");
     }

     return accountno;
}

/***********************************************************
*
* FUNCTION NAME:  printAllRecords
*
* DESCRIPTION:    prints all records in database
*
* PARAMETERS:     file - first file in database
*
* RETURN VALUES:  -
*
**********************************************************/

void printAllRecords(struct record * file)
{
     struct record * current = file;
     
     if (debug)
     {
         printf("*****ENTERING printAllRecords*****\n");
     }

     if(current == NULL)
     {
         if(debug)
         {
             printf("***LIST IS EMPTY***\n");
         }
         printf("There are no records to print.\n");

     }

     while(current != NULL)
     {
         printf("------------------------------\n");
         printf("Account Number: \n%d\n", current->accountno);
         printf("Name: \n%s\n", current->name);
         printf("Address: \n%s\n", current->address);
         printf("------------------------------\n");
         current = current->next;   
     }

     if (debug)
     {
         printf("*****EXITING printAllRecord*****\n");
     }

}

/***********************************************************
*
* FUNCTION NAME:  readfile
*
* DESCRIPTION:    reads the data from a text file and
*                 stores it in linked list
*
* PARAMETERS:     start - first file in database
*                 filename - name of the file to read from
*
* RETURN VALUES:  int - number of records stored in array
*                  -1 - if the function fails to read a 
*                       file
*
**********************************************************/

int readfile(struct record ** start, char filename[])
{
    FILE * file = NULL; int i = 0; int z = 0;
    int accountno; char name [25]; char address [80];
    int success = -1; int stop = 0; int len;

    if(debug)
    {
        printf("****ENTERING readfile****\n");
        printf("*****(1) %s*****\n", filename);
    }

    file = fopen(filename, "r");

    if(file)
    {
        success = 0;
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        fclose(file);
        file = fopen(filename, "r");
        if(!(len > 0))
        {
            if(debug)
            {
                printf("***FILE IS EMPTY***\n");
            }
        }
        else
        {
            while(!feof(file))
            {
                fscanf(file, "%d\n", &accountno);
                fgets(name, 25, file);
                removeNewLine(name);
                i = 0; z = 80;
                while(!stop)
                {
                    fgets(&address[i], z, file);
                    if(!(z > 0))
                    {
                        stop = 1;
                    }
                    if(address[i] == '\n')
                    {
                        if(address[i-1] == '\n')
                        {
                            stop = 1;
                        }
                    }
                    i = strlen(address);
                    z = z - i;
                }
                stop = 0;
                if(address[strlen(address)-2] == '\n')
                {
                    address[strlen(address)-2] = '\0';
                }
                else
                {
                    address[strlen(address)-1] = '\0';
                }
                if(debug)
                {
                    printf("***ADDING (1)%d (2)%s (3)%s TO RECORD\n", accountno, name, address);
                }
                addRecord(start, accountno, name, address);
                success++;
            }
        }

        fclose(file);
    }

    if(debug)
    {
        printf("****EXITING readfile****\n");
    }

    return success;
}

/***********************************************************
*
* FUNCTION NAME:  writefile
*
* DESCRIPTION:    writes the data stored in the list into
*                 a file
*
* PARAMETERS:     start - first file in database
*                 filename - file to be written to
*
* RETURN VALUES:  -
*
**********************************************************/
void writefile(struct record * start, char filename [])
{
    FILE * file = NULL;
    file = fopen(filename, "w+");

    if (debug)
    {
        printf("*****ENTERING writefile*****\n");
        printf("*****(1) %s*****\n", filename);
        if(start == NULL)
        {
            printf("***START RECORD IS NULL***\n");
        }
    }

    while(start != NULL)
    {
        if(start->next == NULL)
        {
            if(debug)
            {
                printf("***ADDING (1)%d (2)%s (3)%s TO FILE***\n", start->accountno, start->name, start->address);
            }
            fprintf(file, "%d\n%s\n%s\n", start->accountno, start->name, start->address);
            start = start->next;
        }
        else
        {
            if(debug)
            {
                printf("***ADDING (1)%d (2)%s (3)%s TO FILE***\n", start->accountno, start->name, start->address);
            }
            fprintf(file, "%d\n%s\n%s\n\n", start->accountno, start->name, start->address);
            start = start->next;
        }
    }

    if (debug)
    {
        printf("*****EXITING writefile*****\n");
    }
}
