#include "demolish/world/object.h"
#include <cmath>
#include <iostream>
#include <memory>
#include "demolish/lib/glut.h"
void demolish::world::Object::fillSectors() {
    auto geometryVerts = _geometry.getVertices();
    auto hullVerts = _convexHull.getVertices();
    int hullVertsSz = hullVerts.size();
    int geometryVertsSz = geometryVerts.size();

    for (int i = 0; i < hullVertsSz - 1; i++) {
        Sector tempSec(hullVerts[i].getTheta(), hullVerts[i + 1].getTheta());

        std::shared_ptr<Vertex> chp1(
            new Vertex(hullVerts[i].getX(), hullVerts[i].getY()));
        chp1->fillPolars();
        chp1->setAssociatedSectorIndex(i);
        std::shared_ptr<Vertex> chp2(
            new Vertex(hullVerts[i + 1].getX(), hullVerts[i + 1].getY()));
        chp2->fillPolars();
        chp2->setAssociatedSectorIndex(i);

        std::vector<std::shared_ptr<Vertex>> vecOfVert;
        vecOfVert.push_back(chp1);
        vecOfVert.push_back(chp2);
        tempSec._LoD.push_back(vecOfVert);
        _sectors.push_back(tempSec);
    }
    Sector tempSec(hullVerts[hullVertsSz - 1].getTheta(),
                   hullVerts[0].getTheta());

    std::shared_ptr<Vertex> chp1(new Vertex(hullVerts[hullVertsSz - 1].getX(),
                                            hullVerts[hullVertsSz - 1].getY()));
    chp1->fillPolars();
    std::shared_ptr<Vertex> chp2(
        new Vertex(hullVerts[0].getX(), hullVerts[0].getY()));
    chp2->fillPolars();
    chp1->setAssociatedSectorIndex(hullVertsSz - 1);
    chp2->setAssociatedSectorIndex(hullVertsSz - 1);
    std::vector<std::shared_ptr<Vertex>> vecOfVert;
    vecOfVert.push_back(chp1);
    vecOfVert.push_back(chp2);
    tempSec._LoD.push_back(vecOfVert);
    _sectors.push_back(tempSec);

    std::vector<std::shared_ptr<Vertex>> finestLoD;

    float thetaHi = _sectors[0]._theta2;
    float thetaLow = _sectors[0]._theta1;

    int sectorIndex = 0;
    int vertexIndex = 0;
    bool needtominus = true;
    while (sectorIndex < _sectors.size() - 1) {
        if (geometryVerts[vertexIndex].getTheta() <= thetaHi) {
            needtominus = true;
            if (geometryVerts[vertexIndex].getTheta() < thetaLow) {
                vertexIndex++;
                continue;
            }

            std::shared_ptr<Vertex> vp(
                new Vertex(geometryVerts[vertexIndex].getX(),
                           geometryVerts[vertexIndex].getY()));
            vp->fillPolars();
            vp->setAssociatedSectorIndex(sectorIndex);
            finestLoD.push_back(vp);
            vertexIndex++;
            if (vertexIndex == geometryVertsSz) {
                break;
            }
        } else {
            needtominus = false;
            vertexIndex--;
            auto tempVec = finestLoD;
            _sectors[sectorIndex]._finestLoD = tempVec;
            finestLoD.clear();
            sectorIndex++;
            thetaHi = _sectors[sectorIndex]._theta2;
            thetaLow = _sectors[sectorIndex]._theta1;
        }
    }
    if (needtominus) vertexIndex--;
    auto tempVec = finestLoD;
    _sectors[sectorIndex]._finestLoD = tempVec;
    finestLoD.clear();

    sectorIndex++;

    if (sectorIndex == hullVertsSz) sectorIndex--;
    while (geometryVerts[vertexIndex].getTheta() <= 2 * M_PI) {
        std::shared_ptr<Vertex> vp(
            new Vertex(geometryVerts[vertexIndex].getX(),
                       geometryVerts[vertexIndex].getY()));
        vp->fillPolars();
        vp->setAssociatedSectorIndex(sectorIndex);
        finestLoD.push_back(vp);
        vertexIndex++;
        if (vertexIndex == geometryVertsSz) {
            vertexIndex = 0;
            break;
        }
    }
    while (geometryVerts[vertexIndex].getTheta() <=
           _sectors[sectorIndex]._theta2) {
        std::shared_ptr<Vertex> vp(
            new Vertex(geometryVerts[vertexIndex].getX(),
                       geometryVerts[vertexIndex].getY()));
        vp->fillPolars();
        vp->setAssociatedSectorIndex(sectorIndex);

        finestLoD.push_back(vp);
        vertexIndex++;
        if (vertexIndex == geometryVertsSz) {
            vertexIndex = 0;
            break;
        }
    }
    _sectors[sectorIndex]._finestLoD = finestLoD;
    for (auto &s : _sectors) {
        s.prepareSector();
    }
}

void demolish::world::Object::calculateBoundingRadius() {
    _geometry.sortWRTRadius();
    auto v = _geometry.getVertices();
    _boundingRadius = v[0].getRadius();
}

demolish::world::Object::Object(Polygon &geometry,
                                std::array<float, 2> &location) {
    _geometry = geometry;
    _location = location;
    _geometry.calculateCentroid();
    // calculates centroid
    _geometry.centreGeometry();
    // translates polygon s.t centroid is (0,0)
    _geometry.calculatePolarWRTCentroid();
    // fills in the polar rep. of the vectors
    _convexHull = _geometry.convexHull();
    // obtains the convex hull
    _convexHull.setCentroid(_geometry.getCentroid());
    // set the centroid of the convex hull to
    // the centroid of _geometry
    calculateBoundingRadius();
    _geometry.sortWRTTheta();
    _convexHull.sortWRTTheta();
    fillSectors();
    // fills the sectors with initial data
}

void demolish::world::Object::displayProperties() {
    std::cout << "location: x = " << std::get<0>(_location)
              << " and y = " << std::get<1>(_location) << '\n';
    std::cout << "vertices: " << '\n';
    _geometry.displayProperties();
    std::cout << "hull: " << '\n';
    _convexHull.displayProperties();

    std::cout << "conents of each sector " << '\n' << std::endl;

    int i = 0;
    for (auto &v : _sectors) {
        std::cout << "Sector " << i++ << std::endl;
        v.displayContents();
        std::cout << std::endl;
    }
}

// just making you aware of the note that was given above
// Polygon::calculateCentroid().

void demolish::world::Object::calculateMaterialParameters(float density) {
    Vertex centroid(0, 0);
    float areaComponent, Ix, Iy;
    float inertia = 0;
    float oneOverTwelve = 1.0f / 12.0f;
    float numberOfVertices = _geometry.getNumberOfVertices();
    std::vector<Vertex> vertices = _geometry.getVertices();
    Vertex origin(0, 0);
    float area = 0;
    for (int i = 0; i < numberOfVertices; ++i) {
        //
        // Calculation of the (second moment of) inertia
        //
        //      https://en.wikipedia.org/wiki/Second_moment_of_area#Any_cross_section_defined_as_polygon
        //

        Vertex vi = vertices[i];
        int j = i + 1 < numberOfVertices ? i + 1 : 0;
        Vertex vj = vertices[j];
        areaComponent = cross(origin, vi, vj);
        area += 0.5 * areaComponent;
        Ix = vi.getX() * vi.getX() + vi.getX() * vj.getX() +
             vj.getX() * vj.getX();
        Ix = vi.getY() * vi.getY() + vi.getY() * vj.getY() +
             vj.getY() * vj.getY();
        inertia += oneOverTwelve * areaComponent * (Ix + Iy);
    }
    _mass = density * area;
    _invMass = _mass ? 1.0f / _mass : 0.0f;

    _inertia = inertia * density;
    _invIntertia = _inertia ? 1.0f / _inertia : 0.0f;
}

void demolish::world::Object::draw() {
    // draw the object
    /*
    glColor3f(1,1,1);
    auto verts = _geometry.getVertices();
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<verts.size();i++)
    {
        glVertex2f(verts[i].getX() + std::get<0>(_location),
                   verts[i].getY() + std::get<1>(_location));
    }

    // draw the convex hull
    glEnd();
    */
    /*
    glColor3f(1,0,0);
    verts = _convexHull.getVertices();
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<verts.size();i++)
    {
        glVertex2f(verts[i].getX() + std::get<0>(_location),
                   verts[i].getY() + std::get<1>(_location));
    }
    glEnd();
    */
    // draw the centroid
    // note that the entroid of the object is the
    // centroid of _geometry
    glPointSize(3.0);
    auto c = _geometry.getCentroid();
    glColor3f(0, 1, 1);
    glBegin(GL_POINTS);
    glVertex2f(/*0**/ std::get<0>(c) + std::get<0>(_location),
               /*0**/ std::get<1>(c) + std::get<1>(_location));
    glEnd();

    // draw the bounding radius
    //
    /*
      glColor3f(1,1,0);
      glBegin(GL_LINE_LOOP);
      float theta = 0;
      float inc = M_PI * 2.0f / 50.0f;
      for(int i=0;i<50;i++)
      {

          glVertex2f(std::get<0>(_location) + _boundingRadius*std::cos(theta),
                     std::get<1>(_location) + _boundingRadius*std::sin(theta));
          theta += inc;


      }
      glEnd();
     */

    for (int i = 0; i < _sectors.size(); i++) {
        auto drawvec = _sectors[i].obtainCurrentLevelOfDetailInWorld(_location);
        glColor3f(0, 1, 1);
        glBegin(GL_LINE_STRIP);
        for (int k = 0; k < drawvec.size(); k++) {
            glVertex2f(drawvec[k].getX(), drawvec[k].getY());
        }
        glEnd();
    }
}

std::array<float, 2> demolish::world::Object::getLocation() {
    return _location;
}

float demolish::world::Object::getBoundingRadius() { return _boundingRadius; }

std::vector<Vertex> demolish::world::Object::getConvexHullVertices() {
    return _convexHull.getVertices();
}

std::vector<Vertex> demolish::world::Object::getVertices() {
    return _geometry.getVertices();
}

// the next two functions will need to be updated when we
// finally implement the physics!!!

std::vector<Vertex> demolish::world::Object::getWorldVertices() {
    auto verts = this->getVertices();
    Vertex loc(std::get<0>(_location), std::get<1>(_location));
    for (auto &v : verts) {
        v += loc;
    }
    return verts;
}

std::vector<Vertex> demolish::world::Object::getWorldConvexHullVertices() {
    auto verts = this->getConvexHullVertices();
    Vertex loc(std::get<0>(_location), std::get<1>(_location));
    for (auto &v : verts) {
        v += loc;
    }
    return verts;
}
demolish::world::Object &demolish::world::Object::operator=(
    const demolish::world::Object &o) {
    // considering this is only used to form a collison pair we
    // can "fill this in as we go along"
    return *this;
}

void demolish::world::Object::reset() {
    for (auto &sec : _sectors) {
        sec._detailLevelIndex = 0;
    }
}

void demolish::world::Object::manuallyMoveObject(float x, float y) {
    std::get<0>(_location) += x;
    std::get<1>(_location) += y;
}
