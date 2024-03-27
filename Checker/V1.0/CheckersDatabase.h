#ifndef CHECKERSDATABASE_H
#define CHECKERSDATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>


void AddMove(int& TempBoardID);
void AddBoard(int TempBoardID);
void UpdateDatabaseFromTemp();
void InsertToTemp(std::string& BoardState, std::string& Move, int& Counter, int PlayerId);
void InsertToMove(int& BoardID, std::string& MoveToCheck, double& WinChecker, int& PlayerId);
void UpdateMoveWinrate(int& BoardID, std::string& MoveToCheck, double &WinChecker, int& PlayerId);
std::string MovePlayer(std::vector<std::vector<std::string>>& BoardState,int& PlayerTurn);
void RefreshTempTable(int& PlayerTurn);

//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando




#endif // CHECKERSDATABASE_H
