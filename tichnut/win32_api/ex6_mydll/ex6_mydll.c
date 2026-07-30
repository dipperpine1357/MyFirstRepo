/*
Name: ex6_mydll.c
Author: dipper pine
Date: 27.7.2026
Description: this code has to function that use winapi function
                it should be used as a dll  
includes & more
*/
#include <Windows.h> // ! PlaySound function
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include "Shlwapi.h"


#pragma comment(lib ,"winmm.lib")
#pragma comment(lib ,"User32.lib")
#pragma comment(lib ,"Shlwapi.lib")


#define SOME_MINUTES 5 
#define SECONDS_PER_MINUTE 60


// this function plays a G-F song for 10 seconds
// returns false if the file didnt exit
__declspec(dllexport) BOOL play_song()
{
    printf("YOU ARE IN MY DLL.\nu should check the song file is in the dll directory\n");

    LPCWSTR filename = L"GravityFalls.wav";

     // check if file exists
    if (!PathFileExistsW(filename)){
        printf("file doesnt exist");
        return false;
    }
    
    if (false == PlaySoundW(filename, NULL, SND_ASYNC | SND_FILENAME))
    {
        printf("didnt work\n");
        return false;
    }
    // playing for 10 seconds
    Sleep(39000);
    return true;
}

// this func plays the first episode from grafity falls
// returns false if the file didnt exit
__declspec(dllexport) BOOL play_episode()
{
    LPCWSTR filename = L"Gravity.Falls.S01E01.wmv";

    // check if file exists
    if (!PathFileExistsW(filename)){
        printf("file doesnt exist");
        return false;
    }

    MessageBox(
        NULL,
        (LPCTSTR)"DON'T U DARE TAKE YOURE EYES OFF THE SCREEN",
        (LPCTSTR)"DON'T MISS THE EPISODE",
        MB_HELP | MB_ICONEXCLAMATION | MB_DEFBUTTON2
    );
    printf("YOU ARE IN MY DLL.\nu should check the video file is in the dll directory\n"
        "u are about to watch rhe first episode in the best show ever\n");

    system("pause");

    char message[100];
    mciSendStringA("Open Gravity.Falls.S01E01.wmv type mpegvideo Alias MyVideo", message, 100, 0);
    printf("open: %s\n", message);
    mciSendStringA("Play MyVideo FullScreen", message, 100, 0);
    Sleep(100000);
  


    mciSendStringA("Close MyVideo", "", 0, 0);
    return true;
}


int main(){
return 0;
}