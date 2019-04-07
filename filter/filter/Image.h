#pragma once
#ifndef _IMAGE
#define _IMAGE

#include "Array.h"
#include "Vec3.h"

using namespace math;

class Image:public Array< Vec3<float> > {

public:

	// constructors and destructor

	/*! Default constructor.
	*
	* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
	*/
	Image();

	/*! Constructor with width and height specification.
	*
	* \param width is the desired width of the new image.
	* \param height is the desired height of the new image.
	*/
	Image(unsigned int width, unsigned int height);

	/*! Constructor with data initialization.
	*
	* \param width is the desired width of the new image.
	* \param height is the desired height of the new image.
	* \param data_ptr is the source of the data to copy to the internal image buffer.
	*
	* \see setData
	*/
	Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr);

	/*! Copy constructor.
	*
	* \param src is the source image to replicate in this object.
	*/
	Image(const Image &src);

	/*! The Image destructor.
	*/
	~Image();

	/*! Copy assignment operator.
	*
	* \param right is the source image.
	*/

	/*!
	* Loads the image data from the specified file, if the extension of the filename matches the format string.
	*
	* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
	* Image object is initialized, its contents are wiped out before initializing it to the width, height and data
	* read from the file.
	*
	* \param filename is the string of the file to read the image data from.
	* \param format specifies the file format according to which the image data should be decoded from the file.
	* Only the "ppm" format is a valid format string for now.
	*
	* \return true if the loading completes successfully, false otherwise.
	*/
	bool load(const std::string & filename, const std::string & format);

	/*!
	* Stores the image data to the specified file, if the extension of the filename matches the format string.
	*
	* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
	* Image object is not initialized, the method should return immediately with a false return value.
	*
	* \param filename is the string of the file to write the image data to.
	* \param format specifies the file format according to which the image data should be encoded to the file.
	* Only the "ppm" format is a valid format string for now.
	*
	* \return true if the save operation completes successfully, false otherwise.
	*/
	bool save(const std::string & filename, const std::string & format);
	
};


#endif