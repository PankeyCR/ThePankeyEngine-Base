
#ifndef TR_MemorySize_Testing_hpp
	#define TR_MemorySize_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "MemorySize.hpp"

	namespace pankey{

		namespace Base{
		
			TestResult<String> TR_MemorySize_Testing_1(){
				TestResult<String> i_result;

				memory_size i_memory = sizeof(int);
				size_t i_size = sizeof(int);
				
				i_result.assertEqual("int size should be the same for memory_size and size_t", i_memory, i_size);
				
				return i_result;
			}
		
			TestResult<String> TR_MemorySize_Testing_2(){
				TestResult<String> i_result;

				memory_size i_memory = sizeof(char);
				size_t i_size = sizeof(char);
				
				i_result.assertEqual("char size should be the same for memory_size and size_t", i_memory, i_size);
				
				return i_result;
			}

			void TR_MemorySize_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("sizeof int size", TR_MemorySize_Testing_1);
				a_test_runner.add("sizeof char size", TR_MemorySize_Testing_2);
			}		

		}		

	}

#endif
