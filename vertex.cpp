#include"vertex.h"

#include<cmath>

using demolish::geometry::Vertex;

Vertex::Vertex(float x,float y)
{
    _x = x; _y = y;
    _r = 0; _theta = 0;
}

Vertex& Vertex::operator=(const Vertex& v)
{
   _x =     v._x;
   _y =     v._y;
   _r =     v._r;
   _theta = v._theta;
   return *this;
}

// lexicographic ordering
bool Vertex::operator<(const Vertex&v) const
{
    return _x < v._x || (_x == v._x && _y < v._y);
}


/**
 * We have not found that we need to update the radial
 * and angular component of the vector as of yet. Although,
 * we do suspect that we will need to soon. 
 */

Vertex Vertex::operator+(const Vertex&v) const
{
    float X = _x + v._x, Y = _y + v._y;
    Vertex v = Vertex(X,Y);
    return v;
}

Vertex& Vertex::operator+=(const Vertex&v) const
{
    _x += v._x;
    _y += v._y;
    return *this;
}

Vertex& Vertex::operator*=(const float&a) const
{
    _x*=a;_y*=a;
    return *this;
}

void Vertex::fillPolars(std::array<float,2> loc)
{
    float X = std::get<0>(loc);
    float Y = std::get<1>(loc);
    //we could do without the sqrt
    _r = sqrt((X - _x)*(X - _x) + (Y - _y)*(Y - _y));
    _theta = atan2(_y - Y,_x - X);
    if(_theta<0)
    {
        _theta += 2*M_PI;
    }
}
