
#ifndef RawList_hpp
	#define RawList_hpp

	#include "RawPointerList.hpp"

	#if defined(pankey_Log) && (defined(RawList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define RawListLog(status,method,mns) pankey_Log(status,"RawList",method,mns)
	#else
		#define RawListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template <class T>
			class RawList : virtual public RawPointerList<T>{	
				public:
					virtual ~RawList(){}

					using RawPointerList<T>::addPack;
					using RawPointerList<T>::addWithParameters;

					virtual void addCopy(RawList<T>& a_list){
						RawListLog(pankey_Log_StartMethod, "addCopy", "");
                        for(int x = 0; x < a_list.length(); x++){
                            T* f_value = a_list.getPointerByIndex(x);
                            this->add(*f_value);
                        }
						RawListLog(pankey_Log_EndMethod, "addCopy", "");
					}

					virtual T* add(T a_value)=0;
					
					virtual T* set(int a_index, T a_value)=0;
					
					virtual T* insert(int a_index, T a_value)=0;
					
					virtual T* getPointer(T a_value)=0;
					
					virtual T& getReference(T a_value)=0;
					
					virtual T& getReferenceByIndex(int x)const{
						RawListLog(pankey_Log_StartMethod, "getReferenceByIndex", "");
						RawListLog(pankey_Log_EndMethod, "getReferenceByIndex", "");
						return *this->getPointerByIndex(x);
					}
					
					virtual T getByIndex(int x)const{
						RawListLog(pankey_Log_StartMethod, "getByIndex", "");
						T* i_pointer = this->getPointerByIndex(x);
						if(i_pointer == nullptr){
							return T();
						}
						RawListLog(pankey_Log_EndMethod, "getByIndex", "");
						return *i_pointer;
					}
					
					virtual bool contain(T a_value)=0;
					
					virtual int getIndex(T a_value)=0;

					virtual T* remove(T a_value)=0;

					virtual bool destroy(T a_value){
						RawListLog(pankey_Log_StartMethod, "destroy", "");
						T* t = this->remove(a_value);
						bool removed = t != nullptr;
						if(removed && this->isOwner()){
							RawListLog(pankey_Log_Statement, "destroy", "deleting pointer");
							delete t;
						}
						RawListLog(pankey_Log_EndMethod, "destroy", "");
						return removed;
					}
					
					//special removes
					virtual bool destroyAll(T a_value)=0;
					virtual bool destroyFirst(T a_value)=0;
					virtual bool destroyLast(T a_value)=0;
					
					virtual T* put(T a_value){
						RawListLog(pankey_Log_StartMethod, "put", "");
						if(this->contain(a_value)){
							return this->getPointer(a_value);
						}
						RawListLog(pankey_Log_EndMethod, "put", "");
						return this->add(a_value);
					}
					
					virtual int repeated(T a_value){
						RawListLog(pankey_Log_StartMethod, "repeated", "");
						int size = 0;
						for(int x = 0; x < this->length(); x++){
							T t = *this->getPointerByIndex(x);
							if(a_value == t){
								size++;
							}
						}
						RawListLog(pankey_Log_EndMethod, "repeated", "");
						return size;
					}
					
					virtual T* addFirst(T a_value){
						RawListLog(pankey_Log_StartMethod, "addFirst", "");
						RawListLog(pankey_Log_EndMethod, "addFirst", "");
						return this->insert(0, a_value);
					}
					
					virtual T* addLast(T a_value){
						RawListLog(pankey_Log_StartMethod, "addLast", "");
						RawListLog(pankey_Log_EndMethod, "addLast", "");
						return this->add(a_value);
					}
					
					//operators
					virtual T& operator[](int x)=0;
				private:
			};

		}

	}

#endif