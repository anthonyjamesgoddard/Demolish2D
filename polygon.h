#ifndef _POLYGON
#define _POLYGON

#include"vertex.h"

#include<vector>
#include<array>

namespace demolish{
    namespace geometry{
            class Polygon;
        }
    }

using demolish::geometry::Vertex;

class demolish::geometry::Polygon
{
private:
    std::vector<Vertex>     _vertices;
    std::array<float,2>     _centroid;
    int                     _numberOfVertices;
public:
    Polygon(){};
    Polygon(std::vector<Vertex> &uniqueVertices);
    Polygon                 convexHull();
    
    Polygon& operator=(const Polygon& p);
    
    // getters and setters
    std::array<float,2>&    getCentroid();
    void                    setCentroid(std::array<float,2> c);
    float                   getNumberOfVertices();
    std::vector<Vertex>&    getVertices();

    void                    calculateCentroid();
    void                    centreGeometry();
    void                    sortWRTTheta();
    void                    sortWRTRadius();
    void                    displayProperties();
    void                    calculatePolarWRTCentroid();
    ~Polygon();
};

#endif
