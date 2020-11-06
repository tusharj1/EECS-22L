
#created 4/22/2020

CC	= gcc
CCT	= gcc  -g
DEBUG	= -DDEBUG
DNDEBUG	= -DNDEBUG
CFLAGS	= -ansi -std=c99 -Wall -c
LFLAGS	= -ansi -std=c99 -Wall

all: Chess

#target to generate test executable
test: ChessTest

#target to clean the directory
clean:
	rm -f *.o
	rm -f Chess
	rm -f ChessTest
	rm -f *.txt

############ generate object files #################

#target to generate Log.o
Log.o: Log.h Log.c
	$(CC) $(CFLAGS) Log.c -o Log.o

#target to generate Conversion.o
Conversion.o: Conversion.h Conversion.c
	$(CC) $(CFLAGS) Conversion.c -o Conversion.o

#target to generate Piece.o
Piece.o: Piece.h Player.h Log.h Piece.c
	$(CC) $(CFLAGS) Piece.c -o Piece.o

#target to generate ChessBoard.o
ChessBoard.o: ChessBoard.h Piece.h ChessBoard.c
	$(CC) $(CFLAGS) ChessBoard.c -o ChessBoard.o

#target to generate Display.o
Display.o: Display.h Piece.h Display.c
	$(CC) $(CFLAGS) Display.c -o Display.o

#target to generate Player.o
Player.o: Piece.h Player.h Player.c
	$(CC) $(CFLAGS) Player.c -o Player.o	

#target to generate AI.o
AI.o: AI.h Piece.h Conversion.h
	$(CC) $(CFLAGS) AI.c -o AI.o

#target to generate Main.o
Main.o: Main.c Piece.h ChessBoard.h Display.h Player.h Conversion.h Log.h AI.h
	$(CC) $(CFLAGS) Main.c -o Main.o

#target to generate Main_DEBUG.o
Main_DEBUG.o: Main.c Piece.h ChessBoard.h Display.h Player.h Conversion.h Log.h AI.h
	$(CC) $(CFLAGS) $(DEBUG) Main.c -o Main_DEBUG.o

############ generate executables ##################
#target to generate Chess
Chess: Main.o Piece.o ChessBoard.o Display.o Player.o Conversion.o Log.o AI.o
	$(CC) $(LFLAGS) Main.o Piece.o ChessBoard.o Display.o Player.o Conversion.o Log.o AI.o -o Chess

#target to generate ChessTest
ChessTest: Main_DEBUG.o Piece.o ChessBoard.o Display.o Player.o Conversion.o Log.o AI.o
	$(CCT) $(LFLAGS) Main_DEBUG.o Piece.o ChessBoard.o Display.o Player.o Conversion.o Log.o AI.o -o ChessTest


