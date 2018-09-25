#pragma once
#include "stdafx.h"
#include "ListDisk.h"

# include <iostream>
# include <windows.h>
# include <stdio.h>
# include <string.h>

void str(int x, unsigned char *t)
{
	int n = 0;
	do
	{
		t[n] = x % 10 + '0';
		x /= 10;
		n++;
	} while (x > 0);
	for (int i = 0; i<n / 2; i++)
	{
		int temp = t[i];
		t[i] = t[n - i - 1];
		t[n - i - 1] = temp;
	}
	t[n] = 0;
}

int getDriveList(unsigned char ***listOut) {
	//FILE *f = fopen("test.txt", "w");
	unsigned char *link = (unsigned char *) malloc(1999);
	*listOut = NULL;
	unsigned char num[10];
	int outSize = 0;
	//DWORD nRead;

	//fprintf(f,"Physical hard drive:\n");
	for (int i = 0; i<16; i++)
	{
		str(i, num);
		link = Hstrndup((unsigned char*)"\\\\.\\PhysicalDrive", 17); // len of '\\.\PhysicalDrive'
		link = Hstrcat(link, num);
		HANDLE hDisk = CreateFileA((char*) link, //PhysicalDrive0
			GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL, OPEN_EXISTING, 0, NULL);
		if (hDisk != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hDisk);
			//fprintf(f,"%s\n", link);
		}
	}
	
	//fprintf(f, "Logical drive:\n");
	for (int i = 0; i < 26; i++)
	{
		sprintf((char*) link, "\\\\.\\%c:", i + 'A'); 
		HANDLE hDisk = CreateFileA((char*) link, //PhysicalDrive0
			GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL, OPEN_EXISTING, 0, NULL);
		if (hDisk != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hDisk);
			*listOut = (unsigned char **)realloc(*listOut, sizeof(unsigned char*)*(outSize + 1));
			*(*listOut + outSize) = Hstrndup(link, Hstrlen(link));
			//fprintf(f, "%s\n", *(*listOut + outSize));
			outSize++;
		}
	}
	free(link);
	//fclose(f);
	return outSize;
}