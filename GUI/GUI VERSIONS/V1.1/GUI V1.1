#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>

using namespace cv;
using namespace std;

//Nedarvet klasse og constructor
class Circle : public Rect{
    using Rect::Rect;
};

vector<Rect> rectangles; //Vector som indeholder spillepladen
vector<Circle> bCheckers; //Vector som indeholder sorte spillebrikker
vector<Circle> rCheckers; //Vector som indeholder røde spillebrikker

Mat3b canvas(500, 1000, Vec3b(255, 255, 255)); //Generer tegneflade
string winName = "Project GUI"; //Vindue navn

//callBack funktion som bliver kaldt når man klikker på et felt.
void callBackFunc(int event, int userX, int userY, int flags, void* userdata){
    if(event == EVENT_LBUTTONDOWN){ //Hvis venstre museknap trykkes på:

        //Tjekker om de valgte koordinater er indenfor et felt.
        for(int i = 0; i < 64; i++){

            if(rectangles[i].contains(Point(userX,userY))){
                system("clear");
                cout << "Blok: " << i << ". Blev trykket på." << endl;
                
                //if statement for hvilke spiller der skal vælge brik.

                //Skal undgå bug i opencv bibliotek
                if(rectangles[i].x <= canvas.cols && rectangles[i].y <= canvas.rows){
                    
                    //Tjekker om der eksisterer en brik på de valgte koordinater
                    for(int j = 0; j < 12; j++){
                        if(rCheckers[j].contains(Point(userX, userY))){
                            cout << "RØD brik, nummer: " << j << endl;
                        }
                        else if(bCheckers[j].contains(Point(userX, userY))){
                            cout << "SORT brik, nummer: " << j << endl;
                        }
                    }

                    //canvas(rectangles[i]) = Vec3b(0,0,255);
                    //skal muligvis tegne brikken igen

                }
                else{ // debugging
                    cout << "X: " << rectangles[i].x << ">" << canvas.cols << endl;
                    cout << "Y: " << rectangles[i].y << ">" << canvas.rows << endl;
                    cout << "Plads ikke inden for vindue" << endl;
                }

                updateWindow;
                break;
            }
        }
    }

    imshow(winName, canvas);
    waitKey();
}

int main(int argc, char** argv) {

    int lineNum = 0;
    int width = 50;
    int height = 50;
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    //Genererer spil pladen, bestående af 64 segmenter og spilbrikker.

    for(int i = 0; i < 64; i++){
        int x = (i%8) * 50 + boardOffSetX;
        int y = lineNum * 50 + boardOffSetY;

        rectangles.push_back(Rect(x,y,width,height));

        if(i%2){
            if(lineNum%2){
                canvas(rectangles[i]) = Vec3b(90,145,201);
            }

            else{
                canvas(rectangles[i]) = Vec3b(33,67,101);

                if(lineNum < 3){
                    bCheckers.push_back(Circle(x, y, 30, 30));
                    circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                }

                else if(lineNum > 4){
                    rCheckers.push_back(Circle(x, y, 30, 30));
                    circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                }
            }
        }

        else{
            if(lineNum%2){
                //angiver felts mørkebrune farve
                canvas(rectangles[i]) = Vec3b(33,67,101);

                if(lineNum < 3){
                    bCheckers.push_back(Circle(x, y, 30, 30));
                    circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(0,0,0), -1);
                }

                else if(lineNum > 4){
                    rCheckers.push_back(Circle(x, y, 30, 30));
                    circle(canvas, {rectangles[i].x + 25, rectangles[i].y + 25}, 20, Vec3b(14,17,175), -1);
                }
            }
            else{
                canvas(rectangles[i]) = Vec3b(90,145,201);
            }
        }

        (i%8 == 7) ? lineNum++ : lineNum;
    }

    for(int i = 0; i < 8; i++){
        putText(canvas, alphabetArr[i], Point({(i * 50) + boardOffSetX + 12}, {boardOffSetY - 5}), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
        putText(canvas, numArr[i], Point({boardOffSetX - 30}, {(i * 50) + boardOffSetY + 35}), FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,0));
    }

    namedWindow(winName, WINDOW_AUTOSIZE);
    setMouseCallback(winName, callBackFunc);
    imshow(winName, canvas);
    waitKey();

    return 0;
}
