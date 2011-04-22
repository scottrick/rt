#ifndef _SCENE_H_
#define _SCENE_H_

#include "Buffer.h"
#include "Eye.h"
#include "Light.h"
#include "Sphere.h"
#include "Unknown.h"

//#include <boost/thread.hpp>
#include <vector>
using namespace std;

class Scene : public Unknown
{
public:
    Scene(unsigned int sizeX = 800, unsigned int sizeY = 600);
    ~Scene();

    void Add(const char *pFilename); //parse the given file and add its stuff to the scene
    void Clear();
    void DecreaseThreadCount();

    Buffer          *GetBuffer()                            { return m_pBuffer; }
    unsigned int    GetNumRaysShot()                        { return m_dwNumRaysShot; }
    RAY             *GetRay(unsigned int index);
    RAY             *GetRay(unsigned int x, unsigned int y);
    unsigned int    GetThreadCount();
    void            IncreaseThreadCount();

    unsigned int			PeekNextRayIndex();
    virtual void			Print();
    virtual void			Refresh(int DeltaTime);
    void					ShootRays();

private:
    COLOR					FindColor(RAY *pRay);
    int						GetNextRayIndex();
    void					Init();
    void					ProcessRays();
    void					UpdateRays();

    unsigned int			m_BufferSizeX;
    unsigned int			m_BufferSizeY;
    Buffer					*m_pBuffer;

    vector<Object *>		m_Objects;
    vector<Light *>			m_Lights;
    Eye						m_Eye;

    RAY						*m_Rays;

    //	boost::mutex			m_RayIndexMutex;
    int						m_dwNextRayIndex;
    unsigned int			m_dwNumRaysShot;

    //	boost::mutex			m_ThreadCountMutex;
    unsigned int			m_dwThreadCount;
};

#endif
