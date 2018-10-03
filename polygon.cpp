#include "polygon.h"
#include<algorithm>

using demolish::geometry::Polygon;

void Polygon::calculateCentroid()
{
    Vertex centroid(0,0);
    float areaOfPolygon = 0;
    float oneOverThree = 1.0f/3.0f;

    for(int i=0;i<_numberOfVertices;++i)
    {
        Vertex vi = _vertices[i];
        int j = i + 1 < _numberOfVertices ? i + 1 : 0;
        Vertex vj = _vertices[j];
        float areaComponent = cross(vi,vj);
        area+=0.5*areaComponent;

        // this is not finished!!!!!!
    }
}

Polygon::Polygon(
        std::vector<Vertex> &uniqueVertices)
{
    _vertices = uniqueVertices;
    _numberOfVertices = uniqueVertices.size();
}


Polygon Polygon::convexHull()
{
    int n = _vertices.size(),k=0;

    if(n<4)return *this;
    std::vector<Vertex> hull(2*n);

    sort(_vertices.begin(),_vertices.end());

    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], _vertices[i]) <= 0) k--;
        hull[k++] = _vertices[i];
    }

    for (int i = n-1, t = k+1; i > 0; --i) {
        while (k >= t && cross(hull[k-2], hull[k-1], _vertices[i-1]) <= 0) k--;
        hull[k++] = _vertices[i-1];
    }

    hull.resize(k-1);
    return Polygon(hull);
}

Polygon& Polygon::operator=(const Polygon& p)
{
    _vertices = p._vertices;
    return *this;
}


std::vector<Vertex>& Polygon::getVertices()
{
    return _vertices;
}

//
// Sorting by theta
//
bool compTheta(Vertex a, Vertex b)
{
    return a.getTheta() < b.getTheta();
}


//


void Polygon::sortWRTTheta()
{
    std::sort(_vertices.begin(),_vertices.end(),compTheta);
}

void Polygon::displayProperties()
{
    for(auto & v : _vertices )
    {
        v.displayProperties();
    }
}

void Polygon::calculatePolarWRTLocation(std::array<float,2> loc)
{
    for(auto & v : _vertices )
    {
        v.fillPolars(loc);
    }
}

Polygon::~Polygon()
{

}


