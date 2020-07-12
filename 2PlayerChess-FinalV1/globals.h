/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: globals.h
 *      Purpose: Contains all global data types that are included by other classes. No methods declared.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 *
 */
#ifndef GLOBALS_H
#define GLOBALS_H
#include <cstdlib>
#include <string>

using namespace std;

    // Declare Global Data Types used by all classes.
    enum color{WHITE, BLACK, NONE};
    // Represents the color of chess pieces, or the player.
    enum chessPieceType{PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, NOPIECE};
    // Represents the various types of chess pieces used in the game.
    enum gameState{NORMALPLAY, ERROR, CHECK, CHECKMATE, STALEMATE};
    // Represents the various game states that can exist in a game of chess.
    struct coordinates {int posX; int posY;};
    // X,Y coordinates that denote position on the chess board. 0,0 = A8 in SAN, while 7,7 = H1.
    struct pieceData {chessPieceType pieceType; color pieceColor; char pieceIcon;};
    // Holds various data relevant to a specific chess piece when queried.

#endif /* GLOBALS_H */

