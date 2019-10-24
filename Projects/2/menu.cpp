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
 * FILE:          menu.cpp
 *
 * DESCRIPTION:   contains the user-interface
 *
 ********************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <climits>
#include <string.h>
#include "menu.h"
#include "llist.h"
using namespace std;

void printCommands();
void addSubMenu(llist &);
void printSubMenu(llist &);
void deleteSubMenu(llist &);
bool confirm();

/********************************************************************************
 *
 * FUNCTION NAME:  interface
 * 
 * DESCRIPTION:    the user-interface of the bank database
 *
 * PARAMETERS:     - 
 *
 * RETURN VALUES:  -
 *
 *******************************************************************************/

void interface()
{
    bool quit = false; bool reversed = false; // checks if user reversed list 
    char input[12]; 

    llist * database = new llist();

    cout << "--------------------------------------\n";
    cout << "-----Welcome to the Bank Database-----\n";
#ifdef DEBUG    
    cout << "***DEBUG MODE ON***\n";
#endif
    printCommands();
    cout << "--------------------------------------\n";

    while(!quit)
    {
        cout << "~ ";
        cin.get(input, 12);
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if(strcmp(input, "q") == 0 || strcmp(input, "7") == 0 || strcmp(input, "quit") == 0)
        {
            cout << "--------------------------------------\n";
            cout << "Are you sure?" << endl;
            if(confirm())
            {
                quit = true;
            }
            cout << "--------------------------------------\n";
        }
        else if(strcmp(input, "r") == 0 || strcmp(input, "6") == 0 || strcmp(input, "reverse") == 0)
        {
            cout << "--------------------------------------\n";
            cout << "        ||Reverse Record Order||\n";
            cout << "--------------------------------------\n";

            database->reverse();
            
            if(reversed)
            {
                cout << "Unreversed the records.\n";
                reversed = false;
            }
            else
            {
                cout << "Reversed the records.\n";
                reversed = true;
            }
            cout << "--------------------------------------\n";
        }
        else if(strcmp(input, "a") == 0 || strcmp(input, "2") == 0 || strcmp(input, "add") == 0)
        {
            if(reversed)
            {
                cout << "ERROR: records are reversed.\nPlease reverse the records again to continue.\n";
                cout << "--------------------------------------\n";
            }
            else
            {
                addSubMenu(*database);
            }
        }
        else if(strcmp(input, "d") == 0 || strcmp(input, "3") == 0 || strcmp(input, "delete") == 0)
        {
            deleteSubMenu(*database);
        }
        else if(strcmp(input, "p") == 0 || strcmp(input, "4") == 0 || strcmp(input, "print") == 0)
        {
            printSubMenu(*database);
        }
        else if(strcmp(input, "pa") == 0 || strcmp(input, "5") == 0 || strcmp(input, "print all") == 0)
        {
            cout << "--------------------------------------\n";
            cout << "         ||Print All Records||\n";
            cout << "--------------------------------------\n";
            cout << *database;
            cout << "--------------------------------------\n";
        }
        else if(strcmp(input, "c") == 0 || strcmp(input, "1") == 0 || strcmp(input, "clear") == 0)
        {
            system("clear");
            #ifdef DEBUG    
            cout << "***DEBUG MODE ON***\n";
            #endif
            printCommands(); 
            cout << "--------------------------------------\n";
        }
        else
        {
            cout << "ERROR: invalid input.\n";
        }
    }

    delete database;
    cout << "Thank you! Have a good day!\n";
}

/********************************************************************************
 *
 * FUNCTION NAME:  printCommands
 * 
 * DESCRIPTION:    prints the list of commands
 *
 * PARAMETERS:     -
 *
 * RETURN VALUES:  -
 *
 *******************************************************************************/

void printCommands()
{
    cout << "--------------------------------------\n";
    cout << "            ||Commands||\n";
    cout << "--------------------------------------\n";
    cout << "(1) 'c' to clear and get commands\n(2) 'a' to add a record\n(3) 'd' to delete a record\n(4) 'p' to print a record\n(5) 'pa' to print all records\n(6) 'r' to reverse record order\n(7) 'q' to quit\n";
}

/********************************************************************************
 *
 * FUNCTION NAME:  addSubMenu
 * 
 * DESCRIPTION:    obtains the needed information to add a record then
 *                 adds the record
 *
 * PARAMETERS:     list - the linked list to add to
 *
 * RETURN VALUES:  -
 *
 *******************************************************************************/

void addSubMenu(llist & list)
{
    int accno = -1; char name [25]; char address [80]; 
    bool quitMenu = false;

    cout << "--------------------------------------\n";
    cout << "           ||Add a Record||\n";
    cout << "--------------------------------------\n";
    cout << "Do you want to add a record?\n";
    if(confirm())
    {
        do // get account number
        {
            cout << "Please enter an account number (greater than zero).\n~ ";
            cin >> accno;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if(accno <= 0)
            {
                cout << "ERROR: invalid number entered.\n";
            }
            else
            {
                cout << "Is " << accno << " correct?\n";
                if(confirm())
                {
                    quitMenu = true;
                }
                else
                {
                    quitMenu = false;
                }
            }
        } while(!quitMenu);
        
        do // get name
        {
            cout << "Please enter a name for the account.\n~ ";
            cin.get(name, 25);
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Is " << name << " correct?\n";
            if(confirm())
            {
                quitMenu = true;
            }
            else
            {
                quitMenu = false;
            }
        } while(!quitMenu);
        
        do // get address
        {
            cout << "Please enter an address for the account. (Allowed to use multiple lines).\n";
            cout << "When finished you are finished, put a '!' at the end.\n~ ";
            cin.getline(address, 80, '!');
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Is " << address << " correct?\n";
            if(confirm())
            {
                quitMenu = true;
            }
            else
            {
                quitMenu = false;
            }
        } while(!quitMenu); 

        do // final confirmation
        {
            cout << "--------------------------------------\n";
            cout << "AccountNo:\n" << accno << "\nName:\n" << name << "\nAddress:\n" << address;
            cout << "\n--------------------------------------\n";
            cout << "Do you want to add this record to the database?\n";
            if(confirm())
            {
                cout << "Record #" << list.addRecord(accno, name, address) << " was successfully added.\n";
                quitMenu = true;
            }
            else
            {
                cout << "Are you sure?\n";
                if(confirm())
                {
                    cout << "Record #" << accno << " was not added.\n";
                    quitMenu = true;
                }
                else
                {
                    quitMenu = false;
                }
            }
        } while(!quitMenu);
    }
    cout << "--------------------------------------\n";
}

/********************************************************************************
 *
 * FUNCTION NAME:  printSubMenu
 * 
 * DESCRIPTION:    obtains the needed information to print a record
 *                 then prints the record
 *
 * PARAMETERS:     list - the linked list to print from
 *
 * RETURN VALUES:  -
 *
 *******************************************************************************/

void printSubMenu(llist & list)
{
    cout << "--------------------------------------\n";
    cout << "          ||Print a Record||\n";
    cout << "--------------------------------------\n";
    cout << "Do you want to print a record?\n";

    if(confirm())
    {
        int accno = -1; bool quitMenu = false;

        do // get account number
        {
            cout << "Please enter an account number (greater than 0).\n~ ";
            cin >> accno;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if(accno <= 0)
            {
                cout << "ERROR: invalid number entered.\n";
            }
            else
            {
                cout << "Is " << accno << " correct?\n";
                if(confirm())
                {
                    quitMenu = true;
                }
                else
                {
                    quitMenu = false;
                }
            }
        } while(!quitMenu);
        
       list.printRecord(accno);

    }
    
    cout << "--------------------------------------\n";
}

/********************************************************************************
 *
 * FUNCTION NAME:  deleteSubMenu
 * 
 * DESCRIPTION:    obtains the needed information to delete a record
 *                 then attempts to delete the record
 *
 * PARAMETERS:     list - the linked list to delete from
 *
 * RETURN VALUES:  -
 *
 *******************************************************************************/

void deleteSubMenu(llist & list)
{
    int accno = -1; int wasPrinted = 0;
    bool quitMenu = false;

    cout << "--------------------------------------\n";
    cout << "          ||Delete a Record||\n";
    cout << "--------------------------------------\n";
    cout << "Do you want to delete a record?\n";

    if(confirm())
    {
        do // get account number
        {
            cout << "Please enter an account number (greater than 0).\n~ ";
            cin >> accno;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            if(accno <= 0)
            {
                cout << "ERROR: invalid number entered.\n";
            }
            else
            {
                cout << "Is " << accno << " correct?\n";
                if(confirm())
                {
                    quitMenu = true;
                }
                else
                {
                    quitMenu = false;
                }
            }
        } while(!quitMenu);

        wasPrinted = list.printRecord(accno);

        if(wasPrinted != -1)
        {
            cout << "--------------------------------------\n";
            cout << "Are you sure you want to delete Record #" << accno << "?\n";
            if(confirm())
            {
                list.deleteRecord(accno);
                cout << "Record #" << accno << " was removed from the database.\n";
            }
            else
            {
                cout << "Record #" << accno << " was not removed from the database.\n";
            }
        }

    }

    cout << "--------------------------------------\n";
}

/********************************************************************************
 *
 * FUNCTION NAME:  confirm
 * 
 * DESCRIPTION:    asks the user if what was said before this is
 *                 correct
 *
 * PARAMETERS:     -
 *
 * RETURN VALUES:  true  - if the response is yes
 *                 false - if the response is no
 *
 *******************************************************************************/
bool confirm()
{
    char input [5]; bool answer = false; bool valid = false;

    while(!valid)
    { 
        cout << "'y' for yes or 'n' for no\n~ ";
        cin.get(input, 5);
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if(strcmp(input, "y") == 0)
        {
            answer = true;
            valid = true;
        }
        else if(strcmp(input, "n") == 0)
        {
            answer = false;
            valid = true;
        }
        else
        {
            cout << "ERROR: invalid input.\n";
        }
    }

    return answer;
}
