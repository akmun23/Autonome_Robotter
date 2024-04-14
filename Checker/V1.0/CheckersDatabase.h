#ifndef CHECKERSDATABASE_H
#define CHECKERSDATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>




//Nye
void UploadTempToDatabase(int& UniqueBoardIDCounter);
void InsertBoardToDatabase(QString& BoardState);
void InsertMoveToP1Database(QString& Move, int& BoardID, double& WinOrLoss);
void InsertMoveToP2Database(QString& Move, int& BoardID, double& WinOrLoss);
void UpdateMoveWinRate(QString& Move, int& BoardID, double& WinOrLoss, int& PlayerId);

void insertAlphaBetaToTemp(std::vector<std::vector<std::string>>& tempBoard, std::string& MoveMade, int& tempPlayer, int& CounterForTempTable);



//Gamle
void InsertToTemp(std::string& BoardState, std::string& Move, int& Counter, int PlayerId);
std::string MovePlayer(std::string& BoardState,int& PlayerTurn);
void RefreshTempTable(int& PlayerTurn);
bool CheckDuplicateMoves(std::string& BoardState, std::string& MoveToCheck, int& PlayerId);


//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando




#endif // CHECKERSDATABASE_H
