#ifndef _VERTEX
#define _VERTEX

#include<vector>
#include<array>
#include<iostream>

namespace demolish{
    namespace geometry{
        class Vertex;
    }
}

class demolish::geometry::Vertex
{
private:
    // replace with std::array<float,4> ?!
    float _x,_y;                        // cartesian
    float _r,_theta;                    // polar (w.r.t centroid of polygon)
public:
    Vertex(){};
    Vertex(float x,float y);

    // operator overloads
    Vertex&     operator= (const Vertex&v);
    bool        operator< (const Vertex&v) const;
    Vertex      operator+ (const Vertex&v) const; 
    Vertex      operator* (const float& a) const; 
    Vertex&     operator+=(const Vertex&v);
    Vertex&     operator*=(const float& a);
    // member functions
    void        fillPolars();

    float getTheta()
    {
        return _theta;
    }

    float getRadius()
    {
        return _r;
    }
    float getX(){return _x;}
    float getY(){return _y;}
    void set(float x,float y){_x = x;_y=y;}

    void displayProperties()
    {
        std::cout << _x << " " << _y << " " << _r << " " << _theta << std::endl;
    }

    friend float cross(const Vertex&o,const Vertex&a,const Vertex&b)
    {
        return (a._x - o._x) * (b._y - o._y) - 
            (a._y - o._y) * (b._x - o._x);
    }
};

using demolish::geometry::Vertex;
#endif
