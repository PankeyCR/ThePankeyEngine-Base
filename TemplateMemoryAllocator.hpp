
#ifndef TemplateMemoryAllocator_hpp
	#define TemplateMemoryAllocator_hpp

	#include "MemoryAllocator.hpp"
	#include "MemorySize.hpp"

	#if defined(pankey_Log) && (defined(TemplateMemoryAllocator_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
        #define TemplateMemoryAllocatorLog(status,method,mns) pankey_Log(status,"TemplateMemoryAllocator",method,mns)
    #else
        #define TemplateMemoryAllocatorLog(status,method,mns)
    #endif

	namespace pankey{

		namespace Base{

			template<class T>
			class TemplateMemoryAllocator : public MemoryAllocator{
				public:
					TemplateMemoryAllocator(){}
					TemplateMemoryAllocator(bool a_static){this->m_static = a_static;}
					virtual ~TemplateMemoryAllocator(){}

					virtual void* create(memory_size a_type_size){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "create", "");
						if(a_type_size != sizeof(T)){
							return nullptr;
						}
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "create", "");
						return new T();
					}

					virtual void* create(){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "create", "");
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "create", "");
						return new T();
					}

					virtual void* createArray(memory_size a_type_size, memory_size a_count){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "createArray", "");
						if(a_type_size != sizeof(T)){
							return nullptr;
						}
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "createArray", "");
						return new T[a_count];
					}

					virtual void* createArray(memory_size a_count){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "createArray", "");
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "createArray", "");
						return new T[a_count];
					}
					
					virtual void destroy(memory_size a_type_size, void* a_destroy){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						if(a_destroy == nullptr){
							return;
						}
						if(a_type_size != sizeof(T)){
							return;
						}
						T* i_var = (T*)a_destroy;
						delete i_var;
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}
					
					virtual void destroy(void* a_destroy){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						if(a_destroy == nullptr){
							return;
						}
						T* i_var = (T*)a_destroy;
						delete i_var;
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}

					virtual void destroyArray(memory_size a_type_size, memory_size a_count, void* a_destroy){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						if(a_destroy == nullptr){
							return;
						}
						T* i_var = (T*)a_destroy;
						delete[] i_var;
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}

					virtual void destroyArray(void* a_destroy){
						TemplateMemoryAllocatorLog(pankey_Log_StartMethod, "destroy", "");
						if(a_destroy == nullptr){
							return;
						}
						T* i_var = (T*)a_destroy;
						delete[] i_var;
						TemplateMemoryAllocatorLog(pankey_Log_EndMethod, "destroy", "");
					}

					virtual MemoryAllocator* clone()const{
						return new TemplateMemoryAllocator<T>();
					}
			};

		}

	}

#endif