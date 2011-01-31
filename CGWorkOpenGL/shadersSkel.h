#ifndef ___SHADERSSKEL_H___
#define ___SHADERSSKEL_H___

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/wglext.h>
#include <string>
#include <fstream>

using namespace std;

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;

typedef enum shaderType_t {
	SH_DEFAULT,
	SH_CEL_SHADER,
	SH_EDGE_SHADER_PASS1,
	SH_EDGE_SHADER_PASS2,
	SH_DRAW_BG
} shaderType_t;

/* Set shader uniform variables to enable selected shading behavior */
void selectShader(shaderType_t type, int screen_w, int screen_h);

/* Perform shader initializations. Call once on program start if you wish to use shaders
   later on */
void initShaders();

/* Returns true on success, false on failure. */
void setShaders();

/* Delete shaders. Call once before exiting the program. */
void delShaders();

/* Return to fixed-pipeline behaviour */
void unsetShaders();

#endif //___SHADERSSKEL_H___