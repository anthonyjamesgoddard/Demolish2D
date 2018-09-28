#include<iostream>
#include"polygon.h"
#include"object.h"

using namespace demolish;

int main()
{
    std::vector<Vertex> verts;

    /*
     *  "K"
     *
     *  Tested:
     *      Convex Hull (correct)
     *      Plenim. Sectorisation (correct)
     *
     */

    /*
    verts.push_back(Vertex(1,1));
    verts.push_back(Vertex(0.5,0.9));
    verts.push_back(Vertex(0,0.7));
    verts.push_back(Vertex(-0.5,0.9));
    verts.push_back(Vertex(-1,1));
    verts.push_back(Vertex(-1,-1));
    verts.push_back(Vertex(0,-0.7));
    verts.push_back(Vertex(1,-1));
    verts.push_back(Vertex(0.3,0));
    std::array<float,2> origin = {0,0};
    */
    
    /*
     *  "Fish"
     *
     *  Tested:
     *      Convex Hull (correct)
     *      Plenim. Sectorisation (issue):
     *          the x and y co-ordinates are
     *          both zero for the last vertex
     *          (1.3,0.1)
     *          int the sectorisation.
     *
     */

    
    verts.push_back(Vertex(1,1));
    verts.push_back(Vertex(0.5,0.9));
    verts.push_back(Vertex(0,0.7));
    verts.push_back(Vertex(-0.5,0.9));
    verts.push_back(Vertex(-1,1));
    verts.push_back(Vertex(-1,-1));
    verts.push_back(Vertex(0,-0.7));
    verts.push_back(Vertex(1,-1));
    verts.push_back(Vertex(1.3,0.1));
    std::array<float,2> origin = {0,0};
    
    

    auto poly = geometry::Polygon(verts);
    auto obj  = world::Object(poly,origin);

    obj.displayProperties();
    return 0;
}
