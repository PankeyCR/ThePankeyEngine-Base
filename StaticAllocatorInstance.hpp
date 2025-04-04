
#ifndef StaticAllocatorInstance_hpp
	#define StaticAllocatorInstance_hpp

    #include "MemoryAllocator.hpp"
    #include "TemplateMemoryAllocator.hpp"

	#if defined(pankey_Log) && (defined(StaticAllocatorInstance_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define StaticAllocatorInstanceLog(status,method,mns) pankey_Log(status,"StaticAllocatorInstance",method,mns)
    #else
        #define StaticAllocatorInstanceLog(status,method,mns)
    #endif

	namespace pankey{

		namespace Base{

            template<class T>
            struct StaticAllocatorInstance{
                static MemoryAllocator* m_Allocator;

                static MemoryAllocator* getAllocator(){
                    StaticAllocatorInstanceLog(pankey_Log_StartMethod, "getAllocator", "");
                    StaticAllocatorInstanceLog(pankey_Log_Statement, "getAllocator",  m_Allocator == nullptr);
                    StaticAllocatorInstanceLog(pankey_Log_EndMethod, "getAllocator", "");
                    return m_Allocator;
                }
            };

            template<class T>
            MemoryAllocator* StaticAllocatorInstance<T>::m_Allocator = new TemplateMemoryAllocator<T>();
            
        }
            
	}

#endif