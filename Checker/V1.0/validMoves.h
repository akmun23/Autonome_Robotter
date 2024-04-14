#ifndef VALIDMOVES_H
#define VALIDMOVES_H
#include <climits>
#include <iostream>
#include <unistd.h>
#include<vector>
#include<string>
#include <random>
#include "CheckersDatabase.h"

//Function to get the player's input
bool playerInput(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards) {
    bool valid = false; //If the player's input is valid

    //Loop to get the player's input until a valid one is given
    while(!valid){
        std::cout << "Player " << playerTurn << ", please enter the coordinates of the piece you would like to move (e.g. A3): ";
        std::cin >> playerStart;
        std::cout << "Player " << playerTurn << ", please enter the coordinates of the square you would like to move to (e.g. B4): ";
        std::cin >> playerMove;
        std::cout << std::endl;

        //Checks if the input has the correct number of characters
        if(playerStart.length() != 2 || playerMove.length() != 2) {
            std::cout << "Invalid move. Please enter a move in the format A3." << std::endl;
            valid = false;
        }
        else {
            //Converts the player's input to lowercase
            playerStart[0] = tolower(playerStart[0]);
            playerMove[0] = tolower(playerMove[0]);
            valid = true;
        }
    }
    //Returns true if the move is valid, which it must be to break out of the while-loop
    return true;
}

//Returns a vector of possible jump moves for a player
std::vector<std::string> jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards){
    std::vector<std::string> playerJump = {};

    char column = 'a'; //Variable used to set push the correct column where the player starts the turn to the vector playerJump
    char column2 = 'a'; //Variable used to set push the correct column where the player ends the turn to the vector playerJump

    //Iterates through all spaces on the board and checks if a jump is possible
    for(int i = 0; i < 8; i++){
        column = 'a' + i;
        for(int j = 0; j < 8; j++){
            if(boards[i][j] == "1 " || boards[i][j] == "  "){
                continue;
            }
    //Normal pieces can only jump forward. For black this means increasing the row number, for red it means decreasing the row number
    //Kings can jump in all directions
            if((i == 0) || (i == 1)){ //checks if the player's piece is close to the edge of the board
                if((playerTurn == 1) && (boards[i][j] == "B " || boards[i][j] == "BK")){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((boards[i+1][j+1] == "R ") || (boards[i+1][j+1] == "RK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i+1][j-1] == "R ") || (boards[i+1][j-1] == "RK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((playerTurn == 2) && (boards[i][j] == "RK")){ //Checks if the checker belongs to player 2 and if a jump is possible
                    if((j < 6) && ((boards[i+1][j+1] == "B ") || (boards[i+1][j+1] == "BK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                                                                                                                                                                                                        }
                    if((j > 1) && ((boards[i+1][j-1] == "B ") || (boards[i+1][j-1] == "BK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                            }
                }
            } else if((i == 6) || (i == 7)){ //checks if the player's piece is close to the edge of the board
                if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){ //Checks if the checker belongs to player 2 and if a jump is possible
                    if((j < 6) && ((boards[i-1][j+1] == "B ") || (boards[i-1][j+1] == "BK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "B ") || (boards[i-1][j-1] == "BK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((playerTurn == 1) && (boards[i][j] == "BK")){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((boards[i-1][j+1] == "R ") || (boards[i-1][j+1] == "RK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "R ") || (boards[i-1][j-1] == "RK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            } else { //else it can jump freely
                if((playerTurn == 1) && ((boards[i][j] == "B ") || (boards[i][j] == "BK"))){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((boards[i+1][j+1] == "R ") || (boards[i+1][j+1] == "RK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i+1][j-1] == "R ") || (boards[i+1][j-1] == "RK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                    if((j < 6)  && (boards[i][j] == "BK") && ((boards[i-1][j+1] == "R ") || (boards[i-1][j+1] == "RK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && (boards[i][j] == "BK") && ((boards[i-1][j-1] == "R ") || (boards[i-1][j-1] == "RK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){ //Checks if the checker belongs to player 2 and if a jump is possible
                    if((j < 6) && ((boards[i-1][j+1] == "B ") || (boards[i-1][j+1] == "BK")) && (boards[i-2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((boards[i-1][j-1] == "B ") || (boards[i-1][j-1] == "BK")) && (boards[i-2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        playerJump.push_back(column2 + std::to_string(j-1));
                    }
                    if((j < 6) && (boards[i][j] == "RK") && ((boards[i+1][j+1] == "B ") || (boards[i+1][j+1] == "BK")) && (boards[i+2][j+2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && (boards[i][j] == "RK") && ((boards[i+1][j-1] == "B ") || (boards[i+1][j-1] == "BK")) && (boards[i+2][j-2] == "1 ")){
                        playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
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
bool moreMoveCheck(std::vector<std::string>& playerJump, std::string& playerMove) {
    //Iterates through the vector playerJump and checks if the player's piece is able to jump again
    //By comparing where the piece just ended with all the possible jumps for the new board-state
    for (int i = 0; i < playerJump.size(); i += 2) {
        if(playerMove == playerJump[i]){
            return true;
        }
    }

    return false;
}

//Returns a vector of possible moves for a player
std::vector<std::string> movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards, std::vector<std::string>& playerJump, bool& moreMove, std::string& playerMove){
    char column;
    char column2;
    std::vector<std::string> posMove = {};

    //If a jump is possible it goes into this if-statement since a jump is mandatory
    if(playerJump.size() > 0){
        //If the player is able to jump again, it checks all the possible jumps for the new board-state
        if(moreMove){
            for(int i = 0; i < playerJump.size(); i +=2){
                if(playerMove == playerJump[i]){
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

            if(boards[i][j] == "1 " || boards[i][j] == "  "){
                continue;
            }

            if(playerTurn == 1 && ((boards[i][j] == "B ") || (boards[i][j] == "BK"))){ //If it is player 1's turn, it checks if the player's piece is able to move
                if(i < 7){
                    if((j < 7) && (boards[i+1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i+1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
                if(i > 0){
                    if((j < 7) && (boards[i][j] == "BK") && (boards[i-1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i][j] == "BK") && (boards[i-1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }

            } else if((playerTurn == 2) && ((boards[i][j] == "R ") || (boards[i][j] == "RK"))){ //If it is player 2's turn, it checks if the player's piece is able to move
                if(i > 0){
                    if((j < 7) && (boards[i-1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i-1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
                if(i < 7){
                    if((j < 7) && (boards[i][j] == "RK") && (boards[i+1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (boards[i][j] == "RK") && (boards[i+1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
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
bool pieceJump(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards){
    int row = playerStart[1] - '1'; //Starting row
    int row2 = playerMove[1] - '1'; //Ending row
    int row3 = row2 + (row-row2)/2; //Middle row
    char column = playerStart[0]-((playerStart[0]-playerMove[0])/2); //Middle column
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

//Checks if a piece is able to promote
bool promotion(std::vector<std::vector<std::string>>& boards, int& playerTurn){
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

// Counts the number of pieces on the board
int pieceCount(std::vector<std::vector<std::string>>& boards, int& blackPieces, int& redPieces){
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

    return count;
}

//Changes the board according to the player's move
bool boardChange(int& playerTurn, std::vector<std::vector<std::string>>& boards, std::string& playerStart, std::string& playerMove, int& redPieces, int& blackPieces){
     std::string piece;
     int row = playerStart[1] - '1'; //Starting row
     int row2 = playerMove[1] - '1'; //Ending row
     int row3 = row2 + (row-row2)/2; //Middle row if jump
     int column = playerStart[0] - 'a'; //Starting column
     int column2 = playerMove[0] - 'a'; //Ending column
     int column3 = column - (column-column2)/2; //Middle column if jump

     //Changes the board according to the player's move and what piece has been moved
     piece = boards[column][row];
     boards[column][row] = "1 ";
     boards[column2][row2] = piece;

     //Checks if the piece has jumped
     if(pieceJump(playerStart, playerMove, playerTurn, boards)){
         //Sets the middle position to empty
         boards[column3][row3] = "1 ";
     }

     pieceCount(boards, blackPieces, redPieces);

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

bool move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces){
    bool valid = false;
    bool jumped = false; //If a piece has jumped
    bool promotion = false; //If a piece has been promoted


    //Get the player"s move
    std::string playerStart;
    std::string playerMove;

    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
    std::vector<std::string> jumps = jumpPossible(playerTurn, boards); //Checks all possible jumps
    bool moreMove = moreMoveCheck(jumps, playerMove); //If the player is able to jump again

    //Checks all possible moves
    std::vector<std::string> moves = movePossible(playerTurn, boards, jumps, moreMove, playerMove);

    while(!valid){
        playerInput(playerStart, playerMove, playerTurn, boards);
        for (int i = 0; i < moves.size(); i += 2) {
            if(playerStart == moves[i] && playerMove == moves[i+1]){
                jumped = pieceJump(playerStart, playerMove, playerTurn, boards);
                promotion = boardChange(playerTurn, boards, playerStart, playerMove, redPieces, blackPieces);
                moveSet.push_back(playerStart);
                moveSet.push_back(playerMove);
                valid = true;
                break;
            }
        }

        if(!valid){
            std::cout << "Move not valid. Please enter a new move." << std::endl;
            return false;
        }
    }

    //If the player is able to jump again, it returns true without changing the playerTurn
    jumps = jumpPossible(playerTurn, boards);
    moreMove = moreMoveCheck(jumps, playerMove);
    if(moreMove && jumped && !promotion){
        return true;
    } else {
        if(playerTurn == 1){
            playerTurn = 2;
        } else {
            playerTurn = 1;
        }
        return true;
    }
}

bool DB_move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::string playerStart, std::string playerMove){ // MoveFunction for database input
    bool valid = false;
    bool jumped = false; //If a piece has jumped
    bool promotion = false; //If a piece has been promoted

    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
    std::vector<std::string> jumps = jumpPossible(playerTurn, boards); //Checks all possible jumps
    bool moreMove = moreMoveCheck(jumps, playerMove); //If the player is able to jump again

    //Checks all possible moves
    std::vector<std::string> moves = movePossible(playerTurn, boards, jumps, moreMove, playerMove);

    while(!valid){
        for (int i = 0; i < moves.size(); i += 2) {
            if(playerStart == moves[i] && playerMove == moves[i+1]){
                jumped = pieceJump(playerStart, playerMove, playerTurn, boards);
                promotion = boardChange(playerTurn, boards, playerStart, playerMove, redPieces, blackPieces);
                moveSet.push_back(playerStart);
                moveSet.push_back(playerMove);
                valid = true;
                break;
            }
        }

        if(!valid){
            std::cout << "Move not valid. Please enter a new move." << std::endl;
            return false;
        }
    }

    //If the player is able to jump again, it returns true without changing the playerTurn
    jumps = jumpPossible(playerTurn, boards);
    moreMove = moreMoveCheck(jumps, playerMove);
    if(moreMove && jumped && !promotion){
        return true;
    } else {
        if(playerTurn == 1){
            playerTurn = 2;
        } else {
            playerTurn = 1;
        }
        return true;
    }
}

//Gives the board a game score based on the number of pieces and the number of possible moves
//Used in the alphaBeta function
int giveBoardScore(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth){
    int score = 0;

    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, 10); // Define the range for the random number
    int random = distr(eng); // Generate a random number

    // Checks if a jump is possible
    std::vector<std::string> jump1 = jumpPossible(1, boards);
    std::vector<std::string> jump2 = jumpPossible(2, boards);

    bool moreMove = false;
    std::string move = "";

    //Gives score depending on the number of pieces on the board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(boards[i][j] == "B "){
                score += 10;
                score += i/2;
                if((i == 5) && (boards[i+2][j] == "R " || boards[i+2][j] == "RK")){
                    score += 5;
                }
                if((j == 2) && (boards[i][j-2] == "R " || boards[i][j-2] == "RK")){
                    score += 5;
                } else if((j == 5) && (boards[i][j+2] == "R " || boards[i][j+2] == "RK")){
                    score += 5;
                }
            }
            else if(boards[i][j] == "BK"){
                score += 20;
                if((i == 5) && (boards[i+2][j] == "R " || boards[i+2][j] == "RK")){
                    score += 5;
                } else if((i == 2) && (boards[i-2][j] == "R " || boards[i-2][j] == "RK")){
                    score += 5;
                }
                if((j == 2) && (boards[i][j-2] == "R " || boards[i][j-2] == "RK")){
                    score += 5;
                } else if((j == 5) && (boards[i][j+2] == "R " || boards[i][j+2] == "RK")){
                    score += 5;
                }
            }
            else if(boards[i][j] == "R "){
                score -= 10;
                score -= -(4-(i+1)/2);
                if((i == 2) && (boards[i-2][j] == "B " || boards[i-2][j] == "BK")){
                    score -= 5;
                }
                if((j == 2) && (boards[i][j-2] == "B " || boards[i][j-2] == "BK")){
                    score -= 5;
                } else if((j == 5) && (boards[i][j+2] == "B " || boards[i][j+2] == "BK")){
                    score -= 5;
                }
            }
            else if(boards[i][j] == "RK"){
                score -= 20;
                if((i == 2) && (boards[i-2][j] == "B " || boards[i-2][j] == "BK")){
                    score -= 5;
                } else if((i == 5) && (boards[i+2][j] == "B " || boards[i+2][j] == "BK")){
                    score -= 5;
                }
                if((j == 2) && (boards[i][j-2] == "B " || boards[i][j-2] == "BK")){
                    score -= 5;
                } else if((j == 5) && (boards[i][j+2] == "B " || boards[i][j+2] == "BK")){
                    score -= 5;
                }
            }
        }
    }

    //Gives score depending on the jumps that are possible
    //And if the game is in a winning state

   if(jump2.empty()){
        score += 20;
        if(!(jump1.empty())){
            score += 50;
        }
    }

    if(jump1.empty()){
        score -= 10;
        if(!(jump2.empty())){
            score -= 80;
        }
    }

    if(red == 0 || movePossible(2, boards, jump2, moreMove, move).empty()){
        score += 10000;
    }

    if(jump1.empty()){
        score -= 20;
        if(!jump2.empty()){
            score -= 50;
        }
    }

    if(jump2.empty()){
        score += 10;
        if(!(jump1.empty())){
            score += 80;
        }
    }

    if(black == 0 || movePossible(1, boards, jump1, moreMove, move).empty()){
        score -= 10000;
    }

    if(playerTurn == 1){
        score += depth*10;
    } else {
        score -= depth*10;
    }

    score *= 1000;

    if(playerTurn == 1){
        score += random;
    } else {
        score -= random;
    }

    //Returns the score
    return score;
}

// The alphaBeta function
int alphaBeta(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet, int alpha, int beta, int& blackPieces2, int& redPieces2, int& playerTurn2, std::string playerMove, int& CounterForTempTable, int& TurnNr){

    QSqlDatabase db = QSqlDatabase::database("QMYSQL");                         // Opretter forbindelse til databasen
    QSqlQuery query = QSqlQuery(db);

    int maxEval; //The highest eval
    int eval; //The eval
    bool jumped; //If a piece has jumped
    bool promotion; //If a piece has been promoted
    int bestPlayer; //Keeps track of the playerTurn for the best board
    int bestBlack; //Keeps track of the blackPieces for the best board
    int bestRed; //Keeps track of the redPieces for the best board
    int tempBlack = blackPieces; //Keeps track of the blackPieces
    int tempRed = redPieces; //Keeps track of the redPieces
    int tempPlayer = playerTurn; //Keeps track of the playerTurn
    std::vector<std::vector<std::string>> tempBoard = boards; //Keeps track of the board
    std::vector<std::vector<std::string>> bestBoard; //The best board
    std::string playerStart; //The start position for the move
    std::vector<std::string> moves; //The moves that have been made during the turn
    std::vector<std::string> bestMoves; //The best moves

    //The possible moves for the player
    std::vector<std::string> jumps = jumpPossible(tempPlayer, boards);
    bool moreMove = moreMoveCheck(jumps, playerMove);
    std::vector<std::string> posMove = movePossible(tempPlayer, boards, jumps, moreMove, playerMove);
    moveSet = {}; //Clears the moveSet

    //If the depth is 0, the game is in a winning state, or no moves are possible, it returns the score of the board
    if( depth == 0 || posMove.empty() || tempRed == 0 || tempBlack == 0) {
        return giveBoardScore(boards, tempPlayer, blackPieces, redPieces, depth);
    }

    //If it is player 1's turn, it checks all the possible moves and returns the best move
    if(tempPlayer == 1){
        maxEval = INT_MIN; //Set the maxEval to the lowest possible value

        //Iterates through all possible moves
        for (int i = 0; i < (posMove.size()-1); i += 2) {

            //Sets the start and end position for the move
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            std::string MoveMade = playerStart+playerMove;
            //Adds the start and end position to the vector moves
            moves.push_back(playerStart);
            moves.push_back(playerMove);

            if (depth == 2 || depth == 1){
                insertAlphaBetaToTemp(tempBoard,MoveMade,tempPlayer,CounterForTempTable); // Skal slettes når Database er trænet
            }

            //Checks if the piece has jumped
            jumped = pieceJump(playerStart, playerMove, tempPlayer, tempBoard);

            //Checks if the piece has been promoted
            promotion = boardChange(tempPlayer, tempBoard, playerStart, playerMove, tempRed, tempBlack);
            bool promotion2 = promotion;

            //If the piece is able to jump again the turn doesnt change
            jumps = jumpPossible(tempPlayer, tempBoard);
            if(moreMoveCheck(jumps, playerMove) && jumped && !promotion){
                eval = alphaBeta(tempBoard, depth-1, 1, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, playerMove,CounterForTempTable,TurnNr);
            } else {
                eval = alphaBeta(tempBoard, depth-1, 2, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, {},CounterForTempTable,TurnNr);
            }

            //If the eval is higher than the maxEval, it sets the maxEval to eval and sets the bestBoard, bestMoves, bestPieces and playerTurn to the match the board
            if(maxEval < eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
                bestBlack = tempBlack;
                bestRed = tempRed;
                alpha = eval;
                if(moreMoveCheck(jumps, playerMove) && jumped && !promotion2){
                    bestPlayer = 1;
                } else {
                    bestPlayer = 2;
                }
            }

            //If eval is higher than beta, it breaks the for-loop
            /*
            if(eval > beta){
                break;
            }
            */
            //Resets the board, pieces, and moves
            tempBoard = boards;
            tempBlack = blackPieces;
            tempRed = redPieces;
            tempPlayer = playerTurn;
            playerStart = {};
            playerMove = {};
            moves = {};
        }

        //Sets the best values found to the variables that are returned
            boards2 = bestBoard;
            moveSet = bestMoves;
            blackPieces2 = bestBlack;
            redPieces2 = bestRed;
            playerTurn2 = bestPlayer;
        return maxEval;

    //The same is done for player 2
    } else {
        maxEval = INT_MAX;
        for (int i = 0; i < (posMove.size()-1); i += 2) {
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            std::string MoveMade = playerStart+playerMove;
            //Adds the start and end position to the vector moves
            moves.push_back(playerStart);
            moves.push_back(playerMove);

            if (depth == 2 || depth == 1){
                insertAlphaBetaToTemp(tempBoard,MoveMade,tempPlayer,CounterForTempTable); // Skal slettes når Database er trænet
            }
            jumped = pieceJump(playerStart, playerMove, tempPlayer, tempBoard);
            promotion = boardChange(tempPlayer, tempBoard, playerStart, playerMove, tempRed, tempBlack);
            bool promotion2 = promotion;


            //If the piece is able to jump again, it finds all possible moves
            jumps = jumpPossible(tempPlayer, tempBoard);
            if(moreMoveCheck(jumps, playerMove) && jumped && !promotion){
                eval = alphaBeta(tempBoard, depth-1, 2, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, playerMove,CounterForTempTable,TurnNr);
            } else {
                eval = alphaBeta(tempBoard, depth-1, 1, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, {},CounterForTempTable,TurnNr);
            }
            if(maxEval > eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
                bestBlack = tempBlack;
                bestRed = tempRed;
                beta = eval;

                if(moreMoveCheck(jumps, playerMove) && jumped && !promotion2){
                    bestPlayer = 2;
                } else {
                    bestPlayer = 1;
                }
            }
            /*
            if(eval < alpha){
                break;
            }
            */
            tempBoard = boards;
            tempBlack = blackPieces;
            tempRed = redPieces;
            tempPlayer = playerTurn;
            playerStart = {};
            playerMove = {};
            moves = {};
        }
        boards2 = bestBoard;
        moveSet = bestMoves;
        blackPieces2 = bestBlack;
        redPieces2 = bestRed;
        playerTurn2 = bestPlayer;
        return maxEval;
    }

}


#endif // VALIDMOVES_H
