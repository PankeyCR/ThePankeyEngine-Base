
#ifndef TR_ClassType_Testing_hpp
	#define TR_ClassType_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ClassType.hpp"

	namespace pankey{

		namespace Base{
		
			TestResult<String> TR_ClassType_Testing_1(){
				TestResult<String> i_result;

				long i_int_t = ClassType<int>::getId();
				long i_char_t = ClassType<char>::getId();
				long i_float_t = ClassType<float>::getId();
				long i_long_t = ClassType<long>::getId();
				
				i_result.assertNotEqual("int and char types shoulnt be equal", i_int_t, i_char_t);
				i_result.assertNotEqual("float and long types shoulnt be equal", i_float_t, i_long_t);
				
				return i_result;
			}

			void TR_ClassType_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("ClassType", TR_ClassType_Testing_1);
			}		

		}		

	}

#endif
