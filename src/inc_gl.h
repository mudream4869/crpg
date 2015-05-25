#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h>
#elif __FreeBSD__ || __linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#elif _WIN32

/** special hack */
#define GLUT_DISABLE_ATEXIT_HACK

#include <GL\glut.h>
#include <windows.h>
#endif
