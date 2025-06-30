
#ifndef Command_hpp
	#define Command_hpp

	#include "Type.hpp"
	#include "ClassType.hpp"

	namespace pankey{

		namespace Base{

			template<class... Args>
			class Command : public Type{
				public:
					virtual ~Command(){}
					virtual void execute(Args... args)=0;

					virtual bool istype(long a_type)const{
						return ClassType<Command<Args...>>::getId() == a_type;
					}
			};

		}

	}

#endif