
#include <iostream>
#include<vector>
#include<string>
#include "boardUpdate.h"
#include "qa.hpp"
#include "validmoves.h"

#include "mainfunctions.h"
#include "CheckersDatabase.h"
#include "computerVision.h"
//#include "robotMove.h"
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

//#include <future>




//using namespace ur_rtde;

int main(int argc, char** argv) {

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("IndsætBrugernavn");  // Change to username
    db.setPassword("IndsætPassword!");  // Change to password
    db.open();

    QSqlQuery query;

    // Skriv true i input hvis databasens indhold skal slettes
    resetDB(false); // Resets the database
    /*
    for (int ii = 1; ii <= 100; ++ii) {

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
                alphaBeta alphaBeta(4);
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
    */


    for (int ii = 1; ii <= 1; ++ii) {

            int CounterForTempTable = 1;

            int playerTurn = 2; //Which player's turn it is
            int blackPieces = 12; //Initial number of black pieces
            int redPieces = 12; //Initial number of red pieces
            bool gameEnd = false; //If the game has ended
            int thisTurn; //Which player's turn it is
            int DrawChecker = 1; //When this equal 200 the game is called draw
            std::vector<std::vector<std::string>> thisBoard = {}; //The current state of the board
            std::string player = "AI"; //If the player is human or AI
            std::string player2 = "p"; //If the player is human or AI
            std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
            std::vector<std::vector<double>> startUpRobot; //The initial position of the robot
            std::future<bool> fut;
            std::string MoveMade; // Stores the move made to put it in the database
            bool DatabaseMoveMade = false;
            validMoves validMoves;
            alphaBeta alphaBeta(4);

            std::vector<double> teachPos;
            //prepForPic(true, teachPos);

            // Loads in the image
            cv::Mat img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/Checker/V1.0/build/Desktop-Debug/main1.jpg");

            // Variables that is needed for the robot movement
            std::vector<cv::Point2f> newCorners;
            std::vector<cv::Point2f> calibrate;
            double pixToMeters;
            double boardSize;

            // The chessboard
            std::vector<std::vector<std::string>> boards;

            // Finds the new corners of the chessboard
            std::vector<Vec3b> colours = firstLoop(newCorners, img, boards, calibrate, pixToMeters, boardSize);

            // Robot movement
            std::cout << calibrate[0] << std::endl;
            std::cout << calibrate[1] << std::endl;
            std::cout << calibrate[2] << std::endl;

            //std::vector<std::vector<double>> startUp = robotStartVision(newCorners, calibrate, boardSize, pixToMeters);


            int TestCounterForDatabase = 0;

            int i = 0;

            int UniqueBoardIDCounter;
            // Skriv true i nr 2 input hvis temp skal uploades til databasen inden man starter spillet
            DatabaseInit(UniqueBoardIDCounter,false); //Initializes the database

            // Construct initial board
            //std::vector<std::vector<std::string>> boards = startUp();

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

                std::vector<std::string> jumps = validMoves.jumpPossible(playerTurn, boards);
                bool moreMove = false;
                std::string moveTo = "";


                //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
                if(((validMoves.movePossible(playerTurn, boards, jumps, moreMove, moveTo).size())/2) > 0 && redPieces > 0 && blackPieces > 0){
                    std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is
                    std::vector<std::vector<std::string>> tempBoard = boards; // To be used in robotMove

                    if((playerTurn == 1 && player == "p") || (playerTurn == 2 && player2 == "p")){
                        bool valid = false;
                        while(!valid){
                            //prepForPic(false, teachPos);
                            img.empty();
                            img = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/Checker/V1.0/build/Desktop-Debug/main0.jpg"); // Loads in the image
                            std::vector<std::string> move = boardLoop(colours[0], colours[1], newCorners, img, boards, playerTurn, pixToMeters); // Player's move
                            std::cout << move[0] << " " << move[1] << std::endl;

                            valid = validMoves.DB_move(playerTurn, boards, redPieces, blackPieces, move[0], move[1]); //Player's move
                            moveSet = move;
                        }

                    } else {
                        if (playerTurn == 1 && player == "DB" || playerTurn == 2 && player2 == "DB"){

                            MoveDBMain(BoardState, playerTurn, boards, redPieces, blackPieces, moveSet, MoveMade, CounterForTempTable, DrawChecker, DatabaseMoveMade, TestCounterForDatabase,validMoves,alphaBeta); // Database AI's move
                        }
                        else if (playerTurn == 1 && player == "Random" || playerTurn == 2 && player2 == "Random"){

                            MoveRandom(playerTurn, boards, redPieces, blackPieces, moveSet, MoveMade, DatabaseMoveMade, jumps, moreMove, moveTo,validMoves); // Random move

                        }
                        else if (playerTurn == 1 && player == "AI" || playerTurn == 2 && player2 == "AI"){
                            alphaBeta.moveAI(boards, 2, playerTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {},CounterForTempTable); //AI's move
                        }
                    }

                    // Skriv true i første input for at køre robotten
                    MoveRobot(false ,fut,tempBoard,thisTurn,moveSet,startUpRobot,i); //Robot movement

                    printAIMove(DatabaseMoveMade,moveSet,MoveMade,thisTurn); //Prints the move made by the AI


                    std::string* MoveMadePtr = &MoveMade;

                    InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet




                    DrawChecker++;


                    int depth = 7;

                    printGameState(ii,DrawChecker,redPieces,blackPieces,playerTurn,boards,depth,alphaBeta); //Prints the game state


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


/*


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
