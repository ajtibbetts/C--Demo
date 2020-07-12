/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessGame.h
 *      Purpose: Contains member and method declaration for chessGame class.  Manages the entire 2-Player Chess Game
 *      Input: Receives string input from users through getNotationInput() method.
 *      Output: Void. When class methods resolve game returns to main menu.
 *      Exceptions: Input validation is handled through getNotationInput().
 * 
 */

#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <cstdlib>
#include <string>
#include "globals.h"
#include "chessInterface.h"
#include "chessLogic.h"
#include "chessTile.h"
#include "chessPiece.h"

using namespace std;

class chessGame {
public:
    chessGame();
//     Purpose: Default constructor. Empty.
//     Input:   None.
//     Output:  None.
//     Caller:  Main.activeGame 
//    
    void startNewGame();
    // Purpose: Initializes a game of 2-Player Chess.  Sets up all game components and starts main game play loop.
    // Input:   None.
    // Output:  None.
    // Caller:  Main.activeGame
    //
    void setupChessBoard(); 
    // Purpose: Sets up the virtual 8x8 chess board for game play.  Spawns the chess pieces and creates the game board.
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::StartNewGame();   
    //
    void spawnPiece(chessPieceType, color, coordinates);
    // Purpose: Creates a virtual chess piece of specific type and color, then puts the piece on a space on the chessboard.
    // Input:   chessPieceType p - The type of chess piece to spawn. (Pawn, Rook, Knight, Bishop, Queen, King, NOPIECE)
    //          color c - The color of the chess piece to create. (WHITE, BLACK, NONE)
    //          coordinates coords - The x,y position on the chessBoard game board to spawn the chess piece at.
    // Output:  None.
    // Caller:  chessGame::SetupChessBoard();
    //
    void updateGameState();
    // Purpose: Notifies the instanced chessInterface object 'cinterface' of updated game play data: which player's turn 
    //          it is, whether anybody is in check/checkmate/stalemate, and what the last action was in game.
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::loopGamePlay(), chessGame::endGame();
    //
    void loopGameplay();
    // Purpose: Handles the main game play loop of 2-player chess. Continues until either a player is in checkmate,
    //          or the board state is in a stalemate.  
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::StartNewGame();
    //
    coordinates getNotationInput();
    // Purpose: Receives user input and converts the input into valid game data, looping until validated per each input.
    //          User input is entered in Standard Algebraic Notation, then converted internally into x,y coordinates. 
    // Input:   None;
    // Output:  Returns a coordinate struct of x,y coordinates that denote the position on the chess board.
    // Caller:  chessGame::loopGameplay;
    //
    coordinates validateCoordinates(string);
    // Purpose: Converts Standard Algebraic Notation chess coordinates into coordinate struct x,y values for game play.
    // Input:   string s - User string input passed through to the function.
    // Output:  coordinate coords - Returns x,y struct that denotes position on the game board.
    // Caller:  chessGame::getNotationInput();
    //
    bool isValidMove();
    // Purpose: Runs through a series of checks that validates whether the users inputted move is legally valid in
    //          a game of 2-Player Chess.  If the move is invalid, a specific reason is passed through to the on
    //          screen game interface.
    // Input:   None.
    // Output:  bool isValid - Returns TRUE if the move is legal, and FALSE if there is a reason it is not.
    // Caller:  chessGame::loopGamePlay();
    void capturePiece(chessPieceType, chessPieceType, color);
    // Purpose: When a player successfully lands their piece on an opposing player's piece, this function
    //          properly notifies the user interface by adding data to the gameAction string variable.
    // Input:   chessPieceType attackingPiece - The type of chess piece that is attacking.
    //          chessPieceType capturedPiece -  The type of chess piece that is captured.
    //          color c - Color of the piece that is attacking.
    // Output:  None.
    // Caller:  chessGame::doMove();
    //
    void doMove(coordinates, coordinates);
    // Purpose: Handles the logic for actually moving a chess piece on the virtual game board, including if an
    //          opposing player's piece is captured during the movement process.
    // Input:   coordinates from - The starting x,y position of the move on the game board. 
    //          coordinates to - The destination x,y position of where to move the piece on the game board.
    // Output:  None.
    // Caller:  chessGame::loopGameplay();
    //
    void endGame();
    // Purpose: Handles the process of actually ending the game once a winner or stalemate is declared.
    // Input:   None.
    // Output:  None.
    // Caller: Main.activeGame
    //
    
private:
    chessLogic clogic;
    // Holds instance of a chessLogic object that governs game play mechanics.
    chessInterface cinterface;
    // Holds instance of a chessInterface object that handles on screen output / user interface.
    chessTile chessBoard[8][8] = {};
    // Virtual representation of the 8x8 standard chess board.
    coordinates moveFrom, moveTo;
    // Represents a player's inputted desired move.
    color activePlayer = WHITE;
    // Holds the value of which player's turn is currently active.
    color playerInCheck = NONE;
    // Holds the value of which if any player is currently in 'Check'.
    gameState activeGameState = NORMALPLAY;
    // Holds the value of the state of the game, whether the game is normal, error, check, checkmate, or stalemate.
    string lastMove;
    // Holds data of the last inputted move, in Standard Algebraic Notation
    string gameAction = "New Game Started. White Moves First.";
    // Holds relevant data to the last gameplay action.
};

#endif /* CHESSGAME_H */

