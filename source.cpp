#include<iostream>
#include"scenario.h"

using namespace demolish;

world::Scenario scenario(0.1,10);

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


    std::array<float,2> locObj1 = {3,0};
    std::array<float,2> locObj2 = {0,0};
     
    auto poly = geometry::Polygon(verts);
    
    scenario.addObjectToScenario(poly,locObj1);
    scenario.addObjectToScenario(poly,locObj2);

    return 0;
}
