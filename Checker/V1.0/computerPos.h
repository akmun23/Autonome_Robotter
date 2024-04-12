#ifndef COMPUTERPOS_H
#define COMPUTERPOS_H

#include "boardUpdate.h"
#include "computerVision.h"
#include <vector>
#include <opencv2/opencv.hpp>

std::vector<double> yaxis1 = {0.399853, -0.0506146, -0.018515};
std::vector<double> yaxis2 = {0.399852, -0.0506224, -0.0185018};
std::vector<double> yaxis3 = {0.399851, -0.0506165, -0.0185018};
std::vector<double> xaxis1 = {-0.0889017, -0.876077, -0.0112772};
std::vector<double> xaxis2 = {-0.0888664, -0.876096, -0.01124};
std::vector<double> xaxis3 = {-0.0888984, -0.876086, -0.0112617};
std::vector<double> orego1 = {-0.290504, -0.336675, -0.0178658};
std::vector<double> orego2 = {-0.290528, -0.336664, -0.0178206};
std::vector<double> orego3 = {-0.29052, -0.33669, -0.0178003};

cv::Point2f meanPoints(std::vector<double> point1, std::vector<double> point2, std::vector<double> point3){
    //find median of the three vectors
    double x = (point1[0] + point2[0] + point3[0]) / 3;
    double y = (point1[1] + point2[1] + point3[1]) / 3;
    double z = (point1[2] + point2[2] + point3[2]) / 3;

    return cv::Point2f(x, y);
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

    cv::Point2f newOrego = cv::Point2f(orego.x+(-0.015*unit1[0]-0.015*unit2[0]), orego.y+(-0.015*unit1[1] - 0.015*unit2[1]));
    cv::Point2f newPos1 = cv::Point2f(pos1.x+(0.015*unit1[0]-0.015*unit2[0]), pos1.y+(0.015*unit1[1] - 0.015*unit2[1]));
    cv::Point2f newPos2 = cv::Point2f(pos2.x+(-0.015*unit1[0]+0.015*unit2[0]), pos2.y+(-0.015*unit1[1] + 0.015*unit2[1]));
    return {newPos1, newOrego, newPos2};
}

std::vector<double> findCoordFrame(std::vector<cv::Point2f> axis, cv::Point2f varpoint){
    std::vector<double> vec1;
    std::vector<double> vec2;

    cv::Point2f orego = axis[1];
    cv::Point2f pos1 = axis[0];
    cv::Point2f pos2 = axis[2];

    std::vector<std::vector<double>> units = calcUnitVec2D({pos2, orego, pos1});
    std::vector<double> unit1 = units[0];
    std::vector<double> unit2 = units[1];

    double newPointx = ((varpoint.x-orego.x)*unit1[0] + (varpoint.y-orego.y)*unit1[1]);
    double newPointy = ((varpoint.x-orego.x)*unit2[0] + (varpoint.y-orego.y)*unit2[1]);

    cv::Point2f newPoint = cv::Point2f((varpoint.x)/pixToMeters, (varpoint.y)/pixToMeters);

    return {newPointx, newPointy};
}

std::vector<Vec3b> startBoard(std::vector<std::vector<double>> circleChecked, std::vector<cv::Vec3f> colors, std::vector<std::vector<std::string>>& chessBoard){
    double bBlack = 0;
    double gBlack = 0;
    double rBlack = 0;
    double bRed = 0;
    double gRed = 0;
    double rRed = 0;
    Vec3b black = 0;
    Vec3b red = 0;
    for(int i = 0; i < 8; i++){
        if(i%2 == 0){
            chessBoard.push_back({"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "});
        } else {
            chessBoard.push_back({"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "});
        }
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < circleChecked.size(); k++) {
                if(((circleChecked[k][0] - 0.005) <  (j*0.03)) && ((circleChecked[k][0] + 0.005) > (j*0.03) && ((circleChecked[k][1] - 0.005) < (i*0.03)) && ((circleChecked[k][1] + 0.005) > (i*0.03)))){
                    if(circleChecked[k][1] < 0.1){
                        chessBoard[i][j] = "B ";
                        bBlack += colors[k][0];
                        gBlack += colors[k][1];
                        rBlack += colors[k][2];
                        std::cout << "Black: " << colors[k] << std::endl;
                    } else if(circleChecked[k][1] > 0.14){
                        chessBoard[i][j] = "R ";
                        bRed += colors[k][0];
                        gRed += colors[k][1];
                        rRed += colors[k][2];
                        std::cout << "Red: " << colors[k] << std::endl;
                    }
                }
            }

        }
    }
    bBlack = bBlack/12;
    gBlack = gBlack/12;
    rBlack = rBlack/12;

    bRed = bRed/12;
    gRed = gRed/12;
    rRed = rRed/12;

    black = Vec3b(bBlack, gBlack, rBlack);
    red = Vec3b(bRed, gRed, rRed);

    std::cout << "Black: " << black << std::endl;
    std::cout << "Red: " << red << std::endl;
    checkerBoard(chessBoard);
    std::cout << "<----------------------->" <<std::endl;

    return {black, red};
}

std::vector<Vec3b> firstLoop(std::vector<cv::Point2f> allAxis, std::vector<cv::Point2f>& newCorners, cv::Mat img, std::vector<cv::Vec3f> circles, std::vector<cv::Vec3f> colors, std::vector<std::vector<std::string>>& chessBoard){
    std::vector<std::vector<double>> circleChecked;
    int checkLoop = 0;
    std::vector<double> init = findCoordFrame(newCorners, cv::Point2f(circles[0][0]*pixToMeters, circles[0][1]*pixToMeters));

    while(1){
        int xcheck = 0;
        int ycheck = 0;
        bool orego = false;
        bool pos1 = false;
        bool pos2 = false;
        int remove = 0;
        if(checkLoop == 0){
            for (int i = 0; i < circles.size()+remove; i++) {
                circleChecked.push_back(findCoordFrame(newCorners, cv::Point2f(circles[i-remove][0]*pixToMeters, circles[i-remove][1]*pixToMeters)));
                if((circleChecked[i-remove][0] > -0.02) && (circleChecked[i-remove][0] < 0.242) && (circleChecked[i-remove][1] > -0.02) && (circleChecked[i-remove][1] < 0.242)){
                    continue;
                }
                circleChecked.erase(std::next(circleChecked.begin(), i-remove));
                circles.erase(std::next(circles.begin(), i-remove));
                colors.erase(std::next(colors.begin(), i-remove));
                remove++;
            }
        } else {
            circleChecked = {};
            for (int i = 0; i < circles.size(); ++i) {
                circleChecked.push_back(findCoordFrame(newCorners, cv::Point2f(circles[i][0]*pixToMeters, circles[i][1]*pixToMeters)));
            }
        }

        for (int i = 0; i < circleChecked.size(); i++) {
            if(((circleChecked[i][0] - 0.005) < init[0]) && ((circleChecked[i][0] + 0.005) > init[0])){
                std::cout << "Circle is alligned on the x-axis: " << i+1 << std::endl;
                xcheck++;
            }
            if(((circleChecked[i][1] - 0.005) < init[1]) && ((circleChecked[i][1] + 0.005) > init[1])){
                std::cout << "Circle is alligned on the y-axis: " << i+1 << std::endl;
                ycheck++;
            }

            if(-0.005 < circleChecked[i][0] && 0.005 > circleChecked[i][0] && -0.005 < circleChecked[i][1] && 0.005 > circleChecked[i][1]){
                orego = true;
            } else if (0.205 < circleChecked[i][0] && 0.215 > circleChecked[i][0] && -0.005 < circleChecked[i][1] && 0.005 > circleChecked[i][1]){
                pos2 = true;
            } else if (-0.005 < circleChecked[i][0] && 0.005 > circleChecked[i][0] && 0.205 < circleChecked[i][1] && 0.215 > circleChecked[i][1]){
                pos1 = true;
            }
        }
        if(orego){
            break;
        } else if(pos1){
            axis = {allAxis[1], allAxis[0], allAxis[2]};
            newCorners = newChessCorners(axis);
            std::cout << "Koordinatsystemet er nu vendt" << std::endl;

        } else if(pos2){
            axis = {allAxis[2], allAxis[3], allAxis[1]};
            newCorners = newChessCorners(axis);
            std::cout << "Koordinatsystemet er nu vendt" << std::endl;
        }
        std::cout << "-------------------" <<std::endl;
        checkLoop++;
    }
   return startBoard(circleChecked, colors, chessBoard);
}

std::vector<std::string> boardLoop(cv::Vec3b black, cv::Vec3b red, std::vector<cv::Point2f> newCorners, cv::Mat img, std::vector<std::vector<std::string>>& chessBoard, int playerTurn){
    std::vector<std::vector<double>> circleChecked = {};
    std::vector<std::vector<Vec3f>> colorsAndCircles;
    std::vector<Vec3f> circles;
    std::vector<Vec3f> colors;
    std::vector<std::vector<std::string>> prevBoard = chessBoard;
    int count = 0;
    int tolerance = 10;
    while(count != 24){
    count = 0;
    circleChecked = {};
    colorsAndCircles = detectAndDrawCentersOfCircles(img);
    circles = colorsAndCircles[0];
    colors = colorsAndCircles[1];
    int remove = 0;
    for(int i = 0; i < circles.size()+remove; i++) {
        circleChecked.push_back(findCoordFrame(newCorners, cv::Point2f(circles[i-remove][0]*pixToMeters, circles[i-remove][1]*pixToMeters)));
        if((circleChecked[i-remove][0] > -0.02) && (circleChecked[i-remove][0] < 0.242) && (circleChecked[i-remove][1] > -0.02) && (circleChecked[i-remove][1] < 0.242)){
            continue;
        }
        circleChecked.erase(std::next(circleChecked.begin(), i-remove));
        circles.erase(std::next(circles.begin(), i-remove));
        colors.erase(std::next(colors.begin(), i-remove));
        remove++;
    }


    chessBoard = {};
    for(int i = 0; i < 8; i++){
        if(i%2 == 0){
            chessBoard.push_back({"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "});
        } else {
            chessBoard.push_back({"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "});
        }
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < circleChecked.size(); k++) {
                if(((circleChecked[k][0] - 0.005) <  (j*0.03)) && ((circleChecked[k][0] + 0.005) > (j*0.03)) && ((circleChecked[k][1] - 0.005) < (i*0.03)) && ((circleChecked[k][1] + 0.005) > (i*0.03))){
                    if((black[0]-tolerance < colors[k][0]) && (black[0]+tolerance > colors[k][0]) && (black[1]-tolerance < colors[k][1]) && (black[1]+tolerance > colors[k][1]) && (black[2]-tolerance < colors[k][2]) && (black[2]+tolerance > colors[k][2])){
                        chessBoard[i][j] = "B ";
                        count++;
                    } else if((red[0]-tolerance < colors[k][0]) && (red[0]+tolerance > colors[k][0]) && (red[1]-tolerance < colors[k][1]) && (red[1]+tolerance > colors[k][1]) && (red[2]-tolerance < colors[k][2]) && (red[2]+tolerance > colors[k][2])){
                        chessBoard[i][j] = "R ";
                        count++;
                    }
                }
            }

        }
    }
    }
    checkerBoard(chessBoard);
    std::cout << "<----------------------->" <<std::endl;

    int column = 0;
    int row = 0;
    int column2 = 0;
    int row2 = 0;
    std::string checkPiece;
    if(playerTurn == 1){
        checkPiece = "B ";
    } else {
        checkPiece = "R ";
    }
    for (int i = 0; i < chessBoard.size(); ++i) {
        for (int j = 0; j < chessBoard[0].size(); ++j) {
            if (prevBoard[i][j] != chessBoard[i][j]){
                if(prevBoard[i][j] == checkPiece){
                    row = i;
                    column = j;
                }
                if(chessBoard[i][j] == checkPiece){
                    row2 = i;
                    column2 = j;
                }
            }
        }
    }

    //Turn row into letter and column into number for start position
    std::string columnLetter;
    columnLetter += std::to_string(column+1);
    std::string rowLetter;
    rowLetter += row + 'a';
    std::string playerStart = rowLetter + columnLetter;

    //Turn row into letter and column into number for end position
    std::string columnLetter2;
    columnLetter2 += std::to_string(column2+1);
    std::string rowLetter2;
    rowLetter2 += row2 + 'a';
    std::string playerEnd = rowLetter2 + columnLetter2;
    return {playerStart, playerEnd};
}

std::vector<cv::Point2f> calibrationCircles(std::vector<std::vector<Vec3f>> circlesAndColors){
    std::vector<cv::Vec3f> circles = circlesAndColors[0];
    std::vector<cv::Vec3f> colors = circlesAndColors[1];
    cv::Point2f greenFunc;
    cv::Point2f yellowFunc;
    cv::Point2f magentaFunc;
    int tolerance = 20;

    for (int k = 0; k < circles.size(); k++) {
        if((green[0]-tolerance < colors[k][0]) && (green[0]+tolerance > colors[k][0]) && (green[1]-tolerance < colors[k][1]) && (green[1]+tolerance > colors[k][1]) && (green[2]-tolerance < colors[k][2]) && (green[2]+tolerance > colors[k][2])){
            greenFunc = {circles[k][0], circles[k][1]};
        } else if((yellow[0]-tolerance < colors[k][0]) && (yellow[0]+tolerance > colors[k][0]) && (yellow[1]-tolerance < colors[k][1]) && (yellow[1]+tolerance > colors[k][1]) && (yellow[2]-tolerance < colors[k][2]) && (yellow[2]+tolerance > colors[k][2])){
            yellowFunc = {circles[k][0], circles[k][1]};
        } else if((magenta[0]-tolerance < colors[k][0]) && (magenta[0]+tolerance > colors[k][0]) && (magenta[1]-tolerance < colors[k][1]) && (magenta[1]+tolerance > colors[k][1]) && (magenta[2]-tolerance < colors[k][2]) && (magenta[2]+tolerance > colors[k][2])){
            magentaFunc = {circles[k][0], circles[k][1]};
        }
    }
    return {magentaFunc, yellowFunc, greenFunc};
}
#endif // COMPUTERPOS_H
