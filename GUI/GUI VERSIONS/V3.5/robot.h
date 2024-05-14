#pragma once
#ifndef ROBOT_H
#define ROBOT_H

#include "vision.h"
#include "matrix.h"
#include "AtmegaCom.h"

#include <vector>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace ur_rtde;

class Robot : public Vision, public Matrix, public AtmegaCom
{
    RTDEControlInterface rtde_control = RTDEControlInterface("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);
    RTDEReceiveInterface rtde_receive = RTDEReceiveInterface("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);

    /*
    std::vector<double> _yaxis1 = {0.4076880, -0.0492708, 0.125247};
    std::vector<double> _yaxis2 = {0.4077010, -0.0492651, 0.125247};
    std::vector<double> _yaxis3 = {0.4076790, -0.0492790, 0.12528};
    std::vector<double> _xaxis1 = {-0.0642869, -0.889975, 0.126027};
    std::vector<double> _xaxis2 = {-0.0642557, -0.889982, 0.126268};
    std::vector<double> _xaxis3 = {-0.0642705, -0.889994, 0.126356};
    std::vector<double> _orego1 = {-0.294341, -0.338338, 0.12538};
    std::vector<double> _orego2 = {-0.294350, -0.338339, 0.125314};
    std::vector<double> _orego3 = {-0.294359, -0.338352, 0.125344};
    */

    std::vector<double> _orego1 = {-0.30305, -0.43205, 0.12538};
    std::vector<double> _orego2 = {-0.30305, -0.43205, 0.12538};
    std::vector<double> _orego3 = {-0.30305, -0.43205, 0.12538};

    std::vector<double> _xaxis1 = {-0.02675, -0.98675, 0.126027};
    std::vector<double> _xaxis2 = {-0.02675, -0.98675, 0.126027};
    std::vector<double> _xaxis3 = {-0.02675, -0.98675, 0.126027};

    std::vector<double> _yaxis1 = {0.4987, -0.00960, 0.125247};
    std::vector<double> _yaxis2 = {0.4987, -0.00960, 0.125247};
    std::vector<double> _yaxis3 = {0.4987, -0.00960, 0.125247};

    std::vector<cv::Point2f> _newCorners;
    std::vector<cv::Point2f> _calibrate;
    double _factor;
    double _pixToMeters;
    double _piece = 0;
    double _chess = 0;
    double _table = 0;
    double _hover = 0;
    Matrix _CamToChess = Matrix(4,4);
    Matrix _robot = Matrix(4,4);
    std::vector<std::string> _moveSet;
    int _playerTurn;
    std::vector<double> _unit1;
    std::vector<double> _unit2;



public:
    Robot();

    // Finds the median of the three vectors
    cv::Point2f meanPoints(std::vector<double> point1, std::vector<double> point2, std::vector<double> point3);

    // Function to calculate the transformation matrix for the robot to the chessboard
    void robotStartVision();

    // Function to make the robot promote a piece by placiing a previously captured piece ontop of the piece to be promoted
    void checkerJump(int piecesLeft);

    void promotePiece(std::vector<std::vector<std::string>> boards, int piecesLeft);

    //Function to move the robot
    bool robotMove(std::vector<std::string> moveSet, std::vector<std::vector<std::string>> boards, int playerTurn);

    void prepForPic();

    void calcUnitVec2D(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis) override;

};

#endif // ROBOT_H
