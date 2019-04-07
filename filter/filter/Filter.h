#ifndef _FILTER
#define _FILTER
#include "Image.h"
class Filter {
public:
	Filter(){}
	Filter(const Filter& src){}
	virtual Image operator << (const Image &src) = 0;
};

#endif
