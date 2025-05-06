
#ifndef ArrayRawPointerList_hpp
	#define ArrayRawPointerList_hpp

	#include "RawPointerList.hpp"
	#include "MemoryAllocator.hpp"

	#if defined(pankey_Log) && (defined(ArrayRawPointerList_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayRawPointerListLog(status,method,mns) pankey_Log(status,"ArrayRawPointerList",method,mns)
	#else
		#define ArrayRawPointerListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			class ArrayRawPointerList : virtual public RawPointerList<T>{
				public:
					ArrayRawPointerList(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayRawPointerListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayRawPointerList(MemoryAllocator* a_allocator){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "Constructor", "");
						this->m_allocator = setMemoryAllocator(a_allocator);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayRawPointerList(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "Constructor", "");
						this->m_allocator = setMemoryAllocator(a_list.m_allocator);
						this->setOwner(false);
						this->expand(a_list.getSize());
						for(int x = 0; x < a_list.length(); x++){
							this->addPointer(a_list.getPointerByIndex(x));
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					ArrayRawPointerList(int c_size, bool c_own, bool c_reordering){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "Constructor", "");
						this->m_owner = c_own;
						this->m_reorder = c_reordering;
						this->expand(c_size);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~ArrayRawPointerList(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "Destructor", "");
						if(this->m_owner){
							for(int x=0; x < this->length() ; x++){
								this->destroyPointer(this->m_values[x]);
							}
						}
						deallocatePointerArray<T>(this->m_allocator, this->m_size, this->m_values);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "Destructor", "");
					}
					

					virtual bool isEmpty()const{
						ArrayRawPointerListLog(pankey_Log_StartMethod, "isEmpty", "");
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", "List Index:");
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", this->length());
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", "List Size:");
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", this->getSize());
						ArrayRawPointerListLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->length() == 0 || this->m_values == nullptr;
					}
				
					virtual bool replace(int i, int j){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "replace", "");
						if(i >= this->length() || j >= this->length()){
							return false;
						}
						T* it = this->m_values[i];
						T* jt = this->m_values[j];
						this->m_values[i] = jt;
						this->m_values[j] = it;
						ArrayRawPointerListLog(pankey_Log_EndMethod, "replace", "");
						return true;
					}
					
					virtual T* addPointer(T* a_value){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "addPointer", "");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Index Before adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->length());
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Size Before adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->getSize());
						if(this->length() >= this->getSize()){
							ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "this->length() >= this->getSize()");
							this->expand(this->m_expandSize);
						}
						if(this->length() >= this->getSize()){
							ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "this->length() >= this->getSize()");
							if(a_value != nullptr && this->isOwner()){
								ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "deleting pointer");
								delete a_value;
							}
							return nullptr;
						}
						this->m_values[this->length()] = a_value;
						this->incrementIndex();
						
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Index After adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->length());
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Size After adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->getSize());	
						ArrayRawPointerListLog(pankey_Log_EndMethod, "addPointer", "");
						return a_value;
					}
					
					virtual T* setPointer(int a_index, T* a_value){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "setPointer", "");
						if(a_index >= this->getSize()){
							ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", "expanding:");
							ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", a_index - this->getSize() + this->m_expandSize);
							this->expand(a_index - this->getSize() + this->m_expandSize);
						}
						if(a_index >= this->getSize()){
							if(a_value != nullptr && this->isOwner()){
								ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", "deleting a_value");
								delete a_value;
							}
							ArrayRawPointerListLog(pankey_Log_EndMethod, "setPointer", "a_index >= this->getSize()");
							return nullptr;			
						}
						T* i_value = this->getPointerByIndex(a_index);
						if(a_value == i_value){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "setPointer", "a_value == i_value");
							return a_value;
						}
						if(this->isOwner() && i_value != nullptr){
							ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", "deleting i_value");
							delete i_value;
						}
						this->m_values[a_index] = a_value;
						if(a_index > this->length()){
							this->length(a_index + 1);
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "setPointer", "");
						return a_value;
					}
					
					virtual T* insertPointer(int a_index, T* a_value){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "insertPointer", "");
						if(a_index >= this->length()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "insertPointer", "a_index >= this->length()");
							return this->addPointer(a_value);
						}
						if(this->length() >= this->getSize()){
							this->expand(this->m_expandSize);
						}
						if(this->length() >= this->getSize()){
							if(a_value != nullptr){
								delete a_value;
							}
							return nullptr;
						}
						T* nVaule;
						T* rVaule = a_value;
						for(int x = a_index; x <= this->length(); x++){
							nVaule = this->m_values[x];
							this->m_values[x] = rVaule;
							rVaule = nVaule;
						}
						this->incrementIndex();
						ArrayRawPointerListLog(pankey_Log_EndMethod, "insertPointer", "");
						return a_value;
					}
					
					virtual T* getPointerByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "getPointerByPointer", "");
						if(this->isEmpty()){
							return nullptr;
						}
						for(int x = 0; x < this->length(); x++){
							if(a_key == this->m_values[x]){
								return a_key;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "getPointerByPointer", "");
						return nullptr;
					}
					
					virtual T* getPointerByIndex(int x)const{
						ArrayRawPointerListLog(pankey_Log_StartMethod, "getPointerByIndex", "");
						ArrayRawPointerListLog(pankey_Log_Statement, "getPointerByIndex", "index: ");
						ArrayRawPointerListLog(pankey_Log_Statement, "getPointerByIndex", x);
						if(this->isEmpty() || x >= this->length()){
							ArrayRawPointerListLog(pankey_Log_Statement, "getPointerByIndex", "this->isEmpty(): ");
							ArrayRawPointerListLog(pankey_Log_Statement, "getPointerByIndex", this->isEmpty());
							ArrayRawPointerListLog(pankey_Log_Statement, "getPointerByIndex", "x >= this->length(): ");
							ArrayRawPointerListLog(pankey_Log_Statement, "getPointerByIndex", x >= this->length());
							return nullptr;
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "getPointerByIndex", "");
						return this->m_values[x];
					}
					
					virtual bool containByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "containByPointer", "");
						if(this->isEmpty()){
							ArrayRawPointerListLog(pankey_Log_Statement, "containByPointer", "this->isEmpty()");
							ArrayRawPointerListLog(pankey_Log_EndMethod, "containByPointer", "return false");
							return false;
						}
						for(int x = 0; x < this->length(); x++){
							if(a_key == this->m_values[x]){
								ArrayRawPointerListLog(pankey_Log_Statement, "containByPointer", "a_key == this->m_values[x]");
								ArrayRawPointerListLog(pankey_Log_EndMethod, "containByPointer", "return true");
								return true;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "containByPointer", "");
						return false;
					}
					
					virtual int getIndexByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "getIndexByPointer", "");
						if(this->isEmpty()){
							return -1;
						}
						for(int x = 0; x < this->length(); x++){
							if(a_key == this->m_values[x]){
								return x;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "getIndexByPointer", "");
						return -1;
					}
					
					virtual void reset(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "reset", "");
						this->length(0);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "reset", "");
					}
					
					virtual void clear(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "clear", "");
						for(int x = 0; x < this->length(); x++){
							T* f_value = this->m_values[x];
							if(f_value == nullptr){
								ArrayRawPointerListLog(pankey_Log_Statement, "clear", "this->m_values[x] == nullptr");
								continue;
							}
							if(this->isOwner()){
								ArrayRawPointerListLog(pankey_Log_Statement, "clear", "this->isOwner()");
								delete f_value;
							}
							this->m_values[x] = nullptr;
						}
						this->length(0);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "clear", "");
					}
					
					virtual T* removePointerByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "removePointerByPointer", "");
						int i_index = this->getIndexByPointer(a_key);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removePointerByPointer", "removed Index: ");
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removePointerByPointer", i_index);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removePointerByPointer", "");
						return this->removePointerByIndex(i_index);
					}
					
					virtual T* removePointerByIndex(int a_index){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "removePointerByIndex", "");
						if(this->isEmpty() || a_index >= this->length()){
							return nullptr;
						}
						T* i_value = this->m_values[a_index];
						this->m_values[a_index] = nullptr;
						if(!this->isInOrder()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "removePointerByIndex", "!this->isInOrder()");
							return i_value;
						}
						int i_iteration = this->length();
						this->decrementIndex();
						for(int x = a_index + 1; x < i_iteration; x++){
							this->m_values[x - 1] = this->m_values[x];
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removePointerByIndex", "");
						return i_value;
					}
					
					virtual bool destroyFirstIndex(int a_amount){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "destroyFirstIndex", "");
						if(this->isEmpty()){
							return false;
						}
						int i_iteration = 0;
						for(int x = 0; x < a_amount && x < this->length(); x++){
							if(this->isOwner() && this->m_values[x] != nullptr){
								delete this->m_values[x];
							}
							this->m_values[x] = nullptr;
							i_iteration++;
						}
						if(!this->isInOrder()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "destroyFirstIndex", "!this->isInOrder()");
							return true;
						}
						for(int x = i_iteration; x < this->length(); x++){
							this->m_values[x - i_iteration] = this->m_values[x];
						}
						this->decrementIndex(i_iteration);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "destroyFirstIndex", "");
						return true;
					}
				
					virtual bool destroyLastIndex(int a_amount){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "destroyLastIndex", "");
						if(this->isEmpty()){
							return false;
						}
						int i_iteration = 0;
						for(int x = this->length() - 1; x >= this->length() - a_amount && x >= 0; x--){
							if(this->isOwner() && this->m_values[x] != nullptr){
								delete this->m_values[x];
							}
							this->m_values[x] = nullptr;
							i_iteration++;
						}
						if(!this->isInOrder()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "destroyLastIndex", "!this->isInOrder()");
							return true;
						}
						this->decrementIndex(i_iteration);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "destroyLastIndex", "");
						return true;
					}
					
					//resize length by adding more space
					//bug unkown for template = char on feather m0
					virtual void expand(int a_size){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "expand", "");
						
						int i_size = this->getSize() + a_size;
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Index:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->length());
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Size:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->getSize());	
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List extra size added:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", a_size);
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List new size:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", i_size);
						if(i_size <= 1){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "expand", "new size is too small");
							return;
						}
						T **nT;
						nT = allocatePointerArray<T>(this->m_allocator, i_size);
						for(int x = 0; x < this->length(); x++){
							ArrayRawPointerListLog(pankey_Log_Statement, "expand", "iteration:");
							ArrayRawPointerListLog(pankey_Log_Statement, "expand", x);
							nT[x] = this->m_values[x];
						}
						if(this->m_values != nullptr){
							ArrayRawPointerListLog(pankey_Log_Statement, "expand", "this->m_values != nullptr");
							deallocatePointerArray<T>(this->m_allocator, this->m_size, this->m_values);
						}
						this->m_values = nT;
						this->setSize(i_size);
						
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Index:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->length());
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Size:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->getSize());	
						ArrayRawPointerListLog(pankey_Log_EndMethod, "expand", "");
					}
					
					// virtual ArrayRawPointerList<T>* expand(int a_size){
					// 	ArrayRawPointerListLog(pankey_Log_StartMethod, "expand", "");
					// 	int i_size = this->getSize() + a_size;
					// 	ArrayRawPointerList<T> *i_list = new ArrayRawPointerList<T>(i_size, true, true);	
					// 	for(int x = 0; x < this->length(); x++){
					// 		T* f_value = this->getPointerByIndex(x);
					// 		i_list->addPointer(f_value);
					// 	}
					// 	ArrayRawPointerListLog(pankey_Log_EndMethod, "expand", "");
					// 	return i_list;
					// }

					virtual void reorder(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "reoder", "");
						int i_offset = 0;
						for(int x = 0; x < this->length(); x++){
							T* f_value = this->getPointerByIndex(x);
							if(f_value == nullptr){
								continue;
							}
							this->m_values[i_offset] = f_value;
							i_offset++;
						}
						this->length(i_offset);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "reoder", "");
					}
				
					////////////////////////////////////////////operator part///////////////////////////////////////////////
					
					
					virtual ArrayRawPointerList& operator=(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "operator=", "const ArrayRawPointerList<T>&");
						this->clear();
						for(int x = 0; x < a_list.length(); x++){
							T* f_value = a_list.getPointerByIndex(x);
							this->addPointer(f_value);
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					virtual bool operator==(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "operator=", "const ArrayRawPointerList<T>&");
						if(a_list.length() != this->length()){
							return false;
						}
						for(int x = 0; x < a_list.length(); x++){
							T* f_value_1 = a_list.getPointerByIndex(x);
							T* f_value_2 = this->getPointerByIndex(x);
							if(f_value_1 != f_value_2){
								return false;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "operator=", "const ArrayRawPointerList<T>&");
						return true;
					}

					virtual bool operator!=(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "operator=", "");
						if(a_list.length() != this->length()){
							return true;
						}
						for(int x = 0; x < a_list.length(); x++){
							T* f_value_1 = a_list.getPointerByIndex(x);
							T* f_value_2 = this->getPointerByIndex(x);
							if(f_value_1 != f_value_2){
								return true;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "operator=", "");
						return false;
					}
					
				protected:
					virtual void destroyPointer(T* a_pointer){
						if(a_pointer == nullptr){
							return;
						}
						delete a_pointer;
					}
					
					MemoryAllocator* m_allocator = nullptr;
					T** m_values = nullptr;
					int m_expandSize = 5;
			};

		}
		
	}

#endif