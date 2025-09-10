
#ifndef CombinedMutate_hpp
	#define CombinedMutate_hpp

	#include "InvokeMethod.hpp"

	namespace pankey{

		namespace Base{

			template<class T>
			class CombinedMutate{
				public:
					void mutate(InvokeMethod<T&> a_method){
						invoke<T&>(a_method, m_intance);
					}
				protected:
					T m_intance;
			};

		}

	}

#endif
