
#ifndef MemoryAllocator_hpp
	#define MemoryAllocator_hpp

	#include "MemorySize.hpp"

	namespace pankey{

		namespace Base{

			class MemoryAllocator{
				public:
					MemoryAllocator(){}
					MemoryAllocator(bool a_managed){this->m_managed = a_managed;}
					virtual ~MemoryAllocator(){}

					virtual void* create(memory_size a_type_size){return malloc(a_type_size);}
					virtual void* create(){return nullptr;}

					virtual void* createArray(memory_size a_type_size, memory_size a_count){return malloc(a_type_size * a_count);}
					virtual void* createArray(memory_size a_count){return nullptr;}

					virtual void destroy(memory_size a_type_size, void* a_destroy){free(a_destroy);}
					virtual void destroy(void* a_destroy){free(a_destroy);}

					virtual void destroyArray(memory_size a_type_size, memory_size a_count, void* a_destroy){free(a_destroy);}
					virtual void destroyArray(void* a_destroy){free(a_destroy);}

					virtual void isManaged(bool a_managed){
						this->m_managed = a_managed;
					}

					virtual bool isManaged(){
						return this->m_managed;
					}

					virtual MemoryAllocator* clone()const{
						return new MemoryAllocator();
					}

				protected:
					bool m_managed = false;
			};

		}

	}

#endif