
#ifndef State_hpp
	#define State_hpp

	#if defined(State_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
		#define StateLog(status,method,mns) pankey_Log(status,"State",method,mns)
	#else
		#define StateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class State{
				public:
					State(){
						StateLog(pankey_Log_StartMethod, "Contructor", "");
						StateLog(pankey_Log_EndMethod, "Contructor", "");
					}
					virtual ~State(){
						StateLog(pankey_Log_StartMethod, "Destructor", "");
						StateLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void initialize(){
						StateLog(pankey_Log_StartMethod, "initialize", "");
						this->initializeState();
						StateLog(pankey_Log_EndMethod, "initialize", "");
					}
					virtual void initializeState(){
						StateLog(pankey_Log_StartMethod, "initializeState", "");
						StateLog(pankey_Log_EndMethod, "initializeState", "");
					}
					virtual bool hasInitialize(){
						StateLog(pankey_Log_StartMethod, "hasInitialize", "");
						StateLog(pankey_Log_EndMethod, "hasInitialize", "");
						return false;
					}
					virtual void onEnable(){
						StateLog(pankey_Log_StartMethod, "onEnable", "");
						StateLog(pankey_Log_EndMethod, "onEnable", "");
					}
					virtual void onDisable(){
						StateLog(pankey_Log_StartMethod, "onDisable", "");
						StateLog(pankey_Log_EndMethod, "onDisable", "");
					}
					virtual void update(Args... a_values){
						StateLog(pankey_Log_StartMethod, "update", "");
						this->updateState(a_values...);
						StateLog(pankey_Log_EndMethod, "update", "");
					}
					virtual void updateState(Args... a_values){
						StateLog(pankey_Log_StartMethod, "updateState", "");
						StateLog(pankey_Log_EndMethod, "updateState", "");
					}
					
					virtual void operator=(const State<Args...>& a_state){
						StateLog(pankey_Log_StartMethod, "operator=", "");
						StateLog(pankey_Log_EndMethod, "operator=", "");
					}
					virtual bool operator==(const State<Args...>& a_state){
						StateLog(pankey_Log_StartMethod, "operator==", "");
						StateLog(pankey_Log_EndMethod, "operator==", "");
						return false;
					}
					virtual bool operator!=(const State<Args...>& a_state){
						StateLog(pankey_Log_StartMethod, "operator!=", "");
						StateLog(pankey_Log_EndMethod, "operator!=", "");
						return true;
					}
					
				protected:
			};

		}

	}

#endif
