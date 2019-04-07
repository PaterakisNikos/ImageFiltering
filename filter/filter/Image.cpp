#include "Image.h"
#include "../ppm/ppm.h"
Image::Image() : Array() {}

Image::Image(unsigned int width,unsigned int height) : Array(width,height) {}

Image::Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr) : Array(width, height,data_ptr){}

Image::Image(const Image &src) : Array((Array < Vec3 < float> > )src) {}

Image::~Image() {}

bool Image::load(const std::string & filename, const std::string & format) {
	if (format.compare("ppm") != 0)
		return false;
	std::string fullFileName = filename + "." + format;
	unsigned int tempW = this->width;
	unsigned int tempH = this->height;
	float * temp = imaging::ReadPPM(fullFileName.c_str(), (int *)(&(this->width)), (int *)(&(this->height)));
	if (temp == 0) {
		this->width = tempW;
		this->height = tempH;
		return false;
	}
	
	int length = Image::getHeight()*Image::getWidth() * 3;
	this->buffer.clear();
	Vec3<float> color;
	int howManyColors = 0;
	for (int i = 0; i < length; i++) {
		if (howManyColors == 3) {
			this->buffer.push_back (color);
			howManyColors = 0;
		}
		if (howManyColors == 0)
			color.r = temp[i] / 255.0f;
		else if (howManyColors == 1)
			color.g = temp[i] / 255.0f;
		else if (howManyColors == 2)
			color.b = temp[i] / 255.0f;
		howManyColors++;
	}
	delete[] temp;
	return true;
}

bool Image::save(const std::string & filename, const std::string & format) {
	if (format.compare("ppm") != 0)
		return false;
	if (this->buffer.size() == 0)
		return false;
	std::string fullFileName = filename + "." + format;
	int length = Image::getHeight()*this->getWidth();
	float * temp = new float[Image::getHeight()*this->getWidth() * 3];
	Vec3<float>color;
	for (int i = 0; i < length; i++) {

		color = this->buffer[i];

		temp[i * 3] = color.r*255.0f;
		temp[i * 3 + 1] = color.g*255.0f;
		temp[i * 3 + 2] = color.b*255.0f;
	}
	bool returnData = imaging::WritePPM(temp, this->getWidth(), this->getHeight(), fullFileName.c_str());
	delete[] temp;
	return returnData;
}