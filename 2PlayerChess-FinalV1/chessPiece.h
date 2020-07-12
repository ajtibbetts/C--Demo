/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessPiece.h
 *      Purpose: Holds all relevant data and methods needed to manage a virtual chess piece.
 *               Methods are called by chessTile objects, each of which hold a chessPiece as a data member.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include <cstdlib>
#include "globals.h"

using namespace std;

class chessPiece {
public:  
    chessPiece();
    // Purpose: Default constructor. Creates a 'null' or 'empty' chess piece.
    // Input:   None.
    // Output:  None.
    // Caller:  chessTile::chessTile(); 
    //
    chessPiece(chessPieceType, color);
    // Purpose: Overloaded constructor. Creates a piece of a specific type and color.
    // Input:   chessPieceType type - The type of piece to create (PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, NOPIECE).
    //          color c - Color of the chessPiece to create. (WHITE, BLACK, NONE).
    // Output:  None.
    // Caller:  chessGame::spawnPiece(); 
    //
    void setPieceType(chessPieceType);
    // Purpose: Sets the type of chess piece this piece will be, then sets the appropriate character icon.
    //          Designed with future functionality in mind, such as upgrading Pawn pieces.
    // Input:   chessPieceType type - The type of piece to set (PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, NOPIECE).
    // Output:  None.
    // Caller:  N/A 
    //
    void setPieceColor(color);
    // Purpose: Sets the color of this chess piece. (WHITE, BLACK, NONE)
    // Input:   color c - The value of the color to set.
    // Output:  None.
    // Caller:  N/A 
    //
    void setIcon();
    // Purpose: Sets the appropriate ASCII character icon for this chess piece, based on its chessPieceType.
    // Input:   None.
    // Output:  None.
    // Caller:  chessPiece::chessPiece(); chessPiece::setPieceType(); 
    //
    chessPieceType getPieceType();
    // Purpose: Returns the type of chess piece this piece is when called.
    // Input:   None.
    // Output:  chessPieceType pieceType - The enum value of the type of chess piece this object is.
    // Caller:  chessTile::getActivePiece(); 
    //
    color getPieceColor();
    // Purpose: Returns the color of this piece is when called.
    // Input:   None.
    // Output:  color pieceColor - The color of this chess piece object. (WHITE OR BLACK).
    // Caller:  chessTile::getActivePiece();  
    //
    char getIcon();  
    // Purpose: Returns the ASCII char icon of this chessPiece when called.
    // Input:   None.
    // Output:  char pieceIcon - The ASCII character. WHITE is upper case, BLACK is lower case. 
    //                           P/p = Pawn         R/r = Rook          N/n = Knight
    //                           B/b = Bishop       Q/q = Queen         K/k = King
    // Caller:  chessTile::getActivePiece();  
    //
private:
    chessPieceType pieceType;
    // Enum value of the type of chess piece (PAWN, KNIGHT, ROOK, BISHOP, QUEEN, KING
    color pieceColor;
    // Enum value that denotes the color of this piece.
    char pieceIcon;
    // ASCII icon used to represent this piece on the game board.
};

#endif /* CHESSPIECE_H */

