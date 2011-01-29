#include "MyEdgeDetector.h"
#include <exception>
#include <cmath>

using namespace std;

MyEdgeDetector::MyEdgeDetector(int screen_w, int screen_h)
:	w(screen_w), h(screen_h)
{
	read_buffer = new GLfloat[w*h*3];
	write_buffer = new GLubyte[w*h];

	if (!read_buffer || !write_buffer)
		throw exception("Failed dynamically allocating image buffer");
}

MyEdgeDetector::~MyEdgeDetector(void)
{
	delete[] read_buffer;
	delete[] write_buffer;
}

void MyEdgeDetector::readBuffers()
{
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_FLOAT, read_buffer);
}

void MyEdgeDetector::detectEdges()
{
	readBuffers();

	// Kernels for Sobel algorithm
	int GX[3][3] = {	{-1,  0,  1},
						{-2,  0,  2},
						{-1,  0,  1}	};
	int GY[3][3] = {	{ 1,  2,  1},
						{ 0,  0,  0},
						{-1, -2, -1}	};

	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int index = y*w + x;

			float y_sum_n = 0,
				  y_sum_d = 0,
				  x_sum_n = 0,
				  x_sum_d = 0,
				  sum_n = 0,
				  sum_d = 0,
				  sum = 0;

			// do nothing on image boundaries
			if (y == 0 || y == h-1)
				;
			else if (x == 0 || x == w-1)
				;

			// perform convolution
			else {
				// Approximate X,Y gradients
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						int cindex = 3*( (y+j)*w + (x+ i) );

						// calculate for normals
						x_sum_n += read_buffer[cindex]*GX[i+1][j+1];
						y_sum_n += read_buffer[cindex]*GY[i+1][j+1];

						// calculate for depth
						x_sum_d += read_buffer[cindex+2]*GX[i+1][j+1];
						y_sum_d += read_buffer[cindex+2]*GY[i+1][j+1];
					}
				}

				// Approximate gradient magnitude
				sum_n = fabs(x_sum_n) + fabs(y_sum_n);
				sum_d = fabs(x_sum_d) + fabs(y_sum_d);
				sum = max(sum_n, sum_d);

				// clamp sum to [0, 1]. gray midtones are discarded to make the outline clearer
				if (sum < 0.6) sum = 0;
				else sum = 1;
			}

			// invert, since we want edges in black!
			write_buffer[index] = (GLubyte)sum;
		}
	}
}

void MyEdgeDetector::drawEdges()
{
	glClearColor((GLclampf)0.0, (GLclampf)1.0, (GLclampf)0.0, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2d(0,0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glDrawPixels(w, h, GL_RGB, GL_FLOAT, write_buffer);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void MyEdgeDetector::stencilEdges()
{
	//glClearColor((GLclampf)0.0, (GLclampf)1.0, (GLclampf)0.0, (GLclampf)1.0);
	glClearStencil(0x0);
	glClear(GL_STENCIL_BUFFER_BIT/*GL_COLOR_BUFFER_BIT*/);

	/* Only draw where the stencil is zero = no boundary line is present */
	glStencilFunc (GL_EQUAL, 0x0, 0x1);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glRasterPos2d(0,0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glDrawPixels(w, h, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, write_buffer);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

GLubyte* MyEdgeDetector::getEdgeMap()
{
	return write_buffer;
}