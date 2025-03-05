
#ifndef BaseAppState_hpp
	#define BaseAppState_hpp

	#include "AppState.hpp"

	#if defined(pankey_Log) && (defined(BaseAppState_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define BaseAppStateLog(status,method,mns) pankey_Log(status,"BaseAppState",method,mns)
	#else
		#define BaseAppStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class A, class... Args>
			class BaseAppState : public AppState<A,Args...>{
				public:
					BaseAppState(){}
					virtual ~BaseAppState(){}
					
					virtual void initialize(A& a_app){
						BaseAppStateLog(pankey_Log_StartMethod, "initialize", "");
						m_init = true;
						initializeState(a_app);
						initializeState();
						BaseAppStateLog(pankey_Log_EndMethod, "initialize", "");
					}
					
					virtual void initializeState(A& a_app){}
					
					virtual void initializeState(){}
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

				protected:
					bool m_enable = false;
					bool m_init = false;
					Note m_id = "";
			};

		}

	}

#endif
