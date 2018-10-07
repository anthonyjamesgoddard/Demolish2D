#include"scenario.h"

using demolish::world::Scenario;

void Scenario::step()
{
   //
   //   GENERATE NEW COLLISION DATA
   //       
   //       + First determine if bounding spheres collide.
   //       + Use SAT for convex hull (like impulse)
   //       + resort to penalty
   //

   // clear collision information 
   

   //
   //   INTEGRATE FORCES
   //
   //
   

   // ... 
}

void Scenario::addObjectToScenario(Polygon&                geometry,
                            std::array<float,2>               position)
{
    Object o = Object(geometry,position);
    _objects.push_back(o);
}

void Scenario::addObjectToScenario(Object&                object)
{
    _objects.push_back(object);
}

void Scenario::render()
{
    for(auto & o: _objects)
    {   
        o.draw();
    }

}
