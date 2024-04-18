#pragma once


#ifndef COMPUTERVISION_H
#define COMPUTERVISION_H


#include <vector>

#include <iostream>
#include "qa.hpp"
#include "boardUpdate.h"

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cmath>



using namespace cv;
using namespace std;


std::vector<std::vector<Vec3f>> detectAndDrawCentersOfCircles(Mat& src);

std::vector<cv::Point2f> detectAndDrawChessboardCorners(cv::Mat src);

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
std::vector<cv::Vec3b> firstLoop(std::vector<cv::Point2f>& newCorners, cv::Mat& firstLoop, std::vector<std::vector<std::string>>& chessBoard, std::vector<cv::Point2f>& calibrate, double& pixToMeters, double& boardSize);

// Runs the loop that detects the checker pieces on the board
std::vector<std::string> boardLoop(cv::Vec3b black, cv::Vec3b red, std::vector<cv::Point2f> newCorners, cv::Mat img, std::vector<std::vector<std::string>> chessBoard, int playerTurn, double pixToMeters);

cv::Mat cameraFeed(char** argv);

#endif // COMPUTERVISION_H
