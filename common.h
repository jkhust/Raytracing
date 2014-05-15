#ifndef __COMMON_H__
#define __COMMON_H__

#define __MAC__

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __MAC__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif


#define PI 3.14159265358979323846264338327f

const int iScreenWidth = 800;
const int iScreenHeight = 600;

// **************************************************


#endif
