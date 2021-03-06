#include <stdlib.h>
#include <iostream>

#include "demolish/lib/glut.h"
#include "demolish/utils/matrix.h"
#include "demolish/utils/render_string.h"
#include "demolish/utils/timer.h"
#include "demolish/world/scenario.h"

using namespace demolish;

world::Scenario scenario(0.1, 10);
utils::Timer timer;
void displayfunc(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scenario.render();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(1, 1);
    glVertex2f(49, 1);
    glEnd();

    auto cpsvec = scenario.obtainCollisionPoints();
    for (auto& cps : cpsvec) {
        glColor3f(1, 0.5, 0.5);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(cps.getX(), cps.getY());
        glEnd();
    }
    cpsvec = scenario.obtainCHCollisionPoints();
    for (auto& cps : cpsvec) {
        glColor3f(0, 1, 0);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(cps.getX(), cps.getY());
        glEnd();
    }
    auto cpsvecofpairs = scenario.obtainEdgesUnderConsideration();
    for (auto& cps : cpsvecofpairs) {
        glColor3f(0, 1, 0);
        glPointSize(5.0);
        glBegin(GL_LINES);
        glVertex2f(cps.first.getX(), cps.first.getY());
        glVertex2f(cps.second.getX(), cps.second.getY());
        glEnd();
    }
    auto cpslalal = scenario.obtainBreachedSectors();
    for (unsigned int i = 0; i < cpslalal.size(); i++) {
        auto cps = cpslalal[i];
        std::string objectA = std::to_string(cps.first.first);
        std::string objectB = std::to_string(cps.first.second);
        std::string sectorA = std::to_string(cps.second.first);
        std::string sectorB = std::to_string(cps.second.second);
    }
    glutSwapBuffers();
}

// we are going to use this function to move one of the
// objects and make it "collide" with the other object.
//

void physics(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scenario.step();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            scenario.manuallyMoveObject(0, 0, -0.1);
            break;
        case 'w':
            scenario.manuallyMoveObject(0, 0, 0.1);
            break;
        case 'd':
            scenario.manuallyMoveObject(0, 0.1, 0);
            break;
        case 'a':
            scenario.manuallyMoveObject(0, -0.1, 0);
            break;
        case 27:
            int hW = glutGetWindow();
            glutDestroyWindow(hW);
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    std::vector<Vertex> verts1;

    /*
     *  "K"
     */

    verts1.push_back(Vertex(1, 1));
    verts1.push_back(Vertex(0.5, 1.9));
    verts1.push_back(Vertex(0, 0.7));
    verts1.push_back(Vertex(-0.5, 0.9));
    verts1.push_back(Vertex(-1, 1));
    verts1.push_back(Vertex(-1.5, 0));
    verts1.push_back(Vertex(-1, -1));
    verts1.push_back(Vertex(0, -0.7));
    verts1.push_back(Vertex(1, -1));
    verts1.push_back(Vertex(1.3, 0.05));

    std::vector<Vertex> verts2;

    /*
     *  "Kv2"
     */

    verts2.push_back(Vertex(1, 1));
    verts2.push_back(Vertex(0, 0.7));
    verts2.push_back(Vertex(-0.5, 1.1));
    verts2.push_back(Vertex(-1, 1));
    verts2.push_back(Vertex(-0.5, 0));
    verts2.push_back(Vertex(-1, -1));
    verts2.push_back(Vertex(0, -0.9));
    verts2.push_back(Vertex(1, -1));
    verts2.push_back(Vertex(0.5, 0.05));
    verts2.push_back(Vertex(0.7, -0.1));

    std::vector<Vertex> verts3;

    /*
     *  "somethinelse"
     */

    verts3.push_back(Vertex(0, 3));
    verts3.push_back(Vertex(-1.1, 1));
    verts3.push_back(Vertex(-0.8, 0.8));
    verts3.push_back(Vertex(-1.8, 0.6));
    verts3.push_back(Vertex(-0.6, 0.4));
    verts3.push_back(Vertex(-1, 0.2));
    verts3.push_back(Vertex(-0.8, 0));
    verts3.push_back(Vertex(1, 0));
    verts3.push_back(Vertex(0.8, 0.1));
    verts3.push_back(Vertex(1, 0.5));
    verts3.push_back(Vertex(0.8, 0.7));
    verts3.push_back(Vertex(1, 0.9));
    verts3.push_back(Vertex(0.8, 1));

    std::array<float, 2> locObj1 = {15, 5};
    std::array<float, 2> locObj2 = {3, 18};
    std::array<float, 2> locObj3 = {8, 30};
    std::array<float, 2> locObj4 = {45, 35};
    std::array<float, 2> locObj5 = {36, 38};
    std::array<float, 2> locObj6 = {8, 13};
    std::array<float, 2> locObj7 = {15, 34};
    std::array<float, 2> locObj8 = {15, 18};
    std::array<float, 2> locObj9 = {16, 35};
    std::array<float, 2> locObj10 = {32, 14};
    std::array<float, 2> locObj11 = {25, 26};
    std::array<float, 2> locObj12 = {23, 34};

    auto poly1 = geometry::Polygon(verts1);
    auto poly2 = geometry::Polygon(verts2);
    auto poly3 = geometry::Polygon(verts3);

    auto obj1 = world::Object(poly1, locObj1);
    auto obj2 = world::Object(poly2, locObj2);
    auto obj3 = world::Object(poly3, locObj3);
    auto obj4 = world::Object(poly1, locObj4);
    auto obj5 = world::Object(poly2, locObj5);
    auto obj6 = world::Object(poly3, locObj6);
    auto obj7 = world::Object(poly1, locObj7);
    auto obj8 = world::Object(poly2, locObj8);
    auto obj9 = world::Object(poly3, locObj9);
    auto obj10 = world::Object(poly1, locObj10);
    auto obj11 = world::Object(poly2, locObj11);
    auto obj12 = world::Object(poly3, locObj12);

    scenario.addObjectToScenario(obj1);
    scenario.addObjectToScenario(obj2);
    scenario.addObjectToScenario(obj3);
    scenario.addObjectToScenario(obj4);
    scenario.addObjectToScenario(obj5);
    scenario.addObjectToScenario(obj6);
    scenario.addObjectToScenario(obj7);
    scenario.addObjectToScenario(obj8);
    scenario.addObjectToScenario(obj9);
    scenario.addObjectToScenario(obj10);
    scenario.addObjectToScenario(obj11);
    scenario.addObjectToScenario(obj12);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("demolish 1.001");
    glutDisplayFunc(displayfunc);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(physics);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 50, 0, 38);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    std::cout << "//////////////////////// OBJECT PROPS ///////////////////////"
              << std::endl;
    std::cout << std::endl;
    std::cout << "//////////////////////// OBJECT 1 ///////////////////////"
              << std::endl;
    std::cout << std::endl;
    obj1.displayProperties();
    std::cout << "//////////////////////// OBJECT 2 ///////////////////////"
              << std::endl;
    std::cout << std::endl;
    obj2.displayProperties();
    std::cout << "//////////////////////// OBJECT 3 ///////////////////////"
              << std::endl;
    std::cout << std::endl;
    obj3.displayProperties();

    glutMainLoop();

    return 0;
}
