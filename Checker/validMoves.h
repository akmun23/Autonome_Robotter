#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include <climits>
#include <iostream>
#include <unistd.h>
#include<vector>
#include<string>
//#include "playerInput.h"
#include <stdlib.h>
#include <random>

std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>> boards){
    bool jump = false;
    std::vector<std::string> playerJump = {};
    char column = 'A';
    char column2 = 'A';
    for(int i = 0; i < 8; i++){
        column = 'A' + i;
        for(int j = 0; j < 8; j++){
            if((i == 0) || (i == 1)){
                if((playerTurn == 1) && (boards[i][j] == "B " || boards[i][j] == "BK")){
                    if((j < 6) && ((boards[i+1][j+1] == "R ") || (boards[i+1][j+1] == "RK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i+1][j-1] == "R ") || (boards[i+1][j-1] == "RK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((playerTurn == 2) && (boards[i][j] == "RK")){
                    if((j < 6) && ((boards[i+1][j+1] == "B ") || (boards[i+1][j+1] == "BK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                                                                                                                                                                                                        }
                    if((j > 1) && ((boards[i+1][j-1] == "B ") || (boards[i+1][j-1] == "BK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                            }
                }
            } else if((i == 6) || (i == 7)){
                if(playerTurn == 2 && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){
                    if((j < 6) && ((boards[i-1][j+1] == "B ") || (boards[i-1][j+1] == "BK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "B ") || (boards[i-1][j-1] == "BK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((playerTurn == 1) && (boards[i][j] == "BK")){
                    if((j < 6) && ((boards[i-1][j+1] == "R ") || (boards[i-1][j+1] == "RK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "R ") || (boards[i-2][j-2] == "RK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            } else {
                if((playerTurn == 1) && ((boards[i][j] == "B ") || (boards[i][j] == "BK"))){
                    if((j < 6) && ((boards[i+1][j+1] == "R ") || (boards[i+1][j+1] == "RK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i+1][j-1] == "R ") || (boards[i+1][j-1] == "RK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                    if((j < 6)  && (boards[i][j] == "BK") && ((boards[i-1][j+1] == "R ") || (boards[i-1][j+1] == "RK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && (boards[i][j] == "BK") && ((boards[i-1][j-1] == "R ") || (boards[i-1][j-1] == "RK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){
                    if((j < 6) && ((boards[i-1][j+1] == "B ") || (boards[i-1][j+1] == "BK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "B ") || (boards[i-1][j-1] == "BK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                    if((j < 6) && (boards[i][j] == "RK") && ((boards[i+1][j+1] == "B ") || (boards[i+1][j+1] == "BK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && (boards[i][j] == "RK") && ((boards[i+1][j-1] == "B ") || (boards[i+1][j-1] == "BK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            }
        }
    }

    return playerJump;
}

bool moreMoveCheck(std::vector<std::string> playerJump, std::string playerMove) {
    std::string lowerCase;
    bool check;

        for (int i = 0; i < playerJump.size(); i += 2) {
        lowerCase = playerJump[i];
        lowerCase[0] = tolower(lowerCase[0]);
        if(playerMove == playerJump[i] || playerMove == lowerCase){
            return true;
        }
    }

    return false;
}

std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards, std::vector<std::string> playerJump, bool moreMove, std::string playerMove){
    int check = 0;
    bool move = false;
    char column;
    char column2;
    std::string lowerCase;
    std::vector<std::string> posMove = {};

    if(playerJump.size() > 0){
        if(moreMove){
            for(int i = 0; i < playerJump.size(); i +=2){
                lowerCase = playerJump[i];
                lowerCase[0] = tolower(lowerCase[0]);
                if(playerMove == playerJump[i] || playerMove == lowerCase){
                    posMove.push_back(playerJump[i]);
                    posMove.push_back(playerJump[i+1]);
                }
            }
        } else {
            posMove = playerJump;
        }

        return posMove;

    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(playerTurn == 1 && ((boards[i][j] == "B ") || (boards[i][j] == "BK"))){
                if(i < 7){
                    if((j < 7) && (boards[i+1][j+1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i+1][j-1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
                if(i > 0){
                    if((j < 7) && (boards[i][j] == "BK") && (boards[i-1][j+1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i][j] == "BK") && (boards[i-1][j-1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
            } else if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){
                if(i > 0){
                    if((j < 7) && (boards[i-1][j+1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i-1][j-1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
                if(i < 7){
                    if((j < 7) && (boards[i][j] == "RK") && (boards[i+1][j+1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i][j] == "RK") && (boards[i+1][j-1] == "1 ")){
                        column = 'A' + i;
                        column2 = 'A' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));

                    }
                }
            }
        }
    }

    return posMove;
}

bool pieceJump(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>>& boards){
    int row = playerStart[1] - '1';
    int row2 = playerMove[1] - '1';
    int row3 = row2 + (row-row2)/2;
    char column = playerStart[0]-((playerStart[0]-playerMove[0])/2);
    column = tolower(column);
    column = column - 'a';

    if(((boards[column][row3] == "R ") || (boards[column][row3] == "RK")) && (playerTurn == 1)){
        return true;
    } else if(((boards[column][row3] == "B ") || (boards[column][row3] == "BK")) && (playerTurn == 2)){
        return true;
    } else {
        return false;
    }

}

bool isValid(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>> boards) {
    int row = playerStart[1] - '0';
    int row2 = playerMove[1] - '0';
    char lowerCase = tolower(playerStart[0]);
    int column = lowerCase - 'a';
    int check;
    bool king = false;

    if(playerStart == playerMove){
        std::cout << "Invalid move. Please enter a move that is not the same as your starting position." << std::endl;
        return false;
    }

    if(playerTurn % 2 == 0){
        check = -1;
    } else {
        check = 1;
    }

    if(playerStart[0] == playerMove[0] || playerStart[1] == playerMove[1]) {
        std::cout << "Invalid move. Please enter a move that is diagonal." << std::endl;
        return false;
    }

    if(isupper(playerStart[0])){
        if(playerStart[0] < 'A' || playerStart[0] > 'H') {
            std::cout << "Invalid move. Please enter a letter between A and H." << std::endl;
            return false;
        }
    } else {
        if(playerStart[0] < 'a' || playerStart[0] > 'h') {
            std::cout << "Invalid move. Please enter a letter between a and h." << std::endl;
            return false;
        }
    }

    if(isupper(playerMove[0])){
        if(playerMove[0] < 'A'|| playerMove[0] > 'H') {
            std::cout << "Invalid move. Please enter a letter between A and H." << std::endl;
            return false;
        }
    } else {
        if(playerMove[0] < 'a' || playerMove[0] > 'h') {
            std::cout << "Invalid move. Please enter a letter between a and h." << std::endl;
            return false;
        }
    }

    if(row == 0 || row > 8 || row2 < 1 || row2 > 8){
        std::cout << "Invalid move. Please enter a number between 1 and 8." << std::endl;
        return false;
    }

    if(boards[column][row-1] == "BK" || boards[column][row-1] == "RK"){
        king = true;
    }

    if(!king){
        if(abs(row2-row) != 1 || (playerMove[0]-'0')-(playerStart[0]-'0') != check){
            if(abs(row2-row) == 2 && (playerMove[0]-'0')-(playerStart[0]-'0') == 2*check){
                if(pieceJump(playerStart, playerMove, playerTurn, boards)){
                    return true;
                }
            }
            std::cout << "Invalid move. Please enter a move that is only one square away." << std::endl;
            return false;
        }
    } else {
        if(abs(row2-row) != 1 || abs((playerMove[0]-'0')-(playerStart[0]-'0')) != 1){
            if(abs(row2-row) == 2 && abs((playerMove[0]-'0')-(playerStart[0]-'0')) == 2){
                if(pieceJump(playerStart, playerMove, playerTurn, boards)){
                    return true;
                }
            }
            std::cout << "Invalid move. Please enter a move that is only one square away." << std::endl;
            return false;
        }
    }

    return true;
}

bool promotion(std::vector<std::vector<std::string>> boards, int playerTurn){
    if(playerTurn == 1){
        for(int i = 0; i < 8; i++){
            if(boards[7][i] == "B "){
                return true;
            }
        }
    } else {
        for(int i = 0; i < 8; i++){
            if(boards[0][i] == "R "){
                return true;
            }
        }
    }
    return false;
}

void aiMover(std::string& playerMove, std::string& playerStart, std::vector<std::string> posMove){
    int random;
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    // Define the range for the random number
    std::uniform_int_distribution<> distr(0, posMove.size()-1);

    random = distr(eng);

    if(random % 2 != 0){
        random--;
    }
    std::cout << "AI moves from " << posMove[random] << " to " << posMove[random+1] << std::endl;
    playerStart = posMove[random];
    playerMove = posMove[random+1];
    return;
}

bool playerMover(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>> boards) {
    bool validMove1 = false;
    bool validMove2 = false;
    int row;
    int row2;
    char lowerCase;
    char lowerCase2;
    int column;
    int column2;
    std::vector<std::string> jump = jumpPossible(playerTurn, boards);

    std::vector<std::string> piece;
    if(playerTurn == 1){
        piece = {"B ", "BK"};
    } else {
        piece = {"R ", "RK"};
    }

    if(movePossible(playerTurn, boards, jump, moreMoveCheck(jump, playerMove), playerMove).size() < 1){
        return false;
    }

    if(!isValid(playerStart, playerMove, playerTurn, boards)){
        return false;
    }

    while(!validMove1){
        row = playerStart[1] - '1';
        lowerCase = tolower(playerStart[0]);
        column = lowerCase - 'a';

        if((boards[column][row] != piece[0]) && (boards[column][row] != piece[1])) {
            std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
            return false;
        } else {
            validMove1 = true;
        }

    }

    while(!validMove2){
        row2 = playerMove[1] - '0' - 1;
        lowerCase2 = tolower(playerMove[0]);
        column2 = lowerCase2 - 'a';

        if(boards[column2][row2] != "1 "){
            std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
            return false;
        } else {
            validMove2 = true;
        }
    }

    return true;

}

bool boardChange(int playerTurn, std::vector<std::vector<std::string>>& boards, std::string playerStart, std::string playerMove, int& redPieces, int& blackPieces){
     std::string piece;
     int row = playerStart[1] - '1';
     int row2 = playerMove[1] - '1';
     int row3 = row2 + (row-row2)/2;
     char lowerCase = tolower(playerStart[0]);
     char lowerCase2 = tolower(playerMove[0]);
     int column = lowerCase - 'a';
     int column2 = lowerCase2 - 'a';
     int column3 = column - (column-column2)/2;

     piece = boards[column][row];
     boards[column][row] = "1 ";
     boards[column2][row2] = piece;

     if(pieceJump(playerStart, playerMove, playerTurn, boards)){
         boards[column3][row3] = "1 ";
         int count = 0;
         int count2 = 0;
         for (int i = 0; i < 8; ++i) {
             for (int j = 0; j < 8; ++j) {
                 if(boards[i][j] == "R " || boards[i][j] == "RK"){
                     count2++;
                 } else if(boards[i][j] == "B " || boards[i][j] == "BK"){
                     count++;
                 }
             }
         }
         redPieces = count2;
         blackPieces = count;
     }

     if(promotion(boards, playerTurn)){
         if(playerTurn == 1){
             boards[column2][row2] = "BK";
         } else {
             boards[column2][row2] = "RK";
         }
         return true;
     }

     return false;
}

void aiPlay(std::vector<std::vector<std::string>>& boards, std::string playerStart, std::string playerMove, int playerTurn, int& redPieces, int& blackPieces){
    bool jumped;
    bool promotion;

    do{
    aiMover(playerMove, playerStart, movePossible(playerTurn, boards, jumpPossible(playerTurn, boards), moreMoveCheck(jumpPossible(playerTurn, boards), playerMove), playerMove));
    playerMover(playerStart, playerMove, playerTurn, boards);
    jumped = pieceJump(playerStart, playerMove, playerTurn, boards);
    promotion = boardChange(playerTurn, boards, playerStart, playerMove, redPieces, blackPieces);
    } while(moreMoveCheck(jumpPossible(playerTurn, boards), playerMove) && jumped && !promotion);

}

int giveBoardScore(std::vector<std::vector<std::string>> boards, int playerTurn){
    int score = 0;
    int black = 0;
    int red = 0;
    int diff = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(boards[i][j] == "B "){
                score += 4;
                black++;
                diff++;
            }
            else if(boards[i][j] == "BK"){
                score += 6;
                black++;
                diff++;
            }
            else if(boards[i][j] == "R "){
                score -= 4;
                red++;
                diff--;
            }
            else if(boards[i][j] == "RK"){
                score -= 6;
                red++;
                diff--;
            }
        }
    }
    score += diff;

    if(playerTurn == 1){
 /*       if(jumpPossible(2, boards).empty()){
            score += 15;
            if(!(jumpPossible(1, boards).empty())){
                score += 25;
            }
        }
        if(!(jumpPossible(1, boards).empty())){
            score += 5;
            if(!(jumpPossible(2, boards).empty())){
                score -= 20;
            }
        }
        if(jumpPossible(1, boards).empty()){
            score -= 20;
            if(!(jumpPossible(2, boards).empty())){
                score -= 50;
            }
        } */
        if(red == 0 || movePossible(2, boards, jumpPossible(2, boards), false, "").empty()){
            score += 1000;
        }
        score *= 1000;
        score += rand()%10;
    } else if(playerTurn == 2) {
/*      if(jumpPossible(1, boards).empty()){
                score -= 15;
            if(!(jumpPossible(2, boards).empty())){
                score -= 25;
            }
        }
        if(!(jumpPossible(2, boards).empty())){
                score -= 5;
                if(!(jumpPossible(1, boards).empty())){
                    score += 20;
                }
        }
        if(jumpPossible(2, boards).empty()){
            score += 20;
            if(!(jumpPossible(1, boards).empty())){
                score += 50;
        }
    } */
        if(black == 0 || movePossible(1, boards, jumpPossible(1, boards), false, "").empty()){
            score -= 1000;
        }
        score *= 1000;
        score -= rand()%10;
    }


    return score;
}

void minMax(std::vector<std::vector<std::string>>& boards, std::string playerStart, std::string playerMove, int playerTurn, int& redPieces, int& blackPieces, int depth){
    bool jumped;
    bool promotion;
    std::vector<int> score;
    int redPieces2 = redPieces;
    int blackPieces2 = blackPieces;
    int bestBlack = blackPieces;
    int bestRed = redPieces;
    std::vector<std::vector<std::string>> bestBoard;
    int maxScore;
    if(playerTurn == 1){
        maxScore = INT_MIN;
    } else {
        maxScore = INT_MAX;
    }
    std::vector<std::vector<std::string>> tempBoard = boards;
    std::vector<std::string> posMoveStart = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, boards), moreMoveCheck(jumpPossible(playerTurn, boards), playerMove), playerMove);
    std::vector<std::string> posMove;

    for (int i = 0; i < posMoveStart.size(); i += 2) {
        posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), false, playerMove);
        playerStart = posMove[i];
        playerMove = posMove[i+1];
        playerMover(playerStart, playerMove, playerTurn, tempBoard);
        jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
        promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);

        while(moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove) && jumped && !promotion){
            posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove), playerMove);
            playerStart = posMove[0];
            playerMove = posMove[1];
            playerMover(playerStart, playerMove, playerTurn, tempBoard);
            jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
            promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);
        }

        score.push_back(giveBoardScore(tempBoard, playerTurn));

        if(score[i/2] > maxScore && playerTurn == 1){
            maxScore = score[i/2];
            bestBoard = tempBoard;
            bestBlack = blackPieces2;
            bestRed = redPieces2;
        } else if(score[i/2] < maxScore && playerTurn == 2){
            maxScore = score[i/2];
            bestBoard = tempBoard;
            bestBlack = blackPieces2;
            bestRed = redPieces2;
        }

        tempBoard = boards;
        redPieces2 = redPieces;
        blackPieces2 = blackPieces;
        playerStart = {};
        playerMove = {};
    }
    redPieces = bestRed;
    blackPieces = bestBlack;
    boards = bestBoard;

}

int minMaxAlgo(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet){
    int maxEval;
    int eval;
    bool jumped;
    bool promotion;
    int blackPieces2 = blackPieces;
    int redPieces2 = redPieces;
    std::vector<std::vector<std::string>> tempBoard;
    std::vector<std::vector<std::string>> bestBoard;
    std::string playerStart;
    std::string playerMove;
    std::vector<std::string> moves;
    std::vector<std::string> bestMoves;
    std::vector<std::string> posMove = movePossible(playerTurn, boards, jumpPossible(playerTurn, boards), moreMoveCheck(jumpPossible(playerTurn, boards), playerMove), playerMove);
    tempBoard = boards;
    moveSet = {};
    if( depth == 0 || posMove.empty() || redPieces2 == 0 || blackPieces2 == 0) {
        return giveBoardScore(boards, playerTurn);
    }

    if(playerTurn == 1){
        maxEval = INT_MIN;
        posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, boards), playerMove), playerMove);
        for (int i = 0; i < (posMove.size()-1); i += 2) {
            posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove), playerMove);
            if(i > posMove.size()-1){
                return maxEval;
            }
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            moves.push_back(playerStart);
            moves.push_back(playerMove);
            playerMover(playerStart, playerMove, playerTurn, tempBoard);
            jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
            promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);

            while(moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove) && jumped && !promotion){
                posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove), playerMove);
                playerStart = posMove[0];
                moves.push_back(playerStart);
                playerMove = posMove[1];
                moves.push_back(playerMove);
                playerMover(playerStart, playerMove, playerTurn, tempBoard);
                jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
                promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);
            }

            eval = minMaxAlgo(tempBoard, depth-1, 2, blackPieces2, redPieces2, boards2, moveSet);
            if(maxEval < eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
            }

            tempBoard = boards;
            blackPieces2 = blackPieces;
            redPieces2 = redPieces;
            playerStart = {};
            playerMove = {};
            moves = {};
            }
        boards2 = bestBoard;
        moveSet = bestMoves;
        return maxEval;
    } else {
        maxEval = INT_MAX;
        posMove = movePossible(playerTurn, boards, jumpPossible(playerTurn, boards), false, playerMove);

        for (int i = 0; i < (posMove.size()-1); i += 2) {
            posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), false, playerMove);
            if(i > posMove.size()-1){
                return maxEval;
            }
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            moves.push_back(playerStart);
            moves.push_back(playerMove);
            playerMover(playerStart, playerMove, playerTurn, tempBoard);
            jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
            promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);

            while(moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove) && jumped && !promotion){
                posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove), playerMove);
                playerStart = posMove[0];
                playerMove = posMove[1];
                moves.push_back(playerStart);
                moves.push_back(playerMove);
                playerMover(playerStart, playerMove, playerTurn, tempBoard);
                jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
                promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);
            }

            eval = minMaxAlgo(tempBoard, depth-1, 1, blackPieces2, redPieces2, boards2, moveSet);
            if(maxEval > eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
            }

            tempBoard = boards;
            blackPieces2 = blackPieces;
            redPieces2 = redPieces;
            playerStart = {};
            playerMove = {};
            moves = {};
            }
        boards2 = bestBoard;
        moveSet = bestMoves;
        return maxEval;
    }

}


#endif // VALIDMOVES_H
