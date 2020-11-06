#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Piece.h"
#include "ChessBoard.h"
#include "Display.h"
#include "Player.h"
#include "Conversion.h"
#include "Log.h"
#include "AI.h"

int main(void) {

	// Initializes board
	srand(time(NULL));
	remove("Log.txt");

	int level;
	int gamemode;
	int usercolor = 10;

	printf("\n*********************************\n");
	printf("*********************************\n");
	printf("**************WELCOME************\n");
	printf("*********************************\n");
	printf("**************LETS***************\n");
	printf("**************PLAY***************\n");
	printf("**************CHESS**************\n");
	printf("*********************************\n");
	printf("****Created by: White Knights****\n");
	printf("*********************************\n");
	printf("*********************************\n\n");

	#ifdef DEBUG
	gamemode = 2;
	level = 1;
	usercolor = 2;
	#else
	while (1) {
		printf("Select Gamemode\n0-Human vs Human, 1-Human vs AI, 2-AI vs AI\n");
		printf("Which Game Type?: ");
		scanf("%d", &gamemode);
		if (gamemode >= 0 && gamemode <= 2) {
			break;
		}
		else {
			printf("Invalid input\n");
		}
	}
	printf("\n\n");
	
	if (gamemode == 0) {
		usercolor = 3;
	}

	if (gamemode == 1) {
		while (1) {
			printf("Please select a level\nLEVEL --- 1 ,  LEVEL --- 2 , INFORMATION -- 3, EXIT --- 0 \n");
			printf("Which LEVEL?: ");
			scanf("%d",&level);
			if (level >= 0 && level <= 2) {
				break;
			}
			else if (level == 3) {
				printf("Level 1:\n");
				printf("The AI plays random moves.\n");
				printf("Level 2:\n");
				printf("The AI plays a preset order of moves. If the preset is exhausted the AI switches to random moves.\n");
			}
			else {
				printf("Invalid input\n");
			}
		}
		printf("\n");
	    
	    if (level==0)
	    {
	        printf("Bye ...............\n\n");
	        return 0;
	   
	    }
		printf("0-Red, 1-Green\n");
		while (1) {
			printf("Which color do you want to be? (Red goes first): ");
			scanf("%d", &usercolor);
			if (usercolor >= 0 && usercolor <= 1) {
				break;
			}
			else {
				printf("Invalid input\n");
			}
		}	
		printf("\n\n");
	}

	if (gamemode == 2) {
		gamemode = 1;
		while (1) {
			printf("Please select a level\nLEVEL --- 1 ,  LEVEL --- 2 , INFORMATION -- 3, EXIT --- 0 \n");
			printf("Which LEVEL?: ");
			scanf("%d",&level);
			if (level >= 0 && level <= 2) {
				break;
			}
			else if (level == 3) {
				printf("Level 1:\n");
				printf("The AI plays random moves.\n");
				printf("Level 2:\n");
				printf("The AI plays a preset order of moves. If the preset is exhausted the AI switches to random moves.\n");
			}
			else {
				printf("Invalid input\n");
			}
		}
		printf("\n");
	    
	    if (level==0)
	    {
	        printf("Bye ...............\n\n");
	        return 0;
	   
	    }

		usercolor = 2;
	}
	#endif

	PIECE *Board[8][8];
	PIECE *tempBoard[8][8];

	PIECE *capturedPieces[30];
	for (int n = 0; n < 30; n++) {
		capturedPieces[n] = NULL;
	}
	int capturecount = 0;

	startBoard(Board);
	copyBoard(Board, tempBoard);


	TYPE *typelist[6];
	// Pawn type
	typelist[0] = Board[1][0]->t;
	// Other types
	for (int i = 0; i < 5; i++) {
		typelist[i+1] = Board[0][i]->t;
	}

	PLAYER *playerW = createPlayer(0, Board);
	PLAYER *playerB = createPlayer(1, Board);
	PLAYER* tempptr = playerW;
	playerW->other = playerB;
	playerB->other = tempptr;

	updatePlayer(playerW, Board);
	updatePlayer(playerB, Board);
	updateMoves(Board);
	printBoard(Board);

/*
	int oldx, oldy, newx, newy = 0;
*/

	char oldletter, newletter;
	int oldnumber, newnumber;
	int oldx, oldy, newx, newy;
	int counter = 1;
	int whitecheck = 0;
	int blackcheck = 0;
	int movecheck;
	int mate;
	int choice = 0;
	int test;
	int capturetimer = 0;
	int drawcheck = 0;
	int aifailw = 0;
	int aifailb = 0;

	PIECE *tempPiece;
	
	test = 0;
	while(1) {
		printf("Turn %d\n", counter);
		counter++;
		while(counter > 2 && (usercolor == 0 || usercolor == 3)) {
			printf("Red's turn\n");
			printf("Make a move-0 OR Print log-1 OR Exit-2\n");
			printf("Choice: ");
			scanf("%d", &choice);
			if (choice == 0) {
				break;
			}
			else if (choice == 1) {
				readfile();
			}
			else if (choice == 2){
				break;
			}
			else {
				printf("Invalid input\n");
			}
		}
		if (choice == 2) {
			printf("\nBye ...............\n\n");
			break;
		}
		while(1) {
			if (gamemode == 0 || usercolor == 0) {
				// Ask player for movement
				printf("Enter piece you want to move\n");
				printf("Enter Coordinate: ");
				scanf(" %c", &oldletter);
				scanf("%d", &oldnumber);

				printf("Enter where you want to move\n");
				printf("Enter Coordinate: ");
				scanf(" %c", &newletter);
				scanf("%d", &newnumber);
				
				oldx = convertNumber(oldnumber);
				oldy = convertLetter(oldletter);
				newx = convertNumber(newnumber);
				newy = convertLetter(newletter);
			}
			else {
				aifunction(Board, 0, &level, &oldx, &oldy, &newx, &newy, aifailw);
				aifailw++;
			}
			
			// Checks if new coordinates are in the movelist of the piece
			if (Board[oldx][oldy] != NULL) {
				movecheck = checkPiece(Board[oldx][oldy], newx, newy);
			}
			// Check for no piece at spot
			if (oldx > 7 || oldx < 0 || oldy > 7 || oldy < 0 || Board[oldx][oldy] == NULL) {
				// Does not display error if AI
				if (gamemode == 0 || usercolor == 0) {
					printf("Invalid Move: There is no piece there!\n");
				}
			}
			// Checks for correct piece color
			else if (Board[oldx][oldy]->color == 1) {
				// Does not display error if AI
				if (gamemode == 0 || usercolor == 0) {
					printf("Invalid Move: That piece is not yours!\n");
				}
			}
			// If checks pass then the piece is moved and movelists are updated
			else if (movecheck) {
				// Points to new position in case there is a capture
				tempPiece = Board[newx][newy];
				movePiece(Board, Board[oldx][oldy], newx, newy);
				// Updates player defend list after move to see if white is in check
				updatePlayer(playerW, Board);
				updatePlayer(playerB, Board);
				// Checks if white is in check
				whitecheck = Check(Board, 0);
				if (whitecheck) {
					// If white is in check after the move then reset to previous board state
					copyBoard(tempBoard, Board);
					Board[oldx][oldy]->x = oldx;
					Board[oldx][oldy]->y = oldy;
					// Resets defend lists
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					// Does not display error if AI
					if (gamemode == 0 || usercolor == 0) {
						printf("Invalid Move: That piece can't move there!\n");
					}
				}
				// White is not in Check after move
				else { 
					unmarkPawn(Board);
					// If there is a piece at new position add to captured pieces array to be freed later
					if (tempPiece) { 
						capturedPieces[capturecount] = tempPiece;
						capturecount++;
						// If there was a capture reset capture timer
						capturetimer = 0;
					}
					// If the moved piece is a pawn reset capture timer
					if (Board[newx][newy]->t->t == 0) {
						capturetimer = 0;
					}
					// Writefile needs information on previous position so the position is temporarily reset
					Board[newx][newy]->x = oldx;
					Board[newx][newy]->y = oldy;
					writefile(tempBoard[oldx][oldy], newx, newy, tempBoard);
					Board[newx][newy]->x = newx;
					Board[newx][newy]->y = newy;
					copyBoard(Board, tempBoard);
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					// Checks if there is a pawn that needs to be promoted
					if (gamemode == 0 || usercolor == 0) {
						PawnPromotion(Board[newx][newy], typelist, 0);
					}
					else {
						PawnPromotion(Board[newx][newy], typelist, 1);
					}
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					blackcheck = Check(Board, 1);
					mate = Mate(Board, 1);
					printBoard(Board);
					aifailw = 0;
					break;
				}
			}
			// Executes if the new coordinate is not in the movelist
			else {
				// Does not display error if AI
				if (gamemode == 0 || usercolor == 0) {
					printf("Invalid Move: That piece can't move there!\n");
				}
			}
		}
		
		// If mate is detected then the game ends
		if (mate == 1) {
			// If black is in check and mated, then white wins
			if (blackcheck) {
				writefile(NULL, 10, 10, tempBoard);
				printf("Checkmate! Red Wins\n");
				break;
			}
			// If black is not in check and mated, then stalemate
			else {
				writefile(NULL, 12, 12, tempBoard);
				printf("Stalemate!\n");
				break;
			}
		}

		while(counter > 1 && (usercolor == 1 || usercolor == 3)) {
			printf("Green's turn\n");
			printf("Make a move-0 OR Print log-1 OR Exit-2\n");
			printf("Choice: ");
			scanf("%d", &choice);
			if (choice == 0) {
				break;
			}
			else if (choice == 1) {
				readfile();
			}
			else if (choice == 2){
				break;
			}
			else {
				printf("Invalid input\n");
			}
		}
		if (choice == 2) {
			printf("\nBye ...............\n\n");
			break;
		}
		while(1) {
			if (gamemode == 0 || usercolor == 1) {
				// Ask player for movement
				printf("Enter piece you want to move\n");
				printf("Enter Coordinate: ");
				scanf(" %c", &oldletter);
				scanf("%d", &oldnumber);

				printf("Enter where you want to move\n");
				printf("Enter Coordinate: ");
				scanf(" %c", &newletter);
				scanf("%d", &newnumber);

				oldx = convertNumber(oldnumber);
				oldy = convertLetter(oldletter);
				newx = convertNumber(newnumber);
				newy = convertLetter(newletter);
			}
			else {
				aifunction(Board, 1, &level, &oldx, &oldy, &newx, &newy, aifailb);
				aifailb++;
			}
			
			// Checks if new coordinates are in the movelist of the piece
			if (Board[oldx][oldy] != NULL) {
				movecheck = checkPiece(Board[oldx][oldy], newx, newy);
			}
			// Check for no piece at spot
			if (oldx > 7 || oldx < 0 || oldy > 7 || oldy < 0 || Board[oldx][oldy] == NULL) {
				// Does not display error if AI
				if (gamemode == 0 || usercolor == 1) {
					printf("Invalid Move: There is no piece there!\n");
				}
			}
			// Checks for correct piece color
			else if (Board[oldx][oldy]->color == 0) {
				// Does not display error if AI
				if (gamemode == 0 || usercolor == 1) {
					printf("Invalid Move: That piece is not yours!\n");
				}
			}
			// If checks pass then the piece is moved and movelists are updated
			else if (movecheck) {
				unmarkPawn(Board);
				// Points to new position in case there is a capture
				tempPiece = Board[newx][newy];
				movePiece(Board, Board[oldx][oldy], newx, newy);
				// Updates player defend list after move to see if black is in check
				updatePlayer(playerW, Board);
				updatePlayer(playerB, Board);
				// Checks if black is in check
				blackcheck = Check(Board, 1);
				if (blackcheck) {
					// If black is in check after the move then reset to previous board state
					copyBoard(tempBoard, Board);
					Board[oldx][oldy]->x = oldx;
					Board[oldx][oldy]->y = oldy;
					// Resets defend lists
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					// Does not display error if AI
					if (gamemode == 0 || usercolor == 1) {
						printf("Invalid Move: That piece can't move there!\n");
					}
				}
				// Black is not in Check after move
				else {
					// If there is a piece at new position add to captured pieces array to be freed later
					if (tempPiece) {
						capturedPieces[capturecount] = tempPiece;
						capturecount++;
						// If there was a capture reset capture timer
					}
					else {
						// If there was no capture increment capture timer
						capturetimer++;
					}
					// If the moved piece is a pawn reset capture timer
					if (Board[newx][newy]->t->t == 0) {
						capturetimer = 0;
					}
					// Writefile needs information on previous position so the position is temporarily reset
					Board[newx][newy]->x = oldx;
					Board[newx][newy]->y = oldy;
					writefile(tempBoard[oldx][oldy], newx, newy, tempBoard);
					Board[newx][newy]->x = newx;
					Board[newx][newy]->y = newy;
					copyBoard(Board, tempBoard);
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					// Checks if there is a pawn that needs to be promoted
					if (gamemode == 0 || usercolor == 1) {
						PawnPromotion(Board[newx][newy], typelist, 0);
					}
					else {
						PawnPromotion(Board[newx][newy], typelist, 1);
					}
					updatePlayer(playerW, Board);
					updatePlayer(playerB, Board);
					updateMoves(Board);
					whitecheck = Check(Board, 0);
					mate = Mate(Board, 0);
					printBoard(Board);
					aifailb = 0;
					break;
				}
			}
			// Executes if the new coordinate is not in the movelist
			else {
				// Does not display error if AI
				if (gamemode == 0 || usercolor == 1) {
					printf("Invalid Move: That piece can't move there!\n");
				}
			}
		}
		if (capturetimer >= 50) {
			#ifdef DEBUG
			printf("50 Moves have been made without capture or pawn move.\n");
			printf("Draw Game\n");
			writefile(NULL, 12, 12, tempBoard);
			break;
			#else
			while (1) {
				printf("50 Moves have been made without capture or pawn move.\n");
				printf("Do both players accept a draw? 0-No 1-Yes\n");
				printf("Choice: ");
				scanf("%d",&drawcheck);
				if (drawcheck >= 0 && drawcheck <= 1) {
					break;
				}
				else {
					printf("Invalid Input\n");
				}
			}
			if (drawcheck) {
				printf("Players agree to a draw\n");
				writefile(NULL, 12, 12, tempBoard);
				break;
			}
			#endif
		}

		if (drawcheck) {
			printf("Players agree to a draw.\n");
			writefile(NULL, 12, 12, tempBoard);
			break;
		}
		if (mate == 1) {
			if (whitecheck) {
				writefile(NULL, 11, 11, tempBoard);
				printf("Checkmate! Green Wins\n");
				break;
			}
			else {
				writefile(NULL, 12, 12, tempBoard);
				printf("Stalemate!\n");
				break;
			}
		}
		#ifdef DEBUG
		#else
		if (usercolor == 2 && test != 2) {
			while (1) {
				printf("Continue? 0-No 1-Yes 2-Stop Asking\n");
				scanf("%d", &test);
				if (test >= 0 && test <= 2) {
					break;
				}
				else {
					printf("Invalid input\n");
				}
			}
			if (test == 0) {
				break;
			}
		}
		#endif
	}

	tempPiece = NULL;

	// Free type declarations
	for (int n = 0; n < 6; n++) {
		typelist[n]->updateMoves = NULL;
		free(typelist[n]);
		typelist[n] = NULL;
	}

	// Free Captured Pieces
	for (int n = 0; n < 30; n++) {
		if (capturedPieces[n]) {
			if (capturedPieces[n]->t) {
				capturedPieces[n]->t = NULL;
			}
			if (capturedPieces[n]->player) {
				capturedPieces[n]->player = NULL;
			}
			if (capturedPieces[n]->board) {
				capturedPieces[n]->board = NULL;
			}
			free(capturedPieces[n]);
			capturedPieces[n] = NULL;
		}
		else {
			break;
		}
	} 

	// Free Pieces on Board
	for (int n = 0; n < 8; n++) {
		for (int m = 0; m < 8; m++) {
			if (Board[n][m]) {
				if (Board[n][m]->t) {
					Board[n][m]->t = NULL;
				}
				if (Board[n][m]->player) {
					Board[n][m]->player = NULL;
				}
				if (Board[n][m]->board) {
					Board[n][m]->board = NULL;
				}
				free(Board[n][m]);
				Board[n][m] = NULL;
			}
		}
	}

	// Free Players
	playerW->other = NULL;
	free(playerW);
	playerW = NULL;
	playerB->other = NULL;
	free(playerB);
	playerB = NULL;
	
	return 0;
}
