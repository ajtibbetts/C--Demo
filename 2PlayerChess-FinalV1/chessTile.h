/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessTile.h
 *      Purpose: Holds all relevant data and methods needed to manage a virtual chess tile on the 8x8 board.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#ifndef CHESSTILE_H
#define CHESSTILE_H
#include <cstdlib>
#include <iostream>
#include "globals.h"
#include "chessPiece.h"

using namespace std;

class chessTile {
public:
    chessTile();
    // Purpose: Default constructor. Creates a null/empty chessTile with no piece and no color.
    // Input:   None.
    // Output:  None.
    // Caller:  None(); 
    //
    chessTile(chessPiece);
    // Purpose: Overloaded constructor.  Creates a chessTile occupied with a specific chessPiece object.
    // Input:   chessPiece piece - The chess piece object that will occupy this piece.
    // Output:  None.
    // Caller:  chessGame::setupChessBoard();
    //
    /* SET METHODS */
    void setActivePiece(chessPiece);
    // Purpose: Sets the active chess piece that will now occupy this chessTile.
    // Input:   chessPiece piece - The chess piece object that will occupy this piece.
    // Output:  None.
    // Caller:  N/A
    //
    void setControllingPlayer(color);
    // Purpose: Sets the color of the player that controls this chessTile.
    // Input:   color c - Color of the player that will now control this chessTile.
    // Output:  None.
    // Caller:  N/A
    //
    void emptyTile();
    // Purpose: Resets the tile to a null/empty state, as if a chessPiece has moved from the tile.
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::doMove();
    //
    
    /* GET METHODS */
    pieceData getActivePiece();
    // Purpose: Returns a data structure of relevant data pertaining to the chess piece occupying this tile.
    // Input:   None.
    // Output:  pieceData pieceInfo - Data structure of the chess piece type, color, and character icon.
    // Caller:  chessGame::doMove(), chessInterface::getIcon(), various chessLogic methods.
    //
    color getControllingPlayer();
    // Purpose: Returns the color of the player that controls or occupies this chessTile when called.
    // Input:   None.
    // Output:  color controllingPlayer - The color of the player that controls this chess tile.
    // Caller:  Various chessLogic methods.
    //
   
private:
    chessPiece activePiece;
    // holds the data of any chessPiece object that occupies this chessTile in game play.
    color controllingPlayer;
    // holds the color of the player that controls/occupies this chessTile
   
};

#endif /* CHESSTILE_H */

