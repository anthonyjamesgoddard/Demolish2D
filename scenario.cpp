#include"scenario.h"
#include"render.h"
#include"collisionpair.h"

using demolish::world::Scenario;

void Scenario::step()
{

   //   DELETE OLD COLLISION DATA
   //       + how do we store our collison data?
   //           We generate pairs of object index data
   //           which narrow down the collision.
   //       + especially since out data is multileveled?!

   //
   //   GENERATE NEW COLLISION DATA
   //       
   //       + First determine if bounding spheres collide.
   //       + Use SAT for convex hull (like impulse)
   //       + resort to penalty
   //

  
   // 
   //       FIRST DETERMINE IF BOUNDING SPHERES COLLIDE
   //

   std::vector<std::pair<int,int>> pairwiseObjectCollisionIndexData;

   
   float ri,rj;
   std::array<float,2> locationi, locationj;
   int numberOfObjects = _objects.size();
   for(int i=0;i<numberOfObjects;i++)
   {
       ri        =  _objects[i].getBoundingRadius();
       locationi =  _objects[i].getLocation();
       for(int j=i+1;j<numberOfObjects;j++)
       {
           rj        =  _objects[j].getBoundingRadius();
           locationj =  _objects[j].getLocation();
           // If the distance between the centres is less
           // than the sum of the radi we have a POTENTIAL
           // collisioon.
           float DBLsquared = (std::get<0>(locationi)-std::get<0>(locationj))*(std::get<0>(locationi)-std::get<0>(locationj))
                        + (std::get<1>(locationi)-std::get<1>(locationj))*(std::get<1>(locationi)-std::get<1>(locationj));
           // note that we are giving our bounding spheres a little bit of slacjk
           if(DBLsquared<=(ri+rj)*(ri+rj)+0.5)
           {
               pairwiseObjectCollisionIndexData.emplace_back(i,j);
           }

       }
   }
    
   _pleniminaryCollisionData = pairwiseObjectCollisionIndexData;
   //
   // ON THIS DATA WE APPLY THE SEPARATING AXES
   //

   for(auto & pair: pairwiseObjectCollisionIndexData)
   {
       auto A = _objects[pair.first].getConvexHullVertices();
       auto B = _objects[pair.second].getConvexHullVertices();
       auto SATAxes = demolish::world::obtainSATAxes(A,B);

       std::cout << "there are " << SATAxes.size() << " axes to check" << std::endl;
       // now we need to loop over the axes and obtain projections
       for(auto&axis:SATAxes)
       {

            // project the shape onto the axis
           auto projectionA = demolish::world::projectShapeOntoAxis(A,axis);
           auto projectionB = demolish::world::projectShapeOntoAxis(B,axis);
           //std::cout << "Projection A : " << std::endl;
           //std::cout << projectionA.first << " " << projectionA.second << std::endl;
           //std::cout << "Projection B : " << std::endl;
           //std::cout << projectionB.first << " " << projectionB.second << std::endl;
           if(demolish::world::overlap(projectionA,projectionB))
               std::cout << "we have a rpojection" << std::endl;
       }
   }

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
