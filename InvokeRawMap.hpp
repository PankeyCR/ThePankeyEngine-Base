
#ifndef InvokeRawMap_hpp
	#define InvokeRawMap_hpp

	#include "ArrayRawMap.hpp"
	#include "InvokeFunction.hpp"

	#if defined(pankey_Log) && (defined(InvokeRawMap_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define InvokeRawMapLog(status,method,mns) pankey_Log(status,"InvokeRawMap",method,mns)
	#else
		#define InvokeRawMapLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class K, class... Args>
			using FunctionMap = ArrayRawMap<K,InvokeFunction<Args...>>;

			template<class K, class R, class... Args>
			using FunctionReturnMap = ArrayRawMap<K,InvokeFunctionReturn<R,Args...>>;

			template<class T, class K, class... Args>
			using ClassFunctionMap = ArrayRawMap<K,InvokeClassFunction<T,Args...>>;

			template<class T, class K, class R, class... Args>
			using ClassFunctionReturnMap = ArrayRawMap<K,InvokeClassFunctionReturn<T,R,Args...>>;

			template<class K, class... Args>
			void invoke(const RawMap<K,InvokeFunction<Args...>>& a_map, K a_key, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_map.getValuePointer(a_key);
				if(i_event == nullptr){
					InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
					return;
				}
				(*i_event)(args...);
				InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class K, class... Args>
			void invokeAll(const RawMap<K,InvokeFunction<Args...>>& a_map, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_map.length(); x++){
					auto i_event = a_map.getValuePointerByIndex(x);
					if(i_event == nullptr){
						InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
						return;
					}
					(*i_event)(args...);
				}
				InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			template<class T, class K, class... Args>
			void invoke(const RawMap<K,InvokeClassFunction<T,Args...>>& a_map, T& a_instance, K a_key, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_map.getValuePointer(a_key);
				if(i_event == nullptr){
					InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
					return;
				}
				(*i_event)(a_instance, args...);
				InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class T, class K, class... Args>
			void invokeAll(const RawMap<K,InvokeClassFunction<T,Args...>>& a_map, T& a_instance, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_map.length(); x++){
					auto i_event = a_map.getValuePointerByIndex(x);
					if(i_event == nullptr){
						InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
						return;
					}
					(*i_event)(a_instance, args...);
				}
				InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			template<class K, class R, class... Args>
			R invoke(const RawMap<K,InvokeFunctionReturn<R,Args...>>& a_map, K a_key, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_map.getValuePointer(a_key);
				if(i_event == nullptr){
					InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
					return R();
				}
				InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
				return (*i_event)(args...);
			}

			template<class K, class R, class... Args>
			void invokeAll(const RawMap<K,InvokeFunctionReturn<R,Args...>>& a_map, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_map.length(); x++){
					InvokeRawMapLog(pankey_Log_Statement, "invokeAll", "loop index:");
					InvokeRawMapLog(pankey_Log_Statement, "invokeAll", x);
					auto i_event = a_map.getValuePointerByIndex(x);
					if(i_event == nullptr){
						InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
						continue;
					}
					(*i_event)(args...);
				}
				InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			template<class T, class K, class R, class... Args>
			R invoke(const RawMap<K,InvokeClassFunctionReturn<T,R,Args...>>& a_map, T& a_instance, K a_key, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_map.getValuePointer(a_key);
				if(i_event == nullptr){
					InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
					return R();
				}
				InvokeRawMapLog(pankey_Log_EndMethod, "invoke", "");
				return (*i_event)(a_instance, args...);
			}

			template<class T, class K, class R, class... Args>
			void invokeAll(const RawMap<K,InvokeClassFunctionReturn<T,R,Args...>>& a_map, T& a_instance, Args... args){
				InvokeRawMapLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_map.length(); x++){
					auto i_event = a_map.getValuePointerByIndex(x);
					if(i_event == nullptr){
						InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
						return;
					}
					(*i_event)(a_instance, args...);
				}
				InvokeRawMapLog(pankey_Log_EndMethod, "invokeAll", "");
			}

		}

	}

#endif