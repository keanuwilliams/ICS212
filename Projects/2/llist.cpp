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
 * FILE:          llist.cpp
 *
 * DESCRIPTION:   the linked list class with the required functions
 *                and data
 *
 ********************************************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <climits>
#include "llist.h"
using namespace std;

/************************************************************************
 *
 * FUNCTION NAME:  readfile
 * 
 * DESCRIPTION:    reads the data from a text file and stores it
 *                 into the linked list
 *
 * PARAMETERS:     -
 *
 * RETURN VALUES:  int - number of records stored in array
 *                 -1  - if the function fails to read the file
 *
 ***********************************************************************/
        
int llist::readfile()
{
    ifstream file(filename); int success = -1; bool exit = false;
    int accno; char name [25]; char address [80];

    #ifdef DEBUG
    cout << "***ENTERING READFILE***\n";
    #endif
    
    if(!file.good() || file.peek() == std::ifstream::traits_type::eof())
    {
        #ifdef DEBUG
        cout << "***FILE DOES NOT EXIST***" << endl;
        #endif
    }
    else
    {
        while(!file.eof() || !exit)
        {
            file >> accno;
            if(accno == -1)
            {
                exit = true;
            }
            file.clear();
            file.ignore(INT_MAX, '\n');
            file.get(name, 25);
            file.clear();
            file.ignore(INT_MAX, '\n');
            file.getline(address, 80, '!');
            file.clear();
            file.ignore(INT_MAX, '\n');
            #ifdef DEBUG
            cout << "***ADDING (1)" << accno << " (2)" << name << " (3)" << address << " TO DATABASE***" << endl;
            #endif
            if(accno != -1)
            {
                addRecord(accno, name, address);
                success++;
                accno = -1;
            }
        }
    }
     
    #ifdef DEBUG
    cout << "***EXITING READFILE***\n";
    #endif

    file.close();
    return success;
}

/************************************************************************
*
* FUNCTION NAME:  writefile
* 
* DESCRIPTION:    writes the data stored in the linked list to
*                 a file 
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
***********************************************************************/
        
void llist::writefile()
{
    ofstream file(filename); record * current = start;

    #ifdef DEBUG
    cout << "***ENTERING WRITEFILE***\n";
    #endif

    if(current == NULL)
    {
        #ifdef DEBUG
        cout << "***NO RECORDS IN DATABASE***" << endl;
        #endif
    }
    else
    {
        while(current != NULL)
        {
            file << current->accountno << "\n" << current->name << "\n" << current->address << "!" << "\n";
            #ifdef DEBUG
            cout << "***ADDING TO FILE (1)" << current->accountno << " (2)" << current->name << " (3)" << current->address << "***" << endl;
            #endif
            current = current->next;
        }
    }
 
    #ifdef DEBUG
    cout << "***EXITING WRITEFILE***\n";
    #endif

    file.close();
} 

/************************************************************************
*
* FUNCTION NAME:  reverse
* 
* DESCRIPTION:    reverses the linked list recursively
*
* PARAMETERS:     start - the start of the list
*
* RETURN VALUES:  the new start of the list
*
***********************************************************************/

record * llist::reverse(record * first)
{
    record * rec = NULL;

    #ifdef DEBUG
    cout << "***ENTERING REVERSE***\n";
    #endif

    if(first == NULL)
    {
        rec = NULL;
    }
    else if(first->next == NULL)
    {
        rec = first;
    }
    else
    {
        rec = reverse(first->next);
        first->next->next = first;
        first->next = NULL;
    }
            
    #ifdef DEBUG
    cout << "***EXITING REVERSE***\n";
    #endif

    return rec;
}

/************************************************************************
*
* FUNCTION NAME:  cleanup
* 
* DESCRIPTION:    accomplishes the necessary deallocation of the
*                 linked list 
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
***********************************************************************/

void llist::cleanup()
{
    record * prev = NULL;

    #ifdef DEBUG
    cout << "***ENTERING CLEANUP***\n";
    #endif
    
    if(start == NULL)
    {
        #ifdef DEBUG
        cout << "***NO RECORDS IN DATABASE***" << endl;
        #endif
    }
    else
    {
        while(start != NULL)
        {
            prev = start;
            start = start->next;
            free(prev);
        }

        start = NULL; prev = NULL;

        #ifdef DEBUG
        cout << "***NO RECORDS IN DATABASE***" << endl;
        #endif
    }
        
    #ifdef DEBUG
    cout << "***EXITING CLEANUP***\n";
    #endif
}
 
/************************************************************************
*
* FUNCTION NAME:  llist
* 
* DESCRIPTION:    constructor for the class
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
***********************************************************************/

llist::llist()
{
    #ifdef DEBUG
    cout << "***ENTERING CONSTRUCTOR LLIST***\n";
    #endif

    start = NULL;
    strcpy(filename, "file.txt");

    #ifdef DEBUG
    cout << "***FILENAME = file.txt***" << endl;
    #endif

    if(readfile() == -1)
    {
        #ifdef DEBUG
        cout << "***UNABLE TO OPEN FILE  " << filename << ". FILE DOES NOT EXIST***\n";
        #endif
    }
    else
    {
        #ifdef DEBUG
        cout << "***FILE " << filename << " SUCCESSFULLY OPENED***\n";
        #endif
    }
            
    #ifdef DEBUG
    cout << "***EXITING CONSTRUCTOR LLIST***\n";
    #endif
}

/************************************************************************
*
* FUNCTION NAME:  llist
* 
* DESCRIPTION:    overloaded constructor for the class which
*                 includes an already created filename (assumes
*                 that filename is a valid .txt file)
*
* PARAMETERS:     char [] - the filename to use (with .txt)
*                 at the end
*
* RETURN VALUES:  -
*
***********************************************************************/
llist::llist(char filename[])
{
    #ifdef DEBUG
    cout << "***ENTERING CONSTRUCTOR LLIST***\n";
    cout << "***(1) " << filename <<"***\n";
    #endif

    #ifdef DEBUG
    cout << "***FILENAME = " << filename << "***" << endl;
    #endif
      
    start = NULL;
    strcpy(this->filename, filename);

    if(readfile() == -1)
    {
        #ifdef DEBUG
        cout << "***UNABLE TO OPEN FILE  " << filename << ". FILE DOES NOT EXIST***\n";
        #endif
    }
    else
    {
        #ifdef DEBUG
        cout << "***FILE " << filename << " SUCCESSFULLY OPENED***\n";
        #endif
    }

    #ifdef DEBUG
    cout << "***EXITING CONSTRUCTOR LLIST***\n";
    #endif
}

/************************************************************************
*
* FUNCTION NAME:  ~llist
* 
* DESCRIPTION:    the destructor for the class
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
***********************************************************************/

llist::~llist()
{
    #ifdef DEBUG
    cout << "***ENTERING DESTRUCTOR LLIST***\n";
    #endif

    writefile();
    cleanup();
            
    #ifdef DEBUG
    cout << "***EXITING DESTRUCTOR LLIST***\n";
    #endif
}

/************************************************************************
*
* FUNCTION NAME:  addRecord 
* 
* DESCRIPTION:    adds a new record to the database
*
* PARAMETERS:     accno - account number to add to account
*                 name - name to be added to account
*                 address - address to be added to account
*
* RETURN VALUES:  int - the account number
*
***********************************************************************/

int llist::addRecord(int accno, char name [], char address [])
{
    record * temp = NULL;
    record * newAccount = new record();
    int valid = 0;

    #ifdef DEBUG
    cout << "***ENTERING ADDRECORD***\n";
    cout << "***(1)" <<  accno << ", (2)" << name << "(3)" << address << "***\n";
    #endif

    temp = start;
    newAccount->accountno = accno;
    strcpy(newAccount->name, name);
    strcpy(newAccount->address, address);
    newAccount->next = NULL;

    if(temp == NULL)
    {
        #ifdef DEBUG
        cout << "***START IS NULL***\n";
        #endif
        start = newAccount;
    }
    else if(temp->accountno > newAccount->accountno)
    {
        #ifdef DEBUG
        cout << "***ADDING TO BEGINNING OF LIST***\n";
        #endif
        newAccount->next = temp;
        start = newAccount;
    }
    else
    {
        while(valid == 0)
        {
            #ifdef DEBUG
            cout << "***FINDING WHERE TO PUT NEW ACCOUNT***\n";
            #endif

            if(newAccount->accountno == temp->accountno)
            {
                #ifdef DEBUG
                cout << "***ACCOUTNOS ARE THE SAME***\n";
                #endif
                newAccount->accountno = ++accno;
            }
            if(temp->next == NULL)
            {
                #ifdef DEBUG
                cout << "***TEMP'S NEXT IS NULL***\n";
                #endif
                temp->next = newAccount;
                valid = 1;
            }
            if(newAccount->accountno > temp->accountno && newAccount->accountno < temp->next->accountno)
            { 
                #ifdef DEBUG
                cout << "***ACCOUTNO IS IN BETWEEN TWO***\n";
                #endif
                newAccount->next = temp->next;
                temp->next = newAccount;
                valid = 1;
            }

            temp = temp->next;
        }
    }
     
    #ifdef DEBUG
    cout << "***EXITING ADDRECORD***\n";
    #endif

    return newAccount->accountno;
}

/************************************************************************
*
* FUNCTION NAME:  printRecord
* 
* DESCRIPTION:    prints the record of given account number
*
* PARAMETERS:     accno - the account number to print
*
* RETURN VALUES:  int - successful (prints the accno)
*                 -1  - no such account
*
***********************************************************************/

int llist::printRecord(int accno)
{
   record * current = start;
   bool found = false;

   #ifdef DEBUG
   cout << "***ENTERING PRINTRECORD***\n";
   cout << "***(1)" << accno <<"***\n";
   #endif
 
   if(start == NULL)
   {
       #ifdef DEBUG
       cout << "--------------------------------------\n"; 
       cout << "***THERE ARE NO RECORDS IN DATABASE***.\n";
       #endif
   }
   while(current != NULL)
   {
       if(current->accountno == accno)
       {
           cout << "--------------------------------------\n";
           cout << "Account No:\n" << current->accountno;
           cout << "\nName:\n" << current->name;
           cout << "\nAddress:\n" << current->address << "\n";
           found = true;
       }

       current = current->next;
   }

   if(!found)
   {
       cout << "--------------------------------------\n"; 
       cout << "Record #" << accno << " was not found.\n";
       accno = -1;
   }
        
   #ifdef DEBUG
   cout << "***EXITING PRINTRECORD***\n";
   #endif

   return accno;
}

/************************************************************************
*
* FUNCTION NAME:  deleteRecord
* 
* DESCRIPTION:    deletes a record from the database
*
* PARAMETERS:     accno - the account number to be deleted
*
* RETURN VALUES:  int - the account number deleted
*                 -1  - not successful
*
***********************************************************************/

int llist::deleteRecord(int accno)
{
    record * prev = NULL; record * temp = start; int success = -1;

    #ifdef DEBUG
    cout << "***ENTERING DELETERECORD***\n";
    cout << "***(1) "<< accno << "***\n";
    #endif

    if(temp == NULL)
    {
        #ifdef DEBUG
        cout << "***NO RECORDS IN THE DATABASE***\n";
        #endif
        success = -1;
    }
    else
    {
        if(temp->accountno == accno)
        {
            prev = temp;
            temp = temp->next;
            free(prev);
            start = temp;
            success = accno;
        }
        else
        {
            prev = temp;
            temp = temp->next;
            while(temp != NULL)
            {
                if(temp->accountno == accno)
                {
                    prev->next = temp->next;
                    free(temp);
                    success = accno;
                }
                prev = temp;
                temp = temp->next;
            }
        }
    }
           
    #ifdef DEBUG
    cout << "***EXITING DELETERECORD***\n";
    #endif

    return success;
}

/************************************************************************
*
* FUNCTION NAME:  printAll or just <<
* 
* DESCRIPTION:    prints all records in database
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
***********************************************************************/

ostream &operator<<(ostream& os, const llist& list)
{
    record * current = list.start;

    #ifdef DEBUG
    cout << "***ENTERING PRINTALLRECORDS***\n";
    #endif

    if(current == NULL)
    {
        os << "--------------------------------------\n"; 
        os << "No records in the database.\n";
    }
    else
    {
        while(current != NULL)
        {
            os << "--------------------------------------\n"; 
            os << "Account No:\n" << current->accountno;
            os << "\nName:\n" << current->name;
            os << "\nAddress:\n" << current->address << "\n";
            current = current->next;
        }

    }
 
    #ifdef DEBUG
    cout << "***EXITING PRINTALLRECORDS***\n";
    #endif
 
    return os;
}

/************************************************************************
*
* FUNCTION NAME:  reverse
* 
* DESCRIPTION:    calls the private reverse function
*
* PARAMETERS:     -
*
* RETURN VALUES:  -
*
***********************************************************************/

void llist::reverse()
{
    #ifdef DEBUG
    cout << "***ENTERING REVERSE***\n";
    #endif
    
    start = reverse(start);
        
    #ifdef DEBUG
    cout << "***EXITING REVERSE***\n";
    #endif
}
