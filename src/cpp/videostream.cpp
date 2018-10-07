/*
    Copyright (C) 2018, by Christopher F. Moran and Emergent Technology
    This is original work contains products developed by other organisations
    including, but not limited to:
    OpenCV

    This was originally written for the Raspberry Pi, but I am gradually
    adapting it to the NanoPC T4 from FriendlyArm.  Mostly because the
    WiringNP library they wrote doesn't work with the RockChip-based board
*/
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <errno.h>
#ifdef _HAS_SERIAL
#include <wiringSerial.h>
#endif
#ifdef _HAS_WIRING
#include <wiringPi.h>
#endif
#include "videostream.h"
#ifdef _HAS_MQTT
#include "mosquitto.h"
#endif

using namespace cv;
using namespace std;

#ifdef _HAS_MQTT
struct mosquitto *mosq = NULL;
bool clean_session = true;
#endif

int main(int, char**)
{
	char msgBuf[2048];
        int com = 0;
        
        // Set up WiringPi GPIO support
        // Use ...SetupSys() instead of ...Setup() so we don't need root
#ifdef _HAS_WIRING        
        wiringPiSetupSys();
        pinMode(US_INPUT, INPUT);
#endif        

#ifdef _HAS_SERIAL
        com = serialOpen("/dev/ttyAMA0", 115200);
        if(com == -1)
        {
                printf("Error %d opening serial line\n", errno);
                return -1;
        }
#endif
        Mat frame, frame1;
        //--- INITIALIZE VIDEOCAPTURE
        VideoCapture cap;
        // open the default camera using default API
        cap.open(0);
        // OR advance usage: select any API backend
        int deviceID = 0;             // 0 = open default camera
        int apiID = cv::CAP_ANY;      // 0 = autodetect default API
        // open selected camera using selected API
        //cap.open(deviceID + apiID);

        // check if we succeeded
        if (!cap.isOpened())
        {
                cerr << "ERROR! Unable to open camera\n";
                return -1;
        }
        cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        
        int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        
        //--- GRAB AND WRITE LOOP
        cout << "Start grabbing" << endl
                << "Press any key to terminate" << endl;
        for (;;)
        {
#ifdef _HAS_WIRING                
                // Check and see if we have an obstruction first
                if(digitalRead(US_INPUT) == LOW)
#else
                if(1)
#endif                                
                {
                        // wait for a new frame from camera and store it into 'frame'
                        cap.read(frame);
                        // check if we succeeded
                        if (frame.empty())
                        {
                                cerr << "ERROR! blank frame grabbed\n";
                                break;
                        }
#ifdef _HAS_GUI
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
                        grid.push_back(Rect(Point(0, frame.rows - 200), Point(frame.cols, frame.rows - 150)));   //Rectangle bottom
                        grid.push_back(Rect(Point(160, frame.rows - 300), Point(480, frame.rows - 250)));   //Rectangle top
                        grid.push_back(Rect(Point(0, frame.rows - 300), Point(160, frame.rows - 250)));   //Rectangle left top
                        grid.push_back(Rect(Point(480, frame.rows - 300), Point(640, frame.rows - 250)));   //Rectangle right top
//#ifdef _HAS_GUI
//                        imshow("Processed", frame1);
//#endif
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
                        float h2 = frame.rows / 2.0f;
                        float k = (w2 - x) / w2 * 2;
                        int speed = 35;
                        int vr = speed;
                        int vl = speed;
                        
                        if (k >= 0)
                                vl = (1 - fabs(k)) * speed;
                        else
                                (1 - fabs(k)) * speed;
#ifndef _HAS_MQTT
                        printf("w2=%4.1f h2=%4.1f x=%f k=%f vl=%d vr=%d\n", w2, h2, x, k, vl, vr);
#endif
#ifdef _HAS_MQTT
			mosquitto_lib_init();
			mosq = mosquitto_new(NULL, clean_session, NULL);
			if(!mosq)
			{
				printf("Out of memory!\n");
			}
			else
			{
				if(mosquitto_connect(mosq,
						"barry.emergent.tld",
						1883,
						1)!= 0)
				{
					printf("Error connecting to broker\n");
				}
				else
				{
					sprintf(msgBuf, "{\"w2\":\"%4.1f\",\"h2\":\"%4.1f\",\"x\":\"%f\",\"k\":\"%f\",\"vl\":\"%d\",\"vr\":\"%d\"}", w2, h2, x, k, vl, vr);
					mosquitto_publish(mosq,
							0,
							"data/video",
							strlen(msgBuf),
							msgBuf,
							0,
							false);
					mosquitto_disconnect(mosq);
				}
			}
			mosquitto_lib_cleanup();
#endif
#ifdef _HAS_GUI
                        rectangle(frame, grid[0], Scalar( 255, 255, 255), 2, 8); //bottom
                        rectangle(frame, grid[1], Scalar( 255, 0, 0), 2, 8); //top
                        rectangle(frame, grid[2], Scalar( 0, 0, 255), 2, 8); //left
                        rectangle(frame, grid[3], Scalar( 0, 0, 255), 2, 8); //right
                        
                        circle(frame, Point(xLeft, frame.rows - 250 - yLeft), 10, Scalar(0, 0, 255), 3, 8); //left
                        circle(frame, Point(xRight + 480, frame.rows - 250 - yRight), 10, Scalar(0, 0, 255), 3, 8); //right
                        circle(frame, Point(x + 100, frame.rows - 150 - y), 10, Scalar( 255, 255, 255), 3, 8); //bottom
                        circle(frame, Point(x2 + 160, frame.rows - 250 - y2), 10, Scalar( 0, 255, 0), 3, 8); //top
                        namedWindow( "Live", WINDOW_AUTOSIZE );
                        imshow("Live", frame);
#endif

#ifdef _HAS_SERIAL
                        // Send the command to our steering controller
                        if (k > 0)
                        {
                                serialPutchar(com, '.');
                        }
                        else if (k < 0)
                        {
                                serialPutchar(com, ',');
                        }
                        serialPutchar(com, 'f');        // Move
                        serialPutchar(com, 'p');        // Look for an obstacle
#endif
                }
                else
                {
                        printf("Wait for obstacle\n");
                        // See if it has cleared yet
#ifdef _HAS_SERIAL                        
                        serialPutchar(com, 'p');
#endif                        
                }
        }
        // the camera will be deinitialized automatically in VideoCapture destructor
        return 0;
}
