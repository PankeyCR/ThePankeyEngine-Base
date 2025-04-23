
#ifndef State_hpp
	#define State_hpp

	#include "Type.hpp"

	#if defined(State_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
		#define StateLog(status,method,mns) pankey_Log(status,"State",method,mns)
	#else
		#define StateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class State : public Type{
			};

		}

	}

#endif
