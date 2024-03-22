#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "CheckersDatabase.h"

void UpdateDatabaseFromTemp()
{
    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    //printBoardStates();

    std::vector<int> TempBoardID;
    TempBoardID.clear();

    query.exec("SELECT tempboard_id FROM Temp");
    while (query.next()) {
        int BoardID = query.value(0).toInt();
        TempBoardID.push_back(BoardID);
    }

    for (int i = 0; i < TempBoardID.size(); i++) {
        AddBoard(TempBoardID[i]);
    }
    // Clear temp
    query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");



    return;
}





void AddBoard(int& TempBoardID){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);


    std::string BoardStateInputtet;

    query.exec("Select BoardState FROM Temp WHERE tempBoard_id = " + QString::number(TempBoardID));
    while (query.next()) {
        BoardStateInputtet = query.value(0).toString().toStdString();
    }

    std::vector<std::string> OldBoardState;
    OldBoardState.clear();

    query.exec("SELECT BoardState FROM UniqueBoard");
    while (query.next()) {
        std::string BoardState = query.value(0).toString().toStdString();
        OldBoardState.push_back(BoardState);
    }


    if (OldBoardState.size() == 0){
        int newBoardID = OldBoardState.size()+1;
        query.prepare("INSERT INTO UniqueBoard ( board_id, BoardState) "
                      "VALUES (:board_id, :BoardState)");
        query.bindValue(":board_id", newBoardID);
        query.bindValue(":BoardState", QString::fromStdString(BoardStateInputtet));
        query.exec();
    }
    else{
        // Det er her den dør Pt
        for (int i = 0; i <= OldBoardState.size(); i++) {
            if (BoardStateInputtet == OldBoardState[i]) {
                AddMove(TempBoardID);
                return;

            }

            else if (i == OldBoardState.size()){

                int newBoardID = OldBoardState.size()+1;
                query.prepare("INSERT INTO UniqueBoard ( board_id, BoardState) "
                              "VALUES (:board_id, :BoardState)");
                query.bindValue(":board_id", newBoardID);
                query.bindValue(":BoardState", QString::fromStdString(BoardStateInputtet));
                query.exec();
                AddMove(TempBoardID);
            }
        }
    }

}

void AddMove(int& TempBoardID){


    //Declare variables
    int BoardID = 0;
    int WinChecker = 0;

    std::string BoardStateInputtet;


    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    if (TempBoardID == 1){
        return;
    }

    query.exec("Select BoardState FROM Temp WHERE tempBoard_id = " + QString::number(TempBoardID-1));
    while (query.next()) {
        BoardStateInputtet = query.value(0).toString().toStdString();
    }

    query.prepare("SELECT board_id FROM UniqueBoard WHERE BoardState = :boardState");
    query.bindValue(":boardState", BoardStateInputtet.c_str());
    query.exec();
    while (query.next()) {
        BoardID = query.value(0).toInt();
    }

    std::string MoveToCheck;

    query.exec("Select Move FROM Temp WHERE tempBoard_id = " + QString::number(TempBoardID));
    while (query.next()) {
        MoveToCheck = query.value(0).toString().toStdString();
    }

    std::vector<std::string> OldMoves;
    OldMoves.clear();

    query.exec("SELECT Move FROM Moves WHERE board_id = " + QString::number(BoardID));
    while (query.next()) {
        std::string Move = query.value(0).toString().toStdString();
        OldMoves.push_back(Move);
    }

    query.exec("Select WinOrLoss FROM Temp WHERE tempBoard_id = " + QString::number(TempBoardID));
    while (query.next()) {
        WinChecker = query.value(0).toInt();
    }

    if (OldMoves.size() == 0){
        query.prepare("INSERT INTO Moves ( board_id, Move, WinRate, WinCases, UseCases) "
                      "VALUES (:board_id, :Move, :WinRate, :WinCases, 1)");
        query.bindValue(":board_id", BoardID);
        query.bindValue(":Move", MoveToCheck.c_str());
        query.bindValue(":WinRate", WinChecker*100);
        query.bindValue(":WinCases", WinChecker);
        query.exec();




    }

    else{

        for (int i = 0; i <= OldMoves.size(); i++) {
            if (MoveToCheck == OldMoves[i]) {
                double WinCases = 0;
                double UseCases = 0;
                double WinRate = 0;
                query.prepare("UPDATE Moves SET "
                              " WinCases = WinCases + :WinCases,"
                              " UseCases = UseCases + 1 "
                              " WHERE board_id = :board_id AND Move = :Move");
                query.bindValue(":WinCases", WinChecker);
                query.bindValue(":board_id", BoardID);
                query.bindValue(":Move", MoveToCheck.c_str());
                query.exec();


                query.prepare("SELECT Wincases, UseCases FROM Moves "
                              " WHERE board_id = :board_id AND Move = :Move");
                query.bindValue(":board_id", BoardID);
                query.bindValue(":Move", MoveToCheck.c_str());
                query.exec();
                while (query.next()) {
                    WinCases = query.value(0).toDouble();
                    UseCases = query.value(1).toDouble();
                }
                WinRate = (WinCases/UseCases)*100;

                query.prepare("UPDATE Moves SET "
                              " WinRate = :WinRate"
                              " WHERE board_id = :board_id AND Move = :Move");
                query.bindValue(":WinRate", WinRate);
                query.bindValue(":board_id", BoardID);
                query.bindValue(":Move", MoveToCheck.c_str());
                query.exec();




                return;

            }

            else if (i == OldMoves.size()){

                query.prepare("INSERT INTO Moves ( board_id, Move, WinRate, WinCases, UseCases) "
                              "VALUES (:board_id, :Move, :WinRate, :WinCases, 1)");
                query.bindValue(":board_id", BoardID);
                query.bindValue(":Move", MoveToCheck.c_str());
                query.bindValue(":WinRate", WinChecker*100);
                query.bindValue(":WinCases", WinChecker);
                query.exec();



            }
        }
    }

}
void InsertToTemp(std::string& BoardState, std::string& Move, int& Counter,int PlayerId){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    query.prepare("INSERT INTO Temp (tempBoard_id, BoardState, Move, PlayerID, WinOrLoss) "
                  "VALUES (:tempBoard_id, :BoardState, :Move, :PlayerID, :WinOrLoss)");
    query.bindValue(":tempBoard_id", Counter);
    query.bindValue(":BoardState", QString::fromStdString(BoardState));
    query.bindValue(":Move", QString::fromStdString(Move));
    query.bindValue(":PlayerID", PlayerId);

    query.exec();

    Counter++;
}
