#include "Scene.h"

#include "globals.h"
#include "PixelUtility.h"

#include <cassert>
#include <cmath>
#include <deque>
#include <fstream>
#include <string>
using namespace std;

Scene::Scene(unsigned int sizeX, unsigned int sizeY)
{
	m_BufferSizeX = sizeX;
	m_BufferSizeY = sizeY;

	Init();
}

Scene::~Scene()
{
	if (m_pBuffer)
	{
		delete m_pBuffer;
	}

	Clear();
}

void Scene::Add(const char *pFilename)
{
	if (!pFilename) {
		printf("File Not Found.\n");
		return;		
	}

	ifstream inStream;
	inStream.open(pFilename);

	if (inStream.fail()) {
		printf("Open Failed.\n");
		inStream.close();
		return;
	}
	
	float			fX;
	float			fY;
	float			fZ;
	float			fRadius;
	string			sNext;
	Material		currentMaterial;
	COLOR			cTemp;
	VECTOR3			vTemp;
	cTemp.a = 0.0f;

	while (inStream >> sNext) {
		//cout << sNext << endl;
	
		/*
		if (loadPolygons) {
			if (sNext == "polygon") {
				inStream >> sNext >> sNext;
	
				//only allow triangles
				if (sNext == "3") {
					float x, y, z;
					inStream >> sNext;
					sNext = sNext.substr(1, sNext.size() - 1);
					x = (float)atof(sNext.c_str());
					inStream >> sNext;
					y = (float)atof(sNext.c_str());
					inStream >> sNext;
					z = (float)atof(sNext.c_str());
					SVertex* pointOne = new SVertex(x, y, z);		

					inStream >> sNext;	
					sNext = sNext.substr(1, sNext.size() - 1);
					x = (float)atof(sNext.c_str());
					inStream >> sNext;
					y = (float)atof(sNext.c_str());
					inStream >> sNext;
					z = (float)atof(sNext.c_str());
					SVertex* pointTwo = new SVertex(x, y, z);

					inStream >> sNext;
					sNext = sNext.substr(1, sNext.size() - 1);
					x = (float)atof(sNext.c_str());
					inStream >> sNext;
					y = (float)atof(sNext.c_str());
					inStream >> sNext;
					z = (float)atof(sNext.c_str());
					SVertex* pointThree = new SVertex(x, y, z);

					Triangle* newTriangle = new Triangle(pointOne, pointTwo, pointThree, currentMaterial);
					newTriangle->print();
					theObjects.push_back(newTriangle);
				}		
			}
		}
		*/

		if (sNext == "material") {
			inStream >> sNext >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			cTemp.r = (float)atof(sNext.c_str());
			inStream >> sNext;
			cTemp.g = (float)atof(sNext.c_str());
			inStream >> sNext;
			cTemp.b = (float)atof(sNext.c_str());
			currentMaterial.SetDiffuseColor(&cTemp);

			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			cTemp.r = (float)atof(sNext.c_str());
			inStream >> sNext;
			cTemp.g = (float)atof(sNext.c_str());
			inStream >> sNext;
			cTemp.b = (float)atof(sNext.c_str());
			currentMaterial.SetSpecularColor(&cTemp);
			
			/*
			inStream >> sNext >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			uR = (unsigned int)atoi(sNext.c_str());
			inStream >> sNext;
			uG = (unsigned int)atoi(sNext.c_str());
			inStream >> sNext;
			uB = (unsigned int)atoi(sNext.c_str());
			SetR(&cTemp, uR);
			SetG(&cTemp, uG);
			SetB(&cTemp, uB);
			currentMaterial.SetDiffuseColor(&cTemp);

			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			uR = (unsigned int)atoi(sNext.c_str());
			inStream >> sNext;
			uG = (unsigned int)atoi(sNext.c_str());
			inStream >> sNext;
			uB = (unsigned int)atoi(sNext.c_str());
			SetR(&cTemp, uR);
			SetG(&cTemp, uG);
			SetB(&cTemp, uB);
			currentMaterial.SetSpecularColor(&cTemp);
			*/

			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			currentMaterial.SetAmbientCoef((float)atof(sNext.c_str()));
			inStream >> sNext;
			currentMaterial.SetDiffuseCoef((float)atof(sNext.c_str()));
			inStream >> sNext;
			currentMaterial.SetSpecularCoef((float)atof(sNext.c_str()));
			inStream >> sNext;
			currentMaterial.SetSpecularExp((float)atof(sNext.c_str()));
			inStream >> sNext;
			currentMaterial.SetTransparency((float)atof(sNext.c_str()));
			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			currentMaterial.SetRefractIndexEnv((float)atof(sNext.c_str()));
			inStream >> sNext;
			currentMaterial.SetRefractIndexObject((float)atof(sNext.c_str()));
		}

		if (sNext == "sphere") {
			inStream >> sNext >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			fX = (float)atof(sNext.c_str());
			
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			inStream >> sNext;
			fRadius = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);

			Sphere *pSphere = new Sphere();
			pSphere->SetCenter(&vTemp);
			pSphere->SetMaterial(&currentMaterial);
			pSphere->SetRadius(fRadius);
			
			m_Objects.push_back(pSphere);
		}

		if (sNext == "image") {
			//get top left
			inStream >> sNext >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			fX = (float)atof(sNext.c_str());
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);
			m_Eye.SetTopLeft(&vTemp);

			//get top right
			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			fX = (float)atof(sNext.c_str());
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);
			m_Eye.SetTopRight(&vTemp);

			//get bottom right
			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			fX = (float)atof(sNext.c_str());
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);
			m_Eye.SetBottomRight(&vTemp);

			//get bottom left
			inStream >> sNext;
			sNext = sNext.substr(1, sNext.size() - 1);
			fX = (float)atof(sNext.c_str());
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);
			m_Eye.SetBottomLeft(&vTemp);
		}

		if (sNext == "eye") {
			inStream >> sNext >> sNext;
			fX = (float)atof(sNext.c_str());
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);
			m_Eye.SetPosition(&vTemp);
		}	

		if (sNext == "light") {
			inStream >> sNext >> sNext;
			fX = (float)atof(sNext.c_str());
			inStream >> sNext;
			fY = (float)atof(sNext.c_str());
			inStream >> sNext;
			fZ = (float)atof(sNext.c_str());
			vTemp.Set(fX, fY, fZ);

			inStream >> sNext;
			//int type = (int)atoi(sNext.c_str());  //TYPE IS BEING IGNORED RIGHT NOW
			
			Light *pLight = new Light();
			pLight->SetCenter(&vTemp);
			pLight->SetMaterial(&currentMaterial);

			m_Lights.push_back(pLight);
		}
	}
	
	inStream.close();	
}

void Scene::Clear()
{
	Light *pCurrentLight = 0;
	for (unsigned int i = 0; i < m_Lights.size(); i++)
	{
		pCurrentLight = m_Lights[i];
		if (pCurrentLight)
		{
			delete pCurrentLight;
			m_Lights[i] = 0;
		}
	}

	Object *pCurrentObject = 0;
	for (unsigned int i = 0; i < m_Objects.size(); i++)
	{
		pCurrentObject = m_Objects[i];
		if (pCurrentObject)
		{
			delete pCurrentObject;
			m_Objects[i] = 0;
		}
	}
}

void Scene::DecreaseThreadCount()
{
	m_ThreadCountMutex.lock();
	//assert(m_dwThreadCount > 0);
	m_dwThreadCount--;
	m_ThreadCountMutex.unlock();
}	

COLOR Scene::FindColor(RAY *pRay)
{
	m_dwNumRaysShot++;

	COLOR theColor;
	theColor.Set(0.0f, 0.0f, 0.0f, 0.0f);

	//deque<INTERSECTION *> intersections;
	INTERSECTION bestIntersection;
	bestIntersection.object = 0;
	bestIntersection.ray	= 0;
	bestIntersection.t		= 0.0f;

	for (unsigned int i = 0; i < m_Objects.size(); i++)
	{
		float fNewT = m_Objects[i]->Intersects(pRay);
		
		//make sure its a valid T
		if (fNewT != 0.0f)
		{
			//see if this new T is closer than the current best one (or one doesn't already exist)
			if ((bestIntersection.object == 0) || (fNewT < bestIntersection.t))
			{
				bestIntersection.object = m_Objects[i];
				bestIntersection.ray	= pRay;
				bestIntersection.t		= fNewT;
			}
		}

		/*
		pCurrent = m_Objects[i]->Intersects(pRay);
		if (pCurrent)
		{
			intersections.push_back(pCurrent);
			pCurrent = 0;
		}
		*/
	}

	if (bestIntersection.object == 0) //no intersections, so return black color
	{
		return theColor;
	}
	else //there were some intersections, so now find the closest one (smallest T value)!
	{	
		/*
		unsigned int closest = 0;
		for (unsigned int i = 0; i < intersections.size(); i++)
		{
			if (intersections[i]->t < intersections[closest]->t) //current intersection is closer than the current best
			{
				closest = i;
			}
		}
		*/

		Object	*pObject = bestIntersection.object;
		VECTOR3 IntersectPoint = bestIntersection.ray->ValueWhenT(bestIntersection.t);
		//VECTOR3 IntersectPoint = intersections[closest]->ray->ValueWhenT(intersections[closest]->t);
		COLOR	CurrentPart;
		
		//AMBIENT Part
		//*****************************c********************************************************************
		CurrentPart.Set(pObject->GetMaterial().GetDiffuseColor());
		CurrentPart.Scale(pObject->GetMaterial().GetAmbientCoef());
		theColor.Add(&CurrentPart);
		//*************************************************************************************************

		//SPECULAR and DIFFUSE Part
		//*************************************************************************************************
		VECTOR3		vLightDirection;
		VECTOR3		vL;
		VECTOR3		vNormal		= pObject->GetNormal(&bestIntersection);
		float		fValue		= -2.0f * (pRay->vDirection.DotProduct(&vNormal));
		VECTOR3		vReflectDirection;

		vReflectDirection.x = pRay->vDirection.x + (fValue * vNormal.x);
		vReflectDirection.y = pRay->vDirection.y + (fValue * vNormal.y);
		vReflectDirection.z = pRay->vDirection.z + (fValue * vNormal.z);
		vReflectDirection.Normalize();

		for (unsigned int i = 0; i < m_Lights.size(); i++) 
		{
			Light *pLight = m_Lights[i];

			if (pLight)
			{
				CurrentPart.Set(pObject->GetMaterial().GetDiffuseColor());

				vLightDirection.x	= pLight->GetCenter().x - IntersectPoint.x;
				vLightDirection.y	= pLight->GetCenter().y - IntersectPoint.y;
				vLightDirection.z	= pLight->GetCenter().z - IntersectPoint.z;
				vLightDirection.Normalize();
				
				//only use the light if it is facing the intersection normal
				if (vLightDirection.DotProduct(&vNormal) >= 0.0f)
				{
					
					//shoot a ray from the intersection point to the current light to see if it is visible, or is in shadow
					//deque<INTERSECTION *>	shadowIntersections;
					RAY						rayToLight;
					//INTERSECTION			*pNewIntersection		= 0;
					rayToLight.vStart								= IntersectPoint;
					rayToLight.vDirection							= vLightDirection;
					bool					bObjectInTheWay			= false;
					float					fDistance				= DistanceBetween(IntersectPoint, pLight->GetCenter());

					//find any intersections on the shadow ray
					for (unsigned int k = 0; k < m_Objects.size(); k++)
					{
						float fShadowT = m_Objects[k]->Intersects(&rayToLight);
						if (fShadowT > 0.0f)
						{ //intersection occurred
							if (fShadowT < fDistance)
							{ //intersection occurred before the light, so it is in shadow
								bObjectInTheWay = true;
								k = m_Objects.size();
							}
							//shadowIntersections.push_back(pNewIntersection);
							//pNewIntersection = 0;
						}
					}

					/*
					for (unsigned int k = 0; k < shadowIntersections.size(); k++)
					{
						pNewIntersection = shadowIntersections.at(0);
						if (pNewIntersection->t < fDistance)
						{ //intersection happens before the light, so it is in shadow
							bObjectInTheWay = true;
							break;
						}
					}*/

					/*
					//delete all the shadowIntersections
					while (shadowIntersections.size() > 0)
					{
						delete shadowIntersections[0];
						shadowIntersections.pop_front();
					}
					*/

					if (!bObjectInTheWay)
					{
						//DIFFUSE PART
						if (USE_FAST_MATH)
						{
							fValue	= InvSqrt((vLightDirection.x * vLightDirection.x) + (vLightDirection.y * vLightDirection.y) + (vLightDirection.z * vLightDirection.z));
							vL.x = vLightDirection.x * fValue;
							vL.y = vLightDirection.y * fValue;
							vL.z = vLightDirection.z * fValue;
						}
						else
						{
							fValue	= sqrt((vLightDirection.x * vLightDirection.x) + (vLightDirection.y * vLightDirection.y) + (vLightDirection.z * vLightDirection.z));
							vL.x = vLightDirection.x / fValue;
							vL.y = vLightDirection.y / fValue;
							vL.z = vLightDirection.z / fValue;
						}
						
						fValue = pObject->GetMaterial().GetDiffuseCoef() * vL.DotProduct(&vNormal);
						CurrentPart.Scale(fValue);
						
						theColor.Add(&CurrentPart);

						//SPECULAR PART
						float phongTerm = vReflectDirection.DotProduct(&vLightDirection);
						if (phongTerm > 0.0f)
						{
							phongTerm = pObject->GetMaterial().GetSpecularCoef() * pow(phongTerm, pObject->GetMaterial().GetSpecularExp());
							CurrentPart.Set(pObject->GetMaterial().GetSpecularColor());
							CurrentPart.Scale(phongTerm);
							//at this time, not considering that a light could be of a color other than white
							theColor.Add(&CurrentPart);
						}
						else
						{
							phongTerm = 0.0f;
							//there is no Specular part, so add nothing!
						}
					}
				}
			}
		}
		//*************************************************************************************************

		//Shoot a REFLECTION Ray
		//*************************************************************************************************
		if (pRay->dwGeneration < MAX_NUM_RAY_GENERATIONS)
		{
			RAY reflectionRay;
			reflectionRay.dwGeneration	= pRay->dwGeneration + 1;
			reflectionRay.vDirection	= vReflectDirection;
			reflectionRay.vStart		= IntersectPoint;

			CurrentPart = FindColor(&reflectionRay);
			CurrentPart.Scale(pObject->GetMaterial().GetSpecularCoef());
			theColor.Add(&CurrentPart);
		}

		//*************************************************************************************************

		/*
		//delete all the intersections
		while (intersections.size() > 0)
		{
			delete intersections[0];
			intersections.pop_front();
		}
		*/

		return theColor;
	}
}	

int Scene::GetNextRayIndex()
{
	m_RayIndexMutex.lock();

	int returnIndex = m_dwNextRayIndex;

	if (m_dwNextRayIndex >= 0)
	{ //only increment if its not negative
		m_dwNextRayIndex++;
	}

	if (m_dwNextRayIndex > (int)(m_BufferSizeX * m_BufferSizeY))
	{ //all done!
		m_dwNextRayIndex = -1;
		returnIndex = -1; //ALL DONE WITH THE RAYS!
	}

	m_RayIndexMutex.unlock();

	return returnIndex;
}

RAY *Scene::GetRay(unsigned int index)
{
	assert(index < (m_BufferSizeX * m_BufferSizeY));

	return m_Rays + index;
}

RAY *Scene::GetRay(unsigned int x, unsigned int y)
{
	assert((x < m_BufferSizeX) && (y < m_BufferSizeY));

	return m_Rays + (y * m_BufferSizeX) + x;
}

unsigned int Scene::GetThreadCount()
{
	int count = 0;

	m_ThreadCountMutex.lock();
	count = m_dwThreadCount;
	m_ThreadCountMutex.unlock();

	return count;
}

void Scene::IncreaseThreadCount()
{
	m_ThreadCountMutex.lock();
	m_dwThreadCount++;
	m_ThreadCountMutex.unlock();
}

void Scene::Init()
{
	m_pBuffer				= new Buffer(m_BufferSizeX, m_BufferSizeY);
	m_Rays					= (RAY *)malloc(m_BufferSizeX * m_BufferSizeY * sizeof(RAY));
	m_dwNextRayIndex		= -1;
	m_dwNumRaysShot			= 0;
	m_dwThreadCount			= 0;
}

unsigned int Scene::PeekNextRayIndex()
{
	int index = 0;

	m_RayIndexMutex.lock();
	index = m_dwNextRayIndex;
	m_RayIndexMutex.unlock();

	return index;
}	

void Scene::Print()
{
	printf("SCENE          0x%x\n", this);
	printf("Size           = (%u, %u)\n", m_BufferSizeX, m_BufferSizeY);
	printf("Buffer         = 0x%x\n\n", m_pBuffer);
	
	m_Eye.Print();
	printf("\n");

	for (unsigned int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Print();
		printf("\n");
	}
	for (unsigned int i = 0; i < m_Lights.size(); i++)
	{
		m_Lights[i]->Print();
		printf("\n");
	}
}

void Scene::ProcessRays()
{
	for (unsigned int x = 0; x < m_BufferSizeX; x++)
	{
		for (unsigned int y = 0; y < m_BufferSizeY; y++)
		{
			m_pBuffer->SetColor(x, y, &FindColor(GetRay(x, y)));
		}
	}
}

void Scene::Refresh(int DeltaTime)
{
	m_Eye.Refresh(DeltaTime);
	for (unsigned int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Refresh(DeltaTime);
	}
	for (unsigned int i = 0; i < m_Lights.size(); i++)
	{
		m_Lights[i]->Refresh(DeltaTime);
	}

	UpdateRays();

	m_dwNextRayIndex	= 0;
	m_dwNumRaysShot		= 0;
}

void Scene::ShootRays()
{	
	//IncreaseThreadCount();

	//printf("Starting Ray Thread...\n");
	int dwNextRay					= 0;
	//int dwNumRaysThisThreadShot		= 0;

	while (true)
	{
		dwNextRay = GetNextRayIndex();
		if (dwNextRay >= 0)
		{
			m_pBuffer->SetColor(dwNextRay, &FindColor(GetRay(dwNextRay)));
			//dwNumRaysThisThreadShot++;
		}
	}

	//printf("ShootRays() Finished.\n  Shot %d base rays of %d.  Total number of rays shot was %d.\n", dwNumRaysThisThreadShot, m_BufferSizeX * m_BufferSizeY, GetNumRaysShot());
	//DecreaseThreadCount();
}

void Scene::UpdateRays()
{
	float fBufferX	= (float)m_BufferSizeX;
	float fBufferY	= (float)m_BufferSizeY;
	float fNewX		= 0.0f;
	float fNewY		= 0.0f;
	float fNewZ		= 0.0f;
	RAY *pCurrent = 0;
	for (unsigned int x = 0; x < m_BufferSizeX; x++)
	{
		for (unsigned int y = 0; y < m_BufferSizeY; y++)
		{
			pCurrent = GetRay(x, y);
			pCurrent->dwGeneration = 0;
			pCurrent->vStart.Set(m_Eye.GetPosition());

			/*
			float fLowerLeftMultiplier;
			float fLowerRightMultiplier;
			float UpperLeftMultiplier;
			float UpperRightMultiplier;

			fLowerLeftMultiplier = ((fBufferY - (float)y) / fBufferY) * ((fBufferX - (float)x) / fBufferX);
			fLowerRightMultiplier = ((fBufferY - (float)y) / fBufferY) * ((float)x / fBufferX);
			UpperLeftMultiplier = ((float)y / fBufferY) * ((fBufferX - (float)x) / fBufferX);
			UpperRightMultiplier = ((float)y / fBufferY) * ((float)x / fBufferX);

			fNewX = (fLowerLeftMultiplier * m_Eye.GetBottomLeft()->x) + (fLowerRightMultiplier * m_Eye.GetBottomRight()->x) + (UpperLeftMultiplier * m_Eye.GetTopLeft()->x) + (UpperRightMultiplier * m_Eye.GetTopRight()->x);
			fNewY = (fLowerLeftMultiplier * m_Eye.GetBottomLeft()->y) + (fLowerRightMultiplier * m_Eye.GetBottomRight()->y) + (UpperLeftMultiplier * m_Eye.GetTopLeft()->y) + (UpperRightMultiplier * m_Eye.GetTopRight()->y);
			fNewZ = (fLowerLeftMultiplier * m_Eye.GetBottomLeft()->z) + (fLowerRightMultiplier * m_Eye.GetBottomRight()->z) + (UpperLeftMultiplier * m_Eye.GetTopLeft()->z) + (UpperRightMultiplier * m_Eye.GetTopRight()->z);
			*/

			fNewX = (m_Eye.GetTopRight()->x - m_Eye.GetTopLeft()->x) * ((float)x / fBufferX) + m_Eye.GetTopLeft()->x;
			fNewY = m_Eye.GetTopLeft()->y - (m_Eye.GetTopLeft()->y - m_Eye.GetBottomLeft()->y) * ((float)y / fBufferY);
			fNewZ = m_Eye.GetTopLeft()->z;
			
			pCurrent->vDirection.Set(fNewX - m_Eye.GetPosition()->x, fNewY - m_Eye.GetPosition()->y, fNewZ - m_Eye.GetPosition()->z);
		}
	}
}