#ifndef _COLLISIONPAIR
#define _COLLISIONPAIR

#include<vector>
#include"vertex.h"
#include"object.h"

using demolish::geometry::Vertex;
using demolish::world::Object;

/**
 * This collection of functions helps us with our collision
 * detection. 
 *
 * After we have obtained collision pair condidates ( from 
 * considering bounding spheres) we then have to decide if 
 * convex hulls of the geometry collide.
 *
 * After we have acheived this we can then. implement
 * a sector based approach.
 *
 * obtainSATAxes just returns the usual SAT axes.
 * projectShapeOntoAxis returns the min and max projections
 * the shape onto the axes
 *
 */
namespace demolish{
    namespace world{
        std::vector<Vertex>     obtainSATAxes(Object&a,
                                              Object&b);
        std::pair<float,float>  projectShapeOntoAxis(Polygon&poly,
                                                     Vertex& axis);
    }
}


#endif
