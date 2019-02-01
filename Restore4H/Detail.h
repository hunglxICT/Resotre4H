#pragma once
#include "stdafx.h"
#include "CommonInclude.h"

# define DETAIL_SIZE 8

void PrintDetail(unsigned char *drive, unsigned char *patternInput, PMYCONTROL controlist, long long &position);
int SaveResult(unsigned char *filename);
void AddPrevious(int n, long long &position, PMYCONTROL controlist);
void AddAfter(int n, long long &position, PMYCONTROL controlist);
void DeletePrevious(int n, long long &position, PMYCONTROL controlist);
void DeleteAfter(int n, long long &position, PMYCONTROL controlist);