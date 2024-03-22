#ifndef CHECKERSDATABASE_H
#define CHECKERSDATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>


void AddMove(int TempBoardID);
void AddBoard(int TempBoardID);
void UpdateDatabaseFromTemp();
void InsertToTemp(std::string& BoardState, std::string& Move, int& Counter, int PlayerId);
//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando




#endif // CHECKERSDATABASE_H
