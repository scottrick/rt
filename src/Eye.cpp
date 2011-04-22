#include "Eye.h"

#include <iostream>
using namespace std;

void Eye::Init()
{
    m_vPosition.Set(0.0f, 0.0f, 0.0f);
    m_vDirection.Set(0.0, 0.0, -1.0);
}

void Eye::Print()
{
    cout << "Eye 0x" << hex << (unsigned int)this << dec << endl;
    cout << "  Position";
    m_vPosition.Print();
    cout << "  Direction";
    m_vDirection.Print();
    cout << "  FoV " << m_fFoV << endl;
    cout << "  AspectRatio " << m_fAspectRatio << endl;
}

void Eye::Refresh(int DeltaTime)
{

}
