
#ifndef SelfMemoryAllocator_hpp
	#define SelfMemoryAllocator_hpp

	#include "MemoryAllocator.hpp"

	#if defined(pankey_Log) && (defined(SelfMemoryAllocator_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define SelfMemoryAllocatorLog(status,method,mns) pankey_Log(status,"SelfMemoryAllocator",method,mns)
    #else
        #define SelfMemoryAllocatorLog(status,method,mns)
    #endif

	namespace pankey{

		namespace Base{

			template<class T>
			class SelfMemoryAllocator : public MemoryAllocator{
				public:
					SelfMemoryAllocator(T* a_pointer){
						m_pointer = a_pointer;
						m_managed = true;
					}
					virtual ~SelfMemoryAllocator(){}

					virtual void* create(memory_size a_size){
						SelfMemoryAllocatorLog(pankey_Log_StartMethod, "create", "");
						SelfMemoryAllocatorLog(pankey_Log_EndMethod, "create", "");
						return m_pointer;
					}

					virtual void* create(){
						SelfMemoryAllocatorLog(pankey_Log_StartMethod, "create", "");
						SelfMemoryAllocatorLog(pankey_Log_EndMethod, "create", "");
						return m_pointer;
					}
					virtual void destroy(void* a_destroy){
						SelfMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						SelfMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}
				protected:
					T* m_pointer = nullptr;
			};

		}

	}

#endif