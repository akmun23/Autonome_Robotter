#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <atomic>
#include <thread>

#include "checkersdatabase.h"
#include "validmoves.h"
#include "robot.h"
#include "alphabeta.h"
#include "GameFunctions.h"
#include "DrawFunctions.h"

using namespace cv;
using namespace std;

string winName = "Project GUI"; //Sets name of window being used.
string gameMode = "";

vector<string> stringPos; //Vec consisting of selected positions.
vector<int> intPos;
vector<string> latestMoves = {};

int currentChecker;
bool gameEnd = false;
bool redWon = false;
bool button = false;

std::atomic_bool robotMoving(false);

void robotMoveThread(std::vector<std::vector<std::string>>& prevBoard, int thisTurn, Robot& robot){
    robotMoving = true;

    robot.robotMove(moveSet, prevBoard, thisTurn);

    robotMoving = false;
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

int main(int argc, char* argv[]){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("Pascal");  // Change to username
    db.setPassword("Superbror22!");  // Change to password
    db.open();

    QSqlQuery query;
    while(!gameEnd){
        //start:
        if(startUpMain){
            robot.setArguments(argv);
            robot.prepForPic();
            do{
                thisTurn = 1;
                drawGameMode(img);
                imshow(winName, img);
                setMouseCallback(winName, gameModeCallBack);
                waitKey(0);
            }while(gameMode.empty());
            Draw(img, startUpMain);
            updateText(img, 0, latestScores, latestMoves, moveSet[0], moveSet[1]);
            imshow(winName, img);
            thisTurn = 1;
            robot.robotStartVision();
            boards = robot.getBoard();
            validM.setBoard(boards);
            checkerBoard(boards);
        }

        //Creates window, and shows image on it.
        namedWindow(winName, WINDOW_AUTOSIZE);
        setMouseCallback(winName, callBackFunc);

        while(true){
            callBackFunc(0, 0, 0, 0, nullptr); // Call callBackFunc without relying on mouse events
            imshow(winName, img); // Update GUI
            if(waitKey(1) == 27){ // Check for ESC key press to exit
                exit(0);
            }
        }
    }

    return 0;
}
