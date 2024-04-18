
#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
//#include "computerPos.h"
#include "qa.hpp"

#include "mainfunctions.h"
#include "validMoves.h"
#include "CheckersDatabase.h"
#include "computerVision.h"
#include "robotMove.h"
#include "matrix.h"


#include <unistd.h>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"

#include <future>




//using namespace ur_rtde;

int main() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("Pascal");  // Change to username
    db.setPassword("Superbror22!");  // Change to password
    db.open();

    QSqlQuery query;
    while(1);

    // Skriv true i input hvis databasens indhold skal slettes
    resetDB(false); // Resets the database

    for (int ii = 1; ii <= 100; ++ii) {




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
            std::string MoveMade; // Stores the move made to put it in the database
            bool DatabaseMoveMade = false;

            int TestCounterForDatabase = 0;

            int i = 0;

            int UniqueBoardIDCounter;
            // Skriv true i nr 2 input hvis temp skal uploades til databasen inden man starter spillet
            DatabaseInit(UniqueBoardIDCounter,false); //Initializes the database




            // Construct initial board
            std::vector<std::vector<std::string>> boards = startUp();

            while(true){ //Game loop

                std::string BoardState = "";
                loadBoardToString(boards,BoardState);


                std::string* outputPtr = &BoardState;

                thisTurn = playerTurn; //Which player's turn it is

                if (DrawChecker == 200){ // Tjekker om der er gået 175 træk uden en vinder
                    query.exec("UPDATE TempMoves SET WinOrLoss = 0.5"); // Sætter en halv ind i wincase for uafgjort
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
                        if (playerTurn == 1 && player == "DB" || playerTurn == 2 && player2 == "DB"){

                            MoveDBMain(BoardState, playerTurn, boards, redPieces, blackPieces, moveSet, MoveMade, CounterForTempTable, DrawChecker, DatabaseMoveMade, TestCounterForDatabase); // Database AI's move
                        }
                        else if (playerTurn == 1 && player == "Random" || playerTurn == 2 && player2 == "Random"){

                            MoveRandom(playerTurn, boards, redPieces, blackPieces, moveSet, MoveMade, DatabaseMoveMade, jumps, moreMove, moveTo); // Random move

                        }
                        else if (playerTurn == 1 && player == "AI" || playerTurn == 2 && player2 == "AI"){
                            alphaBeta(boards, 2, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {},CounterForTempTable,DrawChecker); //AI's move
                        }
                    }

                    // Skriv true i første input for at køre robotten
                    MoveRobot(false,fut,tempBoard,thisTurn,moveSet,startUpRobot,i); //Robot movement

                    printAIMove(DatabaseMoveMade,moveSet,MoveMade,thisTurn); //Prints the move made by the AI


                    std::string* MoveMadePtr = &MoveMade;

                    InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet




                    DrawChecker++;


                    int depth = 7;

                    printGameState(ii,DrawChecker,redPieces,blackPieces,playerTurn,boards,depth); //Prints the game state


                    i++;

                } else { //If no valid moves, or no more pieces on the board
                    gameEnd = true; //Game has ended
                    break;
                }
        }


        //Prints the winner of the game
        if(gameEnd){
            GameEnd(redPieces,blackPieces,playerTurn);
        }
        UploadTempToDatabase(UniqueBoardIDCounter); // Uploads the temp table to the database
        std::cout << "Moves made by database: " << TestCounterForDatabase << std::endl;
    }

    // Loads in the image
    cv::Mat img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/visionTest6.jpg");

    // Variables that is needed for the robot movement
    std::vector<cv::Point2f> newCorners;
    std::vector<cv::Point2f> calibrate;
    double pixToMeters;
    double boardSize;

    // The chessboard
    std::vector<std::vector<std::string>> chessBoard;

    // Finds the new corners of the chessboard
    std::vector<Vec3b> colours = firstLoop(newCorners, img, chessBoard, calibrate, pixToMeters, boardSize);

    // Robot movement
    std::cout << calibrate[0] << std::endl;
    std::cout << calibrate[1] << std::endl;
    std::cout << calibrate[2] << std::endl;

    std::vector<std::vector<double>> startUp = robotStartVision(newCorners, calibrate, boardSize, pixToMeters);

    int playerTurn = 1;
    robotMove({"c3", "e5"}, startUp, chessBoard, playerTurn);


    playerTurn = 2;
    img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards5.jpg");
    std::vector<std::string> move = boardLoop(colours[0], colours[1], newCorners, img, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;

    playerTurn = 1;
    img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards6.jpg");
    move = boardLoop(colours[0], colours[1], newCorners, img, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;

    return 0;
}
