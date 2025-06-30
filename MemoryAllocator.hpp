
#ifndef MemoryAllocator_hpp
	#define MemoryAllocator_hpp

	#include "MemorySize.hpp"

	#if defined(pankey_Log) && (defined(MemoryAllocator_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define MemoryAllocatorLog(status,method,mns) pankey_Log(status,"MemoryAllocator",method,mns)
	#else
		#define MemoryAllocatorLog(status,method,mns) 
	#endif

	namespace pankey{

		namespace Base{

			class MemoryAllocator{
				public:
					MemoryAllocator(){}
					MemoryAllocator(bool a_static){this->m_static = a_static;}
					virtual ~MemoryAllocator(){}

					virtual void* create(memory_size a_type_size){return malloc(a_type_size);}
					virtual void* create(){return nullptr;}

					virtual void* createArray(memory_size a_type_size, memory_size a_count){return malloc(a_type_size * a_count);}
					virtual void* createArray(memory_size a_count){return nullptr;}

					virtual void** createPointerArray(memory_size a_type_size, memory_size a_count){return (void**)malloc(a_type_size * a_count);}
					virtual void** createPointerArray(memory_size a_count){return nullptr;}

					virtual void destroy(memory_size a_type_size, void* a_destroy){free(a_destroy);}
					virtual void destroy(void* a_destroy){free(a_destroy);}

					virtual void destroyArray(memory_size a_type_size, memory_size a_count, void* a_destroy){free(a_destroy);}
					virtual void destroyArray(void* a_destroy){free(a_destroy);}

					virtual void destroyPointerArray(memory_size a_type_size, memory_size a_count, void** a_destroy){free(a_destroy);}
					virtual void destroyPointerArray(void** a_destroy){free(a_destroy);}

					virtual void isStatic(bool a_static){
						this->m_static = a_static;
					}

					virtual bool isStatic(){
						return this->m_static;
					}

					virtual MemoryAllocator* clone()const{
						return new MemoryAllocator();
					}

				protected:
					bool m_static = true;
			};

			MemoryAllocator* setMemoryAllocator(MemoryAllocator* a_memory_allocator){
				MemoryAllocatorLog(pankey_Log_StartMethod, "setMemoryAllocator", "");
				MemoryAllocator* i_memory_allocator = nullptr;
				if(a_memory_allocator != nullptr){
					MemoryAllocatorLog(pankey_Log_Statement, "setMemoryAllocator", "a_memory_allocator != nullptr");
					if(!a_memory_allocator->isStatic()){
						MemoryAllocatorLog(pankey_Log_Statement, "setMemoryAllocator", "a_memory_allocator->isManaged()");
						i_memory_allocator = a_memory_allocator->clone();
						i_memory_allocator->isStatic(false);
					}else{
						MemoryAllocatorLog(pankey_Log_Statement, "setMemoryAllocator", "!a_memory_allocator->isManaged()");
						i_memory_allocator = a_memory_allocator;
					}
				}
				MemoryAllocatorLog(pankey_Log_EndMethod, "setMemoryAllocator", "");
				return i_memory_allocator;
			}

			MemoryAllocator* setMemoryAllocator(MemoryAllocator* a_owned_memory_allocator, MemoryAllocator* a_memory_allocator){
				MemoryAllocatorLog(pankey_Log_StartMethod, "setMemoryAllocator", "");
				if(a_owned_memory_allocator == a_memory_allocator){
					return a_owned_memory_allocator;
				}
				if(a_owned_memory_allocator != nullptr){
					if(!a_owned_memory_allocator->isStatic()){
						delete a_owned_memory_allocator;
					}
				}
				MemoryAllocatorLog(pankey_Log_EndMethod, "setMemoryAllocator", "");
				return setMemoryAllocator(a_memory_allocator);
			}

			void destroyMemoryAllocator(MemoryAllocator* a_memory_allocator){
				MemoryAllocatorLog(pankey_Log_StartMethod, "destroyMemoryAllocator", "");
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "destroyMemoryAllocator", "a_memory_allocator == nullptr");
					return;
				}
				if(a_memory_allocator->isStatic()){
					MemoryAllocatorLog(pankey_Log_EndMethod, "destroyMemoryAllocator", "!a_memory_allocator->isManaged()");
					return;
				}
				MemoryAllocatorLog(pankey_Log_EndMethod, "destroyMemoryAllocator", "");
				delete a_memory_allocator;
			}

			template<class T>
			T* allocatePointer(MemoryAllocator* a_memory_allocator){
				MemoryAllocatorLog(pankey_Log_StartMethod, "allocatePointer", "");
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "allocatePointer", "a_memory_allocator == nullptr");
					return new T();
				}
				memory_size i_size = sizeof(T);
				MemoryAllocatorLog(pankey_Log_EndMethod, "allocatePointer", "");
				return (T*)a_memory_allocator->create(i_size);
			}

			template<class T>
			T* allocatePointer(MemoryAllocator* a_memory_allocator, T a_value){
				MemoryAllocatorLog(pankey_Log_StartMethod, "allocatePointer", "");
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "allocatePointer", "a_memory_allocator == nullptr");
					return new T(a_value);
				}
				memory_size i_size = sizeof(T);
				MemoryAllocatorLog(pankey_Log_EndMethod, "allocatePointer", "");
				T* i_value = (T*)a_memory_allocator->create(i_size);
				*i_value = a_value;
				return i_value;
			}

			template<class T>
			T* allocateArray(MemoryAllocator* a_memory_allocator, memory_size a_count){
				MemoryAllocatorLog(pankey_Log_StartMethod, "allocateArray", "");
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "allocateArray", "a_memory_allocator == nullptr");
					return new T[a_count];
				}
				memory_size i_size = sizeof(T);
				MemoryAllocatorLog(pankey_Log_EndMethod, "allocateArray", "");
				return (T*)a_memory_allocator->createArray(i_size, a_count);
			}

			template<class T>
			T** allocatePointerArray(MemoryAllocator* a_memory_allocator, memory_size a_count){
				MemoryAllocatorLog(pankey_Log_StartMethod, "allocatePointerArray", "");
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "allocatePointerArray", "a_memory_allocator == nullptr");
					return new T*[a_count];
				}
				memory_size i_size = sizeof(T);
				MemoryAllocatorLog(pankey_Log_EndMethod, "allocatePointerArray", "");
				return (T**)a_memory_allocator->createPointerArray(i_size, a_count);
			}

			template<class T>
			void deallocatePointer(MemoryAllocator* a_memory_allocator, T* a_pointer){
				MemoryAllocatorLog(pankey_Log_StartMethod, "deallocatePointer", "");
				if(a_pointer == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "deallocatePointer", "a_pointer == nullptr");
					return;
				}
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_Statement, "deallocatePointer", "a_memory_allocator == nullptr");
					delete a_pointer;
					return;
				}
				memory_size i_size = sizeof(T);
				a_memory_allocator->destroy(i_size, a_pointer);
				MemoryAllocatorLog(pankey_Log_EndMethod, "deallocatePointer", "");
			}

			template<class T>
			void deallocateArray(MemoryAllocator* a_memory_allocator, memory_size a_count, T* a_pointer){
				MemoryAllocatorLog(pankey_Log_StartMethod, "deallocateArray", "");
				if(a_pointer == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "deallocateArray", "a_pointer == nullptr");
					return;
				}
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_Statement, "deallocateArray", "a_memory_allocator == nullptr");
					delete[] a_pointer;
					return;
				}
				memory_size i_size = sizeof(T);
				a_memory_allocator->destroyArray(i_size, a_count, a_pointer);
				MemoryAllocatorLog(pankey_Log_EndMethod, "deallocateArray", "");
			}

			template<class T>
			void deallocatePointerArray(MemoryAllocator* a_memory_allocator, memory_size a_count, T** a_pointer){
				MemoryAllocatorLog(pankey_Log_StartMethod, "deallocatePointerArray", "");
				if(a_pointer == nullptr){
					MemoryAllocatorLog(pankey_Log_EndMethod, "deallocatePointerArray", "a_pointer == nullptr");
					return;
				}
				if(a_memory_allocator == nullptr){
					MemoryAllocatorLog(pankey_Log_Statement, "deallocatePointerArray", "a_memory_allocator == nullptr");
					delete[] a_pointer;
					return;
				}
				memory_size i_size = sizeof(T);
				void** i_pointer = reinterpret_cast<void**>(a_pointer);
				a_memory_allocator->destroyPointerArray(i_size, a_count, i_pointer);
				MemoryAllocatorLog(pankey_Log_EndMethod, "deallocatePointerArray", "");
			}

		}

	}

#endif