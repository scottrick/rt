#include "Sphere.h"

#include <cmath>
using namespace std;

VECTOR3 Sphere::GetNormal(INTERSECTION *pInter)
{
	VECTOR3 vVec = pInter->ray->ValueWhenT(pInter->t);

	float xx = vVec.x - m_v3Center.x;
	float yy = vVec.y - m_v3Center.y;
	float zz = vVec.z - m_v3Center.z;

	if (USE_FAST_MATH)
	{
		float bb = InvSqrt(xx * xx + yy * yy + zz * zz);
		vVec.Set(xx * bb, yy * bb, zz * bb);
	}
	else
	{
		float bb = sqrt(xx * xx + yy * yy + zz * zz);
		vVec.Set(xx / bb, yy / bb, zz / bb);
	}

	return vVec;
}

void Sphere::Init()
{
	m_v3Center.Set(0.0f, 0.0f, 0.0f);
	m_fRadius = 1.0f;

	unsigned int random = GenerateRandomUnsignedInt(0, 1);
	if (random)
	{
		m_bMoving = true;
	}
	else
	{
		m_bMoving = false;
	}

	//m_bMoving = false;

	random = GenerateRandomUnsignedInt(0, 1);
	if (random)
	{
		m_bMovementReversed = true;
	}
	else
	{
		m_bMovementReversed = false;
	}
}	

float Sphere::Intersects(RAY *pRay)
{
	float a, b, c;

	float xDist = pRay->vStart.x - m_v3Center.x;
	float yDist	= pRay->vStart.y - m_v3Center.y;
	float zDist = pRay->vStart.z - m_v3Center.z;

	a = 
		(pRay->vDirection.x * pRay->vDirection.x + 
		pRay->vDirection.y * pRay->vDirection.y + 
		pRay->vDirection.z * pRay->vDirection.z) * 2.0f;

	b = 2 * 
		   (pRay->vDirection.x * xDist + 
			pRay->vDirection.y * yDist + 
			pRay->vDirection.z * zDist);

	c = (xDist * xDist) + (yDist * yDist) +	(zDist * zDist) - (m_fRadius * m_fRadius);

 	float			fDescriminant		= (b * b) - (2.0f * a * c);
	float			fIntersectTime		= 0.0f;  //0.0f is default return value when no intersection occurs

	if (fDescriminant >= 0.0f)
	{
		float fSqrtDescriminant = sqrt(fDescriminant);
		float fDivideBy			= 1.0f / a;
		float tPlus				= (-b + fSqrtDescriminant) * fDivideBy;
		
		//first check to see if tPlus is > 0.01f, before we calculate tMinus
		if (tPlus > 0.01f)
		{
			float tMinus			= (-b - fSqrtDescriminant) * fDivideBy;

			//add the intersection to the list of intersections, if it intersects
			//only add if the intersection occurs at least some delta away
			if (tMinus > 0.01f)
			{
				if (fDescriminant > 0) {
					//pIntersection = new INTERSECTION();
					//pIntersection->bEntering = true;
					//pIntersection->object = this;
					//pIntersection->ray = pRay;
					fIntersectTime = tMinus;
					//pIntersection->t = tMinus;

				}
				else if (fDescriminant == 0) {
					//pIntersection = new INTERSECTION();
					//pIntersection->bEntering = true;
					//pIntersection->object = this;
					//pIntersection->ray = pRay;
					//pIntersection->t = tPlus;
					fIntersectTime = tPlus;
				}
			}
		}
	}

	return fIntersectTime;
}

void Sphere::Print()
{
	printf("SPHERE         0x%x\n", this);
	printf("Radius         = %f\n", m_fRadius);
	printf("Center         = ");
	m_v3Center.Print();

	Object::Print();
}

void Sphere::Refresh(int DeltaTime)
{
	if (!m_bMoving)
	{
		return;
	}

	float fChange = (float)DeltaTime / 2000.0f / 2.0f;

	if (m_bMovementReversed)
	{
		fChange = -fChange;
	}
	
	m_v3Center.x += fChange;
	m_v3Center.y += fChange / 2.0f;
}