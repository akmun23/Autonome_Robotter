#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include <string>
#include <vector>
#include <iostream>

class validMoves
{
public:

    bool playerInput(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards);
    std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards);
    bool moreMoveCheck(std::vector<std::string>& playerJump, std::string& playerMove);
    std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards, std::vector<std::string>& playerJump, bool& moreMove, std::string& playerMove);
    bool pieceJump(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards);
    bool promotion(std::vector<std::vector<std::string>>& boards, int& playerTurn);
    int  pieceCount(std::vector<std::vector<std::string>>& boards, int& blackPieces, int& redPieces);
    bool boardChange(int& playerTurn, std::vector<std::vector<std::string>>& boards, std::string& playerStart, std::string& playerMove, int& redPieces, int& blackPieces);
    bool move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces);
    bool DB_move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::string playerStart, std::string playerMove);
};

#endif // VALIDMOVES_H
