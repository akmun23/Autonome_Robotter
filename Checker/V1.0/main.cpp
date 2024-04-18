#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "computerPos.h"
#include "qa.hpp"
//#include "robotMove.h"
#include "validmoves.h"
#include "CheckersDatabase.h"
#include "computerVision.h"
#include "matrix.h"
#include "alphabeta.h"

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

int main(int argc, char** argv) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("alphaBeta");
    db.setUserName("aksel");  // Change to username
    db.setPassword("password");  // Change to password
    db.open();

    QSqlQuery query;

    std::vector<alphaBeta> alphaBetas;
    // If the database has no entries, create 36 alphaBeta objects
    query.exec("SELECT COUNT(*) FROM points");
    query.next();
    int count = query.value(0).toInt();
    if (count < 36){
        query.exec("SELECT * FROM points");
        for(int i = 0; i < count; i++){
            query.next();
            alphaBetas.push_back(alphaBeta(query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
        }
        for (int i = 0; i < 36-count; i++) {
            alphaBetas.push_back(alphaBeta());
            alphaBetas[i].dbInsert();
        }
    } else {
        // If the database has entries, create 36 alphaBeta objects with the data from the database
        query.exec("SELECT * FROM points");
        int i = 0;
        while(query.next()){
            alphaBetas.push_back(alphaBeta(query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
            i++;
        }
    }

    for(int i = 0; i < alphaBetas.size(); i++){
        alphaBetas[i].resetWins();
    }

    double evoRate = 0.3;
    while(true){ //Game loop
        for(int i = 0; i < alphaBetas.size(); i++){
            for (int j = 0; j < alphaBetas.size(); ++j) {
                int playerTurn = 1; //Which player's turn it is
                int blackPieces = 12; //Initial number of black pieces
                int redPieces = 12; //Initial number of red pieces
                bool gameEnd = false; //If the game has ended
                bool draw = false;
                int thisTurn; //Which player's turn it is
                int DrawChecker = 1; //When this equal 200 the game is called draw
                std::vector<std::vector<std::string>> thisBoard = {}; //The current state of the board
                std::string player = "AI"; //If the player is human or AI
                std::string player2 = "AI"; //If the player is human or AI
                std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
                validMoves validMoves;
                // Construct initial board
                std::vector<std::vector<std::string>> boards = startUp();

                while(true){
                    thisTurn = playerTurn; //Which player's turn it is

                    if(DrawChecker == 175){ // Tjekker om der er gået 175 træk uden en vinder
                        draw = true;
                        break;
                    }
                    std::vector<std::string> jumps = validMoves.jumpPossible(playerTurn, boards);
                    bool moreMove = false;
                    std::string moveTo = "";

                    //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
                    if(((validMoves.movePossible(playerTurn, boards, jumps, moreMove, moveTo).size())/2) > 0 && redPieces > 0 && blackPieces > 0){
                        std::vector<std::vector<std::string>> tempBoard = boards; // To be used in robotMove
                        if(playerTurn == 1){
                            alphaBetas[i].moveAI(boards, 5, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {}); //AI's move
                        } else {
                            alphaBetas[j].moveAI(boards, 5, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {}); //AI's move
                        }
                    } else { //If no valid moves, or no more pieces on the board
                        gameEnd = true; //Game has ended
                        break;
                    }
                    DrawChecker++;
                }
                // Checks how the game ended and gives points to the winning AI
               if(gameEnd){
                    if(redPieces == 0){
                        query.prepare("UPDATE winner "
                                      "SET wins = wins + 1"
                                      "WHERE ai_id = :id");
                        query.bindValue(":id", alphaBetas[i].getId());
                        query.exec();
                    } else if(blackPieces == 0){
                        query.prepare("UPDATE winner "
                                      "SET wins = wins + 1 "
                                      "WHERE ai_id = :id");
                        query.bindValue(":id", alphaBetas[j].getId());
                        query.exec();
                    } else if(playerTurn == 1){
                        query.prepare("UPDATE winner "
                                      "SET wins = wins + 1 "
                                      "WHERE ai_id = :id");
                        query.bindValue(":id", alphaBetas[j].getId());
                        query.exec();;
                    } else if(playerTurn == 2){
                        query.prepare("UPDATE winner "
                                      "SET wins = wins + 1 "
                                      "WHERE ai_id = :id");
                        query.bindValue(":id", alphaBetas[i].getId());
                        query.exec();
                    }
                } else if(draw){
                    query.prepare("UPDATE winner "
                                  "SET draws = draws + 1 "
                                  "WHERE ai_id = :id");
                    query.bindValue(":id", alphaBetas[i].getId());
                    query.exec();

                    query.prepare("UPDATE winner "
                                  "SET draws = draws + 1 "
                                  "WHERE ai_id = :id");
                    query.bindValue(":id", alphaBetas[j].getId());
                    query.exec();
                }
                std::cout << "Winners updated: " << j+i*36 << std::endl;
            }
        }

        // Find the 4 best AI's with wins counting as 1 point and draws counting as 0.5 points
        query.exec("SELECT points.*, (winner.wins + (winner.draws * 0.5)) AS winrate "
                   "FROM points "
                   "JOIN winner ON points.ai_id = winner.ai_id "
                   "ORDER BY winrate DESC; "
                   );

        std::cout << "The 4 best AI's have been found" << std::endl;
        // Copy the 4 best AI's into new alphaBeta objects and delete the rest
        int i = 0;

        std::vector<alphaBeta> winners;

        int size = query.size();
        std::vector<int> remove;

        while(i < size){
            if(i < 4){
                query.next();
                winners.push_back(alphaBeta(query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
            } else {
                query.next();
                remove.push_back(query.value(0).toInt());
            }
            i++;
        }

        for(int i = 0; i < remove.size(); i++){
            query.prepare("DELETE FROM winner "
                          "WHERE ai_id = :id");
            query.bindValue(":id", remove[i]);
            query.exec();

            query.prepare("DELETE FROM points "
                          "WHERE ai_id = :id");
            query.bindValue(":id", remove[i]);
            query.exec();
        }

        alphaBetas = {};
        alphaBetas.clear();

        // Create 32 new alphaBeta objects with the data from the 4 best AI's
        query.exec("SELECT COUNT(*) "
                   "FROM points");
        query.next();
        count = query.value(0).toInt();

        if(count == 4){
            alphaBetas = winners;
            query.exec("SELECT * FROM points");
           while(query.next()) {
                for (int i = 0; i < 8; i++) {
                    alphaBetas.push_back(alphaBeta(query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
                }
            }
            // Evolve the 32 new alphaBeta objects
            for (int k = 4; k < 36; ++k) {
                alphaBetas[k].dbInsert();
                alphaBetas[k].evolve(evoRate);
            }
             std::cout << "The 32 new AI's have been evolved" << std::endl;

            for(int i = 0; i < alphaBetas.size(); i++){
                alphaBetas[i].resetWins();
            }
        } else {
            std::cout << "Delete failed" << std::endl;
        }
        evoRate *= 0.9;
    }

    //

    //Det her er er til vis man vil reset dataen i databasen
    /*
    query.exec("DELETE FROM MovesP1 WHERE board_id >= 0");
    query.exec("DELETE FROM MovesP2 WHERE board_id >= 0");
    query.exec("DELETE FROM UniqueBoard WHERE board_id >= 0");
    query.exec("ALTER TABLE UniqueBoard AUTO_INCREMENT = 1");
    query.exec("INSERT INTO UniqueBoard (BoardState) VALUES ('22222222222211111111444444444444')");
    */

    /*
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
                std::vector<std::string> jumps = jumpPovalidssible(playerTurn, boards);
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
    */

/*
    // Loads in the image
    cv::Mat img = cameraFeed(argv);
    // Show the image taken
    imshow("Image", img);

    // Variables that is needed for the robot movement
    std::vector<cv::Point2f> newCorners;
    std::vector<cv::Point2f> calibrate;

    // The chessboard
    std::vector<std::vector<std::string>> chessBoard;

    // Finds the new corners of the chessboard
    std::vector<Vec3b> colours = firstLoop(newCorners, img, chessBoard, calibrate);

    // Robot movement
    std::cout << calibrate[0] << std::endl;
    std::cout << calibrate[1] << std::endl;
    std::cout << calibrate[2] << std::endl;

    // std::vector<std::vector<double>> startUp = robotStartVision(newCorners, calibrate, boardSize);

    int playerTurn = 1;
    // robotMove({"c3", "e5"}, startUp, chessBoard, playerTurn);

    playerTurn = 2;
    img = cameraFeed(argv);
    std::vector<std::string> move = boardLoop(colours[0], colours[1], newCorners, img, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;

    playerTurn = 1;
    img = cameraFeed(argv);
    move = boardLoop(colours[0], colours[1], newCorners, img, chessBoard, playerTurn);
    std::cout << move[0] << " " << move[1] << std::endl;
*/
    return 0;
}
