
#ifndef iAppState_hpp
	#define iAppState_hpp

	#include "Type.hpp"
	#include "ClassType.hpp"

	namespace pankey{

		namespace Base{

			template<class A, class... Args>
			class iAppState : public Type{
				public:
					iAppState(){}
					virtual ~iAppState(){}

					virtual void initialize(A& app){
						this->initializeState(app);
					}
					virtual void initializeState(A& app){}
					virtual bool hasInitialize(){return false;}
					virtual void onEnable(){}
					virtual void onDisable(){}
					virtual void update(A& a_app, Args... a_values){
						this->updateState(a_app, a_values...);
					}
					virtual void updateState(A& a_app, Args... a_values){}
					
					virtual void operator=(iAppState b){}
					virtual bool operator==(iAppState b){return false;}
					virtual bool operator!=(iAppState b){return true;}

					virtual bool istype(long a_type)const{
						return ClassType<iAppState<A,Args...>>::getId() == a_type;
					}
			};
		}
	}

#endif
