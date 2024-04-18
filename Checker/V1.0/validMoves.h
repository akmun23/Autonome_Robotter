#pragma once

#ifndef VALIDMOVES_H
#define VALIDMOVES_H
#include <climits>
#include <iostream>
#include <unistd.h>
#include<vector>
#include<string>
#include <random>


//Function to get the player's input
bool playerInput(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards);
std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards);


//If a jump has been made, this checks if the same piece is able to jump an additional time
bool moreMoveCheck(std::vector<std::string>& playerJump, std::string& playerMove);


//Returns a vector of possible moves for a player
std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards, std::vector<std::string>& playerJump, bool& moreMove, std::string& playerMove);


//Checks if the piece has jumped
bool pieceJump(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards);


//Checks if a piece is able to promote
bool promotion(std::vector<std::vector<std::string>>& boards, int& playerTurn);

// Counts the number of pieces on the board
int pieceCount(std::vector<std::vector<std::string>>& boards, int& blackPieces, int& redPieces);

//Changes the board according to the player's move
bool boardChange(int& playerTurn, std::vector<std::vector<std::string>>& boards, std::string& playerStart, std::string& playerMove, int& redPieces, int& blackPieces);
bool move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces);

bool DB_move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::string playerStart, std::string playerMove); // MoveFunction for database input

//Gives the board a game score based on the number of pieces and the number of possible moves
//Used in the alphaBeta function
int giveBoardScore(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth);

// The alphaBeta function
int alphaBeta(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet, int alpha, int beta, int& blackPieces2, int& redPieces2, int& playerTurn2, std::string playerMove, int& CounterForTempTable, int& TurnNr);

#endif // VALIDMOVES_H
