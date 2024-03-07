#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "playerInput.h"
#include "validMoves.h"
#include "robotMove.h"
#include <unistd.h>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;

// Construct initial board
std::vector<std::vector<std::string>> boards = {
    {"  ", "B ", "  ", "B ", "  ", "B ", "  ", "B "},
    {"B ", "  ", "B ", "  ", "B ", "  ", "B ", "  "},
    {"  ", "B ", "  ", "B ", "  ", "B ", "  ", "B "},
    {"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "},
    {"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "},
    {"R ", "  ", "R ", "  ", "R ", "  ", "R ", "  "},
    {"  ", "R ", "  ", "R ", "  ", "R ", "  ", "R "},
    {"R ", "  ", "R ", "  ", "R ", "  ", "R ", "  "}
};

int main() {
    int playerTurn; //Which player's turn it is
    int blackPieces = 12; //Initial number of black pieces
    int redPieces = 12; //Initial number of red pieces
    bool gameEnd = false; //If the game has ended
    bool promotion = false; //If a piece has been promoted
    int i = 0; //Counter for the number of turns
    bool jumped = false; //If a piece has jumped
    bool valid = false; //If the move is valid

    std::vector<std::string> jump = {}; //Possible jump moves
    std::vector<std::string> posMove = {}; //Possible moves
    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn

    //Print the initial board
    std::cout << "Welcome to Checkers!" << std::endl;
    std::cout << "Here is the board:" << std::endl;
    checkerBoard(boards);

    //Get the player"s move
    std::string playerStart;
    std::string playerMove;

    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, 0}, 1, 0.1);

    while(true){ //Game loop
        valid = false; //Varaible needs to be set to false if a human is playing. Not used when AI plays

        if(i%2 == 0){ //Switch player's turn
            playerTurn = 1;
        } else {
            playerTurn = 2;
        }

        int black = 0; //Variable used to count number of black pieces on board
        int red = 0; //Variable used to count number of red pieces on board

        //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
        if(((movePossible(playerTurn, boards, jumpPossible(playerTurn, boards), false, playerMove).size())/2) > 0 && redPieces > 0 && blackPieces > 0){

            std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is

            if(playerTurn == 1){ //Player 1's turn
                //Can be commented out to make it possible for player to make a move
                /*while(!valid){
                    do{
                        jump = jumpPossible(playerTurn, boards);
                        valid = playerInput(playerStart, playerMove, jump, playerTurn, boards);
                        moveSet.push_back(playerStart);
                        moveSet.push_back(playerMove);
                        jumped = pieceJump(playerStart, playerMove, playerTurn, boards);
                        promotion = boardChange(playerTurn, boards, playerStart, playerMove, redPieces, blackPieces);
                        if(moreMoveCheck(jumpPossible(playerTurn, boards), playerMove) && jumped && !promotion){
                            checkerBoard(boards);
                        }
                    } while(moreMoveCheck(jumpPossible(playerTurn, boards), playerMove) && jumped && !promotion);
                }*/

               alphaBeta(boards, 7, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX); //AI's move

               //Prints the moves made by the AI
                for (int i = 0; i < moveSet.size(); i += 2) {
                    std::cout << "AI moves from: " << moveSet[i] << std::endl;
                    std::cout << "AI moves to: " << moveSet[i+1] << std::endl;
                }

            } else { //Player 2's turn

                alphaBeta(boards, 7, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX); //AI's move

                //Prints the moves made by the AI
                for (int i = 0; i < moveSet.size(); i += 2) {
                    std::cout << "AI moves from: " << moveSet[i] << std::endl;
                    std::cout << "AI moves to: " << moveSet[i+1] << std::endl;
                }
            }

            //Counts the number of pieces on the board
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if(boards[i][j] == "R " || boards[i][j] == "RK"){
                        red++;
                    } else if(boards[i][j] == "B " || boards[i][j] == "BK"){
                        black++;
                    }
                }
            }

            robotMove(moveSet);

            blackPieces = black; //Sets the number of black pieces
            redPieces = red; //Sets the number of red pieces

            //Prints data from the state of the game and prints the board
            std::cout << "There are " << redPieces << " red pieces left." << std::endl;
            std::cout << "There are " << blackPieces << " black pieces left." << std::endl;
            std::cout << std::endl;
            checkerBoard(boards);
            std::cout << "Game score is: " << giveBoardScore(boards, playerTurn) << std::endl;
            std::cout << std::endl;

        } else { //If no valid moves, or no more pieces on the board
            gameEnd = true; //Game has ended
            break;
        }
        i++;
    }


    //Prints the winner of the game
    if(gameEnd){
        if(redPieces == 0){
            std::cout << "Player 1 wins! No more red pieces" << std::endl;
        } else if(blackPieces == 0){
            std::cout << "Player 1 wins! No more black pieces" << std::endl;
        } else if(playerTurn == 1){
            std::cout << "Player 2 wins! No more moves for black" << std::endl;
        } else if(playerTurn == 2){
            std::cout << "Player 1 wins! No more moves for red" << std::endl;
        }
    }

    return 0;
}
