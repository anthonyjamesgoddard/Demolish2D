#include"matrix.h"

using demolish::linearalgebra::Matrix2x2;
using demolish::geometry::Vertex;

Matrix2x2::Matrix2x2(float a11,
                     float a12,
                     float a21,
                     float a22)
{
    _a11 = a11;_a12 = a12;
    _a21 = a21;_a22 = a22;
}

Vertex Matrix2x2::operator*(const Vertex&v) const
{
    float X,Y;
    X = _a11*v.getX() + _a12*v.getY();
    Y = _a21*v.getX() + _a22*v.getY();
    return Vertex(X,Y);
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2&m) const
{
    float res11,res12,res21,res22;
    res11 = _a11*m._a11 + _a12*m._a21;
    res21 = _a21*m._a11 + _a22*m._a21; 
    res12 = _a11*m._a12 + _a12*m._a22;
    res22 = _a21*m._a12 + _a22*m._a22;
    return Matrix2x2(res11,res12,res21,res22);
}

Matrix2x2 Matrix2x2::operator*(const float& a) const
{
    float res11,res12,res21,res22;
    res11 = _a11*a;
    res21 = _a21*a; 
    res12 = _a11*a;
    res22 = _a21*a;
    return Matrix2x2(res11,res12,res21,res22);
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2&m) const
{
    float res11,res12,res21,res22;
    res11 = _a11 + m._a11;
    res12 = _a12 + m._a12;
    res21 = _a21 + m._a21;
    res22 = _a22 + m._a22;
    return Matrix2x2(res11,res12,res21,res22);
}

Vertex Matrix2x2::solve(Vertex& RHS)
{
    // calculate the inverse 
    float det = _a11*_a22 - _a12*_a21;
    Matrix2x2 inv(_a22,-1*_a12,-1*_a21,_a11);
    return inv*RHS*(1.0/det);
}
