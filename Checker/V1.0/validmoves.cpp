#include "validmoves.h"


//Function to get the player's input
bool validMoves::playerInput(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards) {
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
std::vector<std::string> validMoves::jumpPossible(int playerTurn, std::vector<std::vector<std::string>>& boards){
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
bool validMoves::moreMoveCheck(std::vector<std::string>& playerJump, std::string& playerMove) {
    //Iterates through the vector playerJump and checks if the player's piece is able to jump again
    //By comparing where the piece just ended with all the possible jumps for the new board-state
    for (int i = 0; i < playerJump.size(); i += 2) {
        if(playerMove == playerJump[i]){
            return true;
        }
    }

}
//Returns a vector of possible moves for a player
//Returns a vector of possible moves for a player
std::vector<std::string> validMoves::movePossible(int playerTurn, std::vector<std::vector<std::string>>& boards, std::vector<std::string>& playerJump, bool& moreMove, std::string& playerMove){
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
bool validMoves::pieceJump(std::string& playerStart, std::string& playerMove, int& playerTurn, std::vector<std::vector<std::string>>& boards){
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
bool validMoves::promotion(std::vector<std::vector<std::string>>& boards, int& playerTurn){
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
int validMoves::pieceCount(std::vector<std::vector<std::string>>& boards, int& blackPieces, int& redPieces){
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
bool validMoves::boardChange(int& playerTurn, std::vector<std::vector<std::string>>& boards, std::string& playerStart, std::string& playerMove, int& redPieces, int& blackPieces){
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

bool validMoves::move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces){
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

bool validMoves::DB_move(int& playerTurn, std::vector<std::vector<std::string>>& boards, int& redPieces, int& blackPieces, std::string playerStart, std::string playerMove){ // MoveFunction for database input
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

