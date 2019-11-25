#pragma once

#include <array>
#include <iostream>
#include <vector>

namespace demolish {
namespace geometry {
class Vertex {
private:
    float _x, _y;                // cartesian
    float _r, _theta;            // polar (w.r.t centroid of polygon)
    int _associatedSectorIndex;  // the secret
public:
    Vertex(){};
    Vertex(float x, float y);

    // operator overloads
    Vertex& operator=(const Vertex& v);
    bool operator<(const Vertex& v) const;
    Vertex operator+(const Vertex& v) const;
    Vertex operator-(const Vertex& v) const;
    Vertex operator*(const float& a) const;
    float operator*(const Vertex& v) const;
    Vertex& operator+=(const Vertex& v);
    Vertex& operator*=(const float& a);
    // member functions
    void fillPolars();
    Vertex perpendicular();
    float norm();
    void normalise();
    float getTheta() { return _theta; }

    float getRadius() { return _r; }
    float getX() const { return _x; }
    float getY() const { return _y; }
    int getAssociatedSectorIndex() { return _associatedSectorIndex; }
    void setX(float x) { _x = x; }
    void setY(float y) { _y = y; }
    void set(float x, float y) {
        _x = x;
        _y = y;
    }
    void setAssociatedSectorIndex(int i) { _associatedSectorIndex = i; }
    void displayProperties() {
        std::cout << _x << " " << _y << " " << _r << " " << _theta << " "
                  << _associatedSectorIndex << std::endl;
    }

    friend float cross(const Vertex& o, const Vertex& a, const Vertex& b) {
        return (a._x - o._x) * (b._y - o._y) - (a._y - o._y) * (b._x - o._x);
    }
};
}  // namespace geometry
}  // namespace demolish
