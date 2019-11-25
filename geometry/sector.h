#pragma once

#include "demolish/geometry/vertex.h"
#include <memory>
#include <vector>
namespace demolish {
namespace geometry {
class Sector {
public:
    float _theta1, _theta2;
    std::vector<std::shared_ptr<Vertex>> _finestLoD;
    std::vector<std::shared_ptr<Vertex>> _radiallyOrderedLoD;
    int _detailLevelIndex;
    std::vector<std::vector<std::shared_ptr<Vertex>>> _LoD;

public:
    Sector();
    Sector(float theta1, float theta2);
    int generateNextLoD();
    void displayContents();
    void prepareSector();
    std::vector<Vertex> obtainCurrentLevelOfDetailInWorld(
        std::array<float, 2> location);
};
}  // namespace geometry
}  // namespace demolish
