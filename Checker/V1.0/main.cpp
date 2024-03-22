#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "robotMove.h"
#include "validMoves.h"
#include <unistd.h>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include "CheckersDatabase.h"
#include <future>

using namespace ur_rtde;

int main() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("Pascal");  // Change to username
    db.setPassword("Superbror22!");  // Change to password
    db.open();

    QSqlQuery query;

    for (int ii = 0; ii < 1; ++ii) {


            //Clear Temp og sætter start board ind
            query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");
            query.exec("INSERT INTO Temp (tempBoard_id, BoardState) "
                       "VALUES (1, '22222222222111121111444444444444')");

            /*
            query.exec("DELETE FROM Moves WHERE board_id >= 0");
            query.exec("DELETE FROM UniqueBoard WHERE board_id >= 0");*/
            int CounterForTempTable = 1;

            int playerTurn = 1; //Which player's turn it is
            int blackPieces = 12; //Initial number of black pieces
            int redPieces = 12; //Initial number of red pieces
            bool gameEnd = false; //If the game has ended
            int thisTurn; //Which player's turn it is
            int DrawChecker = 1; //When this equal 200 the game is called draw
            std::vector<std::vector<std::string>> thisBoard = {}; //The current state of the board
            std::string player = "AI"; //If the player is human or AI
            std::string player2 = "AI"; //If the player is human or AI
            std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
            std::vector<std::vector<double>> startUpRobot; //The initial position of the robot
            std::future<bool> fut;
            int i = 0;


            // Construct initial board
            std::vector<std::vector<std::string>> boards = startUp();

            while(true){ //Game loop
                thisTurn = playerTurn; //Which player's turn it is
                if (DrawChecker == 200){
                    std::cout << "The game is a draw!" << std::endl;
                    break;
                }

                std::vector<std::string> jumps = jumpPossible(playerTurn, boards);
                bool moreMove = false;
                std::string moveTo = "";

                //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
                if(((movePossible(playerTurn, boards, jumps, moreMove, moveTo).size())/2) > 0 && redPieces > 0 && blackPieces > 0){
                    std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is
                    std::vector<std::vector<std::string>> tempBoard = boards; // To be used in robotMove

                    if((playerTurn == 1 && player == "p") || (playerTurn == 2 && player2 == "p")){

                        move(playerTurn, boards, redPieces, blackPieces); //Player's move

                    } else {

                        alphaBeta(boards, 8, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {}); //AI's move
                        std::cout << "Kører loopet" << std::endl;
                    }
                    if (i > 0){
                        fut.get();
                    }



                    // Moves the robot
                    if(i == 0){
                        // Set up the robot
                        startUpRobot = robotStart();
                        atmegaCom('6'); // Sender et signal for at reset hvis gripperen er stoppet midt i et træk
                        sleep(1); // Venter 1 sekund
                        atmegaCom('8'); // Sender et signal for at gripperen skal åbne
                        fut = std::async(robotMove, moveSet, startUpRobot, tempBoard, thisTurn);
                    } else {
                        fut = std::async(robotMove, moveSet, startUpRobot, tempBoard, thisTurn);
                    }


                    std::string MoveMade;
                    //Prints the moves made by the AI
                    for (int i = 0; i < moveSet.size(); i += 2) {
                        std::cout << "Player " << thisTurn << "  moves from: " << moveSet[i] << std::endl;
                        std::cout << "Player " << thisTurn << " moves to: " << moveSet[i+1] << std::endl;
                        MoveMade = moveSet[i] + moveSet[i+1];
                    }

                    std::string output;

                    for (int i = 0; i < 8; ++i) {
                        for (int j = 0; j < 8; ++j) {
                            if(boards[i][j] == "1 "){
                                output += "1";
                            } else if(boards[i][j] == "B "){
                                output += "2";
                            } else if(boards[i][j] == "BK"){
                                output += "3";
                            } else if(boards[i][j] == "R "){
                                output += "4";
                            } else if(boards[i][j] == "RK"){
                                output += "5";
                            }
                        }
                    }

                    std::string* outputPtr = &output;
                    std::string* MoveMadePtr = &MoveMade;

                    InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);
                    DrawChecker++;
                    int depth = 8;
                    std::cout << "It is game nr: " << ii << std::endl;
                    std::cout << "It is turn: " << DrawChecker << std::endl;
                    //Prints data from the state of the game and prints the board
                    std::cout << "There are " << redPieces << " red pieces left." << std::endl;
                    std::cout << "There are " << blackPieces << " black pieces left." << std::endl;
                    std::cout << std::endl;
                    checkerBoard(boards);
                    std::cout << "Game score is: " << giveBoardScore(boards, playerTurn, blackPieces, redPieces, depth) << std::endl;
                    std::cout << std::endl;


                    i++;

                } else { //If no valid moves, or no more pieces on the board
                    gameEnd = true; //Game has ended
                    break;
                }

            //Prints the winner of the game
            if(gameEnd){
                if(redPieces == 0){
                    query.exec("UPDATE Temp SET WinOrLoss = 1 WHERE PlayerId = 1");
                    query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 2");
                    std::cout << "Player 1 wins! No more red pieces" << std::endl;
                } else if(blackPieces == 0){
                    query.exec("UPDATE Temp SET WinOrLoss = 1 WHERE PlayerId = 2");
                    query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 1");
                    std::cout << "Player 2 wins! No more black pieces" << std::endl;
                } else if (DrawChecker == 200){
                    query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 2");
                    query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 1");
                    std::cout << "The game is a draw!" << std::endl;
                } else if(playerTurn == 1){
                    query.exec("UPDATE Temp SET WinOrLoss = 1 WHERE PlayerId = 2");
                    query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 1");
                    std::cout << "Player 2 wins! No more moves for black" << std::endl;
                } else if(playerTurn == 2){
                    query.exec("UPDATE Temp SET WinOrLoss = 1 WHERE PlayerId = 1");
                    query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 2");
                    std::cout << "Player 1 wins! No more moves for red" << std::endl;
                }
            }
        }

        UpdateDatabaseFromTemp();


    }
    return 0;
}
