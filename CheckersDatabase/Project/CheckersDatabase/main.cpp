#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "Funktioner.h"

int main()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("Pascal");  // Change to username
    db.setPassword("Superbror22!");  // Change to password
    db.open();

    QSqlQuery query;

    /*
    query.exec("Create Table Temp ("
               " tempBoard_id int,"
               " BoardState char(100),"
               " Move char(20),"    /*
    query.exec("ALTER TABLE UniqueBoard ADD PRIMARY KEY (board_id)");
    */

    query.exec("INSERT INTO Temp (tempBoard_id, BoardState, Move) "
               "VALUES (1, 'b0b0b0b0,0b0b0b0b,b0b0b0b0,00000000,00000000,0w0w0w0w,w0w0w0w0,0w0w0w0w', 'g6h5')");

    printBoardStates();

    std::vector<std::string> TempBoard;
    std::vector<int> TempBoardID;
    TempBoard.clear();
    TempBoardID.clear();

    query.exec("SELECT BoardState,tempboard_id FROM Temp");
    while (query.next()) {
        std::string BoardState = query.value(0).toString().toStdString();
        int BoardID = query.value(1).toInt();
        TempBoardID.push_back(BoardID);
        TempBoard.push_back(BoardState);
    }
    /*
    std::string str2;
    std::cout << "What is the boardstate u want to save";
    std::cin >> str2;*/
    for (int i = 0; i < TempBoard.size(); i++) {
        AddBoard(TempBoardID[i]);
    }


    printBoardStates();

    query.exec("DELETE FROM UniqueBoard WHERE board_id >= 4");




    return 0;
}
//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando
