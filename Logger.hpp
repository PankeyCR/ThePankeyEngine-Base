
#ifndef Logger_hpp
	#define Logger_hpp

	#include "Logger_status.hpp"
	#include "InvokeMethod.hpp"
	#include "CharArray.hpp"

	namespace pankey{

		bool g_method_logger_enable = true;

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
			if(!g_method_logger_enable){
				return;
			}
			invoke<int,const CharArray&,const CharArray&,L>(Logger<L>::log, status, name, method, mns);
		}

		template<class L>
		InvokeMethod<int,const CharArray&,const CharArray&,L> Logger<L>::log;

	}

	#ifndef pankey_Log_set
		#define pankey_Log_set(S) pankey::Logger<const CharArray&>::set(S);
	#endif 

	#ifndef pankey_Log
		#define pankey_Log(status,name,method,mns) pankey::Logging<const CharArray&>(status,name,method,mns)
	#endif 

	#ifndef pankey_Logger
		#define pankey_Logger(status,name,method,mns) pankey::Logging(status,name,method,mns)
	#endif 

#endif 

