/*      Author: Drew Tibbetts
 *      Creation Date: 6/22/2019
 *      Modification: 8/6/2019
 *      FileName: chessLogic.cpp
 *      Purpose: Handles all the game play logic needed to conduct a game of 2-player chess.
 *      Input: None.
 *      Output: None.
 *      Exceptions: None.
 * 
 */

#include "chessLogic.h"


chessLogic::chessLogic() {
}
// Overloaded constructor. Initializes memory references found in chessGame.h
chessLogic::chessLogic(chessTile (*ptr)[8][8], color* c, color* ck){
    boardRef = ptr;
    colorRef = c;
    checkRef = ck;
}

// returns a time from the chess board
chessTile chessLogic::getTile(coordinates c){
    
    return (*boardRef)[c.posX][c.posY];
}

// returns FALSE if player enters starting coordinates that denote an empty space on the chessboard
bool chessLogic::isValidPiece(coordinates coords){
    
    if((*boardRef)[coords.posX][coords.posY].getActivePiece().pieceIcon == ' '){
        return false;
    }
    else{
        return true;
    }  
}

// returns FALSE if player enters starting coordinates that denote an opposing player's piece
bool chessLogic::isPlayerPiece(coordinates coords, color playerColor){
    if((*boardRef)[coords.posX][coords.posY].getActivePiece().pieceColor == playerColor ){
        return true;
    }
    else{
        return false;
    }
}

// returns TRUE if the player tries to move one of their pieces on top of another of their pieces
bool chessLogic::isPlayerDestination(coordinates coords, color playerColor){
    if((*boardRef)[coords.posX][coords.posY].getActivePiece().pieceColor == playerColor){
        return true;
    }
    else{
        return false;
    }
    
}


// checks if movement is valid based on the piece type and position on the board
bool chessLogic::isValidPieceMove(coordinates from, coordinates to){
    availableMoves.clear();
    chessPieceType pieceToCheck = (*boardRef)[from.posX][from.posY].getActivePiece().pieceType;
    bool isValid = false;
    switch(pieceToCheck){
        case PAWN:
            queryValidPawnMoves(from, *colorRef, &availableMoves);
            break;
        case ROOK:
            queryValidRookMoves(from, *colorRef, &availableMoves);
            break;
        case KNIGHT:
            queryValidKnightMoves(from, *colorRef, &availableMoves);
            break;
        case BISHOP:
            queryValidBishopMoves(from, *colorRef, &availableMoves);
            break;
        case QUEEN:
            queryValidQueenMoves(from, *colorRef);
            break;
        case KING:
            queryValidKingMoves(from, *colorRef, &availableMoves);
            break;
        default:
            break;
    }
    for(int i = 0; i < availableMoves.size(); i++){  
        // cout << "DEBUG -- Valid destination: " << availableMoves.at(i).posX << ", " << availableMoves.at(i).posY << endl; // debug line
        if(availableMoves.at(i).posX == to.posX && availableMoves.at(i).posY == to.posY){
            return true;
        }
    }
    return isValid;
}

// simulates move, then checks if moving player is in check before reverting the game move
bool chessLogic::isMoveCheckForKing(coordinates from, coordinates to, color c){  
    bool isCheck;
    // backup the two pieces to check
    chessTile backupFrom = (*boardRef)[from.posX][from.posY];
    chessTile backupTo = (*boardRef)[to.posX][to.posY];
    // simulate move
    (*boardRef)[to.posX][to.posY] = (*boardRef)[from.posX][from.posY];
    (*boardRef)[from.posX][from.posY].emptyTile();
    // check if player's king is in check in simulated board
    isCheck = isPlayerInCheck(c);
    // restore board position to original state
    (*boardRef)[from.posX][from.posY] = backupFrom;
    (*boardRef)[to.posX][to.posY] = backupTo;
    return isCheck;  
}

void chessLogic::setKingPosition(coordinates pos, color c){   
    if(c == WHITE){
        wKingPos.posX = pos.posX;
        wKingPos.posY = pos.posY;
    }
    else {
        bKingPos.posX = pos.posX;
        bKingPos.posY = pos.posY;
    }   
}

// PIECE QUERY METHODS
// BASED ON PIECE TYPE AND COORDINATES RECEIVED
// FILLS PASSED THROUGH VECTOR WITH ALL VIABLE DESTINATION COORDINATES
// LEGAL FOR THAT CHESS PIECE TYPE

void chessLogic::queryValidPawnMoves(coordinates from, color c, vector<coordinates>* vc){
    
    coordinates offset;
    int startX; 
    // determine query direction based on player color
    int dir;
    switch(c){
        case WHITE:
            dir = -1;
            startX = 6;
            break;
        case BLACK:
            dir = 1;
            startX = 1;
            break;
    }
    
    // move forward 1 space
    offset = {from.posX + dir, from.posY};
    if(offset.posX < 8 && offset.posX >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() == NONE){            
            vc->push_back(offset);    
        }
    }
    // move forward 2 space if pawn has not moved once yet and there are no pieces blocking the move
    offset = {from.posX + (dir*2), from.posY};
    if(offset.posX < 8 && offset.posX >= 0){
        if((*boardRef)[from.posX + dir][from.posY].getControllingPlayer() == NONE && (*boardRef)[offset.posX][offset.posY].getControllingPlayer() == NONE && from.posX == startX){
            vc->push_back(offset);    
        }
    }
    // check diagonal forward left for enemy piece to capture
    offset = {from.posX + dir, from.posY - 1};
    if(offset.posX < 8 && offset.posX >= 0 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);    
            }
        }
    }
    // check diagonal forward  right for enemy piece to capture
    offset = {from.posX + dir, from.posY + 1};
    if(offset.posX < 8 && offset.posX >= 0 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);    
            }
        }
    }   
}

void chessLogic::queryValidRookMoves(coordinates from, color c, vector<coordinates>* vc){
    
    // set directional block flags that flag TRUE once a pieces movement is blocked
    bool isBlockedU = false, isBlockedD = false, isBlockedL = false, isBlockedR = false;
    coordinates tempCoords;

    // logic for determining valid moves for the rook piece at this location
    for(int i = 1; i < 8; i++){  
        // check tiles downward
        if(from.posX + i < 8 && !isBlockedD) {
            
            tempCoords.posX = from.posX + i;
            tempCoords.posY = from.posY;
           
            if((*boardRef)[from.posX + i][from.posY].getControllingPlayer() != NONE){
                if((*boardRef)[from.posX + i][from.posY].getControllingPlayer() != c){
                    vc->push_back(tempCoords);
                }
                isBlockedD = true;
            }
            else{
                vc->push_back(tempCoords);
            }  
        }
        // check tiles upward
        if(from.posX - i >= 0 && !isBlockedU) {
          
            tempCoords.posX = from.posX - i;
            tempCoords.posY = from.posY;
 
            if((*boardRef)[from.posX - i][from.posY].getControllingPlayer() != NONE){
                if((*boardRef)[from.posX - i][from.posY].getControllingPlayer() != c){
                    vc->push_back(tempCoords);
                }
                isBlockedU = true;
            }
            else{
                vc->push_back(tempCoords);
            }
             
        }    
        // check tiles rightward
        if(from.posY + i < 8 && !isBlockedR){
            
            tempCoords.posX = from.posX;
            tempCoords.posY = from.posY + i;
            
           
            if((*boardRef)[from.posX][from.posY + i].getControllingPlayer() != NONE){
                if((*boardRef)[from.posX][from.posY + i].getControllingPlayer() != c){
                    vc->push_back(tempCoords);
                }
                isBlockedR = true;
            }
            else{
                vc->push_back(tempCoords);
            }
           
        } 
        // check tiles leftward
        if(from.posY - i >= 0 && !isBlockedL){
           
            tempCoords.posX = from.posX;
            tempCoords.posY = from.posY - i;
            
            
            if((*boardRef)[from.posX][from.posY - i].getControllingPlayer() != NONE){
                if((*boardRef)[from.posX][from.posY - i].getControllingPlayer() != c){
                  vc->push_back(tempCoords);  
                }
                isBlockedL = true;
            }
            else{
                vc->push_back(tempCoords);
            }   
        }      
    }   
}

void chessLogic::queryValidKnightMoves(coordinates from, color c, vector<coordinates>* vc){
    
    coordinates offset;
    
    // check bottom right 1
    offset = {from.posX + 2, from.posY + 1};
    if(offset.posX < 8 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check bottom right 2
    offset = {from.posX + 1, from.posY + 2};
    if(offset.posX < 8 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check top right 1
    offset = {from.posX - 1, from.posY + 2};
    if(offset.posX >= 0 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check top right 2
    offset = {from.posX - 2, from.posY + 1};
    if(offset.posX >= 0 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check bottom left 1
    offset = {from.posX + 1, from.posY - 2};
    if(offset.posX < 8 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check bottom left 2
    offset = {from.posX + 2, from.posY - 1};
    if(offset.posX < 8 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check top left 1
    offset = {from.posX - 2, from.posY - 1};
    if(offset.posX >= 0 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check top left 2
    offset = {from.posX - 1, from.posY - 2};
    if(offset.posX >= 0 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    
}

void chessLogic::queryValidBishopMoves(coordinates from, color c, vector<coordinates>* vc){
    
    // set directional block flags that flag TRUE once a pieces movement is blocked
    bool isBlockedUL = false, isBlockedUR = false, isBlockedDL = false, isBlockedDR = false;
    coordinates offset;
    
    // loop through all valid bishop moves in each diagonal direction, expanding outward from starting position
    
    for(int i = 1; i < 8; i++){
        
        // check up and to the left
       // cout << "Starting position: " << from.posX << "," << from.posY << endl;
        offset = {from.posX - i, from.posY - i};
      //  cout << "Check for valid UL move at coordinates: " << offset.posX << "," << offset.posY << endl;
        if(offset.posX >= 0 && offset.posY >= 0 && !isBlockedUL) {
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
                if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                    vc->push_back(offset);
                }
                isBlockedUL = true;
            }
            else{
                vc->push_back(offset);
            }  
        }
        
        // check up and to the right
        offset = {from.posX - i, from.posY + i};
     //   cout << "Check for valid UR move at coordinates: " << offset.posX << "," << offset.posY << endl;
        if(offset.posX >= 0 && offset.posY < 8 && !isBlockedUR) {
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
                if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                    vc->push_back(offset);
                }
                isBlockedUR = true;
            }
            else{
                vc->push_back(offset);
            }  
        }
        // check down and to the left
        offset = {from.posX + i, from.posY - i};
    //    cout << "Check for valid DL move at coordinates: " << offset.posX << "," << offset.posY << endl;
        if(offset.posX < 8 && offset.posY >= 0 && !isBlockedDL) {
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
                if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                    vc->push_back(offset);
                }
                isBlockedDL = true;
            }
            else{
                vc->push_back(offset);
            }  
        }
        // check down and to the right
        offset = {from.posX + i, from.posY + i};
      //  cout << "Check for valid DR move at coordinates: " << offset.posX << "," << offset.posY << endl;
        if(offset.posX < 8 && offset.posY < 8 && !isBlockedDR) {
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
                if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                    vc->push_back(offset);
                }
                isBlockedDR = true;
            }
            else{
                vc->push_back(offset);
            }  
        }      
    }  
}

void chessLogic::queryValidQueenMoves(coordinates from, color c){

        queryValidRookMoves(from, *colorRef, &availableMoves);
        queryValidBishopMoves(from, *colorRef, &availableMoves);
     
}

void chessLogic::queryValidKingMoves(coordinates from, color c, vector<coordinates>* vc){
    
    coordinates offset;
    
   
    // check diagonal
    offset = {from.posX + 1, from.posY + 1};
    if(offset.posX < 8 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    offset = {from.posX - 1, from.posY + 1};
    if(offset.posX >= 0 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    offset = {from.posX + 1, from.posY - 1};
    if(offset.posX < 8 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    offset = {from.posX - 1, from.posY - 1};
    if(offset.posX >= 0 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    // check rank diretions
    offset = {from.posX + 1, from.posY};
    if(offset.posX < 8 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    offset = {from.posX - 1, from.posY};
    if(offset.posX >= 0 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    offset = {from.posX, from.posY + 1};
    if(offset.posX >= 0 && offset.posY < 8){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }
    offset = {from.posX, from.posY - 1};
    if(offset.posX >= 0 && offset.posY >= 0){
        if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != NONE){
            if((*boardRef)[offset.posX][offset.posY].getControllingPlayer() != c){
                vc->push_back(offset);  
            }  
        }
        else{
            vc->push_back(offset);
        }
    }                                   
}


// adds all valid moves for all pieces of a color to colorMoves vector;
void chessLogic::queryAllMovesByColor(color c){
    colorMoves.clear();
    chessTile tile;
    // query every tile on the board and get the piece
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tile = getTile({i,j});
            if(tile.getControllingPlayer() == c){
                switch(tile.getActivePiece().pieceType){
                    case PAWN:
                        queryValidPawnMoves({i,j}, c, &colorMoves);
                         break;
                    case ROOK:
                         queryValidRookMoves({i,j}, c, &colorMoves);
                         break;
                    case KNIGHT:
                        queryValidKnightMoves({i,j}, c, &colorMoves);
                        break;
                    case BISHOP:
                        queryValidBishopMoves({i,j}, c, &colorMoves);
                        break;
                    case QUEEN:
                        queryValidRookMoves({i,j}, c, &colorMoves);
                        queryValidBishopMoves({i,j}, c, &colorMoves);
                        break;
                    case KING:
                        queryValidKingMoves({i,j}, c, &colorMoves);
                        break;
                    default:
                        break;   
                }
            }
        }
    } 
}



// returns tile that holds King piece of chosen color
chessTile chessLogic::getKing(color c){  
   chessTile tile;
   for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tile = getTile({i,j});
            if(tile.getControllingPlayer() == c){
                switch(tile.getActivePiece().pieceType){
                    case KING:
                        setKingPosition({i,j}, c);
                        return tile;
                        break;
                    default:
                        break;   
                }
            }
        }
    }     
}



coordinates chessLogic::getKingPosition(color c){
    if(c == WHITE){
        return wKingPos;
    }
    else{
        return bKingPos;
    }
}

bool chessLogic::isPlayerInCheck(color c){
    
    chessTile kingTile = getKing(c);
    coordinates kingPos = getKingPosition(c);
    
    if(c == WHITE){
        queryAllMovesByColor(BLACK);
    }
    else{
        queryAllMovesByColor(WHITE);
    }
    
    for(int i = 0; i < colorMoves.size(); i++){  
        if(colorMoves.at(i).posX == kingPos.posX && colorMoves.at(i).posY == kingPos.posY){
            return true;
        }
    }
    
    return false;
}

// called if a king is in check. gets all the possible moves from a player color,
// and sees if there is any way to protect against check
bool chessLogic::isPlayerOutOfMoves(color c){
    
    int movesInCheck = 0;
    int totalAvailableMoves = 0;
    vector<coordinates> newMoves;
    chessTile tile;
    
    
        // query every tile on the board and get the piece
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                // reset pool of moves each pass through
                
                tile = getTile({i,j});
                if(tile.getControllingPlayer() == c){
                    
                    newMoves.clear(); 
                  //  cout << "CHECK FOR TILE PIECE TYPE: " << tile.getActivePiece().pieceIcon << " at " << i << "," << j << endl;
                    switch(tile.getActivePiece().pieceType){
                        case PAWN:
                            queryValidPawnMoves({i,j}, c, &newMoves);
                            totalAvailableMoves += newMoves.size();
                             break;
                        case ROOK:
                             queryValidRookMoves({i,j}, c, &newMoves);
                             totalAvailableMoves += newMoves.size();
                             break;
                        case KNIGHT:
                            queryValidKnightMoves({i,j}, c, &newMoves);                            
                            totalAvailableMoves += newMoves.size();
                            break;
                        case BISHOP:
                            queryValidBishopMoves({i,j}, c, &newMoves);
                            totalAvailableMoves += newMoves.size();
                            break;
                        case QUEEN:
                            queryValidRookMoves({i,j}, c, &newMoves);
                            totalAvailableMoves += newMoves.size();
                            queryValidBishopMoves({i,j}, c, &newMoves);
                            totalAvailableMoves += newMoves.size();
                            break;
                        case KING:
                            queryValidKingMoves({i,j}, c, &newMoves);
                            totalAvailableMoves += newMoves.size();
                            break;
                        default:                            
                            break;   
                    }
                  //  cout << "Total Available Moves: " << totalAvailableMoves << endl;
                    if (newMoves.size() >= 1 ){
                        // add number of available moves to the total then check if moves are in check
                        
                        for(int x = 0; x < newMoves.size(); x++){
                       //     cout << "check for check at pos " << i << "," << j << " to " << newMoves.at(x).posX << "," << newMoves.at(x).posY  << endl;
                            if(isMoveCheckForKing({i,j}, newMoves.at(x), c)){

                                movesInCheck++;
                            }
                        }
                    }
                }
            }
        }     
    
    
   // cout << "Total Available Moves: " << totalAvailableMoves << endl;
   // cout << "Total moves in check: " << movesInCheck << endl;
    
    if(movesInCheck == totalAvailableMoves){
        return true;
    }
    else{
        return false;
    } 
}

