
#ifndef UpdateManager_hpp
	#define UpdateManager_hpp

	namespace pankey{

		namespace Base{

			template<class A, class... Args>
			class UpdateManager{
				public:
					virtual ~UpdateManager(){}
					
					virtual int length()=0;
					
					virtual void clear()=0;

					virtual void initialize(A& a_app){}
					
					virtual void update(A& a_app, Args... a_update)=0;
			};

		}

	}

#endif
