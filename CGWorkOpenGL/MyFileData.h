#pragma once
#include "My3dObject.h"

class MyFileData: public MyGlDrawable
{
public:
	MyFileData(void);
	~MyFileData(void);
	
	My3dObject **m_objects;
	int m_nextObj;
	int m_arrSize;

public:
	void addObjectRef(My3dObject* obj);
	void Draw();
	void Draw(bool torchEnabled, bool showFaceNormals, bool showVertexNormals, bool recompile = false);
	void init(bool showFaceNormals, bool showVertexNormals);
	void changeColor(int r,int g,int b);
};
