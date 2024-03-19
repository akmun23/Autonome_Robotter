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

    query.exec("ALTER TABLE UniqueBoard ADD PRIMARY KEY (board_id)");


    query.exec("Create Table Moves ("
               " board_id int,"
               " Move char(20)"
               " WinRate double"
               " FOREIGN KEY (board_id) REFERENCES UniqueBoard(board_id))");

    printBoardStates();

    std::string str2;
    std::cout << "What is the boardstate u want to save";
    std::cin >> str2;

    AddBoard(str2);

    printBoardStates();

    query.exec("DELETE FROM UniqueBoard WHERE board_id >= 4");




    return 0;
}
