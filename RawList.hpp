
#ifndef RawList_hpp
#define RawList_hpp

#include "RawPointerList.hpp"

#if defined(RawList_LogApp) && defined(pankey_Log)
	#include "Logger_status.hpp"
	#define RawListLog(status,method,mns) pankey_Log(status,"RawList",method,mns)
#else
	#define RawListLog(status,method,mns)
#endif

namespace pankey{

template <class T>
class RawList : virtual public RawPointerList<T>{	
	public:
		virtual ~RawList(){}

		virtual void addCopy(RawPointerList<T>* a_list){
			RawListLog(pankey_Log_StartMethod, "addCopy", "");
			for(int x = 0; x < a_list->getLastIndex(); x++){
				T* f_value = a_list->getByIndex(x);
				if(f_value == nullptr){
					continue;
				}
				this->addLValue(*f_value);
			}
			RawListLog(pankey_Log_EndMethod, "addCopy", "");
		}

		virtual T* addLValue(T a_value)=0;

		virtual T* add(T a_value){
			RawListLog(pankey_Log_StartMethod, "add", "");
			RawListLog(pankey_Log_EndMethod, "add", "");
			return this->addLValue(a_value);
		}

		virtual T* setLValue(int a_position, T a_value)=0;
		
		virtual T* set(int a_position, T a_value){
			RawListLog(pankey_Log_StartMethod, "set", "");
			RawListLog(pankey_Log_EndMethod, "set", "");
			return this->setLValue(a_position, a_value);
		}
		
		virtual T* insertLValue(int a_position, T a_value)=0;
		
		virtual T* insert(int a_position, T a_value){
			RawListLog(pankey_Log_StartMethod, "insert", "");
			RawListLog(pankey_Log_EndMethod, "insert", "");
			return this->insertLValue(a_position, a_value);
		}
		
		virtual T* getByLValue(T a_value)=0;
		
		virtual T* get(T a_value){
			RawListLog(pankey_Log_StartMethod, "get", "");
			RawListLog(pankey_Log_EndMethod, "get", "");
			return this->getByLValue(a_value);
		}
		
		virtual T& getReferenceByIndex(int x)const{
			RawListLog(pankey_Log_StartMethod, "getByIndex", "");
			RawListLog(pankey_Log_EndMethod, "getByIndex", "");
			return *this->getByIndex(x);
		}
		
		virtual T getValueByIndex(int x)const{
			RawListLog(pankey_Log_StartMethod, "getValueByIndex", "");
			T* i_pointer = this->getByIndex(x);
			if(i_pointer == nullptr){
				return T();
			}
			RawListLog(pankey_Log_EndMethod, "getValueByIndex", "");
			return *i_pointer;
		}
		
		virtual bool containByLValue(T a_value)=0;
		
		virtual bool contain(T a_value){
			RawListLog(pankey_Log_StartMethod, "contain", "");
			RawListLog(pankey_Log_EndMethod, "contain", "");
			return this->containByLValue(a_value);
		}
		
		virtual int getIndexByLValue(T a_value)=0;
		
		virtual int getIndex(T a_value){
			RawListLog(pankey_Log_StartMethod, "getIndex", "");
			RawListLog(pankey_Log_EndMethod, "getIndex", "");
			return this->getIndexByLValue(a_value);
		}

		virtual T* removeByLValue(T a_value)=0;
		
		virtual bool remove(T a_value){
			RawListLog(pankey_Log_StartMethod, "remove", "");
			RawListLog(pankey_Log_EndMethod, "remove", "");
			return this->removeDeleteByLValue(a_value);
		}
		
		virtual bool removeByIndex(int a_position){
			RawListLog(pankey_Log_StartMethod, "removeByIndex", "");
			RawListLog(pankey_Log_EndMethod, "removeByIndex", "");
			return this->removeDeleteByPosition(a_position);
		}

		virtual bool removeDeleteByLValue(T a_value){
			RawListLog(pankey_Log_StartMethod, "removeDeleteByLValue", "");
			T* t = this->removeByLValue(a_value);
			bool removed = t != nullptr;
			if(removed && this->isOwner()){
				RawListLog(pankey_Log_Statement, "removeDeleteByLValue", "deleting pointer");
				delete t;
			}
			RawListLog(pankey_Log_EndMethod, "removeDeleteByLValue", "");
			return removed;
		}
		
		//special removes
		virtual bool removeAll(T a_value)=0;
		virtual bool removeFirst(T a_value)=0;
		virtual bool removeLast(T a_value)=0;
	
		template<class... Args>
		void addPack(Args... x){
			RawListLog(pankey_Log_StartMethod, "addPack", "");
			T array[] = {x...};
			for(const T& a : array){
				this->addPointer(new T(a));
			}
			RawListLog(pankey_Log_EndMethod, "addPack", "");
		}
		
		template<class... Args>
		T* addWithParameters(Args... x){
			RawListLog(pankey_Log_StartMethod, "addWithParameters", "");
			RawListLog(pankey_Log_EndMethod, "addWithParameters", "");
			return this->addPointer(new T(x...));
		}
		
		virtual T* put(T a_value){
			RawListLog(pankey_Log_StartMethod, "put", "");
			if(this->containByLValue(a_value)){
				return nullptr;
			}
			RawListLog(pankey_Log_EndMethod, "put", "");
			return this->addLValue(a_value);
		}
		
		virtual int repeated(T a_value){
			RawListLog(pankey_Log_StartMethod, "repeated", "");
			int size = 0;
			for(int x = 0; x < this->getLastIndex(); x++){
				T t = *this->getByIndex(x);
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
			return this->insertLValue(0, a_value);
		}
		
		virtual T* addLast(T a_value){
			RawListLog(pankey_Log_StartMethod, "addLast", "");
			RawListLog(pankey_Log_EndMethod, "addLast", "");
			return this->addLValue(a_value);
		}
		
		//operators
		virtual T& operator[](int x)=0;
	private:
};

}

#endif