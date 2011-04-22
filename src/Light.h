#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "globals.h"
#include "Object.h"

class Light : public Object
{
public:
    Light()             { Init(); }
    ~Light()            {}

    VECTOR3             GetCenter() const           { return m_v3Center; }
    virtual VECTOR3     GetNormal(INTERSECTION *pInter);

    virtual float       Intersects(RAY *pRay);
    virtual void        Print();
    virtual void        Refresh(int DeltaTime);

    void                SetCenter(VECTOR3 *pVec)    { m_v3Center.Set(pVec); }

private:	
    void                Init();

    VECTOR3             m_v3Center;
};

#endif
