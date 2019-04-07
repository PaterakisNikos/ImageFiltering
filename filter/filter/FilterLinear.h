#pragma once
#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "Filter.h"

class FilterLinear :public Filter {
protected:
	Vec3<float> a;
	Vec3<float> c;
public:
	FilterLinear(Vec3<float>a,Vec3<float>c);
	FilterLinear(float a, float c);

	Image  operator << (const Image &src);
};

#endif