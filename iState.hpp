
#ifndef iState_hpp
	#define iState_hpp

	#include "Type.hpp"

	#if defined(iState_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
		#define iStateLog(status,method,mns) pankey_Log(status,"iState",method,mns)
	#else
		#define iStateLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			class iState : public Type{
				public:
					iState(){
						iStateLog(pankey_Log_StartMethod, "Contructor", "");
						iStateLog(pankey_Log_EndMethod, "Contructor", "");
					}
					virtual ~iState(){
						iStateLog(pankey_Log_StartMethod, "Destructor", "");
						iStateLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual void initialize(){
						iStateLog(pankey_Log_StartMethod, "initialize", "");
						this->initializeiState();
						iStateLog(pankey_Log_EndMethod, "initialize", "");
					}
					virtual void initializeiState(){
						iStateLog(pankey_Log_StartMethod, "initializeiState", "");
						iStateLog(pankey_Log_EndMethod, "initializeiState", "");
					}
					virtual bool hasInitialize(){
						iStateLog(pankey_Log_StartMethod, "hasInitialize", "");
						iStateLog(pankey_Log_EndMethod, "hasInitialize", "");
						return false;
					}
					virtual void onEnable(){
						iStateLog(pankey_Log_StartMethod, "onEnable", "");
						iStateLog(pankey_Log_EndMethod, "onEnable", "");
					}
					virtual void onDisable(){
						iStateLog(pankey_Log_StartMethod, "onDisable", "");
						iStateLog(pankey_Log_EndMethod, "onDisable", "");
					}
					virtual void update(Args... a_values){
						iStateLog(pankey_Log_StartMethod, "update", "");
						this->updateiState(a_values...);
						iStateLog(pankey_Log_EndMethod, "update", "");
					}
					virtual void updateiState(Args... a_values){
						iStateLog(pankey_Log_StartMethod, "updateiState", "");
						iStateLog(pankey_Log_EndMethod, "updateiState", "");
					}
					
					virtual void operator=(const iState<Args...>& a_iState){
						iStateLog(pankey_Log_StartMethod, "operator=", "");
						iStateLog(pankey_Log_EndMethod, "operator=", "");
					}
					virtual bool operator==(const iState<Args...>& a_iState){
						iStateLog(pankey_Log_StartMethod, "operator==", "");
						iStateLog(pankey_Log_EndMethod, "operator==", "");
						return false;
					}
					virtual bool operator!=(const iState<Args...>& a_iState){
						iStateLog(pankey_Log_StartMethod, "operator!=", "");
						iStateLog(pankey_Log_EndMethod, "operator!=", "");
						return true;
					}

					virtual long getType()const{
						iStateLog(pankey_Log_StartMethod, "getType", "");
						iStateLog(pankey_Log_EndMethod, "getType", "");
						return ClassCount<iState<Args...>>::get();
					}

					virtual bool istype(long a_type)const{
						iStateLog(pankey_Log_StartMethod, "istypeof", "");
						iStateLog(pankey_Log_EndMethod, "istypeof", "");
						return ClassCount<iState<Args...>>::get() == a_type;
					}
					
				protected:
			};

		}

	}

#endif
