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

void PrintDetail(unsigned char *drive, unsigned char *patternInput, CListCtrl* outputfield, long long &position)
{
	outputfield->DeleteAllItems();
	int len = nRead;
	int cnt = 0;
	//int patternlen = Hstrlen(patternInput);
	//int patternpos = Hsubstr(patternInput, buf, patternlen, BLOCK_LEN + BLOCK_LEN);
	for (int i = 0; i < len; i += DETAIL_SIZE)
	{
		int t = outputfield->InsertItem(cnt, HcharStringToLPCTSTR(Hitoa(i + position)));
		for (int j = 0; j < DETAIL_SIZE; j++)
		{
			/*
			if (i + j >= patternpos && i + j < patternpos + patternlen)
			{
				//TODO: change color
			}
			else outputfield->SetTextColor(0);
			*/
			outputfield->SetItemText(t, j + 1, HcharStringToLPCTSTR(hexa(buf[i + j])));
			outputfield->SetItemText(t, j + DETAIL_SIZE + 2, HcharStringToLPCTSTR(HReadable(&buf[i + j],1)));
		}
		cnt++;
	}
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
	int writesize = fwrite(buf, 1, nRead, f);
	fclose(f);
	if (writesize != nRead)
	{
		return ERROR_CANT_ACCESS_FILE;
	}
	return 0;
}

void AddPrevious(int n, long long &position, CListCtrl *output)
{
	if (position - n < 0)
	{
		return;
	}
	for (int i = nRead-1; i >= 0; i--)
	{
		buf[i + n] = buf[i];
	}
	position = position - n;
	nRead += n;
	ReadMemory(position, buf, n, drive);
	PrintDetail(NULL, NULL, output, position);
}

void AddAfter(int n, long long &position, CListCtrl *output)
{
	ReadMemory(position + nRead, buf + nRead, n, drive);
	nRead += n;
	PrintDetail(NULL, NULL, output, position);
}