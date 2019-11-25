#include "demolish/world/collision_pair.h"
#include <cmath>
using demolish::utils::Matrix2x2;
using demolish::geometry::Vertex;
using demolish::world::Object;

std::vector<Vertex> demolish::world::obtainSATAxes(
    std::vector<Vertex>& convexHullVerticesOfObjectA,
    std::vector<Vertex>& convexHullVerticesOfObjectB) {
    std::vector<Vertex> vectorOfProjectionAxes;
    // now we form the projection axes...
    for (int i = 0; i < convexHullVerticesOfObjectA.size(); i++) {
        Vertex p1 = convexHullVerticesOfObjectA[i];
        Vertex p2 = convexHullVerticesOfObjectA
            [i + 1 == convexHullVerticesOfObjectA.size() ? 0 : i + 1];
        Vertex edge = p2 - p1;
        auto perpToEdge = edge.perpendicular();
        // perpToEdge.normalise();
        vectorOfProjectionAxes.push_back(perpToEdge);
    }
    for (int i = 0; i < convexHullVerticesOfObjectB.size(); i++) {
        Vertex p1 = convexHullVerticesOfObjectB[i];
        Vertex p2 = convexHullVerticesOfObjectB
            [i + 1 == convexHullVerticesOfObjectB.size() ? 0 : i + 1];
        Vertex edge = p2 - p1;
        auto perpToEdge = edge.perpendicular();
        // AS WE ONLY NEED TO KNOW WHETHER OR NOT A COLLISION HAS OCCURRED
        // WE CAN DO AWAY WITH THE NORMALISATION
        // perpToEdge.normalise();
        vectorOfProjectionAxes.push_back(perpToEdge);
    }
    return vectorOfProjectionAxes;
}

std::pair<float, float> demolish::world::projectShapeOntoAxis(
    std::vector<Vertex>& polygonVertices, Vertex& axis) {
    // we cycle through the
    float min = axis * polygonVertices[0];
    float max = min;
    for (int i = 1; i < polygonVertices.size(); i++) {
        float projection = axis * polygonVertices[i];
        if (projection < min) {
            min = projection;
        }
        if (projection > max) {
            max = projection;
        }
    }
    auto minMax = std::make_pair(min, max);
    return minMax;
}

// returns true when we dont have an overlap
bool demolish::world::overlap(std::pair<float, float>& A,
                              std::pair<float, float>& B) {
    return ((A.first <= B.second) && (B.first <= A.second));
}

Vertex matrixVectorMultiplication2x4(std::array<float, 8> mat,
                                     std::array<float, 4> vec) {
    float X, Y;
    X = std::get<0>(mat) * std::get<0>(vec) +
        std::get<1>(mat) * std::get<1>(vec) +
        std::get<2>(mat) * std::get<2>(vec) +
        std::get<3>(mat) * std::get<3>(vec);

    Y = std::get<4>(mat) * std::get<0>(vec) +
        std::get<5>(mat) * std::get<1>(vec) +
        std::get<6>(mat) * std::get<2>(vec) +
        std::get<7>(mat) * std::get<3>(vec);
    return Vertex(X, Y);
}

Matrix2x2 grammianOf(std::array<float, 8> mat) {
    float a11, across, a22;
    a11 = std::get<0>(mat) * std::get<0>(mat) +
          std::get<1>(mat) * std::get<1>(mat) +
          std::get<2>(mat) * std::get<2>(mat) +
          std::get<3>(mat) * std::get<3>(mat);

    across = std::get<4>(mat) * std::get<0>(mat) +
             std::get<5>(mat) * std::get<1>(mat) +
             std::get<6>(mat) * std::get<2>(mat) +
             std::get<7>(mat) * std::get<3>(mat);

    a22 = std::get<4>(mat) * std::get<4>(mat) +
          std::get<5>(mat) * std::get<5>(mat) +
          std::get<6>(mat) * std::get<6>(mat) +
          std::get<7>(mat) * std::get<7>(mat);
    return Matrix2x2(a11, across, across, a22);
}

std::pair<float, float> demolish::world::minimumDistanceBetweenLineSegments(
    Vertex& A, Vertex& B, Vertex& C, Vertex& D, float r, float tol) {
    Vertex AB = B - A;
    Vertex CD = D - C;
    Vertex CA = A - C;
    Matrix2x2 I(1, 0, 0, 1);
    Matrix2x2 hf(AB * AB * 2, AB * CD * -2, AB * CD * -2, CD * CD * 2);
    Vertex x(0.333, 0.333);
    for (int i = 0; i < 10; i++) {
        Vertex gf(
            CD * AB * -2 * x.getY() + AB * AB * 2 * x.getX() + CA * AB * 2,
            CD * AB * -2 * x.getX() + CD * CD * 2 * x.getY() - CA * CD * 2);
        // constraints
        std::array<float, 4> h = {-x.getX(), -x.getY(), x.getX() - 1,
                                  x.getY() - 1};

        std::array<float, 8> dh = {-1, 0, 1, 0, 0, -1, 0, 1};

        // obtain mask
        std::array<float, 4> mask;
        std::get<0>(mask) = (std::get<0>(h) < 0) ? 0 : 1;
        std::get<1>(mask) = (std::get<1>(h) < 0) ? 0 : 1;
        std::get<2>(mask) = (std::get<2>(h) < 0) ? 0 : 1;
        std::get<3>(mask) = (std::get<3>(h) < 0) ? 0 : 1;

        std::array<float, 4> htemp;
        std::get<0>(htemp) = (std::get<0>(h) < 0) ? 0 : std::get<0>(h);
        std::get<1>(htemp) = (std::get<1>(h) < 0) ? 0 : std::get<0>(h);
        std::get<2>(htemp) = (std::get<2>(h) < 0) ? 0 : std::get<0>(h);
        std::get<3>(htemp) = (std::get<3>(h) < 0) ? 0 : std::get<0>(h);

        std::array<float, 8> dmax = {std::get<0>(mask) * std::get<0>(dh),
                                     std::get<1>(mask) * std::get<1>(dh),
                                     std::get<2>(mask) * std::get<2>(dh),
                                     std::get<3>(mask) * std::get<3>(dh),
                                     std::get<0>(mask) * std::get<4>(dh),
                                     std::get<1>(mask) * std::get<5>(dh),
                                     std::get<2>(mask) * std::get<6>(dh),
                                     std::get<3>(mask) * std::get<7>(dh)};

        auto grad = gf + matrixVectorMultiplication2x4(dmax, htemp) * r;

        auto hes = hf + grammianOf(dmax) * r + I * (1.0 / (r * r));

        auto dx = hes.solve(grad);

        auto DX = AB * dx.getX();
        auto DY = CD * dx.getY();
        float error =
            std::sqrt(DX * DX + DY * DY);  // we can do awawy with this
        x = x - dx;
        if (error < tol) {
            break;
        }
    }
    return std::make_pair(x.getX(), x.getY());
}

std::pair<Vertex, Vertex> demolish::world::verticesOnLineSegments(
    Vertex& a, Vertex& b, Vertex& c, Vertex& d,
    std::pair<float, float> minparams) {
    float X1 = a.getX() + std::get<0>(minparams) * (b.getX() - a.getX());
    float Y1 = a.getY() + std::get<0>(minparams) * (b.getY() - a.getY());
    float X2 = c.getX() + std::get<1>(minparams) * (d.getX() - c.getX());
    float Y2 = c.getY() + std::get<1>(minparams) * (d.getY() - c.getY());

    auto returnpair = std::make_pair(Vertex(X1, Y1), Vertex(X2, Y2));
    return returnpair;
}

float demolish::world::calculateDistanceBetweenVertices(
    std::pair<Vertex, Vertex> vertexpair) {
    auto v1 = std::get<0>(vertexpair);
    auto v2 = std::get<1>(vertexpair);
    return std::sqrt((v1.getX() - v2.getX()) * (v1.getX() - v2.getX()) +
                     (v1.getY() - v2.getY()) * (v1.getY() - v2.getY()));
}
