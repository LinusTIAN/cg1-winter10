#pragma once
#include "pngwrapper.h"
#include <stdexcept>

class MyWhiteVirtualPng :
	public PngWrapper
{
public:
	MyWhiteVirtualPng(const char * name,int width =0,int height =0) { throw std::runtime_error("Operation not supported"); }
	MyWhiteVirtualPng() {}
	~MyWhiteVirtualPng() {}
    void SetFileName(const char * name) { throw std::runtime_error("Operation not supported"); }
    void SetWidth(int width) { throw std::runtime_error("Operation not supported"); }
    void SetHeight(int height) { throw std::runtime_error("Operation not supported"); }
	int GetWidth() { return 1; } 
	int GetHeight() { return 1; }
    void SetValue(unsigned int x,unsigned int y,unsigned int value) { throw std::runtime_error("Operation not supported"); }
	int GetValue(unsigned int x,unsigned int y) { return 0xffffffff; }
	int GetNumChannels() { return 3; }
	int GetBPP() { return 8; }
    bool ReadPng() { throw std::runtime_error("Operation not supported"); }
    bool InitWritePng() { throw std::runtime_error("Operation not supported"); }
    bool WritePng() { throw std::runtime_error("Operation not supported"); }
};
