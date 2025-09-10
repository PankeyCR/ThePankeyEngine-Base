
#ifndef CombinedInstance_hpp
	#define CombinedInstance_hpp

	#include "CombinedMutate.hpp"

	namespace pankey{

		namespace Base{

			template<class... Bases>
			struct CombinedInstance : public CombinedMutate<Bases>...{};

		}

	}

#endif
