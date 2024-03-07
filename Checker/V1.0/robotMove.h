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
std::vector<double> robotStart() {
    rtde_control.moveJ({-1, -1.57, -1.57, -1.57, 1.57, 0}, 1, 0.1);
    std::vector<double> target = rtde_receive.getActualTCPPose();
    rtde_control.teachMode();
    std::cin.get();
    std::vector<double> boardPlane = rtde_receive.getActualTCPPose();
    rtde_control.endTeachMode();
    rtde_control.moveL(target, 1, 0.1);
    return boardPlane;
}

//Function to move the robot
void robotMove(std::vector<std::string> moveSet, std::vector<double> boardPlane){
    double factor = 0.05;
    for (int i = 0; i < moveSet.size(); i += 2) {
        char column = moveSet[i][0]; //Starting column
        column = tolower(column);
        column = column - 'a';
        int row = moveSet[i][1] - '1'; //Starting row

        char column2 = moveSet[i+1][0]; //Ending column
        column2 = tolower(column2);
        column2 = column2 - 'a';
        int row2 = moveSet[i+1][1] - '1'; //Ending row

        std::vector<double> wrt_feature = {column*factor, row*factor, 0, 0, 0, 0};
        std::vector<double> wrt_feature2 = {column2*factor, row2*factor, 0, 0, 0, 0};
        std::vector<double> result = rtde_control.poseTrans(boardPlane, wrt_feature);
        std::vector<double> result2 = rtde_control.poseTrans(boardPlane, wrt_feature2);

        std::vector<double> target = rtde_receive.getActualTCPPose();
        rtde_control.moveL({result[0], result[1], target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({result[0], result[1], boardPlane[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({result[0], result[1], target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({result2[0], result2[1], target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({result2[0], result2[1], boardPlane[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({result2[0], result2[1], target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL(target, 0.2, 0.05);

    }
}


#endif // ROBOTMOVE_H
