#pragma once
#ifndef _FILTERBLUR
#define _FILTERBLUR
#include "Filter.h"
class FilterBlur :public Array<float>, public Filter{
protected:
	 int N;
public:
	FilterBlur(int N) :Array(N,N) {
		this->N = N;
		int length = this->N*this->N; 
		float * data = new float[length];
		for (int i = 0; i < length; i++) *(data + i) = (1 /(float) (length)); //length = N^2;
		this->setData(data);
		delete[]data;
	}

	FilterBlur() : Array() {}

	Image operator << (const Image &src) {
		Image returnData(src);
		for (unsigned int j = 0; j < src.getHeight(); j++) {
			for (unsigned int i = 0; i < src.getWidth(); i++) {
				Vec3<float> test(0.0);
				for (int m = -N / 2; m < N / 2; m++) {
					for (int n = -N / 2; n < N / 2; n++) {
						unsigned int x = i + m;
						unsigned int y = j + n;
						//std::cout << "X: "<< x << ", Y: " << y << std::endl;
						if (x>=0 && x<src.getWidth() && y >=0 && y<src.getHeight()) {
							test.r += src.getElement(i + m, j + n).r * this->getElement(m+N/2,n+N/2);
							test.g += src.getElement(i + m, j + n).g * this->getElement(m + N / 2, n + N / 2);
							test.b += src.getElement(i + m, j + n).b * this->getElement(m + N / 2, n + N / 2);
						}
					}
				}
				
				//std::cout << N * N << std::endl;
				//std::cout << test.r << std::endl;
				
				
				//if(j>640)
					//std::cout << "X: " << i << ", Y: " << j << std::endl;
				test = test.clampToLowerBound(0.0);
				test = test.clampToUpperBound(1.0);


				returnData.setElement(i, j, test);
			}
		}
		return returnData;
	}

};

#endif