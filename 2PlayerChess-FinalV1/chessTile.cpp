/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessTile.cpp
 *      Purpose: Holds all relevant data and methods needed to manage a virtual chess tile on the 8x8 board.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#include "chessTile.h"

/* Default Constructor
 * Creates an 'empty' chess tile not occupied by any piece or player. 
 */
chessTile::chessTile() {
    activePiece = chessPiece();
    controllingPlayer = NONE;

}
/* Overloaded Constructor
 * Creates a chess tile already occupied by a specific chess piece and player.
 */
chessTile::chessTile(chessPiece piece){
    activePiece = piece;
    controllingPlayer = activePiece.getPieceColor();
}

/* Set method to set the active piece on this chess tile. */
void chessTile::setActivePiece(chessPiece piece){
    activePiece = piece;
}
/* Set method to set the controlling player who occupies this tile.  */
void chessTile::setControllingPlayer(color c){
    controllingPlayer = c;
}

/* Nullifies the tile of any existing chess piece or player control. */
void chessTile::emptyTile(){   
    activePiece = chessPiece(NOPIECE, NONE);
    controllingPlayer = NONE;
}

/* Returns a struct of pieceData info when called, generally called 
 * externally by chessLogic or chessInterface class methods.
 */
pieceData chessTile::getActivePiece(){
    pieceData pieceInfo;
    pieceInfo.pieceType = activePiece.getPieceType();
    pieceInfo.pieceColor = activePiece.getPieceColor();
    pieceInfo.pieceIcon = activePiece.getIcon(); 
    return pieceInfo;
}

/* Returns the color of the player that currently controls this chess piece (WHITE/BLACK/NONE) */
color chessTile::getControllingPlayer(){    
    return controllingPlayer;
}
