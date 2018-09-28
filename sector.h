#ifndef _SECTOR
#define _SECTOR

#include"vertex.h"

#include<vector>

namespace demolish{
    namespace world{
        class Sector;
    }
}

using demolish::geometry::Vertex;

class demolish::world::Sector
{
public:
    float _theta1,_theta2;
    std::vector<std::vector<Vertex*>> _LoD;
public:
    Sector(){};
    Sector(float theta1,float theta2)
    {
        _theta1 = theta1; _theta2 = theta2;
    }
    void displayContents()
    {
        int LoDSz = _LoD.size();
        for(int i=0;i<LoDSz;i++)
        {
            auto tempVec = _LoD[i];
            int tempSz = tempVec.size();
            for(int j=0;j<tempSz;j++)
            {
                tempVec[j]->displayProperties();
            }
        }
    }
};

#endif
