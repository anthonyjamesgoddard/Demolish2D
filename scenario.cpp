#include"scenario.h"

using demolish::world::Scenario;

void Scenario::addObjectToScenario(Polygon&                geometry,
                            std::array<float,2>               position)
{
    Object* o = new Object(geometry,position);
    _objects.push_back(o);
}

std::vector<std::vector<Vertex>*> Scenario::getDrawables()
{
    for(auto & o: _objects)
    {   
        o->displayProperties();
    }

    std::vector<std::vector<Vertex>*> v;
    return v;
}
