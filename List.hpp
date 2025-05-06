
#ifndef List_hpp
	#define List_hpp

	#include "RawPointerList.hpp"

	#if defined(pankey_Log) && (defined(List_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ListLog(status,method,mns) pankey_Log(status,"List",method,mns)
	#else
		#define ListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template <class T>
			class List : virtual protected RawPointerList<T>{	
				public:
					virtual ~List(){}

					using RawPointerList<T>::addPack;
					using RawPointerList<T>::addWithParameters;

					virtual void addCopy(List<T>& a_list){
						ListLog(pankey_Log_StartMethod, "addCopy", "");
                        for(int x = 0; x < a_list.length(); x++){
                            T* f_value = a_list.getPointerByIndex(x);
                            this->add(*f_value);
                        }
						ListLog(pankey_Log_EndMethod, "addCopy", "");
					}

					// virtual T* add(T a_value)=0;
					
					// virtual T* set(int a_index, T a_value)=0;
					
					// virtual T* insert(int a_index, T a_value)=0;
					
					// virtual T* getPointer(T a_value)=0;
					
					// virtual T& getReference(T a_value)=0;
					
					// virtual T& getReferenceByIndex(int x)const{
					// 	ListLog(pankey_Log_StartMethod, "getReferenceByIndex", "");
					// 	ListLog(pankey_Log_EndMethod, "getReferenceByIndex", "");
					// 	return *this->getPointerByIndex(x);
					// }
					
					// virtual T getByIndex(int x)const{
					// 	ListLog(pankey_Log_StartMethod, "getByIndex", "");
					// 	T* i_pointer = this->getPointerByIndex(x);
					// 	if(i_pointer == nullptr){
					// 		return T();
					// 	}
					// 	ListLog(pankey_Log_EndMethod, "getByIndex", "");
					// 	return *i_pointer;
					// }
					
					// virtual bool contain(T a_value)=0;
					
					// virtual int getIndex(T a_value)=0;

					// virtual T* remove(T a_value)=0;

					// virtual bool destroy(T a_value){
					// 	ListLog(pankey_Log_StartMethod, "destroy", "");
					// 	T* t = this->remove(a_value);
					// 	bool removed = t != nullptr;
					// 	if(removed && this->isOwner()){
					// 		ListLog(pankey_Log_Statement, "destroy", "deleting pointer");
					// 		delete t;
					// 	}
					// 	ListLog(pankey_Log_EndMethod, "destroy", "");
					// 	return removed;
					// }
					
					// //special removes
					// virtual bool destroyAll(T a_value)=0;
					// virtual bool destroyFirst(T a_value)=0;
					// virtual bool destroyLast(T a_value)=0;
					
					// virtual T* put(T a_value){
					// 	ListLog(pankey_Log_StartMethod, "put", "");
					// 	if(this->contain(a_value)){
					// 		return this->getPointer(a_value);
					// 	}
					// 	ListLog(pankey_Log_EndMethod, "put", "");
					// 	return this->add(a_value);
					// }
					
					// virtual int repeated(T a_value){
					// 	ListLog(pankey_Log_StartMethod, "repeated", "");
					// 	int size = 0;
					// 	for(int x = 0; x < this->length(); x++){
					// 		T t = *this->getPointerByIndex(x);
					// 		if(a_value == t){
					// 			size++;
					// 		}
					// 	}
					// 	ListLog(pankey_Log_EndMethod, "repeated", "");
					// 	return size;
					// }
					
					// virtual T* addFirst(T a_value){
					// 	ListLog(pankey_Log_StartMethod, "addFirst", "");
					// 	ListLog(pankey_Log_EndMethod, "addFirst", "");
					// 	return this->insert(0, a_value);
					// }
					
					// virtual T* addLast(T a_value){
					// 	ListLog(pankey_Log_StartMethod, "addLast", "");
					// 	ListLog(pankey_Log_EndMethod, "addLast", "");
					// 	return this->add(a_value);
					// }
					
					// //operators
					// virtual T& operator[](int x)=0;
				private:
			};

		}

	}

#endif