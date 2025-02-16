
#ifndef InvokeMethod_hpp
	#define InvokeMethod_hpp

	#if defined(InvokeMethod_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
		#define InvokeMethodLog(status,method,mns) pankey_Log(status,"InvokeMethod",method,mns)
	#else
		#define InvokeMethodLog(status,method,mns)
	#endif

	namespace pankey{

		template<class... Args>
		using InvokeMethod = void (*)(Args...);

		template<class R, class... Args>
		using InvokeMethodReturn = R (*)(Args...);

		template<class T, class... Args>
		using InvokeClassMethod = void (T::*)(Args...);

		template<class T, class R, class... Args>
		using InvokeClassMethodReturn = R (T::*)(Args...);

		template<class... Args>
		void invoke(InvokeMethod<Args...> a_method, Args... args){
			InvokeMethodLog(pankey_Log_StartMethod, "invoke", "");
			InvokeMethodLog(pankey_Log_Statement, "invoke", "invoking as a lvalue");
			if(a_method == nullptr){
				InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
				return;
			}
			(*a_method)(args...);
			InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
		}

		template<class... Args>
		void invoke(InvokeMethod<Args...>* a_method, Args... args){
			InvokeMethodLog(pankey_Log_StartMethod, "invoke", "");
			InvokeMethodLog(pankey_Log_Statement, "invoke", "invoking as a pointer");
			if(a_method == nullptr){
				InvokeMethodLog(pankey_Log_EndMethod, "invoke", "a_method == nullptr");
				return;
			}
			(**a_method)(args...);
			InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
		}

		template<class R, class... Args>
		R invoke(InvokeMethodReturn<R,Args...> a_method, Args... args){
			InvokeMethodLog(pankey_Log_StartMethod, "invoke", "");
			InvokeMethodLog(pankey_Log_Statement, "invoke", "invoking as a lvalue, and returning value");
			if(a_method == nullptr){
				InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
				return R();
			}
			InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
			return (*a_method)(args...);
		}

		template<class R, class... Args>
		R invoke(InvokeMethodReturn<R,Args...>* a_method, Args... args){
			InvokeMethodLog(pankey_Log_StartMethod, "invoke", "");
			InvokeMethodLog(pankey_Log_Statement, "invoke", "invoking as a pointer, and returning value");
			if(a_method == nullptr){
				InvokeMethodLog(pankey_Log_EndMethod, "invoke", "a_method == nullptr");
				return R();
			}
			InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
			return (**a_method)(args...);
		}

		template<class T, class... Args>
		void invoke(T& a_instance, InvokeClassMethod<T,Args...> a_method, Args... args){
			InvokeMethodLog(pankey_Log_StartMethod, "invoke", "");
			InvokeMethodLog(pankey_Log_Statement, "invoke", "invoking class method as a lvalue");
			if(a_method == nullptr){
				InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
				return;
			}
			T* i_instance = &a_instance;
			(i_instance->*a_method)(args...);
			InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
		}

		template<class T, class R, class... Args>
		R invoke(T& a_instance, InvokeClassMethodReturn<T,R,Args...> a_method, Args... args){
			InvokeMethodLog(pankey_Log_StartMethod, "invoke", "");
			InvokeMethodLog(pankey_Log_Statement, "invoke", "invoking class method as a lvalue, and returning value");
			if(a_method == nullptr){
				InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
				return R();
			}
			T* i_instance = &a_instance;
			InvokeMethodLog(pankey_Log_EndMethod, "invoke", "");
			return (i_instance->*a_method)(args...);
		}
	}

#endif