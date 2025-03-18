
#ifndef TR_GlobalEvents_Testing_hpp
	#define TR_GlobalEvents_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "GlobalEvents.hpp"
	#include "CharArray.hpp"

	namespace pankey{

		namespace Base{
	
			void GlobalEventMethod(TestResult& a_result, float a_tpc){
				a_result.assertTrue("executing method", true);
			}
		
			TestResult TR_GlobalEvents_Testing_1(){
				TestResult i_result;

				GlobalEvents<CharArray,TestResult&,float>::clear();

				GlobalEvents<CharArray,TestResult&,float>::put("assert", GlobalEventMethod);

				GlobalEvents<CharArray,TestResult&,float>::run("assert", i_result, 15.5f);

				GlobalEvents<CharArray,TestResult&,float>::clear();
				
				return i_result;
			}
		
			static void GlobalEventMethod2(TestResult& a_result, float a_tpc){
				a_result.assertTrue("executing method", false);
			}
		
			TestResult TR_GlobalEvents_Testing_2(){
				TestResult i_result;

				GlobalEvents<CharArray,TestResult&,float>::clear();

				GlobalEvents<CharArray,TestResult&,float>::put("assert", GlobalEventMethod2);

				GlobalEvents<CharArray,TestResult&,float>::change("assert", GlobalEventMethod);

				GlobalEvents<CharArray,TestResult&,float>::run("assert", i_result, 15.5f);

				GlobalEvents<CharArray,TestResult&,float>::clear();
				
				return i_result;
			}

			void TR_GlobalEvents_Testing(TestRunner& a_test_runner){
				a_test_runner.add("Application Constructor", TR_GlobalEvents_Testing_1);
				a_test_runner.add("Application getStateManager", TR_GlobalEvents_Testing_2);
			}

		}

	}

#endif
