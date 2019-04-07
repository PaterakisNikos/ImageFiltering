#pragma once
#ifndef _FILTERGAMMA
#define _FILTERGAMMA
#include "Filter.h"
class FilterGamma :public Filter {
protected:
	float gamma;
public:

	FilterGamma(float gamma);

	Image  operator << (const Image &src);

};

#endif