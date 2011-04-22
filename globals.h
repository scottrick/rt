#ifndef		GLOBALS
#define		GLOBALS

#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

class Object;

/*
	----------------------------------------------------------------------------------------------------------
	TYPES
	----------------------------------------------------------------------------------------------------------
*/
static	int						MAX_NUM_RAY_GENERATIONS		= 5;
static	int						NUM_RAY_THREADS				= 4;
static	bool					USE_FAST_MATH				= true;

static	float					InvSqrt(float x);

struct COLOR {
	float r;
	float g;
	float b;
	float a;

	void Add(COLOR *pVal)									{ r += pVal->r;  g += pVal->g;  b += pVal->b;  a += pVal->a; }
	void Print()											{ printf("COLOR (%f, %f, %f, %f)\n", r, g, b, a); }
	void Scale(float fScale)								{ r *= fScale;  g *= fScale;  b *= fScale;  a *= fScale; }
	void Set(float fR, float fG, float fB, float fA)		{ r = fR;  g = fG;  b = fB;  a = fA; }
	void Set(COLOR *pVal)									{ r = pVal->r;  g = pVal->g;  b = pVal->b;  a = pVal->a; }
};

struct VECTOR2 {
	float x;
	float y;

	void Print()					{ printf("VEC2 (%f, %f)\n", x, y); }
	void Set(float fX, float fY)	{ x = fX;  y = fY; }
	void Set(VECTOR2 *pVec)			{ x = pVec->x;  y = pVec->y; }
};

struct VECTOR3 {
	float x;
	float y;
	float z;

	float DotProduct(VECTOR3 *pVec)				{ return x * pVec->x + y * pVec->y + z * pVec->z; }
	void Normalize()							
	{ 
		float fT = x*x + y*y + z*z;  
		if (USE_FAST_MATH) {
			fT = InvSqrt(fT);
			x = x * fT;
			y = y * fT;
			z = z * fT;
		}
		else {
			fT = sqrt(fT);  
			x = x / fT;  
			y = y / fT;  
			z = z / fT;
		}
	 }
	void Print()								{ printf("VEC3 (%f, %f, %f)\n", x, y, z); }
	void Set(float fX, float fY, float fZ)		{ x = fX;  y = fY;  z = fZ; }
	void Set(VECTOR3 *pVec)						{ x = pVec->x;  y = pVec->y;  z = pVec->z; }
};

struct VECTOR4 {
	float x;
	float y;
	float z;
	float w;

	void Print()											{ printf("VEC4 (%f, %f, %f, %f)\n", x, y, z, w); }
	void Set(float fX, float fY, float fZ, float fW)		{ x = fX;  y = fY;  z = fZ;  w = fW; }
	void Set(VECTOR4 *pVec)									{ x = pVec->x;  y = pVec->y;  z = pVec->z;  w = pVec->w; }
};

struct RAY {
	VECTOR3 vStart;
	VECTOR3 vDirection;

	VECTOR3 ValueWhenT(float fT)	{ VECTOR3 val; val.Set(vStart.x + fT * vDirection.x, vStart.y + fT * vDirection.y, vStart.z + fT * vDirection.z); return val; }

	int		dwGeneration; 
};

/*
	----------------------------------------------------------------------------------------------------------
	GLOBAL FUNCTIONS
	----------------------------------------------------------------------------------------------------------
*/


/*
	----------------------------------------------------------------------------------------------------------
	GLOBAL FUNCTIONS
	----------------------------------------------------------------------------------------------------------
*/
static unsigned int	GenerateRandomUnsignedInt(unsigned int min, unsigned int max)
{
	return (rand() % (max - min + 1)) + min;
}
static float		GenerateRandomFloat(float min, float max)
{
	return (float)rand() / (float(RAND_MAX + 1)) * (max - min) + min;
}

static void			InitializeRandomGenerator(unsigned int dwSeed)
{
	srand(dwSeed);
}

//Fast approximation of  "1 / sq rt(x)"
//http://www.beyond3d.com/content/articles/8/
static float InvSqrt (float x)
{
    float	xhalf		= 0.5f*x;
    int		i			= *(int*)&x;

    i		= 0x5f3759df - (i>>1);
    x		= *(float*)&i;
    x		= x*(1.5f - xhalf*x*x);

    return x;
}

static float DistanceBetween(VECTOR3 p1, VECTOR3 p2)
{
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	float z = p1.z - p2.z;

	return sqrt(x * x + y * y + z * z);
}

#endif