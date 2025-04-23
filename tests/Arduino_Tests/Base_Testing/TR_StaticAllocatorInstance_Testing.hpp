
#ifndef TR_StaticAllocatorInstance_Testing_hpp
	#define TR_StaticAllocatorInstance_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "MemorySize.hpp"
	#include "StaticAllocatorInstance.hpp"

	namespace pankey{

		namespace Base{
		
			TestResult<String> TR_StaticAllocatorInstance_Testing_1(){
				TestResult<String> i_result;
				
				memory_size i_memory = sizeof(int);
				MemoryAllocator* i_allocator = StaticAllocatorInstance<int>::getAllocator();

				i_result.assertNotNull("i_allocator shoudnt be null", i_allocator);

				if(i_allocator == nullptr){
					return i_result;
				}

				void* i_var = i_allocator->create(i_memory);

				i_result.assertNotNull("i_var shoudnt be null", i_var);

				if(i_var == nullptr){
					return i_result;
				}

				int* i_num = (int*)i_var;
				*i_num = 15;
				
				i_result.assertEqual("int should contain a 15", *i_num, 15);
				
				i_allocator->destroy(i_memory, i_var);

				return i_result;
			}

			void TR_StaticAllocatorInstance_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("StaticAllocatorInstance create(memory_size), destroy(memory_size,void*)", TR_StaticAllocatorInstance_Testing_1);
			}		

		}		

	}

#endif
