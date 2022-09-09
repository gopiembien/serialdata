// File: conserial.cpp
// Description: Serial communication console program for Windows and Linux
// WebSite: http://cool-emerald.blogspot.sg/2017/05/serial-port-programming-in-c-with.html
// MIT License (https://opensource.org/licenses/MIT)
// Copyright (c) 2018 Yan Naing Aye

#include <stdio.h>
#include "ceSerial.h"
#include <errno.h>
#include <cstring>
using namespace std;
using namespace ce;
extern int errno;

int main()
{
#ifdef ceWINDOWS
	ceSerial com("\\\\.\\COM12",9600,8,'N',1); // Windows
#else
	ceSerial com("/dev/ttyUSB0",9600,8,'N',1); // Linux
#endif

	printf("Opening port %s.\n",com.GetPort().c_str());
	if (com.Open() == 0) {
		printf("OK.\n");
	}
	else {
		printf("Error.\n");
		perror("opening port error");
		return 1;
	}

	bool successFlag;
	printf("Writing.\n");
	char str[100];
	char ch;

	while(1)
	{
		FILE *ptr;
		ptr = fopen("file.txt", "r");
    // Return if could not open file
    	if (ptr == NULL)
		{
			printf("File opening failed");
			return 0;
		}
		do 
		{
			ch = fgetc(ptr);
			int i = 0;
			while((ch != '\n') && (ch != '\r') && (ch != EOF))
			{
				str[i] = ch;
				i++;
				ch = fgetc(ptr);
			}
			if((ch == '\n') || (ch == '\r') || (ch != EOF)) 
			{
				str[i] = '\0';
				printf("string sending to port is %s\r\n", str);
				successFlag=com.Write(str);
				if(successFlag)
				{
					printf("data successfully send\r\n");
				}
				ceSerial::Delay(10000);
				memset(&str, '\0', sizeof(str));
			}
    	} while (ch != EOF);
 
    	fclose(ptr);
	// successFlag=com.Write(s); // write string
	// successFlag=com.WriteChar('i'); // write a character
	// printf("Waiting 3 seconds.\n");
	// ceSerial::Delay(3000); // delay to wait for a character

	// printf("Reading.\n");
	// char c=com.ReadChar(successFlag); // read a char
	// if(successFlag) printf("Rx: %c\n",c);
	ceSerial::Delay(10000);
	}
	// printf("Closing port %s.\n",com.GetPort().c_str());
	com.Close();
	return 0;
}
