#include "FilterLinear.h"

FilterLinear::FilterLinear(float a, float c) {
	this->a.r = a;
	this->a.g = a;
	this->a.b = a;
	this->c.r = c;
	this->c.g = c;
	this->c.b = c;
}

FilterLinear::FilterLinear(Vec3<float>a, Vec3<float>c) {
	this->a = a;
	this->c = c;
}



Image FilterLinear::operator<<(const Image & src) {

	Image  returnData(src);
	int length = src.getHeight()*src.getWidth();
	if (length == 0) return src;
	Vec3<float> * temp = returnData.getRawDataPtr();
	for (int i = 0; i < length; i++) { 
		*(temp + i) *= a;
		*(temp + i) += c;
		*(temp + i) = (*(temp + i)).clampToLowerBound(0.0);
		*(temp + i) = (*(temp + i)).clampToUpperBound(1.0);
	}
	returnData.setData(temp);
	delete []temp;
	return returnData;
}