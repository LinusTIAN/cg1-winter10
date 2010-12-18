#include "MyTorchFX.h"
#include <typeinfo>

void MyTorchFX::TransformsUpdated(void)
{
	glGetDoublev(GL_MODELVIEW_MATRIX, &modelMatrix[0]);
	glGetDoublev(GL_PROJECTION_MATRIX, &projMatrix[0]);
	glGetIntegerv(GL_VIEWPORT, &viewportMatrix[0]);
}

void MyTorchFX::Apply(MyGlDrawable& target)
{
	if (typeid(target) != typeid(MyVertex))
		return;

	MyVertex *v = &(static_cast<MyVertex&>(target));

	double	o_cursor_x,
			o_cursor_y,
			o_cursor_z;

	gluUnProject(cursor_x, cursor_y, cursor_z,
				 modelMatrix, projMatrix, viewportMatrix,
				 &o_cursor_x, &o_cursor_y, &o_cursor_z);

	double	dx = v->x - o_cursor_x,
			dy = v->y - o_cursor_y,
			dz = v->z - o_cursor_z,
			distance = sqrt(dx*dx + dy*dy);

	double colorModifier = 1 - (distance / dim_range);
	colorModifier = (colorModifier < 0.25) ? 0.25 : colorModifier;

	/*glColor3d(	colorModifier*g_3dModel->m_color[0],
				colorModifier*g_3dModel->m_color[1],
				colorModifier*g_3dModel->m_color[2]	);*/
	
				//AfxMessageBox("ERROR!!!!! GOT TO FX!!!");
}