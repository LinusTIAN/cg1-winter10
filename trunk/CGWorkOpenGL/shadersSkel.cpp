#include "stdafx.h"
#include "shadersSkel.h"

static PFNGLCREATESHADERPROC glCreateShader = NULL;
static PFNGLSHADERSOURCEPROC glShaderSource = NULL;
static PFNGLCOMPILESHADERPROC glCompileShader = NULL;
static PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
static PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
static PFNGLATTACHSHADERPROC glAttachShader = NULL;
static PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
static PFNGLUSEPROGRAMPROC glUseProgram = NULL;
static PFNGLDELETESHADERPROC glDeleteShader = NULL;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;

static GLchar	**vs,
				**fs;
static int	vs_lines,
			fs_lines;

int fileToGLcharPP(char * filename, GLchar ***res)
{
	string * strp = NULL;
	string str;
	int linesNum = 0;
    fstream file_op2(filename,ios::in);
	int b = file_op2.fail();
    while(getline(file_op2,str,'\n'))
	{
        linesNum++;
	}
	strp = new string[linesNum];
	file_op2.clear();
    file_op2.close();
    fstream file_op(filename,ios::in);
	int i;
	for (i = 0; i < linesNum; i++)
	{
		getline(file_op,strp[i],'\n');
		strp[i] += '\n';
	}
	*res = new GLchar*[linesNum];
	for (i = 0; i < linesNum; i++)
	{
		(*res)[i] = new GLchar[strlen(strp[i].c_str())+1];
		strcpy((*res)[i],strp[i].c_str());
	}
	delete[] strp;

    file_op.close();
	return linesNum;

}

void deleteGLcharPP(GLchar **s, int num)
{
	int i;
	for ( i = 0; i < num; i++)
		delete[] s[i];
	delete[] s;
}

void readShaders() {
	static bool init = false;

	if (init) return;

	vs_lines = fileToGLcharPP("..\\shaders\\shaders.vert", &vs);
	fs_lines = fileToGLcharPP("..\\shaders\\shaders.frag", &fs);

	init = true;
}

// Get pointers to needed OpenGL GLSL-related functions. Idempotent - subsequent calls will return immediately
void findFunctions()
{
	static bool called = false;

	if (called)
		return;

	glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
	glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC) wglGetProcAddress("glDeleteShader");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC) wglGetProcAddress("glDeleteProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog");

	called = true;
}

bool setShaders()
{
	findFunctions();
	
	GLint result;
	GLchar info_log[2048];

	char ok[] = "No errors.\xA";

	// Load fragment shader
	GLuint Fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fshader, fs_lines, (const GLchar**)fs, NULL);	
	glCompileShader(Fshader);
	glGetShaderiv(Fshader, GL_COMPILE_STATUS, &result);
	glGetShaderInfoLog(Fshader, 2047, &result, info_log ); // check the log for compilation errors
	if (strcmp(info_log, ok)) {
		CString s;
		s.Format("Error creating fragment shader: %s", info_log);
		AfxMessageBox(s);
		return false;
	}

	// Load vertex shader
	GLuint Vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Vshader, vs_lines, (const GLchar**)vs, NULL);	
	glCompileShader(Vshader);
	glGetShaderiv(Vshader, GL_COMPILE_STATUS, &result);
	glGetShaderInfoLog(Vshader, 2047, &result, info_log ); // check the log for compilation errors
	if (strcmp(info_log, ok)) {
		CString s;
		s.Format("Error creating vertex shader: %s", info_log);
		AfxMessageBox(s);
		return false;
	}
	
	// Now create the program
	GLuint prog = glCreateProgram();
	glAttachShader(prog, Fshader);
	glAttachShader(prog, Vshader);
	glLinkProgram(prog);
	glGetProgramiv(prog,GL_LINK_STATUS,&result);
	glGetProgramInfoLog(prog,2047,&result,info_log); // check th log for linking errors
	if (strcmp(info_log, ok)) {
		CString s;
		s.Format("Error creating program: %s", info_log);
		AfxMessageBox(s);
		return false;
	}
	glUseProgram(prog);
	
	// cleanup
	glDeleteShader(Fshader);
	glDeleteShader(Vshader);
	glDeleteProgram(prog);

	return true; 
}

void unsetShaders()
{
	findFunctions();

	glUseProgram(0);	// return to fixed functionality - shaders are automatically detached and both
						// shaders and program are deleted since they were previously flagged for
						// deletion
}

