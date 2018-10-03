#ifndef _SCENARIO
#define _SCENARIO

#include"object.h"

namespace demolish{
    namespace world{
        class Scenario;
    }
}

class demolish::world::Scenario
{
private:
    float                   _timestep;
    int                     _numberOfIterations;
    std::vector<Object*>    _objects;
    // add vec of manifolds 
public:
    Scenario(  float       timestep,
            int         numberOfIterations)
    : _timestep(timestep)
    , _numberOfIterations(numberOfIterations){}

    void    addObjectToScenario(Polygon&                geometry, 
                                std::array<float,2>     position);

};

#endif
