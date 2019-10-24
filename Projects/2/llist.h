/***********************************************************
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
 * FILE:          llist.h
 *
 * DESCRIPTION:   contains the functions and data for the
 *                linked list class
 *
 **********************************************************/

#ifndef LLIST_H
#define LLIST_H

#include "record.h"
#include <iostream>

class llist
{
    private:
        record * start;
        char filename[16];
        int readfile();
        void writefile();
        record * reverse (record *);
        void cleanup();
    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char[], char[]);
        int printRecord(int);
        int deleteRecord(int);
        friend std::ostream &operator<<(std::ostream&, const llist&);
        void reverse();
};

#endif
