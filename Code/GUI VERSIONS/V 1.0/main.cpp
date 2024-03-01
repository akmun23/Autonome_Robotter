#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat3b canvas;

Rect button;

int main(int argc, char** argv) {

    //Generates drawing surface.
    Mat image(600, 600, CV_8UC3, Scalar(255, 255, 255));

    //Generates 64 boards pieces.

    int lineNum = 1;
    int chckSX = 50;
    int chckSY = 50;
    int boardOffSetX = 100;
    int boardOffSetY = 25;

    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 8; i++){
            if(i%2 == 0){
                rectangle(image, {chckSX*i + boardOffSetX, boardOffSetY + chckSY*lineNum}, {chckSX+chckSX*i + boardOffSetX, chckSY + (boardOffSetY + chckSY*lineNum)}, Scalar(33,67,101), -1);
            }

            else{
                rectangle(image, {chckSX*i + boardOffSetX, boardOffSetY + chckSY*lineNum}, {chckSX+chckSX*i + boardOffSetX, chckSY + (boardOffSetY + chckSY*lineNum)}, Scalar(90,145,201), -1);
            }
        }

        lineNum++;

        for(int i = 0; i < 8; i++){
            if(i%2 == 0){
                rectangle(image, {chckSX*i + boardOffSetX, boardOffSetY + chckSY*lineNum}, {chckSX+chckSX*i + boardOffSetX, chckSY + (boardOffSetY + chckSY*lineNum)}, Scalar(90,145,201), -1);
            }

            else{
                rectangle(image, {chckSX*i + boardOffSetX, boardOffSetY + chckSY*lineNum}, {chckSX+chckSX*i + boardOffSetX, chckSY + (boardOffSetY + chckSY*lineNum)}, Scalar(33,67,101), -1);
            }
        }

        lineNum++;
    }

    string winName = "Project GUI";
    imshow(winName, image);
    waitKey();

    return 0;
}
