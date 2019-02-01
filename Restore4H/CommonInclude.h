#pragma once

#include "stdafx.h"

typedef struct MyData {
	unsigned char *drive;
	unsigned char *patternInput;
	CEdit  *processedResult;
	CListCtrl *scanResult;
	int *isRunning;
} MYDATA, *PMYDATA;

typedef struct MyControl {
	CEdit *startPosition;
	CEdit *endPosition;
	CListCtrl *detailOutputField;
} MYCONTROL, *PMYCONTROL;

# define BLOCK_LEN 512
# define PLAIN 0
# define HEX   1
# define MAX_INPUT 1999
# define MAX_BUFFER_SIZE 51309
# define NOT_NUMBER_ERROR_MSG "The thing in the textbox is not a number"

extern MYCONTROL mycontrol;

extern DWORD nRead;
extern unsigned char buf[MAX_BUFFER_SIZE];

extern int inputMode;
extern int isRunning;
extern unsigned char *drive;
extern unsigned char *patternInput;
extern long long position;
extern int bufferstart;
extern int bufferend;

unsigned char HHexToDec(unsigned char t);
int HisHexString(unsigned char *s);
unsigned char *HConvertHexStr(unsigned char *s);
int HcheckInt(unsigned char *s);
long long Hmax(long long a, long long b);
int Hstrlen(unsigned char *s); //get length of string start with s and end with 0
int Hsubstr(unsigned char *pattern, unsigned char *src, int lenpattern, int lensrc);
unsigned char *Hstrndup(unsigned char *s, int len);
unsigned char *Hitoa(long long x);
long long Hatoi(unsigned char *x);
unsigned char *Hstrcat(unsigned char *src, unsigned char *add);
LPCTSTR HcharStringToLPCTSTR(unsigned char *x);
LPCTSTR HcharStringToLPCTSTRn(unsigned char *x, int len);
LPCTSTR HIntToLPCTSTR(long long x);
unsigned char *HReadable(unsigned char *src, int len);
int Hhighbit(unsigned long long x);
int Hlowbit(unsigned long long x);
int GetValue(unsigned char *x);
int ReadMemory(long long start, unsigned char *buf, int readsize, HANDLE hDisk);
int ReadMemory(long long start, unsigned char *buf, int readsize, unsigned char *drive);

int scan(unsigned char* drive, unsigned char* pattern, CEdit* processedResult, CListCtrl* scanResult, int* isRunning);
DWORD WINAPI scan(LPVOID lpParam);