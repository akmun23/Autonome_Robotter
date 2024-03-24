    #ifndef GUI_H
    #define GUI_H

    #include <vector>
    #include <opencv2/opencv.hpp>
    #include <opencv2/highgui.hpp>
    #include <opencv2/imgproc.hpp>
    #include <opencv2/core.hpp>
    #include <string>

    using namespace cv;
    using namespace std;

    //Circle inherites methods and attribute templates from "Rect"
    class Circle : public Rect{
        using Rect::Rect; //Inherites constructor from "Rect"
    };

    class GUI
    {
        vector<Circle> bCheckers; //Vec consisting of instances of "Circle" for black checkers.
        vector<Circle> rCheckers; //Vec consisting of instances of "Circle" for red checkers.
        vector<Rect> rectangles; //Vec consisting of instances of "Rect", as segments of board.
        vector<int> selected; //Vec consisting of INT, that refer to information of selected Rect.
        vector<string> stringPos; //Vec consisting of selected positions.
        Mat graveyardDownSized;
        std::string winName; //String, used as window name.
        int turnVal = 0; //Array containing INT representing how many turns have been taken.
        bool startUpMain = true; //Bool, true if code is being run for the first time.
        int redCheckers = 12; //Start amount of red checker pieces.
        int blackCheckers = 12; //Start amount of black checker pieces.
        bool jumpPerformed;
        bool startJump;
        int currentChecker;
        string pos;
        int playerTurn = 2;
        std::vector<std::vector<std::string>> boards;
        std::vector<std::string> movesPossible;
        bool moreMove;
        std::vector<std::string> jumpsPossible;
        Rect graveyardRect;

    public:
        Mat3b canvas; //Mat3b, used as canvas.
        GUI(const string& winName); //Constructor for GUI.
        void clearVecInt(vector<int>& vec);
        void clearVecString(vector<string>& vector);
        void updateText();
        int findInVector(string input[], string wantFound);
        void posToStringConvert(int x, int y);
        void Draw();
        bool doesRectContainChecker(int x, int y, vector<Circle> enemyCheckerVec);
        bool doesPosContainRect(int x, int y);
        bool isJumpPossible(int x, int y, vector<Circle> enemyCheckerVec);
        bool isGameWon(vector<Circle> enemyCheckerVec, int playerTurn);
        void setJumpPerformed(bool& jumpPerformed, bool TrueFalse);
        static void mouseCallBack(int event, int userX, int userY, int flags, void* userdata);
        void callBackFunc(int event, int userX, int userY, int flags, void* userdata);
    };

    #endif // GUI_H
