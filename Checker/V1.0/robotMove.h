#ifndef ROBOTMOVE_H
#define ROBOTMOVE_H

#include <vector>
#include <string>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

using namespace ur_rtde;

RTDEControlInterface rtde_control("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);
RTDEReceiveInterface rtde_receive("192.168.1.54", RTDEControlInterface::FLAG_NO_WAIT | RTDEControlInterface::FLAG_USE_EXT_UR_CAP);

//Function to move the robot
void robotMove(std::vector<std::string> moveSet){
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

        std::vector<double> target = rtde_receive.getActualTCPPose();
        rtde_control.moveL({target[0] + column*factor, target[1] + row*factor, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({target[0] + column*factor, target[1] + row*factor, target[2]-0.35, target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({target[0] + column*factor, target[1] + row*factor, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({target[0] + column2*factor, target[1] + row2*factor, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({target[0] + column2*factor, target[1] + row2*factor, target[2]-0.35, target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL({target[0] + column2*factor, target[1] + row2*factor, target[2], target[3], target[4], target[5]}, 0.2, 0.05);
        rtde_control.moveL(target, 0.2, 0.05);

    }
}


#endif // ROBOTMOVE_H
