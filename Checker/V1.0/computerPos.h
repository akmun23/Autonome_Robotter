#ifndef COMPUTERPOS_H
#define COMPUTERPOS_H

#include "boardUpdate.h"
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
            } else if (newCorners[1].x-newCorners[2].x-0.005 < circleChecked[i][0] && newCorners[1].x-newCorners[2].x+0.005 > circleChecked[i][0] && newCorners[1].y-newCorners[2].y-0.005 < circleChecked[i][1] && newCorners[1].y-newCorners[2].y+0.005 > circleChecked[i][1]){
                pos2 = true;
            } else if (newCorners[0].x-newCorners[1].x-0.005 < circleChecked[i][0] && newCorners[0].x-newCorners[1].x+0.005 > circleChecked[i][0] && newCorners[0].y-newCorners[1].y-0.005 < circleChecked[i][1] && newCorners[0].y-newCorners[1].y+0.005 > circleChecked[i][1]){
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

std::vector<std::vector<std::string>> boardLoop(cv::Vec3b black, cv::Vec3b red, std::vector<cv::Point2f> newCorners, cv::Mat img){
    std::vector<std::vector<double>> circleChecked = {};
    std::vector<std::vector<Vec3f>> colorsAndCircles;
    std::vector<Vec3f> circles;
    std::vector<Vec3f> colors;
    std::vector<std::vector<std::string>> chessBoard;
    int count = 0;
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
                    if((black[0]-10 < colors[k][0]) && (black[0]+10 > colors[k][0]) && (black[1]-10 < colors[k][1]) && (black[1]+10 > colors[k][1]) && (black[2]-10 < colors[k][2]) && (black[2]+10 > colors[k][2])){
                        chessBoard[i][j] = "B ";
                        count++;
                    } else if((red[0]-10 < colors[k][0]) && (red[0]+10 > colors[k][0]) && (red[1]-10 < colors[k][1]) && (red[1]+10 > colors[k][1]) && (red[2]-10 < colors[k][2]) && (red[2]+10 > colors[k][2])){
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
    return chessBoard;
}

std::vector<std::string> findMove(std::vector<std::vector<std::string>> prevBoard, std::vector<std::vector<std::string>> chessBoard, int playerTurn){
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

#endif // COMPUTERPOS_H
