/*
Name: win32_ex2.c
Author: dipper pine
Date: 22.6.2026
Description: this code recives 2 pathes take the first 24 byres from the first 
             one and add them to the second on
             if the destenerion file exits it'll print error
includes & more
*/
#include <windows.h>
#include <tchar.h>  
#include <stdio.h>  
#include <strsafe.h>
#include <errno.h>


int main()
{

    HANDLE hFile; 
    char filename1[300], filename2[300];
    char content[25] ;
    DWORD dwBytesToWrite = 24, bytesread;
    DWORD dwBytesWritten = 0;
    BOOL error_flag = FALSE;
    OVERLAPPED ol = {0};
    ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    //recive file name
    printf("Enter the source filename to open for reading: (without \"\") \n");
    scanf("%299s", filename1);
    printf("Enter the dest filename to open for writing: (without \"\") (should not exist) \n");
    scanf("%299s", filename2);

    // Open one file for reading and creating a handle
    hFile = CreateFile(filename1,               // file to open
                       GENERIC_READ,          // open for reading
                       0,       // share for reading
                       NULL,                  // default security
                       OPEN_EXISTING,         // existing file only
                       FILE_ATTRIBUTE_NORMAL, // normal file
                       NULL);
    
    // did handle work
    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf(TEXT("failure: unable to open file \"%s\" for read.\n"), filename1);
        return 1; 
    }

    error_flag = ReadFile(hFile, content , sizeof(content)-1, &bytesread, NULL);


    if (TRUE == error_flag) 
    {
        printf("\ncopied %d bytes:)\n", (int)(strlen(content)-1));
    }
    else{
      printf("\ndidnt copy\n");
      printf("%lu",GetLastError());
    }    

    //prevent BOF
    content[24] = '\0';

    // Close the file
    CloseHandle(hFile);
    printf("the content is: %s\n", content );

    //creating a handle
    hFile = CreateFile(filename2,                // name of the write
                       GENERIC_WRITE,          // open for writing
                       0,                      // do not share
                       NULL,                   // default security
                       CREATE_NEW,             // only create new file 
                       FILE_ATTRIBUTE_NORMAL,  // normal file
                       NULL);
    if (hFile == INVALID_HANDLE_VALUE) 
    { 
        printf(TEXT("failure: unable to open file \"%s\" for read.\n probebly already exitst\n"), filename2);
        return 1; 
    }

    //write to file
    error_flag = WriteFile( 
                    hFile,           // open file handle
                    content,      // start of data to write
                    dwBytesToWrite,  // number of bytes to write
                    &dwBytesWritten, // number of bytes that were written
                    NULL);

    if (FALSE == error_flag)
    {
        printf("Terminal failure: Unable to write to file.\n");
    }
    else
    {
        // This is an error because a synchronous write
        if (dwBytesWritten != dwBytesToWrite)
        {           
            printf("Error: dwBytesWritten != dwBytesToWrite\n");
        }
    }
    
    // Close the file
    CloseHandle(hFile);

    system("pause");
    return 0;
}