
#ifndef BaseIAppState_hpp
	#define BaseIAppState_hpp

	#include "iAppState.hpp"

	#if defined(pankey_Log) && (defined(BaseIAppState_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define BaseIAppStateLog(status,method,mns) pankey_Log(status,"BaseIAppState",method,mns)
	#else
		#define BaseIAppStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class A, class... Args>
			class BaseIAppState : public iAppState<A,Args...>{
				public:
					BaseIAppState(){}
					virtual ~BaseIAppState(){}
					
					virtual void initialize(A& a_app){
						BaseIAppStateLog(pankey_Log_StartMethod, "initialize", "");
						m_init = true;
						initializeState(a_app);
						BaseIAppStateLog(pankey_Log_EndMethod, "initialize", "");
					}
					
					virtual void initializeState(A& a_app){}
					
					virtual bool hasInitialize(){return m_init;}
					
					virtual void onEnable(){m_enable = true;}
					virtual void onDisable(){m_enable = false;}
					
					virtual bool isEnable(){return m_enable;}
					
					
					virtual void update(A& a_app, Args... a_values){
						if(!m_enable){
							return;
						}
						updateState(a_app, a_values...);
					}
					
					virtual void updateState(A& a_app, Args... a_values){}

					virtual long getType()const{
						return ClassCount<BaseIAppState<A,Args...>>::get();
					}

					virtual bool istype(long a_type)const{
						return iAppState<A,Args...>::istype(a_type) || ClassCount<BaseIAppState<A,Args...>>::get() == a_type;
					}

				protected:
					bool m_enable = false;
					bool m_init = false;
			};

		}

	}

#endif
