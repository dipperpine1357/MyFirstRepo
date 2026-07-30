/*
Name: ex6_winapi_use_dll.c
Author: dipper pine
Date: 28.7.2026
Description: this code uses the dll and shows the episode after playing the song 
includes & more
*/

#include <windows.h>
#include <libloaderapi.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib ,"User32.lib")
#pragma comment(lib ,"Kernel32.lib")


int main ()
{

    // get a handle on the dll
    HINSTANCE hDLL = LoadLibrary("ex6_mydll.dll");              

    //check if dll loaded
	if(hDLL != NULL)
	{
		printf("Library has been loaded\n");
        
        }
	else
	{  
		printf("Couldn't load dll\n");
        return 1;
	}

    printf("now u are going to here the song\n");
    printf("it won't come out of youre head\n");
    MessageBox(
        NULL,
        (LPCTSTR)"dont even try to stop it\njust 39 secondss",
        (LPCTSTR)"enjoy the song",
        MB_HELP | MB_ICONEXCLAMATION | MB_DEFBUTTON2
    );

	
    // play theme song from play_song func in the dll
    FARPROC SongFunction = GetProcAddress(hDLL, "play_song");
    if(SongFunction != NULL)
    {
        SongFunction((LPCWSTR)L"play_song");
    }


    printf("now u are going to watch the episode\n");
    // play first episode from play_episode func in the dll
    FARPROC EpisodeFunction = GetProcAddress(hDLL, "play_episode");
    if(EpisodeFunction != NULL)
    {
        EpisodeFunction((LPCWSTR)L"play_episode");
    }


    
    FreeLibrary(hDLL);
    return 0;
}