#include <iostream>
#include<vector>
#include<string>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <chrono>

#include "validmoves.h"
#include "mainfunctions.h"
#include "CheckersDatabase.h"
#include "robot.h"
#include "alphabeta.h"
#include "vision.h"

//using namespace ur_rtde;
int main(int argc, char** argv) {

    std::string RunMode = "DatabaseSimulation"; // Options are "Evolutions", "RobotWithVision" or "DatabaseSimulation"

    if (RunMode == "Evolutions"){

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("alphaBeta");
        db.setUserName("aksel");  // Change to username
        db.setPassword("password");  // Change to password
        db.open();

        QSqlQuery query;

        // Skriv true i input hvis databasens indhold skal slettes
        resetDB(false); // Resets the database

        //for (int ii = 1; ii <= 100; ++ii) {
        validMoves validMoves;

        std::vector<alphaBeta> alphaBetas;
        // If the database has no entries, create 36 alphaBeta objects
        query.exec("SELECT COUNT(*) FROM points");
        query.next();
        int count = query.value(0).toInt();
        if (count < 36){
            query.exec("SELECT * FROM points");
            for(int i = 0; i < count; i++){
                query.next();
                alphaBetas.push_back(alphaBeta(&validMoves, query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
            }
            for (int i = 0; i < 36-count; i++) {
                alphaBetas.push_back(alphaBeta(&validMoves));
                alphaBetas[i].dbInsert();
            }
        } else {
            // If the database has entries, create 36 alphaBeta objects with the data from the database
            query.exec("SELECT * FROM points");
            int i = 0;
            while(query.next()){
                alphaBetas.push_back(alphaBeta(&validMoves, query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
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
                    int trash = 0;
                    int playerTurn = 1; //Which player's turn it is
                    int blackPieces = 12; //Initial number of black pieces
                    int redPieces = 12; //Initial number of red pieces
                    bool gameEnd = false; //If the game has ended
                    bool draw = false;
                    int thisTurn; //Which player's turn it is
                    int DrawChecker = 1; //When this equal 200 the game is called draw
                    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn

                    // Construct initial board
                    std::vector<std::vector<std::string>> boards = startUp();
                    validMoves.setBoards(boards);
                    validMoves.setPlayerTurn(playerTurn);
                    validMoves.setPieceCount(blackPieces, redPieces);

                    while(true){
                        thisTurn = playerTurn; //Which player's turn it is

                        if(DrawChecker == 175){ // Tjekker om der er gået 175 træk uden en vinder
                            draw = true;
                            break;
                        }

                        //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
                        if((validMoves.movePossible().size()) > 0 && redPieces > 0 && blackPieces > 0){
                            if(playerTurn == 1){
                                //alphaBetas[i].makeMove(boards, 5, playerTurn, redPieces, blackPieces, INT_MIN, INT_MAX, {},trash); //AI's move
                                moveSet = alphaBetas[i].getMove();
                            } else {
                                //alphaBetas[j].makeMove(boards, 5, playerTurn, redPieces, blackPieces, INT_MIN, INT_MAX, {},trash); //AI's move
                                moveSet = alphaBetas[j].getMove();
                            }
                        } else { //If no valid moves, or no more pieces on the board
                            gameEnd = true; //Game has ended
                            break;
                        }
                        playerTurn = validMoves.getPlayerTurn();
                        boards = validMoves.getBoards();
                        blackPieces = validMoves.getPieceCount()[0];
                        redPieces = validMoves.getPieceCount()[1];
                        DrawChecker++;
                    }
                                    // Checks how the game ended and gives points to the winning AI
                   if(gameEnd){
                        if(redPieces == 0){
                            query.prepare("UPDATE winner "
                                          "SET wins = wins + 1 "
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
            query.exec("SELECT points.*, (winner.wins + (winner.draws * 0.33)) AS winrate "
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
                    winners.push_back(alphaBeta(&validMoves, query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
                } else {
                    query.next();
                    remove.push_back(query.value(0).toInt());
                }
                i++;
            }

            winners[0].addWinner();

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
                        alphaBetas.push_back(alphaBeta(&validMoves, query.value(1).toDouble(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toDouble(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toDouble()));
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

    }

    else if (RunMode == "RobotWithVision"){
        for (int ii = 1; ii <= 1; ++ii) {

                int CounterForTempTable = 1;
                int thisTurn = 1;
                int playerTurn = 1; //Which player's turn it is
                int blackPieces = 12; //Initial number of black pieces
                int redPieces = 12; //Initial number of red pieces
                bool gameEnd = false; //If the game has ended
                int thisTurIntern; //Which player's turn it is
                int DrawChecker = 1; //When this equal 200 the game is called draw
                std::vector<std::vector<std::string>> thisBoard = {}; //The current state of the board
                std::string player = "p"; //If the player is human or AI
                std::string player2 = "p"; //If the player is human or AI
                std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
                std::vector<std::vector<double>> startUpRobot; //The initial position of the robotRobot
                std::future<bool> fut;
                std::string MoveMade = {}; // Stores the move made to put it in the database
                bool DatabaseMoveMade = false;
                //std::vector<std::vector<std::string>> boards = startUp();

                std::vector<double> teachPos;


                // Constructs the vision object for ComputerVision
                // AtmegaCom atmegaCom;
                // Robot robot(&atmegaCom);
                // robot.setArguments(argv);
                // robot.prepForPic();
                // Finds the new corners of the chessboard
                // robot.robotStartVision();
                Vision vision(argv);
                vision.firstLoop();
                std::vector<std::vector<std::string>> boards = vision.getBoard();
                validMoves validMoves;
                validMoves.setBoards(boards);
                validMoves.setPlayerTurn(playerTurn);
                validMoves.setPieceCount(blackPieces, redPieces);

                alphaBeta alphaBeta(0);

                int TestCounterForDatabase = 0;

                int i = 0;

                int UniqueBoardIDCounter;

                // Skriv true i nr 2 input hvis temp skal uploades til databasen inden man starter spillet
                // DatabaseInit(UniqueBoardIDCounter,false); //Initializes the database

                while(true){ //Game loop
                    std::string BoardState = "";
                    loadBoardToString(boards,BoardState);

                    std::string* outputPtr = &BoardState;

                    thisTurn = validMoves.getPlayerTurn(); //Which player's turn it is

                    if (DrawChecker == 200){ // Tjekker om der er gået 175 træk uden en vinder
                        //query.exec("UPDATE TempMoves SET WinOrLoss = 0.5"); // Sætter en halv ind i wincase for uafgjort
                        std::cout << "The game is a draw!" << std::endl;
                        break;
                    }

                    //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
                    if((validMoves.movePossible().size()) > 0 && redPieces > 0 && blackPieces > 0){
                        std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is
                        std::vector<std::vector<std::string>> tempBoard = validMoves.getBoards(); // To be used in robotMove

                        if((playerTurn == 1 && player == "p") || (playerTurn == 2 && player2 == "p")){
                            bool valid = false;
                            while(!valid){
                                std::cout << "Please make your move and then press enter: " << std::endl;
                                std::cin.get();
                                // robot.prepForPic();
                                std::vector<std::string> move = vision.boardLoop(boards, playerTurn); // Player's move
                                std::cout << move[0] << " " << move[1] << std::endl;
                                valid = validMoves.DB_move(move[0], move[1]); //Player's move
                                moveSet = move;
                            }
                        } else {
                            if (playerTurn == 1 && player == "DB" || playerTurn == 2 && player2 == "DB"){
                                MoveDBMain(BoardState, playerTurn, boards, redPieces, blackPieces, moveSet, CounterForTempTable, DrawChecker, DatabaseMoveMade, TestCounterForDatabase,validMoves,alphaBeta); // Database AI's move

                            } else if (playerTurn == 1 && player == "Random" || playerTurn == 2 && player2 == "Random"){
                                MoveRandom(moveSet, DatabaseMoveMade, validMoves); // Random move

                            } else if (playerTurn == 1 && player == "AI" || playerTurn == 2 && player2 == "AI"){
                                //alphaBeta.makeMove(boards, 9, playerTurn, redPieces, blackPieces, INT_MIN, INT_MAX, {}, CounterForTempTable); //AI's move
                                moveSet = alphaBeta.getMove();
                            }
                        }

                        playerTurn = validMoves.getPlayerTurn();
                        boards = validMoves.getBoards();
                        blackPieces = validMoves.getPieceCount()[0];
                        redPieces = validMoves.getPieceCount()[1];

                        if(player != "p"){
                            //robot.robotMove(moveSet, tempBoard, thisTurn);
                        }

                        printAIMove(DatabaseMoveMade,moveSet,MoveMade,thisTurn); //Prints the move made by the AI
                        std::string* MoveMadePtr = &MoveMade;
                        InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet
                        DrawChecker++;
                        int depth = 1;
                        printGameState(ii, DrawChecker, redPieces, blackPieces, playerTurn, boards, depth, alphaBeta); //Prints the game state
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
            UploadTempToDatabase(UniqueBoardIDCounter,false); // Uploads the temp table to the database
            std::cout << "Moves made by database: " << TestCounterForDatabase << std::endl;
        }
    }


    else if (RunMode == "DatabaseSimulation"){

        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("CheckersDatabase");
        db.setUserName("IndsætBrugernavn");  // Change to username
        db.setPassword("IndsætPassword");  // Change to password
        db.open();

        QSqlQuery query;


        //Database settings
        bool ResetDB = false; //If the database should be reset set this to true
        bool LoadTempBeforeStart = false; //If there are a full temp table from previous games that should be loaded before the game starts set this to true
        bool UploadTempToDB = true; //If the temp table should be uploaded to the database after the game ends set this to true
        resetDB(ResetDB); // Resets the database
        int UniqueBoardIDCounter;
        int CounterForTempTable = 1;
        int depth = 7; //Depth of the alphaBeta algorithm
        int playerTurn = 1; //Which player's turn it is
        int blackPieces = 12; //Initial number of black pieces
        int redPieces = 12; //Initial number of red pieces
        bool gameEnd = false; //If the game has ended
        int thisTurn; //Which player's turn it is
        int DrawChecker = 1; //When this equal 200 the game is called draw

        std::string player = "DB"; //If the player is human or AI
        std::string player2 = "p"; //If the player is human or AI
        std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
        std::string MoveMade = {}; // Stores the move made to put it in the database
        bool DatabaseMoveMade = false;

        int TestCounterForDatabase = 0;


        for (int ii = 1; ii <= 1; ++ii) {
            validMoves validMoves;
            alphaBeta alphaBeta(&validMoves, 0);
            std::cout << "Game number: " << ii << std::endl;
            CounterForTempTable = 1;
            playerTurn = 1; //Which player's turn it is
            blackPieces = 12; //Initial number of black pieces
            redPieces = 12; //Initial number of red pieces
            gameEnd = false; //If the game has ended
            DrawChecker = 1; //When this equal 200 the game is called draw

            moveSet = {}; //The moves that have been made during the turn
            MoveMade = {}; // Stores the move made to put it in the database

            thisTurn = playerTurn; //Which player's turn it is
            validMoves.setPlayerTurn(playerTurn);
            validMoves.setPieceCount(blackPieces, redPieces);

            int i = 0;

            int UniqueBoardIDCounter;
            // Skriv true i nr 2 input hvis temp skal uploades til databasen inden man starter spillet
            DatabaseInit(UniqueBoardIDCounter,LoadTempBeforeStart); //Initializes the database
            RefreshTempTable(); // Refreshes the Temp table
            // Construct initial board
            std::vector<std::vector<std::string>> boards = startUp();
            validMoves.setBoards(boards);
            while(true){ //Game loop
                std::string BoardState = "";
                loadBoardToString(boards,BoardState);


                std::string* outputPtr = &BoardState;

                thisTurn = playerTurn; //Which player's turn it is

                if (DrawChecker == 201){ // Tjekker om der er gået 175 træk uden en vinder
                    query.exec("UPDATE TempMoves SET WinOrLoss = 0.35"); // Sætter en halv ind i wincase for uafgjort
                    std::cout << "The game is a draw!" << std::endl;
                    break;
                }


                //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
                if((validMoves.movePossible().size()) > 0 && redPieces > 0 && blackPieces > 0){
                    //std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is
                    std::vector<std::vector<std::string>> tempBoard = boards; // To be used in robotMove

                    if((playerTurn == 1 && player == "p") || (playerTurn == 2 && player2 == "p")){

                        checkerBoard(boards);
                        while(!validMoves.move()){} //Player's move

                    } else {
                        if (playerTurn == 1 && player == "DB" || playerTurn == 2 && player2 == "DB"){

                            MoveDBMain(BoardState, playerTurn, boards, redPieces, blackPieces, moveSet, CounterForTempTable, DrawChecker, DatabaseMoveMade, TestCounterForDatabase,validMoves,alphaBeta); // Database AI's move

                        }
                        else if (playerTurn == 1 && player == "Random" || playerTurn == 2 && player2 == "Random"){

                            //checkerBoard(boards);
                            MoveRandom(moveSet, DatabaseMoveMade, validMoves); // Random move

                        }
                        else if (playerTurn == 1 && player == "AI" || playerTurn == 2 && player2 == "AI"){
                            CounterForTempTable = 0;
                            //checkerBoard(boards);
                            alphaBeta.makeMove(boards, depth, playerTurn, blackPieces, redPieces, INT_MIN, INT_MAX, {}, CounterForTempTable); //AI's move
                            moveSet = alphaBeta.getMove();
                        }
                    }

                    moveSet = validMoves.getMove();
                    playerTurn = validMoves.getPlayerTurn();
                    boards = validMoves.getBoards();
                    blackPieces = validMoves.getPieceCount()[0];
                    redPieces = validMoves.getPieceCount()[1];

                    // Skriv true i første input for at køre robotten
                    // MoveRobot(false,fut,tempBoard,thisTurn,moveSet,startUpRobot,i); //Robot movement

                    //printAIMove(DatabaseMoveMade,moveSet,MoveMade,thisTurn); //Prints the move made by the AI

                    MoveMade = moveSet[0]+moveSet[1];
                    std::string *MoveMadePtr = &MoveMade;

                    InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet

                    //printGameState(ii,DrawChecker,redPieces,blackPieces,playerTurn,boards,depth,alphaBeta); //Prints the game state


                    DrawChecker++;
                    i++;

                } else { //If no valid moves, or no more pieces on the board
                    //checkerBoard(boards);
                    gameEnd = true; //Game has ended
                    break;
                }
            }

            //Prints the winner of the game
            if(gameEnd){
                GameEnd(redPieces,blackPieces,playerTurn);
            }

            UploadTempToDatabase(UniqueBoardIDCounter, UploadTempToDB); // Uploads the temp table to the database
        }

    }

    else if (RunMode == "SimOnly"){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("IndsætBrugernavn");  // Change to username
    db.setPassword("IndsætPassword!");  // Change to password
    db.open();

    QSqlQuery query;
    /*
        for (int i = 1; i <= 200; i++) {
            query.prepare("INSERT INTO SimMovesP1 "
                          "(MoveDepth, MoveChoise)"
                          "Values"
                          "(:MoveDepth, :MoveChoise)");
            query.bindValue(":MoveDepth", i);
            query.bindValue(":MoveChoise", 1);
            query.exec();

            query.prepare("INSERT INTO SimMovesP2 "
                          "(MoveDepth, MoveChoise)"
                          "Values"
                          "(:MoveDepth, :MoveChoise)");
            query.bindValue(":MoveDepth", i);
            query.bindValue(":MoveChoise", 1);
            query.exec();

        }
        */

    //Database settings
    bool ResetDB = false; //If the database should be reset set this to true
    bool LoadTempBeforeStart = false; //If there are a full temp table from previous games that should be loaded before the game starts set this to true
    bool UploadTempToDB = false; //If the temp table should be uploaded to the database after the game ends set this to true

    resetDB(ResetDB); // Resets the database
    int TestCounterForDatabase = 0;

    int CounterForTempTable = 1;
    int UniqueBoardIDCounter;
    // Skriv true i nr 2 input hvis temp skal uploades til databasen inden man starter spillet
    DatabaseInit(UniqueBoardIDCounter,LoadTempBeforeStart); //Initializes the database


    for (int ii = 1; ii <= 10000000; ++ii) {

        int depth = 6; //Depth of the alphaBeta algorithm
        int playerTurn = 1; //Which player's turn it is
        int blackPieces = 12; //Initial number of black pieces
        int redPieces = 12; //Initial number of red pieces
        bool gameEnd = false; //If the game has ended
        int thisTurn; //Which player's turn it is
        int DrawChecker = 1; //When this equal 200 the game is called draw
        std::string player = "Simu"; //If the player is human or AI
        std::string player2 = "Simu"; //If the player is human or AI
        std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
        std::string MoveMade = {}; // Stores the move made to put it in the database
        bool DatabaseMoveMade = false;
        validMoves validMovesHolder;

        validMoves validMoves = validMovesHolder;

        alphaBeta alphaBeta(&validMoves,0);
        std::vector<int> Player1SimChoise;
        std::vector<int> Player2SimChoise;
        int Player1MoveCount = 0;
        int Player2MoveCount = 0;
        bool SimuIncreased = false;
        std::vector<std::string> MovePossibleForSimu;
        LoadSimVectors(Player1SimChoise,Player2SimChoise);


        int i = 0;

        validMoves.setPlayerTurn(1);
        // Construct initial board
        std::vector<std::vector<std::string>> boards = startUp();
        validMoves.setBoards(boards);

        while(true){ //Game loop

            std::string BoardState = "";
            loadBoardToString(boards,BoardState);

            std::string* outputPtr = &BoardState;

            thisTurn = playerTurn; //Which player's turn it is

            if (DrawChecker == 175){ // Tjekker om der er gået 175 træk uden en vinder
                query.exec("UPDATE TempMoves SET WinOrLoss = 0.5"); // Sætter en halv ind i wincase for uafgjort
                break;
            }
            MovePossibleForSimu.clear();
            MovePossibleForSimu = validMoves.movePossible();

            //Checks if the game has ended either by player not having any possible moves or no more pieces on the board
            if((MovePossibleForSimu.size()) > 0 && redPieces > 0 && blackPieces > 0){
                //std::cout << "Player " << playerTurn << "'s turn:" << std::endl; //Prints which player's turn it is

                if(playerTurn == 1){
                    if(MovePossibleForSimu.size() > Player1SimChoise[Player1MoveCount]*2){
                        SimMove(moveSet, DatabaseMoveMade, validMoves, playerTurn, Player1SimChoise, Player1MoveCount,MovePossibleForSimu);
                        Player1MoveCount++;
                    }
                    else{

                        if(DrawChecker == 1){
                            //std::cout << "All simus for current oponent has been used, increase oponents simu" << std::endl;
                            query.exec("UPDATE SimMovesP1 set MoveChoise = 0");
                            query.exec("UPDATE SimMovesP2 set MoveChoise = MoveChoise+1 where MoveDepth = 1");
                            UploadTempToDatabase(UniqueBoardIDCounter, UploadTempToDB); // Uploads the temp table to the database
                            MoveRandom(moveSet, DatabaseMoveMade, validMoves); // Random move
                        }
                        else{
                            IncreaseSimu(Player1MoveCount,SimuIncreased,Player1SimChoise);
                            SimMove(moveSet, DatabaseMoveMade, validMoves, playerTurn, Player1SimChoise, Player1MoveCount,MovePossibleForSimu);
                            Player1MoveCount++;
                        }

                    }
                }
                else if (playerTurn == 2){
                    if(MovePossibleForSimu.size() > Player2SimChoise[Player2MoveCount]*2){
                        SimMove(moveSet, DatabaseMoveMade, validMoves, playerTurn, Player2SimChoise, Player2MoveCount,MovePossibleForSimu);
                        Player2MoveCount++;
                    }
                    else{
                        std::cout << "Du kom herind" << std::endl;
                        IncreaseOponentSimu(Player2MoveCount,Player2SimChoise);
                        SimMove(moveSet, DatabaseMoveMade, validMoves, playerTurn, Player2SimChoise, Player2MoveCount,MovePossibleForSimu);
                        Player2MoveCount++;
                    }
                }


                playerTurn = validMoves.getPlayerTurn();
                boards = validMoves.getBoards();
                blackPieces = validMoves.getPieceCount()[0];
                redPieces = validMoves.getPieceCount()[1];

                MoveMade = moveSet[0]+moveSet[1];
                std::string *MoveMadePtr = &MoveMade;
                //printAIMove(DatabaseMoveMade,moveSet,MoveMade,thisTurn); //Prints the move made by the AI

                //printGameState(ii,DrawChecker,redPieces,blackPieces,playerTurn,boards,depth,alphaBeta); //Prints the game state

                //InsertToTemp(*outputPtr, *MoveMadePtr, CounterForTempTable, thisTurn);  // Indsætter rykket hvis det ikke er en kopi af et move den allerede har lavet i spillet

                DrawChecker++;
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
        if(ii%100 == 0){
            std::cout << "Game number: " << ii << std::endl;
        }


        IncreaseSimu(Player1MoveCount-1,SimuIncreased,Player1SimChoise);
    }
}

    else {
        std::cout << "Invalid RunMode" << std::endl;
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
