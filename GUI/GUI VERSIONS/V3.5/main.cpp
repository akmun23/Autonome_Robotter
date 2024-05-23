#include <opencv4/opencv2/highgui.hpp>
#include "DrawFunctions.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("CheckersDatabase");
    db.setUserName("IndsætBrugernavn");  // Change to username
    db.setPassword("IndsætPassword!");  // Change to password
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
