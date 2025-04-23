
#ifndef TR_MemoryAllocator_Testing_hpp
	#define TR_MemoryAllocator_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "MemorySize.hpp"
	#include "MemoryAllocator.hpp"

	namespace pankey{

		namespace Base{
		
			TestResult<String> TR_MemoryAllocator_Testing_1(){
				TestResult<String> i_result;
				
				memory_size i_memory = sizeof(int);
				MemoryAllocator i_allocator;
				void* i_var = i_allocator.create(i_memory);

				i_result.assertNotNull("i_var shoudnt be null", i_var);

				if(i_var == nullptr){
					return i_result;
				}

				int* i_num = (int*)i_var;
				*i_num = 15;
				
				i_result.assertEqual("int should contain a 15", *i_num, 15);
				
				i_allocator.destroy(i_memory, i_var);

				return i_result;
			}
		
			TestResult<String> TR_MemoryAllocator_Testing_2(){
				TestResult<String> i_result;
				
				memory_size i_memory = sizeof(int);
				MemoryAllocator i_allocator;
				void* i_var = i_allocator.create(i_memory);

				i_result.assertNotNull("i_var shoudnt be null", i_var);

				if(i_var == nullptr){
					return i_result;
				}

				int* i_num = (int*)i_var;
				*i_num = 15;
				
				i_result.assertEqual("int should contain a 15", *i_num, 15);
				
				i_allocator.destroy(i_var);

				return i_result;
			}
		
			TestResult<String> TR_MemoryAllocator_Testing_3(){
				TestResult<String> i_result;
				
				memory_size i_count = 5;
				memory_size i_memory = sizeof(int);

				MemoryAllocator i_allocator;
				void* i_var = i_allocator.createArray(i_memory, i_count);

				i_result.assertNotNull("i_var shoudnt be null", i_var);

				if(i_var == nullptr){
					return i_result;
				}

				int* i_num = (int*)i_var;
				*i_num = 15;
				
				i_result.assertEqual("int should contain a 15", *i_num, 15);
				
				i_allocator.destroyArray(i_memory, i_count, i_var);

				return i_result;
			}
		
			TestResult<String> TR_MemoryAllocator_Testing_4(){
				TestResult<String> i_result;
				
				memory_size i_count = 5;
				memory_size i_memory = sizeof(int);

				MemoryAllocator i_allocator;
				void* i_var = i_allocator.createArray(i_memory, i_count);

				i_result.assertNotNull("i_var shoudnt be null", i_var);

				if(i_var == nullptr){
					return i_result;
				}

				int* i_num = (int*)i_var;
				*i_num = 15;
				
				i_result.assertEqual("int should contain a 15", *i_num, 15);
				
				i_allocator.destroyArray(i_var);

				return i_result;
			}

			void TR_MemoryAllocator_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("MemoryAllocator create(memory_size), destroy(memory_size,void*)", TR_MemoryAllocator_Testing_1);
				a_test_runner.add("MemoryAllocator create(memory_size), destroy(void*)", TR_MemoryAllocator_Testing_2);
				a_test_runner.add("MemoryAllocator createArray(memory_size, i_count), destroyArray(memory_size, i_count, void*)", TR_MemoryAllocator_Testing_3);
				a_test_runner.add("MemoryAllocator createArray(memory_size, i_count), destroyArray(void*)", TR_MemoryAllocator_Testing_4);
			}		

		}		

	}

#endif
