// FilterGamma.h represents and implements a filter to an image.

#ifndef _GAMMA
#define _GAMMA

#include "Filter.h"
#include <iostream>
#include <cmath>

class FilterGamma : public Filter {

double y;

public:
	// overwritting operator << from base class.
	virtual imaging::Image operator << (const imaging::Image & image) {
		imaging::Image result(image.getWidth(), image.getHeight());
		for (int i = 0; i < image.getHeight(); i++) { // i = row
			for (int j = 0; j < image.getWidth(); j++) {// j = column
				result.setElement(j, i, getPow(image.getElement(j, i), y));
			}
		}
		return result;
	}

	FilterGamma(double y) {
		this->y = y;
		// input control.
		if ((y < 0.5) || (y > 2)) {
			std::cerr << "Error: y must be between 0.5-2.0 .\nTerminating.\n";
			system("pause");
			exit(1);
		}

	}

private:
	math::Vec3<float> getPow(math::Vec3<float> a, double p) {
		a[0] = pow(a[0], p);
		a[1] = pow(a[1], p);
		a[2] = pow(a[2], p);
		return a;
	}
};

#endif