#ifndef COMPUTERPOS_H
#define COMPUTERPOS_H

#include <vector>

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

double boardCorners() {

}

#endif // COMPUTERPOS_H
