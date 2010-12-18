#pragma once
#include "My3dObject.h"

class MyFileData
{
public:
	MyFileData(void);
	~MyFileData(void);
	
	My3dObject **m_objects;
	int m_nextObj;
	int m_arrSize;
	MyBoundingBox bbox;

public:
	void addObjectRef(My3dObject* obj);
	void draw(bool torchEnabled, bool showFaceNormals, bool showVertexNormals, bool recompile = false);
	void drawBoundingBox();
	void init(bool showFaceNormals, bool showVertexNormals);
	void changeColor(int r,int g,int b);
};
