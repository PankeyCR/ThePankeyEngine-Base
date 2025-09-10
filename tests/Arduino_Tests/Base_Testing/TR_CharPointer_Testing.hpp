
#ifndef TR_CharPointer_Testing_hpp
	#define TR_CharPointer_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharPointer.hpp"

	namespace pankey{

		namespace Base{
			
			TestResult<String> TR_CharPointer_Testing_1(){
				TestResult<String> i_result;
				
				CharPointer i_pointer = "hellow";

				i_result.assertTrue("value should be hellow", i_pointer == "hellow");
				i_result.assertTrue("value shouldnt be world", i_pointer != "world");
				i_result.assertEqual("length should be 6", i_pointer.length(), 6);
				
				return i_result;
			}
			
			TestResult<String> TR_CharPointer_Testing_2(){
				TestResult<String> i_result;
				
				CharPointer i_pointer = CharPointer("hellow world", 6);

				i_result.assertTrue("value should be hellow", i_pointer == "hellow");
				i_result.assertTrue("value shouldnt be world", i_pointer != "world");
				i_result.assertEqual("length should be 6", i_pointer.length(), 6);
				
				return i_result;
			}
			
			TestResult<String> TR_CharPointer_Testing_3(){
				TestResult<String> i_result;
				
				CharPointer i_pointer_1 = "hellow";
				CharPointer i_pointer_2 = i_pointer_1;

				i_result.assertTrue("value should be hellow", i_pointer_1 == "hellow");
				i_result.assertTrue("value should be hellow", i_pointer_2 == "hellow");
				i_result.assertEqual("length should be 6", i_pointer_1.length(), 6);
				i_result.assertEqual("length should be 6", i_pointer_2.length(), 6);
				
				return i_result;
			}
			
			TestResult<String> TR_CharPointer_Testing_4(){
				TestResult<String> i_result;
				
				CharPointer i_pointer_1 = "hellow";
				CharPointer i_pointer_2 = move(i_pointer_1);

				i_result.assertTrue("value should be hellow", i_pointer_1 != "hellow");
				i_result.assertTrue("value should be hellow", i_pointer_2 == "hellow");
				i_result.assertEqual("length should be 6", i_pointer_1.length(), 0);
				i_result.assertEqual("length should be 6", i_pointer_2.length(), 6);
				
				return i_result;
			}
			
			TestResult<String> TR_CharPointer_Testing_5(){
				TestResult<String> i_result;
				
				CharPointer i_pointer_1 = nullptr;
				CharPointer i_pointer_2 = nullptr;
				CharPointer i_pointer_3 = "hellow";

				i_result.assertTrue("i_pointer_1 == i_pointer_2", i_pointer_1 == i_pointer_2);
				i_result.assertTrue("i_pointer_1 != i_pointer_3", i_pointer_1 != i_pointer_3);
				i_result.assertTrue("i_pointer_1 == nullptr", i_pointer_1 == nullptr);
				i_result.assertTrue("i_pointer_3 == nullptr", i_pointer_3 != nullptr);
				i_result.assertTrue("i_pointer_3 == hellow", i_pointer_3 == "hellow");
				i_result.assertTrue("i_pointer_3 != hellow world", i_pointer_3 != "hellow world");
				i_result.assertTrue("i_pointer_3 != yellow", i_pointer_3 != "yellow");
				
				return i_result;
			}
			
			TestResult<String> TR_CharPointer_Testing_6(){
				TestResult<String> i_result;

				i_result.assertTrue("should be empty, because is null", CharPointer::isEmpty(nullptr));
				i_result.assertTrue("should be empty, because has no length", CharPointer::isEmpty(""));
				i_result.assertTrue("shouldnt be empty", !CharPointer::isEmpty("hellow"));
				
				return i_result;
			}
			
			void TR_CharPointer_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("CharPointer Contructor, ==, !=, length", TR_CharPointer_Testing_1);
				a_test_runner.add("CharPointer Contructor(pointer,length), ==, !=, length", TR_CharPointer_Testing_2);
				a_test_runner.add("CharPointer copy Contructor, ==, length", TR_CharPointer_Testing_3);
				a_test_runner.add("CharPointer move Contructor, ==, length", TR_CharPointer_Testing_4);
				a_test_runner.add("CharPointer ==, !=", TR_CharPointer_Testing_5);
				a_test_runner.add("CharPointer isEmpty", TR_CharPointer_Testing_6);
			}

		}

	}

#endif