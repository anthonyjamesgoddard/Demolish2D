#include"collisionpair.h"


std::vector<Vertex> demolish::world::obtainSATAxes(Object&a,
                                                   Object&b)
{
    std::vector<Vertex> vectorOfProjectionAxes;
    // we obtain the SAT axes by considering the normals of the edges
    // we have to keep in mind that we only use SAT for the convex hulls
    // only.
    auto verticesObjectA = a.getConvexHullVertices();
    auto verticesObjectB = b.getConvexHullVertices();
    // now we form the projection axes...
    for(int i=0;i<verticesObjectA.size();i++)
    {
        Vertex p1   = verticesObjectA[i];
        Vertex p2   = verticesObjectA[i+1 == verticesObjectA.size() ? 0 : i+1];
        Vertex edge = p2-p1;
        auto perpToEdge = edge.perpendicular();
        perpToEdge.normalise();
        vectorOfProjectionAxes.push_back(perpToEdge);
    }
    for(int i=0;i<verticesObjectB.size();i++)
    {
        Vertex p1   = verticesObjectB[i];
        Vertex p2   = verticesObjectB[i+1 == verticesObjectB.size() ? 0 : i+1];
        Vertex edge = p2-p1;
        auto perpToEdge = edge.perpendicular();
        perpToEdge.normalise();
        vectorOfProjectionAxes.push_back(perpToEdge);
    }
    return vectorOfProjectionAxes;
}


// BUGGY NEEDS TO BE FIXED
std::pair<float,float> demolish::world::projectShapeOntoAxis(Polygon&poly,
                                                             Vertex&axis)
{
    // we cycle through the 
    auto polygonVertices = poly.getVertices();
    float min = axis*polygonVertices[0];
    float max = min;
    for(int i=1;i<polygonVertices.size();i++)
    {
        float projection = axis*polygonVertices[i];
        if(projection<min)
        {
            min = p;
        }
        if(p>max)
        {
            max = p;
        }
    }
    auto minMax = std::make_pair(min,max);
    return minMax; 
}
