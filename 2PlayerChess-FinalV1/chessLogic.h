/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessLogic.h
 *      Purpose: Handles all the game play logic needed to conduct a game of 2-player chess.
 *               Communicates externally with the chessGame object.  Most methods are called externally by
 *               the chessGame class.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#ifndef CHESSLOGIC_H
#define CHESSLOGIC_H
#include <cstdlib>
#include <string>
#include <vector>
#include <exception>
#include "globals.h"
#include "chessTile.h"
#include "chessPiece.h"
#include "chessInterface.h"

#include <iostream> // debug tests

using namespace std;

class chessLogic {
  
public:
    
    chessLogic();
    // Purpose: Default constructor. Empty.
    // Input:   None.
    // Output:  None.
    // Caller:  None; 
    //
    chessLogic(chessTile (*ptr)[8][8], color*, color*);
    // Purpose: Default constructor. Empty.
    // Input:   chessTile (*ptr)[8][8] - Reference to the 8x8 chessBoard for used for game play.
    //          color* c - Reference to the current active player, WHITE OR BLACK.
    //          color* ck - Reference to the current player if any that is in 'check'.
    // Output:  None.
    // Caller:  chessGame::startNewGame(); 
    // 
    chessTile getTile(coordinates);
    // Purpose: Returns the specific chess tile and any piece data at that tile of X,Y position on the game board.
    // Input:   coordinates c - X,Y position of the chess board to get the piece from.
    // Output:  Returns the specific chessTile object at X,Y position.
    // Caller:  Various chessLogic methods. 
    // 
    bool isValidPiece(coordinates);
    // Purpose: Checks whether the given starting X,Y coordinates on the chess board contain a chess piece.
    // Input:   coordinates coords - X,Y position of the chess board to check.
    // Output:  Returns TRUE if space is occupied by a valid chess piece, otherwise returns FALSE.
    // Caller:  chessGame::isValidMove();
    // 
    bool isPlayerPiece(coordinates, color);
    // Purpose: Checks whether the starting given X,Y coordinates on the chess board contain a chess piece
    //          controlled by the current active player.
    // Input:   coordinates coords - X,Y position of the chess board to check.
    //          color playerColor - Color of the active player.
    // Output:  Returns TRUE if space is occupied by a chess piece the active player controls.
    // Caller:  chessGame::isValidMove();
    // 
    bool isPlayerDestination(coordinates, color);
    // Purpose: Checks whether the given destination X,Y coordinates on the chess board contain a chess piece
    //          controlled by the current active player.
    // Input:   coordinates coords - X,Y position of the chess board to check.
    //          color playerColor - Color of the active player.
    // Output:  Returns TRUE if space is occupied by a chess piece the active player controls.
    // Caller:  chessGame::isValidMove();
    // 
    bool isValidPieceMove(coordinates, coordinates);
    // Purpose: Checks whether chess piece at starting coordinates can legally perform the move at the 
    //          destination coordinates.  Queries all possible legal moves of the relevant chess piece
    //          type and checks if any of them match the destination coordinates.
    // Input:   coordinates from - Starting X,Y position of the chess board to check.
    //          coordinates to - Destination X,Y position of the requested move.
    // Output:  Returns TRUE if the destination coordinates is a valid legal move for the chess piece.
    // Caller:  chessGame::isValidMove();
    // 
    bool isMoveCheckForKing(coordinates, coordinates, color);
    // Purpose: Checks whether the requested move would result in putting the active player into check.
    //          Simulates the move, analyzes the game board state for 'check', then reverts the game board.
    // Input:   coordinates from - Starting X,Y position of the chess board to check.
    //          coordinates to - Destination X,Y position of the requested move.
    //          color c - The color of the active player.
    // Output:  Returns TRUE if the destination coordinates would put the active player in check.
    // Caller:  chessGame::isValidMove();
    //
    void setKingPosition(coordinates, color);
    // Purpose: Sets the current X,Y position of a KING piece of a specific color
    // Input:   coordinates pos - X,Y position of the KING
    //          color c - Color of the KING piece to store data for.
    // Output:  None.
    // Caller:  chessLogic::getKing();
    //
    void queryValidPawnMoves(coordinates, color, vector<coordinates>*);
    // Purpose: Adds all legal moves for a PAWN piece at X,Y coordinates to the referenced vector.
    // Input:   coordinates from - Starting X,Y position of where the chess piece is.
    //          color c - Color of the chess piece to query.
    //          vector<coordinates>* vc - Reference to the coordinate vector to populate with valid moves.
    // Output:  None.
    // Caller:  chessLogic::isValidPieceMove(); chessLogic::queryAllMovesByColor(); isPlayerOutOfMoves();
    //
    void queryValidRookMoves(coordinates, color, vector<coordinates>*);
    // Purpose: Adds all legal moves for a ROOK piece at X,Y coordinates to the referenced vector.
    // Input:   coordinates from - Starting X,Y position of where the chess piece is.
    //          color c - Color of the chess piece to query.
    //          vector<coordinates>* vc - Reference to the coordinate vector to populate with valid moves.
    // Output:  None.
    // Caller:  chessLogic::isValidPieceMove(); chessLogic::queryAllMovesByColor(); isPlayerOutOfMoves();
    //
    void queryValidKnightMoves(coordinates, color, vector<coordinates>*);
    // Purpose: Adds all legal moves for a KNIGHT piece at X,Y coordinates to the referenced vector.
    // Input:   coordinates from - Starting X,Y position of where the chess piece is.
    //          color c - Color of the chess piece to query.
    //          vector<coordinates>* vc - Reference to the coordinate vector to populate with valid moves.
    // Output:  None.
    // Caller:  chessLogic::isValidPieceMove(); chessLogic::queryAllMovesByColor(); isPlayerOutOfMoves();
    //
    void queryValidBishopMoves(coordinates, color, vector<coordinates>*);
    // Purpose: Adds all legal moves for a BISHOP piece at X,Y coordinates to the referenced vector.
    // Input:   coordinates from - Starting X,Y position of where the chess piece is.
    //          color c - Color of the chess piece to query.
    //          vector<coordinates>* vc - Reference to the coordinate vector to populate with valid moves.
    // Output:  None.
    // Caller:  chessLogic::isValidPieceMove(); chessLogic::queryAllMovesByColor(); isPlayerOutOfMoves();
    //
    void queryValidQueenMoves(coordinates, color);
    // Purpose: Adds all legal moves for a QUEEN piece at X,Y coordinates to the referenced vector.
    //          As a Queen's movement is the Rook + Bishop combined, this method calls those two methods.
    //          Populates the availableMoves coordinate vector specifically.
    // Input:   coordinates from - Starting X,Y position of where the chess piece is.
    //          color c - Color of the chess piece to query.
    //          
    // Output:  None.
    // Caller:  chessLogic::isValidPieceMove();
    //
    void queryValidKingMoves(coordinates, color, vector<coordinates>*);
    // Purpose: Adds all legal moves for a KING piece at X,Y coordinates to the referenced vector.
    // Input:   coordinates from - Starting X,Y position of where the chess piece is.
    //          color c - Color of the chess piece to query.
    //          vector<coordinates>* vc - Reference to the coordinate vector to populate with valid moves.
    // Output:  None.
    // Caller:  chessLogic::isValidPieceMove(); chessLogic::queryAllMovesByColor(); isPlayerOutOfMoves();
    //
    void queryAllMovesByColor(color);
    // Purpose: Queries all legal moves for all pieces controlled by a specific color.
    //          Populates the colorMoves coordinate vector when called.
    // Input:   color c - Color of the pieces to query.
    // Output:  None.
    // Caller:  chessLogic::isPlayerinCheck();
    //
    chessTile getKing(color);
    // Purpose: Returns the chessTile object that contains the KING piece of a specific color.
    // Input:   color c - Color of KING piece to retrieve.
    // Output:  chessTile tile - The chessTile object that contains the KING.
    // Caller:  chessLogic::isPlayerinCheck();
    //
    coordinates getKingPosition(color);
    // Purpose: Returns the X,Y position of the KING piece of a specific color.
    // Input:   color c - Color of KING piece to retrieve coordinates for.
    // Output:  wKingPos  or bKingPos - X,Y coordinates of WHITE or BLACK KING.
    // Caller:  chessLogic::isPlayerinCheck();
    //
    bool isPlayerInCheck(color);
    // Purpose: Checks whether the current board state results in the player of a specific color being in 'Check'.
    // Input:   color c - Color of player to check for whether they are in 'Check' or not.
    // Output:  Returns TRUE if the current board state puts the player in check, FALSE if not.
    // Caller:  chessLogic::isMoveCheckForKing; chessGame::loopGameplay();
    //
    bool isPlayerOutOfMoves(color);
    // Purpose: Checks whether a player of a specific color has any valid moves left to perform.
    //          Basically used to determine if the game is in CHECKMATE or STALEMATE.
    //          Does this by simulating all potential moves a player can make, and comparing that
    //          Against the number of potential moves that would put that same player in check.
    // Input:   color c - Color of player to check for whether they have any valid moves left.
    // Output:  Returns TRUE if all potential moves the player can make would put them in 'Check'.
    // Caller:  chessGame::loopGameplay();
    //
    
private:
    chessTile (*boardRef)[8][8] = {};
    // Holds reference the 8x8 chess board from chessGame.
    color *colorRef = NULL;
    // Holds reference to the current active player.
    color *checkRef = NULL;
    // Holds reference to the current player in 'check', if any.
    vector<coordinates> availableMoves;
    // Holds any valid destination coordinates a specific piece can move to.
    vector<coordinates> colorMoves;
    // Holds any valid destination coordinates all pieces of a specific color can move to.
    coordinates wKingPos, bKingPos;
    // Holds the X,Y positions of the WHITE and BLACK KING pieces respectively. 
};

#endif /* CHESSLOGIC_H */

