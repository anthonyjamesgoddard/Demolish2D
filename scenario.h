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
    std::vector<Object>     _objects;
    // add vec of manifolds 
public:
    Scenario(  float        timestep,
               int          numberOfIterations)
    : _timestep(timestep)
    , _numberOfIterations(numberOfIterations){}


    void        step();

    void        addObjectToScenario(
                Polygon&                geometry, 
                std::array<float,2>     position);

    void        addObjectToScenario(
                Object&                 object);

    void        render();

    // temp function for testing purposes
    void manuallyMoveObject(int ObjectIndex, float x, float y)
    {
        _objects[ObjectIndex].manuallyMoveObject(x,y);
    }
};

#endif
