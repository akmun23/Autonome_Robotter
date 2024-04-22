#pragma once
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>
#include <future>

#include "alphabeta.h"
#include "validmoves.h"

void resetDB(bool choise);
void DatabaseInit(int &UniqueBoardIDCounter, bool UploadTemp);
void loadBoardToString(std::vector<std::vector<std::string>> boards, std::string &output);
void MoveDBMain(std::string& BoardState, int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::vector<std::string>& moveSet, int& CounterForTempTable, int& DrawChecker, bool& DatabaseMoveMade, int& TestCounterForDatabase, validMoves& validm, alphaBeta alphab);
void MoveRandom(std::vector<std::string>& moveSet, bool& DatabaseMoveMade, validMoves &validm);

void MoveRobot(bool RunChecker,std::future<bool>& fut, std::vector<std::vector<std::string>>& tempBoard, int& thisTurn, std::vector<std::string>& moveSet, std::vector<std::vector<double>>& startUpRobot, int& i);
void printAIMove(bool& DatabaseMoveMade, std::vector<std::string>& moveSet, std::string& MoveMade, int& thisTurn);
void printGameState(int ii, int DrawChecker, int redPieces, int blackPieces, int playerTurn, std::vector<std::vector<std::string>>& boards, int depth, alphaBeta alphab);
void GameEnd(int redPieces, int blackPieces, int playerTurn);

#endif // MAINFUNCTIONS_H
