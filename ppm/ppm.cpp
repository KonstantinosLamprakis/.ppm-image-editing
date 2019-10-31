// ppm.cpp impement namespace of ppm.h, methods ReadPPM and WritePPM.

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "ppm.h"


using namespace std;

namespace imaging {

	// Reads a PPM image file and returns a pointer to a newly allocated float array containing the image data.
	float * ReadPPM(const char * filename, int * w, int * h) {

		// Read Header:

		string type; // type of image P6, P3.
		int maxval; // the maximum value of each color e.x.255

		ifstream inFile(filename, ios::in | ios::binary);

		// if error occurs during opening. 
		if (!inFile) {
			cerr << "Error: failure opening file." << endl;
			return nullptr;
		}


		// if a value doesn't exist (that means inFile returns null which means false).
		if (!(inFile >> type >> *w >> *h >> maxval)) { // read type, width, height and maxval.
			cerr << "A parameter is missing. Press any key to terminate.";
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // This prevent the termination of program.
			return nullptr;
		}

		if (type != "P6") {
			cerr << "Error: This program supports only P6 type ppm images." << endl;
			return nullptr;
		}

		if (maxval > 255) {
			cerr << "Error: This program supports only 24-bit ppm images. Pixel's size must not be greater than 255." << endl;
			return nullptr;
		}

		// Read Data: 


		unsigned char * colorChar = new unsigned char[*w * *h * 3]; // array stores an integer(as 1-byte char between 0-255) for each color (r,g,b) of each pixel.
		inFile.read(reinterpret_cast<char *>(colorChar), *w * *h * 3);

		float * colorArray = new float[*w * *h * 3]; // array stores a float for each color (r,g,b) of each pixel.

													 // Initialization of colorArray with floats. It works like right-shift of elements at colorChar, otherwise there is a bug an 1st column of pixels.
		for (int i = 0; i < (*w) * (*h) * 3 - 1; i++) {
			colorArray[i] = colorChar[i + 1] / 255.0f;
		}
		colorArray[(*w) * (*h) * 3 - 1] = colorChar[0] / 255.0f;

		// doesn't close file because it will close anyway when the methos terminate.
		inFile.close();
		delete[] colorChar;
		return colorArray;
	}

	// Writes an image buffer as a PPM file.
	bool WritePPM(const float * data, int w, int h, const char * filename) {

		if (!data) return false; //if data == nullptr then return false.

		ofstream outFile(filename, ios::out | ios::binary);

		// if error occurs during creation.
		if (!outFile) {
			cerr << "Error: failure creating file." << endl;
			return false;
		}

		// Write header.
		outFile << "P6" << '\n' << w << '\n' << h << '\n' << "255" << '\n';

		// Write data.

		unsigned char * charData = new unsigned char[w * h * 3];
		for (int i = 0; i < w * h * 3; i++) {
			charData[i] = data[i] * 255;
		}
		outFile.write(reinterpret_cast<char *>(charData), w * h * 3);
		outFile.close();

		delete[] charData;
		delete[] data;
		return true;
	}

}