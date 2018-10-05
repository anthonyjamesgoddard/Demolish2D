#ifndef _DEMvis2D
#define _DEMvis2D

#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

#include"scenario.h"

namespace demolish{
    namespace world{
        class DEMvis2D;
        }
}

class demolish::world::DEMvis2D
{
public:
    Scenario                _scenario
    void                    drawScenario();

//OpenGL / X11 stuff
    DisplayDisplay          *dpy;
    Window                  root;
    GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XVisualInfo             *vi;
    Colormap                cmap;
    XSetWindowAttributes    swa;
    Window                  win;
    GLXContext              glc;
    XWindowAttributes       gwa;
    XEvent                  xev;
}

#endif
