#include"demolish/utils/render_string.h"
#include<cstring>
void displayString( float x, float y, const char *s ) 
{ 
  glColor3f( 0.5f, 0.5f, 0.9f ); 
  glRasterPos2f( x, y ); 
  unsigned int l = (unsigned int)std::strlen( s ); 
  for(unsigned int i = 0; i < l; ++i) 
      glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *(s + i) ); 
} 

