#pragma once
#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include "boardUpdate.h"
#include <string>
#include <vector>
#include <iostream>
#include <climits>

class validMoves
{
    std::string _playerStart = "a1";
    std::string _playerMove = "a1";
    int _playerTurn = 1;
    int _blackPieces = 12;
    int _redPieces = 12;
    std::vector<std::string> _playerJump = {};
    std::vector<std::vector<std::string>> _boards;

public:
    validMoves();
    validMoves(std::string playerStart, std::string playerMove, int playerTurn, int &blackPieces, int &redPieces, std::vector<std::vector<std::string>> &boards);
    bool playerInput();
    virtual std::vector<std::string> jumpPossible();
    bool moreMoveCheck();
    virtual std::vector<std::string> movePossible();
    bool pieceJump();
    bool promotion();
    int  pieceCount();
    bool boardChange();
    bool move();
    bool DB_move(std::string playerStart, std::string playerMove);
    int getPlayerTurn();
    std::vector<std::vector<std::string>> getBoards();
    std::vector<int> getPieceCount();
    std::vector<std::string> getMove();
    void setBoards(std::vector<std::vector<std::string>> boards);
    void setMove(std::string playerStart, std::string playerMove);
    void setPlayerTurn(int playerTurn);
    void setPieceCount(int blackPieces, int redPieces);
};

#endif // VALIDMOVES_H
