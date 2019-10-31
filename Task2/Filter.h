#ifndef _FILTER
#define _FILTER

#include "Image.h"

class Filter {
	
public:
	virtual imaging::Image operator << (const imaging::Image & image) = 0;
		
};

#endif