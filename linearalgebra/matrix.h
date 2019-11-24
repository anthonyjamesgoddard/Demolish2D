#pragma once
/**
 * The linear algebra sub directory is going to
 * be replaced by importing solvant
 */

#include "demolish/geometry/vertex.h"

namespace demolish {
namespace linearalgebra {

using Vertex = demolish::geometry::Vertex;

class Matrix2x2 {
private:
    float _a11, _a12, _a21, _a22;

public:
    Matrix2x2(float a11, float a12, float a21, float a22);
    Vertex operator*(const Vertex& v) const;
    Matrix2x2 operator*(const Matrix2x2& m) const;
    Matrix2x2 operator*(const float& a) const;
    Matrix2x2 operator+(const Matrix2x2& m) const;
    Vertex solve(Vertex& RHS);
    void print() {
        std::cout << _a11 << " " << _a12 << std::endl;
        std::cout << _a21 << " " << _a22 << std::endl;

        std::cout << std::endl;
    }
};
}  // namespace linearalgebra
}  // namespace demolish

