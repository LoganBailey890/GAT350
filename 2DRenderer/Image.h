#pragma once
#include "ColorBuffer.h"
#include <string>
class Image
{
public:
	~Image();
	bool Load(const std::string& filename, uint8_t alpha = 256);
	void Flip();

	friend class Framebuffer;
public:
	ColorBuffer colorBuffer;
private:
	//uint8_t* buffer;
	/*int width;
	int height;*/

};
