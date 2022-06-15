/*
    Gavin Green
    6/15/2022
    https://github.com/Scattercatt/ClickMacro
    gavinr11213@gmail.com

    VRC Pen-Img-Drawer

    This app was a very crude way to be able to take any image and print it out using the cursor. Kinda jank but it works.


*/

#include <windows.h>
#include <iostream>
#include <conio.h>
#include "opencv2/opencv.hpp"
#include <stdint.h>


using namespace std;
using namespace cv;

void moveMouse(long x, long y);
void vrcClickPen(const int sleeptime);
void drive();

int main()
{

    drive();
}

void drive()
{
    string imdir = "nerdemoji.jpg";

    Mat original = imread(imdir, IMREAD_GRAYSCALE);
    Mat modified = imread(imdir, IMREAD_GRAYSCALE);



    for (int r = 0; r < modified.rows; r++)
    {
        for (int c = 0; c < modified.cols; c++)
        {
            if (original.at<uint8_t>(r, c) < 127)
                modified.at<uint8_t>(r, c) = 0;
            else
                modified.at<uint8_t>(r, c) = 255;
        }
    }


    //imshow("Original", original);
    //imshow("Modified", modified);

    cout << "Press enter to generate image." << endl << "REMEMBER: DISABLE ENHANCED POINTER PRECISION!!!";

    cin.get();

    cout << "Activating in 3 seconds...";
    Sleep(3000);
    cout << "Generating image...";

    //Pen click sleep time (Should be 20 for VRC)
    int penSleepTime = 20;

    //Movement sleep time
    int movementSleepTime = 20;

    //Pixel Spacing
    long pS = 3;

    //Original Cursor Position
    POINT cP; GetCursorPos(&cP);
    POINT* cPptr = &cP;
    
    //Last position
    POINT lP;
    POINT* lPptr = &lP;

    *lPptr = *cPptr;

    for (int r = 0; r < modified.rows; r++)
    {
        //This for loop basically alternates between ascending and descending. This way, the cursor can move back and forth on the image, making it so there are no large jumps.
        for (int c = (r % 2 == 0) ? 0 : modified.cols - 1; (c >= 0) && (c < modified.cols); (r % 2 == 0) ? c++ : c--)
        {
            


            if (modified.at<uint8_t>(r, c) == 0)
                vrcClickPen(penSleepTime);
            ////cout << c << ',' << r << ' ';

            if (r % 2 == 0)
            {
                if (c != modified.cols - 1) 
                    moveMouse(pS, 0);
            }
            else
            {
                if (c != 0)
                    moveMouse(pS * -1, 0);
            }
            Sleep(movementSleepTime);
            
            //Move mouse depending on if the current cycle is on an even rotation or odd
            
        }

        ////cout << endl;

        //Move cursor down one space
        moveMouse(0, pS); 

        Sleep(movementSleepTime);
    }


}

//Relative mouse move function
void moveMouse(long x, long y)
{
    int mouseSpeed = 0;
    SystemParametersInfo(SPI_GETMOUSESPEED, 0, &mouseSpeed, 0);

    INPUT ip = { 0 };
    

    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_MOVE;
    ip.mi.dwExtraInfo = 0x200;
    ip.mi.dx = static_cast<int>(10.0 / static_cast<double>(mouseSpeed) * x);
    ip.mi.dy = static_cast<int>(10.0 / static_cast<double>(mouseSpeed) * y);

    SendInput(1, &ip, sizeof(INPUT));
    ZeroMemory(&ip, sizeof(ip));
}

//This function is special. Although its purpose is to draw just a pixel of color, it must actually hold down, move a pixel, move back, and THEN hold up. This is just some weird VRChat shenanigans, but it is necessary. 
void vrcClickPen(const int sleeptime)
{
    INPUT ip = { 0 };

    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, &ip, sizeof(INPUT));

    moveMouse(1, 0);

    Sleep(sleeptime);

    ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, &ip, sizeof(INPUT));

    moveMouse(-1, 0);

    ZeroMemory(&ip, sizeof(ip));
}