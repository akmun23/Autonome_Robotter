#include <iostream>
#include <opencv2/opencv.hpp>
//#include "boardUpdate.h"
#include "validMoves.h"
//#include "robotMove.h"
//#include <unistd.h>
//#include <ur_rtde/rtde_control_interface.h>
//#include <ur_rtde/rtde_receive_interface.h>

using namespace cv;
using namespace std;

//Circle inherites methods and attribute templates from "Rect"
class Circle : public Rect{
    using Rect::Rect; //Inherites constructor from "Rect"
};

vector<Circle> bCheckers; //Vec consisting of instances of "Circle" for black checkers.
vector<Circle> rCheckers; //Vec consisting of instances of "Circle" for red checkers.
vector<Rect> rectangles; //Vec consisting of instances of "Rect", as segments of board.
vector<int> selected; //Vec consisting of INT, that refer to information of selected Rect.
vector<string> stringPos; //Vec consisting of selected positions.
Mat graveyardDownSized;
Rect graveyardRect(600, 75, 50, 50); //Instance of Rect, used as a graveyard Rect.
int turnVal = 0; //Array containing INT representing how many turns have been taken.
bool startUpMain = true; //Bool, true if code is being run for the first time.
int redCheckers = 12; //Start amount of red checker pieces.
int blackCheckers = 12; //Start amount of black checker pieces.
bool jumpPerformed;
bool startJump;
int currentChecker;
string pos;

Mat3b canvas(500, 1000, Vec3b(255, 255, 255)); //Creates drawing surface, canvas.
string winName = "Project GUI"; //Sets name of window being used.

void clearVecInt(vector<int>& vector){
    for(int i = 0; i < vector.size(); i++){
        vector[i] = 0;
    }

    vector.resize(0);
}

void clearVecString(vector<string>& vector){
    vector.resize(0);
}

//Updates text displayed, depending player turn.
void updateText(){
    string spiller = "Det er spillerens tur.";
    string robot = "Det er robottens tur.";
    string playerTurnString;

    ((turnVal%2 == 0) ? playerTurnString = spiller : playerTurnString = robot);

    rectangle(canvas, Point(115,0), Point(500,35), Scalar(255,255,255), -1); //Creates a white rectangle, that covers the old text.
    putText(canvas, playerTurnString, Point(115, 25), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1); //Prints new text.
}

//Finds the "ID" of given element in given array, and returns the ID.
int findInVector(string input[], string wantFound){
    for(int i = 0; i < 8; i++){
        if(input[i].compare(wantFound) == 0){
           return i; 
        }
    }
    return 0;
}

//Converts position as "INT" to position described as string.
void posToStringConvert(int x, int y, vector<string>& stringPos){
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    string col;
    string row;

    col = numArr[findInVector(numArr,to_string((x-boardOffSetX/2)/50))];
    row = alphabetArr[findInVector(alphabetArr,alphabetArr[(y-boardOffSetY)/50])];

    stringPos.push_back(row + col);
}

//Draws all elements of the GUI.
void Draw(bool& startUpMain){
    int lineNum = 0;
    int width = 50;
    int height = 50;
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    //If first time running the code, run this section.
    if(startUpMain){
        
        //Generates row and col names along board edge.
        for(int i = 0; i < 8; i++){
            putText(canvas, numArr[i], Point({(i * 50) + boardOffSetX + 12}, {boardOffSetY - 5}), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
            putText(canvas, alphabetArr[i], Point({boardOffSetX - 30}, {(i * 50) + boardOffSetY + 35}), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
        }

        //Loads graveyard segment image, and resizes it to fit inside rect.
        resize(imread("/home/mads-hyrup/Uni/2.-Semester/SemesterProjekt/Projekt/graveyard.jpg"), graveyardDownSized, Size(graveyardRect.width, graveyardRect.height), INTER_LINEAR);
        graveyardDownSized.copyTo(canvas(graveyardRect)); //Draws graveyard onto canvas.

        //Generates board pieces and checkers, while also filling up the corresponding vectors with instances of corresponding vectors.
        for(int i = 0; i < 64; i++){
            int x = (i%8) * 50 + boardOffSetX;
            int y = lineNum * 50 + boardOffSetY;

            rectangles.push_back(Rect(x,y,width,height));

            if(i%2){
                if(lineNum%2){
                    canvas(rectangles[i]) = Vec3b(90,145,201); //Light-brown color code
                }

                else{
                    canvas(rectangles[i]) = Vec3b(33,67,101); //Dark-brown color code

                    if(lineNum < 3){
                        bCheckers.push_back(Circle(x, y, 50, 50));
                        circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                    }

                    else if(lineNum > 4){
                        rCheckers.push_back(Circle(x, y, 50, 50));
                        circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                    }
                }
            }
            else{
                if(lineNum%2){
                    canvas(rectangles[i]) = Vec3b(33,67,101);

                    if(lineNum < 3){
                        bCheckers.push_back(Circle(x, y, 50, 50));
                        circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                    }

                    else if(lineNum > 4){
                        rCheckers.push_back(Circle(x, y, 50, 50));
                        circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                    }
                }
                else{
                    canvas(rectangles[i]) = Vec3b(90,145,201);
                }
            }

            (i%8 == 7) ? lineNum++ : lineNum;
        }
        startUpMain = false;
    }
    //Runs if not first time running the code - Replaces old board image with new game state.
    else if(!startUpMain){
        for(int i = 0; i < 64; i++){

            if(i%2){
                if(lineNum%2){
                    canvas(rectangles[i]) = Vec3b(90,145,201);
                }

                else{
                    canvas(rectangles[i]) = Vec3b(33,67,101);
                }
            }
            else{
                if(lineNum%2){
                    canvas(rectangles[i]) = Vec3b(33,67,101);
                }
                else{
                    canvas(rectangles[i]) = Vec3b(90,145,201);
                }
            }

            (i%8 == 7) ? lineNum++ : lineNum;
        }
    }
    //Draws checkers on new positions.
    for(int j = 0; j < 12; j++){
        for(int i = 0; i < 64; i++){
            if(rCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                break;
            }
        }
    }
    for(int j = 0; j < 12; j++){
        for(int i = 0; i < 64; i++){
            if(bCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                break;
            }
        }
    }
    for(int j = 0; j < 12; j++){
        if(rCheckers[j].contains(Point(graveyardRect.x, graveyardRect.y))){
                circle(canvas, {graveyardRect.x + 25, graveyardRect.y + 25}, 20, Vec3b(14,17,175), -1);
                break;
        }
        if(bCheckers[j].contains(Point(graveyardRect.x, graveyardRect.y))){
                circle(canvas, {graveyardRect.x + 25, graveyardRect.y + 25}, 20, Vec3b(0,0,0), -1);
                break;
            }
    }
}

//Checks if a requested move is legal.
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

//Updates the game state.
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

//Checks if a "Rect" contains elements of given vector.
bool doesRectContainChecker(int x, int y, vector<Circle> enemyCheckerVec){
            for(int i = 0; i < 12; i++){
                if(enemyCheckerVec[i].contains(Point(x, y))){
                    return true;
                }
            }

    return 0;
}

bool doesPosContainRect(int x, int y){
    for(int i = 0; i < 64; i++){
        if(rectangles[i].contains(Point(x, y))){
            cout << "Rect: " << i << " , indeholder punktet: " << x << "," << y << endl;
            return true;
        }
    }

    return false;
}

//Checks if a jump is possible for an element of given vector at a given position.
bool isJumpPossible(int x, int y, vector<Circle> enemyCheckerVec){

    if(enemyCheckerVec == bCheckers){
        if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec))){
            cout << "Jump is possible, checking for checker." << endl;
            if(doesPosContainRect(x + 100, y - 100)){
                cout << "Jump is possible, x+100, y-100" << endl;
                return true;
            }
        }
        else if((doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec))){
            cout << "Jump is possible, checking for checker." << endl;
            if(doesPosContainRect(x - 100, y - 100)){
                cout << "Jump is possible, x-100, y-100" << endl;
                return true;
            }
        }
    }
    else{
        if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec))){
            cout << "Jump is possible, checking for checker." << endl;
            if(doesPosContainRect(x + 100, y + 100)){
                cout << "Jump is possible, x+100, y+100" << endl;
                return true;
            }
        }
        else if((doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec))){
            cout << "Jump is possible, checking for checker." << endl;
            if(doesPosContainRect(x - 100, y + 100)){
                cout << "Jump is possible, x-100, y+100" << endl;
                return true;
            }
        }
    }

    return false;
}

bool isGameWon(vector<Circle> enemyCheckerVec, int playerTurn){
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 12; j++){
            if(rectangles[i].contains(Point(enemyCheckerVec[j].x, enemyCheckerVec[j].y)) && movePossible(((turnVal%2 == 0) ? 2 : 1), boards, jumpPossible(((turnVal%2 == 0) ? 2 : 1), boards), false, {}).size() > 0){
                return false;
            }
        }
        if(i == 64){
            return true;
        }
    }

    return 0;
}

void setJumpPerformed(bool& jumpPerformed, bool TrueFalse){
    jumpPerformed = TrueFalse;
    cout << "JumpPerformed was updated: " << jumpPerformed << endl;
}

//callBack function, that runs every time you click.
void callBackFunc(int event, int userX, int userY, int flags, void* userdata){
    if(selected.size() != 0 && event == EVENT_LBUTTONDOWN){ //Runs this code left mouse button clicked and "Rect" is already selected.

        for(int i = 0; i < 64; i++){
            if(rectangles[i].contains(Point(userX,userY))){ //Checks if the click is inside of the game board.
                
                //If click is at the same location as previously selected, then deselect.
                if(rectangles[selected[2]].x == rectangles[i].x && rectangles[selected[2]].y == rectangles[i].y){
                    Draw(startUpMain); //Draws new game state.    
                    clearVecInt(selected); //Clears vector selected.
                    clearVecString(stringPos); 
                    /*stringPos.clear(); //Clears stringPos.
                    selected.clear();*/
                    cout << "Selected ved deselect: "<< selected[3] << endl;
                }
                else if(selected[0] == 1){ //If it is player 1's turn, run this code.

                    if(selected[3] == 1){ //If there is a single jump possible run this code.
                        cout << "Hopper i selecetd == 1" << endl;
                        posToStringConvert(rectangles[selected[4]].x, rectangles[selected[4]].y, stringPos);
                    }
                    else if(selected[3] == 2){ //If there is multiple jumps possible, run this code.
                        cout << "Hopper i selecetd == 2" << endl;
                        if(rectangles[i].x > rectangles[selected[2]].x){ //If "Rect" that was clicked is to the right of the earlier selected "Rect".
                            posToStringConvert(rectangles[selected[4]].x, rectangles[selected[4]].y, stringPos); //Gets string position for possible jump to the right.
                        }
                        else{
                            posToStringConvert(rectangles[selected[5]].x, rectangles[selected[5]].y, stringPos); //Gets string position for possible jump to the left.
                        }
                    }
                    else{ //If no jumps possible.
                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                        cout << "stringPos blev opdateret med andet klik" << stringPos[1] << endl;
                    }

                    cout << "stringPos[0]" << stringPos[0] << endl;
                    cout << "stringPos[1]" << stringPos[1] << endl;
                    cout << stringPos.size() << endl;
                    //Checks if move is legal.
                    if(playerMover(stringPos[0], stringPos[1], ((turnVal%2 == 0) ? 2 : 1), boards)){
                        
                        //Changes the position of selected checker.
                        rCheckers[selected[1]].x = rectangles[i].x;
                        rCheckers[selected[1]].y = rectangles[i].y;
                        
                        //Changes gamestate in board.
                        boardChange(((turnVal%2 == 0) ? 2 : 1), boards, stringPos[0], stringPos[1], redCheckers, blackCheckers);
                        //Prints new gamestate to console.
                        checkerBoard(boards);

                        //If a jump has been performed, find and remove the "killed" checker.
                        if(selected[3] == 1 || selected[3] == 2){
                            for(int j = 0; j < 12; j++){
                                if(bCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                    bCheckers[j].x = graveyardRect.x;
                                    bCheckers[j].y = graveyardRect.y;
                                    break;
                                }
                            }
                            setJumpPerformed(jumpPerformed, true);
                            cout << "was set True, JumpPerformed: " << jumpPerformed << endl;
                        }

                        //isGameWon(bCheckers, ((turnArr[1]%2 == 0) ? 2 : 1));

                        cout << "JumpPerformed: " << jumpPerformed << endl;

                        cout << "Is game won: " << isGameWon(bCheckers, ((turnVal%2 == 0) ? 2 : 1)) << endl;

                        if(isJumpPossible(rectangles[i].x, rectangles[i].y, bCheckers) && jumpPerformed){
                            cout << "It is possible for red to jump multiple times" << endl;

                            Draw(startUpMain);

                            currentChecker = selected[1];

                            clearVecInt(selected); //Clears vector selected.
                            clearVecString(stringPos);

                            /*selected.clear();
                            stringPos.clear();*/

                            selected.insert(selected.end(), {1, currentChecker, i});
                            posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                            canvas(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                            circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);

                            if(isJumpPossible(rectangles[i].x, rectangles[i].y, bCheckers)){ //Checks if there is a jump possible for a checker at the given position, where the enemy is given also.
                                cout << "Jump is possible." << endl;
                                //Checks if there is a checker across from the selected checker - Both right and left.
                                if((doesRectContainChecker(rectangles[i].x + 50, rectangles[i].y - 50, bCheckers) && !doesRectContainChecker(rectangles[i].x + 100, rectangles[i].y - 100, bCheckers)) && (doesRectContainChecker(rectangles[i].x - 50, rectangles[i].y - 50, bCheckers) && !doesRectContainChecker(rectangles[i].x - 100, rectangles[i].x - 100, bCheckers))){
                                    
                                    if(rectangles[i-14].contains(Point(rectangles[i].x + 100,rectangles[i].y - 100))){
                                        canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                                    }
                                    if(rectangles[i-18].contains(Point(rectangles[i].x - 100,rectangles[i].y - 100))){
                                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                                    }
                                    
                                    selected.push_back(2); //Represents multiple jumps possible.
                                    selected.push_back(i-14); //Right rectangle ID.
                                    selected.push_back(i-18); //Left rectangle ID.
                                }
                                //Checks if there is a checker across from the selected checker - Right.
                                else if(doesRectContainChecker(rectangles[i].x + 50, rectangles[i].y - 50, bCheckers) && !doesRectContainChecker(rectangles[i].x + 100, rectangles[i].y - 100, bCheckers)){
                                    if(rectangles[i-14].contains(Point(rectangles[i].x + 100,rectangles[i].y - 100))){
                                        canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights.
                                    }
                                    
                                    selected.push_back(1); //Represents one jump possible.
                                    selected.push_back(i-14); //Pushes ID for right rectangle.
                                }
                                //Checks if there is a checker across from the selected checker - Left.
                                else{
                                    if(rectangles[i-18].contains(Point(rectangles[i].x - 100,rectangles[i].y - 100))){
                                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                                    }
                                    selected.push_back(1);
                                    selected.push_back(i-18);
                                }
                            }
                            else{
                                cout << "jump not possible" << endl;
                            }
                        }
                        else{
                            cout << "JumpPerformed, after red move: " << jumpPerformed << endl;
                            Draw(startUpMain); //Draws new gamestate.
                            turnVal++;
                            setJumpPerformed(jumpPerformed, false);
                            updateText(); //Updates text.
                            clearVecInt(selected); //Clears vector selected.
                            clearVecString(stringPos);
                            /*selected.clear(); //Clears "selected" vector.    
                            stringPos.clear(); //Clears "stringPos" vector.*/
                            cout << "Selected[3] værdi efter clear" << selected[3] << endl;
                            cout << "------ RED" << endl;
                        }
                    }
                    else{
                        stringPos.pop_back(); //If the move is invalid, remove invalid position.
                    }
                }
                else if(selected[0] == 0){ //If it is player 2's turn, run this code - To see code explaination see previous section, as they are basically identical.
                    
                    cout << "JumpPerformed, black selected: " << jumpPerformed << endl;

                    if(selected[3] == 1){
                        posToStringConvert(rectangles[selected[4]].x, rectangles[selected[4]].y, stringPos);
                        cout << "Hopper i selecetd == 1, sort" << endl;
                    }
                    else if(selected[3] == 2){
                        cout << "Hopper i selecetd == 2, sort" << endl;
                        if(rectangles[i].x > rectangles[selected[2]].x){
                            posToStringConvert(rectangles[selected[4]].x, rectangles[selected[4]].y, stringPos);
                        }
                        else{
                            posToStringConvert(rectangles[selected[5]].x, rectangles[selected[5]].y, stringPos);
                        }
                    }
                    else{
                        cout << "hopper i ingen hop muligt" << endl;
                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                    }
                    
                    cout << "JumpPerformed, before move approval: " << jumpPerformed << endl;
                    cout << stringPos[0] << endl;
                    cout << stringPos[1] << endl;
                    cout << stringPos.size() << endl;
                    if(playerMover(stringPos[0], stringPos[1], ((turnVal%2 == 0) ? 2 : 1), boards)){

                        cout << "JumpPerformed, after move approval: " << jumpPerformed << endl;

                        bCheckers[selected[1]].x = rectangles[i].x;
                        bCheckers[selected[1]].y = rectangles[i].y;

                        boardChange(((turnVal%2 == 0) ? 2 : 1), boards, stringPos[0], stringPos[1], redCheckers, blackCheckers);
                        checkerBoard(boards);

                        if(selected[3] == 1 || selected[3] == 2){
                            for(int j = 0; j < 12; j++){
                                if(rCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                    rCheckers[j].x = graveyardRect.x;
                                    rCheckers[j].y = graveyardRect.y;
                                    break;
                                }
                            }
                            setJumpPerformed(jumpPerformed, true);
                            cout << "was set True, JumpPerformed: " << jumpPerformed << endl;
                        }

                        //isGameWon(rCheckers, ((turnArr[1]%2 == 0) ? 2 : 1));
                        cout << "JumpPerformed: " << jumpPerformed << endl;
                        
                        //isJumpPossible skal tjækkes som turen starter.
                        if(isJumpPossible(rectangles[i].x, rectangles[i].y, rCheckers) && jumpPerformed){
                            Draw(startUpMain);
                            cout << "It is possible for black to jump twice" << endl;

                            currentChecker = selected[1];

                            clearVecInt(selected); //Clears vector selected.
                            clearVecString(stringPos); 

                            selected.insert(selected.end(), {0, currentChecker, i});
                            posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos); //Problem her

                            canvas(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                            circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1); //Redraws the checker, as the highlighting (previous line of code) draws over it.

                            if((doesRectContainChecker(rectangles[i].x + 50, rectangles[i].y + 50, rCheckers) && !doesRectContainChecker(rectangles[i].x + 100, rectangles[i].y + 100, rCheckers)) && (doesRectContainChecker(rectangles[i].x - 50, rectangles[i].x + 50, rCheckers) && !doesRectContainChecker(rectangles[i].x - 100, rectangles[i].y + 100, rCheckers))){
                                if(rectangles[i+14].contains(Point(rectangles[i].x - 100,rectangles[i].y + 100))){
                                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                                }
                                if(rectangles[i+18].contains(Point(rectangles[i].x + 100,rectangles[i].y + 100))){
                                canvas(rectangles[i+18]) = Vec3b(14,17,175);
                                }
                                selected.push_back(2);
                                selected.push_back(i+18); //Right
                                selected.push_back(i+14); //Left
                            }
                            else if(doesRectContainChecker(rectangles[i].x + 50, rectangles[i].y + 50, rCheckers) && !doesRectContainChecker(rectangles[i].x + 100, rectangles[i].y + 100, rCheckers)){
                                if(rectangles[i+18].contains(Point(rectangles[i].x + 100,rectangles[i].y + 100))){
                                canvas(rectangles[i+18]) = Vec3b(14,17,175);
                                }
                                selected.push_back(1);
                                selected.push_back(i+18);
                            }
                            else{
                                if(rectangles[i+14].contains(Point(rectangles[i].x - 100,rectangles[i].y + 100))){
                                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                                }
                                selected.push_back(1);
                                selected.push_back(i+14);
                            }
                        }
                        else{
                            Draw(startUpMain); //Draws new gamestate.
                            turnVal++;
                            updateText(); //Updates text. 
                            /*selected.clear(); //Clears "selected" vector.
                            stringPos.clear(); //Clears "stringPos" vector.*/
                            clearVecInt(selected); //Clears vector selected.
                            clearVecString(stringPos);
                            cout << "Selected[3] værdi efter clear" << selected[3] << endl;  
                            setJumpPerformed(jumpPerformed, false);
                            cout << stringPos[0] << stringPos[1] << endl;
                            cout << "StringPos er cleared" << endl;
                            cout << "------ BLACK" << endl;
                        }
                    }
                    else{
                        stringPos.pop_back();
                    }
                }
            }
        }
    }
    else if(event == EVENT_LBUTTONDOWN){ //If left mouse button is clicked and no checker was previously selected, run this code.
        for(int i = 0; i < 64; i++){
            if(rectangles[i].contains(Point(userX,userY))){ //Checks if click is inside game board.
                cout << "Rect: " << rectangles[i] << endl;
                    for(int j = 0; j < 12; j++){
                        if(rCheckers[j].contains(Point(userX, userY)) && turnVal%2 == 0){ //Checks if there is a checker on the Rect, corresponding to the which players turn it is.
                            canvas(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                            circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1); //Redraws the checker, as the highlighting (previous line of code) draws over it.

                            posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos); //Converts position of selected checker to string notation and saves the value in "stringPos".

                            selected.push_back(1); //Represents color of checker.
                            selected.push_back(j); //Vector ID of checker in rCheckers[].
                            selected.push_back(i); //Vector ID of rect in rectangles[].
                            
                                if(isJumpPossible(rCheckers[j].x, rCheckers[j].y, bCheckers)){ //Checks if there is a jump possible for a checker at the given position, where the enemy is given also.
                                    cout << "Jump is possible." << endl;
                                    //Checks if there is a checker across from the selected checker - Both right and left.
                                    if((doesRectContainChecker(rCheckers[j].x + 50, rCheckers[j].y - 50, bCheckers) && !doesRectContainChecker(rCheckers[j].x + 100, rCheckers[j].y - 100, bCheckers)) && (doesRectContainChecker(rCheckers[j].x - 50, rCheckers[j].y - 50, bCheckers) && !doesRectContainChecker(rCheckers[j].x - 100, rCheckers[j].y - 100, bCheckers))){
                                        
                                        if(rectangles[i-14].contains(Point(rectangles[i].x + 100,rectangles[i].y - 100))){
                                            canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                                        }
                                        if(rectangles[i-18].contains(Point(rectangles[i].x - 100,rectangles[i].y - 100))){
                                        canvas(rectangles[i-18]) = Vec3b(14,17,175);
                                        }
                                        
                                        selected.push_back(2); //Represents multiple jumps possible.
                                        selected.push_back(i-14); //Right rectangle ID.
                                        selected.push_back(i-18); //Left rectangle ID.
                                    }
                                    //Checks if there is a checker across from the selected checker - Right.
                                    else if(doesRectContainChecker(rCheckers[j].x + 50, rCheckers[j].y - 50, bCheckers) && !doesRectContainChecker(rCheckers[j].x + 100, rCheckers[j].y - 100, bCheckers)){
                                        if(rectangles[i-14].contains(Point(rectangles[i].x + 100,rectangles[i].y - 100))){
                                            canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights.
                                        }
                                        
                                        selected.push_back(1); //Represents one jump possible.
                                        selected.push_back(i-14); //Pushes ID for right rectangle.
                                    }
                                    //Checks if there is a checker across from the selected checker - Left.
                                    else{
                                        if(rectangles[i-18].contains(Point(rectangles[i].x - 100,rectangles[i].y - 100))){
                                        canvas(rectangles[i-18]) = Vec3b(14,17,175);
                                        }
                                        selected.push_back(1);
                                        selected.push_back(i-18);
                                    }
                                }
                                else{
                                    cout << "jump not possible" << endl;
                                }
                        }
                        else if(bCheckers[j].contains(Point(userX, userY)) && turnVal%2 == 1){ //Same as for the previous section.
                            canvas(rectangles[i]) = Vec3b(0,0,255);
                            circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);

                            posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                            selected.push_back(0);
                            selected.push_back(j);
                            selected.push_back(i);
                            
                            if(isJumpPossible(bCheckers[j].x, bCheckers[j].y, rCheckers)){
                                cout << "Jump is possible" << endl;
                                if((doesRectContainChecker(bCheckers[j].x + 50, bCheckers[j].y + 50, rCheckers) && !doesRectContainChecker(bCheckers[j].x + 100, bCheckers[j].y + 100, rCheckers)) && (doesRectContainChecker(bCheckers[j].x - 50, bCheckers[j].y + 50, rCheckers) && !doesRectContainChecker(bCheckers[j].x - 100, bCheckers[j].y + 100, rCheckers))){
                                    if(rectangles[i+14].contains(Point(rectangles[i].x - 100,rectangles[i].y + 100))){
                                        canvas(rectangles[i+14]) = Vec3b(14,17,175);
                                    }
                                    if(rectangles[i+18].contains(Point(rectangles[i].x + 100,rectangles[i].y + 100))){
                                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                                    }
                                    selected.push_back(2);
                                    selected.push_back(i+18); //Right
                                    selected.push_back(i+14); //Left
                                }
                                else if(doesRectContainChecker(bCheckers[j].x + 50, bCheckers[j].y + 50, rCheckers) && !doesRectContainChecker(bCheckers[j].x + 100, bCheckers[j].y + 100, rCheckers)){
                                    if(rectangles[i+18].contains(Point(rectangles[i].x + 100,rectangles[i].y + 100))){
                                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                                    }
                                    selected.push_back(1);
                                    selected.push_back(i+18);
                                }
                                else{
                                    if(rectangles[i+14].contains(Point(rectangles[i].x - 100,rectangles[i].y + 100))){
                                        canvas(rectangles[i+14]) = Vec3b(14,17,175);
                                    }
                                    selected.push_back(1);
                                    selected.push_back(i+14);
                                }
                            }
                            else{
                                cout << "jump not possible" << endl;
                            }
                        }
                    }

                break;
            }
        }
    }

    imshow(winName, canvas);
    waitKey();
}

int main(int argc, char** argv){
    Draw(startUpMain);
    updateText();

    //Creates window, and shows image on it.
    namedWindow(winName, WINDOW_AUTOSIZE);
    setMouseCallback(winName, callBackFunc);
    imshow(winName, canvas);
    waitKey();

    return 0;
}
