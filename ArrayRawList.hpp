
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
						for(int x = 0; x < a_list.length(); x++){
							this->add(*a_list.getPointerByIndex(x));
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
					
					virtual T* add(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "add", "");
						T* i_value = new T();
						*i_value = a_value;
						ArrayRawListLog(pankey_Log_EndMethod, "add", "");
						return this->addPointer(i_value);
					}
					
					virtual T* set(int a_index, T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "set", "");
						if(a_index >= this->length()){
							return nullptr;			
						}
						if(this->m_values[a_index] == nullptr){
							this->m_values[a_index] = new T();
						}
						*this->m_values[a_index] = a_value;
						ArrayRawListLog(pankey_Log_EndMethod, "set", "");
						return this->m_values[a_index];
					}
					
					virtual T* insert(int a_index, T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "insert", "");
						if(a_index >= this->length() + 1){
							return nullptr;
						}
						if(this->getSize() <= this->length()){
							this->expand(this->m_expandSize);
						}
						T* nVaule;
						T* rVaule = new T();
						*rVaule = a_value;
						for(int x = a_index; x <= this->length(); x++){
							nVaule = this->m_values[x];
							this->m_values[x] = rVaule;
							rVaule = nVaule;
						}
						this->incrementIndex();
						ArrayRawListLog(pankey_Log_EndMethod, "insert", "");
						return this->m_values[a_index];
					}
					
					virtual T* getPointer(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "getPointer", "");
						if(this->m_values == nullptr){
							return nullptr;
						}
						for(int x = 0; x < this->length(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								return this->m_values[x];
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "getPointer", "");
						return nullptr;
					}
					
					virtual T& getReference(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "getReference", "");
						ArrayRawListLog(pankey_Log_EndMethod, "getReference", "");
						return *this->getPointer(a_key);
					}
					
					virtual bool contain(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "contain", "");
						if(this->m_values == nullptr){
							return false;
						}
						for(int x = 0; x < this->length(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								return true;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "contain", "");
						return false;
					}
					
					virtual int getIndex(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "getIndex", "");
						if(this->isEmpty()){
							return -1;
						}
						for(int x = 0; x < this->length(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								return x;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "getIndex", "");
						return -1;
					}
					
					virtual T* remove(T a_key){
						ArrayRawListLog(pankey_Log_StartMethod, "remove", "");
						if(this->isEmpty()){
							ArrayRawListLog(pankey_Log_EndMethod, "remove", "");
							return nullptr;
						}
						int i_index = -1;
						for(int x = 0; x < this->length(); x++){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_key == *this->m_values[x]){
								i_index = x;
								break;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "remove", "");
						return this->removePointerByIndex(i_index);
					}
				
					////////////////////////////////////////////special removes part///////////////////////////////////////////////
					virtual bool destroyAll(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "destroyAll", "");
						if(this->isEmpty()){
							ArrayRawListLog(pankey_Log_EndMethod, "destroyAll", "");
							return false;
						}
						bool r_val = false;
						int p_x = 0;
						for(int x = 0; x < this->length(); x++){
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
							ArrayRawListLog(pankey_Log_EndMethod, "destroyAll", "!this->isInOrder()");
							return r_val;
						}
						this->length(p_x);
						ArrayRawListLog(pankey_Log_EndMethod, "destroyAll", "");
						return r_val;
					}
					
					virtual bool destroyFirst(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "destroyFirst", "");
						ArrayRawListLog(pankey_Log_EndMethod, "destroyFirst", "");
						return this->destroy(a_value);
					}
					
					virtual bool destroyLast(T a_value){
						ArrayRawListLog(pankey_Log_StartMethod, "destroyLast", "");
						if(this->isEmpty()){
							ArrayRawListLog(pankey_Log_EndMethod, "destroyLast", "");
							return false;
						}
						int i_index = -1;
						for(int x = this->length() - 1; x >= 0; x--){
							if(this->m_values[x] == nullptr){
								continue;
							}
							if(a_value == *this->m_values[x]){
								i_index = x;
								break;
							}
						}
						ArrayRawListLog(pankey_Log_EndMethod, "destroyLast", "");
						return this->destroyByIndex(i_index);
					}
					
					virtual T& operator[](int x){
						ArrayRawListLog(pankey_Log_StartMethod, "operator[]", "");
						// if(this->m_values == nullptr){
							// pankey_ErrorHandler(App_Crash_ERROR, "ArrayRawList", "operator[]", "null m_values");
						// }
						if(x > this->length() && this->length() > 0){
							return *this->m_values[this->length() - 1];
						}
						if(x < this->length()){
							return *this->m_values[x];
						}
						if(x >= this->getSize()){
							this->expand(this->m_expandSize);
						}
						if(this->length() == x){
							this->incrementIndex();
						}
						this->m_values[x] = new T();
						ArrayRawListLog(pankey_Log_EndMethod, "operator[]", "");
						return *this->m_values[x];
					}
					
					virtual T operator[](int x) const{
						// ArrayRawListLog(pankey_Log_StartMethod, "operator[]", "");
						if(x >= this->length() && this->length() != 0){
							return *this->m_values[this->length() - 1];
						}
						if(x < this->length() && x >= 0){
							return *this->m_values[x];
						}
						// ArrayRawListLog(pankey_Log_EndMethod, "operator[]", "");
						return T();
					}
				
					////////////////////////////////////////////operator part///////////////////////////////////////////////
					
					
					virtual ArrayRawList<T>& operator=(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "operator=", "");
						this->clear();
						for(int x = 0; x < a_list.length(); x++){
							T* i_pointer = a_list.getPointerByIndex(x);
							if(i_pointer == nullptr){
								this->addPointer(nullptr);
								continue;
							}
							this->add(*i_pointer);
						}
						ArrayRawListLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}
					
					virtual bool operator==(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "operator==", "");
						if(this->length() != a_list.length()){
							return false;
						}
						for(int x = 0; x < a_list.length(); x++){
							T* f_value_1 = this->getPointerByIndex(x);
							T* f_value_2 = a_list.getPointerByIndex(x);
							if(f_value_1 == f_value_2){
								continue;
							}
							if(f_value_1 != nullptr && f_value_2 != nullptr){
								if(*f_value_1 != *f_value_2){
									return false;
								}
							}
							this->add(*a_list.getPointerByIndex(x));
						}
						ArrayRawListLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}
					
					virtual bool operator!=(const ArrayRawList<T>& a_list){
						ArrayRawListLog(pankey_Log_StartMethod, "operator!=", "");
						if(this->length() != a_list.length()){
							return true;
						}
						for(int x = 0; x < a_list.length(); x++){
							T* t_value = this->getPointerByIndex(x);
							T* f_value = a_list.getPointerByIndex(x);
							if(t_value == f_value){
								continue;
							}
							if(t_value != nullptr && t_value != nullptr){
								if(*t_value == *f_value){
									return false;
								}
							}
							this->add(*a_list.getPointerByIndex(x));
						}
						ArrayRawListLog(pankey_Log_EndMethod, "operator!=", "");
						return true;
					}
				
					////////////////////////////////////////////Iterator part///////////////////////////////////////////////
					
					ListIterator<T> begin(){
						ArrayRawListLog(pankey_Log_StartMethod, "begin", "");
						ArrayRawListLog(pankey_Log_EndMethod, "begin", "");
						return ListIterator<T>(this, 0, this->length());
					}
					
					ListIterator<T> end(){
						ArrayRawListLog(pankey_Log_StartMethod, "end", "");
						ArrayRawListLog(pankey_Log_EndMethod, "end", "");
						return ListIterator<T>(this, this->length(), this->length());
					}
					
				protected:
			};

		}

	}

#endif