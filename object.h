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
    float                           _boundingRadius;
    std::vector<Sector>             _sectors;

    // physics parametrs
    std::array<float,2>             _location;
    std::array<float,2>             _velocity;
    float                           _orientation;
    float                           _angularVelocity;

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
    void                            calculateBoundingRadius();
    void                            draw();

    std::array<float,2>             getLocation();
    float                           getBoundingRadius();
    std::vector<Vertex>             getConvexHullVertices();
    std::vector<Vertex>             getVertices();

    //these operators will return the translated vertices.
    // these are the methods that we will need for collision detecton
    std::vector<Vertex>             getWorldVertices();
    std::vector<Vertex>             getWorldConvexHullVertices();

    // operators
    Object&                         operator=(const Object &o);

    // this is most likely going to be a temp function 
    // that allows us to move the object manually.
    void                            manuallyMoveObject(float x,float y);

};
#endif
