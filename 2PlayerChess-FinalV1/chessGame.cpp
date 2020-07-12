/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessGame.cpp
 *      Purpose: Contains method initialization for chessGame class.  Manages the entire 2-Player Chess Game
 *      Input: Receives string input from users through getNotationInput() method.
 *      Output: Void. When class methods resolve game returns to main menu.
 *      Exceptions: Input validation is handled through getNotationInput().
 * 
 */

#include "chessGame.h"



chessGame::chessGame() {
}

void chessGame::startNewGame(){
    
    setupChessBoard();
    
    // setup pointer references for chess board to external classes
    
    cinterface = chessInterface(&chessBoard, &activeGameState, &activePlayer, &playerInCheck);
    clogic = chessLogic(&chessBoard, &activePlayer, &playerInCheck);
    
     // reset the game board and draw to screen
    lastMove = " ";
    gameAction = "New Game Started. White Moves First.";
    activeGameState = NORMALPLAY;
    playerInCheck = NONE;
    updateGameState();
    
    // start the main gameplay loop
    loopGameplay();
}

void chessGame::setupChessBoard(){
    
    // Spawn White Pieces
    spawnPiece(ROOK, WHITE, {7,0});
    spawnPiece(KNIGHT, WHITE, {7,1});
    spawnPiece(BISHOP, WHITE, {7,2});
    spawnPiece(QUEEN, WHITE, {7,3});
    spawnPiece(KING, WHITE, {7,4});
    spawnPiece(BISHOP, WHITE, {7,5});
    spawnPiece(KNIGHT, WHITE, {7,6});
    spawnPiece(ROOK, WHITE, {7,7});
    for (int i = 0; i < 8; i++){
        spawnPiece(PAWN, WHITE, {6, i});
    }
    
    // Spawn Black Pieces
    spawnPiece(ROOK, BLACK, {0,0});
    spawnPiece(KNIGHT, BLACK, {0,1});
    spawnPiece(BISHOP, BLACK, {0,2});
    spawnPiece(QUEEN, BLACK, {0,3});
    spawnPiece(KING, BLACK, {0,4});
    spawnPiece(BISHOP, BLACK, {0,5});
    spawnPiece(KNIGHT, BLACK, {0,6});
    spawnPiece(ROOK, BLACK, {0,7});
    for (int i = 0; i < 8; i++){
        spawnPiece(PAWN, BLACK, {1, i});
    }
    
    // Spawn Empty Pieces in rows 3-6 // MAKE SURE the i < 6 not i < 7 when NOT testing
    for (int i = 2; i < 6; i++){
        for(int j = 0; j < 8; j++){
            chessTile newTile;
            chessBoard[i][j] = newTile;
        }
    }
}

void chessGame::spawnPiece(chessPieceType p, color c, coordinates coords){
    chessPiece newPiece = chessPiece(p,c);
    chessTile newTile(newPiece);
    chessBoard[coords.posX][coords.posY] = newTile;
    
}

void chessGame::updateGameState(){
    
    // update relevant game information and draw game board
    cinterface.setPlayerTurn();
    cinterface.setGameStatus();
    cinterface.setLastAction(gameAction);
}

coordinates chessGame::getNotationInput(){
    bool isValid = false;
    coordinates coords;
    string input;
    
    while(!isValid){
        getline(cin, input);
        coords = validateCoordinates(input);
        if(coords.posX >= 0 || coords.posY >= 0){
            lastMove += input.substr(0,2);
            isValid = true;
        }
        else{
            cout << "Please enter valid input in form of chess notation. (A-H)(1-8): " << endl;
            isValid = false;
        }
    }
    
    return coords;
}

coordinates chessGame::validateCoordinates(string s){
    
    coordinates coords;
    
    // convert string input input coordinates
    // get horizontal coordinate
    switch(s[0]){
        case 'A':
        case 'a':
            coords.posY = 0;
            break;
        case 'B':
        case 'b':
            coords.posY = 1;
            break;
        case 'C':
        case 'c':
            coords.posY = 2;
            break;
        case 'D':
        case 'd':
            coords.posY = 3;
            break;
        case 'E':
        case 'e':
            coords.posY = 4;
            break;
        case 'F':
        case 'f':
            coords.posY = 5;
            break;
        case 'G':
        case 'g':
            coords.posY = 6;
            break;
        case 'H':
        case 'h':
            coords.posY = 7;
            break;
        default:
            coords.posY = -1;
            break;
    }

    // get vertical coordinate
    switch(s[1]){
        case '1':
            coords.posX = 7;
            break;
        case '2':
            coords.posX = 6;
            break;
        case '3':
            coords.posX = 5;
            break;
        case '4':
            coords.posX = 4;
            break;
        case '5':
            coords.posX = 3;
            break;
        case '6':
            coords.posX = 2;
            break;
        case '7':
            coords.posX = 1;
            break;
        case '8':
            coords.posX = 0;
            break;
        default:
            coords.posX = -1;
            break;
    }
    
    
    return coords;
}

bool chessGame::isValidMove(){
    bool isValid = false;
    
    if(!clogic.isValidPiece(moveFrom)){
        cinterface.setErrorMessasge("Invalid starting coordinates. Cannot move an empty space!");
        activeGameState = ERROR;
    }
    else if(!clogic.isPlayerPiece(moveFrom, activePlayer)){
        cinterface.setErrorMessasge("Invalid starting coordinates. Cannot move your opponent's piece!");
        activeGameState = ERROR;
    }
    else if(clogic.isPlayerDestination(moveTo, activePlayer)){
        cinterface.setErrorMessasge("Invalid ending coordinates. Cannot move your piece on top of your other piece!");
        activeGameState = ERROR;
    }
    else if(!clogic.isValidPieceMove(moveFrom, moveTo)){
        cinterface.setErrorMessasge("DESTINATION coordinates is invalid for this piece, or blocked by another piece.");
        activeGameState = ERROR;
    }
    else if(clogic.isMoveCheckForKing(moveFrom, moveTo, activePlayer)){
        cinterface.setErrorMessasge("Invalid move.  Cannot put your own king in check!");
        activeGameState = ERROR;
    } 
    else{
        isValid = true;
        activeGameState = NORMALPLAY;
    }
    
    
    return isValid;
}

void chessGame::loopGameplay(){
    do {
        
        bool isValid = false;
        
        /* Print User Instructions */
        
        // check if the results in a stalemate before any action
        if(clogic.isPlayerOutOfMoves(WHITE)){
            activeGameState = STALEMATE;
            return;
        }
        if (clogic.isPlayerOutOfMoves(BLACK)){
            activeGameState = STALEMATE;
            return;
        }
        
        
        string playerColor;
        while(!isValid){
            
            // draw visual chess board on screen
            // cout << string(50, '\n');
            cinterface.drawChessBoard();
            cinterface.print("    |||--------------|||");
            cinterface.print("    ||| " + (playerColor = (activePlayer == WHITE) ? "WHITE" : "BLACK") + "'S TURN |||");
            cinterface.print("    |||--------------|||");
            // get user input
            lastMove.clear();
            cinterface.print(">>> Please enter the STARTING coordinates in Standard Notation (A1, B2, etc): ");
            moveFrom = getNotationInput();
            cinterface.print(">>> Please enter the DESTINATION coordinates in Standard Notation (A1, B2, etc): ");
            moveTo = getNotationInput();
            
            if(isValidMove()){
                isValid = true;
            }
        }
        
        // if the move is legal and valid, perform the move
        activeGameState = NORMALPLAY;
        gameAction = lastMove.substr(0,2) + " to " + lastMove.substr(2,2) + ". "; // updates the output display of last move
        doMove(moveFrom, moveTo);
        
        
        
        // check if either player is in check
        if(clogic.isPlayerInCheck(WHITE)){
            playerInCheck = WHITE;
            activeGameState = CHECK;
        }
        else if(clogic.isPlayerInCheck(BLACK)){
            playerInCheck = BLACK;
            activeGameState = CHECK;
        }
        else{
            playerInCheck = NONE;
        }
        
        // if check is active, check for checkmate
        if(activeGameState == CHECK){
            if(clogic.isPlayerOutOfMoves(playerInCheck)){
              activeGameState = CHECKMATE;
            }
        }
        
        
        
        
        
        
        // after turn is complete, change to opposing color's turn
        if(activePlayer == WHITE){
            activePlayer = BLACK;
        }
        else {
            activePlayer = WHITE;
        }
        
        
        // update game and draw board once ready
        updateGameState();   
    }  while (activeGameState != CHECKMATE  && activeGameState != STALEMATE); 
    
    return;
}

void chessGame::capturePiece(chessPieceType attackingPiece, chessPieceType capturedPiece, color c){
    string str;
    chessPieceType pieceEval = attackingPiece;
    str += (c == WHITE) ? "WHITE " : "BLACK ";
    
    for(int i = 0; i < 2; i++){
        switch(pieceEval){
            case PAWN: 
                str += "PAWN";
                break;
            case ROOK:
                str += "ROOK";
                break;
            case KNIGHT:
                str += "KNIGHT";
                break;
            case BISHOP:
                str += "BISHOP";
                break;
            case QUEEN:
                str += "QUEEN";
                break;
            case KING:
                str += "KING";
                break;
        }
        
        if(i == 0){
            str += " CAPTURES ";
            str += (c == WHITE) ? "BLACK " : "WHITE ";
            pieceEval = capturedPiece;
        }
        else{
            str += ".";
        } 
    }
    
    gameAction += str;
}

void chessGame::doMove(coordinates from, coordinates to){ 
    bool flagCapture; 
    chessTile* startTile = &chessBoard[from.posX][from.posY];
    chessTile* endTile = &chessBoard[to.posX][to.posY];
    
    // check if the player will capture an enemy piece
    if(endTile->getActivePiece().pieceIcon != ' '){
        chessPieceType attackingPiece, capturedPiece;
        attackingPiece = startTile->getActivePiece().pieceType;
        capturedPiece = endTile->getActivePiece().pieceType;
        capturePiece(attackingPiece, capturedPiece, activePlayer);
    }
    
    // move the starting tile to the destination, and nullify the origin after
    *endTile = *startTile;
    (*startTile).emptyTile();
}

void chessGame::endGame(){
    switch(activeGameState){
        case CHECKMATE:
            gameAction += (playerInCheck == WHITE) ? "CHECKMATE ON WHITE. BLACK WINS!!" : "CHECKMATE ON BLACK. WHITE WINS!!";
            break;
        case STALEMATE:
            gameAction += "STALEMATE. GAME IS A DRAW.";
            break;    
    }
    
    updateGameState();
    cinterface.drawChessBoard();
    cout << "Game is over. Returning to main menu..." << endl;
    return;
}