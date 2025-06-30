
#ifndef TypePointerListManager_hpp
	#define TypePointerListManager_hpp

	#include "Type.hpp"
	#include "ClassType.hpp"
	#include "ArrayRawPointerList.hpp"
	#include "UpdateManager.hpp"
	#include "InvokeMethod.hpp"

	#if defined(pankey_Log) && (defined(TypePointerListManager_Log) || defined(pankey_Global_Log) || defined(pankey_ApplicationSystem_Log))
		#include "Logger_status.hpp"
		#define TypePointerListManagerLog(status,method,mns) pankey_Log(status,"TypePointerListManager",method,mns)
	#else
		#define TypePointerListManagerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class A, class... Args>
			class TypePointerListManager : virtual public UpdateManager<A,Args...>{
				public:
					TypePointerListManager(){
						TypePointerListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						TypePointerListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					TypePointerListManager(Base::InvokeMethod<Type&> a_add, Base::InvokeMethod<Type&> a_remove, Base::InvokeMethod<Type&,A&> a_initialize, Base::InvokeMethod<Type&,A&> a_update){
						TypePointerListManagerLog(pankey_Log_StartMethod, "Constructor", "");
						m_add = a_add;
						m_remove = a_remove;
						m_initialize = a_initialize;
						m_update = a_update;
						TypePointerListManagerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~TypePointerListManager(){
						TypePointerListManagerLog(pankey_Log_StartMethod, "Destructor", "");
						TypePointerListManagerLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual Type* addTypePointer(Type* a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "addTypePointer",  "");
						m_initialize_type_list.addPointer(a_type);
						TypePointerListManagerLog(pankey_Log_EndMethod, "addTypePointer", "");
						return a_type;
					}

					virtual bool containByType(long a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "containByType",  "");
						for(int x = 0; x < m_initialize_type_list.length(); x++){
							Type* f_type = m_initialize_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								continue;
							}
							if(f_type->getType() == a_type){
								return true;
							}
						}
						for(int x = 0; x < m_type_list.length(); x++){
							Type* f_type = m_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								continue;
							}
							if(f_type->getType() == a_type){
								return true;
							}
						}
						TypePointerListManagerLog(pankey_Log_EndMethod, "containByType", "");
						return false;
					}

					virtual bool containByIsType(long a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "containByIsType",  "");
						for(int x = 0; x < m_initialize_type_list.length(); x++){
							Type* f_type = m_initialize_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								continue;
							}
							if(f_type->istype(a_type)){
								return true;
							}
						}
						for(int x = 0; x < m_type_list.length(); x++){
							Type* f_type = m_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								continue;
							}
							if(f_type->istype(a_type)){
								return true;
							}
						}
						TypePointerListManagerLog(pankey_Log_EndMethod, "containByIsType", "");
						return false;
					}

					virtual bool containByTypePointer(Type* a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "containByTypePointer",  "");
						if(a_type == nullptr){
							return false;
						}
						long i_type = a_type->getType();
						TypePointerListManagerLog(pankey_Log_EndMethod, "containByTypePointer", "");
						return this->containByType(i_type);
					}

					virtual Type* getTypePointerByType(long a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "getTypePointerByType",  "");
						TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "a_type");
						TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  a_type);
						TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "m_initialize_type_list length");
						TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  m_initialize_type_list.length());
						TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "m_type_list length");
						TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  m_type_list.length());
						for(int x = 0; x < m_initialize_type_list.length(); x++){
							Type* f_type = m_initialize_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "m_initialize_type_list f_type == nullptr");
								continue;
							}
							TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "m_initialize_type_list state type:");
							TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  f_type->getType());
							if(f_type->getType() == a_type){
								TypePointerListManagerLog(pankey_Log_EndMethod, "getTypePointerByType", " m_initialize_type_listf_type->getType() == a_type");
								return f_type;
							}
						}
						for(int x = 0; x < m_type_list.length(); x++){
							Type* f_type = m_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "m_type_list f_type == nullptr");
								continue;
							}
							TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  "m_type_list state type:");
							TypePointerListManagerLog(pankey_Log_Statement, "getTypePointerByType",  f_type->getType());
							if(f_type->getType() == a_type){
								TypePointerListManagerLog(pankey_Log_EndMethod, "getTypePointerByType", "m_type_list f_type->getType() == a_type");
								return f_type;
							}
						}
						TypePointerListManagerLog(pankey_Log_EndMethod, "getTypePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual Type* removeTypePointer(Type* a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "removeTypePointer",  "");
						Type* i_type = m_initialize_type_list.removePointerByPointer(a_type);
						if(i_type == nullptr){
							i_type = m_type_list.removePointerByPointer(a_type);
						}
						if(i_type == nullptr){
							return nullptr;
						}
						invoke<Type&>(m_remove, *i_type);
						TypePointerListManagerLog(pankey_Log_EndMethod, "removeTypePointer", "");
						return i_type;
					}

					virtual Type* removeTypePointerByType(long a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "removeTypePointerByType",  "");
						TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "a_type");
						TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  a_type);
						TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "m_initialize_type_list length");
						TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  m_initialize_type_list.length());
						TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "m_type_list length");
						TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  m_type_list.length());
						for(int x = 0; x < m_initialize_type_list.length(); x++){
							Type* f_type = m_initialize_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "m_initialize_type_list f_type == nullptr");
								continue;
							}
							TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "m_initialize_type_list state type:");
							TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  f_type->getType());
							if(f_type->getType() == a_type){
								TypePointerListManagerLog(pankey_Log_EndMethod, "removeTypePointerByType", " m_initialize_type_listf_type->getType() == a_type");
								return m_initialize_type_list.removePointerByIndex(x);
							}
						}
						for(int x = 0; x < m_type_list.length(); x++){
							Type* f_type = m_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "m_type_list f_type == nullptr");
								continue;
							}
							TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  "m_type_list state type:");
							TypePointerListManagerLog(pankey_Log_Statement, "removeTypePointerByType",  f_type->getType());
							if(f_type->getType() == a_type){
								TypePointerListManagerLog(pankey_Log_EndMethod, "removeTypePointerByType", "m_type_list f_type->getType() == a_type");
								return m_type_list.removePointerByIndex(x);
							}
						}
						TypePointerListManagerLog(pankey_Log_EndMethod, "removeTypePointerByType", "return nullptr");
						return nullptr;
					}
					
					virtual bool destroyByTypePointer(Type* a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "destroyByTypePointer",  "");
						Type* i_type = this->removeTypePointer(a_type);
						if(i_type == nullptr){
							return false;
						}
						delete i_type;
						TypePointerListManagerLog(pankey_Log_EndMethod, "destroyByTypePointer", "");
						return true;
					}
					
					virtual bool destroyByType(long a_type){
						TypePointerListManagerLog(pankey_Log_StartMethod, "destroyByType",  "");
						Type* i_type = this->removeTypePointerByType(a_type);
						if(i_type == nullptr){
							return false;
						}
						delete i_type;
						TypePointerListManagerLog(pankey_Log_EndMethod, "destroyByType", "");
						return true;
					}

					virtual int TypePointer_length(){
						return m_type_list.length() + m_initialize_type_list.length();
					}

					virtual int length(){
						return m_type_list.length() + m_initialize_type_list.length();
					}
					
					virtual void clearTypePointer(){
						TypePointerListManagerLog(pankey_Log_StartMethod, "clearTypePointer",  "");
						for(int x = 0; x < m_type_list.length(); x++){
							Type* f_type = m_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								continue;
							}
							invoke<Type&>(m_remove, *f_type);
						}
						for(int x = 0; x < m_initialize_type_list.length(); x++){
							Type* f_type = m_initialize_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								continue;
							}
							invoke<Type&>(m_remove, *f_type);
						}
						m_type_list.clear();
						m_initialize_type_list.clear();
						TypePointerListManagerLog(pankey_Log_EndMethod, "clearTypePointer", "");
					}
					
					virtual void clear(){
						TypePointerListManagerLog(pankey_Log_StartMethod, "clear",  "");
						this->clearTypePointer();
						TypePointerListManagerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void initialize(A& a_app){
						TypePointerListManagerLog(pankey_Log_StartMethod, "initialize",  "");
						for(int x = 0; x < this->m_initialize_type_list.length(); x++){
							TypePointerListManagerLog(pankey_Log_StartMethod, "initialize",  "iterating through initializing states");
							TypePointerListManagerLog(pankey_Log_StartMethod, "initialize",  "iteration: ");
							TypePointerListManagerLog(pankey_Log_StartMethod, "initialize",  x);
							Type* f_type = this->m_initialize_type_list.getPointerByIndex(x);
							if(f_type == nullptr){
								TypePointerListManagerLog(pankey_Log_StartMethod, "initialize",  "initializing state is null");
								continue;
							}
							invoke<Type&,A&>(m_initialize, *f_type, a_app);
							this->m_type_list.addPointer(f_type);
						}
						TypePointerListManagerLog(pankey_Log_StartMethod, "initialize",  "m_initialize_type_list");
						this->m_initialize_type_list.reset();
						TypePointerListManagerLog(pankey_Log_EndMethod, "initialize", "");
					}

					virtual void update(A& a_app, Args... a_values){
						TypePointerListManagerLog(pankey_Log_StartMethod, "update",  "");
						
						if(!this->m_initialize_type_list.isEmpty()){
							this->initialize(a_app);
						}

						for(int x = 0; x < this->m_type_list.length(); x++){
							TypePointerListManagerLog(pankey_Log_StartMethod, "update",  "iterating through all states");
							TypePointerListManagerLog(pankey_Log_StartMethod, "update",  "iteration: ");
							TypePointerListManagerLog(pankey_Log_StartMethod, "update",  x);
							Type* f_type = this->m_type_list.getPointerByIndex(x);

							if(f_type == nullptr){
								continue;
							}

							invoke<Type&,A&>(m_update, *f_type, a_app);
						}

						TypePointerListManagerLog(pankey_Log_EndMethod, "update", "");
					}

				protected:

					Base::ArrayRawPointerList<Type> m_type_list;
					Base::ArrayRawPointerList<Type> m_initialize_type_list;
					
					Base::InvokeMethod<Type&,A&> m_initialize = nullptr;
					Base::InvokeMethod<Type&,A&> m_update = nullptr;
					
					Base::InvokeMethod<Type&> m_add = nullptr;
					Base::InvokeMethod<Type&> m_remove = nullptr;
			};

		}

	}

#endif
