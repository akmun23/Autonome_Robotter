#include <iostream>
#include "qa.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cmath>

using namespace cv;
using namespace std;

//Code for detecting and drawing chessboard corners

// String array with images, if more than 1 picture needs to be processed.

string images[1] = {"/home/emil/blackSquaresNoBackground.jpg"};

bool detectAndDrawChessboardCorners()
{
    for (int i = 0; i < 1; i++){
        Mat img = imread(images[i]);
        /* int down_width = 800;
        int down_height = 600;
        Mat resize_down; */

        // Resizing the image to a standard scale. Variables should change depending on camera. Right now scales from Iphone 8 camera.

        //resize(img, resize_down, Size(down_width, down_height), INTER_LINEAR);


    imshow("image",img);
    moveWindow("image",40,40);

    Size patternsize(7,7); // The interior number of corners in a checkers board
    Mat gray;
    cvtColor(img,gray,COLOR_BGR2GRAY);
    vector<Point2f> corners; // Array will be filled by the detected corners

    //CALIB_CB_FAST_CHECK saves a lot of time on images (Removed for better accuracy)
    bool patternfound = findChessboardCorners(gray, patternsize, corners, 0 +
                                              CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                  + CALIB_CB_FILTER_QUADS);

    cout << "Corners:  " << corners << endl;
    cout << "Pattern: " << patternfound << endl;
    cout << "Numb of cha: " << img.channels() << endl;

    if(patternfound){
        cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                     TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS, 30, 0.1));
    } // Subpixels are also considered increasing accuracy

    drawChessboardCorners(img, patternsize, Mat(corners), patternfound); // Corners er visualized.

    namedWindow("detected board", WINDOW_NORMAL);
    imshow("detected board", img);
    resizeWindow("detected board", 1000, 1300);
    moveWindow("detected board",img.cols/2,100);

    // Define the offset of where the table the checkers board can be placed on starts. Also the scale of cm per pixel. These have to be defined when camera is set up.
    int offsetx = 155;
    int offsety = 55;
    float pixToMeters = (0.03 / sqrt(pow((corners[1].x - corners[0].x),2) + pow((corners[1].y - corners[0].y),2)));

    for(int i = 0; i <= corners.size(); i++){
        corners[i].x = (corners[i].x - offsetx)* pixToMeters;
        corners[i].y = (corners[i].y - offsety) * pixToMeters;
    } // Corners er redefined with coordinates in m instead of pixels.

    cout << "New corners:  " << corners << endl;

    float boardSize;
    int exponent = 2;
    boardSize = sqrt((pow(corners[1].x - corners[0].x,exponent)) + (pow(corners[1].y - corners[0].y,exponent)));
    // The length of the individual squares of the board are calculated to calibrate the game program.
    cout << "Boardsize: " << boardSize << endl;



    }
    waitKey(0);

    return true;

}




#if QA_MULTI_DEMO

int main( int argc, char** argv )
{
    detectAndDrawChessboardCorners();

}
#endif
