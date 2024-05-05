#include "alphabeta.h"
#include "opencv2/core/cvdef.h"

// The constructor for the alphaBeta class with no defined values
alphaBeta::alphaBeta(validMoves* vm):_vm(vm){
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

alphaBeta::alphaBeta(validMoves* vm, std::string setValues):_vm(vm){
    _piece = 10;
    _king = 20;
    _lock = 5;
    _lockKing = 5;
    _forward = 2;
    _TwoEmpty = 20;
    _OneJump = 50;
    _OneEmpty = 10;
    _TwoJump = 80;
    _depth = 2;
}

alphaBeta::alphaBeta(validMoves* vm, int depth):_depthAI(depth), _vm(vm){}

// The constructor for the alphaBeta class with defined values
alphaBeta::alphaBeta(validMoves* vm, double id, double piece, double king, double lock, double lockKing, double forward, double TwoEmpty, double OneJump, double OneEmpty, double TwoJump, double depth) {
    _vm = vm;
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
    _id = id;
}

void alphaBeta::allTimeID(){
    // Finds the id in the database that matches the values
    query.prepare("SELECT ai_id "
                  "FROM allTime "
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

std::vector<std::string> alphaBeta::jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards){
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

std::vector<std::string> alphaBeta::movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards){
    char column;
    char column2;
    std::vector<std::string> posMove = {};
    std::vector<std::string> playerJump = jumpPossible(playerTurn, boards);

    //If a jump is possible it goes into this if-statement since a jump is mandatory
    if(playerJump.size() > 0){
        //If the player is able to jump again, it checks all the possible jumps for the new board-state
        if(moreMoveCheck()){
            for(int i = 0; i < playerJump.size(); i +=2){
                if(_playerMove == playerJump[i]){
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

// The giveScoreAI function
int alphaBeta::giveScoreAI(std::vector<std::vector<std::string>>& boards, int& playerTurn, int& black, int& red, int& depth){
    double score = 0;

    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, 10); // Define the range for the random number
    int random = distr(eng); // Generate a random number

    // Checks if a jump is possible
    std::vector<std::string> movePossible1 = movePossible(1, boards);
    std::vector<std::string> jump1 = jumpPossible(1, boards);

    std::vector<std::string> movePossible2 = movePossible(2, boards);
    std::vector<std::string> jump2 = jumpPossible(2, boards);

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

    if(red == 0 || movePossible2.empty()){
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

    if(black == 0 || movePossible1.empty()){
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
int alphaBeta::findMove(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, int alpha, int beta, std::string playerMove,int& CounterForTempTable){
    int maxEval; //The highest eval
    int eval; //The eval
    bool jumped; //If a piece has jumped
    bool promotion; //If a piece has been promoted
    int bestPlayer; //Keeps track of the playerTurn for the best board
    int bestBlack; //Keeps track of the blackPieces for the best board
    int bestRed; //Keeps track of the redPieces for the best board
    std::vector<std::vector<std::string>> bestBoard; //The best board
    std::vector<std::string> bestMoves; //The best moves
    std::string playerStart; //The start position for the move
    std::vector<std::string> moves; //The moves that have been made during the turn
    setPlayerTurn(playerTurn);
    setPieceCount(blackPieces, redPieces);
    setBoards(boards);
    setMove({}, playerMove);

    //The possible moves for the player
    std::vector<std::string> posMove = validMoves::movePossible();

    //If the depth is 0, the game is in a winning state, or no moves are possible, it returns the score of the board
    if( depth == 0 || posMove.empty() || blackPieces == 0 || redPieces == 0) {
        return giveScoreAI(boards, playerTurn, blackPieces, redPieces, depth);
    }

    //If it is player 1's turn, it checks all the possible moves and returns the best move
    if(playerTurn == 1){
        maxEval = INT_MIN; //Set the maxEval to the lowest possible value

        //Iterates through all possible moves
        for (int i = 0; i < (posMove.size()-1); i += 2) {
            //Sets the start and end position for the move
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            std::string MoveMade = playerStart + playerMove;
            //Adds the start and end position to the vector moves
            setMove(playerStart, playerMove);

            if (depth == 1){
                // insertAlphaBetaToTemp(boards, MoveMade, playerTurn, CounterForTempTable);
            }

            //Checks if the piece has jumped
            jumped = pieceJump();
            // Checks if the piece has been promoted
            promotion = boardChange();

            // Sets the number of pieces for black and red
            blackPieces = getPieceCount()[0];
            redPieces = getPieceCount()[1];

            validMoves::jumpPossible();
            bool moreJump = moreMoveCheck();

            // If the piece is able to jump again the turn doesnt change
            if(moreJump && jumped && !promotion){
                eval = findMove(getBoards(), depth, 1, blackPieces, redPieces, alpha, beta, playerMove, CounterForTempTable);
            } else {
                eval = findMove(getBoards(), depth-1, 2, blackPieces, redPieces, alpha, beta, {}, CounterForTempTable);
            }

            //If the eval is higher than the maxEval, it sets the maxEval to eval and sets the bestBoard, bestMoves, bestPieces and playerTurn to the match the board
            if(maxEval < eval){
                maxEval = eval;
                bestBoard = getBoards();
                bestMoves = {playerStart, playerMove};
                bestBlack = getPieceCount()[0];
                bestRed = getPieceCount()[1];

                if(moreJump && jumped && !promotion){
                    bestPlayer = 1;
                } else {
                    bestPlayer = 2;
                }
            }

            alpha = MAX(maxEval, alpha);

            //If alpha is higher than beta, it breaks the for-loop
            if(alpha >= beta){
                break;
            }


            //Resets the board, pieces, and moves
            setBoards(boards);
            setPieceCount(blackPieces, redPieces);
            setPlayerTurn(playerTurn);
            setMove("", playerMove);
        }

        //Sets the best values found to the variables that are returned
        _boards = bestBoard;
        _playerStart = bestMoves[0];
        _playerMove = bestMoves[1];
        _blackPieces = bestBlack;
        _redPieces = bestRed;
        _playerTurn = bestPlayer;
        setPlayerTurn(bestPlayer);

        return maxEval;

        //The same is done for player 2
    } else {
        maxEval = INT_MAX;
        for (int i = 0; i < (posMove.size()-1); i += 2) {
            playerStart = posMove[i];
            playerMove = posMove[i+1];
            std::string MoveMade = playerStart + playerMove;
            setMove(playerStart, playerMove);

            if (depth == 1){
                // insertAlphaBetaToTemp(boards, MoveMade, playerTurn, CounterForTempTable);
            }

            jumped = pieceJump();
            promotion = boardChange();
            // Sets the number of pieces for black and red
            blackPieces = getPieceCount()[0];
            redPieces = getPieceCount()[1];

            validMoves::jumpPossible();
            bool moreJump = moreMoveCheck();

            if(moreJump && jumped && !promotion){
                eval = findMove(getBoards(), depth, 2, blackPieces, redPieces, alpha, beta, playerMove,CounterForTempTable);
            } else {
                eval = findMove(getBoards(), depth-1, 1, blackPieces, redPieces, alpha, beta, {},CounterForTempTable);
            }

            if(maxEval > eval){
                maxEval = eval;
                bestBoard = getBoards();
                bestMoves = {playerStart, playerMove};
                bestBlack = getPieceCount()[0];
                bestRed = getPieceCount()[1];
                beta = eval;               

                if(moreJump && jumped && !promotion){
                    bestPlayer = 2;
                } else {
                    bestPlayer = 1;
                }
            }

            beta = MIN(maxEval, beta);

            if(alpha >= beta){
                break;
            }

            //Resets the board, pieces, and moves
            setBoards(boards);
            setPieceCount(blackPieces, redPieces);
            setPlayerTurn(playerTurn);
            setMove("", playerMove);
        }
        _boards = bestBoard;
        _playerStart = bestMoves[0];
        _playerMove = bestMoves[1];
        _blackPieces = bestBlack;
        _redPieces = bestRed;
        _playerTurn = bestPlayer;
        setPlayerTurn(bestPlayer);
        return maxEval;
    }
}

// Returns the id of the alphaBeta object
int alphaBeta::getId() {
    return _id;
}

std::vector<std::string> alphaBeta::getMove(){
    return {_playerStart, _playerMove};
}

// Changes the values of the alphaBeta object to new random values
void alphaBeta::evolve(double rate){
    // Multiply all values by a random number between 0.7 and 1.3
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(1-rate, 1+rate); // Define the range for the random number
    std::uniform_real_distribution<> evolveChance(0, 100); // Only if number is higher than 90 will the value be evolved
    if(evolveChance(eng) > 90){
        _piece *= distr(eng); // Generate a random number
    }
    if(evolveChance(eng) > 90){
        _king *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _lock *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _lockKing *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _forward *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _TwoEmpty *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _OneJump *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _OneEmpty *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _TwoJump *= distr(eng);
    }
    if(evolveChance(eng) > 90){
        _depth *= distr(eng);
    }

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

// Insert the object into the database
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

// Adds a winner to the database
void alphaBeta::addWinner(){
    query.prepare("SELECT (winner.wins + (winner.draws * 0.33)) AS winrate "
                  "FROM points "
                  "JOIN winner ON points.ai_id = winner.ai_id "
                  "WHERE points.ai_id = :id");
    query.bindValue(":id", _id);
    query.exec();
    query.next();
    double winrate = query.value(0).toDouble();

    if(winrate < 10){
        return;
    }

    query.prepare("SELECT COUNT(*) FROM allTime WHERE ai_id = :id");
    query.bindValue(":id", _id);
    query.exec();
    query.next(); // Move to the first record
    int count = query.value(0).toInt();

    if (count > 0) {
        // AI ID exists, update the existing record
        query.prepare("UPDATE allTime SET winrate = :winrate WHERE ai_id = :id");
        query.bindValue(":winrate", winrate);
        query.bindValue(":id", _id);
        query.exec();

    } else {
        // AI ID does not exist, insert a new record
        query.prepare("INSERT INTO allTime(ai_id, piece, king, locked, lockKing, forward, TwoEmpty, OneJump, "
                            "OneEmpty, TwoJump, depth, winrate) "
                            "VALUES (:id, :piece, :king, :lock, :lockKing, :forward, :TwoEmpty, :OneJump, :OneEmpty, "
                            ":TwoJump, :depth, :winrate)");
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
        query.bindValue(":winrate", winrate);
        query.exec();
    }
}

void alphaBeta::makeMove(std::vector<std::vector<std::string>> boards, int depth, int playerTurn, int blackPieces, int redPieces, int alpha, int beta, std::string playerMove,int& CounterForTempTable){
    findMove(boards, depth, playerTurn, blackPieces, redPieces, alpha, beta, playerMove, CounterForTempTable);
    _vm -> DB_move(_playerStart, _playerMove);
}

