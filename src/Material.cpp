#include "Material.h"

#include "PixelUtility.h"

#include <iostream>
using namespace std;

void Material::Init()
{
    m_DiffuseColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
    m_SpecularColor.Set(0.0f, 0.0f, 0.0f, 1.0f);
    m_fAmbientCoef				= 0.0f;
    m_fDiffuseCoef				= 0.0f;
    m_fSpecularCoef				= 0.0f;
    m_fSpecularExp				= 0.0f;
    m_fTransparency				= 0.0f;
    m_fRefractIndexEnv			= 0.0f;
    m_fRefractIndexObject		= 0.0f;
}

void Material::Print()
{
    cout << "Material 0x" << hex << (unsigned int)this << dec << endl;
    cout << " Diffuse ";
    m_DiffuseColor.Print();
    cout << " Specular ";
    m_SpecularColor.Print();

    cout << " AmbientCoef " << m_fAmbientCoef << endl;
    cout << " DiffuseCoef " << m_fDiffuseCoef << endl;
    cout << " SpeculrCoef " << m_fSpecularCoef << endl;
    cout << " SpecularExp " << m_fSpecularExp << endl;
    cout << " TransparenC " << m_fTransparency << endl;
    cout << " RefractEnv  " << m_fRefractIndexEnv << endl;
    cout << " RefractObj  " << m_fRefractIndexObject << endl;
}

void Material::Refresh(int DeltaTime)
{

}

void Material::Set(Material *pMat)
{
    m_DiffuseColor.Set(pMat->GetDiffuseColor());
    m_SpecularColor.Set(pMat->GetSpecularColor());
    m_fAmbientCoef				= pMat->GetAmbientCoef();
    m_fDiffuseCoef				= pMat->GetDiffuseCoef();
    m_fSpecularCoef				= pMat->GetSpecularCoef();
    m_fSpecularExp				= pMat->GetSpecularExp();
    m_fTransparency				= pMat->GetTransparency();
    m_fRefractIndexEnv			= pMat->GetRefractIndexEnv();
    m_fRefractIndexObject		= pMat->GetRefractIndexObject();
}
