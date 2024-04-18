#include "mainfunctions.h"
#include "boardUpdate.h"
#include "CheckersDatabase.h"
#include "validmoves.h"
#include "AtmegaCom.h"
#include "robotMove.h"
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

void resetDB(bool choise){
    if(choise == true){
        QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
        QSqlQuery query = QSqlQuery(db);

        query.exec("DELETE FROM MovesP1 WHERE board_id >= 0");
        query.exec("DELETE FROM MovesP2 WHERE board_id >= 0");
        query.exec("DELETE FROM UniqueBoard WHERE board_id >= 0");
        query.exec("ALTER TABLE UniqueBoard AUTO_INCREMENT = 1");
    }


}


void DatabaseInit(int& UniqueBoardIDCounter, bool UploadTemp){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    query.exec("select board_id from UniqueBoard order by board_id desc limit 1");
    query.first();
    UniqueBoardIDCounter = query.value(0).toInt() + 1;

    //Til hvis temp er fuld og skal uploades inden den bliver slettet
    if(UploadTemp == true){
        std::cout << "Startet" << std::endl;
        UploadTempToDatabase(UniqueBoardIDCounter); // Uploads the temp table to the database
        std::cout << "Uploaded" << std::endl;
    }
    RefreshTempTable(); // Refreshes the Temp table

}

void loadBoardToString(std::vector<std::vector<std::string>> boards, std::string& output){


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

}

void MoveDBMain(std::string& BoardState, int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::vector<std::string>& moveSet, std::string& MoveMade, int& CounterForTempTable, int& DrawChecker, bool& DatabaseMoveMade, int& TestCounterForDatabase, validMoves validm, alphaBeta alphab){


    std::string DBmove = MovePlayer(BoardState, playerTurn); // Database best move on current board
    if (DBmove == "No moves"){
        std::cout << "No moves found" << std::endl;
        alphab.moveAI(boards, 1, playerTurn, redPieces, blackPieces,boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, playerTurn, {},CounterForTempTable); //AI's move
    }
    else{
        std::cout << "AI move from database: " << DBmove << std::endl;
        std::string DBmoveFrom = DBmove.substr(0,2);
        std::string DBmoveTo = DBmove.substr(2,2);
        validm.DB_move(playerTurn, boards, redPieces, blackPieces, DBmoveFrom, DBmoveTo); //Database AI's move
        MoveMade = DBmove;
        TestCounterForDatabase++;
        DatabaseMoveMade = true;

    }
}

void MoveRandom(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::vector<std::string>& moveSet, std::string& MoveMade, bool& DatabaseMoveMade, std::vector<std::string>& jumps, bool moreMove, std::string moveTo, validMoves validm){
    std::vector<std::string> MovesToPickFrom;
    std::vector<std::string> PossibleJumps = validm.movePossible(playerTurn, boards, jumps, moreMove, moveTo);
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
    std::string moveTo2 = ChosenMove.substr(2,2);
    validm.DB_move(playerTurn, boards, redPieces, blackPieces, moveFrom, moveTo2);
    MoveMade = ChosenMove;
    DatabaseMoveMade = true;
}


void MoveRobot(bool RunChecker,std::future<bool>& fut, std::vector<std::vector<std::string>>& tempBoard, int& thisTurn, std::vector<std::string>& moveSet, std::vector<std::vector<double>>& startUpRobot, int& i){

    if (RunChecker == true){
        if (i > 0){
            fut.get();
        }



        // Moves the robot
        if(i == 0){
            // Set up the robot
            atmegaCom('6'); // Sender et signal for at reset hvis gripperen er stoppet midt i et træk
            sleep(1); // Venter 1 sekund
            atmegaCom('8'); // Sender et signal for at gripperen skal åbne
            fut = std::async(robotMove, moveSet, startUpRobot, tempBoard, thisTurn);
        } else {
            fut = std::async(robotMove, moveSet, startUpRobot, tempBoard, thisTurn);
        }
    }

}

void printAIMove(bool& DatabaseMoveMade, std::vector<std::string>& moveSet, std::string& MoveMade, int& thisTurn){
    //Prints the moves made by the AI
    if(!DatabaseMoveMade){
        for (int i = 0; i < moveSet.size(); i += 2) {
            std::cout << "Player " << thisTurn << "  moves from: " << moveSet[i] << std::endl;
            std::cout << "Player " << thisTurn << " moves to: " << moveSet[i+1] << std::endl;
            MoveMade = moveSet[i] + moveSet[i+1];
        }
    }
    DatabaseMoveMade = false;
}

void printGameState(int ii, int DrawChecker, int redPieces, int blackPieces, int playerTurn, std::vector<std::vector<std::string>>& boards, int depth, alphaBeta alphab){
    //Prints data from the state of the game and prints the board
    std::cout << "It is game nr: " << ii << std::endl;
    std::cout << "It is turn: " << DrawChecker << std::endl;
    std::cout << "There are " << redPieces << " red pieces left." << std::endl;
    std::cout << "There are " << blackPieces << " black pieces left." << std::endl;
    std::cout << std::endl;
    checkerBoard(boards);
    std::cout << "Game score is: " << alphab.giveScoreAI(boards, playerTurn, blackPieces, redPieces, depth) << std::endl;
    std::cout << std::endl;
}


void GameEnd(int redPieces, int blackPieces, int playerTurn){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

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
