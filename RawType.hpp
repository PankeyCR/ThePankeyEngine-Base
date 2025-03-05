
#ifndef RawType_hpp
	#define RawType_hpp

	#include "Type.hpp"

	namespace pankey{

		namespace Base{

			class RawType : public Type{
				public:
					RawType(){}
					RawType(long a_type){
						m_type = a_type;
					}
					virtual ~RawType(){}

					virtual void setType(long a_type){
						m_type = a_type;
					}

					virtual long getType(){
						return m_type;
					}
				protected:
					long m_type = -1;
			};

		}

	}

#endif
