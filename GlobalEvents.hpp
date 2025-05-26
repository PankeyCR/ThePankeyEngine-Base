
#ifndef GlobalEvents_hpp
	#define GlobalEvents_hpp

	#include "InvokeRawMap.hpp"

	#if defined(pankey_Log) && (defined(GlobalEvents_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define GlobalEventsLog(status,method,mns) pankey_Log(status,"GlobalEvents",method,mns)
	#else
		#define GlobalEventsLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class K, class... Args>
			struct GlobalEvents{
				static FunctionMap<K,Args...> g_global_events;

				static void put(K a_key, InvokeMethod<Args...> a_method){
					g_global_events.put(a_key, a_method);
				}

				static void change(K a_key, InvokeMethod<Args...> a_method){
					g_global_events.destroy(a_key);
					g_global_events.add(a_key, a_method);
				}

				static void remove(K a_key){
					g_global_events.removeUpdateFunctionMap(a_key);
				}

				static void clear(){
					g_global_events.clear();
				}

				static void run(K a_key, Args... a_parameters){
					invoke<K,Args...>(g_global_events, a_key, a_parameters...);
				}

				static void runAll(Args... a_parameters){
					invokeAll<K,Args...>(g_global_events, a_parameters...);
				}
			};

			template<class K, class... Args> FunctionMap<K,Args...> GlobalEvents<K,Args...>::g_global_events;

		}

	}

#endif
