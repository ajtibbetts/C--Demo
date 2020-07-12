/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessInterface.h
 *      Purpose: Handles all the processes related to outputting game play data to the screen for the user.
 *               Communicates externally with the chessGame object.  Most methods are called externally by
 *               the chessGame class.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#ifndef CHESSINTERFACE_H
#define CHESSINTERFACE_H
#include <cstdlib>
#include <iostream>
#include <string>
#include "globals.h"
#include "chessTile.h"

using namespace std;

class chessInterface {
public:
    chessInterface();
    // Purpose: Default constructor. Empty.
    // Input:   None.
    // Output:  None.
    // Caller:  None(); 
    //
    chessInterface(chessTile (*ptr)[8][8], gameState*, color*, color*);
    // Purpose: Overloaded constructor. Receives relevant game information as pointer references.
    // Input:   chessTile (*ptr)[8][8] - Reference to the 8x8 chessBoard.
    //          gameState* s - Reference to the game play state.
    //          color* player - Reference to the current active player.
    //          color* check - Reference to the current player if any who is in 'check'.
    // Output:  None.
    // Caller:  chessGame::startNewGame(); 
    //
    char getIcon(coordinates);
    // Purpose: Returns the appropriate chess icon that represents a chess piece at a given position when called.
    // Input:   coordinates coords - X,Y coordinates of the chess piece to get an icon of.
    // Output:  Returns the ASCII character relating to the chess piece found at X,Y.
    // Caller:  chessInterface::drawChessBoard();
    //
    void drawChessBoard();
    // Purpose: Outputs the chess board in its current state and all relevant game data to the console screen for user.
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::loopGameplay(); chessGame::endGame;
    //
    void setPlayerTurn();
    // Purpose: Notifies the UI of the current active player, operating on the *playerRef variable.
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::updateGameState();
    //
    void setGameStatus();
    // Purpose: Notifies the UI of the current game play status, operating on the *stateRef variable.
    // Input:   None.
    // Output:  None.
    // Caller:  chessGame::updateGameState();
    //
    void setErrorMessasge(string);
    void setLastAction(string);
    // Purpose: Notifies the UI of the current last action, populating the lastAction variable with data.
    // Input:   string s - String data to store for output.
    // Output:  None.
    // Caller:  chessGame::updateGameState();
    //
    void print(string);
    // Purpose: Outputs simple string data to the screen for the user.
    // Input:   string s - String data to output.
    // Output:  None.
    // Caller:  chessGame;
    //   
    string getErrorMessage();
    // Purpose: Returns the current error message to the screen when called.
    // Input:   None.
    // Output:  string msg - The string that contains the error data to return.
    // Caller:  chessInterface::drawChessBoard();
    //  
    string getLastAction();
    // Purpose: Returns the current last game play action to the screen when called.
    // Input:   None.
    // Output:  string msg - The string that contains the action data to return.
    // Caller:  chessInterface::drawChessBoard();
    //  
    
private:
    string playerTurn, gameStatus, errorMessage, lastAction;
    // Holds string data for the active player, the status of the game, any errors, and the last move played.
    chessTile (*boardRef)[8][8] = NULL;
    // Reference to the chessBoard from chessGame
    gameState *stateRef = NULL;
    // Reference to the current game play state from chessGame.
    color* playerRef = NULL;
    // Reference to current active player from chessGame.
    color* checkRef = NULL;
    // Reference to the current player if any that is in check.
};

#endif /* CHESSINTERFACE_H */

