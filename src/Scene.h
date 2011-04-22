#ifndef _SCENE_H_
#define _SCENE_H_

#include "Buffer.h"
#include "Eye.h"
#include "Light.h"
#include "Sphere.h"
#include "Unknown.h"

#include <vector>
using namespace std;

class Scene : public Unknown
{
public:
    Scene(const char *pFilename = 0);
    ~Scene();

    void Add(const char *pFilename); //parse the given file and add its stuff to the scene
    void Clear();

    virtual void    Print();
    virtual void    Refresh(int DeltaTime);

private:
    void            Init();

    vector<Object *>    m_Objects;
    vector<Light *>     m_Lights;
    Eye                 m_Eye;
};

#endif
