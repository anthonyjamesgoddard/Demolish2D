#pragma once

#include<vector>
#include"demolish/geometry/vertex.h"
#include"demolish/world/object.h"
#include"demolish/utils/matrix.h"

/**
 * This collection of functions helps us with our collision
 * detection. 
 *
 * After we have obtained collision pair condidates ( from 
 * considering bounding spheres) we then have to decide if 
 * convex hulls of the geometry collide.
 *
 */
namespace demolish{
    namespace world{
        // TODO :: put this a layer deeper
        // SAT helper functions
        std::vector<Vertex>     obtainSATAxes(std::vector<Vertex>& convexHullVerticesOfObjectA,
                                              std::vector<Vertex>& convexHullVerticesOfObjectB);

        std::pair<float,float>  projectShapeOntoAxis(std::vector<Vertex>& polygonVertices,
                                                     Vertex& axis);

        bool                    overlap(std::pair<float,float>& A,
                                        std::pair<float,float>& B);

        // penalty helper functions
        std::pair<float,float>  minimumDistanceBetweenLineSegments(Vertex& A,
                                                                   Vertex& B,
                                                                   Vertex& C,
                                                                   Vertex& D,
                                                                   float   r,
                                                                   float   tol);

        std::pair<Vertex,Vertex> verticesOnLineSegments(Vertex&a,
                                                    Vertex&b,
                                                    Vertex&c,
                                                    Vertex&d,
                                                    std::pair<float,float> minparams);


        float calculateDistanceBetweenVertices(std::pair<Vertex,Vertex> vertexpair);

    }
}
