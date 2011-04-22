#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "globals.h"

class Buffer
{
public:
	Buffer(unsigned int x = 10, unsigned int y = 10);
	~Buffer();

	void				*GetBuffer()	{ return pBuffer; }
	COLOR				*GetColor(unsigned int index);
	COLOR				*GetColor(unsigned int x, unsigned int y);
	unsigned int		GetX()			{ return dwX; }
	unsigned int		GetY()			{ return dwY; }

	void				Randomize();
	void				SetColor(unsigned int index, COLOR *pColor);
	void				SetColor(unsigned int x, unsigned int y, COLOR *pColor);
	void				SetSolidColor(COLOR *pColor);

private:
	void				Init();

	unsigned int		dwX;
	unsigned int		dwY;

	void				*pBuffer;
};

#endif
