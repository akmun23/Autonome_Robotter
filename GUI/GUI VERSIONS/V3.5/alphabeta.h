#pragma once
#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "validmoves.h"
#include <string>
#include <vector>
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>

class alphaBeta : public validMoves
{
    // For database
    double _piece = 9.559397480568023;
    double _king = 14.66551921526645;
    double _lock = 2.886680350048823;
    double _lockKing = 3.4905191066448387;
    double _forward = 0.8713181519315153;
    double _TwoEmpty = 22.023951943802267;
    double _OneJump = 24.64160311651794;
    double _OneEmpty = 5.227387139291636;
    double _TwoJump = 141.6052036767301;
    double _depth = 1.2327709215647928;
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

    validMoves * _vm;

public:
    QSqlQuery query;
    alphaBeta(validMoves* vm);
    alphaBeta(validMoves* vm, int depth);
    alphaBeta(validMoves* vm, double piece, double king, double lock, double lockKing, double forward, double TwoEmpty, double OneJump, double OneEmpty, double TwoJump, double depth);

    std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards);
    std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards);

    int giveScoreAI(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth);
    int findMove(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, int alpha, int beta, std::string playerMove, int &CounterForTempTable);
    int getId();
    std::vector<std::string> getMove();
    void evolve(double rate);
    void resetWins();
    void dbInsert();
    void addWinner();
    void makeMove(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, int alpha, int beta, std::string playerMove,int& CounterForTempTable);
};

#endif // ALPHABETA_H
