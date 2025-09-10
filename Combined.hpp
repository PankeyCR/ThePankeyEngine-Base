
#ifndef Combined_hpp
	#define Combined_hpp

	namespace pankey{

		namespace Base{

			template<class... Bases>
			struct Combined : public Bases...{};

		}

	}

#endif
