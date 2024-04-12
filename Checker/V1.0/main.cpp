#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "robotMove.h"
#include "computerPos.h"
#include "qa.hpp"
#include "robotMove.h"
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
    query.exec("INSERT INTO UniqueBoard (BoardState) VALUES ('22222222222211111111444444444444')");
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


            RefreshTempTable(playerTurn); // Refreshes the Temp table




            // Construct initial board
            std::vector<std::vector<std::string>> boards = startUp();

            while(true){ //Game loop
                thisTurn = playerTurn; //Which player's turn it is

                if (DrawChecker == 175){ // Tjekker om der er gået 175 træk uden en vinder
                    query.exec("UPDATE Temp SET WinOrLoss = 0.5"); // Sætter en halv ind i wincase for uafgjort
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
                                alphaBeta(boards, 5, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {}); //AI's move
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
                        else {
                            //alphaBeta(boards, 3, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {}); //AI's move
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


                    if (CheckDuplicateMoves(output, MoveMade, thisTurn)){
                        InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet
                        CounterForTempTable++;
                    }

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
                query.exec("UPDATE Temp SET WinOrLoss = 1 WHERE PlayerId = 1");
                query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 2");
                std::cout << "Player 1 wins! No more red pieces" << std::endl;
            } else if(blackPieces == 0){
                query.exec("UPDATE Temp SET WinOrLoss = 1 WHERE PlayerId = 2");
                query.exec("UPDATE Temp SET WinOrLoss = 0 WHERE PlayerId = 1");
                std::cout << "Player 2 wins! No more black pieces" << std::endl;
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
        UploadTempToDatabase(); // Uploads the temp table to the database
        //UpdateMoveWinrate(CounterForTempTable);
        std::cout << "Moves made by database: " << TestCounterForDatabase << std::endl;
    }

    cv::Mat img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/visionTest4.jpg");
    std::vector<std::vector<Vec3f>> circlesAndcolors = detectAndDrawCentersOfCircles(img);
    std::vector<cv::Point2f> allAxis = detectAndDrawChessboardCorners(img);
    axis = {allAxis[0], allAxis[2], allAxis[3]};
    std::vector<cv::Point2f> newCorners = newChessCorners(axis);

    std::vector<std::vector<std::string>> chessBoard;
    std::vector<Vec3b> colours = firstLoop(allAxis, newCorners, img, circlesAndcolors[0], circlesAndcolors[1], chessBoard);


    // Robot movement
    std::vector<cv::Point2f> calibrate = calibrationCircles(circlesAndcolors);

    std::cout << calibrate[0] << std::endl;
    std::cout << calibrate[1] << std::endl;
    std::cout << calibrate[2] << std::endl;

    cv::Point2f xaxis = meanPoints(xaxis1, xaxis2, xaxis3);
    cv::Point2f yaxis = meanPoints(yaxis1, yaxis2, yaxis3);
    cv::Point2f orego = meanPoints(orego1, orego2, orego3);
    cv::Point2f oregoPicture = Point2f(calibrate[0].x*pixToMeters, calibrate[0].y*pixToMeters);
    cv::Point2f xaxisPicture = Point2f(calibrate[1].x*pixToMeters, calibrate[1].y*pixToMeters);
    cv::Point2f yaxisPicture = Point2f(calibrate[2].x*pixToMeters, calibrate[2].y*pixToMeters);

    std::vector<std::vector<double>> unitVecRobot = calcUnitVec2D({yaxis, orego, xaxis});
    std::vector<std::vector<double>> unitVecCamera = calcUnitVec2D({yaxisPicture, oregoPicture, xaxisPicture});
    std::vector<std::vector<double>> unitVecChess = calcUnitVec2D({newCorners[0], newCorners[1], newCorners[2]});

    Matrix Robot(4,4);
    setMatrixValues(Robot, {unitVecRobot[0][0], unitVecRobot[1][0], 0, orego.x, unitVecRobot[0][1], unitVecRobot[1][1], 0, orego.y, 0, 0, 1, 0, 0, 0, 0, 1});
    Matrix Camera(4, 4);
    setMatrixValues(Camera, {unitVecCamera[0][0], unitVecCamera[1][0], 0, 0, unitVecCamera[0][1], unitVecCamera[1][1], 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});
    Matrix Chess(4, 4);
    setMatrixValues(Chess, {unitVecChess[0][0], unitVecChess[1][0], 0, newCorners[1].x-oregoPicture.x, unitVecChess[0][1], unitVecChess[1][1], 0, newCorners[1].y-oregoPicture.y, 0, 0, 1, 0, 0, 0, 0, 1});
    Matrix CamToChess = Camera*Chess;
    Matrix Translation(4, 1);
    setMatrixValues(Translation, {CamToChess.at(0,3), CamToChess(1,3) , 0.0, 1});
    Matrix RobotToChessTransformation = Robot*Translation;

    simpleMove(RobotToChessTransformation.at(0,0), RobotToChessTransformation.at(1,0), 0.02);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            setMatrixValues(Chess, {unitVecChess[0][0], unitVecChess[1][0], 0, newCorners[1].x-oregoPicture.x, unitVecChess[0][1], unitVecChess[1][1], 0, newCorners[1].y-oregoPicture.y, 0, 0, 1, 0, 0, 0, 0, 1});
            CamToChess = Camera*Chess;

            Matrix piece(4, 4);
            setMatrixValues(piece, {1, 0, 0, i*0.03, 0, 1, 0, j*0.03, 0, 0, 1, 0, 0, 0, 0, 1});

            Matrix pieceLocation = CamToChess*piece;

            setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , 0.0, 1});
            RobotToChessTransformation = Robot*Translation;

            simpleMove(RobotToChessTransformation.at(0,0), RobotToChessTransformation.at(1,0), 0.02);
        }
    }

    int playerTurn = 2;
    img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards5.jpg");
    std::vector<std::string> move = boardLoop(colours[0], colours[1], newCorners, img, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;

    playerTurn = 1;
    img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards6.jpg");
    move = boardLoop(colours[0], colours[1], newCorners, img, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;
    return 0;
}
