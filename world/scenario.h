#pragma once

#include "demolish/world/object.h"

namespace demolish {
namespace world {
class Scenario {
private:
    float _timestep;
    int _numberOfIterations;
    std::vector<Object> _objects;
    std::vector<std::pair<int, int>> _breachedBoundingSpheres;
    std::vector<std::pair<std::pair<int, int>, std::array<float, 4>>>
        _breachedConvexHulls;
    std::vector<Vertex> _breachedCHPoints;
    std::vector<Vertex> _collisonPoints;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>
        _breachedSectors;
    std::vector<std::pair<Vertex, Vertex>> _edgesUnderConsideration;
    // add vec of manifolds
public:
    Scenario(float timestep, int numberOfIterations)
        : _timestep(timestep), _numberOfIterations(numberOfIterations) {}

    void step();

    void addObjectToScenario(Polygon& geometry, std::array<float, 2> position);

    void addObjectToScenario(Object& object);

    void render();

    bool hasCollision() { return _collisonPoints.size() > 0; }

    bool hasCHCollision() { return _breachedCHPoints.size() > 0; }
    bool breachedSpheres() { return _breachedBoundingSpheres.size() > 0; }

    bool breachedHulls() { return _breachedConvexHulls.size() > 0; }

    std::vector<Vertex> obtainCollisionPoints() { return _collisonPoints; }
    std::vector<Vertex> obtainCHCollisionPoints() { return _breachedCHPoints; }
    std::vector<std::pair<Vertex, Vertex>> obtainEdgesUnderConsideration() {
        return _edgesUnderConsideration;
    }
    void manuallyMoveObject(int ObjectIndex, float x, float y) {
        _objects[ObjectIndex].manuallyMoveObject(x, y);
    }
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>
    obtainBreachedSectors() {
        return _breachedSectors;
    }
};
}  // namespace world
}  // namespace demolish
