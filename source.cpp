#include<iostream>
#include"scenario.h"
#include"glut.h"
using namespace demolish;

world::Scenario scenario(0.1,10);

void displayfunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scenario.render();
    
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(1,1);
    glVertex2f(11,1);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    std::vector<Vertex> verts1;

    /*
     *  "K"
     *
     *  Tested:
     *      Convex Hull (correct)
     *      Plenim. Sectorisation (correct)
     *
     *      !! there is an issue with the values 
     *      of the cartesian coords in the sectors
     *  
     *  Temporary Patch:
     *      If we need cartesian coords then
     *      just calculate them from polar 
     *      coordinates
     */

    
    verts1.push_back(Vertex(1,1));
    verts1.push_back(Vertex(0.5,1.9));
    verts1.push_back(Vertex(0,0.7));
    verts1.push_back(Vertex(-0.5,0.9));
    verts1.push_back(Vertex(-1,1));
    verts1.push_back(Vertex(-0.5,0));
    verts1.push_back(Vertex(-1,-1));
    verts1.push_back(Vertex(0,-0.7));
    verts1.push_back(Vertex(1,-1));
    verts1.push_back(Vertex(1.3,0.05));


    std::vector<Vertex> verts2;

    /*
     *  "Kv2"
     *
     *  Tested:
     *      Convex Hull (correct)
     *      Plenim. Sectorisation (correct)
     *
     *      !! there is an issue with the values 
     *      of the cartesian coords in the sectors
     *  
     *  Temporary Patch:
     *      If we need cartesian coords then
     *      just calculate them from polar 
     *      coordinates
     */

    
    verts2.push_back(Vertex(1,1));
    verts2.push_back(Vertex(0,0.7));
    verts2.push_back(Vertex(-0.5,1.1));
    verts2.push_back(Vertex(-1,1));
    verts2.push_back(Vertex(-0.5,0));
    verts2.push_back(Vertex(-1,-1));
    verts2.push_back(Vertex(0,-0.9));
    verts2.push_back(Vertex(1,-1));
    verts2.push_back(Vertex(1.3,0.05));
    verts2.push_back(Vertex(1.3,-0.1));
     

    std::array<float,2> locObj1 = {5,5};
    std::array<float,2> locObj2 = {3,8};
     
    auto poly = geometry::Polygon(verts1);
    auto poly2= geometry::Polygon(verts2);

    auto obj1 = world::Object(poly,locObj1);
    auto obj2 = world::Object(poly2,locObj2);

    scenario.addObjectToScenario(obj1);
    scenario.addObjectToScenario(obj2);

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 1024, 768 );
    glutCreateWindow( "demolish 1.0" );
    glutDisplayFunc(displayfunc);


    glMatrixMode( GL_PROJECTION );
    glPushMatrix( );
    glLoadIdentity( );
    gluOrtho2D( 0, 12, 0, 10 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glLoadIdentity( );

    glutMainLoop( );

    return 0;
}
