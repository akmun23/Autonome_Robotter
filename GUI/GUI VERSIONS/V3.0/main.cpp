#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
//#include <opencv2/highgui.hpp>
#include "validMoves.h"
#include "boardUpdate.h"
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

Mat3b canvas(500, 1000, Vec3b(255, 255, 255)); //Creates drawing surface, canvas.
string winName = "Project GUI"; //Sets name of window being used.
vector<Circle> bCheckers; //Vec consisting of instances of "Circle" for black checkers.
vector<Circle> rCheckers; //Vec consisting of instances of "Circle" for red checkers.
vector<Rect> rectangles; //Vec consisting of instances of "Rect", as segments of board.
vector<int> selected; //Vec consisting of INT, that refer to information of selected Rect.
vector<string> stringPos; //Vec consisting of selected positions.
vector<Circle> redKing;
vector<Circle> blackKing;
Mat graveyardDownSized;
Rect blackGraveyardRect(600, 75, 50, 50); //Instance of Rect, used as a graveyard Rect.
Rect redGraveyardRect(600, 175, 50, 50);
Rect promotionRect(600, 225, 50, 50);
Rect gameModeRectPVP((canvas.cols/2) - 200, (canvas.rows/2) - 40, 100, 50);
Rect gameModeRectAI((canvas.cols/2) - 50, (canvas.rows/2) - 40, 100, 50);
Rect gameModeRectDB((canvas.cols/2) + 100, (canvas.rows/2) - 40, 100, 50);
//std::vector<std::vector<std::string>> boards;
int turnVal = 0; //Array containing INT representing how many turns have been taken.
bool startUpMain = true; //Bool, true if code is being run for the first time.
//int playerTurn = 1; //Which player's turn it is
int blackPieces = 12; //Initial number of black pieces
int redPieces = 12; //Initial number of red pieces
bool jumpPerformed;
bool startJump;
bool gameEnd = false;
bool redWon = false;
int thisTurn; //Which player's turn it is
int DrawChecker = 1; //When this equal 200 the game is called draw
std::vector<std::vector<std::string>> thisBoard = {};
std::vector<std::string> moveSet = {}; //The moves that have been made during the turn
vector<int> intPos;
std::vector<std::vector<double>> startUpRobot;
int currentChecker;
string pos;
string gameMode;

void setGameMode(string selectedGameMode){
    gameMode = selectedGameMode;
    cout << "Game mode was set to: " << gameMode << endl;
}

void setGameEnd(bool TF){
    gameEnd = TF;
}

void setRedWon(bool TF){
    redWon = TF;
}

void setJumpPerformed(bool& jumpPerformed, bool TF){
    jumpPerformed = TF;
    cout << "JumpPerformed was updated: " << jumpPerformed << endl;
}

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
    string spiller1 = "Det er spiller 1's tur.";
    string spiller2 = "Det er spiller 2's tur.";
    string playerTurnString;

    ((turnVal%2 == 0) ? playerTurnString = spiller1 : playerTurnString = spiller2);

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
    string col, row;

    col = numArr[findInVector(numArr,to_string((x-boardOffSetX/2)/50))];
    row = alphabetArr[findInVector(alphabetArr,alphabetArr[(y-boardOffSetY)/50])];

    stringPos.push_back(row + col);
}

void stringToPosConvert(string stringPosValue, vector<int>& intPos){

    int x, y;
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    //string alphabetString = string str(stringPosValue[0]);
    string alphabetString(1, stringPosValue[0]);
    string intString = to_string((int(stringPosValue[1])-48));

    x = findInVector(numArr, intString)*50 + boardOffSetX;
    y = findInVector(alphabetArr, alphabetString)*50 + boardOffSetY;

    cout << "Input: " << alphabetString << intString << ", er blevet converteret til: " << x << "," << y << endl;

    intPos.push_back(x);
    intPos.push_back(y);

    cout << "Checking information in intPos: " << intPos[intPos.size()-2] << "," << intPos[intPos.size()-1] << endl;

}

//Checks if a "Rect" contains elements of given vector.
bool doesRectContainChecker(int x, int y, vector<Circle> checkerVec){
            for(int i = 0; i < checkerVec.size(); i++){
                if(checkerVec[i].contains(Point(x, y))){
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
        
        rectangle(canvas, Point(0,0), Point(canvas.cols, canvas.rows), Scalar(255,255,255), -1);

        //Generates row and col names along board edge.
        for(int i = 0; i < 8; i++){
            putText(canvas, numArr[i], Point({(i * 50) + boardOffSetX + 12}, {boardOffSetY - 5}), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
            putText(canvas, alphabetArr[i], Point({boardOffSetX - 30}, {(i * 50) + boardOffSetY + 35}), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
        }

        //Loads graveyard segment image, and resizes it to fit inside rect.
        resize(imread("/home/mads-hyrup/Uni/2.-Semester/SemesterProjekt/Projekt/graveyard.jpg"), graveyardDownSized, Size(50, 50), INTER_LINEAR);
        graveyardDownSized.copyTo(canvas(blackGraveyardRect)); //Draws graveyard onto canvas.
        graveyardDownSized.copyTo(canvas(redGraveyardRect));

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

    int redGrave = count_if(rCheckers.begin(), rCheckers.end(), [](Circle obj){
        return(obj.x == redGraveyardRect.x && obj.y == redGraveyardRect.y);
    });

    int blackGrave = count_if(bCheckers.begin(), bCheckers.end(), [](Circle obj){
        return(obj.x == blackGraveyardRect.x && obj.y == blackGraveyardRect.y);
    });

    for(int j = 0; j < (rCheckers.size() > bCheckers.size() ? rCheckers.size() : bCheckers.size()); j++){
        if(rCheckers[j].contains(Point(redGraveyardRect.x, redGraveyardRect.y))){
            circle(canvas, {redGraveyardRect.x + 25, redGraveyardRect.y + 25}, 20, Vec3b(14,17,175), -1);
            if(redGrave){
                putText(canvas, to_string(redGrave), (redGrave < 10 ? Point(redGraveyardRect.x + 15, redGraveyardRect.y + 35) : Point(redGraveyardRect.x + 4, redGraveyardRect.y + 35)), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
            }
        }
        if(bCheckers[j].contains(Point(blackGraveyardRect.x, blackGraveyardRect.y))){
            circle(canvas, {blackGraveyardRect.x + 25, blackGraveyardRect.y + 25}, 20, Vec3b(0,0,0), -1);
            if(blackGrave){
                putText(canvas, to_string(blackGrave), (blackGrave < 10 ? Point(blackGraveyardRect.x + 15, blackGraveyardRect.y + 35) : Point(blackGraveyardRect.x + 4, blackGraveyardRect.y + 35)), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
            }
        }
    }

    if(rCheckers.size() > 12){
        for(int i = 0; i < 64; i++){
            for(int j = 12; j < rCheckers.size(); j++){
                if(rCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                    circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                    break;
                }
            }
        }
    }

    if(bCheckers.size() > 12){
        for(int i = 0; i < 64; i++){
            //cout << "bcheckers størrelse: " << bCheckers.size() << endl;
            for(int j = 12; j < bCheckers.size(); j++){
                //cout << j << endl;
                if(bCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                    cout << "Found checker at: " << rectangles[i].x << "," << rectangles[i].y << endl;
                    circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                    break;
                }
            }
        }
    }
}

void drawGameMode(){
    rectangle(canvas, Point(0,0), Point(canvas.cols, canvas.rows), Scalar(255,255,255), -1);
    rectangle(canvas, gameModeRectPVP, Scalar(0,0,0), 2);
    putText(canvas, "PvP", Point(gameModeRectPVP.x + 20, gameModeRectPVP.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
    rectangle(canvas, gameModeRectAI, Scalar(0,0,0), 2);
    putText(canvas, "AI", Point(gameModeRectAI.x + 35, gameModeRectAI.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
    rectangle(canvas, gameModeRectDB, Scalar(0,0,0), 2);
    putText(canvas, "DB", Point(gameModeRectDB.x + 30, gameModeRectDB.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
    putText(canvas, "Press any button after selecting gamemode, to start the game.", Point(gameModeRectPVP.x - 200, 2*canvas.rows/3), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0), 1);
}

void gameModeCallBack(int event, int userX, int userY, int flags, void* userdata){

    if(event == EVENT_LBUTTONDOWN){
        if(gameModeRectPVP.contains(Point(userX, userY))){
            setGameMode("PVP");
            drawGameMode();
            rectangle(canvas, gameModeRectPVP, Scalar(0,0,255), 2);
            putText(canvas, "PvP", Point(gameModeRectPVP.x + 20, gameModeRectPVP.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }
        else if(gameModeRectAI.contains(Point(userX, userY))){
            setGameMode("AI");
            drawGameMode();
            rectangle(canvas, gameModeRectAI, Scalar(0,0,255), 2);
            putText(canvas, "AI", Point(gameModeRectAI.x + 35, gameModeRectAI.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }
        else if(gameModeRectDB.contains(Point(userX, userY))){
            setGameMode("DB");
            drawGameMode();
            rectangle(canvas, gameModeRectDB, Scalar(0,0,255), 2);
            putText(canvas, "DB", Point(gameModeRectDB.x + 30, gameModeRectDB.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }
    }
    
    imshow(winName, canvas);
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
     if(pieceJump(playerStart, playerMove, thisTurn, boards)){
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
     if(promotion(boards, thisTurn)){
         if((turnVal%2 == 0 ? 1 : 2) == 1){
             boards[column2][row2] = "BK";
         } else {
             boards[column2][row2] = "RK";
         }
         return true;
     }

     //If no promotion has been made, it returns false
     return false;
}

//Checks if a jump is possible for an element of given vector at a given position.
bool isJumpPossible(int x, int y, int checkerID, vector<Circle> checkerVec, vector<Circle> enemyCheckerVec){

    if(enemyCheckerVec == bCheckers){
        if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)){
            cout << "Jump is possible, checking for checker. b1" << endl;
            if(doesPosContainRect(x + 100, y - 100)){
                cout << "Jump is possible, x+100, y-100" << endl;
                return true;
            }
        }
        else if(doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)){
            cout << "Jump is possible, checking for checker. b2" << endl;
            if(doesPosContainRect(x - 100, y - 100)){
                cout << "Jump is possible, x-100, y-100" << endl;
                return true;
            }
        }

        if(checkerID >= 12){

            if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)){
                cout << "Jump is possible, checking for checker. b3" << endl;
                if(doesPosContainRect(x + 100, y + 100)){
                    cout << "Jump is possible, x+100, y+100" << endl;
                    return true;
                }
            }
            else if(doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100)){
                cout << "Jump is possible, checking for checker. b4" << endl;
                if(doesPosContainRect(x - 100, y + 100)){
                    cout << "Jump is possible, x-100, y+100" << endl;
                    return true;
                }
            }
        }
    }
    else{
        if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)){
            cout << "Jump is possible, checking for checker. r1" << endl;
            if(doesPosContainRect(x + 100, y + 100)){
                cout << "Jump is possible, x+100, y+100" << endl;
                return true;
            }
        }
        else if(doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100)){
            cout << "Jump is possible, checking for checker. r2" << endl;
            if(doesPosContainRect(x - 100, y + 100)){
                cout << "Jump is possible, x-100, y+100" << endl;
                return true;
            }
        }

        if(checkerID >= 12){
            cout << "CheckerID >= 12" << endl;
            if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)){
                cout << "Jump is possible, checking for checker. r3" << endl;
                if(doesPosContainRect(x + 100, y - 100)){
                    cout << "Jump is possible, x+100, y-100" << endl;
                    return true;
                }
            }
            else if(doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)){
                cout << "Jump is possible, checking for checker. r4" << endl;
                if(doesPosContainRect(x - 100, y - 100)){
                    cout << "Jump is possible, x-100, y-100" << endl;
                    return true;
                }
            }
        }
    }

    return false;
}

int piecesLeft(vector<Circle> checkerVec){
    int count = 0;

    for(int i = 0; i < 64; i++){
        for(int j = 0; j < checkerVec.size(); j++){
            if(rectangles[i].contains(Point(checkerVec[j].x, checkerVec[j].y))){
                count++;
            }
        }
    }

    return count;
}

void promotionGUI(vector<Circle> checkerVector){
    if(checkerVector == rCheckers){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 12; j++){
                if(rectangles[i].contains(Point(rCheckers[j].x,rCheckers[j].y))){
                    cout << "Red promoted" << endl;
                    rCheckers[j].x = promotionRect.x;
                    rCheckers[j].y = promotionRect.y;
                    rCheckers.push_back(Circle(rectangles[i].x, rectangles[i].y, 50, 50));
                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                }
            }
        }
    }
    else{
        for(int i = 56; i < 64; i++){
            //cout << i << endl;
            for(int j = 0; j < 12; j++){
                if(rectangles[i].contains(Point(bCheckers[j].x,bCheckers[j].y))){
                    cout << "Black promoted" << endl;
                    bCheckers[j].x = promotionRect.x;
                    bCheckers[j].y = promotionRect.y;
                    bCheckers.push_back(Circle(rectangles[i].x, rectangles[i].y, 50, 50));
                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                }
            }
        }
    }
}

bool isGameWon(vector<Circle> checkerVec, int turn){

    if(checkerVec == rCheckers){
        if(piecesLeft(bCheckers) < 1){
            cout << "Rød vandt ved ikke flere sorte tilstede" << endl;
            return true;
        }
        else if(movePossible(turn, boards, jumpPossible(turn, boards), false, "").size() < 1){
            cout << "Rød har vundet ved ingen træk mulig for sort" << endl;
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(piecesLeft(rCheckers) < 1){
            cout << "Sort vandt ved ikke flere røde tilstede" << endl;
            return true;
        }
        else if(movePossible(turn, boards, jumpPossible(turn, boards), false, "").size() < 1){
            cout << "Sort har vundet ved ingen træk mulig for rød" << endl;
            return true;
        }
        else{
            return false;
        }
    }
}

void winAnimation(){
    for(int i = 0; i < (canvas.rows/50)/2; i++){
        for(int j = 0; j < ((canvas.cols - 100 * i)/50); j++){
            rectangle(canvas, Point(j*50 + i*50, i*50), Point((j*50 + i*50) + 50, (i*50) + 50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, canvas);
        }
        for(int j = 0; j < ((canvas.rows - 100 * i)/50); j++){
            rectangle(canvas, Point((canvas.cols - i*50 - 50), (j*50 + i*50)), Point(canvas.cols - i*50, (j*50 + i*50) + 50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, canvas);
        }
        for(int j = 0; j < ((canvas.cols - 100 * i)/50); j++){
            rectangle(canvas, Point(canvas.cols - (j*50 + i*50), canvas.rows - i*50 - 50), Point((canvas.cols - (j*50 + i*50)) + 50, canvas.rows - i*50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, canvas);
        }
        for(int j = 0; j < ((canvas.rows - 100 * i)/50); j++){
            rectangle(canvas, Point((i*50), (canvas.rows - (j*50 + i*50))), Point((i*50) + 50, (canvas.rows - (j*50 + i*50)) + 50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, canvas);
        }
    }

    putText(canvas, (redWon ? "RED HAS WON" : "BLACK HAS WON"), (redWon ? Point(((rectangles[0].x + rectangles[63].x)/2), (rectangles[0].y + rectangles[63].y)/2) : Point((((rectangles[0].x + rectangles[63].x)/2) - 40), (rectangles[0].y + rectangles[63].y)/2)), FONT_HERSHEY_COMPLEX, 2, (redWon ? Scalar(0,0,0) : Scalar(255,255,255)), 1);
    imshow(winName, canvas);
}

void jumps(int x, int y, int i, int checkerID, vector<Circle> checkerVec, vector<Circle> enemyCheckerVec){

    if(isJumpPossible(x, y, checkerID, checkerVec, enemyCheckerVec)){ //Checks if there is a jump possible for a checker at the given position, where the enemy is given also.
        cout << "Jump is possible." << endl;
        //Checks if there is a checker across from the selected checker - Both right and left.
        if(checkerVec == rCheckers && checkerID < 12){ 
            if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec))){
                cout << "Two jumps possible" << endl;
                if(rectangles[i-14].contains(Point(x + 100, y - 100))){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                }
                if(rectangles[i-18].contains(Point(x - 100, y - 100))){
                canvas(rectangles[i-18]) = Vec3b(14,17,175);
                }
                
                selected.push_back(2); //Represents multiple jumps possible.
            }
            //Checks if there is a checker across from the selected checker - Right.
            else if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec)){
                cout << "One jump possible" << endl;
                if(rectangles[i-14].contains(Point(x + 100, y - 100))){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights.
                }
                selected.push_back(1); //Represents one jump possible.
            }
            else{
                cout << "one jump possible" << endl;
                if(rectangles[i-18].contains(Point(x - 100, y - 100))){
                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                }
                selected.push_back(1);
            }
        }
        else if(checkerVec == bCheckers && checkerID < 12){
            if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec))){
                if(rectangles[i+14].contains(Point(x - 100, y + 100))){ //skal tage højde for egne checker også
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                }
                if(rectangles[i+18].contains(Point(x + 100, y + 100))){
                canvas(rectangles[i+18]) = Vec3b(14,17,175);
                }

                selected.push_back(2);
            }
            else if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec)){
                if(rectangles[i+18].contains(Point(x + 100, y + 100))){
                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                    selected.push_back(1);
                }
            }
            else{
                if(rectangles[i+14].contains(Point(x - 100, y + 100))){
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                    selected.push_back(1);
                }
            }
        }

        if((turnVal%2 == 0 ? checkerVec == bCheckers : checkerVec == rCheckers) && (checkerID >= 12)){
            //King jumps - missing red taking into account their own checkers
            cout << "King jump" << endl;

            if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100))){
                cout << "Four jumps possible for king" << endl;
                
                canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                canvas(rectangles[i-18]) = Vec3b(14,17,175);
                canvas(rectangles[i+14]) = Vec3b(14,17,175);
                canvas(rectangles[i+18]) = Vec3b(14,17,175);
                selected.push_back(4); //Represents multiple jumps possible.
                
                cout << "Konge fire træk" << endl;

            }
            else if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100)) && (doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100))){
                
                cout << "Konge tre træk - to nederst" << endl;

                canvas(rectangles[i+14]) = Vec3b(14,17,175);
                canvas(rectangles[i+18]) = Vec3b(14,17,175);
                selected.push_back(3);
                
                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec))){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                }
                else{
                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100)) || (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100) && (doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)))){
                
                cout << "Konge tre træk - to øverst" << endl;

                canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                canvas(rectangles[i-18]) = Vec3b(14,17,175);
                selected.push_back(3);
                
                if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec))){
                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                }
                else{
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) || (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100))){

                cout << "Konge to træk - lige" << endl;

                selected.push_back(2); //3

                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec))){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                }
                else{
                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100))){
                cout << "Konge to træk - lige - til siden" << endl;

                selected.push_back(2); //3

                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100))){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                }
                else{
                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100))){
                cout << "Konge to træk - skråt" << endl;

                selected.push_back(2); //3

                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100))){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                }
                else{
                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)) || (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)) || (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100))){
                selected.push_back(1); //3

                cout << "Konge et træk" << endl;

                if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100)){
                    canvas(rectangles[i-14]) = Vec3b(14,17,175);
                }
                else if(doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100)){
                    canvas(rectangles[i-18]) = Vec3b(14,17,175);
                }
                else if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100)){
                    canvas(rectangles[i+18]) = Vec3b(14,17,175);
                }
                else{
                    canvas(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else{
                cout << "Could not find the possible jump" << endl;
            }
        }
    }
    else{
        cout << "jump not possible" << endl;
    }
}

//callBack function, that runs every time you click.
void callBackFunc(int event, int userX, int userY, int flags, void* userdata){

    if(gameMode == "PVP" || turnVal%2 == 0 && gameMode == "AI" || turnVal%2 == 0 && gameMode == "DB"){
        if(selected.size() != 0 && event == EVENT_LBUTTONDOWN){ //Runs this code left mouse button clicked and "Rect" is already selected.

            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(userX,userY))){ //Checks if the click is inside of the game board.

                    //If click is at the same location as previously selected, then deselect.
                    if(rectangles[selected[2]].x == rectangles[i].x && rectangles[selected[2]].y == rectangles[i].y){
                        Draw(startUpMain); //Draws new game state.    
                        clearVecInt(selected); //Clears vector selected.
                        clearVecString(stringPos);
                        cout << "Selected ved deselect: "<< selected[3] << endl;
                    }
                
                    else if(((turnVal%2 == 0) ? 1 : 2) == 2){ //If it is player 1's turn, run this code.

                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                        cout << "stringPos[0]" << stringPos[0] << endl;
                        cout << "stringPos[1]" << stringPos[1] << endl;
                        cout << stringPos.size() << endl;

                        //Checks if move is legal.
                        if(playerMover(stringPos[0], stringPos[1], ((turnVal%2 == 0) ? 1 : 2), boards)){
                            
                            //Changes the position of selected checker.
                            rCheckers[selected[1]].x = rectangles[i].x;
                            rCheckers[selected[1]].y = rectangles[i].y;
                            cout << "RED Changed location of piece number: " << selected[1] << endl; //WTFFFFFF
                            
                            //Changes gamestate in board.
                            boardChange(((turnVal%2 == 0) ? 1 : 2), boards, stringPos[0], stringPos[1], redPieces, blackPieces);
                            //Prints new gamestate to console.
                            checkerBoard(boards);

                            //If a jump has been performed, find and remove the "killed" checker.
                            if(selected[3] != 0 && selected[3] < 5){
                                cout << "Kill initiated on black" << endl;
                                for(int j = 0; j < bCheckers.size(); j++){
                                    if(bCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                        bCheckers[j].x = blackGraveyardRect.x;
                                        bCheckers[j].y = blackGraveyardRect.y;
                                        break;
                                    }
                                }
                                setJumpPerformed(jumpPerformed, true);
                                cout << "was set True, JumpPerformed: " << jumpPerformed << endl;
                            }

                            cout << "JumpPerformed: " << jumpPerformed << endl;

                            if(isJumpPossible(rectangles[i].x, rectangles[i].y, selected[1], rCheckers, bCheckers) && jumpPerformed){
                                cout << "It is possible for red to jump multiple times" << endl;

                                Draw(startUpMain);

                                currentChecker = selected[1];

                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos);

                                selected.insert(selected.end(), {1, currentChecker, i}); // - 0,1,2
                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos); // - 0

                                canvas(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                                circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);

                                if(selected[1] >= 12){
                                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                                }

                                jumps(rectangles[i].x, rectangles[i].y, i, selected[1], rCheckers, bCheckers);
                            }
                            else{
                                //End of turn.
                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos);
                                setJumpPerformed(jumpPerformed, false);

                                turnVal++;
                                thisTurn = (turnVal%2 == 0 ? 1 : 2);
                                updateText(); //Updates text.
                                promotionGUI(rCheckers);
                                Draw(startUpMain); //Draws new gamestate.

                                cout << "----- Red turn end -----" << endl;
                                //Robotmove

                                cout << "selected[0] after red turn: " << selected[0] << endl;

                                if(isGameWon(rCheckers, (turnVal%2 == 0 ? 1 : 2))){
                                    setGameEnd(true);
                                    setRedWon(true);
                                    rectangle(canvas, Point(115,0), Point(500,35), Scalar(255,255,255), -1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                                    putText(canvas, "Red has won.", Point(200, 25), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                                }
                            }
                        }
                        else{
                            stringPos.pop_back(); //If the move is invalid, remove invalid position.
                        }
                    }
                    else if(((turnVal%2 == 0) ? 1 : 2) == 1){ //If it is player 2's turn, run this code - To see code explaination see previous section, as they are basically identical.

                        cout << "JumpPerformed, black selected: " << jumpPerformed << endl;

                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                        
                        cout << "JumpPerformed, before move approval: " << jumpPerformed << endl;
                        cout << stringPos[0] << endl;
                        cout << stringPos[1] << endl;
                        cout << stringPos.size() << endl;

                        if(playerMover(stringPos[0], stringPos[1], ((turnVal%2 == 0) ? 1 : 2), boards)){

                            cout << "JumpPerformed, after move approval: " << jumpPerformed << endl;

                            bCheckers[selected[1]].x = rectangles[i].x;
                            bCheckers[selected[1]].y = rectangles[i].y;
                            cout << "Changed location of piece number: " << selected[1] << " to coordinates: " << rectangles[i].x << "," << rectangles[i].y << endl;
                            //cout << bCheckers[selected[1]].x << "," << bCheckjumps(ers[selected[1]].y << endl;

                            boardChange(((turnVal%2 == 0) ? 1 : 2), boards, stringPos[0], stringPos[1], redPieces, blackPieces);
                            checkerBoard(boards);

                            if(selected[3] != 0 && selected[3] < 5){
                                cout << "Kill initiated on Red" << endl;
                                for(int j = 0; j < rCheckers.size(); j++){
                                    if(rCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                        rCheckers[j].x = redGraveyardRect.x;
                                        rCheckers[j].y = redGraveyardRect.y;
                                        break;
                                    }
                                }

                                setJumpPerformed(jumpPerformed, true);
                                cout << "was set True, JumpPerformed: " << jumpPerformed << endl;
                            }

                            if(isJumpPossible(rectangles[i].x, rectangles[i].y, selected[1], bCheckers, rCheckers) && jumpPerformed){
                                Draw(startUpMain);
                                cout << "It is possible for black to jump twice" << endl;

                                cout << "selected[3]: " << selected[3] << endl;

                                currentChecker = selected[1];

                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos); 

                                selected.insert(selected.end(), {0, currentChecker, i});
                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                                canvas(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                                circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1); //Redraws the checker, as the highlighting (previous line of code) draws over it.
                                
                                if(selected[1] >= 12){
                                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                                }

                                jumps(rectangles[i].x, rectangles[i].y, i, selected[1], bCheckers, rCheckers);
                            }
                            else{
                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos);
                                setJumpPerformed(jumpPerformed, false);

                                cout << "Er spillet slut? black: " << isGameWon(rCheckers, (turnVal%2 == 0 ? 1 : 2)) << endl;

                                if(isGameWon(bCheckers, ((turnVal%2 == 0) ? 2 : 1))){
                                    cout << "black won the game" << endl;
                                    setGameEnd(true);
                                    Draw(startUpMain); //Draws new gamestate.
                                    imshow(winName, canvas);
                                }

                                turnVal++;
                                thisTurn = (turnVal%2 == 0 ? 1 : 2);
                                updateText(); //Updates text.
                                promotionGUI(bCheckers);
                                Draw(startUpMain); //Draws new gamestate.

                                cout << "----- Black turn end -----" << endl;
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
                    cout << "Rect: " << rectangles[i] << " som rect nummer: " << i << endl;
                        for(int j = 0; j < (rCheckers.size() > bCheckers.size() ? rCheckers.size() : bCheckers.size()); j++){
                            if(rCheckers[j].contains(Point(userX, userY)) && turnVal%2 == 1){ //Checks if there is a checker on the Rect, corresponding to the which players turn it is.
                                
                                cout << "Brik: " << j << endl;
                                canvas(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                                circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1); //Redraws the checker, as the highlighting (previous line of code) draws over it.

                                if(j >= 12){
                                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                                }

                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos); //Converts position of selected checker to string notation and saves the value in "stringPos".

                                selected.push_back(1); //Represents color of checker - not needed
                                selected.push_back(j); //Vector ID of checker in rCheckers[].
                                selected.push_back(i); //Vector ID of rect in rectangles[].

                                jumps(rectangles[i].x, rectangles[i].y, i, j, rCheckers, bCheckers);
                            }
                            else if(bCheckers[j].contains(Point(userX, userY)) && turnVal%2 == 0){ //Same as for the previous section.
                                
                                canvas(rectangles[i]) = Vec3b(0,0,255);
                                circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                                
                                if(j >= 12){
                                    putText(canvas, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                                }
                                
                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                                selected.push_back(0);
                                selected.push_back(j);
                                selected.push_back(i);

                                cout << "Black Jumps" << endl;
                                jumps(rectangles[i].x, rectangles[i].y, i, j, bCheckers, rCheckers);
                            }
                        }
                    break;
                }
            }
        }
        else if(gameEnd){

            cout << "Game has ended" << endl;

            winAnimation();
            setGameEnd(false);
        }
    }
    else if((turnVal%2 == 0 ? 1 : 2) == 2 && gameMode == "AI" && !gameEnd || (turnVal%2 == 0 ? 1 : 2) == 2 && gameMode == "DB" && !gameEnd){
        cout << "----------------------------------------" << endl << "AI's turn." << endl;
        do{
            if(gameMode == "AI"){
                alphaBeta(boards, 5, thisTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, thisTurn, {});
            }
            else{
                //std::string DBmove = MovePlayer(OldBoard, playerTurn); // Database best move on current board
                string DBmove = "";

                if(/*DBmove == "no moves"*/1){
                    //std::cout << "No moves found" << std::endl;
                    alphaBeta(boards, 5, thisTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, thisTurn, {}); //AI's move
                }
                else{
                    std::string DBmoveFrom = DBmove.substr(0,2);
                    std::string DBmoveTo = DBmove.substr(2,2);
                    DB_move(thisTurn, boards, redPieces, blackPieces, DBmoveFrom, DBmoveTo); //Database AI's move
                    moveSet[moveSet.size()-2] = DBmoveFrom;
                    moveSet[moveSet.size()-1] = DBmoveTo;
                }
            }
            cout << moveSet[0] << "," << moveSet[1] << endl;

            stringToPosConvert(moveSet[moveSet.size()-2], intPos);
            cout << "IntPos ved ai turn 1: " << intPos[intPos.size()-2] << "," << intPos[intPos.size()-1] << endl;

            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){
                    //selected.push_back(i);

                    for(int j = 0; j < rCheckers.size(); j++){
                        if(rCheckers[j].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){

                            selected.push_back(j);
                            cout << "Rød brik: " << j << " blev valgt på ai turn." << endl;
                            cout << "Selected[-1] ved pushBack: " << selected[selected.size()-1] << endl;
                            break;
                        }
                    }

                    stringToPosConvert(moveSet[moveSet.size()-1], intPos);
                    cout << "IntPos ved ai turn 2: " << intPos[intPos.size()-2] << "," << intPos[intPos.size()-1] << endl;

                    for(int j = 0; j < bCheckers.size(); j++){
                        if(bCheckers[j].contains(Point((intPos[intPos.size()-2] + intPos[intPos.size()-4])/2, (intPos[intPos.size()-1] + intPos[intPos.size()-3])/2))){
                            bCheckers[j].x = blackGraveyardRect.x;
                            bCheckers[j].y = blackGraveyardRect.y;
                            setJumpPerformed(jumpPerformed, true);
                            break;
                        }
                    }
                }
            }

            /*canvas(rectangles[selected[selected.size()-2]]) = Vec3b(0,0,255);
            circle(canvas, {rectangles[selected[selected.size()-2]].x + 25, rectangles[selected[selected.size()-2]].y + 25}, 20, Vec3b(14,17,175), -1);
            imshow(winName, canvas);*/

            rCheckers[selected[selected.size()-1]].x = intPos[intPos.size()-2];
            rCheckers[selected[selected.size()-1]].y = intPos[intPos.size()-1];

            cout << "Selected[-1]:" << selected[selected.size()-1] << endl;


            boardChange(((turnVal%2 == 0) ? 1 : 2), boards, moveSet[moveSet.size()-2], moveSet[moveSet.size()-1], redPieces, blackPieces);
            checkerBoard(boards);
            Draw(startUpMain);

        }while(isJumpPossible(intPos[intPos.size()-2], intPos[intPos.size()-1], selected[selected.size()-1], rCheckers, bCheckers) && jumpPerformed);

        cout << "Er spillet slut? AI: " << isGameWon(rCheckers, (turnVal%2 == 0 ? 1 : 2)) << endl;

        if(isGameWon(rCheckers, (turnVal%2 == 0 ? 2 : 1))){
            cout << "Red AI, won the game." << endl;
            setGameEnd(true);
            setRedWon(true);
            Draw(startUpMain);
            setRedWon(true);
            rectangle(canvas, Point(115,0), Point(500,35), Scalar(255,255,255), -1);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
            putText(canvas, "Red has won.", Point(200, 25), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }

        clearVecInt(selected);
        setJumpPerformed(jumpPerformed, false);

        turnVal++;
        thisTurn = (turnVal%2 == 0 ? 1 : 2);
        updateText();
        promotionGUI(rCheckers);
        Draw(startUpMain); //Draws new gamestate.
    }
    else if(gameMode == "AI" && gameEnd){
        winAnimation();
        //setGameEnd(false);
    }

    imshow(winName, canvas);
}

int main(){

    while(!gameEnd){

        //start:

        if(startUpMain){
            do{
                drawGameMode();
                imshow(winName, canvas);
                setMouseCallback(winName, gameModeCallBack);
                waitKey(0);
            }while(gameMode.empty());

            rCheckers.clear();

            Draw(startUpMain);
            updateText();
            imshow(winName, canvas);

            //boards = startUp();
        }

        //Creates window, and shows image on it.
        namedWindow(winName, WINDOW_AUTOSIZE);
        setMouseCallback(winName, callBackFunc);

        waitKey(0);
        cout << "Passed waitkey" << endl;
        if(waitKey(0) == 27){
            exit(0);
            cout << "Escape was pressed and window was subsequently destroyed" << endl;
        }
        /*else if(redWon){
            cout << "Going to start" << endl;
            setGameEnd(false);
            startUpMain = true;
            rCheckers.clear();
            bCheckers.clear();
            turnVal = 0;
            goto start;

            //Skal også reset aksels kode.
        }*/
    }

    return 0;
}
