#include "Eye.h"

#include <iostream>
using namespace std;

void Eye::Init()
{
    m_vPosition.Set(0.0f, 0.0f, 0.0f);
    m_vDirection.Set(0.0, 0.0, -1.0);
    m_fFoV = 45.0f;

    m_bUpdateNeeded = true;
}

void Eye::Print()
{
    cout << "Eye 0x" << hex << (unsigned int)this << dec << endl;
    cout << "  Position";
    m_vPosition.Print();
    cout << "  Direction";
    m_vDirection.Print();
    cout << "  FoV " << m_fFoV << endl;
}

void Eye::Refresh(int DeltaTime)
{

}

void Eye::SetDirection(VECTOR3 *pVec)
{
    m_vDirection.Set(pVec);
    m_bUpdateNeeded = true;
}

void Eye::SetFoV(float newFoV)
{
    m_fFoV = newFoV;
    m_bUpdateNeeded = true;
}
void Eye::SetPosition(VECTOR3 *pVec)
{
    m_vPosition.Set(pVec);
    m_bUpdateNeeded = true;
}

void Eye::SetUpdateNeeded(bool bUpdateNeeded)
{
    m_bUpdateNeeded = bUpdateNeeded;
}
