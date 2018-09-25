#pragma once
#include "stdafx.h"
#include "CommonInclude.h"
#include "resource.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <string.h>

int scan(unsigned char* drive, unsigned char* pattern, CEdit* processedResult, CListCtrl* scanResult, int *isRunning)
{
	FILE *f = fopen("scanlog.txt", "w");
	//unsigned char filename[199];
	//unsigned char message[939];

	//FILE *f = fopen(filename,"w");
	//unsigned char message[939] = "Don\"t know if I like you or not...";

	int len = Hstrlen(pattern);
	DWORD nRead;
	unsigned char buf[5130] = { 0 }, last[5130];
	long long first = 0;

	HANDLE hDisk = CreateFileA((char*)drive, //PhysicalDrive0
		GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, NULL);

	/*
	ReadMemory(6435167-512,buf,hDisk);
	for (int i=0; i<512; i++) if (buf[i] >= 32 && buf[i] <= 127) printf("%c ",buf[i]);
	//printf("%s\n",buf);
	CloseHandle(hDisk);
	scanf("%d",&nRead);
	return 0;
	*/

	SetFilePointer(hDisk, 0, 0, FILE_BEGIN);
	/*
	nRead = 0;
	ReadFile(hDisk, buf, 512000, &nRead, NULL);

	fprintf(f,"%d\n",nRead);
	for (int currentpos=0;currentpos < 512000;currentpos++) {
	if (buf[currentpos] >= 32 && buf[currentpos] <= 127)
	fprintf(f,"%c",buf[currentpos]);
	}

	fclose(f);
	return 0;
	*/

	int pos = 0;
	int cnt = 0;
	long long space = 0;
	while (2801) {
		if (*isRunning == 0) break;
		//for (int currentpos=0;currentpos < 512;currentpos++) {
		//SetFilePointer(hDisk, -512, 0, FILE_BEGIN);
		ReadFile(hDisk, buf + BLOCK_LEN, BLOCK_LEN, &nRead, NULL);
		//printf("%d",nRead);

		if (nRead == 0) //Finish reading all drive
		{
			if (scanResult != NULL)
			{
				if (cnt > 0)
					processedResult->SetWindowTextW(HcharStringToLPCTSTR((unsigned char*) "Cancelled"));
				else
					processedResult->SetWindowTextW(HcharStringToLPCTSTR((unsigned char*) "Not found"));
			}
			//scanResult->AddString(Hunsigned charStringToLPCTSTR("Not found"));
			//3040632832
			//oreka 3294805504
			//printf("Not found :<\n");
			//printf("%lld\n", first);
			//printf("%s", buf);
			//scanf("%lld", &first);
			return 0;
		}


		//if (cnt >= 100000) break;

		////Check for deleted file

		int pos = Hsubstr(pattern, buf, len, 512 + 512);
		if (pos >= 0)
		{
			fprintf(f, "O re ka!!!\n");
			fprintf(f, "%d\n", Hstrlen(buf));
			if (scanResult != NULL)
			{
				int t = scanResult->InsertItem(cnt, HcharStringToLPCTSTR(Hitoa(first)));
				scanResult->SetItemText(t, 1, HcharStringToLPCTSTR(HReadable(buf + pos, 50)));
				cnt++;
			}
			//for (int i = 0; i<512 + 512; i++)
			//	if (buf[i] >= 32 && buf[i] <= 127) printf("%c ", buf[i]);
			fprintf(f, "\n%lld\n", first);
			//int smth;
			//scanf("\n%d", &smth);
		}
		for (int i = 0; i<512; i++) buf[i] = buf[i + 512];
		if (space >= 10000000)
		{
			if (processedResult != NULL)
			{
				processedResult->SetWindowTextW(HIntToLPCTSTR(first));
			}
			//scanResult->AddString(Hunsigned charStringToLPCTSTR(HReadable(buf + 512, 20)));
			fprintf(f, "Current Scan: %lld\n", first);
			space = 0;
		}
		//strcpy(last,buf);

		////
		//std::cout << nRead;
		//std::cout << buf[currentpos];
		//std::cout << buf[currentpos];
		//fprintf(f,"%d",nRead);
		//if (buf[0] >= 32 && buf[0] <= 127)
		//fprintf(f,"%c",buf[0]);
		//fprintf(f,"%s",buf);

		/*
		for (int i=0; i<512; i++)
		if (buf[i] >= 32 && buf[i] <= 127)
		{
		printf("%c",buf[i]);
		for (int j=0; j<1000000; j++);
		cnt ++;
		}
		*/

		first += 512;
		space += 512;
		pos += 1;
	}
	//fprintf(f,"\n%d",first);
	if (processedResult != NULL)
		processedResult->SetWindowTextW(HcharStringToLPCTSTR((unsigned char*) "Finish scanning"));
	CloseHandle(hDisk);
	fclose(f);
}

DWORD WINAPI scan(LPVOID lpParam)
{
	PMYDATA pData = (PMYDATA)lpParam;
	unsigned char *drive = pData->drive;
	unsigned char *patternInput = pData->patternInput;
	CEdit* processedResult = pData->processedResult;
	CListCtrl* scanResult = pData->scanResult;
	int *isRunning = pData->isRunning;
	scanResult->DeleteAllItems();	// reset the scan result field
	scan(drive, patternInput, processedResult, scanResult, isRunning);
	return 0;
}