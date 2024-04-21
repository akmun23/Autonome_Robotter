#pragma once
#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "CheckersDatabase.h"
#include "validmoves.h"
#include <string>
#include <vector>
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>

class alphaBeta : public validMoves
{
    // For database
    double _piece = 7.5742126627791135;
    double _king = 15.452885793319332;
    double _lock = 3.510642298522243;
    double _lockKing = 3.217031955937848;
    double _forward = 0.9469326185608599;
    double _TwoEmpty = 24.339960777642677;
    double _OneJump = 37.55305763341628;
    double _OneEmpty = 4.465623172402512;
    double _TwoJump = 139.11336679273032;
    double _depth = 1.281201654689201;
    int _id;

    // For AI
    int _depthAI;
    std::vector<std::vector<std::string>> _boards;
    std::string _playerStart;
    std::string _playerMove;
    int _blackPieces;
    int _redPieces;
    int _playerTurn;
    int _CounterForTempTable;

public:
    QSqlQuery query;
    alphaBeta();
    alphaBeta(int depth);
    alphaBeta(double piece, double king, double lock, double lockKing, double forward, double TwoEmpty, double OneJump, double OneEmpty, double TwoJump, double depth);

    std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards);
    std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards);

    int giveScoreAI(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth);
    int moveAI(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, int alpha, int beta, std::string playerMove, int &CounterForTempTable);
    int getId();
    std::vector<std::string> getMove();
    void evolve(double rate);
    void resetWins();
    void dbInsert();
    void addWinner();
};

#endif // ALPHABETA_H
