
#ifndef CHECKERSDATABASE_H
#define CHECKERSDATABASE_H

#pragma once

#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>




// Boards and Moves
void UploadTempToDatabase(int& UniqueBoardIDCounter);

void UpdateMoveWinRate(QString& Move, int& BoardID, double& WinOrLoss, int& PlayerId);

//Player Moves
std::string MovePlayer(std::string& BoardState,int& PlayerTurn);



//Temp
void RefreshTempTable();
bool CheckDuplicateMoves(std::string& BoardState, std::string& MoveToCheck, int& PlayerId);

// Inserting to database
void InsertBoardToDatabase(QString& BoardState);
void InsertNewMoveToNewBoard(int& Move, int& BoardID);
void InserNewMoveToOldBoard(int& BoardID, int& TempBoardID);
void InsertToTemp(std::string& BoardState, std::string& Move, int& Counter, int PlayerId);
void insertAlphaBetaToTemp(std::vector<std::vector<std::string>>& tempBoard, std::string& MoveMade, int& tempPlayer, int& CounterForTempTable);
void InsertMove(int board_id, QString Move, int PlayerID, double WinOrLoss);
void HandleNewMoves(QString Move, int PlayerID, double WinOrLoss, int BoardID);
//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando




#endif // CHECKERSDATABASE_H
