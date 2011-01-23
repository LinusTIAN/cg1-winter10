#ifndef ___SHADERSSKEL_H___
#define ___SHADERSSKEL_H___

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <string>
#include <fstream>

using namespace std;

/* Reads shader code into memory. Call once on program initialization */
void readShaders();

/* Returns true on success, false on failure. */
bool setShaders();

void unsetShaders();

#endif //___SHADERSSKEL_H___