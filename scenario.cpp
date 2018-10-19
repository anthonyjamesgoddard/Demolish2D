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
   _breachedSectors.clear();
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
                        
                        // POUND-BACK BREACHED SECTORS              
                        std::pair<int,int>  sectorPair   = std::make_pair(pi1.getAssociatedSectorIndex(),
                                                                          pj1.getAssociatedSectorIndex());
                        _breachedSectors.emplace_back(pair,sectorPair);
                        _breachedConvexHulls.emplace_back(pair,thetaRanges);
                        _breachedCHPoints.push_back(std::get<0>(minimumDistanceVertices));
                    }
               }
           }
       }
   }
  

    for(auto&bsecs:_breachedSectors)
    {
        
        auto locOfA = _objects[bsecs.first.first].getLocation();
        auto locOfB = _objects[bsecs.first.second].getLocation();
        auto Asector = _objects[bsecs.first.first]._sectors[bsecs.second.first].obtainCurrentLevelOfDetailInWorld(locOfA);
        auto Bsector = _objects[bsecs.first.second]._sectors[bsecs.second.second].obtainCurrentLevelOfDetailInWorld(locOfB);
        // Asector and Bsector give us the world vertices of the sector

        // Asector and Bsector are a vector of vertices (shared_ptrs)

        // carry out minimisation between line segments
        //  
        
        for(int i=0;i< Asector.size()-1;i++)
        {
            auto pi1  = Asector[i];
            auto pi2  = Asector[i+1];
            for(int j=0;j< Bsector.size()-1;j++)
            {
                 auto pj1  = Bsector[j];
                 auto pj2  = Bsector[j+1];
     
                 _edgesUnderConsideration.emplace_back(pi1,pi2);
                 _edgesUnderConsideration.emplace_back(pj1,pj2);

                 auto minparams = minimumDistanceBetweenLineSegments(pi1,pi2,pj1,pj2,100,0.001);        
                 auto minimumDistanceVertices = verticesOnLineSegments(pi1,pi2,pj1,pj2,minparams);
                 float distance = calculateDistanceBetweenVertices(minimumDistanceVertices);
                 if(distance<0.01)
                 {
                     auto result1 = _objects[bsecs.first.second]._sectors[bsecs.second.second].generateNextLoD(); 
                     auto result2 = _objects[bsecs.first.first ]._sectors[bsecs.second.first].generateNextLoD(); 
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
