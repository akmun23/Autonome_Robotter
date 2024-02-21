#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "validMoves.h"

std::vector<std::string> A = {"0 ", "B ", "0 ", "B ", "0 ", "B ", "0 ", "B "};
std::vector<std::string> B = {"B ", "0 ", "B ", "0 ", "B ", "0 ", "B ", "0 "};
std::vector<std::string> C = {"0 ", "B ", "0 ", "B ", "0 ", "B ", "0 ", "B "};
std::vector<std::string> D = {"1 ", "0 ", "1 ", "0 ", "1 ", "0 ", "1 ", "0 "};
std::vector<std::string> E = {"0 ", "1 ", "0 ", "1 ", "0 ", "1 ", "0 ", "1 "};
std::vector<std::string> F = {"R ", "0 ", "R ", "0 ", "R ", "0 ", "R ", "0 "};
std::vector<std::string> G = {"0 ", "R ", "0 ", "R ", "0 ", "R ", "0 ", "R "};
std::vector<std::string> H = {"R ", "0 ", "R ", "0 ", "R ", "0 ", "R ", "0 "};

int main() {
    int playerTurn = 1;
    int blackPieces = 12;
    int redPieces = 12;
    bool check = false;
    int tries;
    std::string lowerCase;
    std::vector<std::string> playerJump = {};

    std::cout << "Welcome to Checkers!" << std::endl;
    std::cout << "Here is the board:" << std::endl;
    checkerBoard(A, B, C, D, E, F, G, H);

    //Get the player"s move
    std::string playerStart;
    std::string playerMove;

    for (int i = 0; i < 10; ++i) {
        if(i%2 == 0){
            playerTurn = 1;
        } else {
            playerTurn = 2;
        }

        do{
            tries = 0;
            check = false;

            jumpPossible(playerTurn, A, B, C, D, E, F, G, H, playerJump);
            if(moreMove){
                for (int i = 0; i < playerJump.size(); i += 2) {
                    lowerCase = playerJump[i];
                    lowerCase[0] = tolower(lowerCase[0]);
                    if(playerJump[i] == playerMove || lowerCase == playerMove){
                    std::cout << "Jump possible from " << playerJump[i] << " to " << playerJump[i+1] << std::endl;
                    }
                }
            }else {
                for (int i = 0; i < playerJump.size(); i += 2) {
                    std::cout << "Jump possible from " << playerJump[i] << " to " << playerJump[i+1] << std::endl;
                }
            }

            std::cout << std::endl;

            while(!check){
                check = playerMover(playerStart, playerMove, A, B, C, D, E, F, G, H, playerTurn, redPieces, blackPieces, playerJump, tries);

                if(check){
                    checkerBoard(A, B, C, D, E, F, G, H);
                }
            }
            if(gameEnd){
                break;
            }
        } while(moreMove);


        if(gameEnd){
            if(playerTurn == 1 && redPieces == 0){
                std::cout << "Player 1 wins!" << std::endl;
            } else if(playerTurn == 1){
                std::cout << "Player 2 wins!" << std::endl;
            } else if(playerTurn == 2 && blackPieces == 0){
                std::cout << "Player 2 wins!" << std::endl;
            } else if(playerTurn == 2){
                std::cout << "Player 1 wins!" << std::endl;
            }
            break;
        }

        std::cout << "There are " << redPieces << " red pieces left." << std::endl;
        std::cout << "There are " << blackPieces << " black pieces left." << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
