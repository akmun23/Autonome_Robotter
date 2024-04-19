#include "alphabeta.h"
#include "CheckersDatabase.h"
#include "validmoves.h"

// The constructor for the alphaBeta class with no defined values
alphaBeta::alphaBeta() {
    // Multiply all values by a random number between 0.7 and 1.3
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(0.7, 1.3); // Define the range for the random number
    _piece *= distr(eng); // Generate a random number
    _king *= distr(eng);
    _lock *= distr(eng);
    _lockKing *= distr(eng);
    _forward *= distr(eng);
    _TwoEmpty *= distr(eng);
    _OneJump *= distr(eng);
    _OneEmpty *= distr(eng);
    _TwoJump *= distr(eng);
    _depth *= distr(eng);
}

alphaBeta::alphaBeta(int depth) : _depth(depth){}

// The constructor for the alphaBeta class with defined values
alphaBeta::alphaBeta(double piece, double king, double lock, double lockKing, double forward, double TwoEmpty, double OneJump, double OneEmpty, double TwoJump, double depth) {
    _piece = piece;
    _king = king;
    _lock = lock;
    _lockKing = lockKing;
    _forward = forward;
    _TwoEmpty = TwoEmpty;
    _OneJump = OneJump;
    _OneEmpty = OneEmpty;
    _TwoJump = TwoJump;
    _depth = depth;

    // Finds the id in the database that matches the values
    query.prepare("SELECT ai_id "
                  "FROM points "
                  "WHERE piece = :piece "
                  "AND king <= :king "
                  "AND locked = :lock "
                  "AND lockKing = :lockKing "
                  "AND forward = :forward "
                  "AND TwoEmpty = :TwoEmpty "
                  "AND OneJump = :OneJump "
                  "AND OneEmpty = :OneEmpty "
                  "AND TwoJump = :TwoJump "
                  "AND depth = :depth");
    query.bindValue(":piece", _piece);
    query.bindValue(":king", _king);
    query.bindValue(":lock", _lock);
    query.bindValue(":lockKing", _lockKing);
    query.bindValue(":forward", _forward);
    query.bindValue(":TwoEmpty", _TwoEmpty);
    query.bindValue(":OneJump", _OneJump);
    query.bindValue(":OneEmpty", _OneEmpty);
    query.bindValue(":TwoJump", _TwoJump);
    query.bindValue(":depth", _depth);
    query.exec();

    while(query.next()){
        _id = query.value(0).toInt();
    }
}

// The giveScoreAI function
int alphaBeta::giveScoreAI(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth){
    double score = 0;

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
                score += _piece;
                score += i/_forward;
                if((i == 5) && (boards[i+2][j] == "R " || boards[i+2][j] == "RK")){
                    score += _lock;
                }
                if((j == 2) && (boards[i][j-2] == "R " || boards[i][j-2] == "RK")){
                    score += _lock;
                } else if((j == 5) && (boards[i][j+2] == "R " || boards[i][j+2] == "RK")){
                    score += _lock;
                }
            }
            else if(boards[i][j] == "BK"){
                score += _king;
                if((i == 5) && (boards[i+2][j] == "R " || boards[i+2][j] == "RK")){
                    score += _lockKing;
                } else if((i == 2) && (boards[i-2][j] == "R " || boards[i-2][j] == "RK")){
                    score += _lockKing;
                }
                if((j == 2) && (boards[i][j-2] == "R " || boards[i][j-2] == "RK")){
                    score += _lockKing;
                } else if((j == 5) && (boards[i][j+2] == "R " || boards[i][j+2] == "RK")){
                    score += _lockKing;
                }
            }
            else if(boards[i][j] == "R "){
                score -= _piece;
                score -= -(4-(i+1)/_forward);
                if((i == 2) && (boards[i-2][j] == "B " || boards[i-2][j] == "BK")){
                    score -= _lock;
                }
                if((j == 2) && (boards[i][j-2] == "B " || boards[i][j-2] == "BK")){
                    score -= _lock;
                } else if((j == 5) && (boards[i][j+2] == "B " || boards[i][j+2] == "BK")){
                    score -= _lock;
                }
            }
            else if(boards[i][j] == "RK"){
                score -= _king;
                if((i == 2) && (boards[i-2][j] == "B " || boards[i-2][j] == "BK")){
                    score -= _lockKing;
                } else if((i == 5) && (boards[i+2][j] == "B " || boards[i+2][j] == "BK")){
                    score -= _lockKing;
                }
                if((j == 2) && (boards[i][j-2] == "B " || boards[i][j-2] == "BK")){
                    score -= _lockKing;
                } else if((j == 5) && (boards[i][j+2] == "B " || boards[i][j+2] == "BK")){
                    score -= _lockKing;
                }
            }
        }
    }

    //Gives score depending on the jumps that are possible
    //And if the game is in a winning state

    if(jump2.empty()){
        score += _TwoEmpty;
        if(!(jump1.empty())){
            score += _OneJump;
        }
    }

    if(jump1.empty()){
        score -= _OneEmpty;
        if(!(jump2.empty())){
            score -= _TwoJump;
        }
    }

    if(red == 0 || movePossible(2, boards, jump2, moreMove, move).empty()){
        score += 10000;
    }

    if(jump1.empty()){
        score -= _TwoEmpty;
        if(!jump2.empty()){
            score -= _OneJump;
        }
    }

    if(jump2.empty()){
        score += _OneEmpty;
        if(!(jump1.empty())){
            score += _TwoJump;
        }
    }

    if(black == 0 || movePossible(1, boards, jump1, moreMove, move).empty()){
        score -= 10000;
    }

    if(playerTurn == 1){
        score += depth*_depth;
    } else {
        score -= depth*_depth;
    }

    score *= 1000;

    if(playerTurn == 1){
        score += random;
    } else {
        score -= random;
    }

    int roundedScore = score;

    //Returns the score
    return roundedScore;
}

// The alphaBeta function
int alphaBeta::moveAI(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, std::vector<std::vector<std::string>>& boards2, std::vector<std::string>& moveSet, int alpha, int beta, int& blackPieces2, int& redPieces2, int& playerTurn2, std::string playerMove,int& CounterForTempTable){
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
        return giveScoreAI(boards, tempPlayer, blackPieces, redPieces, depth);
    }

    //If it is player 1's turn, it checks all the possible moves and returns the best move
    if(tempPlayer == 1){
        maxEval = INT_MIN; //Set the maxEval to the lowest possible value

        //Iterates through all possible moves
        for (int i = 0; i < (posMove.size()-1); i += 2) {

            //Sets the start and end position for the move
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            std::string MoveMade = playerStart + playerMove;
            //Adds the start and end position to the vector moves
            moves.push_back(playerStart);
            moves.push_back(playerMove);


            //Checks if the piece has jumped
            jumped = pieceJump(playerStart, playerMove, tempPlayer, tempBoard);
            if (depth == 1){
                //insertAlphaBetaToTemp(tempBoard, MoveMade, playerTurn, CounterForTempTable);
            }

            //Checks if the piece has been promoted
            promotion = boardChange(tempPlayer, tempBoard, playerStart, playerMove, tempRed, tempBlack);

            //If the piece is able to jump again the turn doesnt change
            jumps = jumpPossible(tempPlayer, tempBoard);

            if(moreMoveCheck(jumps, playerMove) && jumped && !promotion){
                eval = moveAI(tempBoard, depth, 1, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, playerMove,CounterForTempTable);
            } else {
                eval = moveAI(tempBoard, depth-1, 2, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, {},CounterForTempTable);
            }

            //If the eval is higher than the maxEval, it sets the maxEval to eval and sets the bestBoard, bestMoves, bestPieces and playerTurn to the match the board
            if(maxEval < eval){
                maxEval = eval;
                bestBoard = tempBoard;
                bestMoves = moves;
                bestBlack = tempBlack;
                bestRed = tempRed;
                alpha = eval;
                if(moreMoveCheck(jumps, playerMove) && jumped && !promotion){
                    bestPlayer = 1;
                } else {
                    bestPlayer = 2;
                }
            }

            //If eval is higher than beta, it breaks the for-loop
            if(eval > beta){
                break;
            }

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
            std::string MoveMade = playerStart + playerMove;
            moves.push_back(playerStart);
            moves.push_back(playerMove);

            if (depth == 1){
                //insertAlphaBetaToTemp(tempBoard, MoveMade, playerTurn, CounterForTempTable);
            }

            jumped = pieceJump(playerStart, playerMove, tempPlayer, tempBoard);
            promotion = boardChange(tempPlayer, tempBoard, playerStart, playerMove, tempRed, tempBlack);
            bool promotion2 = promotion;


            //If the piece is able to jump again, it finds all possible moves
            jumps = jumpPossible(tempPlayer, tempBoard);
            if(moreMoveCheck(jumps, playerMove) && jumped && !promotion){
                eval = moveAI(tempBoard, depth, 2, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, playerMove,CounterForTempTable);
            } else {
                eval = moveAI(tempBoard, depth-1, 1, tempBlack, tempRed, boards2, moveSet, alpha, beta, redPieces2, blackPieces2, playerTurn2, {},CounterForTempTable);
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
            if(eval < alpha){
                break;
            }
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

int alphaBeta::getId() {
    return _id;
}

// Changes the values of the alphaBeta object to new random values
void alphaBeta::evolve(double rate){
    // Multiply all values by a random number between 0.7 and 1.3
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(1-rate, 1+rate); // Define the range for the random number
    _piece *= distr(eng); // Generate a random number
    _king *= distr(eng);
    _lock *= distr(eng);
    _lockKing *= distr(eng);
    _forward *= distr(eng);
    _TwoEmpty *= distr(eng);
    _OneJump *= distr(eng);
    _OneEmpty *= distr(eng);
    _TwoJump *= distr(eng);
    _depth *= distr(eng);

    query.prepare("UPDATE points "
                  "SET piece = :piece, "
                  "king = :king, "
                  "locked = :lock, "
                  "lockKing = :lockKing, "
                  "forward = :forward, "
                  "TwoEmpty = :TwoEmpty, "
                  "OneJump = :OneJump, "
                  "OneEmpty = :OneEmpty, "
                  "TwoJump = :TwoJump, "
                  "depth = :depth "
                  "WHERE ai_id = :id");
    query.bindValue(":piece", _piece);
    query.bindValue(":king", _king);
    query.bindValue(":lock", _lock);
    query.bindValue(":lockKing", _lockKing);
    query.bindValue(":forward", _forward);
    query.bindValue(":TwoEmpty", _TwoEmpty);
    query.bindValue(":OneJump", _OneJump);
    query.bindValue(":OneEmpty", _OneEmpty);
    query.bindValue(":TwoJump", _TwoJump);
    query.bindValue(":depth", _depth);
    query.bindValue(":id", _id);
    query.exec();
}

// Resets the wins for the AI
void alphaBeta::resetWins(){
    query.prepare("UPDATE winner "
                  "SET wins = 0, loses = 0, draws = 0 "
                  "WHERE ai_id = :id");
    query.bindValue(":id", _id);
    query.exec();
}

void alphaBeta::dbInsert(){
    query.prepare("INSERT INTO points(piece, king, locked, lockKing, forward, TwoEmpty, OneJump, OneEmpty, TwoJump, depth) "
                  "VALUES (:piece, :king, :lock, :lockKing, :forward, :TwoEmpty, :OneJump, :OneEmpty, :TwoJump, :depth)");
    query.bindValue(":piece", _piece);
    query.bindValue(":king", _king);
    query.bindValue(":lock", _lock);
    query.bindValue(":lockKing", _lockKing);
    query.bindValue(":forward", _forward);
    query.bindValue(":TwoEmpty", _TwoEmpty);
    query.bindValue(":OneJump", _OneJump);
    query.bindValue(":OneEmpty", _OneEmpty);
    query.bindValue(":TwoJump", _TwoJump);
    query.bindValue(":depth", _depth);
    query.exec();

    query.exec("SELECT LAST_INSERT_ID() FROM points");
    while(query.next()){
        _id = query.value(0).toDouble();
    };

    query.prepare("INSERT INTO winner(ai_id) "
                  "VALUES (:id)");
    query.bindValue(":id", _id);
    query.exec();
}

void alphaBeta::addWinner(){
    query.prepare("INSERT INTO allTime(ai_id, piece, king, locked, lockKing, forward, TwoEmpty, OneJump, OneEmpty, TwoJump, depth) "
                  "VALUES (:id, :piece, :king, :lock, :lockKing, :forward, :TwoEmpty, :OneJump, :OneEmpty, :TwoJump, :depth)");
    query.bindValue(":id", _id);
    query.bindValue(":piece", _piece);
    query.bindValue(":king", _king);
    query.bindValue(":lock", _lock);
    query.bindValue(":lockKing", _lockKing);
    query.bindValue(":forward", _forward);
    query.bindValue(":TwoEmpty", _TwoEmpty);
    query.bindValue(":OneJump", _OneJump);
    query.bindValue(":OneEmpty", _OneEmpty);
    query.bindValue(":TwoJump", _TwoJump);
    query.bindValue(":depth", _depth);
    query.exec();
}

