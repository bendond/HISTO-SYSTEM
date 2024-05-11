/*
* FILE        Utils.c
* PROJECT     Assignment 5
* PROGRAMMER  Jason Schneider
* DESCRIPTION  This file contains all of the functions that were needed by more than one of the processes in the histo-system
*/

#include "../inc/Utils.h"

/*
* FUNCTION      getRandomCharacter
* PARAMETERS    void
* RETURN        char
* DESCRIPTION   This function gets a random character between A and T
*/
char getRandomCharacter()
{
    return rand() % (ASCII_T - ASCII_A + 1) + ASCII_A;
}



