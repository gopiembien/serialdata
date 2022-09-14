// File: conserial.cpp
// Description: Serial communication console program for Windows and Linux
// WebSite: http://cool-emerald.blogspot.sg/2017/05/serial-port-programming-in-c-with.html
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

#include <stdio.h>
#include <iostream>
#include "ceSerial.h"
#include <unistd.h>
#include <ostream>
#include "ceSerial.h"

using namespace std;
using namespace ce;

int main()
{
    while (1)
    {
        #ifdef ceWINDOWS
            ceSerial com("\\\\.\\COM8", 115200, 8, 'N', 1); // Windows
        #else
            ceSerial com("/dev/ttyUSB0", 115200, 8, 'N', 1); // Linux
        #endif

        printf("Opening port %s.\n", com.GetPort().c_str());
        if (com.Open() == 0)
        {
            printf("OK.\n");
        }
        else
        {
            printf("Error opening port.\n");
            continue;
        }
        bool successFlag;
        while (1)
        {
            char ch = com.ReadChar(successFlag);
            if (successFlag)
            {
                printf("%c", ch);
                continue;
            }
            #ifdef ceWINDOWS
            if (!com.comportcheck())
            {
                printf("port is closed\r\n");
                break;
            }
            #else
            if (!successFlag)
            {
                printf("port is closed\r\n");
                break;
            }
            #endif
        }
        printf("out of loop.\n");
        // printf("Writing.\n");
        // char s[]="Hello";
        // successFlag=com.Write(s); // write string
        // printf("successflag for write string %d\r\n", successFlag);
        // successFlag=com.WriteChar('!'); // write a character
        // printf("successflag for write char %d\r\n", successFlag);

        // printf("Waiting 3 seconds.\n");
        // ceSerial::Delay(3000); // delay to wait for a character

        // printf("Reading.\n");
        // char arr[1024];
        // for(int j = 0 ; j < 10; j++)
        // {
        // 	ceSerial::Delay(15000);
        // 	memset(&arr, '\0', sizeof(arr));
        // 	int i = 0;
        // 	do
        // 	{
        // 		c=com.ReadChar(successFlag); // read a char
        // 		if(successFlag && c != '\0' && c != '0')
        // 		{
        // 			arr[i] = c;
        // 			i++;
        // 		}
        // 	}while((i < 5));
        // 	arr[i] = '\0';
        // 	printf("Rx: %s\n",arr);
        // }
        // printf("Closing port %s.\n",com.GetPort().c_str());
        com.Close();
    }
    return 0;
}
