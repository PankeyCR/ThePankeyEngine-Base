
#ifndef TR_InvokeRawMap_Testing_hpp
	#define TR_InvokeRawMap_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ArrayRawPointerMap.hpp"
	#include "InvokeRawMap.hpp"

	namespace pankey{
		
		TestResult TR_InvokeRawMap_Testing_1(){
			TestResult result;
			
			return result;
		}
		
		TestResult TR_InvokeRawMap_Testing_2(){
			TestResult result;
			

			return result;
		}

		void TR_InvokeRawMap_Testing(TestRunner& a_test_runner){
			a_test_runner.add("ArrayRawPointerMap Simple Constructor", TR_InvokeRawMap_Testing_1);
			a_test_runner.add("ArrayRawPointerMap addPointer", TR_InvokeRawMap_Testing_2);
		}		

	}

#endif
