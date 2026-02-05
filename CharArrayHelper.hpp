
#ifndef CharArrayHelper_hpp
	#define CharArrayHelper_hpp

	#include "ArrayPointer.hpp"
	#include "CharArray.hpp"

		namespace pankey{

			void toCharArray(Base::CharArray& a_char_array, const CharArray& a_str){
				a_char_array.clear();
				for(int x = 0; a_str.length(); x++){
					char f_chr = a_str.charAt(x);
					a_char_array.add(f_chr);
				}
			}

			Base::CharArray toCharArray(const CharArray& a_str){
				Base::CharArray i_array;
				for(int x = 0; a_str.length(); x++){
					char f_chr = a_str.charAt(x);
					i_array.add(f_chr);
				}
				return i_array;
			}
			
		}
 
#endif