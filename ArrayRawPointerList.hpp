
#ifndef ArrayRawPointerList_hpp
	#define ArrayRawPointerList_hpp

	#include "RawPointerList.hpp"

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
					
					ArrayRawPointerList(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "Constructor", "");
						this->setOwner(false);
						this->expand(a_list.getSize());
						for(int x = 0; x < a_list.getLastIndex(); x++){
							this->addPointer(a_list.getByIndex(x));
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
						if(this->m_values != nullptr){
							if(this->m_owner){
								for(int x=0; x < this->getLastIndex() ; x++){
									delete this->m_values[x];
								}
							}
							this->setLastIndex(0);
							this->setSize(0);
							delete[] this->m_values;
							this->m_values = nullptr;
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "Destructor", "");
					}
					

					virtual bool isEmpty()const{
						ArrayRawPointerListLog(pankey_Log_StartMethod, "isEmpty", "");
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", "List Position:");
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", this->getLastIndex());
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", "List Size:");
						ArrayRawPointerListLog(pankey_Log_Statement, "isEmpty", this->getSize());
						ArrayRawPointerListLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->getLastIndex() == 0 || this->m_values == nullptr;
					}
				
					virtual bool replace(int i, int j){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "replace", "");
						if(i >= this->getLastIndex() || j >= this->getLastIndex()){
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
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Position Before adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->getLastIndex());
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Size Before adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->getSize());
						if(this->getLastIndex() >= this->getSize()){
							ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "this->getLastIndex() >= this->getSize()");
							this->expand(this->m_expandSize);
						}
						if(this->getLastIndex() >= this->getSize()){
							ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "this->getLastIndex() >= this->getSize()");
							if(a_value != nullptr && this->isOwner()){
								ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "deleting pointer");
								delete a_value;
							}
							return nullptr;
						}
						this->m_values[this->getLastIndex()] = a_value;
						this->incrementPosition();
						
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Position After adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->getLastIndex());
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", "List Size After adding:");
						ArrayRawPointerListLog(pankey_Log_Statement, "addPointer", this->getSize());	
						ArrayRawPointerListLog(pankey_Log_EndMethod, "addPointer", "");
						return a_value;
					}
					
					virtual T* setPointer(int a_position, T* a_value){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "setPointer", "");
						if(a_position >= this->getSize()){
							ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", "expanding:");
							ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", a_position - this->getSize() + this->m_expandSize);
							this->expand(a_position - this->getSize() + this->m_expandSize);
						}
						if(a_position >= this->getSize()){
							if(a_value != nullptr && this->isOwner()){
								ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", "deleting a_value");
								delete a_value;
							}
							ArrayRawPointerListLog(pankey_Log_EndMethod, "setPointer", "a_position >= this->getSize()");
							return nullptr;			
						}
						T* i_value = this->getByIndex(a_position);
						if(a_value == i_value){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "setPointer", "a_value == i_value");
							return a_value;
						}
						if(this->isOwner() && i_value != nullptr){
							ArrayRawPointerListLog(pankey_Log_Statement, "setPointer", "deleting i_value");
							delete i_value;
						}
						this->m_values[a_position] = a_value;
						if(a_position > this->getLastIndex()){
							this->setLastIndex(a_position + 1);
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "setPointer", "");
						return a_value;
					}
					
					virtual T* insertPointer(int a_position, T* a_value){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "insertPointer", "");
						if(a_position >= this->getLastIndex()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "insertPointer", "a_position >= this->getLastIndex()");
							return this->addPointer(a_value);
						}
						if(this->getLastIndex() >= this->getSize()){
							this->expand(this->m_expandSize);
						}
						if(this->getLastIndex() >= this->getSize()){
							if(a_value != nullptr){
								delete a_value;
							}
							return nullptr;
						}
						T* nVaule;
						T* rVaule = a_value;
						for(int x = a_position; x <= this->getLastIndex(); x++){
							nVaule = this->m_values[x];
							this->m_values[x] = rVaule;
							rVaule = nVaule;
						}
						this->incrementPosition();
						ArrayRawPointerListLog(pankey_Log_EndMethod, "insertPointer", "");
						return a_value;
					}
					
					virtual T* getByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "getByPointer", "");
						if(this->isEmpty()){
							return nullptr;
						}
						for(int x = 0; x < this->getLastIndex(); x++){
							if(a_key == this->m_values[x]){
								return a_key;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "getByPointer", "");
						return nullptr;
					}
					
					virtual T* getByIndex(int x)const{
						ArrayRawPointerListLog(pankey_Log_StartMethod, "getByIndex", "");
						if(this->isEmpty() || x >= this->getLastIndex()){
							return nullptr;
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "getByIndex", "");
						return this->m_values[x];
					}
					
					virtual bool containByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "containByPointer", "");
						if(this->isEmpty()){
							ArrayRawPointerListLog(pankey_Log_Statement, "containByPointer", "this->isEmpty()");
							ArrayRawPointerListLog(pankey_Log_EndMethod, "containByPointer", "return false");
							return false;
						}
						for(int x = 0; x < this->getLastIndex(); x++){
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
						for(int x = 0; x < this->getLastIndex(); x++){
							if(a_key == this->m_values[x]){
								return x;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "getIndexByPointer", "");
						return -1;
					}
					
					virtual void reset(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "reset", "");
						this->setLastIndex(0);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "reset", "");
					}
					
					virtual void clear(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "clear", "");
						for(int x = 0; x < this->getLastIndex(); x++){
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
						this->setLastIndex(0);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "clear", "");
					}
					
					virtual T* removeByPointer(T* a_key){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "removeByPointer", "");
						int i_position = this->getIndexByPointer(a_key);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removeByPointer", "removed position: ");
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removeByPointer", i_position);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removeByPointer", "");
						return this->removeByPosition(i_position);
					}
					
					virtual T* removeByPosition(int a_position){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "removeByPosition", "");
						if(this->isEmpty() || a_position >= this->getLastIndex()){
							return nullptr;
						}
						T* i_value = this->m_values[a_position];
						this->m_values[a_position] = nullptr;
						if(!this->isInOrder()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "removeByPosition", "!this->isInOrder()");
							return i_value;
						}
						int i_iteration = this->getLastIndex();
						this->decrementPosition();
						for(int x = a_position + 1; x < i_iteration; x++){
							this->m_values[x - 1] = this->m_values[x];
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removeByPosition", "");
						return i_value;
					}
					
					virtual bool removeFirstIndex(int a_amount){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "removeFirstIndex", "");
						if(this->isEmpty()){
							return false;
						}
						int i_iteration = 0;
						for(int x = 0; x < a_amount && x < this->getLastIndex(); x++){
							if(this->isOwner() && this->m_values[x] != nullptr){
								delete this->m_values[x];
							}
							this->m_values[x] = nullptr;
							i_iteration++;
						}
						if(!this->isInOrder()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "removeFirstIndex", "!this->isInOrder()");
							return true;
						}
						for(int x = i_iteration; x < this->getLastIndex(); x++){
							this->m_values[x - i_iteration] = this->m_values[x];
						}
						this->decrementPosition(i_iteration);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removeFirstIndex", "");
						return true;
					}
				
					virtual bool removeLastIndex(int a_amount){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "removeLastIndex", "");
						if(this->isEmpty()){
							return false;
						}
						int i_iteration = 0;
						for(int x = this->getLastIndex() - 1; x >= this->getLastIndex() - a_amount && x >= 0; x--){
							if(this->isOwner() && this->m_values[x] != nullptr){
								delete this->m_values[x];
							}
							this->m_values[x] = nullptr;
							i_iteration++;
						}
						if(!this->isInOrder()){
							ArrayRawPointerListLog(pankey_Log_EndMethod, "removeLastIndex", "!this->isInOrder()");
							return true;
						}
						this->decrementPosition(i_iteration);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "removeLastIndex", "");
						return true;
					}
					
					//resize length by adding more space
					//bug unkown for template = char on feather m0
					virtual void expand(int a_size){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "expand", "");
						
						int i_size = this->getSize() + a_size;
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Position:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->getLastIndex());
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
						nT = new T*[i_size];
						for(int x = 0; x < this->getLastIndex(); x++){
							ArrayRawPointerListLog(pankey_Log_Statement, "expand", "iteration:");
							ArrayRawPointerListLog(pankey_Log_Statement, "expand", x);
							nT[x] = this->m_values[x];
						}
						if(this->m_values != nullptr){
							ArrayRawPointerListLog(pankey_Log_Statement, "expand", "this->m_values != nullptr");
							delete[] this->m_values;
						}
						this->m_values = nT;
						this->setSize(i_size);
						
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Position:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->getLastIndex());
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", "List Size:");
						ArrayRawPointerListLog(pankey_Log_Statement, "expand", this->getSize());	
						ArrayRawPointerListLog(pankey_Log_EndMethod, "expand", "");
					}
					
					// virtual ArrayRawPointerList<T>* expand(int a_size){
					// 	ArrayRawPointerListLog(pankey_Log_StartMethod, "expand", "");
					// 	int i_size = this->getSize() + a_size;
					// 	ArrayRawPointerList<T> *i_list = new ArrayRawPointerList<T>(i_size, true, true);	
					// 	for(int x = 0; x < this->getLastIndex(); x++){
					// 		T* f_value = this->getByIndex(x);
					// 		i_list->addPointer(f_value);
					// 	}
					// 	ArrayRawPointerListLog(pankey_Log_EndMethod, "expand", "");
					// 	return i_list;
					// }

					virtual void reorder(){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "reoder", "");
						int i_offset = 0;
						for(int x = 0; x < this->getLastIndex(); x++){
							T* f_value = this->getByIndex(x);
							if(f_value == nullptr){
								continue;
							}
							this->m_values[i_offset] = f_value;
							i_offset++;
						}
						this->setLastIndex(i_offset);
						ArrayRawPointerListLog(pankey_Log_EndMethod, "reoder", "");
					}
				
					////////////////////////////////////////////operator part///////////////////////////////////////////////
					
					
					virtual ArrayRawPointerList& operator=(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "operator=", "const ArrayRawPointerList<T>&");
						this->clear();
						for(int x = 0; x < a_list.getLastIndex(); x++){
							T* f_value = a_list.getByIndex(x);
							this->addPointer(f_value);
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					virtual bool operator==(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "operator=", "const ArrayRawPointerList<T>&");
						if(a_list.getLastIndex() != this->getLastIndex()){
							return false;
						}
						for(int x = 0; x < a_list.getLastIndex(); x++){
							T* f_value_1 = a_list.getByIndex(x);
							T* f_value_2 = this->getByIndex(x);
							if(f_value_1 != f_value_2){
								return false;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "operator=", "const ArrayRawPointerList<T>&");
						return true;
					}

					virtual bool operator!=(const ArrayRawPointerList<T>& a_list){
						ArrayRawPointerListLog(pankey_Log_StartMethod, "operator=", "");
						if(a_list.getLastIndex() != this->getLastIndex()){
							return true;
						}
						for(int x = 0; x < a_list.getLastIndex(); x++){
							T* f_value_1 = a_list.getByIndex(x);
							T* f_value_2 = this->getByIndex(x);
							if(f_value_1 != f_value_2){
								return true;
							}
						}
						ArrayRawPointerListLog(pankey_Log_EndMethod, "operator=", "");
						return false;
					}
					
				protected:
					T** m_values = nullptr;
					int m_expandSize = 5;
			};

		}
		
	}

#endif