#include "Material.h"

#include "PixelUtility.h"

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
	printf("MATERIAL       0x%x\n", this);
	//printf("DiffuseColor   = (%u, %u, %u, %u)\n", GetR(&m_DiffuseColor), GetG(&m_DiffuseColor), GetB(&m_DiffuseColor), GetA(&m_DiffuseColor));
	//printf("SpecularColor  = (%u, %u, %u, %u)\n", GetR(&m_SpecularColor), GetG(&m_SpecularColor), GetB(&m_SpecularColor), GetA(&m_SpecularColor));
	printf("DiffuseColor   = ");
	m_DiffuseColor.Print();
	printf("SpecularColor  = ");
	m_SpecularColor.Print();
	printf("AmbientCoef    = %f\n", m_fAmbientCoef);
	printf("DiffuseCoef    = %f\n", m_fDiffuseCoef);
	printf("SpeculafCoef   = %f\n", m_fSpecularCoef);
	printf("SpecularExp    = %f\n", m_fSpecularExp);
	printf("Transparency   = %f\n", m_fTransparency);
	printf("RefractEnv     = %f\n", m_fRefractIndexEnv);
	printf("RefractObject  = %f\n", m_fRefractIndexObject);
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