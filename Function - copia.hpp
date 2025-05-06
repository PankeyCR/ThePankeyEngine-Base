
#ifndef Function_hpp
	#define Function_hpp

	#if defined(pankey_Log) && (defined(Function_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
	#include "Logger_status.hpp"
		#define FunctionLog(status,method,mns) pankey_Log(status,"Function",method,mns)
	#else
		#define FunctionLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class MethodType>
			struct Function;

			template<class... Args>
			struct Function<void(Args...)>{
				using WrapperFunction = void (*)(Args...);

				WrapperFunction m_function;
				
				Function() : m_function(nullptr){}
				Function(WrapperFunction a_function) : m_function(a_function){}

				void operator()(Args... a_args) const{
					FunctionLog(pankey_Log_StartMethod, "Function<void(Args...)>", "");
					if(m_function == nullptr){
						FunctionLog(pankey_Log_EndMethod, "Function<void(Args...)>", "");
						return;
					}
					m_function(a_args...);
					FunctionLog(pankey_Log_EndMethod, "Function<void(Args...)>", "");
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const Function<void(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const Function<void(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class ReturnType, class... Args>
			struct Function<ReturnType(Args...)>{
				using WrapperFunction = ReturnType (*)(Args...);

				WrapperFunction m_function;
				
				Function() : m_function(nullptr){}
				Function(WrapperFunction a_function) : m_function(a_function){}

				ReturnType operator()(Args... a_args) const{
					FunctionLog(pankey_Log_StartMethod, "Function<ReturnType(Args...)>", "");
					if(m_function == nullptr){
						FunctionLog(pankey_Log_EndMethod, "Function<ReturnType(Args...)>", "");
						return ReturnType();
					}
					FunctionLog(pankey_Log_EndMethod, "Function<ReturnType(Args...)>", "");
					return m_function(a_args...);
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const Function<ReturnType(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const Function<ReturnType(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class ClassType, class... Args>
			struct Function<void(ClassType::*)(Args...)>{
				using WrapperFunction = void (ClassType::*)(Args...);

				WrapperFunction m_function;
				
				Function() : m_function(nullptr){}
				Function(WrapperFunction a_function) : m_function(a_function){}

				void operator()(ClassType& a_instance, Args... a_args) const{
					FunctionLog(pankey_Log_StartMethod, "Function<void(ClassType::*)(Args...)>", "");
					if(m_function == nullptr){
						FunctionLog(pankey_Log_EndMethod, "Function<void(ClassType::*)(Args...)>", "");
						return;
					}
					ClassType* i_instance = &a_instance;
					(i_instance->*m_function)(a_args...);
					FunctionLog(pankey_Log_EndMethod, "Function<void(ClassType::*)(Args...)>", "");
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const Function<void(ClassType::*)(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const Function<void(ClassType::*)(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

			template<class ClassType, class ReturnType, class... Args>
			struct Function<ReturnType(ClassType::*)(Args...)>{
				using WrapperFunction = ReturnType (ClassType::*)(Args...);

				WrapperFunction m_function;
				
				Function() : m_function(nullptr){}
				Function(WrapperFunction a_function) : m_function(a_function){}

				ReturnType operator()(Args... a_args) const{
					return m_function(a_args...);
				}

				ReturnType operator()(ClassType& a_instance, Args... a_args) const{
					FunctionLog(pankey_Log_StartMethod, "Function<ReturnType(ClassType::*)(Args...)>", "");
					if(m_function == nullptr){
						FunctionLog(pankey_Log_EndMethod, "Function<ReturnType(ClassType::*)(Args...)>", "");
						return ReturnType();
					}
					ClassType* i_instance = &a_instance;
					FunctionLog(pankey_Log_EndMethod, "Function<ReturnType(ClassType::*)(Args...)>", "");
					return (i_instance->*m_function)(a_args...);
				}

				void operator=(WrapperFunction a_function){
					m_function = a_function;
				}

				bool operator==(const Function<ReturnType(ClassType::*)(Args...)>& a_invoker){
					return m_function == a_invoker.m_function;
				}

				bool operator!=(const Function<ReturnType(ClassType::*)(Args...)>& a_invoker){
					return m_function != a_invoker.m_function;
				}
			};

		}
		
	}

#endif