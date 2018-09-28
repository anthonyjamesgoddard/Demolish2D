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
    std::vector<Vertex> _vertices;
public:
    Polygon(){};
    Polygon(std::vector<Vertex> &uniqueVertices);
    Polygon convexHull();
    
    Polygon& operator=(const Polygon& p);
   
    std::vector<Vertex>& getVertices();
    void sortWRTTheta();
    void displayProperties();
    void calculatePolarWRTLocation(std::array<float,2> loc);
    ~Polygon();
};

#endif
