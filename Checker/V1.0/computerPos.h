#ifndef COMPUTERPOS_H
#define COMPUTERPOS_H

#include "computerVision.h"
#include <vector>
#include <opencv2/opencv.hpp>

std::vector<double> tableCorner(){
    // Orego for plane parallel with table
    std::vector<double> pos1 = {-0.21375, -0.333966, -0.017901};
    std::vector<double> pos2 = {-0.21388, -0.333998, -0.0178797};
    std::vector<double> pos3 = {-0.213792, -0.333971, -0.0178758};

    //find median of the three vectors
    double x = (pos1[0] + pos2[0] + pos3[0]) / 3;
    double y = (pos1[1] + pos2[1] + pos3[1]) / 3;
    double z = (pos1[2] + pos2[2] + pos3[2]) / 3;

    return {x, y};
}

std::vector<std::vector<double>> calcUnitVec2D(std::vector<cv::Point2f> axis){
    std::vector<double> vec1;
    std::vector<double> vec2;
    std::vector<double> unit1;
    std::vector<double> unit2;

    cv::Point2f orego = axis[1];
    cv::Point2f pos1 = axis[2];
    cv::Point2f pos2 = axis[0];

    vec1.push_back(pos1.x - orego.x);
    vec1.push_back(pos1.y - orego.y);
    vec2.push_back(pos2.x - orego.x);
    vec2.push_back(pos2.y - orego.y);

    double length1 = sqrt(pow(vec1[0], 2) + pow(vec1[1], 2));
    double length2 = sqrt(pow(vec2[0], 2) + pow(vec2[1], 2));

    unit1.push_back(vec1[0] / length1);
    unit1.push_back(vec1[1] / length1);
    unit2.push_back(vec2[0] / length2);
    unit2.push_back(vec2[1] / length2);

    return {unit1, unit2};
}

std::vector<cv::Point2f> newChessCorners(std::vector<cv::Point2f> axis){
    std::vector<double> unit1 = calcUnitVec2D(axis)[0];
    std::vector<double> unit2 = calcUnitVec2D(axis)[1];

    cv::Point2f orego = axis[1];
    cv::Point2f pos1 = axis[2];
    cv::Point2f pos2 = axis[0];

    cv::Point2f newOrego = cv::Point2f(orego.x+(-0.015*unit1[0]-0.015*unit1[1]), orego.y+(-0.015*unit2[0] + -0.015*unit2[1]));
    cv::Point2f newPos1 = cv::Point2f(pos1.x+(0.015*unit1[0]-0.015*unit1[1]), pos1.y+(0.015*unit2[0] + -0.015*unit2[1]));
    cv::Point2f newPos2 = cv::Point2f(pos2.x+(-0.015*unit1[0]+0.015*unit1[1]), pos2.y+(-0.015*unit2[0] + 0.015*unit2[1]));
    return {newPos1, newOrego, newPos2};
}

std::vector<double> findCoordFrame(std::vector<cv::Point2f> axis, cv::Point2f varpoint){
    std::vector<double> vec1;
    std::vector<double> vec2;

    std::vector<cv::Point2f> newCorners = newChessCorners(axis);
    cv::Point2f orego = newCorners[1];
    cv::Point2f pos1 = newCorners[0];
    cv::Point2f pos2 = newCorners[2];

    std::vector<std::vector<double>> units = calcUnitVec2D({pos2, orego, pos1});
    std::vector<double> unit1 = units[0];
    std::vector<double> unit2 = units[1];

    double newPointx = ((varpoint.x-orego.x)*unit1[0] + (varpoint.y-orego.y)*unit1[1]);
    double newPointy = ((varpoint.x-orego.x)*unit2[0] + (varpoint.y-orego.y)*unit2[1]);

    cv::Mat img = cv::imread("/home/aksel/Documents/GitHub/Autonome_Robotter/ComputerVision_versions/Images/boards4.jpg");
    cv::Point2f newPoint = cv::Point2f((varpoint.x)/pixToMeters, (varpoint.y)/pixToMeters);
    cv::circle(img, newPoint, 20, cv::Scalar(255, 255, 255), -1);
    arrowedLine(img, orego/pixToMeters, pos1/pixToMeters, cv::Scalar(255, 255, 255), 2);
    cv::putText(img, "x-akse", pos1/pixToMeters, FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
    arrowedLine(img, orego/pixToMeters, pos2/pixToMeters, cv::Scalar(255, 255, 255), 2);
    cv::putText(img, "y-akse", pos2/pixToMeters, FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 2);
    namedWindow("detected board", WINDOW_NORMAL);
    imshow("detected board", img);
    resizeWindow("detected board", 1000, 1300);
    moveWindow("detected board",img.cols/2,100);
    cv::waitKey(0);

    return {newPointx, newPointy};
}



#endif // COMPUTERPOS_H
