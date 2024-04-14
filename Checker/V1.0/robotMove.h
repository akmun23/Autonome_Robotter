#ifndef ROBOTMOVE_H
#define ROBOTMOVE_H

#include "AtmegaCom.h"
#include "computerPos.h"
#include "matrix.h"
#include <vector>
#include <string>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;

RTDEControlInterface rtde_control("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);
RTDEReceiveInterface rtde_receive("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);

// Function to set the values of a matrix from the Matrix class
void setMatrixValues(Matrix& m, std::vector<double> v){
    for(int r=0; r<m.getRows(); r++){
        for(int c=0; c<m.getCols(); c++){
            m.at(r,c) = v[r*m.getCols() + c];
        }
    }
}

// Function to set up robot and make a plane parallel with table
// Should no longer be used

/*
std::vector<std::vector<double>> robotStart() {
    std::vector<double> rotMatrix;
    std::vector<double> vec1;
    std::vector<double> vec2;
    std::vector<double> vec3;
    std::vector<double> unit1;
    std::vector<double> unit2;
    std::vector<double> unit3;

    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, 0}, 1, 0.1);
    std::vector<double> target = rtde_receive.getActualTCPPose();

    rtde_control.speedL({0,0,-0.01, 0, 0, 0});

    while(rtde_receive.getActualTCPForce()[2] < 30){
        //std::cout << rtde_receive.getActualTCPForce()[2] << std::endl;
    }
        //std::cout << rtde_receive.getActualTCPForce()[2] << std::endl;
    double table = rtde_receive.getActualTCPPose()[2]+0.0015;
    rtde_control.speedStop();

    rtde_control.teachMode();
    std::cin.get();
    std::vector<double> boardPlane1 = rtde_receive.getActualTCPPose();
    std::cout << boardPlane1[0] << " " << boardPlane1[1] << " " << boardPlane1[2] << std::endl;
    std::cin.get();
    std::vector<double> boardPlane2 = rtde_receive.getActualTCPPose();
    std::cout << boardPlane2[0] << " " << boardPlane2[1] << " " << boardPlane2[2] << std::endl;
    std::cin.get();
    std::vector<double> boardPlane3 = rtde_receive.getActualTCPPose();
    std::cout << boardPlane3[0] << " " << boardPlane3[1] << " " << boardPlane3[2] << std::endl;
    rtde_control.endTeachMode();

    std::vector<double> boardPlane1 = {-0.0842739, -0.305759, table};
    std::vector<double> boardPlane2 =  {0.123559, -0.814958, table};
    std::vector<double> boardPlane3 =  {0.378329, -0.113615, table};

    vec1.push_back(boardPlane2[0] - boardPlane1[0]);
    vec1.push_back(boardPlane2[1] - boardPlane1[1]);
    vec1.push_back(boardPlane2[2] - boardPlane1[2]);

    vec2.push_back(boardPlane3[0] - boardPlane1[0]);
    vec2.push_back(boardPlane3[1] - boardPlane1[1]);
    vec2.push_back(boardPlane3[2] - boardPlane1[2]);

    vec3.push_back(vec1[1]*vec2[2] - vec1[2]*vec2[1]);
    vec3.push_back(vec1[2]*vec2[0] - vec1[0]*vec2[2]);
    vec3.push_back(vec1[0]*vec2[1] - vec1[1]*vec2[0]);

    unit1.push_back(vec1[0]/sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)));
    unit1.push_back(vec1[1]/sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)));
    unit1.push_back(vec1[2]/sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2)));

    unit2.push_back(vec2[0]/sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2)));
    unit2.push_back(vec2[1]/sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2)));
    unit2.push_back(vec2[2]/sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2)));

    unit3.push_back(vec3[0]/sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2)));
    unit3.push_back(vec3[1]/sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2)));
    unit3.push_back(vec3[2]/sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2)));

    rotMatrix = {unit1[0], unit1[1], unit1[2], unit2[0], unit2[1], unit2[2], unit3[0], unit3[1], unit3[2]};

    rtde_control.moveL(target, 1, 0.1);

    return {boardPlane1, rotMatrix};
}
*/

// Function to calculate the transformation matrix for the robot to the chessboard
std::vector<std::vector<double>> robotStartVision(std::vector<cv::Point2f> newCorners, std::vector<cv::Point2f> calibrate, double factor){
    // Defines the frame for the robot
    cv::Point2f xaxis = meanPoints(xaxis1, xaxis2, xaxis3);
    cv::Point2f yaxis = meanPoints(yaxis1, yaxis2, yaxis3);
    cv::Point2f orego = meanPoints(orego1, orego2, orego3);

    // Defines the frame for the camera
    cv::Point2f oregoPicture = Point2f(calibrate[0].x*pixToMeters, calibrate[0].y*pixToMeters);
    cv::Point2f xaxisPicture = Point2f(calibrate[1].x*pixToMeters, calibrate[1].y*pixToMeters);
    cv::Point2f yaxisPicture = Point2f(calibrate[2].x*pixToMeters, calibrate[2].y*pixToMeters);

    std::vector<std::vector<double>> unitVecRobot =  calcUnitVec2D(yaxis, orego, xaxis);
    std::vector<std::vector<double>> unitVecCamera = calcUnitVec2D(yaxisPicture, oregoPicture, xaxisPicture);
    std::vector<std::vector<double>> unitVecChess =  calcUnitVec2D(newCorners[0], newCorners[1], newCorners[2]);

    // Makes a transformation matrix for the robot
    Matrix Robot(4,4);
    setMatrixValues(Robot, {unitVecRobot[0][0], unitVecRobot[1][0], 0, orego.x, unitVecRobot[0][1], unitVecRobot[1][1], 0, orego.y, 0, 0, 1, 0, 0, 0, 0, 1});

    // Makes a transformation matrix for the camera
    Matrix Camera(4, 4);
    setMatrixValues(Camera, {unitVecCamera[0][0], unitVecCamera[1][0], 0, 0, unitVecCamera[0][1], unitVecCamera[1][1], 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});

    // Makes a transformation matrix for the chess board
    Matrix Chess(4, 4);
    setMatrixValues(Chess, {unitVecChess[0][0], unitVecChess[1][0], 0, newCorners[1].x-oregoPicture.x, unitVecChess[0][1], unitVecChess[1][1], 0, newCorners[1].y-oregoPicture.y, 0, 0, 1, 0, 0, 0, 0, 1});

    // Calculates the transformation matrix from the camera to the chessboard
    Matrix CamToChess = Camera*Chess;

    // Makes a transformation matrix for a point on the chessboard
    Matrix checker(4, 4);
    setMatrixValues(checker, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});

    // Calculates the transformation matrix for the peice in the camera frame
    Matrix pieceLocation = CamToChess*checker;

    // Makes a translation matrix for the checker piece
    Matrix Translation(4, 1);
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , pieceLocation(2,3), 1});

    // Calculates the transformation matrix for the robot to the checker piece
    Matrix RobotToChesspieceTransformation = Robot*Translation;

    // Finds the height of a piece on the chessboard
    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, 0}, 1, 0.1);
    std::vector<double> target = rtde_receive.getActualTCPPose();
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,3), RobotToChesspieceTransformation.at(1,3), target[2], target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    target = rtde_receive.getActualTCPPose();
    double piece = target[2]+0.0015;
    rtde_control.speedStop();

    // Moves to standard position
    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, 0}, 2, 0.5);

    // Sets up to move to middle of chess board
    setMatrixValues(checker, {1, 0, 0, (3.5*factor), 0, 1, 0, (3.5*factor), 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , pieceLocation(2,3), 1});
    RobotToChesspieceTransformation = Robot*Translation;

    // Finds heigh of chessboard on table
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,3), RobotToChesspieceTransformation.at(1,3), piece, target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    double chess = rtde_receive.getActualTCPPose()[2]+0.0015;
    rtde_control.speedStop();

    // Sets up to move to graveyard
    setMatrixValues(checker, {1, 0, 0, (1*factor), 0, 1, 0, (-3*factor), 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , pieceLocation(2,3), 1});
    RobotToChesspieceTransformation = Robot*Translation;

    // Finds height of graveyard on table
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,3), RobotToChesspieceTransformation.at(1,3), piece, target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    double table = rtde_receive.getActualTCPPose()[2]+0.0015;
    rtde_control.speedStop();

    std::vector<double> rotMat = {RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(1,0), RobotToChesspieceTransformation.at(2,0), RobotToChesspieceTransformation.at(0,1), RobotToChesspieceTransformation.at(1,1), RobotToChesspieceTransformation.at(2,1), RobotToChesspieceTransformation.at(0,2), RobotToChesspieceTransformation.at(1,2), RobotToChesspieceTransformation.at(2,2)};
    return {target, rotMat, {piece, chess, table}};
}

// Function to make the robot promote a piece by placiing a previously captured piece ontop of the piece to be promoted
void checkerJump(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp, int playerTurn, double factor, int piecesLeft){
    // Calculate the position of the piece to be promoted
    int column = moveSet[0][0] - (moveSet[0][0] - moveSet[1][0])/2;
    column = column - 'a';
    int row = moveSet[0][1] - (moveSet[0][1] - moveSet[1][1])/2;
    row = row - '1';

    // Set up the robot
    std::vector<double> boardPlane = startUp[0];
    std::vector<double> rotMatrix = startUp[1];

    // Calculate the coords of the piece to be promoted
    double xcord = rotMatrix[0]*column*factor + rotMatrix[3]*row*factor + rotMatrix[6]*0*factor + boardPlane[0];
    double ycord = rotMatrix[1]*column*factor + rotMatrix[4]*row*factor + rotMatrix[7]*0*factor + boardPlane[1];
    double hover = startUp[2][0] - startUp[2][1];

    piecesLeft = (12 - piecesLeft) * hover;

    double offset = 0.005;

    std::vector<double> target = rtde_receive.getActualTCPPose();

    rtde_control.moveL({xcord, ycord, startUp[2][0] + hover, target[3], target[4], target[5]}, 1,   0.2);
    rtde_control.moveL({xcord, ycord, startUp[2][1],         target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('6');
    rtde_control.moveL({xcord, ycord, startUp[2][0] + hover + piecesLeft, target[3], target[4], target[5]}, 1,   0.2);

    int gravex;
    if(playerTurn == 1){
        gravex = 1;
    } else {
        gravex = 7;
    }

    int gravey = -3;

    double xcord2 = rotMatrix[0] * gravex * factor + rotMatrix[3] * gravey * factor + rotMatrix[6] * 0 * factor + boardPlane[0];
    double ycord2 = rotMatrix[1] * gravex * factor + rotMatrix[4] * gravey * factor + rotMatrix[7] * 0 * factor + boardPlane[1];

    rtde_control.moveL({xcord2 + offset, ycord2 + offset, startUp[2][2] + hover + piecesLeft, target[3], target[4], target[5]}, 1, 0.2);

    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    double gravez = rtde_receive.getActualTCPPose()[2]+0.0005;
    rtde_control.speedStop();

    rtde_control.moveL({xcord2 + offset, ycord2 + offset, gravez + offset, target[3], target[4], target[5]}, 1,   0.2);
    rtde_control.moveL({xcord2,          ycord2,          gravez + offset, target[3], target[4], target[5]}, 1,   0.2);
    rtde_control.moveL({xcord2,          ycord2,          gravez + 0.001,  target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('8');
    rtde_control.moveL({xcord2,          ycord2,          target[2],       target[3], target[4], target[5]}, 1,   0.2);
}

void promotePiece(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp, std::vector<std::vector<std::string>> boards, int playerTurn, double factor, int piecesLeft){
    std::vector<double> boardPlane = startUp[0];
    std::vector<double> rotMatrix = startUp[1];

    char column = moveSet[1][0];
    column = column - 'a';
    int row = moveSet[1][1] - '1';

    double xcord = rotMatrix[0] * column * factor + rotMatrix[3] * row*factor + rotMatrix[6] * 0 * factor + boardPlane[0];
    double ycord = rotMatrix[1] * column * factor + rotMatrix[4] * row*factor + rotMatrix[7] * 0 * factor + boardPlane[1];
    double hover = startUp[2][0] - startUp[2][1];
    piecesLeft = (12 - piecesLeft) * hover;

    double offset = 0.005;

    std::vector<double> target = rtde_receive.getActualTCPPose();

    int gravex;
    if(playerTurn == 1){
        gravex = 7;
    } else {
        gravex = 1;
    }

    int gravey = -3;
    double xcord2 = rotMatrix[0] * gravex*factor + rotMatrix[3] * gravey * factor + rotMatrix[6] * 0 * factor + boardPlane[0];
    double ycord2 = rotMatrix[1] * gravex*factor + rotMatrix[4] * gravey * factor + rotMatrix[7] * 0 * factor + boardPlane[1];

    rtde_control.moveL({xcord2 + offset, ycord2 + offset, startUp[2][0],                      target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord2 + offset, ycord2 + offset, startUp[2][2] + hover + piecesLeft, target[3], target[4], target[5]}, 1, 0.2);
    atmegaCom('6');
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){
        //std::cout << rtde_receive.getActualTCPForce()[2] << std::endl;
    }
    double gravez = rtde_receive.getActualTCPPose()[2]+0.0005;
    rtde_control.speedStop();

    rtde_control.moveL({xcord2 + offset, ycord2 + offset, gravez + hover, target[3], target[4], target[5]}, 1, 0.2);
    atmegaCom('8');
    rtde_control.moveL({xcord2, ycord2, gravez + hover,             target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord2, ycord2, gravez - hover,             target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('6');
    rtde_control.moveL({xcord2, ycord2, startUp[2][0],              target[3], target[4], target[5]}, 1, 0.2);

    rtde_control.moveL({xcord,  ycord,  startUp[2][0],              target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord,  ycord,  startUp[2][0] - (hover/2),  target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('8');
    rtde_control.moveL({xcord, ycord, startUp[2][0], target[3], target[4], target[5]}, 1, 0.2);
}

//Function to move the robot
bool robotMove(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp, std::vector<std::vector<std::string>> boards, int playerTurn){
    double factor = 0.03;
    double xcord = 0;
    double ycord = 0;
    double zcord = 0;
    double xcord2 = 0;
    double ycord2 = 0;
    double zcord2 = 0;
    double speed = 2;
    double speed2 = 1;
    double acc = 0.5;
    double acc2 = 0.2;
    double hover = startUp[2][0] - startUp[2][1];

    std::vector<double> boardPlane = startUp[0];
    std::vector<double> rotMatrix = startUp[1];

    char column = moveSet[0][0]; //Starting column
    column = column - 'a';
    int row = moveSet[0][1] - '1'; //Starting row

    char column2 = moveSet[1][0]; //Ending column
    column2 = column2 - 'a';
    int row2 = moveSet[1][1] - '1'; //Ending row

    xcord  = rotMatrix[0] * column  * factor + rotMatrix[3] * row  * factor + rotMatrix[6] * 0 * factor + boardPlane[0];
    ycord  = rotMatrix[1] * column  * factor + rotMatrix[4] * row  * factor + rotMatrix[7] * 0 * factor + boardPlane[1];

    xcord2 = rotMatrix[0] * column2 * factor + rotMatrix[3] * row2 * factor + rotMatrix[6] * 0 * factor + boardPlane[0];
    ycord2 = rotMatrix[1] * column2 * factor + rotMatrix[4] * row2 * factor + rotMatrix[7] * 0 * factor + boardPlane[1];

    std::vector<double> target = rtde_receive.getActualTCPPose();

    rtde_control.moveL({xcord,  ycord,  startUp[2][0] + hover, target[3], target[4], target[5]}, speed,  acc);
    rtde_control.moveL({xcord,  ycord,  startUp[2][1],         target[3], target[4], target[5]}, speed2, acc2);
    atmegaCom('6');
    rtde_control.moveL({xcord,  ycord,  startUp[2][0] + hover, target[3], target[4], target[5]}, speed,  acc);
    rtde_control.moveL({xcord2, ycord2, startUp[2][0] + hover, target[3], target[4], target[5]}, speed,  acc);
    rtde_control.moveL({xcord2, ycord2, startUp[2][1],         target[3], target[4], target[5]}, speed2, acc2);
    atmegaCom('8');
    rtde_control.moveL({xcord2, ycord2, startUp[2][0] + hover, target[3], target[4], target[5]}, speed,  acc);

    // Remove the jumped piece
    if(moveSet[0][0] - moveSet[1][0] == 2 || moveSet[0][0] - moveSet[1][0] == -2){
        double piecesLeft = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(playerTurn == 1){
                    if(boards[i][j] == "B "){
                        piecesLeft++;
                    } else if(boards[i][j] == "BK"){
                        piecesLeft--;
                    }
                } else {
                    if(boards[i][j] == "R "){
                        piecesLeft++;
                    } else if(boards[i][j] == "RK"){
                        piecesLeft--;
                    }
                }
            }
        }
        checkerJump({moveSet[0], moveSet[1]}, startUp, playerTurn, factor, piecesLeft);
    }

    // Promotes piece
    if(((playerTurn == 1) && (moveSet[1][0] == 'h') && (boards[column][row] == "B ")) || ((playerTurn == 2) && (moveSet[1][0] == 'a') && (boards[column][row] == "R "))){
        double piecesLeft = 0;
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(playerTurn == 1){
                    if(boards[i][j] == "B "){
                        piecesLeft++;
                    } else if(boards[i][j] == "BK"){
                        piecesLeft--;
                    }
                } else {
                    if(boards[i][j] == "R "){
                        piecesLeft++;
                    } else if(boards[i][j] == "RK"){
                        piecesLeft--;
                    }
                }
            }
        }
        promotePiece({moveSet[0], moveSet[1]}, startUp, boards, playerTurn, factor, piecesLeft);
    }

    rtde_control.moveL(target, 1, hover);

    return true;
}

void simpleMove(double x, double y, double z){
    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, 0}, 1, 0.1);
    std::vector<double> target = rtde_receive.getActualTCPPose();
    rtde_control.moveL({x, y, z, target[3], target[4], target[5]}, 0.5, 0.05);
}

#endif // ROBOTMOVE_H
