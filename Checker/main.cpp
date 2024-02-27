#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "playerInput.h"
#include "validMoves.h"
#include <unistd.h>

std::vector<std::vector<std::string>> boards = {
    {"0 ", "B ", "0 ", "B ", "0 ", "B ", "0 ", "B "},
    {"B ", "0 ", "B ", "0 ", "B ", "0 ", "B ", "0 "},
    {"0 ", "B ", "0 ", "B ", "0 ", "B ", "0 ", "B "},
    {"1 ", "0 ", "1 ", "0 ", "1 ", "0 ", "1 ", "0 "},
    {"0 ", "1 ", "0 ", "1 ", "0 ", "1 ", "0 ", "1 "},
    {"R ", "0 ", "R ", "0 ", "R ", "0 ", "R ", "0 "},
    {"0 ", "R ", "0 ", "R ", "0 ", "R ", "0 ", "R "},
    {"R ", "0 ", "R ", "0 ", "R ", "0 ", "R ", "0 "}
};

int main() {
    int playerTurn = 1;
    int blackPieces = 12;
    int black;
    int redPieces = 12;
    int red;
    bool check = false;
    bool gameEnd = false;
    bool promotion = false;
    int tries;
    int i = 0;
    bool jumped = false;
    bool valid = false;
    std::vector<std::string> jump = {};
    std::vector<std::string> playerJump = {};
    std::vector<std::string> posMove = {};
    std::vector<std::string> moveSet = {};
    std::cout << "Welcome to Checkers!" << std::endl;
    std::cout << "Here is the board:" << std::endl;
    checkerBoard(boards);

    //Get the player"s move
    std::string playerStart;
    std::string playerMove;

    while(true){
        valid = false;
        if(i%2 == 0){
            playerTurn = 1;
        } else {
            playerTurn = 2;
        }
        black = 0;
        red = 0;
        jump = jumpPossible(playerTurn, boards);
        if(((movePossible(playerTurn, boards, jump, moreMoveCheck(jump, playerMove), playerMove).size())/2) > 0 && redPieces > 0 && blackPieces > 0){

            std::cout << "Player " << playerTurn << "'s turn:" << std::endl;
            //aiPlay(boards, playerStart, playerMove, playerTurn, redPieces, blackPieces);

            if(playerTurn == 1){
                while(!valid){
                    do{
                        jump = jumpPossible(playerTurn, boards);
                        valid = false;
                        while(!valid){
                            playerInput(playerStart, playerMove, jump, playerTurn);
                            valid = playerMover(playerStart, playerMove, playerTurn, boards);
                        }
                        jumped = pieceJump(playerStart, playerMove, playerTurn, boards);
                        promotion = boardChange(playerTurn, boards, playerStart, playerMove, redPieces, blackPieces);
                        if(moreMoveCheck(jumpPossible(playerTurn, boards), playerMove) && jumped && !promotion){
                            checkerBoard(boards);
                        }
                    } while(moreMoveCheck(jumpPossible(playerTurn, boards), playerMove) && jumped && !promotion);
                }
            } else {
                minMaxAlgo(boards, 7, playerTurn, redPieces, blackPieces, boards, moveSet);

            //minMax(boards, playerStart, playerMove, playerTurn, redPieces, blackPieces, 3);

                for (int i = 0; i < moveSet.size(); i += 2) {
                    std::cout << "AI moves from: " << moveSet[i] << std::endl;
                    std::cout << "AI moves to: " << moveSet[i+1] << std::endl;
                }
            }

            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if(boards[i][j] == "R " || boards[i][j] == "RK"){
                        red++;
                    } else if(boards[i][j] == "B " || boards[i][j] == "BK"){
                        black++;
                    }
                }
            }

            blackPieces = black;
            redPieces = red;

            std::cout << "There are " << redPieces << " red pieces left." << std::endl;
            std::cout << "There are " << blackPieces << " black pieces left." << std::endl;
            std::cout << std::endl;
            checkerBoard(boards);
            std::cout << "Game score is: " << giveBoardScore(boards, playerTurn) << std::endl;
            std::cout << std::endl;

            sleep(1);
        } else {
            gameEnd = true;
            break;
        }
        i++;
    }


    if(gameEnd){
        if(redPieces == 0){
            std::cout << "Player 1 wins! No more red pieces" << std::endl;
        } else if(blackPieces == 0){
            std::cout << "Player 1 wins! No more black pieces" << std::endl;
        } else if(playerTurn == 1){
            std::cout << "Player 2 wins!         } else if(playerTurn == 2 && blackPieces == 0){No more moves for black" << std::endl;
        } else if(playerTurn == 2){
            std::cout << "Player 1 wins! No more moves for red" << std::endl;
        }
    }

    return 0;
}
