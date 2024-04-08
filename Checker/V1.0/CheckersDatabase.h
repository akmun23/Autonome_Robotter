#ifndef CHECKERSDATABASE_H
#define CHECKERSDATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>


void AddMove(int& TempBoardID, std::string& OldBoardState);
void AddBoard(std::string& NewBoardState, std::string& OldBoardState, int& TempBoardID);
void InsertToTemp(std::string& BoardState, std::string& Move, int& Counter, int PlayerId);
void InsertToMove(int& BoardID, std::string& MoveToCheck, int& PlayerId, std::string& PlayerMoveDB);
void UpdateMoveWinrate(int& AmountOfMoves);
std::string MovePlayer(std::string& BoardState,int& PlayerTurn);
void RefreshTempTable(int& PlayerTurn);
bool CheckDuplicateMoves(std::string& BoardState, std::string& MoveToCheck, int& PlayerId);


//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando




#endif // CHECKERSDATABASE_H
