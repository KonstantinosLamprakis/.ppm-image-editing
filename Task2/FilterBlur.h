// FilterBlur.h represents and implements a filter for an image.

/*
We dont follow exaxly your instructions, because we believe that our way is more simple(and right). The total sum should not devide
by the N*N because some pixels are invalid and aren't included inside the sum, so we declare a counter variable int k to count only 
valid pixels and take the right average of sum. Thus, inheritance of Array<float> is redundant.

In addition, if it's necessary, the << operator algorithm for blur filter could be improved to be more quick. 
*/

#include "Array.h"
#include "Filter.h"
#include "Vec3.h"
#include <iostream>

class FilterBlur : public Filter {

	int N;

public:
	FilterBlur(int N){
		this->N = N;
	}

	virtual imaging::Image operator << (const imaging::Image & image) {

		imaging::Image result(image.getWidth(), image.getHeight());

		// loop for each element(each row and column j, i)
		for (int i = 0; i < image.getHeight(); i++) { // i = row
			for (int j = 0; j < image.getWidth(); j++) {// j = column

				math::Vec3<float> sum(0, 0, 0); // total sum of neibours pixels.
				int k = 0; // counts the number of pixels inside the sum(so we can take the average).

				// loop for sum.
				for (int m = i-(N/2); m <= i+(N/2); m++) {
					for (int n = j-(N/2); n <= j+(N/2); n++) {

						// bounds control:
						if ((m < image.getHeight()) && (m >= 0) && (n < image.getWidth()) && (n >= 0)) {
							sum += image.getElement(n, m);
							k++;
						}
					}
				}

				result.setElement(j, i, sum/k);
			}
		}
		return result;
	}

};