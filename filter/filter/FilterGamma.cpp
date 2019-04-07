#include "FilterGamma.h"
#include <math.h>
FilterGamma::FilterGamma(float gamma) { this->gamma = gamma; }

Image FilterGamma::operator << (const Image &src) {
	Image  returnData(src);
	int length = src.getHeight()*src.getWidth();
	if (length == 0) return src;
	Vec3<float> * temp = returnData.getRawDataPtr();
	for (int i = 0; i < length; i++) {
		Vec3<float> pushVec;
		pushVec.r = pow((*(temp + i)).r,this->gamma);
		pushVec.g = pow((*(temp + i)).g, this->gamma);
		pushVec.b = pow((*(temp + i)).b, this->gamma);
		pushVec = pushVec.clampToLowerBound(0.0);
		pushVec = pushVec.clampToUpperBound(1.0);
		*(temp + i) = pushVec;
	}
	returnData.setData(temp);
	delete[]temp;
	return returnData;
}