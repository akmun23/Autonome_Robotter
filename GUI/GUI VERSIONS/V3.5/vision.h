#pragma once
#ifndef VISION_H
#define VISION_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include "boardUpdate.h"

class Vision
{
    cv::Mat _src = cv::imread("/home/aksel/Downloads/picture1.jpg");
    std::vector<cv::Point2f> _newCorners ={{0,0}, {0,0}, {0,0}};
    double _pixToMeters;
    double _boardSize;
    std::vector<std::vector<std::string>> _chessBoard;
    cv::Mat _firstLoop;
    std::vector<cv::Vec3b> _colours;
    char** _argv;
    cv::Vec3b _black;
    cv::Vec3b _red;
    std::vector<cv::Point2f> _axis;
    std::vector<cv::Vec3f> _circles;
    std::vector<cv::Vec3f> _colors;
    cv::Point2f _greenFunc;
    cv::Point2f _yellowFunc;
    cv::Point2f _magentaFunc;
    std::vector<std::vector<double>> _circleChecked = {};
    std::vector<std::vector<std::string>> _boards;
    std::vector<double> _unit1;
    std::vector<double> _unit2;

public:
    Vision();

    Vision(char** argv);

    void detectAndDrawCentersOfCircles();

    void detectAndDrawChessboardCorners();

    // Calculates the unit vectors for the x and y axis
    virtual void calcUnitVec2D(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis);

    // Shifts the corners to the middle of the checker pieces instead of the inner corner
    void newChessCorners(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis);

    // Finds the coordinates for the circles in the given coordinate frame
    void findCoordInFrame(cv::Point2f varpoint, int& iterator);

    // Finds the coordinates for the three calibration circles
    void calibrationCircles();

    // Finds the colors of the checker pieces on the board
    void startBoard();

    // Opens camera and takes picture after 1 second
    void cameraFeed();

    // Runs the first time the board is detected and finds the orientation of the board
    void firstLoop();

    // Runs the loop that detects the checker pieces on the board
    std::vector<std::string> boardLoop(std::vector<std::vector<std::string>> chessBoard, int playerTurn);

    std::vector<cv::Point2f> getCalibrate();

    double getPixToMeters();

    double getBoardsize();

    std::vector<cv::Point2f> getNewCorners();

    std::vector<std::vector<std::string>> getBoard();

    void setArguments(char** argv);
};

#endif // VISION_H
