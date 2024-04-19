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
public:
    QSqlQuery query;
    alphaBeta();
    alphaBeta(int depth);
    alphaBeta(double piece, double king, double lock, double lockKing, double forward, double TwoEmpty, double OneJump, double OneEmpty, double TwoJump, double depth);
    //alphaBeta(alphaBeta const &ab);

    int giveScoreAI(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth);
    int moveAI(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet, int alpha, int beta, int& blackPieces2, int& redPieces2, int& playerTurn2, std::string playerMove, int &CounterForTempTable);
    int getId();
    void evolve(double rate);
    void resetWins();
    void dbInsert();
    void addWinner();
};

#endif // ALPHABETA_H
