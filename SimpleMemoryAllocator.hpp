
#ifndef SimpleMemoryAllocator_hpp
	#define SimpleMemoryAllocator_hpp

	#include "MemoryAllocator.hpp"

	#if defined(pankey_Log) && (defined(SimpleMemoryAllocator_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define SimpleMemoryAllocatorLog(status,method,mns) pankey_Log(status,"SimpleMemoryAllocator",method,mns)
    #else
        #define SimpleMemoryAllocatorLog(status,method,mns)
    #endif

	namespace pankey{

		namespace Base{

			template<class T>
			class SimpleMemoryAllocator : public MemoryAllocator{
				public:
					SimpleMemoryAllocator(){
						m_managed = true;
					}
					SimpleMemoryAllocator(T* a_pointer){
						m_pointer = a_pointer;
						m_managed = true;
					}
					virtual ~SimpleMemoryAllocator(){}

					virtual void* create(memory_size a_size){
						SimpleMemoryAllocatorLog(pankey_Log_StartMethod, "create", "");
						if(m_pointer == nullptr){
							m_pointer = new T();
						}
						SimpleMemoryAllocatorLog(pankey_Log_EndMethod, "create", "");
						return m_pointer;
					}

					virtual void* create(){
						SimpleMemoryAllocatorLog(pankey_Log_StartMethod, "create", "");
						if(m_pointer == nullptr){
							m_pointer = new T();
						}
						SimpleMemoryAllocatorLog(pankey_Log_EndMethod, "create", "");
						return m_pointer;
					}
					virtual void destroy(memory_size a_size, void* a_destroy){
						SimpleMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						if(m_pointer == nullptr){
							return;
						}
						delete m_pointer;
						SimpleMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}
					virtual void destroy(void* a_destroy){
						SimpleMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						if(m_pointer == nullptr){
							return;
						}
						delete m_pointer;
						SimpleMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}
				protected:
					T* m_pointer = nullptr;
			};

		}

	}

#endif