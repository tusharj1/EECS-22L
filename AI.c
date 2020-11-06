#include <stdio.h>
#include <stdlib.h>

#include "AI.h"

void aifunction(PIECE *Board[8][8], int color, int *level, int *oldx, int *oldy, int *newx, int *newy, int aifail) {
    static int aicountw = 0;
    static int aicountb = 0;
    static int failcount1 = 0;
    static int failcount2 = 0;
    char oldletter, newletter;
    int oldnumber, newnumber;
    PIECE *pieces[16];
    int piececount = 0;
    int num1, num2, num3;
    PIECE *king;
    int kingcanmove = 0;
    int capturemovesold[218][2];
    int capturemovesnew[218][2];
    int capturetype[218];
    int cmcounter = 0;

    if (aifail == 0) {
        failcount1 = 0;
    }

    // White Movelist
    char oldcw[100] = {'e','f','d','h','c', 'a','c','b','e','h', 'g', 'a','c','b','e','h', 'e', 'a','c','b','f','g','g', 'b', 'a','c','c','f','g','g','d', 'b', 'a','a','c','f','g','g','b','b', 'c', 'a','a','f','g','g','b','b','b','d', 'd', 'a','a','f','g','g','b','b','b','e', 'a', 'd','a','f','g','g','b','b','b','e', 'e','X'};
    int oldnw[100] =  { 2 , 1 , 1 , 5 , 4 ,  1 , 1 , 1 , 1 , 1 ,  1 ,  1 , 1 , 1 , 1 , 1 ,  1 ,  1 , 1 , 1 , 1 , 1 , 1 ,  1 ,  1 , 1 , 1 , 1 , 1 , 1 , 2 ,  2 ,  1 , 2 , 1 , 1 , 1 , 1 , 3 , 3 ,  1 ,  1 , 2 , 1 , 1 , 1 , 3 , 3 , 2 , 2 ,  2 ,  1 , 2 , 1 , 1 , 1 , 3 , 3 , 2 , 3 ,  1 ,  1 , 2 , 1 , 1 , 1 , 3 , 3 , 2 , 3 ,  2 , 9};
    char newcw[100] = {'e','c','h','f','b', 'a','b','d','f','h', 'e', 'a','b','d','f','h', 'g', 'a','b','d','f','g','h', 'c', 'a','b','d','f','g','h','c', 'b', 'a','b','d','f','g','h','a','c', 'b', 'a','b','f','g','h','a','c','c','e', 'd', 'a','b','f','g','h','a','c','c','d', 'd', 'd','b','f','g','h','a','c','c','d', 'f','X'};
    int newnw[100] =  { 3 , 4 , 5 , 7 , 5 ,  2 , 2 , 2 , 2 , 2 ,  2 ,  2 , 2 , 2 , 2 , 2 ,  1 ,  2 , 2 , 2 , 2 , 2 , 2 ,  3 ,  2 , 2 , 2 , 2 , 2 , 2 , 3 ,  3 ,  2 , 3 , 2 , 2 , 2 , 2 , 4 , 4 ,  2 ,  2 , 3 , 2 , 2 , 2 , 4 , 4 , 3 , 3 ,  4 ,  2 , 3 , 2 , 2 , 2 , 4 , 4 , 3 , 4 ,  1 ,  4 , 3 , 2 , 2 , 2 , 4 , 4 , 3 , 4 ,  4 , 9};

    // Black Movelist
    char oldcb[100] = {'e','f','d','h','c', 'a','c','b','e','h', 'g', 'a','c','b','e','h', 'e', 'a','c','b','f','g','g', 'b', 'a','c','c','f','g','g','d', 'b', 'a','a','c','f','g','g','b','b', 'c', 'a','a','f','g','g','b','b','b','d', 'd', 'a','a','f','g','g','b','b','b','e', 'a', 'd','a','f','g','g','b','b','b','e', 'e','X'};
    int oldnb[100] =  { 7 , 8 , 8 , 4 , 5 ,  8 , 8 , 8 , 8 , 8 ,  8 ,  8 , 8 , 8 , 8 , 8 ,  8 ,  8 , 8 , 8 , 8 , 8 , 8 ,  8 ,  8 , 8 , 8 , 8 , 8 , 8 , 7 ,  7 ,  8 , 7 , 8 , 8 , 8 , 8 , 6 , 6 ,  8 ,  8 , 7 , 8 , 8 , 8 , 6 , 6 , 7 , 7 ,  7 ,  8 , 7 , 8 , 8 , 8 , 6 , 6 , 7 , 6 ,  8 ,  8 , 7 , 8 , 8 , 8 , 6 , 6 , 7 , 6 ,  7 , 9};
    char newcb[100] = {'e','c','h','f','b', 'a','b','d','f','h', 'e', 'a','b','d','f','h', 'g', 'a','b','d','f','g','h', 'c', 'a','b','d','f','g','h','c', 'b', 'a','b','d','f','g','h','a','c', 'b', 'a','b','f','g','h','a','c','c','e', 'd', 'a','b','f','g','h','a','c','c','d', 'd', 'd','b','f','g','h','a','c','c','d', 'f','X'};
    int newnb[100] =  { 6 , 5 , 4 , 2 , 4 ,  7 , 7 , 7 , 7 , 7 ,  7 ,  7 , 7 , 7 , 7 , 7 ,  8 ,  7 , 7 , 7 , 7 , 7 , 7 ,  6 ,  7 , 7 , 7 , 7 , 7 , 7 , 6 ,  6 ,  7 , 6 , 7 , 7 , 7 , 7 , 5 , 5 ,  7 ,  7 , 6 , 7 , 7 , 7 , 5 , 5 , 6 , 6 ,  5 ,  7 , 6 , 7 , 6 , 6 , 5 , 5 , 6 , 5 ,  8 ,  5 , 6 , 7 , 7 , 7 , 5 , 5 , 6 , 5 ,  5 , 9};

    if (*level==2)
    {
        // white
        if (color == 0) {
            // Stop Scholars Mate if knight at F6
            if (aicountw == 2) {
                if (Board[2][5]) {
                    if (Board[2][5]->t->t == 2) {
                        aicountw++;
                    }
                }
            }
            // Stop Scholars Mate if pawn at D5 or E6
            else if (aicountw == 3) {
                if (Board[2][4] || Board[3][3]) {
                    aicountw++;
                }
                if (Board[4][7]) {
                    newcw[3] = 'h';
                    newnw[3] = 4;
                    oldcw[4] = 'h';
                    oldnw[4] = 5;
                    newcw[4] = 'h';
                    newnw[4] = 4;
                }
            }
            if (aicountw < 73) {
                oldletter = oldcw[aicountw];
                newletter = newcw[aicountw];
                oldnumber = oldnw[aicountw];
                newnumber = newnw[aicountw];
                *oldx = convertNumber(oldnumber);
                *oldy = convertLetter(oldletter);
                *newx = convertNumber(newnumber);
                *newy = convertLetter(newletter);
                aicountw++;
            }
            // When moves run out change to random moves
            else {
                *level = 1;
            }
        }
        // black
        else {
            if (aicountb == 2) {
                if (Board[5][5] || Board[5][6]) {
                    if (Board[5][5]->t->t == 2 || Board[5][6]) {
                        aicountb++;
                    }
                }
                if (Board[3][7]) {
                    oldcb[2] = 'g';
                    oldnb[2] = 7;
                    newcb[2] = 'g';
                    newnb[2] = 6;
                    oldcb[3] = 'g';
                    oldnb[3] = 6;
                    newcb[3] = 'h';
                    newnb[3] = 5;
                }
            }
            else if (aicountb == 3) {
                if (Board[5][4] || Board[4][3]) {
                    aicountb++;
                }
            }
            if (aicountb < 73) {
                oldletter = oldcb[aicountb];
                newletter = newcb[aicountb];
                oldnumber = oldnb[aicountb];
                newnumber = newnb[aicountb];
                *oldx = convertNumber(oldnumber);
                *oldy = convertLetter(oldletter);
                *newx = convertNumber(newnumber);
                *newy = convertLetter(newletter);
                aicountb++;
            }
            else {
                *level = 1;
            }
        }
    }
    else if (*level==1)
    {
        
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (Board[i][j]) {
                    if (Board[i][j]->color == color && Board[i][j]->t->t == 5) {
                        king = Board[i][j];
                    }
                    for (int k = 0; k < Board[i][j]->counter; k++) {
                        if (Board[Board[i][j]->movelist[k][0]][Board[i][j]->movelist[k][1]]) {
                            if (Board[Board[i][j]->movelist[k][0]][Board[i][j]->movelist[k][1]]->color != color) {
                                capturemovesold[cmcounter][0] = i;
                                capturemovesold[cmcounter][1] = j;
                                capturemovesnew[cmcounter][0] = Board[i][j]->movelist[k][0];
                                capturemovesnew[cmcounter][1] = Board[i][j]->movelist[k][1];
                                capturetype[cmcounter] = Board[i][j]->t->t;
                                cmcounter++;
                            }
                        }
                    }
                }
            }
        }
        if (checkSquare(king->player->other, king->x, king->y)) {
            if (king->counter != 0) {
                pieces[0] = king;
                piececount = 1;
                kingcanmove = 1;
            }
            else {
                kingcanmove = 0;
            }
        }
        else if (aifail >= 100) {
            kingcanmove = 0;
        }
        else if (cmcounter) {
            // Caputure importance queen -> rook -> bishop -> knight -> pawn
            for (int i = 0; i < cmcounter; i++) {
                if (capturetype[i] == 2) {
                    num3 = i;
                }
                else {
                    num3 = rand()%(cmcounter);
                }
            }
            for (int i = 0; i < cmcounter; i++) {
                if (capturetype[i] == 3) {
                    num3 = i;
                }
            }
            for (int i = 0; i < cmcounter; i++) {
                if (capturetype[i] == 1) {
                    num3 = i;
                }
            }
            for (int i = 0; i < cmcounter; i++) {
                if (capturetype[i] == 4) {
                    num3 = i;
                }
            }
            *oldx = capturemovesold[num3][0];
            *oldy = capturemovesold[num3][1];
            *newx = capturemovesnew[num3][0];
            *newy = capturemovesnew[num3][1];
            return;
        }
        
        if (kingcanmove == 0) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (Board[i][j]) {
                        if (Board[i][j]->color == color && Board[i][j]->counter != 0) {
                            pieces[piececount] = Board[i][j];
                            piececount++;
                        }
                    }
                }
            }
        }

        if (aifail >= 100) {
            *oldx = pieces[failcount1]->x;
            *oldy = pieces[failcount1]->y;
            *newx = pieces[failcount1]->movelist[failcount2][0];
            *newy = pieces[failcount1]->movelist[failcount2][1];
            failcount2++;
            if (failcount2 >= pieces[failcount1]->counter) {
                failcount2 = 0;
                failcount1++;
            }
            return;
        }

        if (piececount == 0) {
            num1 = 0;
        }
        else {
            num1 = rand()%(piececount);
        }

        if (pieces[num1]->counter == 0) {
            num2 = 0;
        }
        else {
            num2 = rand()%(pieces[num1]->counter);  
        }

        *oldx = pieces[num1]->x;
        *oldy = pieces[num1]->y;
        *newx = pieces[num1]->movelist[num2][0];
        *newy = pieces[num1]->movelist[num2][1]; 
        return;
    }
        
}

