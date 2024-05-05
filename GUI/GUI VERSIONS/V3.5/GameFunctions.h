#pragma once
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/highgui.hpp>

using namespace std;
using namespace cv;

//Circle inherites methods and attribute templates from "Rect"
class Circle : public Rect{
    using Rect::Rect; //Inherites constructor from "Rect"
};

void clearVecInt(std::vector<int>& vector){
    for(int i = 0; i < vector.size(); i++){
        vector[i] = 0;
    }

    vector.resize(0);
}

void clearVecString(vector<string>& vector){
    vector.resize(0);
}

//Finds the "ID" of given element in given array, and returns the ID.
int findInArr(string input[], string wantFound){
    for(int i = 0; i < 8; i++){
        if(input[i].compare(wantFound) == 0){
           return i; 
        }
    }
    return 0;
}

void setString(string& stringToBeChanged, string stringValue){
    stringToBeChanged = stringValue;
}

void setBool(bool& boolean, bool TF){
    boolean = TF;
}

//Converts position as "INT" to position described as string.
void posToStringConvert(int x, int y, vector<string>& stringPos){
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    string col, row;

    col = numArr[findInArr(numArr,to_string((x-boardOffSetX/2)/50))];
    row = alphabetArr[findInArr(alphabetArr,alphabetArr[(y-boardOffSetY)/50])];

    stringPos.push_back(row + col);
}

void stringToPosConvert(string stringPosValue, vector<int>& outputVector){
    int x, y;
    int boardOffSetX = 100;
    int boardOffSetY = 75;
    string alphabetArr[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    string numArr[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    //string alphabetString = string str(stringPosValue[0]);
    string alphabetString(1, stringPosValue[0]);
    string intString = to_string((int(stringPosValue[1])-48));

    x = findInArr(numArr, intString)*50 + boardOffSetX;
    y = findInArr(alphabetArr, alphabetString)*50 + boardOffSetY;

    cout << "Input: " << alphabetString << intString << ", er blevet converteret til: " << x << "," << y << endl;

    outputVector.push_back(x);
    outputVector.push_back(y);

    cout << "Checking information in intPos: " << outputVector[outputVector.size()-2] << "," << outputVector[outputVector.size()-1] << endl;

}

bool doesPosContainRect(int x, int y, vector<Rect> rectangles){
    for(int i = 0; i < 64; i++){
        if(rectangles[i].contains(Point(x, y))){
            cout << "Rect: " << i << " , indeholder punktet: " << x << "," << y << endl;
            return true;
        }
    }

    return false;
}

//Checks if a "Rect" contains elements of given vector.
bool doesRectContainChecker(int x, int y, vector<Circle> checkerVec){
    for(int i = 0; i < checkerVec.size(); i++){
        if(checkerVec[i].contains(Point(x, y))){
            return true;
        }
    }

    return 0;
}

int piecesLeft(vector<Rect> rectangles, vector<Circle> checkerVec){
    int count = 0;

    for(int i = 0; i < 64; i++){
        for(int j = 0; j < checkerVec.size(); j++){
            if(rectangles[i].contains(Point(checkerVec[j].x, checkerVec[j].y))){
                count++;
            }
        }
    }

    return count;
}
