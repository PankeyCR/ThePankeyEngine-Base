
#ifndef InvokeRawList_hpp
	#define InvokeRawList_hpp

	#include "ArrayRawList.hpp"
	#include "InvokeMethod.hpp"

	#if defined(pankey_Log) && (defined(InvokeRawList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define InvokeRawListLog(status,method,mns) pankey_Log(status,"InvokeRawList",method,mns)
	#else
		#define InvokeRawListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class... Args>
			using MethodList = ArrayRawList<InvokeMethod<Args...>>;

			template<class R, class... Args>
			using MethodReturnList = ArrayRawList<InvokeMethodReturn<R,Args...>>;

			template<class T, class... Args>
			using ClassMethodList = ArrayRawList<InvokeClassMethod<T,Args...>>;

			template<class T, class R, class... Args>
			using ClassMethodReturnList = ArrayRawList<InvokeClassMethodReturn<T,R,Args...>>;

			template<class... Args>
			void invoke(const RawList<InvokeMethod<Args...>>& a_list, int a_index, Args... args){
				InvokeRawListLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_list.getPointerByIndex(a_index);
				invoke<Args...>(i_event, args...);
				InvokeRawListLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class... Args>
			void invokeAll(const RawList<InvokeMethod<Args...>>& a_list, Args... args){
				InvokeRawListLog(pankey_Log_StartMethod, "invokeAll", "");
				InvokeRawListLog(pankey_Log_Statement, "invokeAll", "list last index:");
				InvokeRawListLog(pankey_Log_Statement, "invokeAll", a_list.length());
				for(int x = 0; x < a_list.length(); x++){
					InvokeRawListLog(pankey_Log_Statement, "invokeAll", "iteration:");
					InvokeRawListLog(pankey_Log_Statement, "invokeAll", x);
					auto i_event = a_list.getPointerByIndex(x);
					invoke<Args...>(i_event, args...);
				}
				InvokeRawListLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			// template<class... Args>
			// void invokeAll(RawList<int>& a_deletes, RawList<InvokeMethod<Args...>>& a_list, Args... args){
			// 	InvokeRawListLog(pankey_Log_StartMethod, "invokeAll", "");
			// 	InvokeRawListLog(pankey_Log_Statement, "invokeAll", "list initial index:");
			// 	InvokeRawListLog(pankey_Log_Statement, "invokeAll", a_list.length());
			// 	for(int x = 0; x < a_list.length(); x++){
			// 		InvokeRawListLog(pankey_Log_Statement, "invokeAll", "a_list iteration:");
			// 		InvokeRawListLog(pankey_Log_Statement, "invokeAll", x);
			// 		auto i_event = a_list.getPointerByIndex(x);
			// 		invoke<Args...>(i_event, args...);
			// 		int f_last_index = x;
			// 		InvokeRawListLog(pankey_Log_Statement, "invokeAll", "total deletes:");
			// 		InvokeRawListLog(pankey_Log_Statement, "invokeAll", a_deletes.length());
			// 		for(int d = 0; d < a_deletes.length(); d++){
			// 			InvokeRawListLog(pankey_Log_Statement, "invokeAll", "a_deletes iteration:");
			// 			InvokeRawListLog(pankey_Log_Statement, "invokeAll", d);
			// 			int f_index = a_deletes.getValueByIndex(d);
			// 			InvokeRawListLog(pankey_Log_Statement, "invokeAll", "delete index:");
			// 			InvokeRawListLog(pankey_Log_Statement, "invokeAll", f_index);
			// 			if(f_index <= f_last_index && f_index >= 0){
			// 				x--;
			// 				InvokeRawListLog(pankey_Log_Statement, "invokeAll", "new list iteration index:");
			// 				InvokeRawListLog(pankey_Log_Statement, "invokeAll", x);
			// 			}
			// 		}
			// 		a_deletes.clear();
			// 	}
			// 	InvokeRawListLog(pankey_Log_Statement, "invokeAll", "list final index:");
			// 	InvokeRawListLog(pankey_Log_Statement, "invokeAll", a_list.length());
			// 	InvokeRawListLog(pankey_Log_EndMethod, "invokeAll", "");
			// }

			template<class T, class... Args>
			void invoke(const RawList<InvokeClassMethod<T,Args...>>& a_list, T& a_instance, int a_index, Args... args){
				InvokeRawListLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_list.getPointerByIndex(a_index);
				invoke<T,Args...>(a_instance, *i_event, args...);
				InvokeRawListLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class T, class... Args>
			void invokeAll(const RawList<InvokeClassMethod<T,Args...>>& a_list, T& a_instance, Args... args){
				InvokeRawListLog(pankey_Log_StartMethod, "invokeAll", "");
				for(int x = 0; x < a_list.length(); x++){
					auto i_event = a_list.getPointerByIndex(x);
					invoke<T,Args...>(a_instance, *i_event, args...);
				}
				InvokeRawListLog(pankey_Log_EndMethod, "invokeAll", "");
			}

			template<class R, class... Args>
			R invoke(const RawList<InvokeMethodReturn<R,Args...>>& a_list, int a_index, Args... args){
				InvokeRawListLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_list.getPointerByIndex(a_index);
				InvokeRawListLog(pankey_Log_EndMethod, "invoke", "");
				return invoke<R,Args...>(i_event, args...);
			}

			template<class T, class R, class... Args>
			R invoke(const RawList<InvokeClassMethodReturn<T,R,Args...>>& a_list, T& a_instance, int a_index, Args... args){
				InvokeRawListLog(pankey_Log_StartMethod, "invoke", "");
				auto i_event = a_list.getPointerByIndex(a_index);
				InvokeRawListLog(pankey_Log_EndMethod, "invoke", "");
				return invoke<T,R,Args...>(a_instance, *i_event, args...);
			}
		
		}
		
	}

#endif