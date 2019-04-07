#pragma once
#ifndef _FILTERLAPLACE
#define _FILTERLAPLACE
#include "FilterBlur.h"

Vec3<float> min(Vec3<float> arg) {
	float min = 1.0;
	if (arg.r < min)min = arg.r;
	if (arg.g < min) min = arg.g;
	if (arg.b < min) min = arg.b;
	arg.r = min;
	arg.g = min;
	arg.b = min;
	return arg;
}

Vec3<float> max(Vec3<float> arg) {
	float max = 0.0;
	if (arg.r > max)max = arg.r;
	if (arg.g > max) max = arg.g;
	if (arg.b > max) max = arg.b;
	arg.r = max;
	arg.g = max;
	arg.b = max;
	return arg;
}

class FilterLaplace :public FilterBlur {

public:
	FilterLaplace() :FilterBlur(3) {
		float * temp=new float [9];
		temp[0] = 0;
		temp[1] = 1;
		temp[2] = 0;
		temp[3] = 1;
		temp[4] = -4;
		temp[5] = 1;
		temp[6] = 0;
		temp[7] = 1;
		temp[8] = 0;
		this->setData(temp);
		delete[]temp;
	}


	Image operator << (const Image &src) {
		Image returnData(src);
		for (unsigned int j = 0; j < src.getHeight(); j++) {
			for (unsigned int i = 0; i < src.getWidth(); i++) {
				Vec3<float> test(0.0);
				for (int m = -1; m <= 1; m++) {
					for (int n = -1 ; n <= 1 ; n++) {
						unsigned int x = i + m;
						unsigned int y = j + n;
						//std::cout << "X: "<< x << ", Y: " << y << std::endl;
						if (x >= 0 && x<src.getWidth() && y >= 0 && y<src.getHeight()) {
							test.r += src.getElement(i + m, j + n).r * this->getElement(m + 1, n + 1);
							test.g += src.getElement(i + m, j + n).g * this->getElement(m + 1, n + 1);
							test.b += src.getElement(i + m, j + n).b * this->getElement(m + 1, n + 1);
						}
					}
				}
				test = test.clampToUpperBound(1.0);
				test = test.clampToLowerBound(0.0);
				
				
				returnData.setElement(i, j, test);
			}
		}
		return returnData;
	}

	

};



#endif
