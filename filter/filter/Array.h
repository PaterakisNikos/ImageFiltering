#ifndef _ARRAY
#define _ARRAY

#include <vector>

namespace math {
	template <typename T>
	class Array {
	protected:
		std::vector<T> buffer;
		unsigned int width, height;
	public:

		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }


		/*! Obtains a pointer to the internal data.
		*
		*  This is a copy of the internal image data,  so REMEMBER to delete the pointer when you don't need it anymore.
		*/
		T * getRawDataPtr() {
			size_t length = this->getWidth() * this->getHeight();
			if (length == 0) return 0;
			T * returnData = new T[length];
			for (unsigned int i = 0; i < length; i++) *(returnData + i) = buffer[i];
			return returnData;
		}

		
		void setData(const T *   data_ptr) {
			size_t size = this->width * this->height;
			if (size == 0)
				return;
			this->buffer.clear();
			for (size_t i = 0; i<size; i++) {
				buffer.push_back(*(data_ptr + i));
			}
		}

		Array() {
			width = 0;
			height = 0;
			buffer;
		}

		Array(unsigned int width, unsigned int height) {
			this->width = width;
			this->height = height;
			buffer;
		}

		Array(unsigned int width, unsigned int height, const T * data_ptr) {
			this->width = width;
			this->height = height;
			size_t length = this->width *this->height;
			buffer;
			for (size_t i = 0; i < length; i++)
				buffer.push_back(*(data_ptr+i));
		}

		Array(const  Array<T> &src) {
			this->width = src.width;
			this->height = src.height;
			this->buffer.clear();
			buffer = src.buffer;
		}

		Array & operator = (const Array<T> & right) {
			this->width = right.width;
			this->height = right.height;
			this->buffer.clear();
			this->buffer = right.buffer;
			return *(this);
		}
		

		void setElement(unsigned int x, unsigned int y, T element) {
			
			size_t index = y * this->getWidth() + x;
			//std::cout << index << endl;
			if (this->buffer.size() < index) {
				std::cout << "Your x or y it is out of bounds"<<std::endl;
				return;
			}
			this->buffer[index] = element;
		}

		T getElement(unsigned int x, unsigned int y) const {
			size_t index = y * this->getWidth() + x;
			if (this->buffer.size() <= index)
				return 0;
			return this->buffer[index];
		}

		T operator()(unsigned int x, unsigned int y) {
			return getElement(x, y);
		}


		~Array() {
			this->height = 0;
			this->width = 0;
			this->buffer.clear();
		}


	};



}

#endif