
#ifndef ClassType_hpp
	#define ClassType_hpp

	#include "ClassCount.hpp"

	namespace pankey{

		namespace Base{
				
			template<class cls>
			struct ClassType{
				static long m_value;

				static long getId(){
					if(m_value != -1){
						return m_value;
					}
					return ClassCount<cls>::get();
					// return 0;
				}
				static void setId(long a_value){m_value = a_value;}
			};

			template<class cls> long ClassType<cls>::m_value = -1;

		}

	}

#endif