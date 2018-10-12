#ifndef _MATRIX
#define _MATRIX

#include"vertex.h"

namespace demolish{
    namespace linearalgebra{
        class Matrix2x2;
    }
}

using demolish::geometry::Vertex;

class demolish::linearalgebra::Matrix2x2
{
private:
    float _a11,_a12,_a21,_a22;
public:
    Matrix2x2(float a11,
              float a12,
              float a21,
              float a22);
    Vertex      operator*( const Vertex&   v) const;
    Matrix2x2   operator*( const Matrix2x2&m) const;
    Matrix2x2   operator+( const Matrix2x2&m) const;
};

#endif
