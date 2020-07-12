/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessPiece.cpp
 *      Purpose: Holds all relevant data and methods needed to manage a virtual chess piece.
 *               Methods are called by chessTile objects, each of which hold a chessPiece as a data member.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#include "chessPiece.h"


/* Default Constructor
 * Creates an 'empty' chess piece that is essentially 'null'
 * in the context of the game.
 */
chessPiece::chessPiece() {
    pieceType = NOPIECE;
    pieceColor = NONE;
    pieceIcon = ' '; 
}

/* Overloaded Constructor
 * Creates a specific chess piece based on the received parameters when called.
 * Then calls the setIcon() function to set the appropriate game board icon.
 */
chessPiece::chessPiece(chessPieceType type, color c) {
    pieceType = type;
    pieceColor = c;   
    setIcon();
}

/* Sets the type of chess piece from external call,
 * then updates the game board icon.
 */
void chessPiece::setPieceType(chessPieceType type){
    pieceType = type;
    setIcon();
}

/* Sets the color of the chess piece from external call */
void chessPiece::setPieceColor(color c){
    pieceColor = c;
}

/* Sets the game board icon on the chess piece based on
 * pieceType ENUM value that is set prior.
 * Called when object is constructed.
 */
void chessPiece::setIcon(){
    switch(pieceType){
        case PAWN:
            pieceIcon = (pieceColor == WHITE) ? 'P' : 'p';
            break;
        case ROOK:
            pieceIcon = (pieceColor == WHITE) ? 'R' : 'r';
            break;
        case KNIGHT:
            pieceIcon = (pieceColor == WHITE) ? 'N' : 'n';
            break;
        case BISHOP:
            pieceIcon = (pieceColor == WHITE) ? 'B' : 'b';
            break;
        case QUEEN:
            pieceIcon = (pieceColor == WHITE) ? 'Q' : 'q';
            break;
        case KING:
            pieceIcon = (pieceColor == WHITE) ? 'K' : 'k';
            break;  
        default:
            pieceIcon = ' ';
            break;
    }  
}

/* Returns the current type of chess piece when called.
 * Called externally by chessTile objects.
 */
chessPieceType chessPiece::getPieceType(){
    return pieceType;
}

/* Returns the current color of chess piece when called.
 * Called externally by chessTile objects.
 */
color chessPiece::getPieceColor(){
    return pieceColor;
}

/* Returns the current visual icon of chess piece when called.
 * Called externally by chessTile objects.
 */
char chessPiece::getIcon(){
    return pieceIcon;
}

