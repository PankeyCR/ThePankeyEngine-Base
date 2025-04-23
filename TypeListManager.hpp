
#ifndef TypeListManager_hpp
	#define TypeListManager_hpp

	#include "TypePointerListManager.hpp"

	#if defined(pankey_Log) && (defined(TypeListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define TypeListManagerLog(status,method,mns) pankey_Log(status,"TypeListManager",method,mns)
	#else
		#define TypeListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class A, class... Args>
			class TypeListManager : virtual public TypePointerListManager<A,Args...>{
				public:
					TypeListManager(){
						TypeListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						TypeListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					TypeListManager(Base::InvokeMethod<Type&> a_add, Base::InvokeMethod<Type&> a_remove, Base::InvokeMethod<Type&,A&> a_initialize, Base::InvokeMethod<Type&,A&> a_update) : TypePointerListManager<A,Args...>(a_add, a_remove, a_initialize, a_update){
						TypeListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						TypeListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~TypeListManager(){
						TypeListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						TypeListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					template<class AS>
					AS& addType(){
						TypeListManagerLog(pankey_Log_StartMethod, "addType",  "");
						TypeListManagerLog(pankey_Log_EndMethod, "addType", "");
						return *(AS*)this->addTypePointer(new AS());
					}

					template<class AS>
					bool containType(){
						TypeListManagerLog(pankey_Log_StartMethod, "containType",  "");
						long i_type = Base::ClassCount<AS>::get();
						TypeListManagerLog(pankey_Log_EndMethod, "containType", "");
						return this->containByType(i_type);
					}

					template<class AS>
					bool containIsType(){
						TypeListManagerLog(pankey_Log_StartMethod, "containType",  "");
						long i_type = Base::ClassCount<AS>::get();
						TypeListManagerLog(pankey_Log_EndMethod, "containType", "");
						return this->containByIsType(i_type);
					}

					template<class AS>
					void putType(){
						TypeListManagerLog(pankey_Log_StartMethod, "putType",  "");
						if(this->containByType(Base::ClassCount<AS>::get())){
							return;
						}
						this->addTypePointer(new AS());
						TypeListManagerLog(pankey_Log_EndMethod, "putType", "");
					}

					template<class AS, class... MArgs>
					void runTypeMethod(Base::InvokeClassMethod<AS,MArgs...> a_method, MArgs... a_args){
						TypeListManagerLog(pankey_Log_StartMethod, "run",  "");
						Base::Type* f_type = this->getTypePointerByType(Base::ClassCount<AS>::get());
						if(f_type == nullptr){
							TypeListManagerLog(pankey_Log_EndMethod, "run", "f_type == nullptr");
							return;
						}
						AS& i_type = f_type->cast<AS>();
						Base::invoke<AS,MArgs...>(i_type, a_method, a_args...);
						TypeListManagerLog(pankey_Log_EndMethod, "run", "");
					}
			};

		}

	}

#endif
