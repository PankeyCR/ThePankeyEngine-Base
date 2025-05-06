
#ifndef BaseIState_hpp
	#define BaseIState_hpp

	#include "iState.hpp"

	#if defined(pankey_Log) && (defined(BaseIState_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define BaseIStateLog(status,method,mns) pankey_Log(status,"BaseAppState",method,mns)
	#else
		#define BaseIStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class BaseIState : public iState<Args...>{
				public:
					BaseIState(){
						BaseIStateLog(pankey_Log_StartMethod, "Contructor", "");
						BaseIStateLog(pankey_Log_EndMethod, "Contructor", "");
					}
					virtual ~BaseIState(){
						BaseIStateLog(pankey_Log_StartMethod, "Destructor", "");
						BaseIStateLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void initialize(){
						BaseIStateLog(pankey_Log_StartMethod, "initialize", "");
						m_init = true;
						initializeState();
						BaseIStateLog(pankey_Log_EndMethod, "initialize", "");
					}
					
					virtual void initializeState(){
						BaseIStateLog(pankey_Log_StartMethod, "initializeState", "");
						BaseIStateLog(pankey_Log_EndMethod, "initializeState", "");
					}
					virtual bool hasInitialize(){
						BaseIStateLog(pankey_Log_StartMethod, "initializeState", "");
						BaseIStateLog(pankey_Log_EndMethod, "initializeState", "");
						return m_init;
					}
					
					virtual void onEnable(){
						BaseIStateLog(pankey_Log_StartMethod, "onEnable", "");
						m_enable = true;
						BaseIStateLog(pankey_Log_EndMethod, "onEnable", "");
					}
					virtual void onDisable(){
						BaseIStateLog(pankey_Log_StartMethod, "onDisable", "");
						m_enable = false;
						BaseIStateLog(pankey_Log_EndMethod, "onDisable", "");
					}
					
					virtual bool isEnable(){
						BaseIStateLog(pankey_Log_StartMethod, "isEnable", "");
						BaseIStateLog(pankey_Log_EndMethod, "isEnable", "");
						return m_enable;
					}
					
					
					virtual void update( Args... a_values){
						BaseIStateLog(pankey_Log_StartMethod, "update", "");
						if(!m_enable){
							BaseIStateLog(pankey_Log_EndMethod, "update", "!m_enable");
							return;
						}
						updateState(a_values...);
						BaseIStateLog(pankey_Log_EndMethod, "update", "");
					}
					
					virtual void updateState(Args... a_values){
						BaseIStateLog(pankey_Log_StartMethod, "updateState", "");
						BaseIStateLog(pankey_Log_EndMethod, "updateState", "");
					}

				protected:
					bool m_enable = false;
					bool m_init = false;
			};

		}

	}

#endif
