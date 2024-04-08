#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat3b img(500, 1000, Vec3b(255, 255, 255)); //Creates drawing surface, img.
vector<Rect> rectangles; //Vec consisting of instances of "Rect", as segments of board.
vector<Circle> bCheckers; //Vec consisting of instances of "Circle" for black checkers.
vector<Circle> rCheckers; //Vec consisting of instances of "Circle" for red checkers.
Rect blackGraveyardRect(600, 75, 50, 50); //Instance of Rect, used as a graveyard Rect.
Rect redGraveyardRect(600, 175, 50, 50);
Rect promotionRect(600, 225, 50, 50);
Mat graveyardDownSized;

vector<int> selected; //Vec consisting of INT, that refer to information of selected Rect.

bool startUpMain = true; //Bool, true if code is being run for the first time.

int thisTurn; //Which player's turn it is

//Updates text displayed, depending player turn.
void updateText(Mat img, int turnVal){
    string spiller1 = "Det er spiller 1's tur.";
    string spiller2 = "Det er spiller 2's tur.";
    string playerTurnString;

    ((turnVal%2 == 0) ? playerTurnString = spiller1 : playerTurnString = spiller2);

    rectangle(img, Point(115,0), Point(500,35), Scalar(255,255,255), -1); //Creates a white rectangle, that covers the old text.
    putText(img, playerTurnString, Point(115, 25), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1); //Prints new text.
}

void drawGameMode(Mat img){

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
void Draw(Mat img, bool& startUpMain){
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
        
        rectangle(img, Point(0,0), Point(img.cols, img.rows), Scalar(255,255,255), -1);

        //Generates row and col names along board edge.
        for(int i = 0; i < 8; i++){
            putText(img, numArr[i], Point((i * 50) + boardOffSetX + 12, boardOffSetY - 5), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
            putText(img, alphabetArr[i], Point(boardOffSetX - 30, (i * 50) + boardOffSetY + 35), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
        }

        //Loads graveyard segment image, and resizes it to fit inside rect.
        resize(imread("/home/mads-hyrup/Uni/2.-Semester/SemesterProjekt/Projekt/graveyard.jpg"), graveyardDownSized, Size(50, 50), INTER_LINEAR);
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
        else if(movePossible(turn, boards, jumpPossible(turn, boards), false, "").size() < 1){
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
        else if(movePossible(turn, boards, jumpPossible(turn, boards), false, "").size() < 1){
            return true;
        }
        else{
            return false;
        }
    }
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