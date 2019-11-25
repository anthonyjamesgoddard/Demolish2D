#pragma once
/**
 * This is going to be replaced with solvants matrix functionality
 * That is why it is in a stupid place. Although this is not a 
 * priority as we only every need 2x2 in this case tbh - 
 * as for as I remember
 */

#include "demolish/geometry/vertex.h"

namespace demolish {
namespace utils {

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
}  // namespace utils
}  // namespace demolish

