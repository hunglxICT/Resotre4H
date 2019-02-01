#pragma once
#include "stdafx.h"
#include "CommonInclude.h"

MYCONTROL mycontrol;

DWORD nRead;
unsigned char buf[MAX_BUFFER_SIZE] = { 0 };

int inputMode = PLAIN;
int isRunning = 0;
unsigned char *drive = NULL;
unsigned char *patternInput = NULL;
long long position = 0;
int bufferstart = 0;
int bufferend = 0;

long long Hmax(long long a, long long b)
{
	return a > b ? a : b;
}

int Hstrlen(unsigned char *s)
{
	if (s == NULL) return 0;
	int res = 0;
	while (s[res] != 0)
	{
		res++;
	}
	return res;
}

int Hsubstr(unsigned char *pattern, unsigned char *src, int lenpattern, int lensrc) {
	for (int i = 0; i <= lensrc - lenpattern; i++)
	{
		int check = 99;
		for (int j = 0; j<lenpattern; j++) if (pattern[j] != src[i + j]) {
			check = 0;
			break;
		}
		if (check) return i;
	}
	return -1;
}

unsigned char *Hstrndup(unsigned char *s, int len)
{
	unsigned char *temp = (unsigned char*)malloc(len + 1);
	for (int i = 0; i < len; i++) temp[i] = s[i];
	temp[len] = 0;
	return temp;
}

unsigned char *Hitoa(long long x)
{
	int n = 0;
	long long tempx = x;
	do
	{
		n++;
		tempx /= 10;
	} while (tempx > 0);
	unsigned char *res = (unsigned char*)malloc(n + 1);
	for (int i = n - 1; i >= 0; i--)
	{
		res[i] = x % 10 + '0';
		x /= 10;
	}
	res[n] = 0;
	return res;
}

long long Hatoi(unsigned char *s)
{
	int n = Hstrlen(s);
	if (n >= 18) return 0;
	long long result = 0;
	for (int i = 0; i < n; i++) result = result * 10 + s[i] - '0';
	return result;
}

unsigned char *Hstrcat(unsigned char *src, unsigned char *add)
{
	int nsrc = Hstrlen(src);
	int nadd = Hstrlen(add);
	int n = nsrc + nadd;
	src = (unsigned char*)realloc(src, n + 1);
	for (int i = 0; i < nadd; i++)
		src[nsrc + i] = add[i];
	src[n] = 0;
	return src;
}

LPCTSTR HcharStringToLPCTSTR(unsigned char *tempchar)
{
	int n = Hstrlen(tempchar);
	wchar_t* temp = (wchar_t*)malloc((n + 1) * sizeof(wchar_t));
	for (int i = 0; i < n; i++)
	{
		temp[i] = (wchar_t)tempchar[i];
	}
	temp[n] = 0;
	return (LPCTSTR)temp;
}

LPCTSTR HcharStringToLPCTSTRn(unsigned char *x, int len)
{
	wchar_t* temp = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	for (int i = 0; i < len; i++)
	{
		temp[i] = (wchar_t)x[i];
	}
	temp[len] = 0;
	return (LPCTSTR)temp;
}

LPCTSTR HIntToLPCTSTR(long long x)
{
	unsigned char *tempchar = Hitoa(x);
	return HcharStringToLPCTSTR(tempchar);
}

unsigned char *HReadable(unsigned char *src, int len)
{
	unsigned char *temp = (unsigned char*)malloc(len + 1);
	for (int i = 0; i < len; i++)
	{
		if (src[i] >= 32 && src[i] <= 126) temp[i] = src[i];
		else temp[i] = '.';
	}
	temp[len] = 0;
	//FILE *f = fopen("xxx.txt", "w");
	//fprintf(f, "%s", temp);
	//fclose(f);
	return temp;
}

int Hhighbit(unsigned long long x)
{
	int res = 0;
	x >>= 32;
	int base = 0;
	for (int i = 0; i < 32; i++)
	{
		res = res | ((x % 2) << base);
		x >>= 1;
		base++;
	}
	return res;
}

int Hlowbit(unsigned long long x)
{
	int res = 0;
	int base = 0;
	for (int i = 0; i < 32; i++)
	{
		res = res | ((x % 2) << base);
		x >>= 1;
		base++;
	}
	return res;
}

int GetValue(unsigned char *x)
{
	int res = 0;
	int n = Hstrlen(x);
	for (int i = 0; i < n; i++)
	{
		if (x[i] >= '0' && x[i] <= '9') res = res * 10 + x[i] - '0';
		else return 0;
	}
	return res;
}

int ReadMemory(long long start, unsigned char *buf, int readsize, HANDLE hDisk) {
	DWORD nRead;
	LONG startpointhighbit = Hhighbit(start);
	LONG startpointlowbit = Hlowbit(start);
	//FILE *f = fopen("xxx.txt", "w");
	//fprintf(f, "%lld\n", start);
	//fclose(f);
	SetFilePointer(hDisk, startpointlowbit, &startpointhighbit, FILE_BEGIN);
	ReadFile(hDisk, buf, readsize, &nRead, NULL);
	return nRead;
}

int ReadMemory(long long start, unsigned char *buf, int readsize, unsigned char *drive) {
	HANDLE hDisk = CreateFileA((char*)drive, //PhysicalDrive0
		GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL, OPEN_EXISTING, 0, NULL);
	return ReadMemory(start, buf, readsize, hDisk);
}