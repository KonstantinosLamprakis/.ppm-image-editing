// FilterLinear.h represents and implements a filter to an image.

#ifndef _LINEAR
#define _LINEAR

#include "Filter.h"
#include "Vec3.h"
#include "Image.h"
#include <vector>

#include <iostream>

class FilterLinear : public Filter {

	math::Vec3<float> a, c;

public:
	// overwritting operator << from base class.
	virtual imaging::Image operator << (const imaging::Image & image) {

		imaging::Image result(image.getWidth(), image.getHeight());
		for (int i = 0; i < image.getHeight(); i++) { // i = row
			for (int j = 0; j < image.getWidth(); j++) {// j = column
				math::Vec3<float> temp((a * image.getElement(j, i)) + c);
				temp = temp.clampToLowerBound(0.0f);
				temp = temp.clampToUpperBound(1.0f);
				result.setElement(j, i, temp);
			}
		}

		return result;
	}

	FilterLinear(math::Vec3<float> a, math::Vec3<float> c) {
		this->a = a;
		this->c = c;
	}
};

#endif