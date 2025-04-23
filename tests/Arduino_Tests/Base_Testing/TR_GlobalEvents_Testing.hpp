
#ifndef TR_GlobalEvents_Testing_hpp
	#define TR_GlobalEvents_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "GlobalEvents.hpp"
	#include "CharArray.hpp"

	namespace pankey{

		namespace Base{
	
			void GlobalEventMethod(TestResult<String>& a_result, float a_tpc){
				a_result.assertTrue("executing method", true);
			}
		
			TestResult<String> TR_GlobalEvents_Testing_1(){
				TestResult<String> i_result;

				GlobalEvents<CharArray,TestResult<String>&,float>::clear();

				GlobalEvents<CharArray,TestResult<String>&,float>::put("assert", GlobalEventMethod);

				GlobalEvents<CharArray,TestResult<String>&,float>::run("assert", i_result, 15.5f);

				GlobalEvents<CharArray,TestResult<String>&,float>::clear();
				
				return i_result;
			}
		
			static void GlobalEventMethod2(TestResult<String>& a_result, float a_tpc){
				a_result.assertTrue("executing method", false);
			}
		
			TestResult<String> TR_GlobalEvents_Testing_2(){
				TestResult<String> i_result;

				GlobalEvents<CharArray,TestResult<String>&,float>::clear();

				GlobalEvents<CharArray,TestResult<String>&,float>::put("assert", GlobalEventMethod2);

				GlobalEvents<CharArray,TestResult<String>&,float>::change("assert", GlobalEventMethod);

				GlobalEvents<CharArray,TestResult<String>&,float>::run("assert", i_result, 15.5f);

				GlobalEvents<CharArray,TestResult<String>&,float>::clear();
				
				return i_result;
			}

			void TR_GlobalEvents_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("Application Constructor", TR_GlobalEvents_Testing_1);
				a_test_runner.add("Application getStateManager", TR_GlobalEvents_Testing_2);
			}

		}

	}

#endif
