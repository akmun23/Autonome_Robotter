#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
//#include "robotMove.h"
#include "computerPos.h"
#include "qa.hpp"
#include "validMoves.h"
#include "CheckersDatabase.h"
#include "computerVision.h"
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

using namespace ur_rtde;

void setMatrixValues(Matrix& m, std::vector<double> v){
    for(int r=0; r<m.getRows(); r++){
        for(int c=0; c<m.getCols(); c++){
            m.at(r,c) = v[r*m.getCols() + c];
        }
    }
}

int main() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("Indsætbrugernavn");  // Change to username
    db.setPassword("IndsætPassword!");  // Change to password
    db.open();

    QSqlQuery query;



    //Det her er er til vis man vil reset dataen i databasen
    /*
    query.exec("DELETE FROM MovesP1 WHERE board_id >= 0");
    query.exec("DELETE FROM MovesP2 WHERE board_id >= 0");
    query.exec("DELETE FROM UniqueBoard WHERE board_id >= 0");
    query.exec("ALTER TABLE UniqueBoard AUTO_INCREMENT = 1");
    */

    for (int ii = 1; ii <= 1; ++ii) {


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
            std::string OldBoard = "22222222222211111111444444444444";

            int TestCounterForDatabase = 0;

            int i = 0;

            query.exec("select board_id from UniqueBoard order by board_id desc limit 1");
            query.first();
            int UniqueBoardIDCounter = query.value(0).toInt() + 1;

            //Til hvis temp er fuld og skal uploades inden den bliver slettet
            /*
            std::cout << "Startet" << std::endl;
            UploadTempToDatabase(UniqueBoardIDCounter); // Uploads the temp table to the database
            std::cout << "Uploaded" << std::endl;
            while(1);
            */
            RefreshTempTable(playerTurn); // Refreshes the Temp table




            // Construct initial board
            std::vector<std::vector<std::string>> boards = startUp();

            while(true){ //Game loop

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

                            std::string DBmove = MovePlayer(OldBoard, playerTurn); // Database best move on current board

                            if (DBmove == "No moves"){
                                std::cout << "No moves found" << std::endl;
                                alphaBeta(boards, 7, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {},CounterForTempTable,DrawChecker); //AI's move
                            }
                            else{
                                std::cout << "AI move from database: " << DBmove << std::endl;
                                std::string DBmoveFrom = DBmove.substr(0,2);
                                std::string DBmoveTo = DBmove.substr(2,2);
                                DB_move(playerTurn, boards, redPieces, blackPieces, DBmoveFrom, DBmoveTo); //Database AI's move
                                MoveMade = DBmove;
                                TestCounterForDatabase++;
                                DatabaseMoveMade = true;

                            }
                        }
                        else if (playerTurn == 1 && player == "Random" || playerTurn == 2 && player2 == "Random"){

                            std::vector<std::string> MovesToPickFrom;
                            std::vector<std::string> PossibleJumps = movePossible(playerTurn, boards, jumps, moreMove, moveTo);
                            for(int i = 0; i < PossibleJumps.size(); i+=2){
                                MovesToPickFrom.push_back(PossibleJumps[i] + PossibleJumps[i+1]);
                            }

                            std::random_device rd;  // Obtain a random number from hardware
                            std::mt19937 eng(rd()); // Seed the generator
                            std::uniform_int_distribution<> distr(0, MovesToPickFrom.size()-1); // Define the range for the random number
                            int RandomNumber = distr(eng); // Generate a random number
                            std::string ChosenMove = MovesToPickFrom[RandomNumber]; // Generate a random number
                            std::cout << "Chosen move: " << ChosenMove << std::endl;
                            std::string moveFrom = ChosenMove.substr(0,2);
                            std::string moveTo = ChosenMove.substr(2,2);
                            DB_move(playerTurn, boards, redPieces, blackPieces, moveFrom, moveTo);
                            MoveMade = ChosenMove;
                            DatabaseMoveMade = true;

                        }
                        else if (playerTurn == 1 && player == "AI" || playerTurn == 2 && player2 == "AI"){
                            alphaBeta(boards, 5, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {},CounterForTempTable,DrawChecker); //AI's move
                        }
                    }

                    /*
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
                    }*/


                    //Prints the moves made by the AI
                    if(!DatabaseMoveMade){
                        for (int i = 0; i < moveSet.size(); i += 2) {
                            std::cout << "Player " << thisTurn << "  moves from: " << moveSet[i] << std::endl;
                            std::cout << "Player " << thisTurn << " moves to: " << moveSet[i+1] << std::endl;
                            MoveMade = moveSet[i] + moveSet[i+1];
                        }
                    }
                    DatabaseMoveMade = false;



                    std::string* MoveMadePtr = &MoveMade;

                    InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet


                    OldBoard = output;


                    DrawChecker++;


                    int depth = 7;

                    //Prints data from the state of the game and prints the board
                    std::cout << "It is game nr: " << ii << std::endl;
                    std::cout << "It is turn: " << DrawChecker << std::endl;
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
        }


        //Prints the winner of the game
        if(gameEnd){
            if(redPieces == 0){
                query.exec("UPDATE TempMoves SET WinOrLoss = 1 WHERE PlayerId = 1");
                query.exec("UPDATE TempMoves SET WinOrLoss = 0 WHERE PlayerId = 2");
                std::cout << "Player 1 wins! No more red pieces" << std::endl;
            } else if(blackPieces == 0){
                query.exec("UPDATE TempMoves SET WinOrLoss = 1 WHERE PlayerId = 2");
                query.exec("UPDATE TempMoves SET WinOrLoss = 0 WHERE PlayerId = 1");
                std::cout << "Player 2 wins! No more black pieces" << std::endl;
            } else if(playerTurn == 1){
                query.exec("UPDATE TempMoves SET WinOrLoss = 1 WHERE PlayerId = 2");
                query.exec("UPDATE TempMoves SET WinOrLoss = 0 WHERE PlayerId = 1");
                std::cout << "Player 2 wins! No more moves for black" << std::endl;
            } else if(playerTurn == 2){
                query.exec("UPDATE TempMoves SET WinOrLoss = 1 WHERE PlayerId = 1");
                query.exec("UPDATE TempMoves SET WinOrLoss = 0 WHERE PlayerId = 2");
                std::cout << "Player 1 wins! No more moves for red" << std::endl;
            }
        }
        UploadTempToDatabase(UniqueBoardIDCounter); // Uploads the temp table to the database
        std::cout << "Moves made by database: " << TestCounterForDatabase << std::endl;
    }
    /*
    cv::Mat img = imread("/home/pascal/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards4.jpg");
    std::vector<std::vector<Vec3f>> colorsAndCircles = detectAndDrawCentersOfCircles(img);
    std::vector<Vec3f> circles = colorsAndCircles[0];
    std::vector<Vec3f> colors = colorsAndCircles[1];
    std::vector<cv::Point2f> allAxis = detectAndDrawChessboardCorners(img);
    axis = {allAxis[0], allAxis[2], allAxis[3]};
    std::vector<cv::Point2f> newCorners = newChessCorners(axis);
    std::vector<double> init = findCoordFrame(newCorners, cv::Point2f(circles[0][0]*pixToMeters, circles[0][1]*pixToMeters));
    */
    /*
    Matrix robotBase(2, 1);
    setMatrixValues(robotBase, {-robotBasex, -robotBasey});
    Matrix point(2, 1);
    setMatrixValues(point, {offsetx, offsety});
    Matrix add = robotBase+point;
    */

    /*
    std::vector<double> tableCorners = tableCorner();
    Matrix robotCoord(2, 1);
    setMatrixValues(robotCoord, {tableCorners[0], tableCorners[1]});
    Matrix robot(3, 3);
    setMatrixValues(robot, {1, 0 , tableCorners[0], 0, 1, tableCorners[1], 0, 0, 1});
    std::vector<std::vector<double>> unitVecs = calcUnitVec2D(axis);
    Matrix chessRot(2,2);
    setMatrixValues(chessRot, {-unitVecs[0][0], -unitVecs[1][0], -unitVecs[0][1], -unitVecs[1][1]});
    chessRot.transpose();
    std::vector<double> coordPoint = findCoordFrame(axis, cv::Point2f(offsetx*pixToMeters, offsety*pixToMeters));
    Matrix chessCoord(2,1);
    setMatrixValues(chessCoord, {coordPoint[0], coordPoint[1]});
    Matrix multiply = chessRot.multiply(chessCoord);
    setMatrixValues(chessRot, {unitVecs[0][0], unitVecs[1][0], unitVecs[0][1], unitVecs[1][1]});
    chessRot.transpose();
    Matrix chess(3, 3);
    setMatrixValues(chess, {chessRot.at(0,0), chessRot.at(0,1), multiply.at(0,0), chessRot.at(1,0), chessRot.at(1,1), multiply.at(1,0), 0, 0, 1});
    multiply = chess.multiply(robot);
    //simpleMove(multiply.at(0,2), multiply.at(1,2), 0.02);
    */
    /*
    int playerTurn = 2;
    std::vector<std::vector<std::string>> chessBoard;
    std::vector<Vec3b> colours = firstLoop(allAxis, newCorners, img, circles, colors, chessBoard);
    Vec3b black = colours[0];
    Vec3b red = colours[1];
    img = imread("/home/pascal/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards5.jpg");
    std::vector<std::vector<std::string>> prevBoard = chessBoard;
    chessBoard = boardLoop(black, red, newCorners, img);
    std::vector<std::string> move = findMove(prevBoard, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;
    playerTurn = 1;
    img = imread("/home/pascal/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards6.jpg");
    prevBoard = chessBoard;
    chessBoard = boardLoop(black, red, newCorners, img);
    move = findMove(prevBoard, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;
    */
    return 0;
}
