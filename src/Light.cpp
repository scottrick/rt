#include "Light.h"

#include <iostream>
using namespace std;

VECTOR3 Light::GetNormal(INTERSECTION *pInter)
{
    VECTOR3 returnValue;
    returnValue.Set(0.0f, 0.0f, 0.0f);
    return returnValue;
}

void Light::Init()
{
    m_v3Center.Set(0.0f, 0.0f, 0.0f);
}

float Light::Intersects(RAY *pRay)
{
    return 0.0f;
}

void Light::Print()
{
    cout << "Light 0x" << hex << (unsigned int)this << dec << endl;
    cout << "  Center ";
    m_v3Center.Print();
    Object::Print();
}

void Light::Refresh(int DeltaTime)
{

}
