
#ifndef InvokeFunction_hpp
	#define InvokeFunction_hpp

	#if defined(pankey_Log) && (defined(InvokeFunction_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
		#define InvokeFunctionLog(status,method,mns) pankey_Log(status,"InvokeFunction",method,mns)
	#else
		#define InvokeFunctionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class MethodType>
			struct FunctionWrapper;

			template<class... Args>
			struct FunctionWrapper<void(Args...)>{
				using WrapperFunction = void (*)(Args...);

				WrapperFunction m_function;
				
				FunctionWrapper() : m_function(nullptr){}
				FunctionWrapper(WrapperFunction a_function) : m_function(a_function){}

				void operator()(Args... a_args) const{
					InvokeFunctionLog(pankey_Log_StartMethod, "Function<void(Args...)>", "");
					if(m_function == nullptr){
						InvokeFunctionLog(pankey_Log_EndMethod, "Function<void(Args...)>", "");
						return;
					}
					m_function(a_args...);
					InvokeFunctionLog(pankey_Log_EndMethod, "Function<void(Args...)>", "");
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const FunctionWrapper<void(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const FunctionWrapper<void(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class ReturnType, class... Args>
			struct FunctionWrapper<ReturnType(Args...)>{
				using WrapperFunction = ReturnType (*)(Args...);

				WrapperFunction m_function;
				
				FunctionWrapper() : m_function(nullptr){}
				FunctionWrapper(WrapperFunction a_function) : m_function(a_function){}

				ReturnType operator()(Args... a_args) const{
					InvokeFunctionLog(pankey_Log_StartMethod, "Function<ReturnType(Args...)>", "");
					if(m_function == nullptr){
						InvokeFunctionLog(pankey_Log_EndMethod, "Function<ReturnType(Args...)>", "");
						return ReturnType();
					}
					InvokeFunctionLog(pankey_Log_EndMethod, "Function<ReturnType(Args...)>", "");
					return m_function(a_args...);
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const FunctionWrapper<ReturnType(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const FunctionWrapper<ReturnType(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class ClassType, class... Args>
			struct FunctionWrapper<void(ClassType::*)(Args...)>{
				using WrapperFunction = void (ClassType::*)(Args...);

				WrapperFunction m_function;
				
				FunctionWrapper() : m_function(nullptr){}
				FunctionWrapper(WrapperFunction a_function) : m_function(a_function){}

				void operator()(ClassType& a_instance, Args... a_args) const{
					InvokeFunctionLog(pankey_Log_StartMethod, "Function<void(ClassType::*)(Args...)>", "");
					if(m_function == nullptr){
						InvokeFunctionLog(pankey_Log_EndMethod, "Function<void(ClassType::*)(Args...)>", "");
						return;
					}
					ClassType* i_instance = &a_instance;
					(i_instance->*m_function)(a_args...);
					InvokeFunctionLog(pankey_Log_EndMethod, "Function<void(ClassType::*)(Args...)>", "");
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const FunctionWrapper<void(ClassType::*)(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const FunctionWrapper<void(ClassType::*)(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class ClassType, class ReturnType, class... Args>
			struct FunctionWrapper<ReturnType(ClassType::*)(Args...)>{
				using WrapperFunction = ReturnType (ClassType::*)(Args...);

				WrapperFunction m_function;
				
				FunctionWrapper() : m_function(nullptr){}
				FunctionWrapper(WrapperFunction a_function) : m_function(a_function){}

				ReturnType operator()(Args... a_args) const{
					return m_function(a_args...);
				}

				ReturnType operator()(ClassType& a_instance, Args... a_args) const{
					InvokeFunctionLog(pankey_Log_StartMethod, "Function<ReturnType(ClassType::*)(Args...)>", "");
					if(m_function == nullptr){
						InvokeFunctionLog(pankey_Log_EndMethod, "Function<ReturnType(ClassType::*)(Args...)>", "");
						return ReturnType();
					}
					ClassType* i_instance = &a_instance;
					InvokeFunctionLog(pankey_Log_EndMethod, "Function<ReturnType(ClassType::*)(Args...)>", "");
					return (i_instance->*m_function)(a_args...);
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const FunctionWrapper<ReturnType(ClassType::*)(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const FunctionWrapper<ReturnType(ClassType::*)(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class... Args>
			using InvokeFunction = FunctionWrapper<void(Args...)>;

			template<class R, class... Args>
			using InvokeFunctionReturn = FunctionWrapper<R(Args...)>;

			template<class T, class... Args>
			using InvokeClassFunction = FunctionWrapper<void (T::*)(Args...)>;

			template<class T, class R, class... Args>
			using InvokeClassFunctionReturn = FunctionWrapper<R (T::*)(Args...)>;

		}
		
	}

#endif