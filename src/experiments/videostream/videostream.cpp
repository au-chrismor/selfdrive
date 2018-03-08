/**
  @file videocapture_basic.cpp
  @brief A very basic sample for using VideoCapture and VideoWriter
  @author PkLab.net
  @date Aug 24, 2016
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int, char**)
{
    Mat frame, frame1;
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // open the default camera using default API
    //cap.open(0);
    // OR advance usage: select any API backend
    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID + apiID);
    // check if we succeeded
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
#ifdef _GUI        
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
#endif
        // Break the image down to something usable
        cvtColor(frame, frame1, CV_BGR2GRAY);
        equalizeHist(frame1, frame1);
        GaussianBlur(frame1, frame1, Size( 5, 5 ), 0, 0 );
        threshold(frame1, frame1, 125, 255, THRESH_BINARY);
        cv::erode(frame1, frame1, Mat());
        cv::erode(frame1, frame1, Mat());

        std::vector<Rect> grid;
#ifdef _GUI
        grid.push_back(Rect(Point(0, frame.rows - 200), Point(frame.cols, frame.rows - 150)));   //Rectangle bottom
        grid.push_back(Rect(Point(160, frame.rows - 300), Point(480, frame.rows - 250)));   //Rectangle top
        grid.push_back(Rect(Point(0, frame.rows - 300), Point(160, frame.rows - 250)));   //Rectangle left top
        grid.push_back(Rect(Point(480, frame.rows - 300), Point(640, frame.rows - 250)));   //Rectangle right top
        imshow("Processed", frame1);
#endif
        Moments m = moments(frame1(grid[0]), false);   //layer bottom
        float x = m.m10 / m.m00;
        float y = m.m01 / m.m00;

        Moments m2 = moments(frame1(grid[1]), false);    //layer top
        float x2 = m2.m10 / m2.m00;
        float y2 = m2.m01 / m2.m00;

        Moments mLeft = moments(frame1(grid[2]), false);   //left
        float xLeft = mLeft.m10 / mLeft.m00;
        float yLeft = mLeft.m01 / mLeft.m00;

        Moments mRight = moments(frame1(grid[3]), false);   //right
        float xRight = mLeft.m10 / mLeft.m00;
        float yRight = mLeft.m01 / mLeft.m00;

        float w2 = frame.cols / 2.0f;
        float k = (w2 - x) / w2 * 2;
        int speed = 35;
        int vr = speed;
        int vl = speed;

        if (k >= 0)
            vl = (1 - fabs(k)) * speed;
        else
            vr = (1 - fabs(k)) * speed;

#ifdef _GUI
        rectangle(frame, grid[0], Scalar( 255, 0, 0), 2, 8); //bottom
        rectangle(frame, grid[1], Scalar( 255, 0, 0), 2, 8); //top
        rectangle(frame, grid[2], Scalar( 0, 0, 255), 2, 8); //left
        rectangle(frame, grid[3], Scalar( 0, 0, 255), 2, 8); //right

        circle(frame, Point(xLeft, frame.rows - 250 - yLeft), 10, Scalar( 0,0, 255), 3, 8); //left
        circle(frame, Point(xRight + 480, frame.rows - 250 - yRight), 10, Scalar( 0,0, 255), 3, 8); //right
        circle(frame, Point(x + 100, frame.rows - 150 - y), 10, Scalar( 255, 0, 0), 3, 8); //bottom
        circle(frame, Point(x2 + 160, frame.rows - 250 - y2), 10, Scalar( 0, 255, 0), 3, 8); //top
#endif
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}