#include "Scene.h"

#include "globals.h"
#include "PixelUtility.h"

#include <cassert>
#include <cmath>
#include <deque>
#include <fstream>
#include <string>
using namespace std;

Scene::Scene(const char *pFilename)
{
    Init();

    if (pFilename)
    {
        Add(pFilename);
    }
}

Scene::~Scene()
{
    Clear();
}

void Scene::Add(const char *pFilename)
{
    if (!pFilename)
    {
        cout << "NULL filename!" << endl;
        return;
    }

    ifstream inStream;
    inStream.open(pFilename);

    if (inStream.fail())
    {
        cout << "Failed to open file " << pFilename << endl;
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

        if (sNext == "eye")
        {
            //read position
            inStream >> sNext >> sNext;
            fX = (float)atof(sNext.c_str());
            inStream >> sNext;
            fY = (float)atof(sNext.c_str());
            inStream >> sNext;
            fZ = (float)atof(sNext.c_str());
            vTemp.Set(fX, fY, fZ);
            m_Eye.SetPosition(&vTemp);

            //read dir
            inStream >> sNext;
            sNext = sNext.substr(1, sNext.size() - 1);

            fX = (float)atof(sNext.c_str());
            inStream >> sNext;
            fY = (float)atof(sNext.c_str());
            inStream >> sNext;
            fZ = (float)atof(sNext.c_str());
            vTemp.Set(fX, fY, fZ);
            m_Eye.SetDirection(&vTemp);

            //read FoV
            inStream >> sNext;
            fX = (float)atof(sNext.c_str());
            m_Eye.SetFoV(fX);

            //read AspectRatio
            inStream >> sNext;
            fX = (float)atof(sNext.c_str());
            m_Eye.SetAspectRatio(fX);

            m_Eye.Print();
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

//COLOR Scene::FindColor(RAY *pRay)
//{
//    m_dwNumRaysShot++;

//    COLOR theColor;
//    theColor.Set(0.0f, 0.0f, 0.0f, 0.0f);

//    //deque<INTERSECTION *> intersections;
//    INTERSECTION bestIntersection;
//    bestIntersection.object = 0;
//    bestIntersection.ray	= 0;
//    bestIntersection.t		= 0.0f;

//    for (unsigned int i = 0; i < m_Objects.size(); i++)
//    {
//        float fNewT = m_Objects[i]->Intersects(pRay);

//        //make sure its a valid T
//        if (fNewT != 0.0f)
//        {
//            //see if this new T is closer than the current best one (or one doesn't already exist)
//            if ((bestIntersection.object == 0) || (fNewT < bestIntersection.t))
//            {
//                bestIntersection.object = m_Objects[i];
//                bestIntersection.ray	= pRay;
//                bestIntersection.t		= fNewT;
//            }
//        }

//        /*
//		pCurrent = m_Objects[i]->Intersects(pRay);
//		if (pCurrent)
//		{
//			intersections.push_back(pCurrent);
//			pCurrent = 0;
//		}
//		*/
//    }

//    if (bestIntersection.object == 0) //no intersections, so return black color
//    {
//        return theColor;
//    }
//    else //there were some intersections, so now find the closest one (smallest T value)!
//    {
//        /*
//		unsigned int closest = 0;
//		for (unsigned int i = 0; i < intersections.size(); i++)
//		{
//			if (intersections[i]->t < intersections[closest]->t) //current intersection is closer than the current best
//			{
//				closest = i;
//			}
//		}
//		*/

//        Object	*pObject = bestIntersection.object;
//        VECTOR3 IntersectPoint = bestIntersection.ray->ValueWhenT(bestIntersection.t);
//        //VECTOR3 IntersectPoint = intersections[closest]->ray->ValueWhenT(intersections[closest]->t);
//        COLOR	CurrentPart;

//        //AMBIENT Part
//        //*****************************c********************************************************************
//        CurrentPart.Set(pObject->GetMaterial().GetDiffuseColor());
//        CurrentPart.Scale(pObject->GetMaterial().GetAmbientCoef());
//        theColor.Add(&CurrentPart);
//        //*************************************************************************************************

//        //SPECULAR and DIFFUSE Part
//        //*************************************************************************************************
//        VECTOR3		vLightDirection;
//        VECTOR3		vL;
//        VECTOR3		vNormal		= pObject->GetNormal(&bestIntersection);
//        float		fValue		= -2.0f * (pRay->vDirection.DotProduct(&vNormal));
//        VECTOR3		vReflectDirection;

//        vReflectDirection.x = pRay->vDirection.x + (fValue * vNormal.x);
//        vReflectDirection.y = pRay->vDirection.y + (fValue * vNormal.y);
//        vReflectDirection.z = pRay->vDirection.z + (fValue * vNormal.z);
//        vReflectDirection.Normalize();

//        for (unsigned int i = 0; i < m_Lights.size(); i++)
//        {
//            Light *pLight = m_Lights[i];

//            if (pLight)
//            {
//                CurrentPart.Set(pObject->GetMaterial().GetDiffuseColor());

//                vLightDirection.x	= pLight->GetCenter().x - IntersectPoint.x;
//                vLightDirection.y	= pLight->GetCenter().y - IntersectPoint.y;
//                vLightDirection.z	= pLight->GetCenter().z - IntersectPoint.z;
//                vLightDirection.Normalize();

//                //only use the light if it is facing the intersection normal
//                if (vLightDirection.DotProduct(&vNormal) >= 0.0f)
//                {

//                    //shoot a ray from the intersection point to the current light to see if it is visible, or is in shadow
//                    //deque<INTERSECTION *>	shadowIntersections;
//                    RAY						rayToLight;
//                    //INTERSECTION			*pNewIntersection		= 0;
//                    rayToLight.vStart								= IntersectPoint;
//                    rayToLight.vDirection							= vLightDirection;
//                    bool					bObjectInTheWay			= false;
//                    float					fDistance				= DistanceBetween(IntersectPoint, pLight->GetCenter());

//                    //find any intersections on the shadow ray
//                    for (unsigned int k = 0; k < m_Objects.size(); k++)
//                    {
//                        float fShadowT = m_Objects[k]->Intersects(&rayToLight);
//                        if (fShadowT > 0.0f)
//                        { //intersection occurred
//                            if (fShadowT < fDistance)
//                            { //intersection occurred before the light, so it is in shadow
//                                bObjectInTheWay = true;
//                                k = m_Objects.size();
//                            }
//                            //shadowIntersections.push_back(pNewIntersection);
//                            //pNewIntersection = 0;
//                        }
//                    }

//                    /*
//					for (unsigned int k = 0; k < shadowIntersections.size(); k++)
//					{
//						pNewIntersection = shadowIntersections.at(0);
//						if (pNewIntersection->t < fDistance)
//						{ //intersection happens before the light, so it is in shadow
//							bObjectInTheWay = true;
//							break;
//						}
//					}*/

//                    /*
//					//delete all the shadowIntersections
//					while (shadowIntersections.size() > 0)
//					{
//						delete shadowIntersections[0];
//						shadowIntersections.pop_front();
//					}
//					*/

//                    if (!bObjectInTheWay)
//                    {
//                        //DIFFUSE PART
//                        if (USE_FAST_MATH)
//                        {
//                            fValue	= InvSqrt((vLightDirection.x * vLightDirection.x) + (vLightDirection.y * vLightDirection.y) + (vLightDirection.z * vLightDirection.z));
//                            vL.x = vLightDirection.x * fValue;
//                            vL.y = vLightDirection.y * fValue;
//                            vL.z = vLightDirection.z * fValue;
//                        }
//                        else
//                        {
//                            fValue	= sqrt((vLightDirection.x * vLightDirection.x) + (vLightDirection.y * vLightDirection.y) + (vLightDirection.z * vLightDirection.z));
//                            vL.x = vLightDirection.x / fValue;
//                            vL.y = vLightDirection.y / fValue;
//                            vL.z = vLightDirection.z / fValue;
//                        }

//                        fValue = pObject->GetMaterial().GetDiffuseCoef() * vL.DotProduct(&vNormal);
//                        CurrentPart.Scale(fValue);

//                        theColor.Add(&CurrentPart);

//                        //SPECULAR PART
//                        float phongTerm = vReflectDirection.DotProduct(&vLightDirection);
//                        if (phongTerm > 0.0f)
//                        {
//                            phongTerm = pObject->GetMaterial().GetSpecularCoef() * pow(phongTerm, pObject->GetMaterial().GetSpecularExp());
//                            CurrentPart.Set(pObject->GetMaterial().GetSpecularColor());
//                            CurrentPart.Scale(phongTerm);
//                            //at this time, not considering that a light could be of a color other than white
//                            theColor.Add(&CurrentPart);
//                        }
//                        else
//                        {
//                            phongTerm = 0.0f;
//                            //there is no Specular part, so add nothing!
//                        }
//                    }
//                }
//            }
//        }
//        //*************************************************************************************************

//        //Shoot a REFLECTION Ray
//        //*************************************************************************************************
//        if (pRay->dwGeneration < MAX_NUM_RAY_GENERATIONS)
//        {
//            RAY reflectionRay;
//            reflectionRay.dwGeneration	= pRay->dwGeneration + 1;
//            reflectionRay.vDirection	= vReflectDirection;
//            reflectionRay.vStart		= IntersectPoint;

//            CurrentPart = FindColor(&reflectionRay);
//            CurrentPart.Scale(pObject->GetMaterial().GetSpecularCoef());
//            theColor.Add(&CurrentPart);
//        }

//        //*************************************************************************************************

//        /*
//		//delete all the intersections
//		while (intersections.size() > 0)
//		{
//			delete intersections[0];
//			intersections.pop_front();
//		}
//		*/

//        return theColor;
//    }
//}

void Scene::Init()
{

}

void Scene::Print()
{
    cout << "Scene 0x" << hex << (unsigned int)this << dec << endl;
    m_Eye.Print();
    cout << endl;

    for (unsigned int i = 0; i < m_Objects.size(); i++)
    {
        m_Objects[i]->Print();
        cout << endl;
    }
    for (unsigned int i = 0; i < m_Lights.size(); i++)
    {
        m_Lights[i]->Print();
        cout << endl;
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
}
