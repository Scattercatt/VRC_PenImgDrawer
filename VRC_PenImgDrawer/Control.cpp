#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace cv;

void press(WORD w)
{
    INPUT ip;
    ZeroMemory(&ip, sizeof(ip));

    ip.type = INPUT_KEYBOARD;

    ip.ki.wVk = w;
    ip.ki.dwFlags = 0;

    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));


}

void moveMouse(long x, long y)
{
    INPUT ip = { 0 };


    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_MOVE;
    ip.mi.dx = x;
    ip.mi.dy = y;

    SendInput(1, &ip, sizeof(INPUT));
    ZeroMemory(&ip, sizeof(ip));
}
void clickMouse()
{
    INPUT ip = { 0 };

    ip.type = INPUT_MOUSE;
    ip.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    SendInput(1, &ip, sizeof(INPUT));

    ip.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(1, &ip, sizeof(INPUT));
    ZeroMemory(&ip, sizeof(ip));

}