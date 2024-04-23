#include "vision.h"

Vision::Vision(){}

Vision::Vision(char** argv):_argv(argv){

}

void Vision::detectAndDrawCentersOfCircles(){
    _circles = {};
    _colors = {};
    //![convert_to_gray]
    cv::Mat gray;
    cv::cvtColor(_src, gray, cv::COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    cv::medianBlur(gray, gray, 1);
    //![reduce_noise]

    //![houghcircles]
    cv::HoughCircles(gray, _circles, cv::HOUGH_GRADIENT, 1,
                 gray.rows/100,  // change this value to detect circles with different distances to each other
                 110, 25, 5, 20 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
                 );
    //![houghcircles]

    //![draw]
    for(int i = 0; i < _circles.size(); i++ ){
        cv::Vec3i c = _circles[i];
        cv::Point center = cv::Point(c[0], c[1]);
        _colors.push_back(_src.at<cv::Vec3b>(center));
        // circle center
        circle(_src, center, 1, cv::Scalar(0,100,100), 3, cv::LINE_AA);
        // circle outline
        int radius = c[2];
        circle(_src, center, radius+2, cv::Scalar(0,0,0), -1, cv::LINE_AA);
    }
}

void Vision::detectAndDrawChessboardCorners() {
    std::vector<cv::Point2f> corners; // Array will be filled by the detected corners
    for (int i = 0; i < 1; i++){
        cv::Size patternsize(7,7); // The interior number of corners in a checkers board
        cv::Mat gray;
        cvtColor(_src, gray, cv::COLOR_BGR2GRAY);

        //CALIB_CB_FAST_CHECK saves a lot of time on images (Removed for better accuracy)
        bool patternfound = findChessboardCorners(gray, patternsize, corners, 0 +
                            cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE
                            + cv::CALIB_CB_FILTER_QUADS);
        if(patternfound){
            cornerSubPix(gray, corners, cv::Size(11, 11), cv::Size(-1, -1),
                         cv::TermCriteria(cv::TermCriteria::MAX_ITER|cv::TermCriteria::EPS, 30, 0.1));
        } // Subpixels are also considered increasing accuracy

        // Define the offset of where the table the checkers board can be placed on starts. Also the scale of cm per pixel. These have to be defined when camera is set up.
        _pixToMeters = ((0.03*6) / sqrt(pow((corners[6].x - corners[0].x),2) + pow((corners[6].y - corners[0].y),2)));
        std::cout << "PixToMeters: " << _pixToMeters << std::endl;

        // Corners is redefined with coordinates in m instead of pixels.
        for(int i = 0; i <= corners.size(); i++){
            corners[i].x = (corners[i].x)* _pixToMeters;
            corners[i].y = (corners[i].y) * _pixToMeters;
        }

        // Draw the corners of the board and offset
        int exponent = 2;
        _boardSize = sqrt((pow(corners[1].x - corners[0].x,exponent)) + (pow(corners[1].y - corners[0].y,exponent)));

        // The length of the individual squares of the board are calculated to calibrate the game program.
        std::cout << "Boardsize: " << _boardSize << std::endl;
    }
    _axis = {corners[0], corners[6], corners[42], corners[48]};
}

// Calculates the unit vectors for the x and y axis
void Vision::calcUnitVec2D(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis){
    // Calculates the vectors for the x and y axis
    std::vector<double> vec1 = {xaxis.x - orego.x, xaxis.y - orego.y};
    std::vector<double> vec2 = {yaxis.x - orego.x, yaxis.y - orego.y};

    // Calculates the length of the vectors
    double length1 = sqrt(pow(vec1[0], 2) + pow(vec1[1], 2));
    double length2 = sqrt(pow(vec2[0], 2) + pow(vec2[1], 2));

    // Calculates the unit vectors for the x and y axis
    _unit1 = {(vec1[0] / length1), (vec1[1] / length1)};
    _unit2 = {(vec2[0] / length2), (vec2[1] / length2)};
}

// Shifts the corners to the middle of the checker pieces instead of the inner corner
void Vision::newChessCorners(cv::Point2f yaxis, cv::Point2f orego, cv::Point2f xaxis){
    double move = 0.015;
    // Calculates the unit vectors for the x and y axis
    calcUnitVec2D(yaxis, orego, xaxis);

    // Moves the pieces 1.5 cm
    _newCorners[1] = cv::Point2f(orego.x + (-move * _unit1[0] - move * _unit2[0]), orego.y + (-move * _unit1[1] - move * _unit2[1]));
    _newCorners[0] = cv::Point2f(xaxis.x + ( move * _unit1[0] - move * _unit2[0]), xaxis.y + ( move * _unit1[1] - move * _unit2[1]));
    _newCorners[2] = cv::Point2f(yaxis.x + (-move * _unit1[0] + move * _unit2[0]), yaxis.y + (-move * _unit1[1] + move * _unit2[1]));
}

// Finds the coordinates for the circles in the given coordinate frame
std::vector<double> Vision::findCoordInFrame(cv::Point2f varpoint){
    // Calculates the new coordinates for the circle
    double newPointx = ((varpoint.x-_newCorners[1].x)*_unit1[0] + (varpoint.y-_newCorners[1].y)*_unit1[1]);
    double newPointy = ((varpoint.x-_newCorners[1].x)*_unit2[0] + (varpoint.y-_newCorners[1].y)*_unit2[1]);

    return {newPointx, newPointy};
}

void Vision::cameraFeed(){
    //read video
    std::string path;
    cv::VideoCapture capture;
    capture.open("/dev/video2", cv::CAP_V4L2);
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    double dWidth = capture.get(cv::CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = capture.get(cv::CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    std::cout << "camera width = " << dWidth << ", height = " << dHeight << std::endl;

    if (!capture.isOpened()) { //check if video device has been initialised
        std::cout << "cannot open camera";
    }

    cv::Mat frame;

    std::string dir = _argv[0];
    int index = 0;
    while (true)
    {
        bool bSuccess = capture.read(frame); // read a new frame from video

        //Breaking the while loop if the frames cannot be captured
        if (bSuccess == false)
        {
            std::cout << "Video camera is disconnected" << std::endl;
            break;
        }

        //show the frame in the created window
        // imshow("video", frame);

        path = dir + std::to_string(0) + ".jpg";
        imwrite(path, frame);

        //wait for for 10 ms until any key is pressed.
        //If the 'Esc' key is pressed, break the while loop.
        //If the any other key is pressed, continue the loop
        //If any key is not pressed withing 10 ms, continue the loop
        usleep(100);
        index++;
        if (index == 10){
            break;
        }
    }
    _src = cv::imread(path);
}

// Finds the coordinates for the three calibration circles
void Vision::calibrationCircles(){
    // Preset values for the three calibration circles
    cv::Vec3b green = {175, 223, 210};
    cv::Vec3b yellow = {130, 220, 235};
    cv::Vec3b magenta = {200, 138, 190};
    bool greenFound = false;
    bool yellowFound = false;
    bool magentaFound = false;
    int i = 0;
    while(!greenFound || !yellowFound || !magentaFound){
        if(i > 0){
            cameraFeed();
            detectAndDrawCentersOfCircles();

            greenFound = false;
            yellowFound = false;
            magentaFound = false;
        }

        // Stores the coordinates of the three calibration circles
        _greenFunc = {0, 0};
        _yellowFunc = {0, 0};
        _magentaFunc = {0, 0};

        // Tolerance for the color detection
        int tolerance = 25;

        // Finds the coordinates of the three calibration circles by iterating through all the detected circles
        for (int k = 0; k < _circles.size(); k++) {
            if((green[0]-tolerance < _colors[k][0]) && (green[0]+tolerance > _colors[k][0]) && (green[1]-tolerance < _colors[k][1]) && (green[1]+tolerance > _colors[k][1]) && (green[2]-tolerance < _colors[k][2]) && (green[2]+tolerance > _colors[k][2])){
                _greenFunc = {_circles[k][0], _circles[k][1]};
                greenFound = true;
            } else if((yellow[0]-tolerance < _colors[k][0]) && (yellow[0]+tolerance > _colors[k][0]) && (yellow[1]-tolerance < _colors[k][1]) && (yellow[1]+tolerance > _colors[k][1]) && (yellow[2]-tolerance < _colors[k][2]) && (yellow[2]+tolerance > _colors[k][2])){
                _yellowFunc = {_circles[k][0], _circles[k][1]};
                yellowFound = true;
            } else if((magenta[0]-tolerance < _colors[k][0]) && (magenta[0]+tolerance > _colors[k][0]) && (magenta[1]-tolerance < _colors[k][1]) && (magenta[1]+tolerance > _colors[k][1]) && (magenta[2]-tolerance < _colors[k][2]) && (magenta[2]+tolerance > _colors[k][2])){
                _magentaFunc = {_circles[k][0], _circles[k][1]};
                magentaFound = true;
            }
        }
        i++;
    }
}

// Finds the colors of the checker pieces on the board
void Vision::startBoard(){
    // Values are saved as BGR in OpenCV
    double bBlack = 0;
    double gBlack = 0;
    double rBlack = 0;
    double bRed = 0;
    double gRed = 0;
    double rRed = 0;
    cv::Vec3b black = {0, 0, 0};
    cv::Vec3b red = {0, 0, 0};
    _boards = {};

    // Iterates through the board and checks the color of the checker pieces
    // Also outputs the placement of the checker pieces
    for(int i = 0; i < 8; i++){
        if(i%2 == 0){
            _boards.push_back({"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "});
        } else {
            _boards.push_back({"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "});
        }
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < _circleChecked.size(); k++) {
                // Checks if the circle is within the boundaries of the expected location of the checker piece
                if(((_circleChecked[k][0] - 0.012) <  (j*0.03)) && ((_circleChecked[k][0] + 0.012) > (j*0.03) && ((_circleChecked[k][1] - 0.012) < (i*0.03)) && ((_circleChecked[k][1] + 0.012) > (i*0.03)))){
                    // If the piece is located at the black end of the board then the value is saved as the color of a black piece else it is stored as the color of a red piece
                    if(_circleChecked[k][1] < 0.1){
                        _boards[i][7-j] = "B ";
                        bBlack += _colors[k][0];
                        gBlack += _colors[k][1];
                        rBlack += _colors[k][2];
                    } else if(_circleChecked[k][1] > 0.14){
                        _boards[i][7-j] = "R ";
                        bRed += _colors[k][0];
                        gRed += _colors[k][1];
                        rRed += _colors[k][2];
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
    _black = cv::Vec3b(bBlack, gBlack, rBlack);
    _red = cv::Vec3b(bRed, gRed, rRed);

    // Outputs the values and the checkerboard to the terminal
    std::cout << "Black: " << _black << std::endl;
    std::cout << "Red: " << _red << std::endl;
    checkerBoard(_boards);
    std::cout << "<----------------------->" <<std::endl;
}

// Runs the first time the board is detected and finds the orientation of the board
void Vision::firstLoop(){
    // Detects the circles and the chessboard corners
    calibrationCircles();

    _circles = {};
    _colors = {};

    cameraFeed();
    detectAndDrawCentersOfCircles();
    detectAndDrawChessboardCorners();

    // Startup variables
    int checkLoop = 0;

    newChessCorners(_axis[0], _axis[2], _axis[3]);

    while(1){
        // Boolean variables that checks if the orientation of the board is correct
        bool orego = false;
        bool xaxis = false;
        bool yaxis = false;

        // Keeps count of how many circles are removed since they are outside the board
        int remove = 0;

        // The first time it loops through all circles and removes the ones that are outside the board
        if(checkLoop == 0){
            while(1){
                for (int i = 0; i < _circles.size()+remove; i++) {
                    _circleChecked.push_back(findCoordInFrame(cv::Point2f(_circles[i-remove][0]*_pixToMeters, _circles[i-remove][1]*_pixToMeters)));
                    if((_circleChecked[i-remove][0] > -0.02) && (_circleChecked[i-remove][0] < 0.225) && (_circleChecked[i-remove][1] > -0.02) && (_circleChecked[i-remove][1] < 0.225)){
                        continue;
                    }
                    _circleChecked.erase(std::next(_circleChecked.begin(), i-remove));
                    _circles.erase(std::next(_circles.begin(), i-remove));
                    _colors.erase(std::next(_colors.begin(), i-remove));
                    remove++;
                }
                if(_circleChecked.size() != 24){
                    cameraFeed();
                    detectAndDrawCentersOfCircles();
                    detectAndDrawChessboardCorners();
                    std::cout << "Only " << _circleChecked.size() << "circles detected. Trying new picture" << std::endl;
                    _circleChecked = {};
                } else {
                    break;
                }
            }
        } else { // The other times it only checks the circles that are inside the board
            _circleChecked = {};
            for (int i = 0; i < _circles.size(); ++i) {
                _circleChecked.push_back(findCoordInFrame(cv::Point2f(_circles[i][0]*_pixToMeters, _circles[i][1]*_pixToMeters)));
            }
        }

        // Checks if the circle is located at the origin, the x-axis or the y-axis
        for (int i = 0; i < _circleChecked.size(); i++) {
            if(-0.005 < _circleChecked[i][0] && 0.005 > _circleChecked[i][0] && -0.005 < _circleChecked[i][1] && 0.005 > _circleChecked[i][1]){
                orego = true;
                break;
            } else if (0.2 < _circleChecked[i][0] && 0.225 > _circleChecked[i][0] && -0.005 < _circleChecked[i][1] && 0.005 > _circleChecked[i][1]){
                yaxis = true;
                break;
            } else if (-0.005 < _circleChecked[i][0] && 0.005 > _circleChecked[i][0] && 0.2 < _circleChecked[i][1] && 0.225 > _circleChecked[i][1]){
                xaxis = true;
                break;
            }
        }

        // Breaks the loop if the orientation is correct
        if(orego){
            break;
        } else if(xaxis){
            newChessCorners(_axis[1], _axis[0], _axis[2]);
            std::cout << "Koordinatsystemet er nu vendt" << std::endl;
        } else if(yaxis){
            newChessCorners(_axis[2], _axis[3], _axis[1]);
            std::cout << "Koordinatsystemet er nu vendt" << std::endl;
        }
        checkLoop++;
    }

    startBoard();
}

// Runs the loop that detects the checker pieces on the board
std::vector<std::string> Vision::boardLoop(std::vector<std::vector<std::string>> chessBoard, int playerTurn){
    // Startup variables
    std::vector<std::vector<std::string>> prevBoard = chessBoard;
    int count = 99;
    int tolerance = 40;

    while(count > 24){
        cameraFeed();
        // Detects the circles and their colors in the img
        detectAndDrawCentersOfCircles();

        // Resets the variables
        count = 0;
        _circleChecked = {};
        int remove = 0;

        // Removes the circles that are outside the board
        for(int i = 0; i < _circles.size()+remove; i++) {
            _circleChecked.push_back(findCoordInFrame(cv::Point2f(_circles[i-remove][0]*_pixToMeters, _circles[i-remove][1]*_pixToMeters)));
            if((_circleChecked[i-remove][0] > -0.02) && (_circleChecked[i-remove][0] < 0.225) && (_circleChecked[i-remove][1] > -0.02) && (_circleChecked[i-remove][1] < 0.225)){
                continue;
            }
            _circleChecked.erase(std::next(_circleChecked.begin(), i-remove));
            _circles.erase(std::next(_circles.begin(), i-remove));
            _colors.erase(std::next(_colors.begin(), i-remove));
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
                for (int k = 0; k < _circleChecked.size(); k++) {
                    // If the circle is within the boundaries of the expected location of the checker piece then the color is checked
                    if(((_circleChecked[k][0] - 0.015) <  (j*0.03)) && ((_circleChecked[k][0] + 0.015) > (j*0.03)) && ((_circleChecked[k][1] - 0.015) < (i*0.03)) && ((_circleChecked[k][1] + 0.015) > (i*0.03))){
                        // If the color of the circle is within the tolerance of the color of a black or red checker piece then the checker piece is placed on the board
                        if((_black[0]-tolerance < _colors[k][0]) && (_black[0]+tolerance > _colors[k][0]) && (_black[1]-tolerance < _colors[k][1]) && (_black[1]+tolerance > _colors[k][1]) && (_black[2]-tolerance < _colors[k][2]) && (_black[2]+tolerance > _colors[k][2])){
                            chessBoard[i][7-j] = "B ";
                            count++;
                        } else if((_red[0]-tolerance < _colors[k][0]) && (_red[0]+tolerance > _colors[k][0]) && (_red[1]-tolerance < _colors[k][1]) && (_red[1]+tolerance > _colors[k][1]) && (_red[2]-tolerance < _colors[k][2]) && (_red[2]+tolerance > _colors[k][2])){
                            chessBoard[i][7-j] = "R ";
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
    std::string checkPiece2;
    if(playerTurn == 1){
        checkPiece = "B ";
        checkPiece2 = "BK";
    } else {
        checkPiece = "R ";
        checkPiece2 = "RK";
    }
    for (int i = 0; i < chessBoard.size(); ++i) {
        for (int j = 0; j < chessBoard[0].size(); ++j) {
            if (prevBoard[i][j] != chessBoard[i][j]){
                if(prevBoard[i][j] == checkPiece2 && chessBoard[i][j] == checkPiece){
                    continue;
                } else if(prevBoard[i][j] == checkPiece || prevBoard[i][j] == checkPiece2){
                    row = i;
                    column = j;
                } else if(chessBoard[i][j] == checkPiece){
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

std::vector<cv::Point2f> Vision::getCalibrate(){
    return {_magentaFunc, _greenFunc, _yellowFunc};
}

double Vision::getPixToMeters(){
    return _pixToMeters;
}

double Vision::getBoardsize(){
    return _boardSize;
}

std::vector<cv::Point2f> Vision::getNewCorners(){
    return _newCorners;
}

std::vector<std::vector<std::string>> Vision::getBoard(){
    return _boards;
}

void Vision::setArguments(char** argv){
    _argv = argv;
}
