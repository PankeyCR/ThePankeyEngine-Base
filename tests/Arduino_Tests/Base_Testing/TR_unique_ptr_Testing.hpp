
#ifndef TR_unique_ptr_Testing_hpp
	#define TR_unique_ptr_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "unique_ptr.hpp"
	#include "Cast.hpp"

	namespace pankey{

		namespace Base{
			
			TestResult<String> TR_unique_ptr_Testing_1(){
				TestResult<String> i_result;
				
				unique_ptr<int> i_pointer = nullptr;

				i_result.assertNull("pointer should be null", i_pointer.get());
				
				return i_result;
			}
			
			TestResult<String> TR_unique_ptr_Testing_2(){
				TestResult<String> i_result;
				
				unique_ptr<int> i_pointer = new int();

				i_result.assertNotNull("pointer shouldnt be null", i_pointer.get());
				
				return i_result;
			}
			
			TestResult<String> TR_unique_ptr_Testing_3(){
				TestResult<String> i_result;
				
				unique_ptr<int> i_pointer = new int(15);

				i_result.assertEqual("pointer value should be equal to 15", *i_pointer, 15);
				
				return i_result;
			}
			
			TestResult<String> TR_unique_ptr_Testing_4(){
				TestResult<String> i_result;
				
				unique_ptr<int> i_pointer = new int(15);
				unique_ptr<int> i_pointer_2 = move(i_pointer);

				i_result.assertNull("pointer should be null", i_pointer.get());
				i_result.assertEqual("pointer value should be equal to 15", *i_pointer_2, 15);
				
				return i_result;
			}
			
			TestResult<String> TR_unique_ptr_Testing_5(){
				TestResult<String> i_result;
				
				unique_ptr<int> i_pointer = new int(15);
				unique_ptr<int> i_pointer_2;
				i_pointer_2 = move(i_pointer);

				i_result.assertNull("pointer should be null", i_pointer.get());
				i_result.assertEqual("pointer value should be equal to 15", *i_pointer_2, 15);
				
				return i_result;
			}
			
			void TR_unique_ptr_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("unique_ptr get, nullptr", TR_unique_ptr_Testing_1);
				a_test_runner.add("unique_ptr get", TR_unique_ptr_Testing_2);
				a_test_runner.add("unique_ptr *", TR_unique_ptr_Testing_3);
				a_test_runner.add("unique_ptr move contructor", TR_unique_ptr_Testing_4);
				a_test_runner.add("unique_ptr operator move", TR_unique_ptr_Testing_5);
			}
		}
	}

#endif