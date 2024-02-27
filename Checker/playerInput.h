#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include <iostream>
#include <string>
#include <vector>

bool playerInput(std::string& playerStart, std::string& playerMove, std::vector<std::string>& playerJump, int playerTurn) {
    bool valid = false;
    bool check;
    bool moreMoveCheck = false;
    bool jumpPossible = false;
    if(playerJump.size() > 0){
        jumpPossible = true;
    }

    std::string lowerCase;
    std::string lowerCase2;

    std::cout << "Player " << playerTurn << ", please enter the coordinates of the piece you would like to move (e.g. A3): ";
    std::cin >> playerStart;
    std::cout << "Player " << playerTurn << ", please enter the coordinates of the square you would like to move to (e.g. B4): ";
    std::cin >> playerMove;
    std::cout << std::endl;

    if(playerStart.length() != 2 || playerMove.length() != 2) {
        std::cout << "Invalid move. Please enter a move in the format A3." << std::endl;
        valid = false;
    } else {
        valid = true;
    }

    if(jumpPossible && valid){
        for (int i = 0; i < playerJump.size(); i+=2) {
            lowerCase = playerJump[i];
            lowerCase[0] = tolower(lowerCase[0]);
            lowerCase2 = playerJump[i+1];
            lowerCase2[0] = tolower(lowerCase2[0]);
            if(check){
                if((playerStart == playerJump[i] || playerStart == lowerCase) && (playerMove == playerJump[i+1] || playerMove == lowerCase2)){
                    check = false;
                    valid = true;
                } else {
                    valid = false;
                }
            }
        }
        if(!valid){
            std::cout << "Invalid move. You must jump." << std::endl;
            return false;
        }
    }
    return true;
}

#endif // PLAYERINPUT_H
