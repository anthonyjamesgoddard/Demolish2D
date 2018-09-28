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

/*
 * _location is some point *inside* the object
 *  this, or even the barycent might not be good enough
 *  for our purposes.
 */

class demolish::world::Object
{
private:
    Polygon                         _geometry;
    Polygon                         _convexHull;
    std::array<float,2>             _location;
    float                           _boundingRadius;
    std::vector<Sector>             _sectors;

    void                            fillSectors();
public:

    Object( Polygon                          &geometry,
            std::array<float,2>              &location);

    void                            displayProperties();
};
#endif
