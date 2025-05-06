
#ifndef TR_InvokeRawList_Testing_hpp
	#define TR_InvokeRawList_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ArrayRawPointerList.hpp"
	#include "InvokeRawList.hpp"

	namespace pankey{

		namespace Base{

			void TestMethod(TestResult<String>& a_result){
				a_result.assertTrue("executing method", true);
			}

			void TestMethod_2(TestResult<String>& a_result){
				a_result.assertEqual("executing method 2", 1, 1);
			}

			int TestMethod_3(TestResult<String>& a_result){
				a_result.assertEqual("executing method 3", 1, 1);
				return 1;
			}

			int TestMethod_4(TestResult<String>& a_result){
				a_result.assertEqual("executing method 3", 1, 1);
				return 2;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_1(){
				TestResult<String> result;

				FunctionList<> i_list;

				result.assertTrue("list has to be empty", i_list.isEmpty());
				
				return result;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_2(){
				TestResult<String> result;

				FunctionList<float> i_list;

				result.assertTrue("list has to be empty", i_list.isEmpty());
				
				return result;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_3(){
				TestResult<String> result;

				FunctionList<TestResult<String>&> i_list;

				i_list.add(TestMethod);

				invoke<TestResult<String>&>(i_list, 0, result);
				
				return result;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_4(){
				TestResult<String> result;

				FunctionList<TestResult<String>&> i_list;

				i_list.add(TestMethod);
				i_list.add(TestMethod_2);

				invokeAll<TestResult<String>&>(i_list, result);
				
				return result;
			}

			class InvokeExample{
				public:
				void TestMethod(TestResult<String>& a_result){
					a_result.assertTrue("executing method", true);
				}
				void TestMethod_2(TestResult<String>& a_result){
					a_result.assertTrue("executing method", true);
				}
				int TestMethod_3(TestResult<String>& a_result){
					a_result.assertTrue("executing method", true);
					return 1;
				}
				int TestMethod_4(TestResult<String>& a_result){
					a_result.assertTrue("executing method", true);
					return 2;
				}
			};
			
			TestResult<String> TR_InvokeRawList_Testing_5(){
				TestResult<String> result;

				ClassFunctionList<InvokeExample,TestResult<String>&> i_list;

				i_list.add(&InvokeExample::TestMethod);
				i_list.add(&InvokeExample::TestMethod_2);

				InvokeExample example;

				invoke<InvokeExample,TestResult<String>&>(i_list, example, 0, result);
				
				return result;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_6(){
				TestResult<String> result;

				ClassFunctionList<InvokeExample,TestResult<String>&> i_list;

				i_list.add(&InvokeExample::TestMethod);
				i_list.add(&InvokeExample::TestMethod_2);

				InvokeExample example;

				invokeAll<InvokeExample,TestResult<String>&>(i_list, example, result);
				
				return result;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_7(){
				TestResult<String> result;

				FunctionReturnList<int,TestResult<String>&> i_list;

				i_list.add(TestMethod_3);
				i_list.add(TestMethod_4);

				InvokeExample example;

				int i_num = invoke<int,TestResult<String>&>(i_list, 0, result);

				result.assertEqual("i_num should be 1", i_num, 1);
				
				return result;
			}
			
			TestResult<String> TR_InvokeRawList_Testing_8(){
				TestResult<String> result;

				ClassFunctionReturnList<InvokeExample,int,TestResult<String>&> i_list;

				i_list.add(&InvokeExample::TestMethod_3);
				i_list.add(&InvokeExample::TestMethod_4);

				InvokeExample example;

				int i_num = invoke<InvokeExample,int,TestResult<String>&>(i_list, example, 0, result);

				result.assertEqual("i_num should be 1", i_num, 1);
				
				return result;
			}

			void TR_InvokeRawList_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("FunctionList Constructor with no arguments", TR_InvokeRawList_Testing_1);
				a_test_runner.add("FunctionList Constructor with 1 float arguments", TR_InvokeRawList_Testing_2);
				a_test_runner.add("FunctionList invoke with TestResult<String>& argument", TR_InvokeRawList_Testing_3);
				a_test_runner.add("FunctionList invokeAll with TestResult<String>& argument", TR_InvokeRawList_Testing_4);
				a_test_runner.add("FunctionList invoke class with TestResult<String>& argument", TR_InvokeRawList_Testing_5);
				a_test_runner.add("FunctionList invokeAll class with TestResult<String>& argument", TR_InvokeRawList_Testing_6);
				a_test_runner.add("FunctionList invoke return with TestResult<String>& argument", TR_InvokeRawList_Testing_7);
				a_test_runner.add("FunctionList invoke class return with TestResult<String>& argument", TR_InvokeRawList_Testing_8);
			}

		}

	}

#endif
