
#ifndef CommandReturn_hpp
	#define CommandReturn_hpp

	namespace pankey{

		namespace Base{

			template<class R, class... Args>
			class CommandReturn{
				public:
					virtual ~CommandReturn(){}
					virtual R execute(Args... args)=0;
			};

		}

	}

#endif