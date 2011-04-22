#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "globals.h"
#include "Unknown.h"

class Material : public Unknown
{
public:
	Material()					{ Init(); }
	~Material()					{}

	float						GetAmbientCoef()					{ return m_fAmbientCoef; }
	float						GetDiffuseCoef()					{ return m_fDiffuseCoef; }
	COLOR						*GetDiffuseColor()					{ return &m_DiffuseColor; }
	float						GetRefractIndexEnv()				{ return m_fRefractIndexEnv; }
	float						GetRefractIndexObject()				{ return m_fRefractIndexObject; }
	float						GetSpecularCoef()					{ return m_fSpecularCoef; }
	COLOR						*GetSpecularColor()					{ return &m_SpecularColor; }
	float						GetSpecularExp()					{ return m_fSpecularExp; }
	float						GetTransparency()					{ return m_fTransparency; }

	virtual void				Print();
	virtual void				Refresh(int DeltaTime);
	void						Set(Material *pMat);
	void						SetAmbientCoef(float fVal)			{ m_fAmbientCoef = fVal; }
	void						SetDiffuseCoef(float fVal)			{ m_fDiffuseCoef = fVal; }
	void						SetDiffuseColor(COLOR *pColor)		{ m_DiffuseColor.Set(pColor); }
	void						SetRefractIndexEnv(float fVal)		{ m_fRefractIndexEnv = fVal; }
	void						SetRefractIndexObject(float fVal)	{ m_fRefractIndexObject = fVal; }
	void						SetSpecularCoef(float fVal)			{ m_fSpecularCoef = fVal; }
	void						SetSpecularColor(COLOR *pColor)		{ m_SpecularColor.Set(pColor); }
	void						SetSpecularExp(float fVal)			{ m_fSpecularExp = fVal; }
	void						SetTransparency(float fVal)			{ m_fTransparency = fVal; }

private:
	void						Init();

	COLOR						m_DiffuseColor;
	COLOR						m_SpecularColor;
	
	float						m_fAmbientCoef;
	float						m_fDiffuseCoef;
	float						m_fRefractIndexEnv;
	float						m_fRefractIndexObject;
	float						m_fSpecularCoef;
	float						m_fSpecularExp;
	float						m_fTransparency;
};

#endif