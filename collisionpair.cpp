#include"collisionpair.h"

std::vector<Vertex>  demolish::world::obtainSATAxes(std::vector<Vertex>& convexHullVerticesOfObjectA,
                                   std::vector<Vertex>& convexHullVerticesOfObjectB)
{
    std::vector<Vertex> vectorOfProjectionAxes;
    // now we form the projection axes...
    for(int i=0;i<convexHullVerticesOfObjectA.size();i++)
    {
        Vertex p1   = convexHullVerticesOfObjectA[i];
        Vertex p2   = convexHullVerticesOfObjectA[i+1 == convexHullVerticesOfObjectA.size() ? 0 : i+1];
        Vertex edge = p2-p1;
        auto perpToEdge = edge.perpendicular();
        //perpToEdge.normalise();
        vectorOfProjectionAxes.push_back(perpToEdge);
    }
    for(int i=0;i<convexHullVerticesOfObjectB.size();i++)
    {
        Vertex p1   = convexHullVerticesOfObjectB[i];
        Vertex p2   = convexHullVerticesOfObjectB[i+1 == convexHullVerticesOfObjectB.size() ? 0 : i+1];
        Vertex edge = p2-p1;
        auto perpToEdge = edge.perpendicular();
        // AS WE ONLY NEED TO KNOW WHETHER OR NOT A COLLISION HAS OCCURRED
        // WE CAN DO AWAY WITH THE NORMALISATION
        //perpToEdge.normalise();
        vectorOfProjectionAxes.push_back(perpToEdge);
    }
    return vectorOfProjectionAxes;
}


std::pair<float,float> demolish::world::projectShapeOntoAxis(std::vector<Vertex>& polygonVertices,
                                                             Vertex&axis)
{
    // we cycle through the 
    float min = axis*polygonVertices[0];
    float max = min;
    for(int i=1;i<polygonVertices.size();i++)
    {
        float projection = axis*polygonVertices[i];
        if(projection<min)
        {
            min = projection;
        }
        if(projection>max)
        {
            max = projection;
        }
    }
    auto minMax = std::make_pair(min,max);
    return minMax; 
}


// returns true when we dont have an overlap
bool demolish::world::overlap(std::pair<float,float> &A,
                              std::pair<float,float> &B)
{
    return ((A.first <= B.second) && (B.first<=A.second));
}

