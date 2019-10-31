
#ifndef _ARRAY
#define _ARRAY

#include <string>
#include <vector>

// The math namespace contains every class or function associated with the Array(data structure).
namespace math
{

	//------------------------------------ class Array ------------------------------------------------

	/*! It is the class that represents a generic data container(as two dimension array).
	*
	* It holds the actual buffer of the elements values and provides methods for accessing them,
	* either as individual elements or as a memory block.
	*/
	template <typename T>
	class Array
	{
	protected:
		std::vector<T>  buffer; // Holds the Array data.

		unsigned int width, height; // The width and the height of the Array.

	public:

		// Returns the width of the array
		const unsigned int getWidth() const { return width; }

		// Returns the height of the array.
		const unsigned int getHeight() const { return height; }

		// data accessors

		/*! Obtains a vector to the internal data.
		*
		*  This is NOT a copy of the internal image data, but rather a pointer
		*  to the internally allocated space, so DO NOT attempt to delete the pointer.
		*/
		std::vector<T> * getData() {
			return &buffer;
		}

		/*! Obtains the element of the array at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the element to get.
		*  \param y is the (zero-based) vertical index of the element to get.
		*
		*  \return The value of the (x,y) element.
		*/
		T getElement(unsigned int x, unsigned int y) const {

			// if its out of border return null.
			if ((x > width) || (y > height) || (x < 0) || (y < 0)) {
				std::cerr << "Error: getElement() ask for element out of border.\n";
				system("pause");
				exit(1);
			}

			return buffer[y*width + x];
		}

		// data mutators

		/*! Sets the value to a (x,y) element.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the element to set.
		*  \param y is the (zero-based) vertical index of the element to set.
		*  \param value is the new value for the (x,y) element.
		*/
		void setElement(unsigned int x, unsigned int y, T & value) {

			if ((x > width) || (y > height) || (x < 0) || (y < 0)) {
				cerr << "Error: x or/and y are out of border." << endl;
				system("pause");
				exit(1);
			}
			buffer[y*width + x] = value;
		}

		/*! Copies the array data from an external raw buffer to the internal array buffer.
		* If the width or height of the image are 0, the method should exit immediately.
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const std::vector<T> data_vector) {

			if (data_vector.size() > buffer.size()) {
				cerr << "Error: Array isn't suitable for storing, because it has small size." << endl;
				system("pause");
				exit(1);
			}
			buffer = data_vector;
		}

		// constructors and destructor

		/*! Default constructor.
		*
		* By default, the dimensions of the array should be zero and the buffer must be set to null.
		*/
		Array() : width(0), height(0), buffer(std::vector<T>(0)){}

		/*! Constructor with width and height specification.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		*/
		Array(unsigned int width, unsigned int height) : width(width), height(height), buffer(std :: vector<T>(width*height)) {}

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new array.
		* \param height is the desired height of the new array.
		* \param data_ptr is the source of the data to copy to the internal array buffer.
		*
		* \see setData
		*/
		Array(unsigned int width, unsigned int height, const std::vector<T> data_vector) : width(width), height(height), buffer(std :: vector<T>(width*height)) {
			setData(data_vector);
		}

		/*! Copy constructor.
		*
		* \param src is the source array to replicate in this object.
		*/
		Array(const Array &src): Array(src.getWidth(), src.getHeight(), src.buffer) {}

		// The Array destructor.
		~Array() {
			buffer.clear();
		}

		/*! Copy assignment operator.
		*
		* \param right is the source array.
		*/
		Array & operator = (const Array & right) {
			Array temp(right);
			return temp;
		}

		// () operator.
		T & Array::operator () (unsigned int i, unsigned int j) {
			return buffer[j*getWidth() + i]; // j = row, i = column and i,j = 0, 1, 2(zero-based)
		}

	};

} // namespace math

#endif