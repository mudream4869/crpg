#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#elif _WIN32
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL\glut.h>
#include <windows.h>
#endif
