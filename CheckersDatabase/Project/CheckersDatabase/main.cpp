#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include "Funktioner.h"

void printBoardStates();
void AddMove(int TempBoardID);
void AddBoard(int TempBoardID);

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
    query.exec("INSERT INTO Temp (tempBoard_id, BoardState, Move) "
               "VALUES (2, 'b0b0b0b0,0b0b0b0b,b0b0b000,0000000b,00000000,0w0w0w0w,w0w0w0w0,0w0w0w0w', 'b3a4')");

    query.exec("INSERT INTO Temp (tempBoard_id, BoardState, Move) "
               "VALUES (3, 'b0b0b0b0,0b0b0b0b,b0b0b000,0000000b,w0000000,000w0w0w,w0w0w0w0,0w0w0w0w', 'a6b5')");

    query.exec("INSERT INTO Temp (tempBoard_id, BoardState, Move) "
               "VALUES (4, 'b0b0b0b0,0b0b0b0b,00b0b000,0b00000b,00000000,0w0w0w0w,w0w0w0w0,0w0w0w0w', 'h3g4')");

    query.exec("INSERT INTO Temp (tempBoard_id, BoardState) "
               "VALUES (5, 'b0b0b0b0,0b0b0b0b,00b0b000,0b00000b,000000w0,0w0w0w00,w0w0w0w0,0w0w0w0w')");

    */
    printBoardStates();

    std::vector<int> TempBoardID;
    TempBoardID.clear();

    query.exec("SELECT tempboard_id FROM Temp");
    while (query.next()) {
        int BoardID = query.value(0).toInt();
        TempBoardID.push_back(BoardID);
    }
    /*
    std::string str2;
    std::cout << "What is the boardstate u want to save";
    std::cin >> str2;*/
    for (int i = 0; i < TempBoardID.size(); i++) {
        AddBoard(TempBoardID[i]);
    }


    printBoardStates();

    query.exec("DELETE FROM Temp WHERE tempBoard_id >= 0");




    return 0;
}
//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando
