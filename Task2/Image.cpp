
// image.cpp impements Image.h methods.

#include <iostream>
#include <string>
#include "Image.h"
#include "../ppm/ppm.h"

using namespace std;

namespace imaging {

	// Loads the image data from the specified file, if the extension of the filename matches the format string.
	bool Image::load(const string & filename, const string & format) {


		// filename must contains at least 5 characters (e.x. a.ppm).
		if (filename.length() < 5) {
			cerr << "Error. The name of the file is too short." << endl;
			return false;
		}

		// extention must be .ppm or .PPM .
		string extention = filename.substr(filename.length() - 4, filename.length());
		if ((extention != ".ppm") && (extention != ".PPM")) {
			cerr << "Error. Extention isn't valid. This program supports only .ppm extention." << endl;
			return false;
		}

		// check format.
		if (format != "ppm") {
			cerr << "Error. This program supports only ppm format." << endl;
			return false;
		}

		// load image.

		int wTemp, hTemp;
		float * dataArray = imaging::ReadPPM(&filename[0], &wTemp, &hTemp);

		width = wTemp;
		height = hTemp;

		if (!dataArray) return false; // if dataArray == null
		
		buffer = vector<Color>(width*height);// buffer, width and height have protected scope.

		int j = -1;
		for (int i = 0; i < width*height; i++) {
			buffer[i][0] = dataArray[++j];
			buffer[i][1] = dataArray[++j];
			buffer[i][2] = dataArray[++j];
		}

		return true;
	}

	//  Stores the image data to the specified file, if the extension of the filename matches the format string.
	bool Image::save(const std::string & filename, const std::string & format) {

		// check if image is initialized.
		if (width == 0 || height == 0 || buffer.size()==0) {
			cerr << "Error. This image isn't initialized." << endl;
			return false;
		}

		// filename must contains at least 5 characters (e.x. a.ppm).
		if (filename.length() < 5) {
			cerr << "Error. The name of the file is too short." << endl;
			return false;
		}

		// extention must be .ppm or .PPM .
		string extention = filename.substr(filename.length() - 4, filename.length());
		if ((extention != ".ppm") && (extention != ".PPM")) {
			cerr << "Error. Extention isn't valid. This program supports only .ppm extention." << endl;
			return false;
		}

		// check format.
		if (format != "ppm") {
			cerr << "Error. This program supports only ppm format." << endl;
			return false;
		}

		// save Image.

		float * dataArray = new float[width * height * 3];
		int j = -1;
		for (int i = 0; i < width*height; i++) {
			dataArray[++j] = buffer[i][0];
			dataArray[++j] = buffer[i][1];
			dataArray[++j] = buffer[i][2];
		}

		return imaging::WritePPM(dataArray, width, height, &filename[0]);

	}

}