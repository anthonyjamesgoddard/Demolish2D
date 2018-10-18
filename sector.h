#ifndef _SECTOR
#define _SECTOR

#include"vertex.h"

#include<vector>
#include<memory>
namespace demolish{
    namespace world{
        class Sector;
    }
}

using demolish::geometry::Vertex;

class demolish::world::Sector
{
public:
    float                                                   _theta1,_theta2;
    std::vector<std::shared_ptr<Vertex>>                    _finestLoD;
    int                                                     _detailLevelIndex;
    std::vector<std::vector<std::shared_ptr<Vertex>>>       _LoD;
public:
    Sector(){_detailLevelIndex = 0;};
    Sector(float theta1,float theta2)
    {
        _theta1 = theta1; _theta2 = theta2;
    }
    int                                                     generateNextLoD();
    void                                                    displayContents();
};

#endif
