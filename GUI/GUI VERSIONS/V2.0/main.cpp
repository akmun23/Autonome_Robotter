#include "gui.h"
#include <opencv2/opencv.hpp>
//#include "robotMove.h"
//#include <unistd.h>
//#include <ur_rtde/rtde_control_interface.h>
//#include <ur_rtde/rtde_receive_interface.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    std::string winName = "Project GUI";
    GUI gui(winName);

    gui.Draw();
    gui.updateText();

    // Creates window, and shows image on it.
    namedWindow(winName, WINDOW_AUTOSIZE);
    setMouseCallback(winName, &GUI::mouseCallBack, &gui);
    waitKey(0);

    return 0;
}
