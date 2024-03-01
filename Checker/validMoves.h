#ifndef VALIDMOVES_H
#define VALIDMOVES_H

#include <climits>
#include <iostream>
#include <unistd.h>
#include<vector>
#include<string>
#include <stdlib.h>
#include <random>

//Returns a vector of possible jump moves for a player
std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>> boards){
    std::vector<std::string> playerJump = {};

    char column = 'A'; //Variable used to set push the correct column where the player starts the turn to the vector playerJump
    char column2 = 'A'; //Variable used to set push the correct column where the player ends the turn to the vector playerJump

    //Iterates through all spaces on the board and checks if a jump is possible
    for(int i = 0; i < 8; i++){
        column = 'A' + i;
        for(int j = 0; j < 8; j++){

    //Normal pieces can only jump forward. For black this means increasing the row number, for red it means decreasing the row number
    //Kings can jump in all directions
            if((i == 0) || (i == 1)){ //checks if the player's piece is close to the edge of the board
                if((playerTurn == 1) && (boards[i][j] == "B " || boards[i][j] == "BK")){ //Checks if the checker belongs to player 1 and if a jump is possible
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
                } else if((playerTurn == 2) && (boards[i][j] == "RK")){ //Checks if the checker belongs to player 2 and if a jump is possible
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
            } else if((i == 6) || (i == 7)){ //checks if the player's piece is close to the edge of the board
                if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){ //Checks if the checker belongs to player 2 and if a jump is possible
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
                } else if((playerTurn == 1) && (boards[i][j] == "BK")){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((boards[i-1][j+1] == "R ") || (boards[i-1][j+1] == "RK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "R ") || (boards[i-1][j-1] == "RK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'A' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            } else { //else it can jump freely
                if((playerTurn == 1) && ((boards[i][j] == "B ") || (boards[i][j] == "BK"))){ //Checks if the checker belongs to player 1 and if a jump is possible
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
                } else if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){ //Checks if the checker belongs to player 2 and if a jump is possible
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
    //Returns the constructed vector playerJump
    return playerJump;
}

//If a jump has been made, this checks if the same piece is able to jump an additional time
bool moreMoveCheck(std::vector<std::string> playerJump, std::string playerMove) {
    std::string lowerCase;
    bool check;
    //Iterates through the vector playerJump and checks if the player's piece is able to jump again
    //By comparing where the piece just ended with all the possible jumps for the new board-state
        for (int i = 0; i < playerJump.size(); i += 2) {
        lowerCase = playerJump[i];
        lowerCase[0] = tolower(lowerCase[0]);
        if(playerMove == playerJump[i] || playerMove == lowerCase){
            return true;
        }
    }

    return false;
}

//Returns a vector of possible moves for a player
std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards, std::vector<std::string> playerJump, bool moreMove, std::string playerMove){
    char column;
    char column2;
    std::string lowerCase;
    std::vector<std::string> posMove = {};

    //If a jump is possible it goes into this if-statement since a jump is mandatory
    if(playerJump.size() > 0){
        //If the player is able to jump again, it checks all the possible jumps for the new board-state
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
            //Set posMove to all possible jumps, since no piece has jumped yet
            posMove = playerJump;
        }
        //Returns the vector posMove
        return posMove;
    }

    //If no jump is possible, it goes into this if-statement
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if(playerTurn == 1 && ((boards[i][j] == "B ") || (boards[i][j] == "BK"))){ //If it is player 1's turn, it checks if the player's piece is able to move
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

            } else if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){ //If it is player 2's turn, it checks if the player's piece is able to move
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

    //Returns the vector posMove
    return posMove;
}

//Checks if the piece has jumped
bool pieceJump(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>>& boards){
    int row = playerStart[1] - '1'; //Starting row
    int row2 = playerMove[1] - '1'; //Ending row
    int row3 = row2 + (row-row2)/2; //Middle row
    char column = playerStart[0]-((playerStart[0]-playerMove[0])/2); //Middle column
    column = tolower(column);
    column = column - 'a';

    //Checks if the piece is able to jump over an enemy piece
    if(((boards[column][row3] == "R ") || (boards[column][row3] == "RK")) && (playerTurn == 1)){
        return true;
    } else if(((boards[column][row3] == "B ") || (boards[column][row3] == "BK")) && (playerTurn == 2)){
        return true;
    } else {
        return false;
    }

}

//Checks for different invalid moves
bool isValid(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>> boards) {
    int row = playerStart[1] - '0';
    int row2 = playerMove[1] - '0';
    char lowerCase = tolower(playerStart[0]);
    int column = lowerCase - 'a';
    int check;
    bool king = false;

    //Checks if start and end position are the same
    if(playerStart == playerMove){
        std::cout << "Invalid move. Please enter a move that is not the same as your starting position." << std::endl;
        return false;
    }

    //Checks if the move is diagonal
    if(playerStart[0] == playerMove[0] || playerStart[1] == playerMove[1]) {
        std::cout << "Invalid move. Please enter a move that is diagonal." << std::endl;
        return false;
    }

    //Checks if the move is within the board
    if(isupper(playerStart[0])){
        if(playerStart[0] < 'A' || playerStart[0] > 'H' || playerMove[0] < 'A'|| playerMove[0] > 'H') {
            std::cout << "Invalid move. Please enter a letter between A and H." << std::endl;
            return false;
        }
    } else {
        if(playerStart[0] < 'a' || playerStart[0] > 'h' || playerMove[0] < 'a'|| playerMove[0] > 'h') {
            std::cout << "Invalid move. Please enter a letter between a and h." << std::endl;
            return false;
        }
    }

    //Checks if the move is within the board
    if(row == 0 || row > 8 || row2 < 1 || row2 > 8){
        std::cout << "Invalid move. Please enter a number between 1 and 8." << std::endl;
        return false;
    }

    //Checks if the player's piece is a king
    if(boards[column][row-1] == "BK" || boards[column][row-1] == "RK"){
        king = true;
    }

    //Sets the variable for which way a piece is allowed to move
    if(playerTurn % 2 == 0){
        check = -1;
    } else {
        check = 1;
    }

    //Checks if the move is only one square away in the allowed direction
    //Unless its a jump where it is allowed to be two squares away int the allowed direction
    //If the piece is a king, it is allowed to move in all directions
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

    //Returns true if none of the if-statements returned false
    return true;
}

//Checks if a piece is able to promote
bool promotion(std::vector<std::vector<std::string>> boards, int playerTurn){
    //Checks if a normal piece is on the opposing side of the board
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

//Combines the previous checks to check if a move is valid
bool playerMover(std::string playerStart, std::string playerMove, int playerTurn, std::vector<std::vector<std::string>> boards) {
    int row = playerStart[1] - '1';
    char lowerCase = tolower(playerStart[0]);
    int column = lowerCase - 'a';
    int row2 = playerMove[1] - '0' - 1;
    char lowerCase2 = tolower(playerMove[0]);
    int column2 = lowerCase2 - 'a';
    std::vector<std::string> jump = jumpPossible(playerTurn, boards);
    std::vector<std::string> piece;

    //Sets the pieces that belong to the player
    if(playerTurn == 1){
        piece = {"B ", "BK"};
    } else {
        piece = {"R ", "RK"};
    }

    //Checks if the player has any possible moves
    if(movePossible(playerTurn, boards, jump, moreMoveCheck(jump, playerMove), playerMove).size() < 1){
        return false;
    }

    //Checks if the move is valid
    if(!isValid(playerStart, playerMove, playerTurn, boards)){
        return false;
    }

    //Checks if the player's piece is on the start position
    if((boards[column][row] != piece[0]) && (boards[column][row] != piece[1])) {
        std::cout << "Invalid move. Please enter a square containing one of your pieces." << std::endl;
        return false;
    }

    //Checks if the end position is empty
    if(boards[column2][row2] != "1 "){
        std::cout << "Invalid move. Please enter a square that isnt occupied." << std::endl;
        return false;
    }

    //Returns true if none of the if-statements returned false
    return true;
}

//Changes the board according to the player's move
bool boardChange(int playerTurn, std::vector<std::vector<std::string>>& boards, std::string playerStart, std::string playerMove, int& redPieces, int& blackPieces){
     std::string piece;
     int row = playerStart[1] - '1'; //Starting row
     int row2 = playerMove[1] - '1'; //Ending row
     int row3 = row2 + (row-row2)/2; //Middle row if jump
     char lowerCase = tolower(playerStart[0]); //Makes it possible fo input to be lowerCase
     char lowerCase2 = tolower(playerMove[0]); //Makes it possible fo input to be lowerCase
     int column = lowerCase - 'a'; //Starting column
     int column2 = lowerCase2 - 'a'; //Ending column
     int column3 = column - (column-column2)/2; //Middle column if jump

     //Changes the board according to the player's move and what piece has been moved
     piece = boards[column][row];
     boards[column][row] = "1 ";
     boards[column2][row2] = piece;

     //Checks if the piece has jumped
     if(pieceJump(playerStart, playerMove, playerTurn, boards)){
         //Sets the middle position to empty
         boards[column3][row3] = "1 ";
         int count = 0;
         int count2 = 0;
         //Counts the number of pieces on the board
         for (int i = 0; i < 8; ++i) {
             for (int j = 0; j < 8; ++j) {
                 if(boards[i][j] == "R " || boards[i][j] == "RK"){
                     count2++;
                 } else if(boards[i][j] == "B " || boards[i][j] == "BK"){
                     count++;
                 }
             }
         }
         //Sets the number of pieces on the board
         redPieces = count2;
         blackPieces = count;
     }

     //Checks if the piece is able to promote and changes it to a king if it is
     //Returns true if the piece has been promoted
     if(promotion(boards, playerTurn)){
         if(playerTurn == 1){
             boards[column2][row2] = "BK";
         } else {
             boards[column2][row2] = "RK";
         }
         return true;
     }

     //If no promotion has been made, it returns false
     return false;
}

//Gives the board a game score based on the number of pieces and the number of possible moves
//Used in the alphaBeta function
int giveBoardScore(std::vector<std::vector<std::string>> boards, int playerTurn){
    int score = 0;
    int black = 0;
    int red = 0;
    int diff = 0;
    int random;
    //Gives score depending on the number of pieces on the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(boards[i][j] == "B "){
                score += 6;
                black++;
                diff++;
            }
            else if(boards[i][j] == "BK"){
                score += 10;
                black++;
                diff++;
            }
            else if(boards[i][j] == "R "){
                score -= 6;
                red++;
                diff--;
            }
            else if(boards[i][j] == "RK"){
                score -= 10;
                red++;
                diff--;
            }
        }
    }
    score += diff;

    //Gives score depending on the jumps that are possible
    //And if the game is in a winning state
    if(playerTurn == 1){
       if(jumpPossible(2, boards).empty()){
            score += 15;
            if(!(jumpPossible(1, boards).empty())){
                score += 25;
            }
        }
        if(!(jumpPossible(1, boards).empty())){
            score += 15;
            if(!(jumpPossible(2, boards).empty())){
                score -= 15;
            }
        }
        if(jumpPossible(1, boards).empty()){
            score -= 20;
            if(!(jumpPossible(2, boards).empty())){
                score -= 50;
            }
        }
        if(red == 0 || movePossible(2, boards, jumpPossible(2, boards), false, "").empty()){
            score += 1000;
        }
        score *= 1000;

        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 eng(rd()); // Seed the generator
        std::uniform_int_distribution<> distr(0, 10); // Define the range for the random number
        random = distr(eng); // Generate a random number

        score += rand()%10;
    } else if(playerTurn == 2) {
      if(jumpPossible(1, boards).empty()){
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
    }
        if(black == 0 || movePossible(1, boards, jumpPossible(1, boards), false, "").empty()){
            score -= 1000;
        }
        score *= 1000;

        std::random_device rd;  // Obtain a random number from hardware
        std::mt19937 eng(rd()); // Seed the generator
        std::uniform_int_distribution<> distr(0, 10); // Define the range for the random number
        random = distr(eng); // Generate a random number

        score -= random;
    }

    //Returns the score
    return score;
}

int alphaBeta(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet, int alpha, int beta){
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

    //If the depth is 0, the game is in a winning state, or no moves are possible, it returns the score of the board
    if( depth == 0 || posMove.empty() || redPieces2 == 0 || blackPieces2 == 0) {
        return giveBoardScore(boards, playerTurn);
    }

    //If it is player 1's turn, it checks all the possible moves and returns the best move
    if(playerTurn == 1){
        maxEval = INT_MIN; //Set the maxEval to the lowest possible value
        //Finds all possible moves
        posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, boards), playerMove), playerMove);
        //Iterates through all possible moves
        for (int i = 0; i < (posMove.size()-1); i += 2) {
            //Finds all possible moves
            posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove), playerMove);

            //If the for-statement has iterated further than should be possible it returns the maxEval
            if(i > posMove.size()-1){
                return maxEval;
            }
            //Sets the start and end position for the move
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            //Adds the start and end position to the vector moves
            moves.push_back(playerStart);
            moves.push_back(playerMove);
            //Checks if the move is valid
            playerMover(playerStart, playerMove, playerTurn, tempBoard);
            //Checks if the piece has jumped
            jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
            //Checks if the piece has been promoted
            promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);

            //If the piece is able to jump again and hasnt been promoted, it iterates through all possible moves
            while(moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove) && jumped && !promotion){
                posMove = movePossible(playerTurn, tempBoard, jumpPossible(playerTurn, tempBoard), moreMoveCheck(jumpPossible(playerTurn, tempBoard), playerMove), playerMove);
                //Sets the start and end position for the move and adds it to the vector moves
                playerStart = posMove[0];
                moves.push_back(playerStart);
                playerMove = posMove[1];
                moves.push_back(playerMove);
                playerMover(playerStart, playerMove, playerTurn, tempBoard);
                //Checks if the piece has jumped or been promoted
                jumped = pieceJump(playerStart, playerMove, playerTurn, tempBoard);
                promotion = boardChange(playerTurn, tempBoard, playerStart, playerMove, redPieces2, blackPieces2);
            }
            //Sets eval to the value that is being return by the alphaBeta function
            eval = alphaBeta(tempBoard, depth-1, 2, blackPieces2, redPieces2, boards2, moveSet, alpha, beta);

            //If the eval is higher than the maxEval, it sets the maxEval to eval and sets the bestBoard and bestMoves to the current board and moves
            if(maxEval < eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
                alpha = eval;
            }

            //If eval is higher than beta, it breaks the for-loop
            if(eval > beta){
                break;
            }

            //Resets the board, pieces, and moves
            tempBoard = boards;
            blackPieces2 = blackPieces;
            redPieces2 = redPieces;
            playerStart = {};
            playerMove = {};
            moves = {};
        }

        //Sets the board and moves to the bestBoard and bestMoves
        boards2 = bestBoard;
        moveSet = bestMoves;
        return maxEval;

    //The same is done for player 2
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

            eval = alphaBeta(tempBoard, depth-1, 1, blackPieces2, redPieces2, boards2, moveSet, alpha, beta);

            if(maxEval > eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
                beta = eval;
            }

            if(eval < alpha){
                break;
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
