#ifndef _EYE_H_
#define _EYE_H_

#include "globals.h"
#include "Unknown.h"

class Eye : public Unknown
{
public:
	Eye()				{ Init(); }
	~Eye()				{}

	VECTOR3				*GetBottomLeft()					{ return &m_v3BottomLeft; }
	VECTOR3				*GetBottomRight()					{ return &m_v3BottomRight; }
	VECTOR3				*GetPosition()						{ return &m_v3Position; }
	VECTOR3				*GetTopLeft()						{ return &m_v3TopLeft; }
	VECTOR3				*GetTopRight()						{ return &m_v3TopRight; }

	virtual void		Print();
	
	virtual void		Refresh(int DeltaTime);

	void				SetBottomLeft(VECTOR3 *pVec)		{ m_v3BottomLeft.Set(pVec); }
	void				SetBottomRight(VECTOR3 *pVec)		{ m_v3BottomRight.Set(pVec); }
	void				SetPosition(VECTOR3 *pVec)			{ m_v3Position.Set(pVec); }
	void				SetTopLeft(VECTOR3 *pVec)			{ m_v3TopLeft.Set(pVec); }
	void				SetTopRight(VECTOR3 *pVec)			{ m_v3TopRight.Set(pVec); }

private:
	void				Init();

	VECTOR3				m_v3BottomLeft;
	VECTOR3				m_v3BottomRight;
	VECTOR3				m_v3Position;
	VECTOR3				m_v3TopLeft;
	VECTOR3				m_v3TopRight;
};

#endif