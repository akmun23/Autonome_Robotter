#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "validMoves.h"
// #include "robotMove.h"
#include <unistd.h>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;

int main() {
    int playerTurn; //Which player's turn it is
    int blackPieces = 12; //Initial number of black pieces
    int redPieces = 12; //Initial number of red pieces
    bool gameEnd = false; //If the game has ended
    int i = 0; //Counter for the number of turns

    std::string player = "AI"; //If the player is human or AI
    std::string player2 = "AI"; //If the player is human or AI

    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn

    // Construct initial board
    std::vector<std::vector<std::string>> boards = startUp();

    // Set up the robot
    // std::vector<std::vector<double>> startUpRobot = robotStart();

    while(true){ //Game loop
        if(i%2 == 0){ //Switch player's turn
            playerTurn = 1;
        } else {
            playerTurn = 2;
        }

        //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
        if(((movePossible(playerTurn, boards, jumpPossible(playerTurn, boards), false, {}).size())/2) > 0 && redPieces > 0 && blackPieces > 0){

            std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is

            if((playerTurn == 1 && player == "p") || (playerTurn == 2 && player2 == "p")){

                moveSet = move(playerTurn, boards, redPieces, blackPieces); //Player's move

            } else {
                alphaBeta(boards, 7, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces); //AI's move
                //Prints the moves made by the AI
                for (int i = 0; i < moveSet.size(); i += 2) {
                    std::cout << "AI moves from: " << moveSet[i] << std::endl;
                    std::cout << "AI moves to: " << moveSet[i+1] << std::endl;
                }
            }

            // Moves the robot
            // robotMove(moveSet, startUpRobot);

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
