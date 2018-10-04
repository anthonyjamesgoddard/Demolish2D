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
    float                           _boundingRadius;
    std::vector<Sector>             _sectors;
    // material params
    float                           _density;
    float                           _mass;
    float                           _invMass;
    float                           _inertia;
    float                           _invIntertia;
public:

    Object( Polygon                 &geometry,
            std::array<float,2>     &location);

    void                            displayProperties();
    void                            fillSectors();
    void                            generateLoDs();
    void                            calculateMaterialParameters(float density);
};
#endif
