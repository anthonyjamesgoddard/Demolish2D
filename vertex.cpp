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

bool Vertex::operator<(const Vertex&v) const
{
    return _x < v._x || (_x == v._x && _y < v._y);
}

void Vertex::fillPolars(std::array<float,2> loc)
{
    float X = std::get<0>(loc);
    float Y = std::get<1>(loc);
    _r = sqrt((X - _x)*(X - _x) + (Y - _y)*(Y - _y));
    _theta = atan2(_y - Y,_x - X);
    if(_theta<0)
    {
        _theta += 2*M_PI;
    }
}
