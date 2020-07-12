/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Drew
 *
 * Created on July 22, 2019, 6:17 PM
 */

#include <cstdlib>
#include <iostream>
#include "globals.h"
#include "chessGame.h"

using namespace std;

chessGame activeGame;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int menuSelection;
    do{
    
        
    cout << "----------------------" << endl;    
    cout << "||| 2 PLAYER CHESS |||" << endl;
    cout << "----------------------" << endl;
    cout << "       MAIN MENU      " << endl;
    cout << "       ---------      " << endl;
    cout << " Enter the number that" << endl;
    cout << "matches the menu option" << endl;
    cout << "       ---------      " << endl;
    cout << "  1. Start New Game   " << endl;
    cout << "  2. Program Tutorial " << endl;
    cout << "  3. Software Info    " << endl;
    cout << "  4. Exit Program     " << endl;
    cout << "       ---------      " << endl;
    cout << "Enter your selection: ";
    cin >> (cin, menuSelection);
    
    switch(menuSelection){
        case 1:
            cout << "------------------------" << endl;
            cout << "|||  Start New Game  |||" << endl;
            cout << "------------------------" << endl;
            activeGame.startNewGame();
            activeGame.endGame();
            break;
        case 2:
            cout << "------------------------" << endl;
            cout << "||| Program Tutorial |||" << endl;
            cout << "------------------------" << endl;
            cout << "Select 'Start New Game' to begin." << endl;
            cout << "Each player, starting with WHITE, will enter two pairs of coordinates:" << endl;
            cout << "STARTING Coordinates: The position for the starting chess piece." << endl;
            cout << "ENDING Coordinates: The desired destination for the chosen piece." << endl;
            cout << "Moves are entered in the form of Standard Algebraic Notation (SAN)" << endl;
            cout << "For example, bottom left corner of the board is A1, while top right corner of the board is H8" << endl;
            cout << "The game ends when a player is in CHECKMATE, or the chess board becomes a STALEMATE" << endl;
            cout << "Good luck!" << endl;
            cout << "Returning to main menu..." << endl;
            cout << "------------------------" << endl << endl;
             break;
        case 3:
            cout << "------------------------" << endl;
            cout << "|||   Software Info   |||" << endl;
            cout << "------------------------" << endl;
            cout << "This program was developed in C++ by Drew Tibbetts for COP2350C Section 01 Advanced C++ Programming" << endl;
            cout << "Returning to main menu..." << endl;
            cout << "------------------------" << endl << endl;
            break;
        case 4:
            cout << "------------------------" << endl;
            cout << "|||   Exit Program   |||" << endl;
            cout << "------------------------" << endl;
            cout << "Thank you for playing! Exiting program..." << endl;
            cout << "------------------------" << endl << endl;
            exit(0); 
            break;
        default:
            cout << "------------------------" << endl;
            cout <<"Please enter a valid menu selection between 1 and 4." << endl;
            cout << "------------------------" << endl << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            break;  
    }
    }while(menuSelection != 4);       
    
    return 0;
}

