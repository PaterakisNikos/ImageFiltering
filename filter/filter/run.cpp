#include <iostream>
#include <string>
#include "FilterGamma.h"
#include "FilterLinear.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"

using namespace std;
using namespace math;

std::vector<Filter*> yolo(int argc, char*argv[]) {
	int lastElement = argc - 1;
	int index = 1;
	string tempString = argv[index];
	std::vector<string> data;
	std::vector<Filter*> filters;
	while (tempString == "-f") {
		index++;
		if (index == lastElement) break;
		tempString = argv[index];
		//get from -f to -f to data
		while (tempString != "-f") {
			data.push_back(tempString);
			index++;
			if (index == lastElement) break;
			tempString = argv[index];
		}
		if (data[0] == "gamma") {
			if (data.size() > 2) {
				cout << "Wrong number of arguments 0" << endl;
				system("pause");
				std::vector<Filter*> falseF;
				return falseF;
			}
			FilterGamma* temp = new FilterGamma(stof(data[1]));
			filters.push_back(temp);
		}
		else if (data[0] == "blur") {
			if (data.size() > 2) {
				cout << "Wrong number of arguments 1" << endl;
				system("pause");
				std::vector<Filter*> falseF;
				return falseF;
			}
			FilterBlur* temp = new FilterBlur(stoi(data[1]));
			filters.push_back(temp);
		}
		else if (data[0] == "laplace") {
			if (data.size() > 1) {
				cout << "Wrong number of arguments 2" << endl;
				system("pause");
				std::vector<Filter*> falseF;
				return falseF;
			}
			FilterLaplace * temp = new FilterLaplace();
			filters.push_back(temp);
		}
		else if (data[0] == "linear") {
			if (data.size() != 7) {
				cout << "Wrong number of arguments 3" << endl;
				system("pause");
				std::vector<Filter*> falseF;
				return falseF;
			}
			Vec3<float> a, c;
			a.r = (float)stof(data[1]);
			a.g = (float)stof(data[2]);
			a.b = (float)stof(data[3]);
			c.r = (float)stof(data[4]);
			c.g = (float)stof(data[5]);
			c.b = (float)stof(data[6]);
			 
			//cout << "a: " << a.r << ", " << a.g << ", " << a.b << endl;
			//cout << "c: " << c.r << ", " << c.g << ", " << c.b << endl;
			FilterLinear *temp = new FilterLinear(a, c);
			filters.push_back(temp);
		}
		else {
			cout << "No such a filter exist!" << endl;
			system("pause");
			std::vector<Filter*> falseF;
			return falseF;
		}
		data.clear();
	}
	return filters;
}

string actualName(string fullName) {
	string returnData = "";
	for (size_t i = 0; i < fullName.size(); i++){

		if (fullName.at(i) == '.') break;
		returnData += fullName.at(i);
	}
	return returnData;
}

int main(int argc, char * argv[]) {
	
	std::vector<Filter*> filters = yolo(argc, argv);
	Image myImg;
	string fullFileName = argv[argc - 1];
	for (int j = 0; j < fullFileName.length(); j++) {
		if (fullFileName[j] == '.') {
			if (fullFileName[j + 1] != 'p') {
				cout << "Wrong format."<<endl;
				system("pause");
				return 0;
			}
			else if (fullFileName[j + 2] != 'p') {
				cout << "Wrong format." << endl;
				system("pause");
				return 0;
			}
			else if (fullFileName[j + 3] != 'm') {
				cout << "Wrong format." << endl;
				system("pause");
				return 0;
			}
		}
	}
	if (!myImg.load(actualName(fullFileName), "ppm")) {
		cout << "Wrong file name." << endl;
		system("pause");
		return 0;
	}
	
	for (size_t i = 0; i < filters.size(); i++) myImg = filters[i]->operator<<(myImg);
	string outputFile = "filter_" + actualName(fullFileName);
	myImg.save(outputFile, "ppm");
	
	system("pause");
	return 0;
}


