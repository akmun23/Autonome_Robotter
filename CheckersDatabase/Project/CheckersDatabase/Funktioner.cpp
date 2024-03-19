#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "Funktioner.h"

void printBoardStates(){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    query.exec("SELECT * FROM UniqueBoard");
    while (query.next()) {
        int BoardID = query.value(0).toInt();
        QString BoardState = query.value(1).toString();
        qDebug() << "BoardID:" << BoardID << "BoardState:" << BoardState;
    }
}


void AddBoard(int TempBoardID){

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
        query.bindValue(":BoardState", BoardStateInputtet.c_str());
        query.exec();
    }
    else{

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
                query.bindValue(":BoardState", BoardStateInputtet.c_str());
                query.exec();
            }
        }
    }

}

void AddMove(int TempBoardID){



    //Declare variables
    int BoardID = 0;
    std::string BoardStateInputtet;


    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

    //BoardStateInputtet sæt den her lig noget

    query.exec("Select BoardState FROM Temp WHERE tempBoard_id = " + QString::number(TempBoardID));
    while (query.next()) {
        BoardStateInputtet = query.value(0).toString().toStdString();
    }

    query.exec("SELECT board_id FROM UniqueBoard WHERE BoardState = '" + QString::fromStdString(BoardStateInputtet) + "'");
    while (query.next()) {
        BoardID = query.value(0).toInt();
    }

    std::cout << "BoardID: " << BoardID << std::endl;

    std::string MoveToCheck;

    query.exec("Select Move FROM Temp WHERE tempBoard_id = " + QString::number(TempBoardID));
    while (query.next()) {
        MoveToCheck = query.value(0).toString().toStdString();
    }

    std::vector<std::string> OldMoves;
    OldMoves.clear();

    query.exec("SELECT Move FROM Moves WHERE board_id = " + QString::number(BoardID));
    while (query.next()) {
        std::string BoardState = query.value(0).toString().toStdString();
        OldMoves.push_back(BoardState);
    }


    if (OldMoves.size() == 0){
        query.prepare("INSERT INTO Moves ( board_id, Move) "
                      "VALUES (:board_id, :Move)");
        query.bindValue(":board_id", BoardID);
        query.bindValue(":Move", MoveToCheck.c_str());
        query.exec();
    }

    else{

        for (int i = 0; i <= OldMoves.size(); i++) {
            if (MoveToCheck == OldMoves[i]) {
                std::cout << "Move is already stored" << std::endl << std::endl;
                return;

            }

            else if (i == OldMoves.size()){

                query.prepare("INSERT INTO Moves ( board_id, Move) "
                              "VALUES (:board_id, :Move)");
                query.bindValue(":board_id", BoardID);
                query.bindValue(":Move", MoveToCheck.c_str());
                query.exec();
            }
        }
    }

}
