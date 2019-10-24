/***********************************************************
 *
 * NAME:          Keanu Williams
 * 
 * HOMEWORK:      Homework 3b
 *
 * CLASS:         ICS 212
 *
 * INSTRUCTOR:    Ravi Narayan
 *
 * DATE:          March 9, 2018
 *
 * FILE:          record.h
 *
 * DESCRIPTION:   Has the definition of the record structure and contains
 *                all the header files for the database functions
 *
 **********************************************************/

struct record
{
    int                 accountno;
    char                name[25];
    char                address[80];
    struct record *     next;
};

void removeNewLine(char *);
int addRecord(struct record **, int, char [], char []);
int printRecord(struct record *, int);
void printAllRecords(struct record *);
int deleteRecord(struct record **, int);
void deleteAllRecords(struct record **);
int readfile(struct record **, char []);
void writefile(struct record *, char []);
