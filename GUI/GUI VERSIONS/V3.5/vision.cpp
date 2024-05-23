#include "vision.h"

Vision::Vision(){}

Vision::Vision(char** argv):_argv(argv){

}

void Vision::detectAndDrawCentersOfCircles(){
    _circles.clear();
    _colors.clear();
    //![convert_to_gray]
    cv::Mat gray;
    cv::cvtColor(_src, gray, cv::COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    cv::medianBlur(gray, gray, 1);
    //![reduce_noise]

    //![houghcircles]
    cv::HoughCircles(gray, _circles, cv::HOUGH_GRADIENT_ALT, 1,
                     (gray.rows)/100,  // change this value to detect circles with different distances to each other
                     300, 0.8, 5, 25 // change the last two parameters
                     // (min_radius & max_radius) to detect larger circles
                     );
    //![houghcircles]

    //![draw]
    for(int i = 0; i < _circles.size(); i++ ){
        _colors.push_back(_src.at<cv::Vec3b>(cv::Point(_circles[i][0], _circles[i][1])));
        // circle outline
        circle(_src, cv::Point(_circles[i][0], _circles[i][1]), _circles[i][2]+2, cv::Scalar(0,0,0), -1, cv::LINE_AA);
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
        _pixToMeters = ((_boardSize*6) / sqrt(pow((corners[6].x - corners[0].x),2) + pow((corners[6].y - corners[0].y),2)));
        std::cout << "PixToMeters: " << _pixToMeters << std::endl;

        // Corners is redefined with coordinates in m instead of pixels.
        for(int i = 0; i < corners.size(); i++){
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
    Vision::calcUnitVec2D(yaxis, orego, xaxis);

    // Moves the pieces 1.5 cm
    _newCorners[1] = cv::Point2f(orego.x + (-move * _unit1[0] - move * _unit2[0]), orego.y + (-move * _unit1[1] - move * _unit2[1]));
    _newCorners[0] = cv::Point2f(xaxis.x + ( move * _unit1[0] - move * _unit2[0]), xaxis.y + ( move * _unit1[1] - move * _unit2[1]));
    _newCorners[2] = cv::Point2f(yaxis.x + (-move * _unit1[0] + move * _unit2[0]), yaxis.y + (-move * _unit1[1] + move * _unit2[1]));
}

void Vision::findCoordInFrame(cv::Point2f varpoint, int& iterator){
    // Calculates the new coordinates for the circle
    double newPointx = ((varpoint.x-_newCorners[1].x)*_unit1[0] + (varpoint.y-_newCorners[1].y)*_unit1[1]);
    double newPointy = ((varpoint.x-_newCorners[1].x)*_unit2[0] + (varpoint.y-_newCorners[1].y)*_unit2[1]);

    if((newPointx > -0.02) && (newPointx < 0.225) && (newPointy > -0.02) && (newPointy < 0.225)){
        _circleChecked.push_back(cv::Point2f(newPointx, newPointy));        
    } else {
        _circles.erase(_circles.begin()+_circleChecked.size());
        _colors.erase(_colors.begin()+_circleChecked.size());
        iterator++;
    }
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

    // std::cout << "camera width = " << dWidth << ", height = " << dHeight << std::endl;

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
    capture.release();
}

// Finds the coordinates for the three calibration circles
void Vision::calibrationCircles(){
    // Preset values for the three calibration circles
    cv::Vec3b red = {100, 100, 255};
    cv::Vec3b yellow = {160, 255, 255};
    cv::Vec3b blue = {210, 100, 10};
    bool redFound = false;
    bool yellowFound = false;
    bool blueFound = false;
    int i = 0;
    while(!redFound || !yellowFound || !blueFound){
        if(i > 0){
            cameraFeed();
            detectAndDrawCentersOfCircles();

            redFound = false;
            yellowFound = false;
            blueFound = false;;
        }

        // Stores the coordinates of the three calibration circles
        _greenFunc = {0, 0};
        _yellowFunc = {0, 0};
        _magentaFunc = {0, 0};

        // Tolerance for the color detection
        int tolerance = 30;

        // Finds the coordinates of the three calibration circles by iterating through all the detected circles
        for (int k = 0; k < _circles.size(); k++) {
            if((red[0]-tolerance < _colors[k][0]) && (red[0]+tolerance > _colors[k][0]) && (red[1]-tolerance < _colors[k][1]) && (red[1]+tolerance > _colors[k][1]) && (red[2]-tolerance < _colors[k][2]) && (red[2]+tolerance > _colors[k][2])){
                _greenFunc = {_circles[k][0], _circles[k][1]};
                redFound = true;
            } else if((yellow[0]-tolerance < _colors[k][0]) && (yellow[0]+tolerance > _colors[k][0]) && (yellow[1]-tolerance < _colors[k][1]) && (yellow[1]+tolerance > _colors[k][1]) && (yellow[2]-tolerance < _colors[k][2]) && (yellow[2]+tolerance > _colors[k][2])){
                _yellowFunc = {_circles[k][0], _circles[k][1]};
                yellowFound = true;
            } else if((blue[0]-tolerance < _colors[k][0]) && (blue[0]+tolerance > _colors[k][0]) && (blue[1]-tolerance < _colors[k][1]) && (blue[1]+tolerance > _colors[k][1]) && (blue[2]-tolerance < _colors[k][2]) && (blue[2]+tolerance > _colors[k][2])){
                _magentaFunc = {_circles[k][0], _circles[k][1]};
                blueFound = true;
            }
        }
        i++;
    }
}

// Finds the colors of the checker pieces on the board
bool Vision::startBoard(){
    // Values are saved as BGR in OpenCV
    double bBlack = 0;
    double gBlack = 0;
    double rBlack = 0;
    double bRed = 0;
    double gRed = 0;
    double rRed = 0;
    cv::Vec3b black = {0, 0, 0};
    cv::Vec3b red = {0, 0, 0};
    _boards.clear();
    int count = 0;

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
                if(((_circleChecked[k].x - 0.012) <  (j*_boardSize)) && ((_circleChecked[k].x + 0.012) > (j*_boardSize) && ((_circleChecked[k].y - 0.012) < (i*_boardSize)) && ((_circleChecked[k].y + 0.012) > (i*_boardSize)))){
                    // If the piece is located at the black end of the board then the value is saved as the color of a black piece else it is stored as the color of a red piece
                    if(_circleChecked[k].y < (_boardSize*3)){
                        _boards[i][7-j] = "B ";
                        bBlack += _colors[k][0];
                        gBlack += _colors[k][1];
                        rBlack += _colors[k][2];
                        count++;
                    } else if(_circleChecked[k].y > (_boardSize*4)){
                        _boards[i][7-j] = "R ";
                        bRed += _colors[k][0];
                        gRed += _colors[k][1];
                        rRed += _colors[k][2];
                        count++;
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

    if(count < 24){
        std::cout << "Only " << count << " checker pieces detected. Trying new picture" << std::endl;
        return false;
    }
    return true;
}

// Runs the first time the board is detected and finds the orientation of the board
void Vision::firstLoop(){
// Detects the circles and the chessboard corners
    while(1){
        while(1){
            cameraFeed();
            detectAndDrawCentersOfCircles();
            detectAndDrawChessboardCorners();
            calibrationCircles();

            if(_circles.size() < 24 || _circles.empty()){
                std::cout << "Only " << _circles.size() << "circles detected. Trying new picture" << std::endl;
            } else {
                break;
            }
        }

        // Startup variables
        int checkLoop = 0;

        newChessCorners(_axis[0], _axis[2], _axis[3]);

        while(1){
            // Boolean variables that checks if the orientation of the board is correct
            bool orego = false;
            bool xaxis = false;
            bool yaxis = false;

            // The first time it loops through all circles and removes the ones that are outside the board
            if(checkLoop == 0){
                while(1){
                    int iterator = 0;
                    for (int i = 0; i < _circles.size()+iterator; i++) {
                        findCoordInFrame(cv::Point2f(_circles[i-iterator][0]*_pixToMeters, _circles[i-iterator][1]*_pixToMeters), iterator);
                    }
                    if(_circleChecked.size() != 24){
                        cameraFeed();
                        detectAndDrawCentersOfCircles();
                        detectAndDrawChessboardCorners();
                        std::cout << "Only " << _circleChecked.size() << "circles detected. Trying new picture" << std::endl;
                        _circleChecked.clear();
                        iterator = 0;
                    } else {
                        break;
                    }
                }
            } else { // The other times it only checks the circles that are inside the board
                _circleChecked.clear();
                int  iterator = 0;
                for (int i = 0; i < _circles.size(); ++i) {
                    findCoordInFrame(cv::Point2f(_circles[i][0]*_pixToMeters, _circles[i][1]*_pixToMeters), iterator);
                }
            }

            // Checks if the circle is located at the origin, the x-axis or the y-axis
            for (int i = 0; i < _circleChecked.size(); i++) {
                if(-0.0125 < _circleChecked[i].x && 0.0125 > _circleChecked[i].x && -0.0125 < _circleChecked[i].y && 0.0125 > _circleChecked[i].y){
                    orego = true;
                    break;
                } else if (0.2 < _circleChecked[i].x && 0.225 > _circleChecked[i].x && -0.005 < _circleChecked[i].y && 0.005 > _circleChecked[i].y){
                    yaxis = true;
                    break;
                } else if (-0.0125 < _circleChecked[i].x && 0.0125 > _circleChecked[i].x && 0.2 < _circleChecked[i].y && 0.225 > _circleChecked[i].y){
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

        if(startBoard()){
            break;
        }
    }
}

// Runs the loop that detects the checker pieces on the board
std::vector<std::string> Vision::boardLoop(std::vector<std::vector<std::string>> prevBoard, int playerTurn){
    // Startup variables
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

        int iterator = 0;

        for (int i = 0; i < _circles.size()+iterator; i++) {
            findCoordInFrame(cv::Point2f(_circles[i-iterator][0]*_pixToMeters, _circles[i-iterator][1]*_pixToMeters), iterator);
        }


        // Prints a new board with the checker pieces by iterating through the board and checking the color of the checker pieces
        _boards.clear();
        for(int i = 0; i < 8; i++){
            if(i%2 == 0){
                _boards.push_back({"  ", "1 ", "  ", "1 ", "  ", "1 ", "  ", "1 "});
            } else {
                _boards.push_back({"1 ", "  ", "1 ", "  ", "1 ", "  ", "1 ", "  "});
            }
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < _circleChecked.size(); k++) {
                    // If the circle is within the boundaries of the expected location of the checker piece then the color is checked
                    if((_circleChecked[k].x - 0.015) <  (j*_boardSize) && ((_circleChecked[k].x + 0.015) > (j*_boardSize)) && ((_circleChecked[k].y - 0.015) < (i*_boardSize)) && ((_circleChecked[k].y + 0.015) > (i*_boardSize))){
                        // If the color of the circle is within the tolerance of the color of a black or red checker piece then the checker piece is placed on the board
                        if((_black[0]-tolerance < _colors[k][0]) && (_black[0]+tolerance > _colors[k][0]) && (_black[1]-tolerance < _colors[k][1]) && (_black[1]+tolerance > _colors[k][1]) && (_black[2]-tolerance < _colors[k][2]) && (_black[2]+tolerance > _colors[k][2])){
                            _boards[i][7-j] = "B ";
                            count++;
                        } else if((_red[0]-tolerance < _colors[k][0]) && (_red[0]+tolerance > _colors[k][0]) && (_red[1]-tolerance < _colors[k][1]) && (_red[1]+tolerance > _colors[k][1]) && (_red[2]-tolerance < _colors[k][2]) && (_red[2]+tolerance > _colors[k][2])){
                            _boards[i][7-j] = "R ";
                            count++;
                        }
                    }
                }
            }
        }
    }

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
    for (int i = 0; i < _boards.size(); ++i) {
        for (int j = 0; j < _boards[0].size(); ++j) {
            if (prevBoard[i][j] != _boards[i][j]){
                if(prevBoard[i][j] == checkPiece2 && _boards[i][j] == checkPiece){
                    continue;
                } else if(prevBoard[i][j] == checkPiece || prevBoard[i][j] == checkPiece2){
                    row = i;
                    column = j;
                } else if(_boards[i][j] == checkPiece){
                    row2 = i;
                    column2 = j;
                }
            }
        }
    }

    //Turn row into letter and column into number for start position
    std::string columnLetter;
    columnLetter = std::to_string(column+1);
    std::string rowLetter;
    rowLetter = (row + 'a');
    std::string playerStart = rowLetter + columnLetter;

    //Turn row into letter and column into number for end position
    std::string columnLetter2;
    columnLetter2 = std::to_string(column2+1);
    std::string rowLetter2;
    rowLetter2 = (row2 + 'a');
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
