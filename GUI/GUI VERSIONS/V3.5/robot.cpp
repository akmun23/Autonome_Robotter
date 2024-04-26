#include "robot.h"

Robot::Robot(){}

// Function to set the values of a matrix from the Matrix class
void Robot::setMatrixValues(Matrix& m, std::vector<double> v){
    for(int r=0; r<m.getRows(); r++){
        for(int c=0; c<m.getCols(); c++){
            m.at(r,c) = v[r*m.getCols() + c];
        }
    }
}

// Calculates the unit vectors for the x and y axis
void Robot::calcUnitVec2D(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis){
    // Calculates the vectors for the x and y axis
    std::vector<double> vec1 = {xaxis.x - orego.x, xaxis.y - orego.y};
    std::vector<double> vec2 = {yaxis.x - orego.x, yaxis.y - orego.y};

    // Calculates the length of the vectors
    double length1 = sqrt(pow(vec1[0], 2) + pow(vec1[1], 2));
    double length2 = sqrt(pow(vec2[0], 2) + pow(vec2[1], 2));

    // Calculates the unit vectors for the x and y axis
    _unit1 = {(vec1[0] / length1), (vec1[1] / length1)};
    _unit2 = {(vec2[0] / length2), (vec2[1] / length2)};
}

// Finds the median of the three vectors
cv::Point2f Robot::meanPoints(std::vector<double> point1, std::vector<double> point2, std::vector<double> point3){
    double x = (point1[0] + point2[0] + point3[0]) / 3;
    double y = (point1[1] + point2[1] + point3[1]) / 3;

    return cv::Point2f(x, y);
}

// Function to calculate the transformation matrix for the robot to the chessboard
void Robot::robotStartVision(){
    // Starts the vision system
    firstLoop();

    // Gets the values from the vision system
    _newCorners = getNewCorners();
    _calibrate = getCalibrate();
    _factor = getBoardsize();
    _pixToMeters = getPixToMeters();

    // Defines the frame for the robot
    cv::Point2f xaxis = meanPoints(_xaxis1, _xaxis2, _xaxis3);
    cv::Point2f yaxis = meanPoints(_yaxis1, _yaxis2, _yaxis3);
    cv::Point2f orego = meanPoints(_orego1, _orego2, _orego3);

    // Defines the frame for the camera
    cv::Point2f oregoPicture = cv::Point2f(_calibrate[0].x*_pixToMeters, _calibrate[0].y*_pixToMeters);
    cv::Point2f xaxisPicture = cv::Point2f(_calibrate[2].x*_pixToMeters, _calibrate[2].y*_pixToMeters);
    cv::Point2f yaxisPicture = cv::Point2f(_calibrate[1].x*_pixToMeters, _calibrate[1].y*_pixToMeters);

    calcUnitVec2D(yaxis, orego, xaxis);
    // Makes a transformation matrix for the robot
    setMatrixValues(_robot, {_unit1[0], _unit2[0], 0, orego.x, _unit1[1], _unit2[1], 0, orego.y, 0, 0, 1, 0, 0, 0, 0, 1});

    calcUnitVec2D(yaxisPicture, oregoPicture, xaxisPicture);
    // Makes a transformation matrix for the camera
    Matrix Camera(4, 4);
    setMatrixValues(Camera, {_unit1[0], _unit2[0], 0, 0, _unit1[1], _unit2[1], 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});

    calcUnitVec2D(_newCorners[0], _newCorners[1], _newCorners[2]);
    // Makes a transformation matrix for the chess board
    Matrix Chess(4, 4);
    setMatrixValues(Chess, {_unit1[0], _unit2[0], 0, _newCorners[1].x-oregoPicture.x, _unit1[1], _unit2[1], 0, _newCorners[1].y-oregoPicture.y, 0, 0, 1, 0, 0, 0, 0, 1});

    // Calculates the transformation matrix from the camera to the chessboard
    _CamToChess = Camera*Chess;

    // Makes a transformation matrix for a point on the chessboard
    Matrix checker(4, 4);
    setMatrixValues(checker, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1});

    // Calculates the transformation matrix for the peice in the camera frame
    Matrix pieceLocation = _CamToChess*checker;

    // Makes a translation matrix for the checker piece
    Matrix Translation(4, 1);
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , pieceLocation(2,3), 1});

    // Calculates the transformation matrix for the robot to the checker piece
    Matrix RobotToChesspieceTransformation = _robot*Translation;

    atmegaCom('6');
    // Finds the height of a piece on the chessboard
    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, pieceLocation.at(2,2)}, 2, 0.5);
    std::vector<double> target = rtde_receive.getActualTCPPose();
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(0,1), target[2], target[3], target[4], target[5]}, 1, 0.2);

    rtde_control.speedL({0, 0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){   }
    target = rtde_receive.getActualTCPPose();
    _piece = target[2]+0.0015;
    rtde_control.speedStop();

    // Moves robot above the found piece
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(0,1), _piece+0.05, target[3], target[4], target[5]}, 1, 0.2);

    // Sets up to move to middle of chess board
    setMatrixValues(checker, {1, 0, 0, (3.5*_factor), 0, 1, 0, (3.5*_factor), 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = _CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , pieceLocation(2,3), 1});
    RobotToChesspieceTransformation = _robot*Translation;

    // Finds heigh of chessboard on table
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(0,1), _piece+0.05, target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    _chess = rtde_receive.getActualTCPPose()[2]+0.0015;
    rtde_control.speedStop();
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(0,1), _piece+0.05, target[3], target[4], target[5]}, 1, 0.2);

    // Sets up to move to graveyard
    setMatrixValues(checker, {1, 0, 0, (1*_factor), 0, 1, 0, (-4*_factor), 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = _CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3) , pieceLocation(2,3), 1});
    RobotToChesspieceTransformation = _robot*Translation;

    // Finds height of graveyard on table
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(0,1), _piece+0.05, target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    _table = rtde_receive.getActualTCPPose()[2]+0.0015;
    rtde_control.speedStop();
    rtde_control.moveL({RobotToChesspieceTransformation.at(0,0), RobotToChesspieceTransformation.at(0,1), _piece+0.05, target[3], target[4], target[5]}, 1, 0.2);

    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, pieceLocation.at(2,2)}, 2, 0.5);
    atmegaCom('8');

    _hover = (_piece - _chess) * 2;
}

// Function to make the robot promote a piece by placiing a previously captured piece ontop of the piece to be promoted
void Robot::checkerJump(int piecesLeft){
    // Calculate the position of the piece to be promoted
    int column = _moveSet[0][0] - (_moveSet[0][0] - _moveSet[1][0])/2;
    column = column - 'a';
    int row = _moveSet[0][1] - (_moveSet[0][1] - _moveSet[1][1])/2;
    row = 7 - (row - '1');

    // Calculate the coords of the piece that was jumped
    Matrix checker(4, 4);
    setMatrixValues(checker, {1, 0, 0, column*_factor, 0, 1, 0, row*_factor, 0, 0, 1, 0, 0, 0, 0, 1});

    Matrix pieceLocation = _CamToChess*checker;

    Matrix Translation(4, 1);
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3), pieceLocation(2,3), 1});

    Matrix location = _robot*Translation;
    double xcord = location.at(0,0);
    double ycord = location.at(1,0);

    piecesLeft = (12 - piecesLeft) * (_hover/2);

    double offset = 0.005;

    std::vector<double> target = rtde_receive.getActualTCPPose();
    rtde_control.moveL({xcord,     ycord,     _piece + _hover,              target[3], target[4], target[5]}, 1,   0.2);
    rtde_control.moveL({xcord,     ycord,     _chess,                      target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('6');
    rtde_control.moveL({xcord,     ycord,     _piece + _hover + piecesLeft, target[3], target[4], target[5]}, 1,   0.2);

    int gravex;
    if(_playerTurn == 1){
        gravex = 1;
    } else {
        gravex = 7;
    }

    int gravey = -4;

    setMatrixValues(checker, {1, 0, 0, gravex*_factor, 0, 1, 0, gravey*_factor, 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = _CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3), pieceLocation(2,3), 1});
    location = _robot*Translation;
    double xcord2 = location.at(0,0);
    double ycord2 = location.at(1,0);

    rtde_control.moveL({xcord2 + offset, ycord2 + offset, _piece + _hover + piecesLeft, target[3], target[4], target[5]}, 1, 0.2);

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

void Robot::promotePiece(std::vector<std::vector<std::string>> boards, int piecesLeft){
    char column = _moveSet[1][0];
    column = column - 'a';
    int row = 7-(_moveSet[1][1] - '1');

    // Calculate the coords of the piece to be promoted
    Matrix checker(4, 4);
    setMatrixValues(checker, {1, 0, 0, column*_factor, 0, 1, 0, row*_factor, 0, 0, 1, 0, 0, 0, 0, 1});

    Matrix pieceLocation = _CamToChess*checker;

    Matrix Translation(4, 1);
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3), pieceLocation(2,3), 1});

    Matrix location = _robot*Translation;
    double xcord = location.at(0,0);
    double ycord = location.at(1,0);
    piecesLeft = (12 - piecesLeft) * (_hover/2);

    double offset = 0.005;

    std::vector<double> target = rtde_receive.getActualTCPPose();

    int gravex;
    if(_playerTurn == 1){
        gravex = 7;
    } else {
        gravex = 1;
    }
    int gravey = -4;

    setMatrixValues(checker, {1, 0, 0, gravex*_factor, 0, 1, 0, gravey*_factor, 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = _CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3), pieceLocation(2,3), 1});
    location = _robot*Translation;
    double xcord2 = location.at(0,0);
    double ycord2 = location.at(1,0);

    rtde_control.moveL({target[0],       target[1],       _piece + _hover + piecesLeft, target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord2 + offset, ycord2 + offset, _piece + _hover + piecesLeft, target[3], target[4], target[5]}, 1, 0.2);
    atmegaCom('6');
    rtde_control.speedL({0,0,-0.01, 0, 0, 0});
    while(rtde_receive.getActualTCPForce()[2] < 30){}
    double gravez = rtde_receive.getActualTCPPose()[2]+0.0005;
    rtde_control.speedStop();

    rtde_control.moveL({xcord2 + offset, ycord2 + offset, gravez + _hover+ piecesLeft,      target[3], target[4], target[5]}, 1, 0.2);
    atmegaCom('8');
    rtde_control.moveL({xcord2,          ycord2,          gravez + _hover + piecesLeft,     target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord2,          ycord2,          gravez - (_hover/2) + piecesLeft, target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('6');
    rtde_control.moveL({xcord2,          ycord2,          gravez + _hover + piecesLeft,     target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord,           ycord,           gravez + _hover + piecesLeft,     target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord,           ycord,           _piece,                   target[3], target[4], target[5]}, 1, 0.2);
    rtde_control.moveL({xcord,           ycord,           _piece - 0.0015,       target[3], target[4], target[5]}, 0.2, 0.05);
    atmegaCom('8');
    rtde_control.moveL({xcord,           ycord,           _piece + _hover,           target[3], target[4], target[5]}, 1, 0.2);
}

//Function to move the robot
bool Robot::robotMove(std::vector<std::string> moveSet, std::vector<std::vector<std::string>> boards, int playerTurn){
    double _factor = 0.03;
    double xcord = 0;
    double ycord = 0;
    double xcord2 = 0;
    double ycord2 = 0;
    double speed = 2;
    double speed2 = 1;
    double acc = 0.5;
    double acc2 = 0.2;
    _hover = (_piece - _chess) * 2;

    _moveSet = moveSet;
    _playerTurn = playerTurn;

    int column = _moveSet[0][0]; //Starting column
    column = column - 'a';
    int row = 7-(moveSet[0][1] - '1'); //Starting row

    Matrix checker(4, 4);
    setMatrixValues(checker, {1, 0, 0, column*_factor, 0, 1, 0, row*_factor, 0, 0, 1, 0, 0, 0, 0, 1});

    Matrix pieceLocation = _CamToChess*checker;

    Matrix Translation(4, 1);
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3), pieceLocation(2,3), 1});

    Matrix location = _robot*Translation;
    xcord = location.at(0,0);
    ycord = location.at(1,0);

    char column2 = moveSet[1][0]; //Ending column
    column2 = column2 - 'a';
    int row2 = 7-(moveSet[1][1] - '1'); //Ending row

    setMatrixValues(checker, {1, 0, 0, column2*_factor, 0, 1, 0, row2*_factor, 0, 0, 1, 0, 0, 0, 0, 1});
    pieceLocation = _CamToChess*checker;
    setMatrixValues(Translation, {pieceLocation.at(0,3), pieceLocation(1,3), pieceLocation(2,3), 1});
    location = _robot*Translation;
    xcord2 = location.at(0,0);
    ycord2 = location.at(1,0);

    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, pieceLocation.at(2,2)}, 2, 0.5);
    std::vector<double> target = rtde_receive.getActualTCPPose();

    rtde_control.moveL({xcord,  ycord,  _piece + _hover, target[3], target[4], target[5]}, speed,  acc);
    rtde_control.moveL({xcord,  ycord,  _chess,         target[3], target[4], target[5]}, speed2, acc2);
    atmegaCom('6');
    rtde_control.moveL({xcord,  ycord,  _piece + _hover, target[3], target[4], target[5]}, speed,  acc);
    rtde_control.moveL({xcord2, ycord2, _piece + _hover, target[3], target[4], target[5]}, speed,  acc);
    rtde_control.moveL({xcord2, ycord2, _chess,         target[3], target[4], target[5]}, speed2, acc2);
    atmegaCom('8');
    rtde_control.moveL({xcord2, ycord2, _piece + _hover, target[3], target[4], target[5]}, speed,  acc);

    // Remove the jumped piece
    if(_moveSet[0][0] - _moveSet[1][0] == 2 || _moveSet[0][0] - _moveSet[1][0] == -2){
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
        checkerJump(piecesLeft);
    }

    // Promotes piece
    if(((playerTurn == 1) && (_moveSet[1][0] == 'h') && (boards[column][row] == "B ")) || ((playerTurn == 2) && (_moveSet[1][0] == 'a') && (boards[column][row] == "R "))){
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
        promotePiece(boards, piecesLeft);
    }

    rtde_control.moveL(target, speed, acc);

    return true;
}

void Robot::prepForPic(){
    rtde_control.moveJ({-1, -0.75, -1.57, -1.57, 1.57, 0}, 2, 0.5);
}
