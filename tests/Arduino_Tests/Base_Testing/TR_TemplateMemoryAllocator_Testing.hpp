
#ifndef TR_TemplateMemoryAllocator_Testing_hpp
	#define TR_TemplateMemoryAllocator_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "MemorySize.hpp"
	#include "TemplateMemoryAllocator.hpp"

	namespace pankey{

		namespace Base{
		
			TestResult TR_TemplateMemoryAllocator_Testing_1(){
				TestResult i_result;
				
				memory_size i_memory = MemorySize(int);
				TemplateMemoryAllocator<int> i_allocator;
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
		
			TestResult TR_TemplateMemoryAllocator_Testing_2(){
				TestResult i_result;
				
				memory_size i_memory = MemorySize(int);
				TemplateMemoryAllocator<int> i_allocator;
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
		
			TestResult TR_TemplateMemoryAllocator_Testing_3(){
				TestResult i_result;
				
				memory_size i_count = 5;
				memory_size i_memory = ArrayMemorySize(int, i_count);

				TemplateMemoryAllocator<int> i_allocator;
				void* i_var = i_allocator.createArray(i_memory, i_count);

				i_result.assertNotNull("i_var shoudnt be null", i_var);

				if(i_var == nullptr){
					return i_result;
				}

				int* i_num = (int*)i_var;
				i_num[0] = 15;
				
				i_result.assertEqual("int should contain a 15", i_num[0], 15);
				
				i_allocator.destroyArray(i_memory, i_count, i_var);

				return i_result;
			}
		
			TestResult TR_TemplateMemoryAllocator_Testing_4(){
				TestResult i_result;
				
				memory_size i_count = 5;
				memory_size i_memory = ArrayMemorySize(int, i_count);

				TemplateMemoryAllocator<int> i_allocator;
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

			void TR_TemplateMemoryAllocator_Testing(TestRunner& a_test_runner){
				a_test_runner.add("TemplateMemoryAllocator<int> create(memory_size), destroy(memory_size,void*)", TR_TemplateMemoryAllocator_Testing_1);
				a_test_runner.add("TemplateMemoryAllocator<int> create(memory_size), destroy(memory_size)", TR_TemplateMemoryAllocator_Testing_2);
				a_test_runner.add("TemplateMemoryAllocator<int> createArray(memory_size, i_count), destroyArray(memory_size, i_count, void*)", TR_TemplateMemoryAllocator_Testing_3);
				a_test_runner.add("TemplateMemoryAllocator<int> createArray(memory_size, i_count), destroyArray(void*)", TR_TemplateMemoryAllocator_Testing_4);
			}		

		}		

	}

#endif
