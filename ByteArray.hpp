
#ifndef ByteArray_hpp
	#define ByteArray_hpp

	#include "ArrayPointer.hpp"
	#include "Byte.hpp"

	namespace pankey{

		namespace Base{

			using ByteArray = ArrayPointer<Byte>;

			template<class T>
			ByteArray serialize(const T& a_data);

			ByteArray serialize(const ArrayPointer<int>& a_data){
				if(a_data.isEmpty()){
					return ByteArray();
				}
				ByteArray i_array;
				i_array.createArrayFast(a_data.length());
				for(int x = 0; x < a_data.length(); x++){
					i_array.addFast(a_data.getFast(x));
				}
				return i_array;
			}
		}
	}

#endif
