
#ifndef COMPUTERPOS_H
#define COMPUTERPOS_H

#pragma once

#include <vector>
#include <opencv2/opencv.hpp>




/*
    cv::Mat newImg = imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/visionTest4.jpg");

    cv::arrowedLine(newImg, newOrego/pixToMeters, xAxis/pixToMeters, cv::Scalar(0, 0, 255), 3);
    cv::arrowedLine(newImg, newOrego/pixToMeters, yAxis/pixToMeters, cv::Scalar(0, 0, 255), 3);

    cv::namedWindow("detected board", WINDOW_NORMAL);
    cv::imshow("detected board", newImg);
    cv::resizeWindow("detected board", 1000, 1300);
    cv::moveWindow("detected board",newImg.cols/2,100);
    cv::waitKey();
*/
/*
std::vector<double> yaxis1 = {0.399853, -0.0506146, -0.018515};
std::vector<double> yaxis2 = {0.399852, -0.0506224, -0.0185018};
std::vector<double> yaxis3 = {0.399851, -0.0506165, -0.0185018};
std::vector<double> xaxis1 = {-0.0889017, -0.876077, -0.0112772};
std::vector<double> xaxis2 = {-0.0888664, -0.876096, -0.01124};
std::vector<double> xaxis3 = {-0.0888984, -0.876086, -0.0112617};
std::vector<double> orego1 = {-0.290504, -0.336675, -0.0178658};
std::vector<double> orego2 = {-0.290528, -0.336664, -0.0178206};
std::vector<double> orego3 = {-0.29052, -0.33669, -0.0178003};
*/


// Finds the median of the three vectors

cv::Point2f meanPoints(std::vector<double> point1, std::vector<double> point2, std::vector<double> point3);

// Calculates the unit vectors for the x and y axis
std::vector<std::vector<double>> calcUnitVec2D(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis);

// Shifts the corners to the middle of the checker pieces instead of the inner corner
std::vector<cv::Point2f> newChessCorners(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis);

// Finds the coordinates for the circles in the given coordinate frame
std::vector<double> findCoordInFrame(std::vector<cv::Point2f> axis, cv::Point2f varpoint);


// Finds the coordinates for the three calibration circles
std::vector<cv::Point2f> calibrationCircles(std::vector<std::vector<cv::Vec3f>> circlesAndColors);

// Finds the colors of the checker pieces on the board
std::vector<cv::Vec3b> startBoard(std::vector<std::vector<double>> circleChecked, std::vector<cv::Vec3f> colors, std::vector<std::vector<std::string>>& chessBoard);

// Runs the first time the board is detected and finds the orientation of the board
std::vector<cv::Vec3b> firstLoop(std::vector<cv::Point2f>& newCorners, cv::Mat firstLoop, std::vector<std::vector<std::string>>& chessBoard, std::vector<cv::Point2f>& calibrate);

// Runs the loop that detects the checker pieces on the board
std::vector<std::string> boardLoop(cv::Vec3b black, cv::Vec3b red, std::vector<cv::Point2f> newCorners, cv::Mat img, std::vector<std::vector<std::string>>& chessBoard, int playerTurn);
#endif // COMPUTERPOS_H
