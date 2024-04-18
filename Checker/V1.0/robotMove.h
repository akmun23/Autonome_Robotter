#pragma once

#include "opencv2/core/types.hpp"
#ifndef ROBOTMOVE_H
#define ROBOTMOVE_H


#include "matrix.h"
#include "AtmegaCom.h"
#include "computerVision.h"
#include <vector>
#include <string>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;







// Function to set the values of a matrix from the Matrix class
void setMatrixValues(Matrix& m, std::vector<double> v);

// Function to set up robot and make a plane parallel with table
// Should no longer be used


std::vector<std::vector<double>> robotStart();


// Function to calculate the transformation matrix for the robot to the chessboard
std::vector<std::vector<double>> robotStartVision(std::vector<cv::Point2f> newCorners, std::vector<cv::Point2f> calibrate, double factor, double pixToMeters);


// Function to make the robot promote a piece by placiing a previously captured piece ontop of the piece to be promoted
void checkerJump(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp, int playerTurn, double factor, int piecesLeft);

void promotePiece(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp, std::vector<std::vector<std::string>> boards, int playerTurn, double factor, int piecesLeft);

//Function to move the robot
bool robotMove(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp, std::vector<std::vector<std::string>> boards, int playerTurn){
    double factor = 0.03;
    double xcord = 0;
    double ycord = 0;
    double xcord2 = 0;
    double ycord2 = 0;
    double speed = 2;
    double speed2 = 1;
    double acc = 0.5;
    double acc2 = 0.2;
    double hover = (startUp[2][0] - startUp[2][1]) * 2;

void simpleMove(double x, double y, double z);

#endif // ROBOTMOVE_H
