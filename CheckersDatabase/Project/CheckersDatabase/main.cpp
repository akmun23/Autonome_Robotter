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
    db.setUserName("Indsæt dit brugernavn");  // Change to username
    db.setPassword("Indsæt password");  // Change to password
    db.open();

    QSqlQuery query;

    printBoardStates();

    std::string str2;
    std::cout << "What is the boardstate u want to save";
    std::cin >> str2;

    AddBoard(str2);

    printBoardStates();

    query.exec("DELETE FROM UniqueBoard WHERE board_id >= 4");




    return 0;
}
