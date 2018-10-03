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
     *      !! there is an issue with the values 
     *      of the cartesian coords in the sectors
     *  
     *  Temporary Patch:
     *      If we need cartesian coords then
     *      just calculate them from polar 
     *      coordinates
     */

    
    verts.push_back(Vertex(1,1));
    verts.push_back(Vertex(0.5,0.9));
    verts.push_back(Vertex(0,0.7));
    verts.push_back(Vertex(-0.5,0.9));
    verts.push_back(Vertex(-1,1));
    verts.push_back(Vertex(-0.5,0));
    verts.push_back(Vertex(-1,-1));
    verts.push_back(Vertex(0,-0.7));
    verts.push_back(Vertex(1,-1));
    verts.push_back(Vertex(1.3,0.05));
    std::array<float,2> origin = {0,0};
    
    

    auto poly = geometry::Polygon(verts);
    auto obj  = world::Object(poly,origin);

    obj.displayProperties();


    return 0;
}
