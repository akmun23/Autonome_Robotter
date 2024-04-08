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

string images[1] = {"/home/aksel/Downloads/boards4.jpg"};

bool detectAndDrawChessboardCorners(Mat src)
{
    for (int i = 0; i < 1; i++){
        Mat img = src;
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
    int offsetx = 777;
    int offsety = 1313;
    float pixToMeters = (0.03 / sqrt(pow((corners[1].x - corners[0].x),2) + pow((corners[1].y - corners[0].y),2)));

    for(int i = 0; i <= corners.size(); i++){
        corners[i].x = (corners[i].x - offsetx)* pixToMeters;
        corners[i].y = (corners[i].y - offsety) * pixToMeters;
    } // Corners er redefined with coordinates in m instead of pixels.

    cout << "New corners:  " << endl;
    cout << corners << endl;

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

int main(int argc, char** argv )
{
    //![load]
    const char* filename = argc >=2 ? argv[1] : "/home/aksel/Downloads/boards4.jpg";

    // Loads an image
    Mat src = imread( samples::findFile( filename ), IMREAD_COLOR );

    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", filename);
        return EXIT_FAILURE;
    }
    //![load]

    //![convert_to_gray]
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    medianBlur(gray, gray, 1);
    //![reduce_noise]

    //![houghcircles]
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/50,  // change this value to detect circles with different distances to each other
                 100, 30, 20, 21 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
                 );
    //![houghcircles]


    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius+5, Scalar(0,0,0), -1, LINE_AA);
        cout << center << endl;

    }
    //![draw]

    //![display]
    namedWindow("detected circles", WINDOW_NORMAL);
    imshow("detected circles", src);
    resizeWindow("detected circles", 500, 650);
    waitKey();
    //![display]


    detectAndDrawChessboardCorners(src);

}
#endif
