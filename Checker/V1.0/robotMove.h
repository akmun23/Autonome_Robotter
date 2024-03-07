#ifndef ROBOTMOVE_H
#define ROBOTMOVE_H

#include <vector>
#include <string>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;

RTDEControlInterface rtde_control("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);
RTDEReceiveInterface rtde_receive("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);

//Function to set up robot and make a plane parallel with table
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

    rtde_control.teachMode();
    std::cin.get();
    std::vector<double> boardPlane1 = rtde_receive.getActualTCPPose();
    std::cin.get();
    std::vector<double> boardPlane2 = rtde_receive.getActualTCPPose();
    std::cin.get();
    std::vector<double> boardPlane3 = rtde_receive.getActualTCPPose();
    rtde_control.endTeachMode();

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

//Function to move the robot
void robotMove(std::vector<std::string> moveSet, std::vector<std::vector<double>> startUp){
    double factor = 0.05;
    for (int i = 0; i < moveSet.size(); i += 2) {
        double xcord = 0;
        double ycord = 0;
        double zcord = 0;
        double xcord2 = 0;
        double ycord2 = 0;
        double zcord2 = 0;

        std::vector<double> boardPlane = startUp[0];
        std::vector<double> rotMatrix = startUp[1];

        char column = moveSet[i][0]; //Starting column
        column = tolower(column);
        column = column - 'a';
        int row = moveSet[i][1] - '1'; //Starting row

        char column2 = moveSet[i+1][0]; //Ending column
        column2 = tolower(column2);
        column2 = column2 - 'a';
        int row2 = moveSet[i+1][1] - '1'; //Ending row

        xcord = rotMatrix[0]*column*factor + rotMatrix[3]*row*factor + rotMatrix[6]*0*factor + boardPlane[0];
        ycord = rotMatrix[1]*column*factor + rotMatrix[4]*row*factor + rotMatrix[7]*0*factor + boardPlane[1];
        zcord = boardPlane[2];

        xcord2 = rotMatrix[0]*column2*factor + rotMatrix[3]*row2*factor + rotMatrix[6]*0*factor + boardPlane[0];
        ycord2 = rotMatrix[1]*column2*factor + rotMatrix[4]*row2*factor + rotMatrix[7]*0*factor + boardPlane[1];
        zcord2 = boardPlane[2];

        std::vector<double> target = rtde_receive.getActualTCPPose();

        rtde_control.moveL({xcord, ycord, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({xcord, ycord, zcord, target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({xcord, ycord, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({xcord2, ycord2, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({xcord2, ycord2, zcord2, target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({xcord2, ycord2, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL(target, 0.2, 0.05);

    }
}




#endif // ROBOTMOVE_H
