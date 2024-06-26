#include "computerVision.h"



std::vector<std::vector<Vec3f>> detectAndDrawCentersOfCircles(Mat& src){
    vector<Vec3f> circles;
    vector<Vec3f> colors;
    //![convert_to_gray]
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    medianBlur(gray, gray, 1);
    //![reduce_noise]

    //![houghcircles]
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/50,  // change this value to detect circles with different distances to each other
                 100, 30, 16, 32 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
                 );
    //![houghcircles]

    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        colors.push_back(src.at<Vec3b>(center));
        // circle center
        circle(src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(src, center, radius+3, Scalar(0,0,0), -1, LINE_AA);
    }
    namedWindow("detected board", WINDOW_NORMAL);
    imshow("detected board", src);
    resizeWindow("detected board", 1000, 1300);
    moveWindow("detected board",src.cols/2,100);
    waitKey();
    return {circles, colors};
}

std::vector<cv::Point2f> detectAndDrawChessboardCorners(cv::Mat src, double& pixToMeters, double& boardSize) {

    vector<Point2f> corners; // Array will be filled by the detected corners
    for (int i = 0; i < 1; i++){
        Size patternsize(7,7); // The interior number of corners in a checkers board
        Mat gray;
        cvtColor(src,gray,COLOR_BGR2GRAY);

        //CALIB_CB_FAST_CHECK saves a lot of time on images (Removed for better accuracy)
        bool patternfound = findChessboardCorners(gray, patternsize, corners, 0 +
                                                                                  CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE
                                                                                  + CALIB_CB_FILTER_QUADS);
        if(patternfound){
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1),
                         TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS, 30, 0.1));
        } // Subpixels are also considered increasing accuracy

        drawChessboardCorners(src, patternsize, Mat(corners), patternfound); // Corners er visualized.

        // Define the offset of where the table the checkers board can be placed on starts. Also the scale of cm per pixel. These have to be defined when camera is set up.
        pixToMeters = (0.03 / sqrt(pow((corners[1].x - corners[0].x),2) + pow((corners[1].y - corners[0].y),2)));

        for(int i = 0; i <= corners.size(); i++){
            corners[i].x = (corners[i].x)* pixToMeters;
            corners[i].y = (corners[i].y) * pixToMeters;
        } // Corners er redefined with coordinates in m instead of pixels.

        // Draw the corners of the board and offset
        int exponent = 2;
        boardSize = sqrt((pow(corners[1].x - corners[0].x,exponent)) + (pow(corners[1].y - corners[0].y,exponent)));
        // The length of the individual squares of the board are calculated to calibrate the game program.
        cout << "Boardsize: " << boardSize << endl;
    }
    std::vector<cv::Point2f> axis = {corners[0], corners[6], corners[42], corners[48]};
    return axis;
}

// Finds the median of the three vectors
cv::Point2f meanPoints(std::vector<double> point1, std::vector<double> point2, std::vector<double> point3){
    double x = (point1[0] + point2[0] + point3[0]) / 3;
    double y = (point1[1] + point2[1] + point3[1]) / 3;
    double z = (point1[2] + point2[2] + point3[2]) / 3;

    return cv::Point2f(x, y);
}

// Calculates the unit vectors for the x and y axis
std::vector<std::vector<double>> calcUnitVec2D(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis){
    // Calculates the vectors for the x and y axis
    std::vector<double> vec1 = {xaxis.x - orego.x, xaxis.y - orego.y};
    std::vector<double> vec2 = {yaxis.x - orego.x, yaxis.y - orego.y};

    // Calculates the length of the vectors
    double length1 = sqrt(pow(vec1[0], 2) + pow(vec1[1], 2));
    double length2 = sqrt(pow(vec2[0], 2) + pow(vec2[1], 2));

    // Calculates the unit vectors for the x and y axis
    std::vector<double> unit1 = {(vec1[0] / length1), (vec1[1] / length1)};
    std::vector<double> unit2 = {(vec2[0] / length2), (vec2[1] / length2)};

    return {unit1, unit2};
}

// Shifts the corners to the middle of the checker pieces instead of the inner corner
std::vector<cv::Point2f> newChessCorners(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis){
    double move = 0.015;

    // Calculates the unit vectors for the x and y axis
    std::vector<std::vector<double>> unitVectors = calcUnitVec2D(yaxis, orego, xaxis);

    // Moves the pieces 1.5 cm
    cv::Point2f newOrego = cv::Point2f(orego.x + (-move * unitVectors[0][0] - move * unitVectors[1][0]), orego.y + (-move * unitVectors[0][1] - move * unitVectors[1][1]));
    cv::Point2f xAxis    = cv::Point2f(xaxis.x + ( move * unitVectors[0][0] - move * unitVectors[1][0]), xaxis.y + ( move * unitVectors[0][1] - move * unitVectors[1][1]));
    cv::Point2f yAxis    = cv::Point2f(yaxis.x + (-move * unitVectors[0][0] + move * unitVectors[1][0]), yaxis.y + (-move * unitVectors[0][1] + move * unitVectors[1][1]));

    return {xAxis, newOrego, yAxis};
}

// Finds the coordinates for the circles in the given coordinate frame
std::vector<double> findCoordInFrame(std::vector<cv::Point2f> axis, cv::Point2f varpoint){
    // Saves the coordinates for the origin, x-axis and y-axis
    cv::Point2f orego = axis[1];
    cv::Point2f xAxis = axis[0];
    cv::Point2f yAxis = axis[2];

    // Calculates the unit vectors for the x and y axis
    std::vector<std::vector<double>> units = calcUnitVec2D(yAxis, orego, xAxis);
    std::vector<double> unit1 = units[0];
    std::vector<double> unit2 = units[1];

    // Calculates the new coordinates for the circle
    double newPointx = ((varpoint.x-orego.x)*unit1[0] + (varpoint.y-orego.y)*unit1[1]);
    double newPointy = ((varpoint.x-orego.x)*unit2[0] + (varpoint.y-orego.y)*unit2[1]);

    return {newPointx, newPointy};
}


// Finds the coordinates for the three calibration circles
std::vector<cv::Point2f> calibrationCircles(std::vector<std::vector<Vec3f>> circlesAndColors){
    // Preset values for the three calibration circles
    Vec3b green = {101, 190, 168};
    Vec3b yellow = {40, 224, 255};
    Vec3b magenta = {180, 122, 179};

    // Stores the coordinates of all cirlces and their color that has been detected
    std::vector<cv::Vec3f> circles = circlesAndColors[0];
    std::vector<cv::Vec3f> colors = circlesAndColors[1];

    // Stores the coordinates of the three calibration circles
    cv::Point2f greenFunc;
    cv::Point2f yellowFunc;
    cv::Point2f magentaFunc;

    // Tolerance for the color detection
    int tolerance = 22;

    // Finds the coordinates of the three calibration circles by iterating through all the detected circles
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

// Finds the colors of the checker pieces on the board
std::vector<Vec3b> startBoard(std::vector<std::vector<double>> circleChecked, std::vector<cv::Vec3f> colors, std::vector<std::vector<std::string>>& chessBoard){
    // Values are saved as BGR in OpenCV
    double bBlack = 0;
    double gBlack = 0;
    double rBlack = 0;
    double bRed = 0;
    double gRed = 0;
    double rRed = 0;
    Vec3b black = {0, 0, 0};
    Vec3b red = {0, 0, 0};
    chessBoard = {};

    // Iterates through the board and checks the color of the checker pieces
    // Also outputs the placement of the checker pieces
    for(int i = 0; i < 8; i++){
        if(i%2 == 0){
            chessBoard.push_back({"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "});
        } else {
            chessBoard.push_back({"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "});
        }
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < circleChecked.size(); k++) {
                // Checks if the circle is within the boundaries of the expected location of the checker piece
                if(((circleChecked[k][0] - 0.0075) <  (j*0.03)) && ((circleChecked[k][0] + 0.0075) > (j*0.03) && ((circleChecked[k][1] - 0.0075) < (i*0.03)) && ((circleChecked[k][1] + 0.0075) > (i*0.03)))){
                    // If the piece is located at the black end of the board then the value is saved as the color of a black piece else it is stored as the color of a red piece
                    if(circleChecked[k][1] < 0.1){
                        chessBoard[i][j] = "B ";
                        bBlack += colors[k][0];
                        gBlack += colors[k][1];
                        rBlack += colors[k][2];
                    } else if(circleChecked[k][1] > 0.14){
                        chessBoard[i][j] = "R ";
                        bRed += colors[k][0];
                        gRed += colors[k][1];
                        rRed += colors[k][2];
                    }
                }
            }

        }
    }

    // Calculates the average color of the black and red checker pieces
    bBlack = bBlack/12;
    gBlack = gBlack/12;
    rBlack = rBlack/12;
    bRed = bRed/12;
    gRed = gRed/12;
    rRed = rRed/12;

    // Saves the average color of the black and red checker pieces
    black = Vec3b(bBlack, gBlack, rBlack);
    red = Vec3b(bRed, gRed, rRed);

    // Outputs the values and the checkerboard to the terminal
    std::cout << "Black: " << black << std::endl;
    std::cout << "Red: " << red << std::endl;
    checkerBoard(chessBoard);
    std::cout << "<----------------------->" <<std::endl;

    return {black, red};
}

// Runs the first time the board is detected and finds the orientation of the board
std::vector<Vec3b> firstLoop(std::vector<cv::Point2f>& newCorners, cv::Mat firstLoop, std::vector<std::vector<std::string>>& chessBoard, std::vector<cv::Point2f>& calibrate, double& pixToMeters, double& boardSize){
    // Detects the circles and the chessboard corners
    std::vector<std::vector<Vec3f>> circlesAndColors = detectAndDrawCentersOfCircles(firstLoop);
    std::vector<cv::Point2f> allAxis = detectAndDrawChessboardCorners(firstLoop, pixToMeters, boardSize);
    calibrate = calibrationCircles(circlesAndColors);

    // Startup variables
    std::vector<std::vector<double>> circleChecked;
    std::vector<Vec3f> circles = circlesAndColors[0];
    std::vector<Vec3f> colors = circlesAndColors[1];
    int checkLoop = 0;

    newCorners = newChessCorners(allAxis[0], allAxis[2], allAxis[3]);

    while(1){
        // Boolean variables that checks if the orientation of the board is correct
        bool orego = false;
        bool xaxis = false;
        bool yaxis = false;

        // Keeps count of how many circles are removed since they are outside the board
        int remove = 0;

        // The first time it loops through all circles and removes the ones that are outside the board
        if(checkLoop == 0){
            for (int i = 0; i < circles.size()+remove; i++) {
                circleChecked.push_back(findCoordInFrame(newCorners, cv::Point2f(circles[i-remove][0]*pixToMeters, circles[i-remove][1]*pixToMeters)));
                if((circleChecked[i-remove][0] > -0.02) && (circleChecked[i-remove][0] < 0.242) && (circleChecked[i-remove][1] > -0.02) && (circleChecked[i-remove][1] < 0.242)){
                    continue;
                }
                circleChecked.erase(std::next(circleChecked.begin(), i-remove));
                circles.erase(std::next(circles.begin(), i-remove));
                colors.erase(std::next(colors.begin(), i-remove));
                remove++;
            }
            // The other times it only checks the circles that are inside the board
        } else {
            circleChecked = {};
            for (int i = 0; i < circles.size(); ++i) {
                circleChecked.push_back(findCoordInFrame(newCorners, cv::Point2f(circles[i][0]*pixToMeters, circles[i][1]*pixToMeters)));
            }
        }

        // Checks if the circle is located at the origin, the x-axis or the y-axis
        for (int i = 0; i < circleChecked.size(); i++) {
            if(-0.005 < circleChecked[i][0] && 0.005 > circleChecked[i][0] && -0.005 < circleChecked[i][1] && 0.005 > circleChecked[i][1]){
                orego = true;
                break;
            } else if (0.205 < circleChecked[i][0] && 0.215 > circleChecked[i][0] && -0.005 < circleChecked[i][1] && 0.005 > circleChecked[i][1]){
                yaxis = true;
                break;
            } else if (-0.005 < circleChecked[i][0] && 0.005 > circleChecked[i][0] && 0.205 < circleChecked[i][1] && 0.215 > circleChecked[i][1]){
                xaxis = true;
                break;
            }
        }

        // Breaks the loop if the orientation is correct
        if(orego){
            break;
        } else if(xaxis){
            newCorners = newChessCorners(allAxis[1], allAxis[0], allAxis[2]);
            std::cout << "Koordinatsystemet er nu vendt" << std::endl;
        } else if(yaxis){
            newCorners = newChessCorners(allAxis[2], allAxis[3], allAxis[1]);
            std::cout << "Koordinatsystemet er nu vendt" << std::endl;
        }
        checkLoop++;
    }
    return startBoard(circleChecked, colors, chessBoard);
}

// Runs the loop that detects the checker pieces on the board
std::vector<std::string> boardLoop(cv::Vec3b black, cv::Vec3b red, std::vector<cv::Point2f> newCorners, cv::Mat img, std::vector<std::vector<std::string>>& chessBoard, int playerTurn, double pixToMeters){
    // Startup variables
    std::vector<std::vector<double>> circleChecked;
    std::vector<std::vector<Vec3f>> colorsAndCircles;
    std::vector<Vec3f> circles;
    std::vector<Vec3f> colors;
    std::vector<std::vector<std::string>> prevBoard = chessBoard;
    int count = 0;
    int tolerance = 10;

    while(count > 24){
        // Detects the circles and their colors in the img
        colorsAndCircles = detectAndDrawCentersOfCircles(img);

        // Resets the variables
        count = 0;
        circleChecked = {};
        circles = colorsAndCircles[0];
        colors = colorsAndCircles[1];
        int remove = 0;

        // Removes the circles that are outside the board
        for(int i = 0; i < circles.size()+remove; i++) {
            circleChecked.push_back(findCoordInFrame(newCorners, cv::Point2f(circles[i-remove][0]*pixToMeters, circles[i-remove][1]*pixToMeters)));
            if((circleChecked[i-remove][0] > -0.02) && (circleChecked[i-remove][0] < 0.242) && (circleChecked[i-remove][1] > -0.02) && (circleChecked[i-remove][1] < 0.242)){
                continue;
            }
            circleChecked.erase(std::next(circleChecked.begin(), i-remove));
            circles.erase(std::next(circles.begin(), i-remove));
            colors.erase(std::next(colors.begin(), i-remove));
            remove++;
        }

        // Prints a new board with the checker pieces by iterating through the board and checking the color of the checker pieces
        chessBoard = {};
        for(int i = 0; i < 8; i++){
            if(i%2 == 0){
                chessBoard.push_back({"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "});
            } else {
                chessBoard.push_back({"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "});
            }
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < circleChecked.size(); k++) {
                    // If the circle is within the boundaries of the expected location of the checker piece then the color is checked
                    if(((circleChecked[k][0] - 0.005) <  (j*0.03)) && ((circleChecked[k][0] + 0.005) > (j*0.03)) && ((circleChecked[k][1] - 0.005) < (i*0.03)) && ((circleChecked[k][1] + 0.005) > (i*0.03))){
                        // If the color of the circle is within the tolerance of the color of a black or red checker piece then the checker piece is placed on the board
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

    // Prints the new board to the terminal
    checkerBoard(chessBoard);
    std::cout << "<----------------------->" <<std::endl;

    // Returns the start and end position of the player's move by comparing the new board with the previous board
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
