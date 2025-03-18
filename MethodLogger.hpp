
#ifndef MethodLogger_hpp
	#define MethodLogger_hpp

	#include "Logger_status.hpp"
	#include "InvokeMethod.hpp"
	#include "CharArray.hpp"

	namespace pankey{

		namespace Base{

			bool g_method_logger_enable = true;

			#ifndef pankey_Log_enable
				#define pankey_Log_enable(status,name,method,mns) g_method_logger_enable
			#endif

			template<class L>
			struct Logger
			{
				static InvokeMethod<int,const CharArray&,const CharArray&, L> log;

				static void set(InvokeMethod<int,const CharArray&,const CharArray&,L> a_log){
					log = a_log;
				}
			};
			
				
			template<class L>
			void Logging(int status, const CharArray& name, const CharArray& method, L mns){
				if(!pankey_Log_enable(status,name,method,mns)){
					return;
				}
				invoke<int,const CharArray&,const CharArray&,L>(Logger<L>::log, status, name, method, mns);
			}

			template<class L>
			InvokeMethod<int,const CharArray&,const CharArray&,L> Logger<L>::log;

			void LoggingStartPrint_(){
				g_method_logger_enable = true;
			}
		
			void LoggingStopPrint_(){
				g_method_logger_enable = false;
			}

		}

	}

	#ifndef pankey_Log_set
		#define pankey_Log_set(S) pankey::Base::Logger<const CharArray&>::set(S);
	#endif 

	#ifndef pankey_Log_Split
		#define pankey_Log_Split(tittle) 
	#endif
	
	#ifndef pankey_Log_Start
		#define pankey_Log_Start pankey::Base::LoggingStartPrint_
	#endif
	
	#ifndef pankey_Log_Stop
		#define pankey_Log_Stop pankey::Base::LoggingStopPrint_
	#endif 

	#ifndef pankey_Log
		#define pankey_Log(status,name,method,mns) pankey::Base::Logging<const pankey::Base::CharArray&>(status,name,method,mns)
	#endif 

	#ifndef pankey_Logger
		#define pankey_Logger(status,name,method,mns) pankey::Base::Logging(status,name,method,mns)
	#endif

#endif 

