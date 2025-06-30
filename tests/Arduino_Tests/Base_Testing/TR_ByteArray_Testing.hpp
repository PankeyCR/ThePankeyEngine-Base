
#ifndef TR_ByteArray_Testing_hpp
	#define TR_ByteArray_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ByteArray.hpp"

	namespace pankey{

		namespace Base{
			
			TestResult<String> TR_ByteArray_Testing_1(){
				TestResult<String> i_result;
				
				ByteArray i_array = serialize( createArrayPointer<int>(10,11,12,13) );

				i_result.assertEqual<Byte>("ByteArray should be 10", i_array.get(0), 10);
				i_result.assertEqual<Byte>("ByteArray should be 10", i_array.get(1), 11);
				i_result.assertEqual<Byte>("ByteArray should be 10", i_array.get(2), 12);
				i_result.assertEqual<Byte>("ByteArray should be 10", i_array.get(3), 13);
				
				return i_result;
			}
			
			void TR_ByteArray_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("ByteArray", TR_ByteArray_Testing_1);
			}

		}

	}

#endif