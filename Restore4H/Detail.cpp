#pragma once
#include "stdafx.h"
#include "Detail.h"

unsigned char *hexa(unsigned char x)
{
	unsigned char *res = (unsigned char*)malloc(3);
	res[0] = x / 16;
	res[1] = x % 16;
	for (int i = 0; i < 2; i++)
	{
		if (res[i] < 10) res[i] += '0';
		else res[i] += 'a' - 10;
	}
	res[2] = 0;
	return res;
}

void PrintDetail(unsigned char *drive, unsigned char *patternInput, PMYCONTROL controlist, long long &position)
{
	CListCtrl *outputfield = controlist->detailOutputField;
	outputfield->DeleteAllItems();
	//int len = nRead;
	int len = bufferend - bufferstart;
	int cnt = 0;
	//int patternlen = Hstrlen(patternInput);
	//int patternpos = Hsubstr(patternInput, buf, patternlen, BLOCK_LEN + BLOCK_LEN);
	for (int i = 0; i < len; i += DETAIL_SIZE)
	{
		int t = outputfield->InsertItem(cnt, HcharStringToLPCTSTR(Hitoa(i + position + bufferstart)));
		for (int j = 0; j < DETAIL_SIZE; j++)
		{
			if (i + j >= len) break;
			/*
			if (i + j >= patternpos && i + j < patternpos + patternlen)
			{
				//TODO: change color
			}
			else outputfield->SetTextColor(0);
			*/
			outputfield->SetItemText(t, j + 1, HcharStringToLPCTSTR(hexa(buf[i + j + bufferstart])));
			outputfield->SetItemText(t, j + DETAIL_SIZE + 2, HcharStringToLPCTSTR(HReadable(&buf[i + j + bufferstart],1)));
		}
		cnt++;
	}
	controlist->startPosition->SetWindowTextW(HcharStringToLPCTSTR(Hitoa(bufferstart + position)));
	controlist->endPosition->SetWindowTextW(HcharStringToLPCTSTR(Hitoa(bufferend + position)));
}

int SaveResult(unsigned char *filename)
{
	if (Hstrlen(filename) == 0)
	{
		return ERROR_EMPTY;
	}
	FILE *f;
	f = fopen((char*)filename, "rb");
	if (f != NULL)
	{
		fclose(f);
		return ERROR_FILE_EXISTS;
	}
	f = fopen((char*)filename, "wb");
	int writesize = fwrite(buf + bufferstart, 1, bufferend - bufferstart, f);
	fclose(f);
	if (writesize != nRead)
	{
		return ERROR_CANT_ACCESS_FILE;
	}
	return 0;
}

void AddPrevious(int n, long long &position, PMYCONTROL controlist)
{
	if (bufferstart >= n)
	{
		bufferstart -= n;
		return;
	}
	else
	{
		n -= bufferstart;
		bufferstart = 0;
	}
	int nBlockRead = (n - 1) / BLOCK_LEN + 1;
	int ReadSize = nBlockRead * BLOCK_LEN;
	if (position - ReadSize < 0)
	{
		ReadSize = position;
		position = 0;
		bufferstart = 0;
	}
	else
	{
		position -= ReadSize;
		bufferstart = (BLOCK_LEN - (n % BLOCK_LEN)) % BLOCK_LEN;
	}
	for (int i = nRead-1; i >= 0; i--)
	{
		buf[i + ReadSize] = buf[i];
	}
	nRead += ReadSize;
	ReadMemory(position, buf, ReadSize, drive);
	bufferend = bufferend + ReadSize;
}

void AddAfter(int n, long long &position, PMYCONTROL controlist)
{
	int spaceleft = nRead - bufferend;
	if (spaceleft >= n)
	{
		bufferend += n;
		PrintDetail(NULL, NULL, controlist, position);
		return;
	}
	else
	{
		bufferend = nRead;
		n -= spaceleft;
	};
	int nBlockRead = (n - 1) / BLOCK_LEN + 1;
	int ReadSize = nBlockRead * BLOCK_LEN;
	ReadMemory(position + nRead, buf + nRead, ReadSize, drive);
	nRead += ReadSize;
	bufferend = bufferend + n;
}

void DeletePrevious(int n, long long &position, PMYCONTROL controlist)
{
	bufferstart += n;
	if (bufferstart >= bufferend)
	{
		bufferstart = 0;
		bufferend = 0;
		nRead = 0;
	}
}

void DeleteAfter(int n, long long &position, PMYCONTROL controlist)
{
	bufferend -= n;
	if (bufferstart >= bufferend)
	{
		bufferstart = 0;
		bufferend = 0;
		nRead = 0;
	}
}