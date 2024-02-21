extern bool gameEnd;
extern bool moreMove;

#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H
#include <iostream>
#include <string>
#include <vector>

bool gameEnd = false;
bool moreMove = false;

bool playerInput(bool jumpPossible, std::string& playerStart, std::string& playerMove, std::vector<std::string>& playerJump, int playerTurn, bool move, int tries) {
    bool valid = false;
    bool check;
    bool moreMoveCheck = false;

    std::string lowerCase;
    std::string lowerCase2;

    if(!move){
        gameEnd = true;
        return true;
    }

    while(!valid){
        check = true;
        if(moreMove){
            if(!moreMoveCheck && tries == 0){
                playerStart = playerMove;
                moreMoveCheck = true;
            }
            std::cout << "Player " << playerTurn << ", please enter the coordinates of the piece you would like to move (e.g. A3): " << playerStart << std::endl;
            std::cout << "Player " << playerTurn << ", please enter the coordinates of the square you would like to move to (e.g. B4): ";
            std::cin >> playerMove;
            std::cout << std::endl;
        } else {
            std::cout << "Player " << playerTurn << ", please enter the coordinates of the piece you would like to move (e.g. A3): ";
            std::cin >> playerStart;
            std::cout << "Player " << playerTurn << ", please enter the coordinates of the square you would like to move to (e.g. B4): ";
            std::cin >> playerMove;
            std::cout << std::endl;
        }


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
    }
    moreMove = false;
    return true;
}

#endif // PLAYERINPUT_H
