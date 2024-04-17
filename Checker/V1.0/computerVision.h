#ifndef COMPUTERVISION_H
#define COMPUTERVISION_H

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

double pixToMeters;
std::vector<cv::Point2f> axis;
double boardSize = 0;

std::vector<std::vector<Vec3f>> detectAndDrawCentersOfCircles(Mat& src){
    vector<Vec3f> circles;
    vector<Vec3f> colors;
    //![convert_to_gray]
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    medianBlur(gray, gray, 1);
    //![reduce_noise]

    //![houghcircles]
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/50,  // change this value to detect circles with different distances to each other
                 100, 30, 16, 32 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
                 );
    //![houghcircles]

    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        colors.push_back(src.at<Vec3b>(center));
        // circle center
        circle(src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(src, center, radius+3, Scalar(0,0,0), -1, LINE_AA);
    }
    namedWindow("detected board", WINDOW_NORMAL);
    imshow("detected board", src);
    resizeWindow("detected board", 1000, 1300);
    moveWindow("detected board",src.cols/2,100);
    waitKey();
    return {circles, colors};
}

std::vector<cv::Point2f> detectAndDrawChessboardCorners(cv::Mat src) {
    vector<Point2f> corners; // Array will be filled by the detected corners
    for (int i = 0; i < 1; i++){
        Size patternsize(7,7); // The interior number of corners in a checkers board
        Mat gray;
        cvtColor(src,gray,COLOR_BGR2GRAY);

        //CALIB_CB_FAST_CHECK saves a lot of time on images (Removed for better accuracy)
        bool patternfound = findChessboardCorners(gray, patternsize, corners, 0 +
                                                                                  CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                                                  + CALIB_CB_FILTER_QUADS);
        if(patternfound){
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                         TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS, 30, 0.1));
        } // Subpixels are also considered increasing accuracy

        drawChessboardCorners(src, patternsize, Mat(corners), patternfound); // Corners er visualized.

        // Define the offset of where the table the checkers board can be placed on starts. Also the scale of cm per pixel. These have to be defined when camera is set up.
        pixToMeters = (0.03 / sqrt(pow((corners[1].x - corners[0].x),2) + pow((corners[1].y - corners[0].y),2)));

        for(int i = 0; i <= corners.size(); i++){
            corners[i].x = (corners[i].x)* pixToMeters;
            corners[i].y = (corners[i].y) * pixToMeters;
        } // Corners er redefined with coordinates in m instead of pixels.

        // Draw the corners of the board and offset
        int exponent = 2;
        boardSize = sqrt((pow(corners[1].x - corners[0].x,exponent)) + (pow(corners[1].y - corners[0].y,exponent)));
        // The length of the individual squares of the board are calculated to calibrate the game program.
        cout << "Boardsize: " << boardSize << endl;
    }
    std::vector<cv::Point2f> axis = {corners[0], corners[6], corners[42], corners[48]};
    return axis;
}

#endif // COMPUTERVISION_H
