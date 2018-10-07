#include "polygon.h"
#include<algorithm>

using demolish::geometry::Polygon;

void Polygon::setCentroid(std::array<float,2> c)
{
    _centroid = c;
}

std::array<float,2>& Polygon::getCentroid()
{
    return _centroid;
}

float Polygon::getNumberOfVertices()
{
    return _numberOfVertices;
}




// if the material parameters were associated with
// the geometry and not the object itself then we would
// have been able to calculate the centroid and all 
// material parameters in one go. 
//
// The question is, does it makes sence to accociate
// material parameters with a purely geometric entity?
// should we bend the rules in a revision of this software?

void Polygon::calculateCentroid()
{
    Vertex centroid(0,0);
    float areaOfPolygon = 0;
    float oneOverThree = 1.0f/3.0f;
    float areaComponent;
    Vertex origin(0,0);
    for(int i=0;i<_numberOfVertices;++i)
    {
        //
        // Calculation of the centroid
        //
        //      https://en.wikipedia.org/wiki/Centroid
        //

        Vertex vi = _vertices[i];
        int j = i + 1 < _numberOfVertices ? i + 1 : 0;
        Vertex vj = _vertices[j];

        areaComponent = 0.5*cross(origin,vi,vj);
        areaOfPolygon+= areaComponent;
        centroid += (vi+vj)*areaComponent*oneOverThree;
    }
    centroid  *= 1.0f/areaOfPolygon;
    _centroid  = {centroid.getX(),centroid.getY()};
    // we could do away with storing the centroid by
    // "centering the particle at the origin".
    // That is, subtracting the centroid from all
    // vertices in the polygon.
}

void Polygon::centreGeometry()
{
    for(auto&v:_vertices)
    {
       v.set(v.getX()-std::get<0>(_centroid),
             v.getY()-std::get<1>(_centroid)); 
    }
    _centroid = {0.0f,0.0f};
}

Polygon::Polygon(
        std::vector<Vertex> &uniqueVertices)
{
    _vertices = uniqueVertices;
    _numberOfVertices = _vertices.size();
}


Polygon Polygon::convexHull()
{
    int n = _numberOfVertices,k=0;

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
    _numberOfVertices = p._numberOfVertices;
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


bool compRadius(Vertex a, Vertex b)
{
    return a.getRadius() > b.getRadius();
}
//


void Polygon::sortWRTTheta()
{
    std::sort(_vertices.begin(),_vertices.end(),compTheta);
}

void Polygon::sortWRTRadius()
{
    std::sort(_vertices.begin(),_vertices.end(),compRadius);
}
void Polygon::displayProperties()
{
    for(auto & v : _vertices )
    {
        v.displayProperties();
    }
}

void Polygon::calculatePolarWRTCentroid()
{
    for(auto & v : _vertices )
    {
        v.fillPolars();
    }
}

Polygon::~Polygon()
{

}


