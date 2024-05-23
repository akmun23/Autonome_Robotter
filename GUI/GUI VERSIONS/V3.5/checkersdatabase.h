#ifndef CHECKERSDATABASE_H
#define CHECKERSDATABASE_H

#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <string>

// Boards and Moves
void UploadTempToDatabase(int& UniqueBoardIDCounter, bool Toggle);

void UpdateMoveWinRate(QString& Move, int& BoardID, float& WinOrLoss, int& PlayerId);

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

void LoadSimVectors(std::vector<int>& Player1SimChoise,std::vector<int>& Player2SimChoise);
void IncreaseSimu(const int& drawChecker, bool& AlreadyIncreased, std::vector<int>& Player1SimChoise);
void IncreaseOponentSimu(const int& drawChecker, std::vector<int>& Player2SimChoise);

void DeleteWrongMove(std::vector<std::vector<std::string>>& tempBoard, std::string& MoveMade, int& tempPlayer);
//qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number(); // debug komando




#endif // CHECKERSDATABASE_H
