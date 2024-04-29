#include "validmoves.h"
#include "CheckersDatabase.h"

//Constructor for validMoves
validMoves::validMoves(){}

//Constructor for validMoves
validMoves::validMoves(std::string playerStart, std::string playerMove, int playerTurn, int& blackPieces, int& redPieces, std::vector<std::vector<std::string>>& boards){
    _playerStart = playerStart;
    _playerMove = playerMove;
    _playerTurn = playerTurn;
    _blackPieces = blackPieces;
    _redPieces = redPieces;
    _boards = boards;
}

//Function to get the player's input
bool validMoves::playerInput() {
    bool valid = false; //If the player's input is valid

    //Loop to get the player's input until a valid one is given
    while(!valid){
        std::cout << "Player " << _playerTurn << ", please enter the coordinates of the piece you would like to move (e.g. A3): ";
        std::cin >> _playerStart;
        std::cout << "Player " << _playerTurn << ", please enter the coordinates of the square you would like to move to (e.g. B4): ";
        std::cin >> _playerMove;
        std::cout << std::endl;

        //Checks if the input has the correct number of characters
        if(_playerStart.length() != 2 || _playerMove.length() != 2) {
            std::cout << "Invalid move. Please enter a move in the format A3." << std::endl;
            valid = false;
        }
        else {
            //Converts the player's input to lowercase
            _playerStart[0] = tolower(_playerStart[0]);
            _playerMove[0] = tolower(_playerMove[0]);
            valid = true;
        }
    }
    //Returns true if the move is valid, which it must be to break out of the while-loop
    return true;
}

//Returns a vector of possible jump moves for a player
std::vector<std::string> validMoves::jumpPossible(){
    _playerJump = {}; //Vector used to store all possible jump moves for a player
    char column = 'a'; //Variable used to set push the correct column where the player starts the turn to the vector playerJump
    char column2 = 'a'; //Variable used to set push the correct column where the player ends the turn to the vector playerJump

    //Iterates through all spaces on the board and checks if a jump is possible
    for(int i = 0; i < 8; i++){
        column = 'a' + i;
        for(int j = 0; j < 8; j++){
            if(_boards[i][j] == "1 " || _boards[i][j] == "  "){
                continue;
            }
            //Normal pieces can only jump forward. For black this means increasing the row number, for red it means decreasing the row number
            //Kings can jump in all directions
            if((i == 0) || (i == 1)){ //checks if the player's piece is close to the edge of the board
                if((_playerTurn == 1) && (_boards[i][j] == "B " || _boards[i][j] == "BK")){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((_boards[i+1][j+1] == "R ") || (_boards[i+1][j+1] == "RK")) && (_boards[i+2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((_boards[i+1][j-1] == "R ") || (_boards[i+1][j-1] == "RK")) && (_boards[i+2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((_playerTurn == 2) && (_boards[i][j] == "RK")){ //Checks if the checker belongs to player 2 and if a jump is possible
                    if((j < 6) && ((_boards[i+1][j+1] == "B ") || (_boards[i+1][j+1] == "BK")) && (_boards[i+2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((_boards[i+1][j-1] == "B ") || (_boards[i+1][j-1] == "BK")) && (_boards[i+2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            } else if((i == 6) || (i == 7)){ //checks if the player's piece is close to the edge of the board
                if((_playerTurn == 2) && ((_boards[i][j] == "R ") || (_boards[i][j] == "RK"))){ //Checks if the checker belongs to player 2 and if a jump is possible
                    if((j < 6) && ((_boards[i-1][j+1] == "B ") || (_boards[i-1][j+1] == "BK")) && (_boards[i-2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((_boards[i-1][j-1] == "B ") || (_boards[i-1][j-1] == "BK")) && (_boards[i-2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((_playerTurn == 1) && (_boards[i][j] == "BK")){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((_boards[i-1][j+1] == "R ") || (_boards[i-1][j+1] == "RK")) && (_boards[i-2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((_boards[i-1][j-1] == "R ") || (_boards[i-1][j-1] == "RK")) && (_boards[i-2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            } else { //else it can jump freely
                if((_playerTurn == 1) && ((_boards[i][j] == "B ") || (_boards[i][j] == "BK"))){ //Checks if the checker belongs to player 1 and if a jump is possible
                    if((j < 6) && ((_boards[i+1][j+1] == "R ") || (_boards[i+1][j+1] == "RK")) && (_boards[i+2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((_boards[i+1][j-1] == "R ") || (_boards[i+1][j-1] == "RK")) && (_boards[i+2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                    if((j < 6)  && (_boards[i][j] == "BK") && ((_boards[i-1][j+1] == "R ") || (_boards[i-1][j+1] == "RK")) && (_boards[i-2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && (_boards[i][j] == "BK") && ((_boards[i-1][j-1] == "R ") || (_boards[i-1][j-1] == "RK")) && (_boards[i-2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                } else if((_playerTurn == 2) && ((_boards[i][j] == "R ") || (_boards[i][j] == "RK"))){ //Checks if the checker belongs to player 2 and if a jump is possible
                    if((j < 6) && ((_boards[i-1][j+1] == "B ") || (_boards[i-1][j+1] == "BK")) && (_boards[i-2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && ((_boards[i-1][j-1] == "B ") || (_boards[i-1][j-1] == "BK")) && (_boards[i-2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i - 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                    if((j < 6) && (_boards[i][j] == "RK") && ((_boards[i+1][j+1] == "B ") || (_boards[i+1][j+1] == "BK")) && (_boards[i+2][j+2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j+3));
                    }
                    if((j > 1) && (_boards[i][j] == "RK") && ((_boards[i+1][j-1] == "B ") || (_boards[i+1][j-1] == "BK")) && (_boards[i+2][j-2] == "1 ")){
                        _playerJump.push_back(column + std::to_string(j+1));
                        column2 = 'a' + i + 2;
                        _playerJump.push_back(column2 + std::to_string(j-1));
                    }
                }
            }
        }
    }
    //Returns the constructed vector playerJump
    return _playerJump;
}

//If a jump has been made, this checks if the same piece is able to jump an additional time
bool validMoves::moreMoveCheck() {
    //Iterates through the vector playerJump and checks if the player's piece is able to jump again
    //By comparing where the piece just ended with all the possible jumps for the new board-state
    for (int i = 0; i < _playerJump.size(); i += 2) {
        if(_playerMove == _playerJump[i]){
            return true;
        }
    }
    return false;
}

//Returns a vector of possible moves for a player
//Returns a vector of possible moves for a player
std::vector<std::string> validMoves::movePossible(){
    char column;
    char column2;
    std::vector<std::string> posMove = {};
    jumpPossible();

    //If a jump is possible it goes into this if-statement since a jump is mandatory
    if(_playerJump.size() > 0){
        //If the player is able to jump again, it checks all the possible jumps for the new board-state
        if(moreMoveCheck()){
            for(int i = 0; i < _playerJump.size(); i +=2){
                if(_playerMove == _playerJump[i]){
                    posMove.push_back(_playerJump[i]);
                    posMove.push_back(_playerJump[i+1]);
                }
            }
        } else {
            //Set posMove to all possible jumps, since no piece has jumped yet
            posMove = _playerJump;
        }
        //Returns the vector posMove
        return posMove;
    }

    //If no jump is possible, it goes into this if-statement
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if(_boards[i][j] == "1 " || _boards[i][j] == "  "){
                continue;
            }

            if(_playerTurn == 1 && ((_boards[i][j] == "B ") || (_boards[i][j] == "BK"))){ //If it is player 1's turn, it checks if the player's piece is able to move
                if(i < 7){
                    if((j < 7) && (_boards[i+1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (_boards[i+1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
                if(i > 0){
                    if((j < 7) && (_boards[i][j] == "BK") && (_boards[i-1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (_boards[i][j] == "BK") && (_boards[i-1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }

            } else if((_playerTurn == 2) && ((_boards[i][j] == "R ") || (_boards[i][j] == "RK"))){ //If it is player 2's turn, it checks if the player's piece is able to move
                if(i > 0){
                    if((j < 7) && (_boards[i-1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (_boards[i-1][j-1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i - 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j));
                    }
                }
                if(i < 7){
                    if((j < 7) && (_boards[i][j] == "RK") && (_boards[i+1][j+1] == "1 ")){
                        column = 'a' + i;
                        column2 = 'a' + i + 1;
                        posMove.push_back(column + std::to_string(j+1));
                        posMove.push_back(column2 + std::to_string(j+2));
                    }
                    if((j > 0) && (_boards[i][j] == "RK") && (_boards[i+1][j-1] == "1 ")){
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
bool validMoves::pieceJump(){
    int row = _playerStart[1] - '1'; //Starting row
    int row2 = _playerMove[1] - '1'; //Ending row
    int row3 = row2 + (row-row2)/2; //Middle row
    char column = _playerStart[0]-((_playerStart[0]-_playerMove[0])/2); //Middle column
    column = column - 'a';

    //Checks if the piece is able to jump over an enemy piece
    if(((_boards[column][row3] == "R ") || (_boards[column][row3] == "RK")) && (_playerTurn == 1)){
        return true;
    } else if(((_boards[column][row3] == "B ") || (_boards[column][row3] == "BK")) && (_playerTurn == 2)){
        return true;
    } else {
        return false;
    }
}

//Checks if a piece is able to promote
bool validMoves::promotion(){
    //Checks if a normal piece is on the opposing side of the board
    if(_playerTurn == 1){
        for(int i = 0; i < 8; i++){
            if(_boards[7][i] == "B "){
                return true;
            }
        }
    } else {
        for(int i = 0; i < 8; i++){
            if(_boards[0][i] == "R "){
                return true;
            }
        }
    }
    return false;
}

// Counts the numberstd::vector<std::vector<std::string>> getBoards(); of pieces on the board
int validMoves::pieceCount(){
    int count = 0;
    int count2 = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(_boards[i][j] == "R " || _boards[i][j] == "RK"){
                count2++;
            } else if(_boards[i][j] == "B " || _boards[i][j] == "BK"){
                count++;
            }
        }
    }

    _redPieces = count2;
    _blackPieces = count;

    return count;
}

//Changes the board according to the player's move
bool validMoves::boardChange(){
    std::string piece;
    int row = _playerStart[1] - '1'; //Starting row
    int row2 = _playerMove[1] - '1'; //Ending row
    int row3 = row2 + (row-row2)/2; //Middle row if jump
    int column = _playerStart[0] - 'a'; //Starting column
    int column2 = _playerMove[0] - 'a'; //Ending column
    int column3 = column - (column-column2)/2; //Middle column if jump

    //Changes the board according to the player's move and what piece has been moved
    piece = _boards[column][row];
    _boards[column][row] = "1 ";
    _boards[column2][row2] = piece;

    //Checks if the piece has jumped
    if(pieceJump()){
        //Sets the middle position to empty
        _boards[column3][row3] = "1 ";
    }

    pieceCount();

    //Checks if the piece is able to promote and changes it to a king if it is
    //Returns true if the piece has been promoted
    if(promotion()){
        if(_playerTurn == 1){
            _boards[column2][row2] = "BK";
        } else {
            _boards[column2][row2] = "RK";
        }
        return true;
    }

    //If no promotion has been made, it returns false
    return false;
}

bool validMoves::move(){
    bool valid = false;
    bool jumped = false; //If a piece has jumped
    bool promotion = false; //If a piece has been promoted

    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
    bool moreMove = moreMoveCheck(); //If the player is able to jump again

    //Checks all possible moves
    std::vector<std::string> moves = movePossible();

    while(!valid){
        playerInput();
        for (int i = 0; i < moves.size(); i += 2) {
            if(_playerStart == moves[i] && _playerMove == moves[i+1]){
                jumped = pieceJump();
                promotion = boardChange();
                moveSet.push_back(_playerStart);
                moveSet.push_back(_playerMove);
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
    jumpPossible();
    moreMove = moreMoveCheck();
    if(moreMove && jumped && !promotion){
        return true;
    } else {
        if(_playerTurn == 1){
            _playerTurn = 2;
        } else {
            _playerTurn = 1;
        }
        return true;
    }
}

bool validMoves::DB_move(std::string playerStart, std::string playerMove){ // MoveFunction for database input
    bool valid = false;
    bool jumped = false; //If a piece has jumped
    bool promotion = false; //If a piece has been promoted
    _playerStart = playerStart;
    _playerMove = playerMove;
    std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
    std::vector<std::string> jumps = jumpPossible(); //Checks all possible jumps
    bool moreMove = moreMoveCheck(); //If the player is able to jump again

    //Checks all possible moves
    std::vector<std::string> moves = movePossible();
    while(!valid){
        for (int i = 0; i < moves.size(); i += 2) {
            if(_playerStart == moves[i] && _playerMove == moves[i+1]){
                jumped = pieceJump();
                promotion = boardChange();
                moveSet.push_back(_playerStart);
                moveSet.push_back(_playerMove);
                valid = true;
                break;
            }
        }

        if(!valid){
            std::string move = _playerStart+_playerMove;
            DeleteWrongMove(_boards, move , _playerTurn);
            std::cout << "Move not valid. Please enter a new move." << std::endl;
            return false;
        }
    }

    //If the player is able to jump again, it returns true without changing the playerTurn
    jumps = jumpPossible();
    moreMove = moreMoveCheck();
    if(moreMove && jumped && !promotion){
        return true;
    } else {
        if(_playerTurn == 1){
            _playerTurn = 2;
        } else {
            _playerTurn = 1;
        }
        return true;
    }
}

int validMoves::getPlayerTurn(){
    return _playerTurn;
}

std::vector<std::vector<std::string>> validMoves::getBoards(){
    return _boards;
}

std::vector<int> validMoves::getPieceCount(){
    return {_blackPieces, _redPieces};
}

std::vector<std::string> validMoves::getMove(){
    return {_playerStart, _playerMove};
}

void validMoves::setBoards(std::vector<std::vector<std::string>> boards){
    _boards = boards;
}

void validMoves::setMove(std::string playerStart, std::string playerMove){
    _playerStart = playerStart;
    _playerMove = playerMove;
}

void validMoves::setPlayerTurn(int playerTurn){
    _playerTurn = playerTurn;
}

void validMoves::setPieceCount(int blackPieces, int redPieces){
    _blackPieces = blackPieces;
    _redPieces = redPieces;
}
