#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Timer.h"

/* Access <timer.h> lib to act as clock based time */
void delay(int ms)
{
    clock_t timeDelay = ms + clock();
    while (timeDelay > clock());
}


/* Prints Out Timer */
void printTimer(int hour, int minute)
{
        //system("clear"); // Clears Terminal
        printf("\n        Timer        \n");
        printf("************************\n");
        printf("         %d:%d",hour,minute);
        printf("\n************************\n");
}

/* EOF */

