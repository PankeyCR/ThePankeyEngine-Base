
#ifndef ArrayPointer_hpp
	#define ArrayPointer_hpp

	#include "ArrayIterator.hpp"
	#include "Cast.hpp"
	#include "MemoryAllocator.hpp"

	#if defined(pankey_Log) && (defined(ArrayPointer_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayPointerLog(status,method,mns) pankey_Log(status,"ArrayPointer",method,mns)
	#else
		#define ArrayPointerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			class ArrayPointer{
				public:
					ArrayPointer(){
						ArrayPointerLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Constructor", "Default Constructor");
						ArrayPointerLog(pankey_Log_EndMethod, "Constructor", "");
					}

					ArrayPointer(MemoryAllocator* a_allocator){
						ArrayPointerLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Constructor", "MemoryAllocator*");
						this->m_allocator = setMemoryAllocator(a_allocator);
						ArrayPointerLog(pankey_Log_EndMethod, "Constructor", "");
					}

					ArrayPointer(const ArrayPointer<T>& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "Copy Constructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Copy Constructor", "const ArrayPointer&");
						this->m_allocator = setMemoryAllocator(a_values.m_allocator);
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_EndMethod, "Copy Constructor", "a_values.isEmpty()");
							return;
						}
						this->createArray(a_values.m_last_index);
						this->copy(a_values.m_t_value, a_values.m_last_index);
						ArrayPointerLog(pankey_Log_EndMethod, "Copy Constructor", "");
					}

					ArrayPointer(ArrayPointer<T>&& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "Constructor", "start");
						ArrayPointerLog(pankey_Log_Statement, "Constructor", "ArrayPointer&&");
						this->m_last_index = a_values.m_last_index;
						this->m_size = a_values.m_size;
						this->m_t_value = a_values.m_t_value;
						this->m_allocator = a_values.m_allocator;
						a_values.m_allocator = nullptr;
						a_values.m_t_value = nullptr;
						a_values.m_last_index = 0;
						a_values.m_size = 0;
						ArrayPointerLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~ArrayPointer(){
						ArrayPointerLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayPointerLog(pankey_Log_Statement, "Destructor", "~ArrayPointer");
						deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						destroyMemoryAllocator(this->m_allocator);
						ArrayPointerLog(pankey_Log_EndMethod, "Destructor", "");
					}

				protected:

					virtual void copy(T* a_array, int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "copy", "");
						if(this->m_t_value == nullptr || a_array == nullptr){
							ArrayPointerLog(pankey_Log_StartMethod, "copy", "this->m_t_value == nullptr || a_array == nullptr");
							return;
						}
						if(a_size > this->m_size){
							ArrayPointerLog(pankey_Log_EndMethod, "copy", "a_size > this->m_size");
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = a_array[x];
						}
						this->m_last_index = a_size;
						ArrayPointerLog(pankey_Log_EndMethod, "copy", "");
					}

					virtual void copyFast(T* a_array, int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "copyFast", "");
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = a_array[x];
						}
						ArrayPointerLog(pankey_Log_EndMethod, "copyFast", "");
					}

					virtual void move(T* a_array, int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "move", "");
						if(a_size > this->m_last_index || this->m_t_value == nullptr || a_array == nullptr){
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = pankey::Base::move(a_array[x]);
						}
						ArrayPointerLog(pankey_Log_EndMethod, "move", "");
					}

					virtual void moveFast(T* a_array, int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "moveFast", "");
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = pankey::Base::move(a_array[x]);
						}
						ArrayPointerLog(pankey_Log_EndMethod, "moveFast", "");
					}
				
				public:

					virtual T* getArrayPointer() const{
						ArrayPointerLog(pankey_Log_StartMethod, "getArrayPointer", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getArrayPointer", "");
						return this->m_t_value;
					}

					virtual void createArray(int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "createArray", "");
						ArrayPointerLog(pankey_Log_Statement, "createArray", "size:");
						ArrayPointerLog(pankey_Log_Statement, "createArray", a_size);
						deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						this->m_t_value = allocateArray<T>(this->m_allocator, a_size);
						ArrayPointerLog(pankey_Log_Statement, "createArray", "is new Array is null:");
						ArrayPointerLog(pankey_Log_Statement, "createArray", this->m_t_value == nullptr);
						this->m_last_index = 0;
						this->m_size = a_size;
						ArrayPointerLog(pankey_Log_EndMethod, "createArray", "");
					}

					virtual void createArrayFast(int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "createArrayFast", "");
						this->m_t_value = allocateArray<T>(m_allocator, a_size);
						this->m_last_index = 0;
						this->m_size = a_size;
						ArrayPointerLog(pankey_Log_EndMethod, "createArrayFast", "");
					}

					virtual void expand(int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "expand", "");
						int i_size = this->m_size + a_size;
						ArrayPointerLog(pankey_Log_Statement, "expand", "initial size:");
						ArrayPointerLog(pankey_Log_Statement, "expand", this->m_size);
						ArrayPointerLog(pankey_Log_Statement, "expand", "requested extra size:");
						ArrayPointerLog(pankey_Log_Statement, "expand", a_size);
						ArrayPointerLog(pankey_Log_Statement, "expand", "applied new size:");
						ArrayPointerLog(pankey_Log_Statement, "expand", i_size);
						ArrayPointerLog(pankey_Log_Statement, "expand", "last index:");
						ArrayPointerLog(pankey_Log_Statement, "expand", this->m_last_index);
						T *nT = allocateArray<T>(this->m_allocator, i_size);
						for(int x = 0; x < this->m_last_index; x++){
							nT[x] = pankey::Base::move(this->m_t_value[x]);
						}
						if(this->m_t_value != nullptr){
							ArrayPointerLog(pankey_Log_Statement, "expand", "this->m_t_value != nullptr");
							deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						}
						this->m_t_value = nT;
						this->m_size = i_size;
						ArrayPointerLog(pankey_Log_EndMethod, "expand", "");
					}

					virtual void shrink(int a_size){
						ArrayPointerLog(pankey_Log_StartMethod, "shrink", "");
						int i_size = this->m_size - a_size;
						T *nT = allocateArray<T>(m_allocator, i_size);
						for(int x = 0; x < this->m_last_index && x < i_size; x++){
							nT[x] = pankey::Base::move(this->m_t_value[x]);
						}
						if(this->m_t_value != nullptr){
							ArrayPointerLog(pankey_Log_Statement, "shrink", "this->m_t_value != nullptr");
							deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						}
						this->m_t_value = nT;
						this->m_size = i_size;
						if(this->m_last_index > i_size){
							this->m_last_index = i_size;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "shrink", "");
					}

					virtual void clear(){
						ArrayPointerLog(pankey_Log_StartMethod, "clear", "");
						if(this->m_t_value == nullptr){
							this->m_last_index = 0;
							this->m_size = 0;
							ArrayPointerLog(pankey_Log_EndMethod, "clear", "this->m_t_value == nullptr");
							return;
						}
						deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						this->m_t_value = nullptr;
						this->m_last_index = 0;
						this->m_size = 0;
						ArrayPointerLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void reset(){
						ArrayPointerLog(pankey_Log_StartMethod, "reset", "");
						this->m_last_index = 0;
						ArrayPointerLog(pankey_Log_EndMethod, "reset", "");
					}

					virtual bool isEmpty() const{
						ArrayPointerLog(pankey_Log_StartMethod, "isEmpty", "");
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", "this->m_last_index == 0");
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", this->m_last_index == 0);
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", "this->m_t_value == nullptr");
						ArrayPointerLog(pankey_Log_Statement, "isEmpty", this->m_t_value == nullptr);
						ArrayPointerLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->m_last_index == 0 || this->m_t_value == nullptr;
					}

					virtual int getSize() const{
						ArrayPointerLog(pankey_Log_StartMethod, "getSize", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getSize", "");
						return this->m_size;
					}

					virtual void setLastIndex(int a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "setLastIndex", "");
						this->m_last_index = a_index;
						ArrayPointerLog(pankey_Log_EndMethod, "setLastIndex", "");
					}

					virtual int getLastIndex() const{
						ArrayPointerLog(pankey_Log_StartMethod, "getLastIndex", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getLastIndex", "");
						return this->m_last_index;
					}

					virtual void setLength(int a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "setLength", "");
						this->m_last_index = a_index;
						ArrayPointerLog(pankey_Log_EndMethod, "setLength", "");
					}

					virtual int length() const{
						ArrayPointerLog(pankey_Log_StartMethod, "length", "");
						ArrayPointerLog(pankey_Log_EndMethod, "length", "");
						return this->m_last_index;
					}

					virtual int getAvailableSpace() const{
						ArrayPointerLog(pankey_Log_StartMethod, "length", "");
						ArrayPointerLog(pankey_Log_EndMethod, "length", "");
						return this->m_size - this->m_last_index;
					}

					virtual bool add(const T& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "add", "const T&");
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "add", "expanding");
							this->expand(this->m_expandSize);
						}
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						this->m_t_value[this->m_last_index] = a_value;
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					virtual bool add(T&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "add", "T&&");
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "add", "expanding");
							this->expand(this->m_expandSize);
						}
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						this->m_t_value[this->m_last_index] = pankey::Base::move(a_value);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					virtual bool add(const ArrayPointer<T>& a_array){
						ArrayPointerLog(pankey_Log_StartMethod, "add", "const T&");
						if(a_array.isEmpty()){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "a_array.isEmpty()");
							return false;
						}
						if(this->getAvailableSpace() < a_array.length() || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "add", "expanding");
							this->expand(a_array.length());
						}
						if(this->getAvailableSpace() < a_array.length() || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						for(int x = 0; x < a_array.length(); x++){
							this->m_t_value[this->m_last_index] = a_array.get(x);
							this->m_last_index++;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					virtual void addFast(const T& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "addFast", "");
						this->m_t_value[this->m_last_index] = a_value;
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "addFast", "");
					}

					virtual void addFast(T&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "addFast", "");
						this->m_t_value[this->m_last_index] = pankey::Base::move(a_value);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "addFast", "");
					}

					virtual bool set(int a_index, const T& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "set", "");
						if(a_index < 0 || a_index >= this->m_size || this->m_t_value == nullptr){
							return false;
						}
						this->m_t_value[a_index] = a_value;
						if(a_index == this->m_last_index){
							this->m_last_index++;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual bool set(int a_index, T&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "set", "");
						if(a_index < 0 || a_index >= this->m_size || this->m_t_value == nullptr){
							return false;
						}
						this->m_t_value[a_index] = pankey::Base::move(a_value);
						if(a_index == this->m_last_index){
							this->m_last_index++;
						}
						ArrayPointerLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual void setFast(int a_index, const T& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "setFast", "");
						this->m_t_value[a_index] = a_value;
						ArrayPointerLog(pankey_Log_EndMethod, "setFast", "");
					}

					virtual void setFast(int a_index, T&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "setFast", "");
						this->m_t_value[a_index] = pankey::Base::move(a_value);
						ArrayPointerLog(pankey_Log_EndMethod, "setFast", "");
					}

					virtual bool insert(int a_index, const T& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insert", "");
						ArrayPointerLog(pankey_Log_Statement, "insert", "insert index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", a_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "last index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_last_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "size:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_size);
						if(a_index < 0){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index < 0");
							return false;
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "insert", "expanding");
							if(a_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "a_index >= this->m_size");
								this->expand(this->m_expandSize + (this->m_size - a_index));
							}
							if(this->m_last_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "this->m_last_index >= this->m_size");
								this->expand(this->m_expandSize);
							}
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "no more space");
							return false;
						}
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index == this->m_last_index");
							return true;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index > this->m_last_index");
							return true;
						}
						T i_retain = a_value;
						for(int x = a_index; x < this->m_last_index; x++){
							// ArrayPointerLog(pankey_Log_Statement, "insert", "interation:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", x);
							T f_retain = pankey::Base::move(this->m_t_value[x]);
							// ArrayPointerLog(pankey_Log_Statement, "insert", "f_retain:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", f_retain);
							this->m_t_value[x] = pankey::Base::move(i_retain);
							// ArrayPointerLog(pankey_Log_Statement, "insert", "this->m_t_value[x]:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", this->m_t_value[x]);
							i_retain = pankey::Base::move(f_retain);
							// ArrayPointerLog(pankey_Log_Statement, "insert", "i_retain:");
							// ArrayPointerLog(pankey_Log_Statement, "insert", i_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insert", "insert done");
						return true;
					}

					virtual bool insert(int a_index, T&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insert", "");
						ArrayPointerLog(pankey_Log_Statement, "insert", "insert index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", a_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "last index:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_last_index);
						ArrayPointerLog(pankey_Log_Statement, "insert", "size:");
						ArrayPointerLog(pankey_Log_Statement, "insert", this->m_size);
						if(a_index < 0){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index < 0");
							return false;
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_Statement, "insert", "expanding");
							if(a_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "a_index >= this->m_size");
								this->expand(this->m_expandSize + (this->m_size - a_index));
							}
							if(this->m_last_index >= this->m_size){
								ArrayPointerLog(pankey_Log_Statement, "insert", "this->m_last_index >= this->m_size");
								this->expand(this->m_expandSize);
							}
						}
						if(a_index >= this->m_size || this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "no more space");
							return false;
						}
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index == this->m_last_index");
							return true;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insert", "a_index > this->m_last_index");
							return true;
						}
						T i_retain = pankey::Base::move(a_value);
						for(int x = a_index; x < this->m_last_index; x++){
							T f_retain = pankey::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Base::move(i_retain);
							i_retain = pankey::Base::move(f_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insert", "insert done");
						return true;
					}

					virtual void insertFast(int a_index, const T& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insertFast", "");
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index == this->m_last_index");
							return;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index > this->m_last_index");
							return;
						}
						T i_retain = a_value;
						for(int x = a_index; x < this->m_last_index; x++){
							T f_retain = pankey::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Base::move(i_retain);
							i_retain = pankey::Base::move(f_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "");
					}

					virtual void insertFast(int a_index, T&& a_value){
						ArrayPointerLog(pankey_Log_StartMethod, "insertFast", "");
						if(a_index == this->m_last_index){
							this->m_t_value[this->m_last_index] = a_value;
							this->m_last_index++;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index == this->m_last_index");
							return;
						}
						if(a_index > this->m_last_index){
							this->m_t_value[a_index] = a_value;
							ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "a_index > this->m_last_index");
							return;
						}
						T i_retain = pankey::Base::move(a_value);
						for(int x = a_index; x < this->m_last_index; x++){
							T f_retain = pankey::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Base::move(i_retain);
							i_retain = pankey::Base::move(f_retain);
						}
						this->m_t_value[this->m_last_index] = pankey::Base::move(i_retain);
						this->m_last_index++;
						ArrayPointerLog(pankey_Log_EndMethod, "insertFast", "");
					}

					virtual T get(int x) const{
						ArrayPointerLog(pankey_Log_StartMethod, "get", "");
						if(this->m_t_value == nullptr){
							ArrayPointerLog(pankey_Log_EndMethod, "get", "");
							return T();
						}
						if(x < this->m_last_index){
							ArrayPointerLog(pankey_Log_EndMethod, "get", "");
							return this->m_t_value[x];
						}
						ArrayPointerLog(pankey_Log_EndMethod, "get", "");
						return T();
					}

					virtual T getFast(int x) const{
						ArrayPointerLog(pankey_Log_StartMethod, "getFast", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getFast", "");
						return this->m_t_value[x];
					}

					virtual T&& getMove(int x) const{
						ArrayPointerLog(pankey_Log_StartMethod, "getMove", "");
						ArrayPointerLog(pankey_Log_EndMethod, "getMove", "");
						return pankey::Base::move(this->m_t_value[x]);
					}

					virtual T remove(int a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "remove", "");
						
						ArrayPointerLog(pankey_Log_EndMethod, "remove", "");
						return T();
					}

					virtual T removeFast(int a_index){
						ArrayPointerLog(pankey_Log_StartMethod, "removeFast", "");
						
						ArrayPointerLog(pankey_Log_EndMethod, "removeFast", "");
						return T();
					}

					virtual void operator=(const ArrayPointer<T>& a_values){
						ArrayPointerLog(pankey_Log_StartMethod, "operator=", "");
						ArrayPointerLog(pankey_Log_Statement, "operator=", "const ArrayPointer&");
						this->m_allocator = setMemoryAllocator(this->m_allocator, a_values.m_allocator);
						this->clear();
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_EndMethod, "operator=", "a_values.isEmpty()");
							return;
						}
						this->createArray(a_values.m_last_index);
						this->copy(a_values.m_t_value, a_values.m_last_index);
						ArrayPointerLog(pankey_Log_EndMethod, "operator=", "");
					}

					virtual bool operator==(const ArrayPointer<T>& a_values)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator==", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator==", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
							return true;
						}
						if(this->length() != a_values.length()){
							ArrayPointerLog(pankey_Log_Statement, "operator==", "this->length() != a_values.length()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
							return false;
						}
						for(int x = 0; x < this->length(); x++){
							T& f_value_1 = m_t_value[x];
							T& f_value_2 = a_values.m_t_value[x];
							if(f_value_1 != f_value_2){
								ArrayPointerLog(pankey_Log_Statement, "operator==", "f_value_1 != f_value_2");
								ArrayPointerLog(pankey_Log_Statement, "operator==", "iteration:");
								ArrayPointerLog(pankey_Log_Statement, "operator==", x);
								ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
								return false;
							}
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					virtual bool operator!=(const ArrayPointer<T>& a_values)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return false;
						}
						if(this->length() != a_values.length()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->length() != a_values.length()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return true;
						}
						for(int x = 0; x < this->length(); x++){
							T& f_value_1 = m_t_value[x];
							T& f_value_2 = a_values.m_t_value[x];
							if(f_value_1 != f_value_2){
								ArrayPointerLog(pankey_Log_Statement, "operator!=", "f_value_1 != f_value_2");
								ArrayPointerLog(pankey_Log_Statement, "operator!=", "iteration:");
								ArrayPointerLog(pankey_Log_Statement, "operator!=", x);
								ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
								return true;
							}
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}

					virtual ArrayPointer<T> operator+(const ArrayPointer<T>& a_values)const{
						ArrayPointerLog(pankey_Log_StartMethod, "operator!=", "");
						if(this->isEmpty() && a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return ArrayPointer<T>();
						}
						if(this->isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return *this;
						}
						if(a_values.isEmpty()){
							ArrayPointerLog(pankey_Log_Statement, "operator!=", "this->isEmpty() == a_values.isEmpty()");
							ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
							return ArrayPointer<T>(a_values);
						}
						ArrayPointer<T> i_sum;
						i_sum.createArrayFast(this->length() + a_values.length());
						for(int x = 0; x < this->length(); x++){
							i_sum.addFast(this->getFast(x));
						}
						for(int x = 0; x < a_values.length(); x++){
							i_sum.addFast(a_values.getFast(x));
						}
						ArrayPointerLog(pankey_Log_EndMethod, "operator!=", "");
						return i_sum;
					}

				protected:
					MemoryAllocator* m_allocator = nullptr;
					T* m_t_value = nullptr;
					int m_last_index = 0;
					int m_size = 0;
					int m_expandSize = 5;
			};

			template<class T, class... Args>
			ArrayPointer<T> createArrayPointer(Args... a_args){
				T i_values[] = { static_cast<T>(a_args)... };
				ArrayPointer<T> i_array;
				for(const auto& f_value : i_values){
					i_array.add(f_value);
				}
				return i_array;
			}

		}

	}

#endif



