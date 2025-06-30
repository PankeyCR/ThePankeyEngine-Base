
#ifndef Array_hpp
	#define Array_hpp

	#include "ArrayIterator.hpp"
	#include "Cast.hpp"
	#include "MemoryAllocator.hpp"
	#include "ArrayPointer.hpp"

	#if defined(pankey_Log) && (defined(Array_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayLog(status,method,mns) pankey_Log(status,"Array",method,mns)
	#else
		#define ArrayLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class T>
			class Array{
				public:
					Array(){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayLog(pankey_Log_Statement, "Constructor", "Default Constructor");
						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					Array(MemoryAllocator* a_allocator){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayLog(pankey_Log_Statement, "Constructor", "MemoryAllocator*");
						this->m_allocator = setMemoryAllocator(a_allocator);
						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					Array(const Array<T>& a_values){
						ArrayLog(pankey_Log_StartMethod, "Copy Constructor", "");
						ArrayLog(pankey_Log_Statement, "Copy Constructor", "const Array&");
						this->m_allocator = setMemoryAllocator(a_values.m_allocator);
						if(a_values.isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "Copy Constructor", "a_values.isEmpty()");
							return;
						}
						this->createArray(a_values.m_last_index);
						this->copy(a_values.m_t_value, a_values.m_last_index);
						ArrayLog(pankey_Log_EndMethod, "Copy Constructor", "");
					}

					Array(Array<T>&& a_values){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "start");
						ArrayLog(pankey_Log_Statement, "Constructor", "Array&&");
						this->m_last_index = a_values.m_last_index;
						this->m_size = a_values.m_size;
						this->m_t_value = a_values.m_t_value;
						this->m_allocator = a_values.m_allocator;
						a_values.m_allocator = nullptr;
						a_values.m_t_value = nullptr;
						a_values.m_last_index = 0;
						a_values.m_size = 0;
						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~Array(){
						ArrayLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayLog(pankey_Log_EndMethod, "Destructor", "");
					}

				protected:

					virtual void copy(T* a_array, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copy", "");
						if(this->m_t_value == nullptr || a_array == nullptr){
							ArrayLog(pankey_Log_StartMethod, "copy", "this->m_t_value == nullptr || a_array == nullptr");
							return;
						}
						if(this->m_last_index > a_size){
							ArrayLog(pankey_Log_StartMethod, "copy", "this->m_last_index > a_size");
							return;
						}
						if(a_size > this->m_size){
							ArrayLog(pankey_Log_StartMethod, "copy", "a_size > this->m_size");
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = a_array[x];
						}
						this->m_last_index = a_size;
						ArrayLog(pankey_Log_EndMethod, "copy", "");
					}

					virtual void copyFast(T* a_array, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyFast", "");
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = a_array[x];
						}
						ArrayLog(pankey_Log_EndMethod, "copyFast", "");
					}

					virtual void move(T* a_array, int a_size){
						ArrayLog(pankey_Log_StartMethod, "move", "");
						if(a_size > this->m_last_index || this->m_t_value == nullptr || a_array == nullptr){
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = pankey::Base::move(a_array[x]);
						}
						ArrayLog(pankey_Log_EndMethod, "move", "");
					}

					virtual void moveFast(T* a_array, int a_size){
						ArrayLog(pankey_Log_StartMethod, "moveFast", "");
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x] = pankey::Base::move(a_array[x]);
						}
						ArrayLog(pankey_Log_EndMethod, "moveFast", "");
					}
				
				public:

					virtual void setEndValue(T a_value){}
					virtual T getEndValue()const{return T();}

					virtual void enableEndValue(){}
					virtual void disableEndValue(){}

					virtual bool hasEndValue()const{
						return false;
					}

					virtual T* getArray() const{
						ArrayLog(pankey_Log_StartMethod, "getArray", "");
						ArrayLog(pankey_Log_EndMethod, "getArray", "");
						return this->m_t_value;
					}

					virtual void createArray(int a_size){
						ArrayLog(pankey_Log_StartMethod, "createArray", "");
						ArrayLog(pankey_Log_Statement, "createArray", "size:");
						ArrayLog(pankey_Log_Statement, "createArray", a_size);
						deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						this->m_t_value = allocateArray<T>(this->m_allocator, a_size);
						ArrayLog(pankey_Log_Statement, "createArray", "is new Array is null:");
						ArrayLog(pankey_Log_Statement, "createArray", this->m_t_value == nullptr);
						this->m_last_index = 0;
						this->m_size = a_size;
						ArrayLog(pankey_Log_EndMethod, "createArray", "");
					}

					virtual void createArrayFast(int a_size){
						ArrayLog(pankey_Log_StartMethod, "createArrayFast", "");
						this->m_t_value = allocateArray<T>(m_allocator, a_size);
						this->m_last_index = 0;
						this->m_size = a_size;
						ArrayLog(pankey_Log_EndMethod, "createArrayFast", "");
					}

					virtual void expand(int a_size){
						ArrayLog(pankey_Log_StartMethod, "expand", "");
						int i_size = this->m_size + a_size;
						T *nT = allocateArray<T>(this->m_allocator, i_size);
						for(int x = 0; x < this->m_last_index; x++){
							nT[x] = pankey::Base::move(this->m_t_value[x]);
						}
						if(this->m_t_value != nullptr){
							ArrayLog(pankey_Log_Statement, "expand", "this->m_t_value != nullptr");
							deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						}
						this->m_t_value = nT;
						this->m_size = i_size;
						ArrayLog(pankey_Log_EndMethod, "expand", "");
					}

					virtual void shrink(int a_size){
						ArrayLog(pankey_Log_StartMethod, "shrink", "");
						int i_size = this->m_size - a_size;
						T *nT = allocateArray<T>(m_allocator, i_size);
						for(int x = 0; x < this->m_last_index && x < i_size; x++){
							nT[x] = pankey::Base::move(this->m_t_value[x]);
						}
						if(this->m_t_value != nullptr){
							ArrayLog(pankey_Log_Statement, "shrink", "this->m_t_value != nullptr");
							deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						}
						this->m_t_value = nT;
						this->m_size = i_size;
						if(this->m_last_index > i_size){
							this->m_last_index = i_size;
						}
						ArrayLog(pankey_Log_EndMethod, "shrink", "");
					}

					virtual void clear(){
						ArrayLog(pankey_Log_StartMethod, "clear", "");
						if(this->m_t_value == nullptr){
							this->m_last_index = 0;
							this->m_size = 0;
							ArrayLog(pankey_Log_EndMethod, "clear", "this->m_t_value == nullptr");
							return;
						}
						deallocateArray<T>(this->m_allocator, this->m_size, this->m_t_value);
						this->m_t_value = nullptr;
						this->m_last_index = 0;
						this->m_size = 0;
						ArrayLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void reset(){
						ArrayLog(pankey_Log_StartMethod, "reset", "");
						this->m_last_index = 0;
						ArrayLog(pankey_Log_EndMethod, "reset", "");
					}

					virtual bool isEmpty() const{
						ArrayLog(pankey_Log_StartMethod, "isEmpty", "");
						ArrayLog(pankey_Log_Statement, "isEmpty", "this->m_last_index == 0");
						ArrayLog(pankey_Log_Statement, "isEmpty", this->m_last_index == 0);
						ArrayLog(pankey_Log_Statement, "isEmpty", "this->m_t_value == nullptr");
						ArrayLog(pankey_Log_Statement, "isEmpty", this->m_t_value == nullptr);
						ArrayLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->m_last_index == 0 || this->m_t_value == nullptr;
					}

					virtual int getSize() const{
						ArrayLog(pankey_Log_StartMethod, "getSize", "");
						ArrayLog(pankey_Log_EndMethod, "getSize", "");
						return this->m_size;
					}

					virtual void setLastIndex(int a_index){
						ArrayLog(pankey_Log_StartMethod, "setLastIndex", "");
						this->m_last_index = a_index;
						ArrayLog(pankey_Log_EndMethod, "setLastIndex", "");
					}

					virtual int getLastIndex() const{
						ArrayLog(pankey_Log_StartMethod, "getLastIndex", "");
						ArrayLog(pankey_Log_EndMethod, "getLastIndex", "");
						return this->m_last_index;
					}

					virtual void setLength(int a_index){
						ArrayLog(pankey_Log_StartMethod, "setLength", "");
						this->m_last_index = a_index;
						ArrayLog(pankey_Log_EndMethod, "setLength", "");
					}

					virtual int length() const{
						ArrayLog(pankey_Log_StartMethod, "length", "");
						if(this->hasEndValue() && this->m_last_index == 0){
							return 0;
						}
						if(this->hasEndValue() && this->m_last_index > 1){
							return this->m_last_index - 1;
						}

						// pankey_Trigger_Error_Alert(this->m_last_index == 1, pankey_Error_BadPathOnLogic);

						ArrayLog(pankey_Log_EndMethod, "length", "");
						return this->m_last_index;
					}

					virtual bool add(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "add", "const T&");
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayLog(pankey_Log_Statement, "add", "expanding");
							this->expand(this->m_expandSize);
						}
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						if(this->hasEndValue()){
							this->m_t_value[this->length()] = a_value;
							this->m_last_index++;
							this->m_t_value[this->m_last_index] = this->getEndValue();
							this->m_last_index++;
							ArrayLog(pankey_Log_EndMethod, "add", "this->hasEndValue()");
							return true;
						}
						this->m_t_value[this->m_last_index] = a_value;
						this->m_last_index++;
						ArrayLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					virtual bool add(T&& a_value){
						ArrayLog(pankey_Log_StartMethod, "add", "T&&");
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayLog(pankey_Log_Statement, "add", "expanding");
							this->expand(this->m_expandSize);
						}
						if(this->m_last_index >= this->m_size || this->m_t_value == nullptr){
							ArrayLog(pankey_Log_EndMethod, "add", "no more space");
							return false;
						}
						this->m_t_value[this->m_last_index] = pankey::Base::move(a_value);
						this->m_last_index++;
						ArrayLog(pankey_Log_EndMethod, "add", "");
						return true;
					}

					virtual bool addFast(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "addFast", "");
						this->m_t_value[this->m_last_index] = a_value;
						this->m_last_index++;
						ArrayLog(pankey_Log_EndMethod, "addFast", "");
						return true;
					}

					virtual void addFast(T&& a_value){
						ArrayLog(pankey_Log_StartMethod, "addFast", "");
						this->m_t_value[this->m_last_index] = pankey::Base::move(a_value);
						this->m_last_index++;
						ArrayLog(pankey_Log_EndMethod, "addFast", "");
					}

					virtual bool set(int a_index, const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "set", "");
						if(a_index >= this->m_size || this->m_t_value == nullptr){
							return false;
						}
						this->m_t_value[a_index] = a_value;
						if(a_index == this->m_last_index){
							this->m_last_index++;
						}
						ArrayLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual bool set(int a_index, T&& a_value){
						ArrayLog(pankey_Log_StartMethod, "set", "");
						if(a_index >= this->m_size || this->m_t_value == nullptr){
							return false;
						}
						this->m_t_value[a_index] = pankey::Base::move(a_value);
						if(a_index == this->m_last_index){
							this->m_last_index++;
						}
						ArrayLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual void setFast(int a_index, const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "setFast", "");
						this->m_t_value[a_index] = a_value;
						ArrayLog(pankey_Log_EndMethod, "setFast", "");
					}

					virtual void setFast(int a_index, T&& a_value){
						ArrayLog(pankey_Log_StartMethod, "setFast", "");
						this->m_t_value[a_index] = pankey::Base::move(a_value);
						ArrayLog(pankey_Log_EndMethod, "setFast", "");
					}

					virtual bool insert(int a_index, const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "insert", "");
						if(a_index >= this->m_size || this->m_t_value == nullptr){
							ArrayLog(pankey_Log_Statement, "insert", "expanding");
							this->expand(this->m_expandSize);
						}
						if(a_index >= this->m_size || this->m_t_value == nullptr){
							ArrayLog(pankey_Log_EndMethod, "insert", "no more space");
							return false;
						}
						T i_retain = a_value;
						for(int x = a_index; x < this->m_last_index; x++){
							T&& f_retain = pankey::Base::move(this->m_t_value[x]);
							this->m_t_value[x] = pankey::Base::move(i_retain);
							i_retain = pankey::Base::move(f_retain);
						}
						this->m_last_index++;
						ArrayLog(pankey_Log_EndMethod, "insert", "");
						return true;
					}

					virtual bool insert(int a_index, T&& a_value){
						ArrayLog(pankey_Log_StartMethod, "insert", "");
						
						ArrayLog(pankey_Log_EndMethod, "insert", "");
						return true;
					}

					virtual void insertFast(int a_index, const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "insertFast", "");
						
						ArrayLog(pankey_Log_EndMethod, "insertFast", "");
					}

					virtual void insertFast(int a_index, T&& a_value){
						ArrayLog(pankey_Log_StartMethod, "insertFast", "");
						
						ArrayLog(pankey_Log_EndMethod, "insertFast", "");
					}

					virtual T get(int x) const{
						ArrayLog(pankey_Log_StartMethod, "get", "");
						if(this->m_t_value == nullptr){
							ArrayLog(pankey_Log_EndMethod, "get", "");
							return T();
						}
						if(x < this->m_last_index){
							ArrayLog(pankey_Log_EndMethod, "get", "");
							return this->m_t_value[x];
						}
						ArrayLog(pankey_Log_EndMethod, "get", "");
						return T();
					}

					virtual T getFast(int x) const{
						ArrayLog(pankey_Log_StartMethod, "getFast", "");
						ArrayLog(pankey_Log_EndMethod, "getFast", "");
						return this->m_t_value[x];
					}

					virtual T&& getMove(int x) const{
						ArrayLog(pankey_Log_StartMethod, "getMove", "");
						ArrayLog(pankey_Log_EndMethod, "getMove", "");
						return pankey::Base::move(this->m_t_value[x]);
					}

					virtual T remove(int a_index){
						ArrayLog(pankey_Log_StartMethod, "remove", "");
						
						ArrayLog(pankey_Log_EndMethod, "remove", "");
						return T();
					}

					virtual T removeFast(int a_index){
						ArrayLog(pankey_Log_StartMethod, "removeFast", "");
						
						ArrayLog(pankey_Log_EndMethod, "removeFast", "");
						return T();
					}

					virtual void operator=(const Array<T>& a_values){
						ArrayLog(pankey_Log_StartMethod, "operator=", "");
						ArrayLog(pankey_Log_Statement, "operator=", "const Array&");
						this->m_allocator = setMemoryAllocator(this->m_allocator, a_values.m_allocator);
						this->clear();
						if(a_values.isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "operator=", "a_values.isEmpty()");
							return;
						}
						this->createArray(a_values.m_last_index);
						this->copy(a_values.m_t_value, a_values.m_last_index);
						ArrayLog(pankey_Log_EndMethod, "operator=", "");
					}

					virtual bool operator==(const Array<T>& a_values){
						ArrayLog(pankey_Log_StartMethod, "operator=", "");
						if(this->length() != a_values.length()){
							return false;
						}
						for(int x = 0; x < this->length(); x++){
							T& f_value_1 = m_t_value[x];
							T& f_value_2 = a_values.m_t_value[x];
							if(f_value_1 != f_value_2){
								return false;
							}
						}
						ArrayLog(pankey_Log_EndMethod, "operator=", "");
						return true;
					}

					virtual bool operator!=(const Array<T>& a_values){
						ArrayLog(pankey_Log_StartMethod, "operator=", "");
						if(this->length() != a_values.length()){
							return true;
						}
						for(int x = 0; x < this->length(); x++){
							T& f_value_1 = m_t_value[x];
							T& f_value_2 = a_values.m_t_value[x];
							if(f_value_1 != f_value_2){
								return true;
							}
						}
						ArrayLog(pankey_Log_EndMethod, "operator=", "");
						return false;
					}

				protected:
					MemoryAllocator* m_allocator = nullptr;
					T* m_t_value = nullptr;
					int m_last_index = 0;
					int m_size = 0;
					int m_expandSize = 5;
			};

			template<class T, class... Args>
			Array<T> createArray(Args... a_args){
				T i_values[] = { static_cast<T>(a_args)... };
				Array<T> i_array;
				for(const auto& f_value : i_values){
					i_array.add(f_value);
				}
				return i_array;
			}

		}

	}

#endif








