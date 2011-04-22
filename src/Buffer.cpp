#include "Buffer.h"

//#include "globals.h"
#include "PixelUtility.h"

#include <iostream>
#include <cassert>
using namespace std;

Buffer::Buffer(unsigned int x, unsigned int y)
{
	dwX = x;
	dwY = y;

	Init();	
}

Buffer::~Buffer()
{
	free(pBuffer);
	pBuffer = 0;
}

void Buffer::Init()
{
	pBuffer				= malloc(dwX * dwY * sizeof(COLOR));
	//Randomize();
	COLOR newColor;
	newColor.Set(0.5f, 0.5f, 0.5f, 1.0f);
	SetSolidColor(&newColor);
}

COLOR *Buffer::GetColor(unsigned int index)
{
	assert(index < (dwX * dwY));

	int x = index % dwX;
	int y = index / dwX;

	return GetColor(x, y);

	return (COLOR *)pBuffer + index;
}

COLOR *Buffer::GetColor(unsigned int x, unsigned int y)
{
	assert((x < dwX) && (y < dwY));
		
	return (COLOR *)pBuffer + (((dwY - y - 1) * dwX) + x);
}

void Buffer::Randomize()
{
	COLOR	*pCurrent	= 0;
	for (unsigned int x = 0; x < dwX; x++)
	{
		for (unsigned int y = 0; y < dwY; y++)
		{
			pCurrent = GetColor(x, y);
			/*
			SetR(pCurrent, GenerateRandomUnsignedInt(0, 255));
			SetG(pCurrent, GenerateRandomUnsignedInt(0, 255));
			SetB(pCurrent, GenerateRandomUnsignedInt(0, 255));
			SetA(pCurrent, 255);
			*/
			pCurrent->r = GenerateRandomFloat(0.0f, 1.0f);
			pCurrent->g = GenerateRandomFloat(0.0f, 1.0f);
			pCurrent->b = GenerateRandomFloat(0.0f, 1.0f);
		}	
	}
}

void Buffer::SetColor(unsigned int index, COLOR *pColor)
{
	GetColor(index)->Set(pColor);
}

void Buffer::SetColor(unsigned int x, unsigned int y, COLOR *pColor)
{
	GetColor(x, y)->Set(pColor);
}	

void Buffer::SetSolidColor(COLOR *pColor)
{
	for (unsigned int x = 0; x < dwX; x++)
	{
		for (unsigned int y = 0; y < dwY; y++)
		{
			GetColor(x, y)->Set(pColor);		
		}	
	}
}	
