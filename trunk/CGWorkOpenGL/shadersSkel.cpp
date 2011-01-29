#include "stdafx.h"
#include "shadersSkel.h"

PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2IPROC glUniform2i = NULL;
PFNGLUNIFORM2FPROC glUniform2f = NULL;
PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;

static GLchar	**vs,
				**fs;
static int	vs_lines,
			fs_lines;

static GLuint Vshader, Fshader, prog;

static GLint uniCelLoc = -1,
			 uniEdgePassLoc = -1,
			 uniScreenSizeLoc = -1;

void readyUniforms()
{
	uniCelLoc = glGetUniformLocation(prog, "celShade");
	uniEdgePassLoc = glGetUniformLocation(prog, "edge_shading_pass");
	uniScreenSizeLoc = glGetUniformLocation(prog, "screenSize");
}

static int fileToGLcharPP(char * filename, GLchar ***res)
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

static void readShaders() {
	static bool init = false;

	if (init) return;

	vs_lines = fileToGLcharPP("..\\shaders\\shaders.vert", &vs);
	fs_lines = fileToGLcharPP("..\\shaders\\shaders.frag", &fs);

	init = true;
}

// Get pointers to needed OpenGL GLSL-related functions. Idempotent - subsequent calls will return immediately
static void findFunctions()
{
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
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
	glUniform1i = (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC) wglGetProcAddress("glUniform1iv");
	glUniform2i = (PFNGLUNIFORM2IPROC) wglGetProcAddress("glUniform2i");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC) wglGetProcAddress("glActiveTexture");
	glUniform2f  = (PFNGLUNIFORM2FPROC) wglGetProcAddress("glUniform2f");
}

static void registerShaders()
{
	GLint result;
	GLchar info_log[2048];

	char ok[] = "No errors.\xA";

	// Load fragment shader
	Fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fshader, fs_lines, (const GLchar**)fs, NULL);	
	glCompileShader(Fshader);
	glGetShaderiv(Fshader, GL_COMPILE_STATUS, &result);
	glGetShaderInfoLog(Fshader, 2047, &result, info_log ); // check the log for compilation errors
	if (strcmp(info_log, ok)) {
		CString s;
		s.Format("Error creating fragment shader: %s", info_log);
		AfxMessageBox(s);
		return;
	}

	// Load vertex shader
	Vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Vshader, vs_lines, (const GLchar**)vs, NULL);	
	glCompileShader(Vshader);
	glGetShaderiv(Vshader, GL_COMPILE_STATUS, &result);
	glGetShaderInfoLog(Vshader, 2047, &result, info_log ); // check the log for compilation errors
	if (strcmp(info_log, ok)) {
		CString s;
		s.Format("Error creating vertex shader: %s", info_log);
		AfxMessageBox(s);
		return;
	}
	
	// Now create the program
	prog = glCreateProgram();
	glAttachShader(prog, Fshader);
	glAttachShader(prog, Vshader);
	glLinkProgram(prog);
	glGetProgramiv(prog,GL_LINK_STATUS,&result);
	glGetProgramInfoLog(prog,2047,&result,info_log); // check th log for linking errors
	if (strcmp(info_log, ok)) {
		CString s;
		s.Format("Error creating program: %s", info_log);
		AfxMessageBox(s);
		return;
	}
}

void initShaders()
{
	static bool called = false;

	if (called) return;

	findFunctions();
	readShaders();
	registerShaders();
}

void setShaders()
{
	glUseProgram(prog);
	readyUniforms();
}

void unsetShaders()
{
	glUseProgram(0);
}

void delShaders()
{
	glDeleteShader(Fshader);
	glDeleteShader(Vshader);
	glDeleteProgram(prog);
	unsetShaders();

	delete[] vs;
	delete[] fs;
}

void selectShader(shaderType_t type, int screen_w, int screen_h)
{
	int celShade, edge_shading_pass;

	switch (type) {
	case SH_CEL_SHADER:
		celShade = 1;
		edge_shading_pass = 0;
		break;
	case SH_EDGE_SHADER_PASS1:
		celShade = 0;
		edge_shading_pass = 1;
		break;
	case SH_EDGE_SHADER_PASS2:
		celShade = 0;
		edge_shading_pass = 2;
		break;
	default:
		celShade = edge_shading_pass = 0;
		break;
	}

	glUniform1i(uniCelLoc, celShade);
	glUniform1i(uniEdgePassLoc, edge_shading_pass);
	//glUniform2f(uniScreenSizeLoc, screen_w, screen_h);
	
	//GLint loc = glGetUniformLocation(prog, "tex");
	//glUniform1i(loc, 0);
	//loc = glGetUniformLocation(prog, "outlineTex");
	//glUniform1i(loc, 1);
}
