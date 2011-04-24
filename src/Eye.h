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
    float           GetFoV() const                  { return m_fFoV; }
    VECTOR3         *GetPosition()                  { return &m_vPosition; }

    bool            IsUpdateNeeded() const          { return m_bUpdateNeeded; }

    virtual void    Print();

    virtual void    Refresh(int DeltaTime);

    void            SetDirection(VECTOR3 *pVec);
    void            SetFoV(float newFoV);
    void            SetPosition(VECTOR3 *pVec);
    void            SetUpdateNeeded(bool bUpdateNeeded);

private:
    void            Init();

    VECTOR3         m_vDirection;
    VECTOR3         m_vPosition;

    float           m_fFoV; //in degrees

    bool            m_bUpdateNeeded;
};

#endif
