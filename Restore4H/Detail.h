#pragma once
#include "stdafx.h"
#include "CommonInclude.h"

# define DETAIL_SIZE 8

void PrintDetail(unsigned char *drive, unsigned char *patternInput, CListCtrl* listctrl, long long &position);
int SaveResult(unsigned char *filename);
void AddPrevious(int n, long long &position, CListCtrl *output);
void AddAfter(int n, long long &position, CListCtrl *output);