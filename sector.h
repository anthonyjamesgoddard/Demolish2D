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
    std::vector<std::shared_ptr<Vertex>>                    _radiallyOrderedLoD;
    int                                                     _detailLevelIndex;
    std::vector<std::vector<std::shared_ptr<Vertex>>>       _LoD;
public:
    Sector();
    Sector(float theta1,float theta2);
    int                                                     generateNextLoD();
    void                                                    displayContents();
    void                                                    prepareSector(); // called after filling
};

#endif
