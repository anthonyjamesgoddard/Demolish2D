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
    _geometry.calculateCentroid();
    // calculates centroid
    _geometry.centreGeometry();
    // translates polygon s.t centroid is (0,0)
     _geometry.calculatePolarWRTCentroid();      
    // fills in the polar rep. of the vectors
    _convexHull = _geometry.convexHull();   
    // obtains the convex hull
    _convexHull.setCentroid(_geometry.getCentroid());
    // set the centroid of the convex hull to
    // the centroid of _geometry
    _geometry.sortWRTTheta();               
    _convexHull.sortWRTTheta();
    fillSectors();                              
    // fills the sectors with initial data
    generateLoDs();                             
    // fills in the levels of detail data structure.
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

// just making you aware of the note that was given above
// Polygon::calculateCentroid(). 

void demolish::world::Object::calculateMaterialParameters(float density)
{
    Vertex centroid(0,0); 
    float areaComponent,Ix,Iy;
    float inertia = 0;
    float oneOverTwelve = 1.0f/12.0f;
    float numberOfVertices = _geometry.getNumberOfVertices();
    std::vector<Vertex> vertices = _geometry.getVertices(); 
    Vertex origin(0,0);
    float area=0;
    for(int i=0;i<numberOfVertices;++i)
    {
        //
        // Calculation of the (second moment of) inertia
        //
        //      https://en.wikipedia.org/wiki/Second_moment_of_area#Any_cross_section_defined_as_polygon
        //

        Vertex vi       = vertices[i];
        int j = i + 1 < numberOfVertices ? i + 1 : 0;
        Vertex vj       = vertices[j];
        areaComponent   = cross(origin,vi,vj);
        area            += 0.5*areaComponent;
        Ix = vi.getX()*vi.getX() + vi.getX()*vj.getX() +  vj.getX()*vj.getX();
        Ix = vi.getY()*vi.getY() + vi.getY()*vj.getY() +  vj.getY()*vj.getY();
        inertia+=oneOverTwelve*areaComponent*(Ix+Iy);
    }
    _mass = density*area;
    _invMass = _mass ? 1.0f/_mass : 0.0f;

    _inertia = inertia*density;
    _invIntertia = _inertia ? 1.0f / _inertia : 0.0f;

}
