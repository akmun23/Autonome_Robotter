#include "alphabeta.h"
#include "boardUpdate.h"
#include "checkersdatabase.h"
#include "robot.h"
#include "validmoves.h"
#include "GameFunctions.h"

#include <iostream>
#include <opencv4/opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat3b img(500, 1000, Vec3b(255, 255, 255)); //Creates drawing surface, img.
vector<Rect> rectangles; //Vec consisting of instances of "Rect", as segments of board.
vector<Circle> bCheckers, rCheckers; //Vec consisting of instances of "Circle" for black checkers.
vector<int> latestScores = {};
vector<std::string> moveSet = {"",""}; //The moves that have been made during the turn
Rect blackGraveyardRect(600, 75, 50, 50); //Instance of Rect, used as a graveyard Rect.
Rect redGraveyardRect(600, 175, 50, 50);
Rect takePicture(Point(redGraveyardRect.x - 30, redGraveyardRect.y + 100), Point(redGraveyardRect.x + 80, redGraveyardRect.y + 150));
Rect promotionRect(600, 225, 50, 50);
Mat graveyardDownSized;
vector<int> selected; //Vec consisting of INT, that refer to information of selected Rect.
string moveStart = "", moveEnd = "";
string winName = "Project GUI"; //Sets name of window being used.
string gameMode = "";
vector<string> stringPos; //Vec consisting of selected positions.
vector<int> intPos;
vector<string> latestMoves = {};

int currentChecker;
bool gameEnd = false;
bool redWon = false;
bool button = false;
int thisTurn = 1; //Which player's turn it is
int blackPieces = 12; //Initial number of black pieces
int redPieces = 12; //Initial number of red pieces
int depth = 7; //Depth of the minimax algorithm
std::vector<std::vector<std::string>> boards; //2D vec of strings, that represent the board state.

bool startUpMain = true; //Bool, true if code is being run for the first time.

Robot robot;
Vision vision;
validMoves validM;
alphaBeta alphaBeta(&validM, 0);

std::atomic_bool robotMoving(false);

void robotMoveThread(std::vector<std::vector<std::string>>& prevBoard, int thisTurn, Robot& robot){
    robotMoving = true;

    robot.robotMove(moveSet, prevBoard, thisTurn);

    robotMoving = false;
}

//Updates text displayed, depending player turn.
void updateText(Mat img, int turnVal, vector<int>& scores, vector<string>& moves, string moveStart, string moveEnd){
    string spiller1 = "It is Player 1's turn.";
    string spiller2 = "It is Player 2's turn.";
    string playerTurnString, outputString;

    ((thisTurn%2 == 1) ? playerTurnString = spiller1 : playerTurnString = spiller2);

    rectangle(img, Point(115,0), Point(500,35), Scalar(255,255,255), -1); //Creates a white rectangle, that covers the old text.
    putText(img, playerTurnString, Point(115, 25), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1); //Prints new text.

    if(turnVal > 0){
        outputString = moveStart + " To " + moveEnd + ": ";
        moves.push_back(outputString);
        scores.push_back(alphaBeta.giveScoreAI(boards, thisTurn, blackPieces, redPieces, depth)/1000);

        rectangle(img, Point(700,75), Point(1000,200), Scalar(255,255,255), -1);

        for(int i = (scores.size() < 5 ? 0 : scores.size()-5); i < scores.size(); i++){
            outputString = moves[i] + to_string(scores[i]);
            putText(img, outputString, Point(700, 90 + (i - (scores.size() < 5 ? 0 : scores.size()-5)) * 25), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0,0,0), 1);
        }
    }
}

void drawGameMode(Mat& img){

    Rect gameModeRectPVP((img.cols/2) - 200, (img.rows/2) - 40, 100, 50);
    Rect gameModeRectAI((img.cols/2) - 50, (img.rows/2) - 40, 100, 50);
    Rect gameModeRectDB((img.cols/2) + 100, (img.rows/2) - 40, 100, 50);

    rectangle(img, Point(0,0), Point(img.cols, img.rows), Scalar(255,255,255), -1);
    rectangle(img, gameModeRectPVP, Scalar(0,0,0), 2);
    putText(img, "PvP", Point(gameModeRectPVP.x + 20, gameModeRectPVP.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
    rectangle(img, gameModeRectAI, Scalar(0,0,0), 2);
    putText(img, "AI", Point(gameModeRectAI.x + 35, gameModeRectAI.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
    rectangle(img, gameModeRectDB, Scalar(0,0,0), 2);
    putText(img, "DB", Point(gameModeRectDB.x + 30, gameModeRectDB.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
    putText(img, "Press any button after selecting gamemode, to start the game.", Point(gameModeRectPVP.x - 200, 2*img.rows/3), FONT_HERSHEY_COMPLEX, 0.75, Scalar(0,0,0), 1);
}

void winAnimation(string winName, Mat img, bool redWon, vector<Rect> rectangles){
    for(int i = 0; i < (img.rows/50)/2; i++){
        for(int j = 0; j < ((img.cols - 100 * i)/50); j++){
            rectangle(img, Point(j*50 + i*50, i*50), Point((j*50 + i*50) + 50, (i*50) + 50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, img);
        }
        for(int j = 0; j < ((img.rows - 100 * i)/50); j++){
            rectangle(img, Point((img.cols - i*50 - 50), (j*50 + i*50)), Point(img.cols - i*50, (j*50 + i*50) + 50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, img);
        }
        for(int j = 0; j < ((img.cols - 100 * i)/50); j++){
            rectangle(img, Point(img.cols - (j*50 + i*50), img.rows - i*50 - 50), Point((img.cols - (j*50 + i*50)) + 50, img.rows - i*50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, img);
        }
        for(int j = 0; j < ((img.rows - 100 * i)/50); j++){
            rectangle(img, Point((i*50), (img.rows - (j*50 + i*50))), Point((i*50) + 50, (img.rows - (j*50 + i*50)) + 50), (redWon ? Scalar(14,17,175) : Scalar(0,0,0)), -1);
            waitKey(20);
            imshow(winName, img);
        }
    }

    putText(img, (redWon ? "RED HAS WON" : "BLACK HAS WON"), (redWon ? Point(((rectangles[0].x + rectangles[63].x)/2), (rectangles[0].y + rectangles[63].y)/2) : Point((((rectangles[0].x + rectangles[63].x)/2) - 40), (rectangles[0].y + rectangles[63].y)/2)), FONT_HERSHEY_COMPLEX, 2, (redWon ? Scalar(0,0,0) : Scalar(255,255,255)), 1);
    imshow(winName, img);
}

//Draws all elements of the GUI.
void Draw(Mat& img, bool& startUpMain){
    int redGrave = 0;
    int blackGrave = 0;
    int lineNum = 0;
    int width = 50;
    int height = 50;
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    //If first time running the code, run this section.
    if(startUpMain){
        
        rectangle(img, Point(0,0), Point(img.cols, img.rows), Scalar(255,255,255), -1); //Clears the screen

        //Generates row and col names along board edge.
        for(int i = 0; i < 8; i++){
            putText(img, numArr[i], Point((i * 50) + boardOffSetX + 12, boardOffSetY - 5), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
            putText(img, alphabetArr[i], Point(boardOffSetX - 30, (i * 50) + boardOffSetY + 35), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
        }

        //Loads graveyard segment image, and resizes it to fit inside rect.
        resize(imread("/home/aksel/Documents/GitHub/Autonome_Robotter/GUI/GUI VERSIONS/V3.5/graveyard.jpg"), graveyardDownSized, Size(50, 50), INTER_LINEAR);
        graveyardDownSized.copyTo(img(blackGraveyardRect)); //Draws graveyard onto img.
        graveyardDownSized.copyTo(img(redGraveyardRect));

        //Generates board pieces and checkers, while also filling up the corresponding vectors with instances of corresponding vectors.
        for(int i = 0; i < 64; i++){
            int x = (i%8) * 50 + boardOffSetX;
            int y = lineNum * 50 + boardOffSetY;

            rectangles.push_back(Rect(x,y,width,height));

            if(i%2){
                if(lineNum%2){
                    img(rectangles[i]) = Vec3b(90,145,201); //Light-brown color code
                }

                else{
                    img(rectangles[i]) = Vec3b(33,67,101); //Dark-brown color code

                    if(lineNum < 3){
                        bCheckers.push_back(Circle(x, y, 50, 50));
                        circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                    }

                    else if(lineNum > 4){
                        rCheckers.push_back(Circle(x, y, 50, 50));
                        circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                    }
                }
            }
            else{
                if(lineNum%2){
                    img(rectangles[i]) = Vec3b(33,67,101);

                    if(lineNum < 3){
                        bCheckers.push_back(Circle(x, y, 50, 50));
                        circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                    }

                    else if(lineNum > 4){
                        rCheckers.push_back(Circle(x, y, 50, 50));
                        circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                    }
                }
                else{
                    img(rectangles[i]) = Vec3b(90,145,201);
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
                    img(rectangles[i]) = Vec3b(90,145,201);
                }

                else{
                    img(rectangles[i]) = Vec3b(33,67,101);
                }
            }
            else{
                if(lineNum%2){
                    img(rectangles[i]) = Vec3b(33,67,101);
                }
                else{
                    img(rectangles[i]) = Vec3b(90,145,201);
                }
            }

            (i%8 == 7) ? lineNum++ : lineNum;
        }
    }

    //COPY
    rectangle(img, takePicture, Scalar(0,0,0), -1);
    putText(img, "Take Picture", Point(takePicture.x + 8, takePicture.y + 30), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar(255,255,255));
    //

    //Draws checkers on new positions.
    for(int j = 0; j < 12; j++){
        for(int i = 0; i < 64; i++){
            if(rCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                break;
            }
        }
    }
    for(int j = 0; j < 12; j++){
        for(int i = 0; i < 64; i++){
            if(bCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                break;
            }
        }
    }

    for(int j = 0; j < (rCheckers.size() > bCheckers.size() ? rCheckers.size() : bCheckers.size()); j++){
        if(rCheckers[j].contains(Point(redGraveyardRect.x, redGraveyardRect.y))){
            circle(img, {redGraveyardRect.x + 25, redGraveyardRect.y + 25}, 20, Vec3b(14,17,175), -1);
            
            redGrave = count_if(rCheckers.begin(), rCheckers.end(), [](Circle obj){
                return(obj.x == redGraveyardRect.x && obj.y == redGraveyardRect.y);
            });

            if(redGrave){
                putText(img, to_string(redGrave), (redGrave < 10 ? Point(redGraveyardRect.x + 15, redGraveyardRect.y + 35) : Point(redGraveyardRect.x + 4, redGraveyardRect.y + 35)), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
            }
        }
        if(bCheckers[j].contains(Point(blackGraveyardRect.x, blackGraveyardRect.y))){
            circle(img, {blackGraveyardRect.x + 25, blackGraveyardRect.y + 25}, 20, Vec3b(0,0,0), -1);
            
            blackGrave = count_if(bCheckers.begin(), bCheckers.end(), [](Circle obj){
                return(obj.x == blackGraveyardRect.x && obj.y == blackGraveyardRect.y);
            });
            
            if(blackGrave){
                putText(img, to_string(blackGrave), (blackGrave < 10 ? Point(blackGraveyardRect.x + 15, blackGraveyardRect.y + 35) : Point(blackGraveyardRect.x + 4, blackGraveyardRect.y + 35)), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
            }
        }
    }

    if(rCheckers.size() > 12){
        for(int i = 0; i < 64; i++){
            for(int j = 12; j < rCheckers.size(); j++){
                if(rCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                    circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                    break;
                }
            }
        }
    }

    if(bCheckers.size() > 12){
        for(int i = 0; i < 64; i++){
            for(int j = 12; j < bCheckers.size(); j++){
                if(bCheckers[j].contains(Point(rectangles[i].x, rectangles[i].y))){
                    //cout << "Found checker at: " << rectangles[i].x << "," << rectangles[i].y << endl;
                    circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                    break;
                }
            }
        }
    }


}

//Checks if a jump is possible for an element of given vector at a given position.
bool isJumpPossible(int x, int y, int checkerID, vector<Circle> checkerVec, vector<Circle> enemyCheckerVec){

    if(enemyCheckerVec == bCheckers){
        if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)){
            if(doesPosContainRect(x + 100, y - 100, rectangles)){
                return true;
            }
        }
        else if(doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)){
            if(doesPosContainRect(x - 100, y - 100, rectangles)){
                return true;
            }
        }

        if(checkerID >= 12){

            if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)){
                if(doesPosContainRect(x + 100, y + 100, rectangles)){
                    return true;
                }
            }
            else if(doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles)){
                if(doesPosContainRect(x - 100, y + 100, rectangles)){
                    return true;
                }
            }
        }
    }
    else{
        if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)){
            if(doesPosContainRect(x + 100, y + 100, rectangles)){
                return true;
            }
        }
        else if(doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles)){
            if(doesPosContainRect(x - 100, y + 100, rectangles)){
                return true;
            }
        }

        if(checkerID >= 12){
            if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)){
                if(doesPosContainRect(x + 100, y - 100, rectangles)){
                    return true;
                }
            }
            else if(doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)){
                if(doesPosContainRect(x - 100, y - 100, rectangles)){
                    return true;
                }
            }
        }
    }

    return false;
}

void jumps(int x, int y, int i, int checkerID, vector<Circle> checkerVec, vector<Circle> enemyCheckerVec){

    if(isJumpPossible(x, y, checkerID, checkerVec, enemyCheckerVec)){ //Checks if there is a jump possible for a checker at the given position, where the enemy is given also.
        //Checks if there is a checker across from the selected checker - Both right and left.
        if(checkerVec == rCheckers && checkerID < 12){ 
            if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec))){
                if(rectangles[i-14].contains(Point(x + 100, y - 100))){
                    img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                }
                if(rectangles[i-18].contains(Point(x - 100, y - 100))){
                img(rectangles[i-18]) = Vec3b(14,17,175);
                }
                
                selected.push_back(2); //Represents multiple jumps possible.
            }
            //Checks if there is a checker across from the selected checker - Right.
            else if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec)){
                if(rectangles[i-14].contains(Point(x + 100, y - 100))){
                    img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights.
                }
                selected.push_back(1); //Represents one jump possible.
            }
            else{
                if(rectangles[i-18].contains(Point(x - 100, y - 100))){
                    img(rectangles[i-18]) = Vec3b(14,17,175);
                }
                selected.push_back(1);
            }
        }
        else if(checkerVec == bCheckers && checkerID < 12){
            if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec))){
                if(rectangles[i+14].contains(Point(x - 100, y + 100))){ //skal tage højde for egne checker også
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                }
                if(rectangles[i+18].contains(Point(x + 100, y + 100))){
                img(rectangles[i+18]) = Vec3b(14,17,175);
                }

                selected.push_back(2);
            }
            else if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec)){
                if(rectangles[i+18].contains(Point(x + 100, y + 100))){
                    img(rectangles[i+18]) = Vec3b(14,17,175);
                    selected.push_back(1);
                }
            }
            else{
                if(rectangles[i+14].contains(Point(x - 100, y + 100))){
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                    selected.push_back(1);
                }
            }
        }

        if((thisTurn == 1 ? checkerVec == bCheckers : checkerVec == rCheckers) && (checkerID >= 12)){

            if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles))){
                img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                img(rectangles[i-18]) = Vec3b(14,17,175);
                img(rectangles[i+14]) = Vec3b(14,17,175);
                img(rectangles[i+18]) = Vec3b(14,17,175);
                selected.push_back(4); //Represents multiple jumps possible.

            }
            else if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles)) && (doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles))){

                img(rectangles[i+14]) = Vec3b(14,17,175);
                img(rectangles[i+18]) = Vec3b(14,17,175);
                selected.push_back(3);
                
                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec))){
                    img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                }
                else{
                    img(rectangles[i-18]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles)) || (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles) && (doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)))){

                img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                img(rectangles[i-18]) = Vec3b(14,17,175);
                selected.push_back(3);
                
                if((doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec))){
                    img(rectangles[i+18]) = Vec3b(14,17,175);
                }
                else{
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) || (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles))){

                selected.push_back(2); //3

                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec)) && (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec))){
                    img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                    img(rectangles[i-18]) = Vec3b(14,17,175);
                }
                else{
                    img(rectangles[i+18]) = Vec3b(14,17,175);
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles))){

                selected.push_back(2); //3

                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles))){
                    img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                    img(rectangles[i+18]) = Vec3b(14,17,175);
                }
                else{
                    img(rectangles[i-18]) = Vec3b(14,17,175);
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) && (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles))){

                selected.push_back(2); //3

                if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) && (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles))){
                    img(rectangles[i-14]) = Vec3b(14,17,175); //Highlights the possible jump locations.
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                }
                else{
                    img(rectangles[i-18]) = Vec3b(14,17,175);
                    img(rectangles[i+18]) = Vec3b(14,17,175);
                }
            }
            else if((doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)) || (doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)) || (doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)) || (doesRectContainChecker(x - 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y + 100, checkerVec) && doesPosContainRect(x - 100, y + 100, rectangles))){
                
                selected.push_back(1); //3

                if(doesRectContainChecker(x + 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y - 100, checkerVec) && doesPosContainRect(x + 100, y - 100, rectangles)){
                    img(rectangles[i-14]) = Vec3b(14,17,175);
                }
                else if(doesRectContainChecker(x - 50, y - 50, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, enemyCheckerVec) && !doesRectContainChecker(x - 100, y - 100, checkerVec) && doesPosContainRect(x - 100, y - 100, rectangles)){
                    img(rectangles[i-18]) = Vec3b(14,17,175);
                }
                else if(doesRectContainChecker(x + 50, y + 50, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, enemyCheckerVec) && !doesRectContainChecker(x + 100, y + 100, checkerVec) && doesPosContainRect(x + 100, y + 100, rectangles)){
                    img(rectangles[i+18]) = Vec3b(14,17,175);
                }
                else{
                    img(rectangles[i+14]) = Vec3b(14,17,175);
                }
            }
        }
    }
}

void promotionGUI(vector<Circle> checkerVector){
    if(checkerVector == rCheckers){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 12; j++){
                if(rectangles[i].contains(Point(rCheckers[j].x,rCheckers[j].y))){
                    rCheckers[j].x = promotionRect.x;
                    rCheckers[j].y = promotionRect.y;
                    rCheckers.push_back(Circle(rectangles[i].x, rectangles[i].y, 50, 50));
                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                }
            }
        }
    }
    else{
        for(int i = 56; i < 64; i++){
            for(int j = 0; j < 12; j++){
                if(rectangles[i].contains(Point(bCheckers[j].x,bCheckers[j].y))){
                    bCheckers[j].x = promotionRect.x;
                    bCheckers[j].y = promotionRect.y;
                    bCheckers.push_back(Circle(rectangles[i].x, rectangles[i].y, 50, 50));
                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                }
            }
        }
    }
}

bool isGameWon(vector<Circle> checkerVec, vector<Circle> enemyCheckerVec, int turn){
    if(checkerVec == rCheckers){
        if(piecesLeft(rectangles, enemyCheckerVec) < 1){
            return true;
        }
        else if(validM.movePossible().size() < 1){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(piecesLeft(rectangles, enemyCheckerVec) < 1){
            return true;
        }
        else if(validM.movePossible().size() < 1){
            return true;
        }
        else{
            return false;
        }
    }
}

void gameModeCallBack(int event, int userX, int userY, int flags, void* userdata){

    Rect gameModeRectPVP((img.cols/2) - 200, (img.rows/2) - 40, 100, 50);
    Rect gameModeRectAI((img.cols/2) - 50, (img.rows/2) - 40, 100, 50);
    Rect gameModeRectDB((img.cols/2) + 100, (img.rows/2) - 40, 100, 50);

    if(event == EVENT_LBUTTONDOWN){
        if(gameModeRectPVP.contains(Point(userX, userY))){
            setString(gameMode, "PVP");
            drawGameMode(img);
            rectangle(img, gameModeRectPVP, Scalar(0,0,255), 2);
            putText(img, "PvP", Point(gameModeRectPVP.x + 20, gameModeRectPVP.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }
        else if(gameModeRectAI.contains(Point(userX, userY))){
            setString(gameMode, "AI");
            drawGameMode(img);
            rectangle(img, gameModeRectAI, Scalar(0,0,255), 2);
            putText(img, "AI", Point(gameModeRectAI.x + 35, gameModeRectAI.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }
        else if(gameModeRectDB.contains(Point(userX, userY))){
            setString(gameMode, "DB");
            drawGameMode(img);
            rectangle(img, gameModeRectDB, Scalar(0,0,255), 2);
            putText(img, "DB", Point(gameModeRectDB.x + 30, gameModeRectDB.y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
        }
    }

    imshow(winName, img);
}

//callBack function, that runs every time you click.
void callBackFunc(int event, int userX, int userY, int flags, void* userdata){
    if(robotMoving){
        imshow(winName, img);
        return;
    }

    std::vector<std::vector<std::string>> prevBoard = robot.getBoard();
    if(gameMode == "PVP"  && (!button)|| (thisTurn == 1 && gameMode == "AI" && (!button)) || (thisTurn == 1 && gameMode == "DB" && (!button))){
        if(selected.size() != 0 && event == EVENT_LBUTTONDOWN){ //Runs this code left mouse button clicked and "Rect" is already selected.
            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(userX,userY))){ //Checks if the click is inside of the game board.
                    //If click is at the same location as previously selected, then deselect.
                    if(rectangles[selected[2]].x == rectangles[i].x && rectangles[selected[2]].y == rectangles[i].y){
                        Draw(img, startUpMain); //Draws new game state.
                        clearVecInt(selected); //Clears vector selected.
                        clearVecString(stringPos);
                    }
                    else if(thisTurn == 2){ //If it is player 2's turn, run this code.
                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                        //Checks if move is legal.
                        if(validM.DB_move(stringPos[0], stringPos[1])){

                            moveSet = {stringPos[0], stringPos[1]};
                            blackPieces = validM.getPieceCount()[0];
                            redPieces = validM.getPieceCount()[1];

                            //Changes the position of selected checker.
                            rCheckers[selected[1]].x = rectangles[i].x;
                            rCheckers[selected[1]].y = rectangles[i].y;

                            //If a jump has been performed, find and remove the "killed" checker.
                            if(selected[3] != 0 && selected[3] < 5){
                                for(int j = 0; j < bCheckers.size(); j++){
                                    if(bCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                        bCheckers[j].x = blackGraveyardRect.x;
                                        bCheckers[j].y = blackGraveyardRect.y;
                                        break;
                                    }
                                }
                            }

                            //End of turn.
                            if(isGameWon(rCheckers, bCheckers, thisTurn)){
                                setBool(gameEnd, true);
                                setBool(redWon, true);
                            }

                            std::thread moveThread(robotMoveThread, std::ref(prevBoard), thisTurn, std::ref(robot));
                            moveThread.detach();
                            thisTurn = validM.getPlayerTurn();
                            updateText(img, thisTurn, latestScores, latestMoves, moveStart, moveEnd); //Updates text.
                            promotionGUI(rCheckers);
                            boards = validM.getBoards();
                            checkerBoard(boards);
                            Draw(img, startUpMain);
                            imshow(winName, img);
                            clearVecInt(selected); //Clears vector selected.
                            clearVecString(stringPos);

                            cout << "----- Red turn end -----" << endl;
                        }
                        else{
                            stringPos.pop_back(); //If the move is invalid, remove invalid position.
                        }
                    }
                    else if(thisTurn == 1){ //If it is player 1's turn, run this code - To see code explaination see previous section, as they are basically identical.

                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);

                        if(validM.DB_move(stringPos[0], stringPos[1])){

                            moveSet = {stringPos[0], stringPos[1]};
                            blackPieces = validM.getPieceCount()[0];
                            redPieces = validM.getPieceCount()[1];

                            bCheckers[selected[1]].x = rectangles[i].x;
                            bCheckers[selected[1]].y = rectangles[i].y;

                            if(selected[3] != 0 && selected[3] < 5){
                                for(int j = 0; j < rCheckers.size(); j++){
                                    if(rCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                        rCheckers[j].x = redGraveyardRect.x;
                                        rCheckers[j].y = redGraveyardRect.y;
                                        break;
                                    }
                                }
                            }

                            if(isGameWon(bCheckers, rCheckers, thisTurn)){
                                setBool(gameEnd, true);
                            }

                            std::thread moveThread(robotMoveThread, std::ref(prevBoard), thisTurn, std::ref(robot));
                            moveThread.detach();
                            thisTurn = validM.getPlayerTurn();
                            boards = validM.getBoards();
                            checkerBoard(boards);

                            updateText(img, thisTurn, latestScores, latestMoves, moveSet[0], moveSet[1]); //Updates text.
                            promotionGUI(bCheckers);
                            Draw(img, startUpMain);
                            imshow(winName, img);
                            clearVecInt(selected); //Clears vector selected.
                            clearVecString(stringPos);

                            cout << "----- Black turn end -----" << endl;
                        }
                        else{
                            stringPos.pop_back();
                        }
                    }
                }
            }
        }
        else if(event == EVENT_LBUTTONDOWN){ //If left mouse button is clicked and no checker was previously selected, run this code.
            if(takePicture.contains(Point(userX, userY))){
                moveSet = {};
                std::cout << "Pressed button" << std::endl;
                robot.prepForPic();
                moveSet = robot.boardLoop(boards, thisTurn); // Player's move
                std::cout << moveSet[0] << " " << moveSet[1] << std::endl;
                if(validM.DB_move(moveSet[0], moveSet[1])){
                    button = true;
                } else {
                    return;
                }
            } else {
                for(int i = 0; i < 64; i++){
                    if(rectangles[i].contains(Point(userX,userY))){ //Checks if click is inside game board.
                        for(int j = 0; j < (rCheckers.size() > bCheckers.size() ? rCheckers.size() : bCheckers.size()); j++){
                            if(rCheckers[j].contains(Point(userX, userY)) && thisTurn == 2){ //Checks if there is a checker on the Rect, corresponding to the which players turn it is.
                                //Use doesRectContainChecker
                                img(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                                circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1); //Redraws the checker, as the highlighting (previous line of code) draws over it.

                                if(j >= 12){
                                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                                }

                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos); //Converts position of selected checker to string notation and saves the value in "stringPos".
                                moveStart = stringPos[stringPos.size()-1];

                                selected.push_back(1); //Represents color of checker - not needed
                                selected.push_back(j); //Vector ID of checker in rCheckers[].
                                selected.push_back(i); //Vector ID of rect in rectangles[].

                                jumps(rectangles[i].x, rectangles[i].y, i, j, rCheckers, bCheckers);
                            }
                            else if(bCheckers[j].contains(Point(userX, userY)) && thisTurn == 1){ //Same as for the previous section.

                                img(rectangles[i]) = Vec3b(0,0,255);
                                circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);

                                if(j >= 12){
                                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                                }

                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                                moveStart = stringPos[stringPos.size()-1];

                                selected.push_back(0);
                                selected.push_back(j);
                                selected.push_back(i);

                                jumps(rectangles[i].x, rectangles[i].y, i, j, bCheckers, rCheckers);
                            }
                        }
                        break;
                    }
                }
            }
        }
        else if(gameEnd){
            winAnimation(winName, img, redWon, rectangles);
            setBool(gameEnd, false); //Stops animation
        }
    } else if((thisTurn == 2 && gameMode == "AI" && !gameEnd) || (thisTurn == 2 && gameMode == "DB" && !gameEnd) || button){
        if(!button){
            cout << "----- AI's turn -----" << endl;
            if(gameMode == "AI" && thisTurn == 2){
                alphaBeta.makeMove(boards, depth, thisTurn, redPieces, blackPieces, INT_MIN, INT_MAX, {}, thisTurn); //AI's move
                moveSet = alphaBeta.getMove();
            } else if ("DB" && thisTurn == 2){
                std::string BoardState;
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 8; ++j) {
                        if(boards[i][j] == "1 "){
                            BoardState += "1";
                        } else if(boards[i][j] == "B "){
                            BoardState += "2";
                        } else if(boards[i][j] == "BK"){
                            BoardState += "3";
                        } else if(boards[i][j] == "R "){
                            BoardState += "4";
                        } else if(boards[i][j] == "RK"){
                            BoardState += "5";
                        }
                    }
                }
                std::string DBmove = MovePlayer(BoardState, thisTurn); // Database best move on current board
                if (DBmove == "No moves"){
                    std::cout << "No moves found" << std::endl;
                    alphaBeta.makeMove(boards, depth, thisTurn, redPieces, blackPieces, INT_MIN, INT_MAX, {}, thisTurn); //AI's move
                    moveSet = alphaBeta.getMove();
                }   else{
                    std::cout << "AI move from database: " << DBmove << std::endl;
                    moveSet = {DBmove.substr(0,2), DBmove.substr(2,2)};
                    if (validM.DB_move(moveSet[0], moveSet[1])){

                    }
                    else{
                        alphaBeta.makeMove(boards, depth, thisTurn, redPieces, blackPieces, INT_MIN, INT_MAX, {}, thisTurn); //AI's move
                        moveSet = alphaBeta.getMove();
                    }
                }
            }

            cout << moveSet[0] << "," << moveSet[1] << endl;

            std::thread moveThread(robotMoveThread, std::ref(prevBoard), thisTurn, std::ref(robot));
            moveThread.detach();
        }
        button = false;
        stringToPosConvert(moveSet[0], intPos);

        if(thisTurn == 2){
            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){
                    //selected.push_back(i);

                    for(int j = 0; j < rCheckers.size(); j++){
                        if(rCheckers[j].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){
                            selected.push_back(j);
                            break;
                        }
                    }

                    stringToPosConvert(moveSet[1], intPos);

                    for(int j = 0; j < bCheckers.size(); j++){
                        if(bCheckers[j].contains(Point((intPos[intPos.size()-2] + intPos[intPos.size()-4])/2, (intPos[intPos.size()-1] + intPos[intPos.size()-3])/2))){
                            bCheckers[j].x = blackGraveyardRect.x;
                            bCheckers[j].y = blackGraveyardRect.y;
                            break;
                        }
                    }
                }
            }

            img(rectangles[selected[selected.size()-2]]) = Vec3b(0,0,255);
            circle(img, {rectangles[selected[selected.size()-2]].x + 25, rectangles[selected[selected.size()-2]].y + 25}, 20, Vec3b(14,17,175), -1);

            rCheckers[selected[selected.size()-1]].x = intPos[intPos.size()-2];
            rCheckers[selected[selected.size()-1]].y = intPos[intPos.size()-1];

        } else if(thisTurn == 1){
            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){
                    //selected.push_back(i);

                    for(int j = 0; j < bCheckers.size(); j++){
                        if(bCheckers[j].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){
                            selected.push_back(j);
                            break;
                        }
                    }

                    stringToPosConvert(moveSet[1], intPos);

                    for(int j = 0; j < rCheckers.size(); j++){
                        if(rCheckers[j].contains(Point((intPos[intPos.size()-2] + intPos[intPos.size()-4])/2, (intPos[intPos.size()-1] + intPos[intPos.size()-3])/2))){
                            rCheckers[j].x = redGraveyardRect.x;
                            rCheckers[j].y = redGraveyardRect.y;
                            break;
                        }
                    }
                }
            }

            img(rectangles[selected[selected.size()-2]]) = Vec3b(0,0,255);
            circle(img, {rectangles[selected[selected.size()-2]].x + 25, rectangles[selected[selected.size()-2]].y + 25}, 20, Vec3b(14,17,175), -1);

            bCheckers[selected[selected.size()-1]].x = intPos[intPos.size()-2];
            bCheckers[selected[selected.size()-1]].y = intPos[intPos.size()-1];
        }

        if(isGameWon(rCheckers, bCheckers, thisTurn)){
            setBool(gameEnd, true);
            setBool(redWon, true);
            Draw(img, startUpMain);
        }
        clearVecInt(selected);
        blackPieces = validM.getPieceCount()[0];
        redPieces = validM.getPieceCount()[1];
        thisTurn = validM.getPlayerTurn();
        boards = validM.getBoards();
        checkerBoard(boards);

        updateText(img, thisTurn, latestScores, latestMoves, moveSet[0], moveSet[1]);
        promotionGUI(rCheckers);
        promotionGUI(bCheckers);
        Draw(img, startUpMain); //Draws new gamestate.
        imshow(winName, img);

    } else if(gameMode == "AI" && gameEnd && thisTurn == 2 || gameMode == "DB" && gameEnd && thisTurn == 2){
        winAnimation(winName, img, redWon, rectangles);
    }

    imshow(winName, img);
}
