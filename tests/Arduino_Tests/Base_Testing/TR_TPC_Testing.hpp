
#ifndef TR_TPC_Testing_hpp
	#define TR_TPC_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "TPC.hpp"

	namespace pankey{

		namespace Base{
		
			TestResult<String> TR_TPC_Testing_1(){
				TestResult<String> result;

				TPC i_tpc;
				
				return result;
			}
			
			TestResult<String> TR_TPC_Testing_2(){
				TestResult<String> result;
				

				return result;
			}

			void TR_TPC_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("TPC", TR_TPC_Testing_1);
				a_test_runner.add("TPC", TR_TPC_Testing_2);
			}		

		}		

	}

#endif
