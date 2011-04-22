#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "globals.h"
#include "Object.h"

class Sphere : public Object
{
public:
	Sphere()				{ Init(); }
	~Sphere()				{}

	VECTOR3					GetCenter() const	{ return m_v3Center; }
	virtual VECTOR3			GetNormal(INTERSECTION *pInter);
	float					GetRadius() const	{ return m_fRadius; }

	virtual void			Print();
	virtual void			Refresh(int DeltaTime);
	virtual float			Intersects(RAY *pRay);

	void					SetCenter(VECTOR3 *pVec)			{ m_v3Center.Set(pVec); }
	void					SetRadius(float fRadius)			{ m_fRadius = fRadius; }

private:
	void					Init();

	VECTOR3					m_v3Center;
	float					m_fRadius;
	bool					m_bMoving;
	bool					m_bMovementReversed;
};

#endif