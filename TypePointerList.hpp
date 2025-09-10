
#ifndef TypePointerList_hpp
	#define TypePointerList_hpp

	#include "ArrayRawPointerList.hpp"
	#include "InvokeMethod.hpp"
	#include "Type.hpp"

	#if defined(pankey_Log) && (defined(TypePointerList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define TypePointerListLog(status,method,mns) pankey_Log(status,"TypePointerList",method,mns)
	#else
		#define TypePointerListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			using TypePointerList = ArrayRawPointerList<Type>;

			bool containTypePointerByType(const RawPointerList<Type>& a_list, long a_type){
				TypePointerListLog(pankey_Log_StartMethod, "getTypePointerByType",  "");
				for(int x = 0; x < a_list.length(); x++){
					Type* f_type = a_list.getPointerByIndex(x);
					if(f_type == nullptr){
						TypePointerListLog(pankey_Log_Statement, "getTypePointerByType",  "f_type == nullptr");
						continue;
					}
					TypePointerListLog(pankey_Log_Statement, "getTypePointerByType",  "type:");
					TypePointerListLog(pankey_Log_Statement, "getTypePointerByType",  f_type->getType());
					if(f_type->getType() == a_type){
						TypePointerListLog(pankey_Log_EndMethod, "getTypePointerByType", "f_type->getType() == a_type");
						return true;
					}
				}
				TypePointerListLog(pankey_Log_EndMethod, "getTypePointerByType", "return nullptr");
				return false;
			}

			Type* getTypePointerByType(const RawPointerList<Type>& a_list, long a_type){
				TypePointerListLog(pankey_Log_StartMethod, "getTypePointerByType",  "");
				for(int x = 0; x < a_list.length(); x++){
					Type* f_type = a_list.getPointerByIndex(x);
					if(f_type == nullptr){
						TypePointerListLog(pankey_Log_Statement, "getTypePointerByType",  "f_type == nullptr");
						continue;
					}
					TypePointerListLog(pankey_Log_Statement, "getTypePointerByType",  "type:");
					TypePointerListLog(pankey_Log_Statement, "getTypePointerByType",  f_type->getType());
					if(f_type->getType() == a_type){
						TypePointerListLog(pankey_Log_EndMethod, "getTypePointerByType", "f_type->getType() == a_type");
						return f_type;
					}
				}
				TypePointerListLog(pankey_Log_EndMethod, "getTypePointerByType", "return nullptr");
				return nullptr;
			}

			template<class T, class... Args>
			void invoke(const RawPointerList<Type>& a_list, Base::InvokeClassMethod<T,Args...> a_method, Args... a_args){
				TypePointerListLog(pankey_Log_StartMethod, "invoke", "");
				Base::Type* f_type = getTypePointerByType(a_list, Base::ClassType<T>::getId());
				if(f_type == nullptr){
					TypePointerListLog(pankey_Log_EndMethod, "run", "f_type == nullptr");
					return;
				}
				T& i_type = f_type->cast<T>();
				Base::invoke<T,Args...>(i_type, a_method, a_args...);
				TypePointerListLog(pankey_Log_EndMethod, "invoke", "");
			}

			template<class T>
			void mutate(const RawPointerList<Type>& a_list, InvokeMethod<T&> a_method){
				TypePointerListLog(pankey_Log_StartMethod, "mutateTypePointer",  "");
				Base::Type* f_type = getTypePointerByType(a_list, Base::ClassType<T>::getId());
				if(f_type == nullptr){
					TypePointerListLog(pankey_Log_EndMethod, "run", "f_type == nullptr");
					return;
				}
				T& i_type = f_type->cast<T>();
				Base::invoke<T&>(a_method, i_type);
				TypePointerListLog(pankey_Log_EndMethod, "mutateTypePointer", "");
			}
		
		}
		
	}

#endif