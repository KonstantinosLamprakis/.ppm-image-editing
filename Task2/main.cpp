/*
Date: 06/01/2017

Author:
Lamprakis Konstantinos, koslamprakis@gmail.com

2nd C++ Task.
*/

// filter.cpp contains main() method and manipulates CLI arguments.

#include <iostream>
#include <string>
#include "../ppm/ppm.h"
#include "Image.h"
#include <regex>
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "FilterBlur.h"


using namespace std;
using namespace math;
using namespace imaging;

bool isFloatingPoint(string str);
bool isInt(string str);

int main(int argc, char* argv[]) {

	Image *image = new Image();

	if (argc < 2) { // only name of application.
		cerr << "No filters or image path.\nTerminating.\n";
		system("pause");
		return 1;
	}
	
	string path = argv[argc - 1]; // last argument must be the path of image.

	if (!image->load(path, "ppm")) { // method load() makes input control for valid extention and image name, and shoes proper messages. 
		cerr << "\nTerminating.\n";
		system("pause");
		return 1;
	}

	Image result(*image); // result is the final edited image which is stored.

	if (argc == 2) { // the only parameters are name of app and a valid name of file.
		return 0; 
	}

	float argumentsAC[6]; // arguments for a, c at linear filter.
	float y; // argument for gamma filter.
	int N; // argument for blur filter.
	int i = 1; // index of first argument after name of app.
	while (i < argc) {

		// filter declaration:
		if (static_cast<string>(argv[i]) == "-f") {
			i++;
			// linear filter:
			if (static_cast<string>(argv[i]) == "linear") {
				
				for (int j = 0; j < 6; j++) {
					if (isFloatingPoint(argv[++i])) {
						argumentsAC[j] = stof(argv[i]);
					}
					else {
						cerr << "Invalid filter parameters.\nTerminating.\n";
						system("pause");
						return 1;
					}
				}

				Vec3<float> a = Vec3<float>(argumentsAC[0], argumentsAC[1], argumentsAC[2]);
				Vec3<float> c = Vec3<float>(argumentsAC[3], argumentsAC[4], argumentsAC[5]);
				FilterLinear filterLinear(a, c);

				result.setData(*(filterLinear << result).getData());

			}
			// gamma filter: 
			else if (static_cast<string>(argv[i]) == "gamma") {
				if (isFloatingPoint(argv[++i])) {
					y = stod(argv[i]);
				}
				else {
					cerr << "Invalid filter parameter.\nTerminating.\n";
					system("pause");
					return 1;
				}
				FilterGamma filterGamma(y);
				result.setData(*(filterGamma << result).getData());
			}
			// blur filter: 
			else if (static_cast<string>(argv[i]) == "blur") {
				if (isInt(argv[++i])) {
					N = stoi(argv[i]);
				}
				else {
					cerr << "Invalid filter parameter.\nTerminating.\n";
					system("pause");
					return 1;
				}
				FilterBlur filterBlur(N);
				result.setData(*(filterBlur << result).getData());
			}
			else {
				cerr << "Non valid filter.\nTerminating.\n";
				system("pause");
				return 1;
			}
		}
		else if(i+1 != argc) { // then parameter isn't path and hasn't start with -f, so command is invalid.
			cerr << "Invalid command.\nTerminating\n";
			system("pause");
			return 1;
		}

		i++;
	}

	// find the final path(and name) for storing edited image.
	int filenamePos = (path.rfind("\\") != -1) ? path.rfind("\\") + 1 : 0; // find last \ at path and return the position+1 of it(if not exist then return 0).
	string filename = "filtered_" + path.substr(filenamePos, (path.length() - filenamePos));
	string storePath = path.substr(0, filenamePos) + filename;
	
	// store image:
	if (!result.save(storePath, "ppm")) {
		cerr << "\nTerminating.\n";
		system("pause");
		return 1;
	}

	delete image;

	cout << "New image was created successfully." << endl;
	system("pause");
}

// isFloatingPoint() returns if a string represent a valid floating point number.
bool isFloatingPoint(string str) {
	/*
	regex explanation:

		^ = begin of string
		[-+]? = 0 or 1 occurance of - or +
		[0-9]+ = at least one occurance of a number in range [0,9]
		\\. = .
		(\\.[0-9]+)? = 0 or 1 occurance of floating point
		$ = end of string	
	*/
	regex pattern("^[-+]?[0-9]+(\\.[0-9]+)?$");
	return regex_match(str, pattern);
}

// isInt() returns if a string represent a valid integer number.
bool isInt(string str) {

	regex pattern("^[-+]?[0-9]+$");
	return regex_match(str, pattern);
}
