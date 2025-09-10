
#ifndef ArrayPointerHelper_hpp
	#define ArrayPointerHelper_hpp

	#include "ArrayPointer.hpp"

	#if defined(pankey_Log) && (defined(ArrayPointerHelper_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayPointerHelperLog(status,method,mns) pankey_Log(status,"ArrayPointerHelper",method,mns)
	#else
		#define ArrayPointerHelperLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			int getLengthUntil(const ArrayPointer<T>& a_array, T a_end){
				ArrayPointerHelperLog(pankey_Log_StartMethod, "getLengthUntil", "");
				for(int x = 0; x < a_array.length(); x++){
					T f_value = a_array.getFast(x);
					if(f_value == a_end){
						return x;
					}
				}
				ArrayPointerHelperLog(pankey_Log_EndMethod, "getLengthUntil", "");
				return -1;
			}

		}

	}

#endif



