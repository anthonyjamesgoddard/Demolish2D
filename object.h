#ifndef _OBJECT
#define _OBJECT

#include"polygon.h"
#include"sector.h"

namespace demolish{
    namespace world{
            class Object;
    }
}

using demolish::geometry::Polygon;

/**
 * 
 * _location is used to denote the position of
 * the object in space.
 *
 */


class demolish::world::Object
{
private:
    Polygon                         _geometry;
    Polygon                         _convexHull;
    std::array<float,2>             _location;
    std::array<float,2>             _centroid;
    float                           _boundingRadius;
    std::vector<Sector>             _sectors;

    void                            fillSectors();
    void                            generateLoDs();
public:

    Object( Polygon                          &geometry,
            std::array<float,2>              &location);

    void                            displayProperties();
};
#endif
