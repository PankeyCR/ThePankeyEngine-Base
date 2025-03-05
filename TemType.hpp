
#ifndef TemType_hpp
	#define TemType_hpp

	#include "Type.hpp"

	namespace pankey{

		namespace Base{

			template<class T>
			class TemType{
				public:
					TemType(){}
					virtual ~TemType(){}

					virtual long getType()const{
						return ClassCount<T>::get();
					}
			};

		}

	}

#endif
