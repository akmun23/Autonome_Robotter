#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include "validMoves.h"
//#include "boardUpdate.h"
#include "GameFunctions.h"
#include "DrawFunctions.h"
//#include "robotMove.h"
//#include <unistd.h>
//#include <ur_rtde/rtde_control_interface.h>
//#include <ur_rtde/rtde_receive_interface.h>

using namespace cv;
using namespace std;

string winName = "Project GUI"; //Sets name of window being used.
string gameMode = "";

vector<std::vector<double>> startUpRobot;
vector<string> stringPos; //Vec consisting of selected positions.
vector<int> intPos;
vector<string> latestMoves;

int currentChecker;
int turnVal = 0; //Array containing INT representing how many turns have been taken.

bool jumpPerformed = false;
bool gameEnd = false;
bool redWon = false;

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

    if(gameMode == "PVP" || thisTurn == 1 && gameMode == "AI" || thisTurn == 1 && gameMode == "DB"){
        if(selected.size() != 0 && event == EVENT_LBUTTONDOWN){ //Runs this code left mouse button clicked and "Rect" is already selected.

            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(userX,userY))){ //Checks if the click is inside of the game board.

                    //If click is at the same location as previously selected, then deselect.
                    if(rectangles[selected[2]].x == rectangles[i].x && rectangles[selected[2]].y == rectangles[i].y){
                        Draw(img, startUpMain); //Draws new game state.    
                        clearVecInt(selected); //Clears vector selected.
                        clearVecString(stringPos);
                    }
                
                    else if(thisTurn == 2){ //If it is player 1's turn, run this code.

                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                        if(!jumpPerformed){
                            moveEnd = stringPos[stringPos.size()-1];
                        }

                        //Checks if move is legal.
                        if(playerMover(stringPos[0], stringPos[1], thisTurn, boards)){
                            
                            //Changes the position of selected checker.
                            rCheckers[selected[1]].x = rectangles[i].x;
                            rCheckers[selected[1]].y = rectangles[i].y;
                            
                            //Changes gamestate in board.
                            boardChange(thisTurn, boards, stringPos[0], stringPos[1], redPieces, blackPieces);
                            //Prints new gamestate to console.
                            checkerBoard(boards);

                            //If a jump has been performed, find and remove the "killed" checker.
                            if(selected[3] != 0 && selected[3] < 5){
                                for(int j = 0; j < bCheckers.size(); j++){
                                    if(bCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                        bCheckers[j].x = blackGraveyardRect.x;
                                        bCheckers[j].y = blackGraveyardRect.y;
                                        break;
                                    }
                                }
                                setBool(jumpPerformed, true);
                            }

                            if(isJumpPossible(rectangles[i].x, rectangles[i].y, selected[1], rCheckers, bCheckers) && jumpPerformed){

                                Draw(img, startUpMain);

                                currentChecker = selected[1];

                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos);

                                selected.insert(selected.end(), {1, currentChecker, i}); // - 0,1,2
                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos); // - 0
                                moveEnd = stringPos[stringPos.size()-1];

                                img(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                                circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);

                                if(selected[1] >= 12){
                                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,0), 1);
                                }

                                jumps(rectangles[i].x, rectangles[i].y, i, selected[1], rCheckers, bCheckers);
                            }
                            else{
                                //End of turn.
                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos);
                                setBool(jumpPerformed, false);

                                turnVal++;
                                thisTurn = (turnVal%2 == 0 ? 1 : 2);
                                updateText(img, turnVal, latestScores, latestMoves, moveStart, moveEnd); //Updates text.
                                promotionGUI(rCheckers);
                                Draw(img, startUpMain); //Draws new gamestate.

                                //Robotmove

                                if(isGameWon(rCheckers, bCheckers, thisTurn)){
                                    setBool(gameEnd, true);
                                    setBool(redWon, true);
                                }

                                cout << "----- Red turn end -----" << endl;
                            }
                        }
                        else{
                            stringPos.pop_back(); //If the move is invalid, remove invalid position.
                        }
                    }
                    else if(thisTurn == 1){ //If it is player 2's turn, run this code - To see code explaination see previous section, as they are basically identical.

                        posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                        if(!jumpPerformed){
                            moveEnd = stringPos[stringPos.size()-1];
                        }

                        if(playerMover(stringPos[0], stringPos[1], thisTurn, boards)){

                            bCheckers[selected[1]].x = rectangles[i].x;
                            bCheckers[selected[1]].y = rectangles[i].y;

                            boardChange(thisTurn, boards, stringPos[0], stringPos[1], redPieces, blackPieces);
                            checkerBoard(boards);

                            if(selected[3] != 0 && selected[3] < 5){
                                for(int j = 0; j < rCheckers.size(); j++){
                                    if(rCheckers[j].contains(Point((rectangles[selected[2]].x + rectangles[i].x)/2, (rectangles[selected[2]].y + rectangles[i].y)/2))){
                                        rCheckers[j].x = redGraveyardRect.x;
                                        rCheckers[j].y = redGraveyardRect.y;
                                        break;
                                    }
                                }

                                setBool(jumpPerformed, true);
                            }

                            if(isJumpPossible(rectangles[i].x, rectangles[i].y, selected[1], bCheckers, rCheckers) && jumpPerformed){
                                Draw(img, startUpMain);

                                currentChecker = selected[1];

                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos); 

                                selected.insert(selected.end(), {0, currentChecker, i});
                                posToStringConvert(rectangles[i].x, rectangles[i].y, stringPos);
                                moveEnd = stringPos[stringPos.size()-1];

                                img(rectangles[i]) = Vec3b(0,0,255); //Highlights the chosen checker.
                                circle(img, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1); //Redraws the checker, as the highlighting (previous line of code) draws over it.
                                
                                if(selected[1] >= 12){
                                    putText(img, "K", Point(rectangles[i].x + 13, rectangles[i].y + 35), FONT_HERSHEY_COMPLEX, 1, Scalar(255,255,255), 1);
                                }

                                jumps(rectangles[i].x, rectangles[i].y, i, selected[1], bCheckers, rCheckers);
                            }
                            else{
                                clearVecInt(selected); //Clears vector selected.
                                clearVecString(stringPos);
                                setBool(jumpPerformed, false);

                                turnVal++;
                                thisTurn = (turnVal%2 == 0 ? 1 : 2);
                                updateText(img, turnVal, latestScores, latestMoves, moveStart, moveEnd); //Updates text.
                                promotionGUI(bCheckers);
                                Draw(img, startUpMain); //Draws new gamestate.

                                if(isGameWon(bCheckers, rCheckers, thisTurn)){
                                    setBool(gameEnd, true);
                                }

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
                        for(int j = 0; j < (rCheckers.size() > bCheckers.size() ? rCheckers.size() : bCheckers.size()); j++){
                            if(rCheckers[j].contains(Point(userX, userY)) && turnVal%2 == 1){ //Checks if there is a checker on the Rect, corresponding to the which players turn it is.
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
                            else if(bCheckers[j].contains(Point(userX, userY)) && turnVal%2 == 0){ //Same as for the previous section.
                                
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
        else if(gameEnd){
            winAnimation(winName, img, redWon, rectangles);
            setBool(gameEnd, false); //Stops animation
        }
    }
    else if(thisTurn == 2 && gameMode == "AI" && !gameEnd || thisTurn == 2 && gameMode == "DB" && !gameEnd){
        cout << "----- AI's turn -----" << endl;
        do{
            if(gameMode == "AI"){
                alphaBeta(boards, depth, thisTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, thisTurn, {});
                moveStart = moveSet[moveSet.size()-2];
            }
            else{
                //std::string DBmove = MovePlayer(OldBoard, playerTurn); // Database best move on current board
                string DBmove = "";

                if(/*DBmove == "no moves"*/1){
                    //std::cout << "No moves found" << std::endl;
                    alphaBeta(boards, depth, thisTurn, redPieces, blackPieces, boards, moveSet, INT_MIN, INT_MAX, blackPieces, redPieces, thisTurn, {}); //AI's move
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

            for(int i = 0; i < 64; i++){
                if(rectangles[i].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){
                    //selected.push_back(i);

                    for(int j = 0; j < rCheckers.size(); j++){
                        if(rCheckers[j].contains(Point(intPos[intPos.size()-2], intPos[intPos.size()-1]))){

                            selected.push_back(j);
                            break;
                        }
                    }

                    stringToPosConvert(moveSet[moveSet.size()-1], intPos);

                    for(int j = 0; j < bCheckers.size(); j++){
                        if(bCheckers[j].contains(Point((intPos[intPos.size()-2] + intPos[intPos.size()-4])/2, (intPos[intPos.size()-1] + intPos[intPos.size()-3])/2))){
                            bCheckers[j].x = blackGraveyardRect.x;
                            bCheckers[j].y = blackGraveyardRect.y;
                            setBool(jumpPerformed, true);
                            break;
                        }
                    }
                }
            }

            img(rectangles[selected[selected.size()-2]]) = Vec3b(0,0,255);
            circle(img, {rectangles[selected[selected.size()-2]].x + 25, rectangles[selected[selected.size()-2]].y + 25}, 20, Vec3b(14,17,175), -1);
            imshow(winName, img);

            rCheckers[selected[selected.size()-1]].x = intPos[intPos.size()-2];
            rCheckers[selected[selected.size()-1]].y = intPos[intPos.size()-1];

            boardChange(thisTurn, boards, moveSet[moveSet.size()-2], moveSet[moveSet.size()-1], redPieces, blackPieces);
            checkerBoard(boards);
            Draw(img, startUpMain);

            moveEnd = moveSet[moveSet.size()-1];

        }while(isJumpPossible(intPos[intPos.size()-2], intPos[intPos.size()-1], selected[selected.size()-1], rCheckers, bCheckers) && jumpPerformed);

        if(isGameWon(rCheckers, bCheckers, thisTurn)){
            setBool(gameEnd, true);
            setBool(redWon, true);
            Draw(img, startUpMain);
        }

        clearVecInt(selected);
        setBool(jumpPerformed, false);

        turnVal++;
        thisTurn = (turnVal%2 == 0 ? 1 : 2);
        updateText(img, turnVal, latestScores, latestMoves, moveStart, moveEnd);
        promotionGUI(rCheckers);
        Draw(img, startUpMain); //Draws new gamestate.
    }
    else if(gameMode == "AI" && gameEnd){
        winAnimation(winName, img, redWon, rectangles);
    }

    imshow(winName, img);
}

int main(){

    while(!gameEnd){

        //start:

        if(startUpMain){
            do{
                drawGameMode(img);
                imshow(winName, img);
                setMouseCallback(winName, gameModeCallBack);
                waitKey(0);
            }while(gameMode.empty());

            Draw(img, startUpMain);
            updateText(img, turnVal, latestScores, latestMoves, moveStart, moveEnd);
            imshow(winName, img);
            thisTurn = (turnVal%2 == 0 ? 1 : 2);
        }

        //Creates window, and shows image on it.
        namedWindow(winName, WINDOW_AUTOSIZE);
        setMouseCallback(winName, callBackFunc);

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
