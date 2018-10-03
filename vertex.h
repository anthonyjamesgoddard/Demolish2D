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
    float _x,_y;                        // cartesian
    float _r,_theta;                    // polar (w.r.t centroid of polygon)
public:
    Vertex(){};
    Vertex(float x,float y);

    // operator overloads
    Vertex& operator=(const Vertex& v);
    bool operator<(const Vertex& v) const;
    Vertex


    
    void fillPolars(std::array<float,2> loc);

    float getTheta()
    {
        return _theta;
    }

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
