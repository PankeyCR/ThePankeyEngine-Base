
#ifndef BaseState_hpp
	#define BaseState_hpp

	#include "State.hpp"

	#if defined(pankey_Log) && (defined(BaseState_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define BaseStateLog(status,method,mns) pankey_Log(status,"BaseAppState",method,mns)
	#else
		#define BaseStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class BaseState : public State<Args...>{
				public:
					BaseState(){
						BaseStateLog(pankey_Log_StartMethod, "Contructor", "");
						BaseStateLog(pankey_Log_EndMethod, "Contructor", "");
					}
					virtual ~BaseState(){
						BaseStateLog(pankey_Log_StartMethod, "Destructor", "");
						BaseStateLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void initialize(){
						BaseStateLog(pankey_Log_StartMethod, "initialize", "");
						m_init = true;
						initializeState();
						BaseStateLog(pankey_Log_EndMethod, "initialize", "");
					}
					
					virtual void initializeState(){
						BaseStateLog(pankey_Log_StartMethod, "initializeState", "");
						BaseStateLog(pankey_Log_EndMethod, "initializeState", "");
					}
					virtual bool hasInitialize(){
						BaseStateLog(pankey_Log_StartMethod, "initializeState", "");
						BaseStateLog(pankey_Log_EndMethod, "initializeState", "");
						return m_init;
					}
					
					virtual void onEnable(){
						BaseStateLog(pankey_Log_StartMethod, "onEnable", "");
						m_enable = true;
						BaseStateLog(pankey_Log_EndMethod, "onEnable", "");
					}
					virtual void onDisable(){
						BaseStateLog(pankey_Log_StartMethod, "onDisable", "");
						m_enable = false;
						BaseStateLog(pankey_Log_EndMethod, "onDisable", "");
					}
					
					virtual bool isEnable(){
						BaseStateLog(pankey_Log_StartMethod, "isEnable", "");
						BaseStateLog(pankey_Log_EndMethod, "isEnable", "");
						return m_enable;
					}
					
					
					virtual void update( Args... a_values){
						BaseStateLog(pankey_Log_StartMethod, "update", "");
						if(!m_enable){
							BaseStateLog(pankey_Log_EndMethod, "update", "!m_enable");
							return;
						}
						updateState(a_values...);
						BaseStateLog(pankey_Log_EndMethod, "update", "");
					}
					
					virtual void updateState(Args... a_values){
						BaseStateLog(pankey_Log_StartMethod, "updateState", "");
						BaseStateLog(pankey_Log_EndMethod, "updateState", "");
					}

				protected:
					bool m_enable = false;
					bool m_init = false;
			};

		}

	}

#endif
