#include "PixelUtility.h"

#include <iostream>
using namespace std;

/*
unsigned int GetA(COLOR *pCOLOR)
{
	return ((0xff000000 & *pCOLOR) >> 24);
}

unsigned int GetB(COLOR *pCOLOR)
{
	return ((0x00ff0000 & *pCOLOR) >> 16);
}

unsigned int GetG(COLOR *pCOLOR)
{
	return ((0x0000ff00 & *pCOLOR) >> 8);
}

unsigned int GetR(COLOR *pCOLOR)
{
	return (0x000000ff & *pCOLOR);
}

void PrintCOLOR(COLOR *pCOLOR)
{
	printf("COLOR 0x%x  (%u, %u, %u, %u)\n", pCOLOR, GetR(pCOLOR), GetG(pCOLOR), GetB(pCOLOR), GetA(pCOLOR));
}

void SetA(COLOR *pCOLOR, COLOR val)
{
	*pCOLOR = ((0x000000ff & val) << 24) | (0x00ffffff & *pCOLOR);
}

void SetB(COLOR *pCOLOR, COLOR val)
{
	*pCOLOR = ((0x000000ff & val) << 16) | (0xff00ffff & *pCOLOR);
}

void SetG(COLOR *pCOLOR, COLOR val)
{
	*pCOLOR = ((0x000000ff & val) << 8) | (0xffff00ff & *pCOLOR);
}

void SetR(COLOR *pCOLOR, COLOR val)
{
	*pCOLOR = (0x000000ff & val) | (0xffffff00 & *pCOLOR);
}
*/