#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Material.h"
#include "Unknown.h"

struct INTERSECTION;

class Object : public Unknown
{
public:
    Object()            {};
    ~Object()           {};

    Material            GetMaterial()                           { return m_Material; }
    virtual VECTOR3     GetNormal(INTERSECTION *pInter)         = 0;

    virtual float       Intersects(RAY *pRay)                   = 0; //return 0.0f if no intersection occurs!
    virtual void        Print()                                 { m_Material.Print(); }
    virtual void        Refresh(int DeltaTime)                  = 0;

    void                SetMaterial(Material *pMat)             { m_Material.Set(pMat); }

private:
    Material            m_Material;

};

struct INTERSECTION
{
    float	t;
    Object	*object;
    RAY		*ray;
    //bool	bEntering;
};

#endif
