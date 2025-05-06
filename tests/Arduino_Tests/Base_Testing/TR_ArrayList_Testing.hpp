
#ifndef TR_ArrayList_Testing_hpp
	#define TR_ArrayList_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ArrayList.hpp"

	namespace pankey{

		namespace Base{
			
			TestResult<String> TR_ArrayList_Testing_1(){
				TestResult<String> i_result;
				
				ArrayList<int> i_array;

				i_result.assertTrue("", i_array.isEmpty());
				
				return i_result;
			}
			
			void TR_ArrayList_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("ArrayList isEmpty", TR_ArrayList_Testing_1);
			}
		}
	}

#endif