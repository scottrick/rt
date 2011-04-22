#ifndef _UNKNOWN_H_
#define _UNKNOWN_H_

class Unknown
{
public:
    Unknown()           {};
    ~Unknown()          {};

    virtual void        Print()                 = 0;

    virtual void        Refresh(int DeltaTime)  = 0;

private:

};

#endif
