
#ifndef Array_hpp
	#define Array_hpp

	#include "ArrayIterator.hpp"
	#include "Cast.hpp"
	#include "MemoryAllocator.hpp"

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

				protected:
					T* m_t_value = nullptr;
					int m_pos = 0;
					int m_size = 0;
					int m_expandSize = 0;
					MemoryAllocator* m_allocator = nullptr;

				public:
					Array(){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayLog(pankey_Log_Statement, "Constructor", "Default Constructor");
						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					template<class... args>
					Array(args... xs){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "args... xs");
						T array1[] = {xs...};
						int i_array_length = 0;
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
						ArrayLog(pankey_Log_Statement, "Constructor", i_array_length);
						for(const T& a : array1){
						i_array_length++;
						}
						if(i_array_length != 0){
							T* c_pointer = this->createFilledArray(i_array_length);
							int count = 0;
							if(c_pointer != nullptr){
								for(const T& a : array1){
									c_pointer[count] = a;
									count++;
								}
							}
						}
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						ArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						ArrayLog(pankey_Log_Statement, "Constructor", this->getSize());

						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					Array(const Array<T>& c_array){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "");
						ArrayLog(pankey_Log_Statement, "Constructor", "const Array& val");
						if(c_array.m_allocator != nullptr){
							if(c_array.m_allocator->isManaged()){
								m_allocator = c_array.m_allocator->clone();
								m_allocator->isManaged(true);
							}else{
								m_allocator = c_array.m_allocator;
							}
						}
						if(c_array.isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "Constructor", "c_array.isEmpty()");
							return;
						}
						int i_array_length = c_array.getPosition();
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
						ArrayLog(pankey_Log_Statement, "Constructor", i_array_length);
						this->createArray(i_array_length);
						this->copyPointer(c_array.pointer(), i_array_length);
						this->copyEndValue();
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						ArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						ArrayLog(pankey_Log_Statement, "Constructor", this->getSize());

						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					Array(Array<T>&& c_array){
						ArrayLog(pankey_Log_StartMethod, "Constructor", "start");
						ArrayLog(pankey_Log_Statement, "Constructor", "Array&& c_array");
						int i_array_length = c_array.getPosition();
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Length:");
						ArrayLog(pankey_Log_Statement, "Constructor", i_array_length);
						this->m_pos = c_array.m_pos;
						this->m_size = c_array.m_size;
						this->m_t_value = c_array.m_t_value;
						this->m_allocator = c_array.m_allocator;
						c_array.m_allocator = nullptr;
						c_array.m_t_value = nullptr;
						c_array.m_pos = 0;
						c_array.m_size = 0;
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Position:");
						ArrayLog(pankey_Log_Statement, "Constructor", this->getPosition());
						ArrayLog(pankey_Log_Statement, "Constructor", "Array Size:");
						ArrayLog(pankey_Log_Statement, "Constructor", this->getSize());

						ArrayLog(pankey_Log_EndMethod, "Constructor", "");
					}

					virtual ~Array(){
						ArrayLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayLog(pankey_Log_Statement, "Destructor", "~Array");
						ArrayLog(pankey_Log_Statement, "Destructor", this->getPosition());
						ArrayLog(pankey_Log_Statement, "Destructor", this->getSize());
						this->fix();
						this->erase();
						this->destroyAllocator();
						ArrayLog(pankey_Log_EndMethod, "Destructor", "");
					}

				protected:

					virtual void expandIfNeeded(int a_array_length){
						ArrayLog(pankey_Log_StartMethod, "expandIfNeeded", "");
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", "Array Position:");
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", this->getPosition());
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", "Array Size:");
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", this->getSize());
						if(this->hasReachedFixSize()){
							return;
						}
						int i_availableSize = this->getFreeSpace();
						if(i_availableSize < a_array_length){
							this->expandLocal(a_array_length + m_expandSize);
						}
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", "Array Position:");
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", this->getPosition());
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", "Array Size:");
						ArrayLog(pankey_Log_Statement, "expandIfNeeded", this->getSize());
						ArrayLog(pankey_Log_EndMethod, "expandIfNeeded", "");
					}

					virtual bool hasEndValue()const{
						ArrayLog(pankey_Log_StartMethod, "endValue", "");
						ArrayLog(pankey_Log_EndMethod, "endValue", "");
						return false;
					}

					virtual T endValue()const{
						ArrayLog(pankey_Log_StartMethod, "endValue", "");
						ArrayLog(pankey_Log_EndMethod, "endValue", "");
						return T();
					}

					virtual void copyEndValue()const{
						ArrayLog(pankey_Log_StartMethod, "copyEndValue", "");
						if(this->isEmpty() || !this->hasEndValue()){
							ArrayLog(pankey_Log_EndMethod, "copyEndValue", "");
							return;
						}
						if(this->getPosition() >= this->getSize()){
							ArrayLog(pankey_Log_EndMethod, "copyEndValue", "");
							return;
						}
						this->m_t_value[this->getPosition()] = this->endValue();
						ArrayLog(pankey_Log_EndMethod, "copyEndValue", "");
					}

					virtual void copyEndValue(int a_position)const{
						ArrayLog(pankey_Log_StartMethod, "copyEndValue", "");
						if(this->isEmpty() || !this->hasEndValue()){
							ArrayLog(pankey_Log_EndMethod, "copyEndValue", "");
							return;
						}
						if(a_position >= this->getSize()){
							ArrayLog(pankey_Log_EndMethod, "copyEndValue", "");
							return;
						}
						this->m_t_value[a_position] = this->endValue();
						ArrayLog(pankey_Log_EndMethod, "copyEndValue", "");
					}

					virtual void copyExternEndValue(T* a_arrray, int a_position)const{
						ArrayLog(pankey_Log_StartMethod, "copyExternEndValue", "");
						ArrayLog(pankey_Log_Statement, "copyExternEndValue", "position ");
						ArrayLog(pankey_Log_Statement, "copyExternEndValue", a_position);
						if(a_arrray == nullptr || !this->hasEndValue()){
							ArrayLog(pankey_Log_EndMethod, "copyExternEndValue", "");
							return;
						}
						a_arrray[a_position] = this->endValue();
						ArrayLog(pankey_Log_EndMethod, "copyExternEndValue", "");
					}

					virtual void erase(){
						ArrayLog(pankey_Log_StartMethod, "erase", "");
						if(this->m_t_value == nullptr){
							this->m_pos = 0;
							this->m_size = 0;
							ArrayLog(pankey_Log_EndMethod, "erase", "this->m_t_value == nullptr");
							return;
						}
						this->destroy(this->m_t_value);
						this->m_t_value = nullptr;
						this->m_pos = 0;
						this->m_size = 0;
						ArrayLog(pankey_Log_EndMethod, "erase", "");
					}

					virtual void destroy(T* a_array){
						ArrayLog(pankey_Log_StartMethod, "create", "");
						if(m_allocator == nullptr){
							if(a_array != nullptr){
								delete[] a_array;
								ArrayLog(pankey_Log_Statement, "create", "delete[] a_array");
							}
							ArrayLog(pankey_Log_EndMethod, "create", "");
							return;
						}
						m_allocator->destroyArray(a_array);
						ArrayLog(pankey_Log_EndMethod, "create", "");
					}

					virtual T* create(int a_size)const{
						ArrayLog(pankey_Log_StartMethod, "create", "");
						if(m_allocator == nullptr){
							return new T[a_size];
						}
						memory_size i_count = a_size;
						memory_size i_memory = sizeof(T);
						ArrayLog(pankey_Log_EndMethod, "create", "");
						return (T*)m_allocator->createArray(i_memory, i_count);
					}

					virtual T* createFilledArray(int a_size){
						ArrayLog(pankey_Log_StartMethod, "createFilledArray", "");
						this->fix();
						this->erase();
						this->m_pos = a_size;
						this->m_size = this->getAvailableSize(this->m_pos);
						this->m_t_value = this->create(this->m_size);
						ArrayLog(pankey_Log_EndMethod, "createFilledArray", "");
						return this->m_t_value;
					}

					virtual T* createArray(int a_size){
						ArrayLog(pankey_Log_StartMethod, "createArray", "");
						this->fix();
						this->erase();
						int i_pos = a_size;
						this->m_size = this->getAvailableSize(i_pos);
						this->m_t_value = this->create(this->m_size);
						ArrayLog(pankey_Log_EndMethod, "createArray", "");
						return this->m_t_value;
					}

					virtual T* createFilledArray(T* a_array, int a_position){
						ArrayLog(pankey_Log_StartMethod, "createFilledArray", "");
						this->fix();
						this->erase();
						this->m_pos = a_position;
						this->m_size = this->getAvailableSize(this->m_pos);
						this->m_t_value = a_array;
						ArrayLog(pankey_Log_EndMethod, "createFilledArray", "");
						return this->m_t_value;
					}

					virtual T* createArray(T* a_array, int a_size){
						ArrayLog(pankey_Log_StartMethod, "createArray", "");
						this->fix();
						this->erase();
						int i_pos = a_size;
						this->m_size = this->getAvailableSize(i_pos);
						this->m_t_value = a_array;
						ArrayLog(pankey_Log_EndMethod, "createArray", "");
						return this->m_t_value;
					}

					virtual T* createFilledArray(T* a_array, int a_position, int a_size){
						ArrayLog(pankey_Log_StartMethod, "createFilledArray", "");
						this->fix();
						this->erase();
						this->m_pos = a_position;
						this->m_size = a_size;
						this->m_t_value = a_array;
						ArrayLog(pankey_Log_EndMethod, "createFilledArray", "");
						return this->m_t_value;
					}

					virtual T* createArrayClone(int a_size)const{
						ArrayLog(pankey_Log_StartMethod, "createArrayClone", "");
						int i_pos = a_size;
						int i_size = this->getAvailableSize(i_pos);
						T* i_t_value = this->create(i_size);
						ArrayLog(pankey_Log_EndMethod, "createArrayClone", "");
						return i_t_value;
					}

					virtual void copyToExternPointer(T* a_array, T a_value, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyToExternPointer", "");
						if(a_array == nullptr || m_t_value == nullptr){
							return;
						}
						for(int x = 0; x < a_size; x++){
							a_array[x] = a_value;
						}
						int i_full_size = a_size;
						if(this->hasEndValue()){
							i_full_size--;
						}
						if(this->getPosition() < a_size){
							i_full_size = this->getPosition();
						}
						for(int x = 0; x < i_full_size; x++){
							a_array[x] = m_t_value[x];
						}
						if(this->hasEndValue()){
							a_array[i_full_size] = this->endValue();
						}
						ArrayLog(pankey_Log_EndMethod, "copyToExternPointer", "");
					}

					virtual void copyExternPointer(T* a_array, const T* a_copy, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyExternPointer", "");
						if(a_array == nullptr || a_copy == nullptr ){
							return;
						}
						for(int x = 0; x < a_size; x++){
							a_array[x] = a_copy[x];
						}
						ArrayLog(pankey_Log_EndMethod, "copyExternPointer", "");
					}

					//Method Functionality: utility - polimorfic - reductive - unit - contruct
					virtual void copyExternPointer(T* a_array, const T* a_copy, int a_start, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyExternPointer", "");
						if(a_array == nullptr || a_copy == nullptr ){
							return;
						}
						for(int x = 0; x < a_size; x++){
							a_array[x] = a_copy[x + a_start];
						}
						ArrayLog(pankey_Log_EndMethod, "copyExternPointer", "");
					}

					//Method Functionality: utility - polimorfic - reductive - unit - contruct
					virtual void copyExternPointer(T* a_array, const T* a_copy, int a_start_1, int a_start_2, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyExternPointer", "");
						if(a_array == nullptr || a_copy == nullptr ){
							return;
						}
						for(int x = 0; x < a_size; x++){
							a_array[x + a_start_1] = a_copy[x + a_start_2];
						}
						ArrayLog(pankey_Log_EndMethod, "copyExternPointer", "");
					}

					virtual void copyPointer(const T* a_copy, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyPointer", "");
						if(this->m_t_value == nullptr || a_copy == nullptr ){
							return;
						}
						if(this->getPosition() + a_size > this->getSize()){
							ArrayLog(pankey_Log_EndMethod, "copyPointer", "this->getPosition() + a_size > this->getSize()");
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[this->m_pos] = a_copy[x];
							this->m_pos++;
						}
						ArrayLog(pankey_Log_EndMethod, "copyPointer", "");
					}

					virtual void copyPointer(const T* a_copy, int a_start, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyPointer", "");
						if(this->m_t_value == nullptr || a_copy == nullptr ){
							return;
						}
						if(this->getPosition() + a_size > this->getSize()){
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[this->m_pos] = a_copy[x + a_start];
							this->m_pos++;
						}
						ArrayLog(pankey_Log_EndMethod, "copyPointer", "");
					}

					virtual void copyPointer(const T* a_copy, int a_start_1, int a_start_2, int a_size){
						ArrayLog(pankey_Log_StartMethod, "copyPointer", "");
						if(this->m_t_value == nullptr || a_copy == nullptr ){
							return;
						}
						if(a_size + a_start_1 > this->getSize()){
							return;
						}
						for(int x = 0; x < a_size; x++){
							this->m_t_value[x + a_start_1] = a_copy[x + a_start_2];
						}
						ArrayLog(pankey_Log_EndMethod, "copyPointer", "");
					}

					//Method Functionality: utility - polimorfic - reductive - unit - contruct
					virtual void copyExternValue(T* a_array, T a_copy, int a_position){
						ArrayLog(pankey_Log_StartMethod, "copyExternValue", "");
						if(a_array == nullptr){
							return;
						}
						a_array[a_position] = a_copy;
						ArrayLog(pankey_Log_EndMethod, "copyExternValue", "");
					}

					virtual void copyValue(T a_value){
						ArrayLog(pankey_Log_StartMethod, "copyValue", "");
						if(this->m_t_value == nullptr){
							ArrayLog(pankey_Log_EndMethod, "copyValue", "this->m_t_value == nullptr");
							return;
						}
						if(!this->hasAvailableSize()){
							ArrayLog(pankey_Log_EndMethod, "copyValue", "!this->hasAvailableSize()");
							return;
						}
						this->m_t_value[this->m_pos] = a_value;
						this->m_pos++;
						ArrayLog(pankey_Log_Statement, "copyValue", "Position: ");
						ArrayLog(pankey_Log_Statement, "copyValue", this->getPosition());
						ArrayLog(pankey_Log_Statement, "copyValue", "Size: ");
						ArrayLog(pankey_Log_Statement, "copyValue", this->getSize());
						// ArrayLog(pankey_Log_Statement, "copyValue", "value copied");
						// ArrayLog(pankey_Log_Statement, "copyValue", this->m_t_value[this->m_pos]);

						ArrayLog(pankey_Log_EndMethod, "copyValue", "");
					}

					virtual int getAvailableSize(int a_pos)const{
						ArrayLog(pankey_Log_StartMethod, "getAvailableSize", "");
						ArrayLog(pankey_Log_EndMethod, "getAvailableSize", "");
						return a_pos;
					}

					virtual int arrayLength(const T* a_array) const{
						return this->arrayLength(a_array, this->endValue());
					}

					virtual int arrayLength(const T* a_array, T a_end) const{
						if(a_array == nullptr){
							return -1;
						}
						for(int x = 0; x < 10000; x++){
							if(a_array[x] == a_end){
								return x;
							}
						}
						return -2;
					}

					virtual void setPosition(int a_position){
						ArrayLog(pankey_Log_StartMethod, "setPosition", "");
						this->m_pos = a_position;
						ArrayLog(pankey_Log_EndMethod, "setPosition", "");
					}

					virtual void setSize(int a_size){
						ArrayLog(pankey_Log_StartMethod, "setSize", "");
						this->m_size = a_size;
						ArrayLog(pankey_Log_EndMethod, "setSize", "");
					}

					virtual void destroyAllocator(){
						ArrayLog(pankey_Log_StartMethod, "destroyAllocator", "");
						if(m_allocator == nullptr){
							ArrayLog(pankey_Log_EndMethod, "destroyAllocator", "m_allocator == nullptr");
							return;
						}
						if(!m_allocator->isManaged()){
							ArrayLog(pankey_Log_EndMethod, "destroyAllocator", "!m_allocator->isManaged()");
							return;
						}
						delete m_allocator;
						ArrayLog(pankey_Log_EndMethod, "destroyAllocator", "");
					}

				public:

					virtual void setAllocator(MemoryAllocator* a_allocator){
						ArrayLog(pankey_Log_StartMethod, "setAllocator", "");
						if(m_allocator != a_allocator){
							this->destroyAllocator();
						}
						m_allocator = a_allocator;
						ArrayLog(pankey_Log_EndMethod, "setAllocator", "");
					}

					virtual bool hasAllocator() const{
						return this->m_allocator != nullptr;
					}

					virtual int getPosition() const{
						return this->m_pos;
					}

					virtual int getSize() const{
						return this->m_size;
					}

					virtual int length(void) const{
						if(this->hasEndValue()){
							return this->m_pos - 1;
						}
						return this->m_pos;
					}

					virtual T* pointer()const{
						ArrayLog(pankey_Log_StartMethod, "pointer", "");
						ArrayLog(pankey_Log_EndMethod, "pointer", "");
						return this->m_t_value;
					}

					virtual T* clonePointer(){
						ArrayLog(pankey_Log_StartMethod, "clonePointer", "");
						if(this->isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "clonePointer", "this->isEmpty()");
							return nullptr;
						}
						int n_size = this->getPosition();
						ArrayLog(pankey_Log_Statement, "clonePointer", "index position ");
						ArrayLog(pankey_Log_Statement, "clonePointer", n_size);
						int availableSize = this->getAvailableSize(n_size);
						ArrayLog(pankey_Log_Statement, "clonePointer", "availableSize size ");
						ArrayLog(pankey_Log_Statement, "clonePointer", availableSize);
						ArrayLog(pankey_Log_Statement, "clonePointer", "array size ");
						ArrayLog(pankey_Log_Statement, "clonePointer", this->m_size);
						T* cloneArray = this->create(availableSize);
						this->copyExternPointer(cloneArray, this->m_t_value, n_size);
						this->copyExternEndValue(cloneArray, n_size);
						ArrayLog(pankey_Log_EndMethod, "clonePointer", "");
						return cloneArray;
					}

					virtual T* clonePointer(int a_start, int a_size){
						ArrayLog(pankey_Log_StartMethod, "clonePointer", "start and end");
						if(a_start < 0 || a_start >= this->getPosition() || a_size < 1){
							return nullptr;
						}
						ArrayLog(pankey_Log_Statement, "clonePointer", "new size: ");
						ArrayLog(pankey_Log_Statement, "clonePointer", a_size);
						T* cloneArray = this->createArrayClone(a_size);
						this->copyExternPointer(cloneArray, this->m_t_value, a_start, a_size);
						return cloneArray;
					}

					virtual bool isEmpty() const{
						ArrayLog(pankey_Log_StartMethod, "isEmpty", "");
						ArrayLog(pankey_Log_Statement, "isEmpty", "this->m_pos == 0");
						ArrayLog(pankey_Log_Statement, "isEmpty", this->m_pos == 0);
						ArrayLog(pankey_Log_Statement, "isEmpty", "this->m_t_value == nullptr");
						ArrayLog(pankey_Log_Statement, "isEmpty", this->m_t_value == nullptr);
						ArrayLog(pankey_Log_EndMethod, "isEmpty", "");
						return this->m_pos == 0 || this->m_t_value == nullptr;
					}

					virtual bool set(int a_position, T a_value){
						ArrayLog(pankey_Log_StartMethod, "set", "");
						if(this->isEmpty()){
							return false;
						}
						if(!this->hasAvailableSize(a_position)){
							return false;
						}
						this->m_t_value[a_position] = a_value;
						ArrayLog(pankey_Log_EndMethod, "set", "");
						return true;
					}

					virtual T get(int x) const{
						if(this->m_t_value == nullptr){
							return T();
						}
						if(x >= this->m_pos && this->m_pos > 0){
							return this->m_t_value[this->m_pos - 1];
						}
						if(x < this->m_pos && x >= 0){
							return this->m_t_value[x];
						}
						return T();
					}

					virtual T* getPointer(int x) const{
						if(this->m_t_value == nullptr){
							return nullptr;
						}
						if(x < this->m_pos && x >= 0 && this->m_pos > 0){
							return &this->m_t_value[x];
						}
						return nullptr;
					}

					Array<T> getArrayPart(int start)const{
						ArrayLog(pankey_Log_StartMethod, "getArrayPart", "");
						
						if(this->isEmpty()){
							ArrayLog(pankey_Log_StartMethod, "getArrayPart", "this->isEmpty()");
							return Array<T>();
						}
						
						int t_size = this->length();
						int s_size = t_size - start;
						ArrayLog(pankey_Log_StartMethod, "getArrayPart", "getArrayPart size");
						ArrayLog(pankey_Log_StartMethod, "getArrayPart", s_size);
						T* buff = this->createArrayClone(s_size);
						
						T* i_arrayPointer = this->pointer();

						if(i_arrayPointer == nullptr || buff == nullptr){
							return Array<T>();
						}

						for(int x = start; x < t_size; x++){
							buff[x - start] = i_arrayPointer[x];
						}
						this->copyExternEndValue(buff, s_size);

						Array<T> i_array;
						i_array.addLocalArrayPointer(buff);
						this->destroy(buff);

						ArrayLog(pankey_Log_EndMethod, "getArrayPart", "");
						return i_array;
					}

					Array<T> getArrayPartBySize(int a_start, int a_size){//subNote
						return this->getArrayPart(a_start, a_start + a_size);
					}

					Array<T> getArrayPartByExtraSpace(int a_start, int a_size){//subNote
						return this->getArrayPart(a_start, this->getPosition() - a_size);
					}

					Array<T> getArrayPartByLastExtraSpace(int a_size){//subNote
						return this->getArrayPart(0, this->getPosition() - a_size);
					}

					Array<T> getArrayPart(int a_start, int a_end){//subNote
						ArrayLog(pankey_Log_StartMethod, "getArrayPart", "");
						
						if(this->isEmpty()){
							ArrayLog(pankey_Log_StartMethod, "getArrayPart", "this->isEmpty()");
							return Array<T>();
						}
						
						// if(a_end > this->getPosition()){
						// 	ArrayLog(pankey_Log_StartMethod, "getArrayPart", "this->isEmpty()");
						// 	return Array<T>();
						// }
						
						int t_size = this->getPosition();
						int s_size = t_size - a_start;
						
						if(a_end < t_size){
							s_size -= this->getPosition() - a_end;
							t_size = a_end;
						}
						
						ArrayLog(pankey_Log_StartMethod, "getArrayPart", "subNote size");
						ArrayLog(pankey_Log_StartMethod, "getArrayPart", s_size);
						T* buff = this->createArrayClone(s_size);
						
						T* i_arrayPointer = this->pointer();

						if(i_arrayPointer == nullptr || buff == nullptr){
							return Array<T>();
						}

						for(int x = a_start; x < t_size; x++){
							buff[x - a_start] = i_arrayPointer[x];
						}
						this->copyExternEndValue(buff, s_size);

						Array<T> i_array;
						i_array.addLocalArrayPointer(buff);
						this->destroy(buff);
						
						ArrayLog(pankey_Log_EndMethod, "getArrayPart", "");
						return i_array;
					}

					virtual Array<T> addValue(T a_value)const{
						ArrayLog(pankey_Log_StartMethod, "addValue", "const T& a_value");
						Array<T> i_array = *this;
						if(this->hasReachedFixSize()){
							return i_array;
						}
						i_array.addLocalValue(a_value);
						ArrayLog(pankey_Log_EndMethod, "addValue", "");
						return i_array;
					}

					virtual void addLocalValue(T a_value){
						ArrayLog(pankey_Log_StartMethod, "addLocalValue", "const T& a_value");
						if(this->hasReachedFixSize()){
							return;
						}
						this->insertLocalValue(this->getPosition(), a_value);
						ArrayLog(pankey_Log_EndMethod, "addLocalValue", "");
					}

					virtual void insertLocalValue(int a_position, T a_value){
						ArrayLog(pankey_Log_StartMethod, "insertLocalValue", "const T& a_value");
						if(this->hasReachedFixSize()){
							return;
						}
						int i_array_length = 1;
						ArrayLog(pankey_Log_Statement, "insertLocalValue", "Array Length:");
						ArrayLog(pankey_Log_Statement, "insertLocalValue", i_array_length);
						ArrayLog(pankey_Log_Statement, "insertLocalValue", "Array Position:");
						ArrayLog(pankey_Log_Statement, "insertLocalValue", this->getPosition());
						ArrayLog(pankey_Log_Statement, "insertLocalValue", "Array Size:");
						ArrayLog(pankey_Log_Statement, "insertLocalValue", this->getSize());
						if(this->isEmpty()){
							ArrayLog(pankey_Log_Statement, "insertLocalValue", "this->isEmpty()");
							this->createArray(i_array_length);
							this->copyValue(a_value);
							this->copyEndValue();
							ArrayLog(pankey_Log_EndMethod, "insertLocalValue", "");
							return;
						}

						this->expandIfNeeded(i_array_length);

						if(a_position >= this->getPosition()){
							this->copyValue(a_value);
							this->copyEndValue();
							ArrayLog(pankey_Log_EndMethod, "insertLocalValue", "");
							return;
						}

						T* i_pointer = this->createArrayClone(i_array_length + this->getPosition());

						this->copyExternPointer(i_pointer, this->pointer(), a_position);
						this->copyExternValue(i_pointer, a_value, a_position);
						this->copyExternPointer(i_pointer, this->pointer(), a_position + i_array_length, a_position, this->getPosition() - a_position);
						this->copyExternEndValue(i_pointer, this->getPosition() + i_array_length);

						this->createFilledArray(i_pointer, this->getPosition() + i_array_length);

						ArrayLog(pankey_Log_Statement, "insertLocalValue", "Array Position:");
						ArrayLog(pankey_Log_Statement, "insertLocalValue", this->getPosition());
						ArrayLog(pankey_Log_Statement, "insertLocalValue", "Array Size:");
						ArrayLog(pankey_Log_Statement, "insertLocalValue", this->getSize());

						ArrayLog(pankey_Log_EndMethod, "insertLocalValue", "");
					}

					virtual Array<T> addArray(const Array<T>& a_array){
						ArrayLog(pankey_Log_StartMethod, "addArray", "");
						if(this->hasReachedFixSize()){
							return *this;
						}
						Array<T> i_array = *this;
						ArrayLog(pankey_Log_EndMethod, "addArray", "");
						return i_array.addLocalArray(a_array);
					}

					virtual Array<T> addLocalArray(const Array<T>& a_array){
						ArrayLog(pankey_Log_StartMethod, "addLocalArray", "const Array<T>& a_array");
						if(this->hasReachedFixSize()){
							return *this;
						}
						ArrayLog(pankey_Log_EndMethod, "addLocalArray", "");
						return this->insertLocalArray(this->getPosition(), a_array);
					}

					virtual Array<T> insertLocalArray(int a_position, const Array<T>& a_array){
						ArrayLog(pankey_Log_StartMethod, "insertLocalArray", "const Array<T>& a_array");
						if(this->hasReachedFixSize()){
							return *this;
						}
						int i_array_length = a_array.getPosition();
						ArrayLog(pankey_Log_Statement, "insertLocalArray", "Array Length:");
						ArrayLog(pankey_Log_Statement, "insertLocalArray", i_array_length);
						ArrayLog(pankey_Log_Statement, "insertLocalArray", "Array Position:");
						ArrayLog(pankey_Log_Statement, "insertLocalArray", this->getPosition());
						ArrayLog(pankey_Log_Statement, "insertLocalArray", "Array Size:");
						ArrayLog(pankey_Log_Statement, "insertLocalArray", this->getSize());
						if(this->isEmpty()){
							this->createArray(i_array_length);
							this->copyPointer(a_array.pointer(), i_array_length);
							this->copyEndValue();
							return *this;
						}
						this->expandIfNeeded(i_array_length);

						if(a_position >= this->getPosition()){
							this->copyPointer(a_array.pointer(), i_array_length);
							this->copyEndValue();
							ArrayLog(pankey_Log_EndMethod, "insertLocalArray", "");
							return *this;
						}

						T* i_pointer = this->createArrayClone(i_array_length + this->getPosition());

						this->copyExternPointer(i_pointer, this->pointer(), a_position);
						this->copyExternPointer(i_pointer, a_array.pointer(), a_position, 0, i_array_length);
						this->copyExternPointer(i_pointer, this->pointer(), a_position + i_array_length, a_position, this->getPosition() - a_position);
						this->copyExternEndValue(i_pointer, this->getPosition() + i_array_length);

						this->createFilledArray(i_pointer, this->getPosition() + i_array_length);

						ArrayLog(pankey_Log_Statement, "insertLocalArray", "Array Position:");
						ArrayLog(pankey_Log_Statement, "insertLocalArray", this->getPosition());
						ArrayLog(pankey_Log_Statement, "insertLocalArray", "Array Size:");
						ArrayLog(pankey_Log_Statement, "insertLocalArray", this->getSize());

						ArrayLog(pankey_Log_EndMethod, "insertLocalArray", "");
						return *this;
					}
					
					virtual Array<T> addArrayPointer(const T* a_pointer)const{
						ArrayLog(pankey_Log_StartMethod, "addArrayPointer", "const char* a_pointer");
						if(this->hasReachedFixSize()){
							return *this;
						}
						ArrayLog(pankey_Log_Statement, "addArrayPointer", "Pointer Array:");
						//ArrayLog(pankey_Log_Statement, "addArrayPointer", a_pointer);
						Array i_array = *this;
						ArrayLog(pankey_Log_EndMethod, "addArrayPointer", "");
						return i_array.addLocalArrayPointer(a_pointer);
					}

					virtual Array<T> addLocalArrayPointer(const T* a_pointer){
						ArrayLog(pankey_Log_StartMethod, "addLocalArrayPointer", "const char* a_pointer");
						if(this->hasReachedFixSize()){
							return *this;
						}
						ArrayLog(pankey_Log_Statement, "addLocalArrayPointer", "Pointer Array:");
						//ArrayLog(pankey_Log_Statement, "addLocalArrayPointer", a_pointer);
						ArrayLog(pankey_Log_EndMethod, "addLocalArrayPointer", "");
						return this->insertLocalArrayPointer(this->getPosition(), a_pointer);
					}

					virtual Array<T> addLocalArrayPointer(const T* a_pointer, int a_size){
						ArrayLog(pankey_Log_StartMethod, "addLocalArrayPointer", "const char* a_pointer");
						if(this->hasReachedFixSize()){
							return *this;
						}
						ArrayLog(pankey_Log_Statement, "addLocalArrayPointer", "Pointer Array:");
						//ArrayLog(pankey_Log_Statement, "addLocalArrayPointer", a_pointer);
						ArrayLog(pankey_Log_EndMethod, "addLocalArrayPointer", "");
						return this->insertLocalArrayPointer(this->getPosition(), a_pointer, a_size);
					}

					virtual Array<T> insertLocalArrayPointer(int a_position, const T* a_pointer){
						ArrayLog(pankey_Log_StartMethod, "insertLocalArrayPointer", "const char* a_pointer");
						if(this->hasReachedFixSize()){
							return *this;
						}
						ArrayLog(pankey_Log_EndMethod, "insertLocalArrayPointer", "");
						return this->insertLocalArrayPointer(a_position, a_pointer, this->arrayLength(a_pointer));
					}

					virtual Array<T> insertLocalArrayPointer(int a_position, const T* a_pointer, int a_size){
						ArrayLog(pankey_Log_StartMethod, "insertLocalArrayPointer", "const char* a_pointer");
						if(this->hasReachedFixSize()){
							return *this;
						}
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Pointer Array:");
						if(a_pointer == nullptr){
							return *this;
						}
						int i_array_length = this->arrayLength(a_pointer);
						if(i_array_length > a_size){
							i_array_length = a_size;
						}
						if(i_array_length == 0){
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "i_array_length == 0");
							ArrayLog(pankey_Log_EndMethod, "insertLocalArrayPointer", "");
							return *this;
						}
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Length:");
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", i_array_length);
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Position:");
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getPosition());
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Size:");
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getSize());
						if(this->isEmpty()){
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "this->isEmpty()");
							this->createArray(i_array_length);
							this->copyPointer(a_pointer, i_array_length);
							this->copyEndValue();
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Position:");
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getPosition());
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Size:");
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getSize());
							ArrayLog(pankey_Log_EndMethod, "insertLocalArrayPointer", "");
							return *this;
						}
						this->expandIfNeeded(i_array_length);
						
						if(a_position >= this->getPosition()){
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "a_position >= this->getPosition()");
							this->copyPointer(a_pointer, i_array_length);
							this->copyEndValue();
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Position:");
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getPosition());
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Size:");
							ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getSize());
							ArrayLog(pankey_Log_EndMethod, "insertLocalArrayPointer", "");
							return *this;
						}

						T* i_pointer = this->createArrayClone(i_array_length + this->getPosition());

						this->copyExternPointer(i_pointer, this->pointer(), a_position);
						this->copyExternPointer(i_pointer, a_pointer, a_position, 0, i_array_length);
						this->copyExternPointer(i_pointer, this->pointer(), a_position + i_array_length, a_position, this->getPosition() - a_position);
						this->copyExternEndValue(i_pointer, this->getPosition() + i_array_length);

						this->createFilledArray(i_pointer, this->getPosition() + i_array_length);
						
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "a_position < this->getPosition()");
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Position:");
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getPosition());
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", "Array Size:");
						ArrayLog(pankey_Log_Statement, "insertLocalArrayPointer", this->getSize());
						
						ArrayLog(pankey_Log_EndMethod, "insertLocalArrayPointer", "");
						return *this;
					}

					virtual Array<T> addLocal(){
						ArrayLog(pankey_Log_StartMethod, "addLocal", "");
						if(this->hasReachedFixSize()){
							return *this;
						}
						if(this->isEmpty()){
							return *this;
						}
						int i_size = this->getPosition();
						T* i_t_value = this->clonePointer();
						if(this->m_size - this->m_pos < 1){
							expandLocal(i_size + this->m_expandSize);
						}
						this->copyPointer(i_t_value, i_size);
						this->destroy(i_t_value);
						ArrayLog(pankey_Log_EndMethod, "addLocal", "");
						return *this;
					}

					virtual ArrayIterator<T> begin() const{
						return ArrayIterator<T>(this->m_t_value,0);
					}
					virtual ArrayIterator<T> end() const{
						return ArrayIterator<T>(this->m_t_value, this->m_pos);
					}

					virtual bool contain(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "contain", "");
						if(this->isEmpty()){
							return false;
						}

						ArrayLog(pankey_Log_Statement, "contain", "Array Position:");
						ArrayLog(pankey_Log_Statement, "contain", this->getPosition());
						ArrayLog(pankey_Log_Statement, "contain", "Array Size:");
						ArrayLog(pankey_Log_Statement, "contain", this->getSize());

						for(int x = 0; x < this->m_pos; x++){
							if(this->m_t_value[x] == a_value){
								ArrayLog(pankey_Log_EndMethod, "contain", "return true");
								return true;
							}
						}
						ArrayLog(pankey_Log_EndMethod, "contain", "return false");
						return false;
					}

					virtual int getFirstIndex(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "getFirstIndex", "");
						if(this->isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "getFirstIndex", "");
							return -1;
						}
						for(int x = 0; x < this->m_pos; x++){
							if(this->m_t_value[x] == a_value){
								return x;
							}
						}
						return -1;
						ArrayLog(pankey_Log_EndMethod, "getFirstIndex", "");
					}

					virtual int getLastIndex(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "getLastIndex", "");
						if(this->isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "getLastIndex", "");
							return -1;
						}
						for(int x = this->m_pos - 1; x >= 0; x--){
							if(this->m_t_value[x] == a_value){
								return x;
							}
						}
						return -1;
						ArrayLog(pankey_Log_EndMethod, "getLastIndex", "");
					}

					virtual bool remove(int a_index){
						ArrayLog(pankey_Log_StartMethod, "remove", "");
						if(a_index == -1 || a_index >= this->m_pos || this->isEmpty()){
							return false;
						}
						if(this->removeShrink){
							int i_pos = this->m_pos - 1;
							T* i_copy = this->createArrayClone(i_pos);
							int x_count = 0;
							for(int x = 0; x < this->m_pos; x++){
								if(a_index != x){
									i_copy[x_count] = this->m_t_value[x];
									x_count++;
								}
							}
							this->createFilledArray(i_copy, i_pos);
							this->copyEndValue();
						}else{

						}
						return true;
						ArrayLog(pankey_Log_EndMethod, "remove", "");
					}

					virtual bool remove(int a_index, int a_size){
						ArrayLog(pankey_Log_StartMethod, "remove", "");
						if(a_index == -1 || a_index >= this->m_pos || this->isEmpty()){
							return false;
						}
						if(this->removeShrink){
							int i_pos = this->m_pos - a_size;
							T* i_copy = this->createArrayClone(i_pos);
							int x_count = 0;
							for(int x = 0; x < a_index; x++){
								i_copy[x_count] = this->m_t_value[x];
								x_count++;
							}
							for(int x = a_index + a_size; x < this->getPosition(); x++){
								i_copy[x_count] = this->m_t_value[x];
								x_count++;
							}
							this->createFilledArray(i_copy, x_count);
							this->copyEndValue();
						}else{

						}
						return true;
						ArrayLog(pankey_Log_EndMethod, "remove", "");
					}

					virtual void removeFirst(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "removeFirst", "");
						int index = getFirstIndex(a_value);
						if(index == -1){
							return;
						}
						this->remove(index);
						ArrayLog(pankey_Log_EndMethod, "removeFirst", "");
					}

					virtual void removeLast(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "removeLast", "");
						int index = getLastIndex(a_value);
						if(index == -1){
							return;
						}
						this->remove(index);
						ArrayLog(pankey_Log_EndMethod, "removeLast", "");
					}

					virtual Array<T> removeAllInitialValues(const T& a_value) const{
						ArrayLog(pankey_Log_StartMethod, "removeAllInitialValues", "");

						Array<T> i_array;
						int i_start_cut = 0;

						ArrayLog(pankey_Log_Statement, "removeAllInitialValues", "this->length()");
						ArrayLog(pankey_Log_Statement, "removeAllInitialValues", this->length());

						for(int x = 0; x < this->length(); x++){
							const T f_val = this->m_t_value[x];
							if(f_val == a_value){
								i_start_cut++;
							}else{
								break;
							}
						}

						ArrayLog(pankey_Log_Statement, "removeAllInitialValues", "i_start_cut");
						ArrayLog(pankey_Log_Statement, "removeAllInitialValues", i_start_cut);

						for(int x = i_start_cut; x < this->length(); x++){
							const T f_val = this->m_t_value[x];
							i_array.addLocalValue(f_val);
							if(x == this->length() - 1 && this->hasEndValue()){
								ArrayLog(pankey_Log_Statement, "removeAllInitialValues", "adding end value");
								i_array.addLocalValue(this->endValue());
							}
						}

						ArrayLog(pankey_Log_EndMethod, "removeAllInitialValues", "");
						return i_array;
					}

					virtual Array<T> removeAllEndingValues(const T& a_value) const{
						ArrayLog(pankey_Log_StartMethod, "removeAllEndingValues", "");

						Array<T> i_array;
						int i_end_cut = 0;

						for(int x = this->length() - 1; x >= 0; x--){
							const T f_val = this->m_t_value[x];
							if(f_val == a_value){
								i_end_cut++;
							}else{
								break;
							}
						}

						for(int x = 0; x < this->length() - i_end_cut; x++){
							const T f_val = this->m_t_value[x];
							i_array.addLocalValue(f_val);
							if(x == this->length() - i_end_cut - 1 && this->hasEndValue()){
								i_array.addLocalValue(this->endValue());
							}
						}

						ArrayLog(pankey_Log_EndMethod, "removeAllEndingValues", "");
						return i_array;
					}

					virtual Array<T> removeAllInitialAndEndingValues(const T& a_value) const{
						ArrayLog(pankey_Log_StartMethod, "removeAllInitialAndEndingValues", "");

						Array<T> i_array;
						int i_start_cut = 0;

						for(int x = 0; x < this->length(); x++){
							const T f_val = this->m_t_value[x];
							if(f_val == a_value){
								i_start_cut++;
							}else{
								break;
							}
						}

						int i_end_cut = 0;

						for(int x = this->length() - 1; x >= 0; x--){
							const T f_val = this->m_t_value[x];
							if(f_val == a_value){
								i_end_cut++;
							}else{
								break;
							}
						}

						for(int x = i_start_cut; x < this->length() - i_end_cut; x++){
							const T f_val = this->m_t_value[x];
							i_array.addLocalValue(f_val);
							if(x == this->length() - i_end_cut - 1 && this->hasEndValue()){
								i_array.addLocalValue(this->endValue());
							}
						}

						ArrayLog(pankey_Log_EndMethod, "removeAllInitialAndEndingValues", "");
						return i_array;
					}

					virtual void removeFirstIndex(){
						ArrayLog(pankey_Log_StartMethod, "removeFirstIndex", "");
						if(this->isEmpty()){
							return;
						}
						this->remove(0);
						ArrayLog(pankey_Log_EndMethod, "removeFirstIndex", "");
					}

					virtual void removeLastIndex(){
						ArrayLog(pankey_Log_StartMethod, "removeLastIndex", "");
						if(this->isEmpty()){
							return;
						}
						this->remove(this->getPosition() - 1);
						ArrayLog(pankey_Log_EndMethod, "removeLastIndex", "");
					}

					Array<T> split(int a_position, T a_split) const{
						ArrayLog(pankey_Log_StartMethod, "split", "");
						Array<T> i_array_cut;
						Array<T> i_array_part;
						int i_position = 0;

						i_array_cut = this->removeAllInitialAndEndingValues(a_split);

						for(int x = 0; x < i_array_cut.getPosition(); x++){
							ArrayLog(pankey_Log_Statement, "split", "iteration: ");
							ArrayLog(pankey_Log_Statement, "split", x);
							const T f_val = i_array_cut.m_t_value[x];
							ArrayLog(pankey_Log_Statement, "split", "char: ");
							ArrayLog(pankey_Log_Statement, "split", f_val);
							ArrayLog(pankey_Log_Statement, "split", "i_array_part: ");
							// ArrayLog(pankey_Log_Statement, "split", i_array_part.pointer());
							if(f_val == a_split){
								ArrayLog(pankey_Log_Statement, "split", "f_val == a_split");
								i_position++;
								ArrayLog(pankey_Log_Statement, "split", "end for loop");
								continue;
							}
							if(i_position == a_position){
								ArrayLog(pankey_Log_Statement, "split", "f_val == a_split");
								i_array_part.addLocalValue(f_val);
								ArrayLog(pankey_Log_Statement, "split", "i_array_part: ");
								// ArrayLog(pankey_Log_Statement, "split", i_array_part.pointer());
								ArrayLog(pankey_Log_Statement, "split", "end for loop");
								continue;
							}
							if(i_position > a_position){
								ArrayLog(pankey_Log_Statement, "split", "i_position > a_position");
								ArrayLog(pankey_Log_Statement, "split", "end for loop");
								break;
							}
							ArrayLog(pankey_Log_Statement, "split", "end for loop");
						}
						ArrayLog(pankey_Log_EndMethod, "split", "");
						return i_array_part;
					}

					//gets the amount of times it gets splits, ignorring extra split values at the start and the end
					int getSplitSize(T a_split) const{
						ArrayLog(pankey_Log_StartMethod, "getSplitSize", "");
						if(this->isEmpty()){
							return 0;
						}
						int i_size = 0;
						Array<T> i_array_part = this->removeAllInitialAndEndingValues(a_split);

						for(int x = 0; x < i_array_part.getPosition(); x++){
							T f_val = i_array_part.get(x);
							if(f_val == a_split){
								i_size++;
							}
						}

						ArrayLog(pankey_Log_EndMethod, "getSplitSize", "");
						return i_size;
					}

					//gets the amount of parts it gets splits on
					int getPartSize(T a_split) const{
						ArrayLog(pankey_Log_StartMethod, "getPartSize", "");
						if(this->isEmpty()){
							return 0;
						}
						Array<T> i_array_part = this->removeAllInitialAndEndingValues(a_split);

						int i_size = 1;
						for(int x = 0; x < i_array_part.getPosition(); x++){
							T f_val = i_array_part.get(x);
							if(f_val == a_split){
								i_size++;
							}
						}

						ArrayLog(pankey_Log_EndMethod, "getPartSize", "");
						return i_size;
					}
			/*
					Array<Array<T>> split(const T& divide){

					}

					Array<T> split(const T& divide, int parte){

					}

					int splitLenght(const T& divide){

					}*/

					virtual void fixSize(int a_length){
						ArrayLog(pankey_Log_StartMethod, "fixSize", "");
						m_fix_length = a_length;
						ArrayLog(pankey_Log_EndMethod, "fixSize", "");
					}

					virtual void setFixSize(int a_length){
						ArrayLog(pankey_Log_StartMethod, "setFixSize", "");
						m_fix_length = a_length;
						expandLocal(a_length);
						ArrayLog(pankey_Log_EndMethod, "setFixSize", "");
					}

					virtual void setFixSize(){
						ArrayLog(pankey_Log_StartMethod, "setFixSize", "");
						if(m_fix_length == -1){
							return;
						}
						expandLocal(m_fix_length);
						ArrayLog(pankey_Log_EndMethod, "setFixSize", "");
					}

					virtual bool hasReachedFixSize()const{
						ArrayLog(pankey_Log_StartMethod, "hasReachedFixSize", "");
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", "m_fix_length:");
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", m_fix_length);
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", "this->length():");
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", this->length());
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", "this->getPosition():");
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", this->getPosition());
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", "this->getSize():");
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", this->getSize());
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", "has reached fix size:");
						ArrayLog(pankey_Log_Statement, "hasReachedFixSize", this->length() >= m_fix_length);
						if(m_fix_length == -1){
							ArrayLog(pankey_Log_EndMethod, "hasReachedFixSize", "m_fix_length == -1");
							return false;
						}
						ArrayLog(pankey_Log_EndMethod, "hasReachedFixSize", "");
						return this->length() >= m_fix_length || this->getPosition() >= m_fix_length;
					}

					virtual int getFreeSpace(int a_position)const{
						ArrayLog(pankey_Log_StartMethod, "getFreeSpace", "int a_position");
						int i_addingEndValue = 0;
						if(this->hasEndValue()){
							ArrayLog(pankey_Log_Statement, "getFreeSpace", "this->hasEndValue()");
							i_addingEndValue = 1;
						}
						int i_availableSize = this->getSize() - a_position - i_addingEndValue;
						ArrayLog(pankey_Log_EndMethod, "getFreeSpace", i_availableSize);
						return i_availableSize;
					}

					virtual int getFreeSpace()const{
						ArrayLog(pankey_Log_StartMethod, "getFreeSpace", "");
						int i_addingEndValue = 0;
						if(this->hasEndValue()){
							ArrayLog(pankey_Log_Statement, "getFreeSpace", "this->hasEndValue()");
							i_addingEndValue = 1;
						}
						int i_availableSize = this->getSize() - this->getPosition() - i_addingEndValue;
						ArrayLog(pankey_Log_EndMethod, "getFreeSpace", i_availableSize);
						return i_availableSize;
					}

					virtual bool hasAvailableSize()const{
						ArrayLog(pankey_Log_StartMethod, "hasAvailableSize", "");
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", "Array Position:");
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", this->getPosition());
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", "Array Size:");
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", this->getSize());
						return this->getFreeSpace() > 0;
					}

					virtual bool hasAvailableSize(int a_size)const{
						ArrayLog(pankey_Log_StartMethod, "hasAvailableSize", "int a_size");
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", "New Size:");
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", a_size);
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", "Array Size:");
						ArrayLog(pankey_Log_Statement, "hasAvailableSize", this->getSize());
						return this->getFreeSpace(a_size) > 0;
					}

					virtual void fix(){
						ArrayLog(pankey_Log_StartMethod, "fix", "");
						ArrayLog(pankey_Log_EndMethod, "fix", "");
					}

					virtual void fill(T a_fill){
						ArrayLog(pankey_Log_StartMethod, "fill", "");
						if(this->isEmpty()){
							return;
						}
						for(int x = 0; x < this->getPosition(); x++){
							this->m_t_value[x] = a_fill;
						}
						ArrayLog(pankey_Log_EndMethod, "fill", "");
					}

					virtual void clear(){
						ArrayLog(pankey_Log_StartMethod, "clear", "");
						if(this->m_t_value == nullptr){
							this->m_pos = 0;
							this->m_size = 0;

							if(this->m_fix_length == -1){
								return;
							}
	
							this->setFixSize();
							
							ArrayLog(pankey_Log_EndMethod, "erase", "this->m_t_value == nullptr");
							return;
						}
						this->destroy(this->m_t_value);
						this->m_t_value = nullptr;
						this->m_pos = 0;
						this->m_size = 0;

						if(this->m_fix_length == -1){
							return;
						}

						this->setFixSize();

						ArrayLog(pankey_Log_EndMethod, "clear", "");
					}

					virtual void reset(){
						ArrayLog(pankey_Log_StartMethod, "reset", "");
						this->m_pos = 0;
						ArrayLog(pankey_Log_EndMethod, "reset", "");
					}

					virtual void expandLocal(int a_size){
						ArrayLog(pankey_Log_StartMethod, "expandLocal", "");
						if(this->hasReachedFixSize()){
							return;
						}
						int nsize = this->getSize() + a_size;
						T *nT = this->create(nsize);
						for(int x = 0; x < this->m_pos; x++){
							nT[x] = this->m_t_value[x];
						}
						if(this->m_t_value != nullptr){
							this->destroy(this->m_t_value);
						}
						this->m_t_value = nT;
						this->setSize(nsize);
						ArrayLog(pankey_Log_EndMethod, "expandLocal", "");
					}

					////////////////////////////operator part////////////////////////////////////////////////////////////////

				public:

					virtual Array<T>& operator=(const Array<T>& a_array){
						ArrayLog(pankey_Log_StartMethod, "operator=", "operator= const Array<T>&");
						this->fix();
						this->erase();

						if(a_array.isEmpty()){
							ArrayLog(pankey_Log_EndMethod, "operator=", "a_array.isEmpty()");
							return *this;
						}
						int i_array_length = a_array.getPosition();
						this->createArray(i_array_length);
						this->copyPointer(a_array.pointer(), i_array_length);
						this->copyEndValue();
						ArrayLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					virtual Array<T> operator=(T a_value){
						ArrayLog(pankey_Log_StartMethod, "operator=", "operator= const T&");
						this->fix();
						this->erase();
						this->createArray(1);
						this->copyValue(a_value);
						this->copyEndValue();
						//ArrayLog(pankey_Log_Statement, "operator=", a_value);
						ArrayLog(pankey_Log_EndMethod, "operator=", "");
						return *this;
					}

					virtual Array<T> operator+=(const Array<T>& a_value){
						ArrayLog(pankey_Log_StartMethod, "operator+=", "const Array<T>& a_value");
						ArrayLog(pankey_Log_EndMethod, "operator+=", "");
						return this->addLocalArray(a_value);
					}

					virtual Array<T> operator+(const Array<T>& a_value){
						ArrayLog(pankey_Log_StartMethod, "operator+", "const Array<T>& a_value");
						Array<T> i_array = *this;
						ArrayLog(pankey_Log_EndMethod, "operator+", "");
						return i_array.addArray(a_value);
					}

					virtual void operator+=(T a_value){
						ArrayLog(pankey_Log_StartMethod, "operator+=", "T a_value");
						this->addLocalValue(a_value);
						ArrayLog(pankey_Log_EndMethod, "operator+=", "");
					}

					virtual Array<T> operator+(T a_value){
						ArrayLog(pankey_Log_StartMethod, "operator+", "T a_value");
						Array<T> i_array = *this;
						ArrayLog(pankey_Log_EndMethod, "operator+", "");
						return i_array.addValue(a_value);
					}

					virtual bool operator==(const Array<T>& o_array)const{
						ArrayLog(pankey_Log_StartMethod, "operator==", "const Array<T>& o_array");
						
						if(o_array.getPosition() != this->getPosition()){
							return false;
						}
						for(int x = 0; x < this->getPosition(); x++){
							if(o_array.get(x) != this->get(x)){
								return false;
							}
						}

						ArrayLog(pankey_Log_EndMethod, "operator==", "");
						return true;
					}

					virtual bool operator!=(const Array<T>& o_array)const{
						ArrayLog(pankey_Log_StartMethod, "operator!=", "const Array<T>& o_array");
						
						if(o_array.getPosition() != this->getPosition()){
							return true;
						}
						for(int x = 0; x < this->getPosition(); x++){
							if(o_array.get(x) != this->get(x)){
								return true;
							}
						}

						ArrayLog(pankey_Log_EndMethod, "operator!=", "");
						return false;
					}

					virtual bool operator==(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "operator==", "const T& a_value");
						
						if(this->length() != 1){
							return false;
						}

						ArrayLog(pankey_Log_EndMethod, "operator==", "");
						return this->get(0) == a_value;
					}
					
					virtual bool operator!=(const T& a_value){
						ArrayLog(pankey_Log_StartMethod, "operator!=", "const T& a_value");
						
						if(this->length() != 1){
							return true;
						}

						ArrayLog(pankey_Log_EndMethod, "operator!=", "");
						return this->get(0) != a_value;
					}

					virtual T& operator[](int x){
						ArrayLog(pankey_Log_StartMethod, "operator[]", "");
						if(x > this->m_pos && this->m_pos > 0){
							return this->m_t_value[this->m_pos - 1];
						}
						if(x < this->m_pos && x >= 0){
							return this->m_t_value[x];
						}
						if(x >= this->m_size){
							expandLocal((x - this->m_size + 1) + this->m_expandSize);
						}
						if(this->m_pos == x){
							this->m_pos++;
						}
						ArrayLog(pankey_Log_EndMethod, "operator[]", "");
						return this->m_t_value[x];
					}

					virtual T operator[](int x) const{
						if(this->m_t_value == nullptr){
							return T();
						}
						if(x >= this->m_pos && this->m_pos > 0){
							return this->m_t_value[this->m_pos - 1];
						}
						if(x < this->m_pos && x >= 0){
							return this->m_t_value[x];
						}
						return T();
					}
			/*
					void replace(Array a_search, Array a_change){
						ArrayLog(pankey_Log_StartMethod, "replace", "");
						ArrayLog(pankey_Log_Statement, "replace", "");
						Array i_Array;
						Array i_search;
						int i_search_index = 0;

						if(isEmpty()){
							return;
						}

						ArrayLog(pankey_Log_Statement, "replace", "start for");
						for(int x = 0; x < this->m_pos; x++){
							ArrayLog(pankey_Log_Statement, "replace", pankey_String("iteration ") + pankey_String(x));
							char cr = charAt(x);
							char schr = a_search.charAt(i_search_index);
							ArrayLog(pankey_Log_Statement, "replace", pankey_String("Arrays char: ") + pankey_String((char)cr));
							ArrayLog(pankey_Log_Statement, "replace", pankey_String("searche char: ") + pankey_String((char)schr));
							if(schr == cr){
								ArrayLog(pankey_Log_Statement, "replace", "schr == cr");
								i_search_index++;
								i_search += schr;
							}else{
								ArrayLog(pankey_Log_Statement, "replace", "schr != cr");
								if(i_search_index > 0){
									ArrayLog(pankey_Log_Statement, "replace", "i_search_index > 0");
									i_search_index = 0;
									i_Array += i_search;
									i_search = "";
								}
								i_Array += cr;
							}
							if(i_search_index == a_search.getPosition()){
								ArrayLog(pankey_Log_Statement, "replace", "i_search_index == a_search.getPosition() - 1");
								i_search_index = 0;
								i_search = "";
								i_Array += a_change;
							}
						}
						ArrayLog(pankey_Log_Statement, "replace", "end for");

						fix(this->m_t_value, this->m_pos, this->m_size);
						erase(this->m_t_value);
						this->m_t_value = i_Array.this->m_t_value;
						this->m_pos = i_Array.this->m_pos;
						this->m_size = i_Array.this->m_size;
						i_Array.this->m_t_value = nullptr;
						i_Array.this->m_pos = 0;
						i_Array.this->m_size = 0;
						return;
					}
			*/

					virtual Array<T> getArray(){
						return *this;
					}

				protected:

					virtual void incrementPosition(){this->m_pos++;}
					virtual void decrementPosition(){
						this->m_pos--;
						if(this->m_pos < 0){
							this->m_pos = 0;
						}
					}

					virtual void incrementPosition(int a_size){this->m_pos += a_size;}
					virtual void decrementPosition(int a_size){
						this->m_pos -= a_size;
						if(this->m_pos < 0){
							this->m_pos = 0;
						}
					}

					virtual void incrementSize(){this->m_size++;}
					virtual void decrementSize(){
						this->m_size--;
						if(this->m_size < 0){
							this->m_size = 0;
						}
					}

					virtual void incrementSize(int a_size){this->m_size += a_size;}
					virtual void decrementSize(int a_size){
						this->m_size -= a_size;
						if(this->m_size < 0){
							this->m_size = 0;
						}
					}

				protected:
					bool removeShrink = true;
					int m_fix_length = -1;
			};

		}

	}

#endif








