#include "Eye.h"

#include <iostream>
using namespace std;

void Eye::Init()
{
    m_v3Position.Set(0.0f, 0.0f, 0.0f);
    m_v3TopLeft.Set(0.0f, 0.0f, 0.0f);
    m_v3TopRight.Set(0.0f, 0.0f, 0.0f);
    m_v3BottomLeft.Set(0.0f, 0.0f, 0.0f);
    m_v3BottomRight.Set(0.0f, 0.0f, 0.0f);
}

void Eye::Print()
{
    cout << "Eye 0x" << hex << (unsigned int)this << dec << endl;

//    printf("Position       = ");
//    m_v3Position.Print();
//    printf("TopLeft        = ");
//    m_v3TopLeft.Print();
//    printf("TopRight       = ");
//    m_v3TopRight.Print();
//    printf("BottomLeft     = ");
//    m_v3BottomLeft.Print();
//    printf("BottomRight    = ");
//    m_v3BottomRight.Print();
}

void Eye::Refresh(int DeltaTime)
{

}
