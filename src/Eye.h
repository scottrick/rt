#ifndef _EYE_H_
#define _EYE_H_

#include "globals.h"
#include "Unknown.h"

class Eye : public Unknown
{
public:
    Eye()           { Init(); }
    ~Eye()          {}

    VECTOR3         *GetDirection()                 { return &m_vDirection; }
    VECTOR3         *GetPosition()                  { return &m_vPosition; }

    virtual void    Print();

    virtual void    Refresh(int DeltaTime);

    void            SetAspectRatio(float newRatio)  { m_fAspectRatio = newRatio; }
    void            SetDirection(VECTOR3 *pVec)     { m_vDirection.Set(pVec); }
    void            SetFoV(float newFoV)            { m_fFoV = newFoV; }
    void            SetPosition(VECTOR3 *pVec)      { m_vPosition.Set(pVec); }

private:
    void            Init();

    VECTOR3         m_vDirection;
    VECTOR3         m_vPosition;

    float           m_fAspectRatio;
    float           m_fFoV; //in degrees
};

#endif
