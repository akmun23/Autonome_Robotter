#ifndef COMPUTERPOS_H
#define COMPUTERPOS_H

#include "computerVision.h"
#include <vector>
#include <opencv2/opencv.hpp>

double tableCorner(){
    // Orego for plane parallel with table
    std::vector<double> pos1 = {-0.21375, -0.333966, -0.017901};
    std::vector<double> pos2 = {-0.21388, -0.333998, -0.0178797};
    std::vector<double> pos3 = {-0.213792, -0.333971, -0.0178758};

    //find median of the three vectors
    double x = (pos1[0] + pos2[0] + pos3[0]) / 3;
    double y = (pos1[1] + pos2[1] + pos3[1]) / 3;
    double z = (pos1[2] + pos2[2] + pos3[2]) / 3;

    return z;
}

double boardCorners(std::vector<cv::Point2f> axis){
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

    double pointx = (offsetx*pixToMeters-orego.x);
    double pointy = (offsety*pixToMeters-orego.y);

    double refx = pointx*unit1[0] + pointy*unit1[1];
    double refy = pointx*unit2[0] + pointy*unit2[1];

    std::cout << "Refx: " << refx << std::endl;
    std::cout << "Refy: " << refy << std::endl;
}


#endif // COMPUTERPOS_H
