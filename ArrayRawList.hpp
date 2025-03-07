
#ifndef ArrayRawList_hpp
	#define ArrayRawList_hpp

	#include "ArrayRawPointerList.hpp"
	#include "RawList.hpp"
	#include "ListIterator.hpp"

	#if defined(pankey_Log) && (defined(ArrayRawList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayRawListLog(status,method,mns) pankey_Log(status,"ArrayRawList",method,mns)
	#else
		#define ArrayRawListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			class ArrayRawList : public ArrayRawPointerList<T>, virtual public RawList<T>{
				public:
					ArrayRawList(){
						ArrayRawListLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayRawListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayRawList(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "Constructor", "");
						this->m_values = new T*[a_list.getSize()];
						this->setSize(a_list.getSize());
						for(int x = 0; x < a_list.getLastIndex(); x++){
							this->addLValue(*a_list.getByIndex(x));
						}
						ArrayRawListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayRawList(int c_size, bool c_own, bool c_reordering) : ArrayRawPointerList<T>(c_size, c_own, c_reordering){
						ArrayRawListLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayRawListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~ArrayRawList(){
						ArrayRawListLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayRawListLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual T* addLValue(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "addLValue", "");
						T* i_value = new T();
						*i_value = a_value;
						ArrayRawListLog(pankey_Log_EndMethod, "addLValue", "");
						return this->addPointer(i_value);
					}
					
					virtual T* setLValue(int a_index, T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "setLValue", "");
						if(a_index >= this->getLastIndex()){
							return nullptr;			
						}
						if(this->m_values[a_index] == nullptr){
							this->m_values[a_index] = new T();
						}
						*this->m_values[a_index] = a_value;
						ArrayRawListLog(pankey_Log_EndMethod, "setLValue", "");
						return this->m_values[a_index];
					}
					
					virtual T* insertLValue(int a_index, T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "insertLValue", "");
						if(a_index >= this->getLastIndex() + 1){
							return nullptr;
						}
						if(this->getSize() <= this->getLastIndex()){
							this->expand(this->m_expandSize);
						}
						T* nVaule;
						T* rVaule = new T();
						*rVaule = a_value;
						for(int x = a_index; x <= this->getLastIndex(); x++){
							nVaule = this->m_values[x];
							this->m_values[x] = rVaule;
							rVaule = nVaule;
						}
						this->incrementIndex();
						ArrayRawListLog(pankey_Log_EndMethod, "insertLValue", "");
						return this->m_values[a_index];
					}
					
					virtual T* getByLValue(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "getByLValue", "");
						if(this->m_values == nullptr){
							return nullptr;
						}
						for(int x = 0; x < this->getLastIndex(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								return this->m_values[x];
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "getByLValue", "");
						return nullptr;
					}
					
					virtual bool containByLValue(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "containByLValue", "");
						if(this->m_values == nullptr){
							return false;
						}
						for(int x = 0; x < this->getLastIndex(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								return true;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "containByLValue", "");
						return false;
					}
					
					virtual int getIndexByLValue(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "getIndexByLValue", "");
						if(this->isEmpty()){
							return -1;
						}
						for(int x = 0; x < this->getLastIndex(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								return x;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "getIndexByLValue", "");
						return -1;
					}
					
					virtual T* removeByLValue(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "removeByLValue", "");
						if(this->isEmpty()){
							ArrayRawListLog(pankey_Log_EndMethod, "removeByLValue", "");
							return nullptr;
						}
						int i_index = -1;
						for(int x = 0; x < this->getLastIndex(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								i_index = x;
								break;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "removeByLValue", "");
						return this->removeByIndex(i_index);
					}
				
					////////////////////////////////////////////special removes part///////////////////////////////////////////////
					virtual bool removeAll(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "removeAll", "");
						if(this->isEmpty()){
							ArrayRawListLog(pankey_Log_EndMethod, "removeAll", "");
							return false;
						}
						bool r_val = false;
						int p_x = 0;
						for(int x = 0; x < this->getLastIndex(); x++){
							if(a_value == *this->m_values[x]){
								if(this->isOwner()){
									delete this->m_values[x];
								}
								r_val = true;
								this->m_values[x] = nullptr;
							}else{
								if(!this->isInOrder()){
									continue;
								}
								this->m_values[p_x] = this->m_values[x];
								p_x++;
							}
						}
						if(!this->isInOrder()){
							ArrayRawListLog(pankey_Log_EndMethod, "removeAll", "!this->isInOrder()");
							return r_val;
						}
						this->setLastIndex(p_x);
						ArrayRawListLog(pankey_Log_EndMethod, "removeAll", "");
						return r_val;
					}
					
					virtual bool removeFirst(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "removeFirst", "");
						ArrayRawListLog(pankey_Log_EndMethod, "removeFirst", "");
						return this->removeDeleteByLValue(a_value);
					}
					
					virtual bool removeLast(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "removeLast", "");
						if(this->isEmpty()){
							ArrayRawListLog(pankey_Log_EndMethod, "removeLast", "");
							return false;
						}
						int i_index = -1;
						for(int x = this->getLastIndex() - 1; x >= 0; x--){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_value == *this->m_values[x]){
								i_index = x;
								break;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "removeLast", "");
						return this->removeDeleteByIndex(i_index);
					}
					
					virtual T& operator[](int x){
						ArrayRawListLog(pankey_Log_StartMethod, "operator[]", "");
						// if(this->m_values == nullptr){
							// pankey_ErrorHandler(App_Crash_ERROR, "ArrayRawList", "operator[]", "null m_values");
						// }
						if(x > this->getLastIndex() && this->getLastIndex() > 0){
							return *this->m_values[this->getLastIndex() - 1];
						}
						if(x < this->getLastIndex()){
							return *this->m_values[x];
						}
						if(x >= this->getSize()){
							this->expand(this->m_expandSize);
						}
						if(this->getLastIndex() == x){
							this->incrementIndex();
						}
						this->m_values[x] = new T();
						ArrayRawListLog(pankey_Log_EndMethod, "operator[]", "");
						return *this->m_values[x];
					}
					
					virtual T operator[](int x) const{
						// ArrayRawListLog(pankey_Log_StartMethod, "operator[]", "");
						if(x >= this->getLastIndex() && this->getLastIndex() != 0){
							return *this->m_values[this->getLastIndex() - 1];
						}
						if(x < this->getLastIndex() && x >= 0){
							return *this->m_values[x];
						}
						// ArrayRawListLog(pankey_Log_EndMethod, "operator[]", "");
						return T();
					}
				
					////////////////////////////////////////////operator part///////////////////////////////////////////////
					
					
					virtual ArrayRawList<T>& operator=(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "operator=", "");
						this->clear();
						for(int x = 0; x < a_list.getLastIndex(); x++){
							T* i_pointer = a_list.getByIndex(x);
							if(i_pointer == nullptr){
								this->addPointer(nullptr);
								continue;
							}
							this->addLValue(*i_pointer);
						}
						ArrayRawListLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}
					
					virtual bool operator==(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "operator==", "");
						if(this->getLastIndex() != a_list.getLastIndex()){
							return false;
						}
						for(int x = 0; x < a_list.getLastIndex(); x++){
							T* f_value_1 = this->getByIndex(x);
							T* f_value_2 = a_list.getByIndex(x);
							if(f_value_1 == f_value_2){
								continue;
							}
							if(f_value_1 != nullptr && f_value_2 != nullptr){
								if(*f_value_1 != *f_value_2){
									return false;
								}
							}
							this->addLValue(*a_list.getByIndex(x));
						}
						ArrayRawListLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}
					
					virtual bool operator!=(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "operator!=", "");
						if(this->getLastIndex() != a_list.getLastIndex()){
							return true;
						}
						for(int x = 0; x < a_list.getLastIndex(); x++){
							T* t_value = this->getByIndex(x);
							T* f_value = a_list.getByIndex(x);
							if(t_value == f_value){
								continue;
							}
							if(t_value != nullptr && t_value != nullptr){
								if(*t_value == *f_value){
									return false;
								}
							}
							this->addLValue(*a_list.getByIndex(x));
						}
						ArrayRawListLog(pankey_Log_EndMethod, "operator!=", "");
						return true;
					}
				
					////////////////////////////////////////////Iterator part///////////////////////////////////////////////
					
					ListIterator<T> begin(){
						ArrayRawListLog(pankey_Log_StartMethod, "begin", "");
						ArrayRawListLog(pankey_Log_EndMethod, "begin", "");
						return ListIterator<T>(this, 0, this->getLastIndex());
					}
					
					ListIterator<T> end(){
						ArrayRawListLog(pankey_Log_StartMethod, "end", "");
						ArrayRawListLog(pankey_Log_EndMethod, "end", "");
						return ListIterator<T>(this, this->getLastIndex(), this->getLastIndex());
					}
					
				protected:
			};

		}

	}

#endif