#include"scenario.h"
#include"render.h"
#include"collisionpair.h"
#include<cmath>
using demolish::world::Scenario;

// really this should be called AT LEAST ONE of two vertices out of range. 

bool bothVerticesAreOutOfRange(Vertex& a1,Vertex& a2,
                               std::pair<float,float> range)
{
    if(range.first<range.second)
    {
        if((a1.getTheta() > range.second || a1.getTheta() < range.first)
        || (a2.getTheta() > range.second || a2.getTheta() < range.first))

        {
            return true;
        }
        return false;
    }
    else  
    {
        // this could be simplified. But it works! 
        float a1theta = a1.getTheta();
        float a2theta = a2.getTheta();
        if((a1theta >= range.first && a2theta >= range.first)
        && (a1theta <= 2*M_PI      && a2theta <= 2*M_PI))
        {
            return false;
        }
        if((a1theta <= range.second && a2theta <= range.second)
        && (a1theta >= 0            && a2theta >= 0))
        {
            return false;
        }
        if((a1theta >= range.first  && a1theta <= 2*M_PI)
        && (a2theta <= range.second && a2theta >= 0))
        {
            return false;
        }
        return true;
    }
}


void Scenario::step()
{
    
   _breachedBoundingSpheres.clear();
   _breachedConvexHulls.clear();
   _collisonPoints.clear();
   _breachedCHPoints.clear();   
   _edgesUnderConsideration.clear();
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
           float DBLsquared = (std::get<0>(locationi)-std::get<0>(locationj))*(std::get<0>(locationi)-std::get<0>(locationj))
                        + (std::get<1>(locationi)-std::get<1>(locationj))*(std::get<1>(locationi)-std::get<1>(locationj));
           if(DBLsquared<=(ri+rj)*(ri+rj)+0.5)
           {
               _breachedBoundingSpheres.emplace_back(i,j);
           }

       }
   }

   for(auto & pair: _breachedBoundingSpheres)
   {
       auto A = _objects[pair.first].getWorldConvexHullVertices();
       auto B = _objects[pair.second].getWorldConvexHullVertices();
       auto SATAxes = demolish::world::obtainSATAxes(A,B);
       
       bool CHbreach = true;
       
       for(auto&axis:SATAxes)
       {

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
            //
            // BEGIN SINGLE PENALTY RUN
            //

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
                        std::array<float,4> thetaRanges = {pi1.getTheta(),
                                                           pi2.getTheta(),
                                                           pj1.getTheta(),
                                                           pj2.getTheta()};
                         
                        _breachedConvexHulls.emplace_back(pair,thetaRanges);
                        _breachedCHPoints.push_back(std::get<0>(minimumDistanceVertices));
                    }
               }
           }
       }
   }
  

    // --------------------------------------------------------------------------------
   // at this point we should remove doubles that were obtained in the above procedcure
    //--------------------------------------------------------------------------------

   for(auto & pairOfPairs: _breachedConvexHulls)
   {
       auto pair = pairOfPairs.first;
       auto arrayOfRanges = pairOfPairs.second; // the first two correspong to A nad the last two to B
       auto A = _objects[pair.first].getWorldVertices();
       auto B = _objects[pair.second].getWorldVertices();
       // for each line segment in A and each line segment in B
       // we calculate the minimum distance between line segments
       for(int i=0;i< A.size();i++)
       {
           std::pair<float,float> thetaRangeA = std::make_pair(std::get<0>(arrayOfRanges),std::get<1>(arrayOfRanges));
           auto pi1  = A[i];
           auto pi2  = A[i+1 == A.size() ? 0 : i+1];
           if(bothVerticesAreOutOfRange(pi1,pi2,thetaRangeA)) continue;
           for(int j=0;j< B.size();j++)
           {
                std::pair<float,float> thetaRangeB = std::make_pair(std::get<2>(arrayOfRanges),std::get<3>(arrayOfRanges));
                auto pj1  = B[j];
                auto pj2  = B[j+1 == B.size() ? 0 : j+1];
                if(bothVerticesAreOutOfRange(pj1,pj2,thetaRangeB)) continue;
    
                _edgesUnderConsideration.emplace_back(pi1,pi2);
                _edgesUnderConsideration.emplace_back(pj1,pj2);

                auto minparams = minimumDistanceBetweenLineSegments(pi1,pi2,pj1,pj2,100,0.001);        
                auto minimumDistanceVertices = verticesOnLineSegments(pi1,pi2,pj1,pj2,minparams);
                float distance = calculateDistanceBetweenVertices(minimumDistanceVertices);
                if(distance<0.01)
                {
                    _collisonPoints.push_back(std::get<0>(minimumDistanceVertices));
                    _collisonPoints.push_back(std::get<1>(minimumDistanceVertices));
                }

           }
       }
   }
   

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
