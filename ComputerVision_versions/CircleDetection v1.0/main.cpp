#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    //![load]
    const char* filename = argc >=2 ? argv[1] : "/home/emil/closeup.jpg";

    // Loads an image
    Mat src = imread( samples::findFile( filename ), IMREAD_COLOR );

    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", filename);
        return EXIT_FAILURE;
    }
    //![load]

    //![convert_to_gray]
    int down_width = 1000;
    int down_height = 1300;

    resize(src, src, Size(down_width, down_height), INTER_LINEAR);



    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    medianBlur(gray, gray, 1);
    //![reduce_noise]

    //![houghcircles]
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/30,  // change this value to detect circles with different distances to each other
                 100, 30, 25, 60 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
                 );
    //![houghcircles]


    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);

        cout << center << endl;

    }
    //![draw]


    //![display]
    namedWindow("detected circles", WINDOW_NORMAL);
    imshow("detected circles", src);
    resizeWindow("detected circles", 500, 650);

    waitKey();
    //![display]

    return EXIT_SUCCESS;
}
