#include"object.h"

#include<iostream>
#include<cmath>

void demolish::world::Object::fillSectors()
{
    //
    // obtain references to underlying geometry
    //

    auto geometryVerts = _geometry.getVertices();
    auto hullVerts     = _convexHull.getVertices();
    int hullVertsSz    = hullVerts.size();
    int geometryVertsSz= geometryVerts.size();

    for(int i=0;i<hullVertsSz-1;i++)
    {
        _sectors.push_back(Sector(hullVerts[i].getTheta(),
                            hullVerts[i+1].getTheta()));
    }
    _sectors.push_back(Sector(hullVerts[hullVertsSz-1].getTheta(),
                                hullVerts[0].getTheta()));
    //
    // fill sectors
    //

    /**
     * By ordering with respect to the angle the vertex makes 
     * with the horizontal we can reduce the complexity of
     * forming these sectors to linear time.
     */


    
    // ------- all but the last sector is filled here ---------------

    std::vector<Vertex*> finestLoD;

    float thetaHi   = _sectors[0]._theta2;
    float thetaLow  = _sectors[0]._theta1;

    int sectorIndex=0;
    int vertexIndex=0;
   
    while(sectorIndex<_sectors.size()-1)
    {
        if(geometryVerts[vertexIndex].getTheta() <= thetaHi)
        {
            if(geometryVerts[vertexIndex].getTheta() < thetaLow)
            {
                vertexIndex++;
                continue;
            }
            finestLoD.push_back(&geometryVerts[vertexIndex]);
            vertexIndex++;
            if(vertexIndex ==  geometryVertsSz)
            {
                break;
            }
        }
        else
        {
            vertexIndex--;
            auto tempVec = finestLoD;
            _sectors[sectorIndex]._LoD.push_back(tempVec);
            finestLoD.clear();
            sectorIndex++;
            thetaHi  = _sectors[sectorIndex]._theta2;
            thetaLow = _sectors[sectorIndex]._theta1;
        }
    }

    auto tempVec = finestLoD;
    _sectors[sectorIndex]._LoD.push_back(tempVec);
    finestLoD.clear();

    // -------- for the last sector 
    vertexIndex--;sectorIndex++;    
    while(geometryVerts[vertexIndex].getTheta()<2*M_PI)
    {
        finestLoD.push_back(&geometryVerts[vertexIndex]);
        vertexIndex++;
        if(vertexIndex = geometryVertsSz)
        {
            vertexIndex=0;
            break;
        }
    }
    while(geometryVerts[vertexIndex].getTheta()<=
            _sectors[sectorIndex]._theta2)
    {
        finestLoD.push_back(&geometryVerts[vertexIndex]);
        //below prints correct result!!!!!!!
        finestLoD[vertexIndex]->displayProperties();
        vertexIndex++;
    }
    tempVec = finestLoD;
    _sectors[sectorIndex]._LoD.push_back(tempVec);
}


void demolish::world::Object::generateLoDs()
{ 
    for(auto & v : _sectors )
    {
        v.generateLoDs();
    }
}

demolish::world::Object::Object(
        Polygon                          &geometry,
        std::array<float,2>              &location)
{
    _geometry = geometry;
    _location = location;
    _geometry.calculatePolarWRTLocation(_location);
    _convexHull = _geometry.convexHull();
    _geometry.sortWRTTheta();
    _convexHull.sortWRTTheta();
    fillSectors();
    generateLoDs();
}

void demolish::world::Object::displayProperties()
{
    std::cout << "location: x = " << 
        std::get<0>(_location) << " and y = " << std::get<1>(_location) << '\n';
    std::cout << "vertices: " << '\n';
    _geometry.displayProperties();
    std::cout << "hull: " << '\n';
    _convexHull.displayProperties();
   
    std::cout << "conents of each sector " << '\n' << std::endl;
    
    int i=0;
    for(auto & v : _sectors )
    {
        std::cout << "Sector " << i++ << std::endl;
        v.displayContents();
        std::cout << std::endl;
    }
}


