#include <iostream>
#include "ppm.h"
#include <fstream>
#include <string>

using namespace std;

namespace imaging {
	
	float * ReadPPM(const char * filename, int * w, int * h) {

		string h1;
		int h4;
		ifstream in;
		in.open(filename, ios::binary);
		
		in >> h1 >> *(w) >> *(h) >> h4;
			if (h1 != "P6") {
				cout << "Wrong format." << endl;
				in.close();
				return 0;
			}
			if (*(w)<1) {
				cout << "Error in width." << endl;
				in.close();
				return 0;
			}
			if (*(h)<1) {
				cout << "Error in length>" << endl;
				in.close();
				return 0;
			}
			if (h4<0 || h4 > 255) {
				cout << "Error in the information of the pixel." << endl;
				in.close();
				return 0;
			}

		

		char r;
		in.read(&r, 1);
		int length = (*(w)) * (*(h)) * 3;
		float * tempBuffer = new float[length];
		for (int i = 0; i<length; i++) {
			in.read(&r, 1);
			unsigned char t = (unsigned char)r;
			float temp = (float)t;
			tempBuffer[i] = temp;
		}

		in.read(&r, 1);
		unsigned char t = (unsigned char)r;
		float temp = (float)t;
		in.close();
		return tempBuffer;
	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {
		ofstream output(filename, ios::binary);
		string magicNumber = "P6";
		int maxNumber = 255;
		output << magicNumber <<" "<< w << " "<< h << " "<< maxNumber << "\n";
		if (!output.good())
			false;
		int length = w * h * 3;
		for (int i = 0; i < length; i++) {
			float tempf = (float)*(data+i);
			unsigned char tempuc = (unsigned char)tempf;
			char writeIt = (char)tempuc;
			output.write(&writeIt,1);

		}
		if (!output.good())
			return false;
		output.close();
		return true;
	}

}