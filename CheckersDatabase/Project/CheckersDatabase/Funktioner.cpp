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

void AddBoard(std::string BoardStateInputtet){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");

    QSqlQuery query = QSqlQuery(db);

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
                std::cout << "BoardState is already stored" << std::endl << std::endl;
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
