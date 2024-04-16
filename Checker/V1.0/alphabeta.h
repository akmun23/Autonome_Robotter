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
    double _piece = 10;
    double _king = 20;
    double _lock = 5;
    double _lockKing = 5;
    double _forward = 2;
    double _TwoEmpty = 20;
    double _OneJump = 50;
    double _OneEmpty = 10;
    double _TwoJump = 80;
    double _depth = 2;
    int _id;
public:
    QSqlQuery query;
    alphaBeta();
    alphaBeta(double piece, double king, double lock, double lockKing, double forward, double TwoEmpty, double OneJump, double OneEmpty, double TwoJump, double depth);
    //alphaBeta(alphaBeta const &ab);

    int giveScoreAI(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth);
    int moveAI(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet, int alpha, int beta, int& blackPieces2, int& redPieces2, int& playerTurn2, std::string playerMove);
    int getId();
    void evolve(double rate);
    void resetWins();
    void dbInsert();
};

#endif // ALPHABETA_H
