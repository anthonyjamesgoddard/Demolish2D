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
   
   _pleniminaryCollisionData.clear();

   //
   // ON THIS DATA WE APPLY THE SEPARATING AXES
   //
    
   for(auto & pair: pairwiseObjectCollisionIndexData)
   {
       auto A = _objects[pair.first].getWorldConvexHullVertices();
       auto B = _objects[pair.second].getWorldConvexHullVertices();
       auto SATAxes = demolish::world::obtainSATAxes(A,B);
       
       bool CHbreach = true;
       
       // now we need to loop over the axes and obtain projections
       for(auto&axis:SATAxes)
       {

            // project the shape onto the axis
           auto projectionA = demolish::world::projectShapeOntoAxis(A,axis);
           auto projectionB = demolish::world::projectShapeOntoAxis(B,axis);
           if(!demolish::world::overlap(projectionA,projectionB))
           {
               CHbreach = false;
               break;
           }
       }
       if(CHbreach == true)
       {
            _pleniminaryCollisionData.push_back(pair);
       }
   }
    
   // At this stage we now have to apply contact detection to all edges 
   
   //
   //   implement matrix class (basic one) in C++
   //       - how are we going to carry out that solve?
   //
   //   we loop through all the edges and calculate the minimum distance
   //   if it less that some tolerance we say that we have colllided

    
   for(auto & pair: pairwiseObjectCollisionIndexData)
   {
       auto A = _objects[pair.first].getWorldVertices();
       auto B = _objects[pair.second].getWorldVertices();
       // for each line segment in A and each line segment in B
       // we calculate the minimum distance between line segments
       for(int i=0;i< A.size();i++)
       {
           auto pi1  = A[i];
           auto pi2  = A[i+1 == A.size() ? 0 : i+1];
           for(int j=0;j< B.size();j++)
           {
                auto pj1  = B[j];
                auto pj2  = B[j+1 == B.size() ? 0 : j+1];
                auto minparams = minimumDistanceBetweenLineSegments(pi1,pi2,pj1,pj2,100,0.001);        
                auto minimumDistanceVertices = verticesOnLineSegments(pi1,pi2,pj1,pj2,minparams);
                float distance = calculateDistanceBetweenVertices(minimumDistanceVertices);
                if(distance<0.01)
                {
                    _collisonPoints.push_back(std::get<0>(minimumDistanceVertices));
                }

           }
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
