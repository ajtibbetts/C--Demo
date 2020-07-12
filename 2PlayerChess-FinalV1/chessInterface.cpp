/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessInterface.cpp
 *      Purpose: Handles all the processes related to outputting game play data to the screen for the user.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#include "chessInterface.h"

chessInterface::chessInterface() {
}

// initialize point reference array of main chess board
chessInterface::chessInterface(chessTile (*ptr)[8][8], gameState* s, color* player, color* check){
    boardRef = ptr;
    stateRef = s;
    playerRef = player;
    checkRef = check;
}



// returns chess piece character to draw to gameboard
char chessInterface::getIcon(coordinates coords){
    
    char icon = (*boardRef)[coords.posX][coords.posY].getActivePiece().pieceIcon;
 
    return icon;
}



void chessInterface::drawChessBoard(){
    
    /* ROW 1 */
    cout <<" __A__B__C__D__E__F__G__H__ " << endl;
    cout <<" |   ///   ///   ///   ///| " << endl;
    cout <<"8| "<< getIcon({0,0}) <<" /"<< getIcon({0,1}) <<"/ "<< getIcon({0,2}) <<" /"<< getIcon({0,3}) <<"/ "<< getIcon({0,4}) <<" /"<< getIcon({0,5}) <<"/ "<< getIcon({0,6}) <<" /"<< getIcon({0,7}) <<"/|8" << endl;
    cout <<" |   ///   ///   ///   ///| " << endl;
    /* ROW 2 */
    cout <<" |///   ///   ///   ///   | " << endl;
    cout <<"7|/"<< getIcon({1,0}) <<"/ "<< getIcon({1,1}) <<" /"<< getIcon({1,2}) <<"/ "<< getIcon({1,3}) <<" /"<< getIcon({1,4}) <<"/ "<< getIcon({1,5}) <<" /"<< getIcon({1,6}) <<"/ "<< getIcon({1,7}) <<" |7" << endl;
    cout <<" |///   ///   ///   ///   | " << endl;
    /* ROW 3 */
    cout <<" |   ///   ///   ///   ///| " << endl;
    cout <<"6| "<< getIcon({2,0}) <<" /"<< getIcon({2,1}) <<"/ "<< getIcon({2,2}) <<" /"<< getIcon({2,3}) <<"/ "<< getIcon({2,4}) <<" /"<< getIcon({2,5}) <<"/ "<< getIcon({2,6}) <<" /"<< getIcon({2,7}) <<"/|6" << endl;
    cout <<" |   ///   ///   ///   ///| " << endl;
    /* ROW 4 */
    cout <<" |///   ///   ///   ///   | " << endl; 
    cout <<"5|/"<< getIcon({3,0}) <<"/ "<< getIcon({3,1}) <<" /"<< getIcon({3,2}) <<"/ "<< getIcon({3,3}) <<" /"<< getIcon({3,4}) <<"/ "<< getIcon({3,5}) <<" /"<< getIcon({3,6}) <<"/ "<< getIcon({3,7}) <<" |5" << endl;
    cout <<" |///   ///   ///   ///   | " << endl;
    /* ROW 5 */
    cout <<" |   ///   ///   ///   ///| " << endl;
    cout <<"4| "<< getIcon({4,0}) <<" /"<< getIcon({4,1}) <<"/ "<< getIcon({4,2}) <<" /"<< getIcon({4,3}) <<"/ "<< getIcon({4,4}) <<" /"<< getIcon({4,5}) <<"/ "<< getIcon({4,6}) <<" /"<< getIcon({4,7}) <<"/|4" << endl;
    cout <<" |   ///   ///   ///   ///| " << endl;
    /* ROW 6 */
    cout <<" |///   ///   ///   ///   | " << endl;
    cout <<"3|/"<< getIcon({5,0}) <<"/ "<< getIcon({5,1}) <<" /"<< getIcon({5,2}) <<"/ "<< getIcon({5,3}) <<" /"<< getIcon({5,4}) <<"/ "<< getIcon({5,5}) <<" /"<< getIcon({5,6}) <<"/ "<< getIcon({5,7}) <<" |3" << endl;
    cout <<" |///   ///   ///   ///   |     |||--------------|||" << endl;
    /* ROW 7 */
    cout <<" |   ///   ///   ///   ///|     ||| "<< playerTurn<<"'S TURN |||" << endl;
    cout <<"2| "<< getIcon({6,0}) <<" /"<< getIcon({6,1}) <<"/ "<< getIcon({6,2}) <<" /"<< getIcon({6,3}) <<"/ "<< getIcon({6,4}) <<" /"<< getIcon({6,5}) <<"/ "<< getIcon({6,6}) <<" /"<< getIcon({6,7}) <<"/|2    |||--------------|||" << endl;
    cout <<" |   ///   ///   ///   ///|     ||| "<< getLastAction() << endl;
    /* ROW 8 */
    cout <<" |///   ///   ///   ///   |     ||| " << gameStatus << endl;
    cout <<"1|/"<< getIcon({7,0}) <<"/ "<< getIcon({7,1}) <<" /"<< getIcon({7,2}) <<"/ "<< getIcon({7,3}) <<" /"<< getIcon({7,4}) <<"/ "<< getIcon({7,5}) <<" /"<< getIcon({7,6}) <<"/ "<< getIcon({7,7}) <<" |1    ||| " << getErrorMessage() << endl;
    cout <<" |///   ///   ///   ///   | " << endl;
    cout <<"  -|--|--|--|--|--|--|--|-  " << endl;
    cout <<"   A  B  C  D  E  F  G  H " << endl;
    
}

void chessInterface::setPlayerTurn(){
    playerTurn = (*playerRef == WHITE) ? "WHITE" : "BLACK";
}


void chessInterface::setGameStatus(){
    switch(*stateRef){
        case NORMALPLAY:
            gameStatus = " ";
            break;
        case CHECK:
            gameStatus = "CHECK: PLAYER "; 
            gameStatus += (*checkRef == WHITE) ? "WHITE" : "BLACK";
            gameStatus += " IS IN CHECK";
            break;
        case CHECKMATE:
            gameStatus = "CHECKMATE: ";
            gameStatus += (*checkRef == WHITE) ? "WHITE" : "BLACK";
            gameStatus += " IS IN CHECKMATE. ";
            gameStatus += (*checkRef == WHITE) ? "BLACK" : "WHITE";
            gameStatus += " WINS THE GAME!!!";
            break;
        case STALEMATE:
            gameStatus += "STALEMATE.  GAME ENDS IN A DRAW";
            break;
    }
}

void chessInterface::setLastAction(string s){
    lastAction = s;
}

void chessInterface::setErrorMessasge(string s){
    errorMessage = s;
}

string chessInterface::getErrorMessage(){
    string msg;
    if(*stateRef == ERROR){
     msg = "INPUT ERROR: " + errorMessage;
    }
    else {
     msg = " ";   
    }
    return msg;
}

string chessInterface::getLastAction(){
    
    return "LAST MOVE: " + lastAction;
}

void chessInterface::print(string s){
    cout << s << endl;
}