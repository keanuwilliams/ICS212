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
 * FILE:          record.h
 *
 * DESCRIPTION:   contains the definition of the record structure
 *
 **********************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                 accountno;
    char                name[25];
    char                address[80];
    struct record *     next;
};

#endif
