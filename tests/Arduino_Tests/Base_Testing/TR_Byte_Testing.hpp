
#ifndef TR_Byte_Testing_hpp
	#define TR_Byte_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "Byte.hpp"

	namespace pankey{

		namespace Base{
			
			TestResult<String> TR_Byte_Testing_1(){
				TestResult<String> i_result;
				
				Byte i_byte = 10;

				i_result.assertEqual<Byte>("byte should be 10", i_byte, 10);
				
				return i_result;
			}
			
			void TR_Byte_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("Byte", TR_Byte_Testing_1);
			}

		}

	}

#endif