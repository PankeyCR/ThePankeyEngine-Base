
#ifndef TR_CharArray_Testing_hpp
	#define TR_CharArray_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "CharArray.hpp"

	namespace pankey{

		namespace Base{
			
			TestResult<String> TR_CharArray_Testing_1(){
				TestResult<String> i_result;

				CharArray i_bool_1 = CharArray(true);
				CharArray i_bool_2 = CharArray(false);
				
				i_result.assertEqual("CharArray = true Constructor Bool", i_bool_1.get(0), '1');
				i_result.assertEqual("CharArray = true length", i_bool_1.length(), 1);
				i_result.assertTrue("CharArray = true should be bool", i_bool_1.isBool());
				
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(0), '0');
				i_result.assertEqual("CharArray = false length", i_bool_2.length(), 1);
				i_result.assertTrue("CharArray = false should be bool", i_bool_2.isBool());
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_2(){
				TestResult<String> i_result;

				CharArray i_bool_1;
				CharArray i_bool_2;

				i_bool_1.setBool(false, true);
				i_bool_2.setBool(false, false);
				
				i_result.assertEqual("CharArray = true Constructor Bool", i_bool_1.get(0), 't');
				i_result.assertEqual("CharArray = true Constructor Bool", i_bool_1.get(1), 'r');
				i_result.assertEqual("CharArray = true Constructor Bool", i_bool_1.get(2), 'u');
				i_result.assertEqual("CharArray = true Constructor Bool", i_bool_1.get(3), 'e');
				i_result.assertEqual("CharArray = true length", i_bool_1.length(), 4);
				i_result.assertTrue("CharArray = true should be bool", i_bool_1.isBool());
				
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(0), 'f');
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(1), 'a');
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(2), 'l');
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(3), 's');
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(4), 'e');
				i_result.assertEqual("CharArray = false length", i_bool_2.length(), 5);
				i_result.assertTrue("CharArray = false should be bool", i_bool_2.isBool());
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_3(){
				TestResult<String> i_result;

				CharArray i_bool_1;
				CharArray i_bool_2;

				i_bool_1.setBool(true);
				i_bool_2.setBool(false);
				
				i_result.assertEqual("CharArray = true Constructor Bool", i_bool_1.get(0), '1');
				i_result.assertEqual("CharArray = true length", i_bool_1.length(), 1);
				i_result.assertTrue("CharArray = true should be bool", i_bool_1.isBool());
				
				i_result.assertEqual("CharArray = false Constructor Bool", i_bool_2.get(0), '0');
				i_result.assertEqual("CharArray = false length", i_bool_2.length(), 1);
				i_result.assertTrue("CharArray = false should be bool", i_bool_2.isBool());
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_4(){
				TestResult<String> i_result;

				CharArray i_str_1 = "hellow world";
				CharArray i_str_2 = "hellow world";
				CharArray i_str_3 = "yellow world";
				CharArray i_str_4 = "hellow";
				
				i_result.assertTrue("i_str_1 == i_str_2", i_str_1 == i_str_2);
				i_result.assertTrue("!(i_str_1 != i_str_2)", !(i_str_1 != i_str_2));
				i_result.assertTrue("i_str_1 != i_str_3", i_str_1 != i_str_3);
				i_result.assertTrue("!(i_str_1 == i_str_3)", !(i_str_1 == i_str_3));
				i_result.assertTrue("i_str_1 != i_str_4", i_str_1 != i_str_4);
				i_result.assertTrue("!(i_str_1 == i_str_4)", !(i_str_1 == i_str_4));
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_5(){
				TestResult<String> i_result;

				CharArray i_str_1 = "hellow world";
				
				i_result.assertTrue("i_str_1 == hellow world", i_str_1 == "hellow world");
				i_result.assertTrue("!(i_str_1 != hellow world)", !(i_str_1 != "hellow world"));
				i_result.assertTrue("i_str_1 != yellow world", i_str_1 != "yellow world");
				i_result.assertTrue("!(i_str_1 == yellow world)", !(i_str_1 == "yellow world"));
				i_result.assertTrue("i_str_1 != hellow", i_str_1 != "hellow");
				i_result.assertTrue("!(i_str_1 == hellow)", !(i_str_1 == "hellow"));
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_6(){
				TestResult<String> i_result;

				CharArray i_bool_1 = CharArray(true);
				CharArray i_bool_2 = CharArray(false);

				bool i_to_bool_1 = i_bool_1.toBool();
				bool i_to_bool_2 = i_bool_2.toBool();
				
				i_result.assertEqual("CharArray = true Constructor Bool", i_to_bool_1, true);
				
				i_result.assertEqual("CharArray = false Constructor Bool", i_to_bool_2, false);
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_7(){
				TestResult<String> i_result;

				int i_positive_size = CharArray::intCharSize(12345);
				int i_negative_size = CharArray::intCharSize(-12345);
				
				i_result.assertEqual("CharArray intCharSize 12345", i_positive_size, 5);
				i_result.assertEqual("CharArray intCharSize -12345", i_negative_size, 6);
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_8(){
				TestResult<String> i_result;
				
				i_result.assertTrue("CharArray 0 is number", CharArray::isNumber('0'));
				i_result.assertTrue("CharArray 1 is number", CharArray::isNumber('1'));
				i_result.assertTrue("CharArray 2 is number", CharArray::isNumber('2'));
				i_result.assertTrue("CharArray 3 is number", CharArray::isNumber('3'));
				i_result.assertTrue("CharArray 4 is number", CharArray::isNumber('4'));
				i_result.assertTrue("CharArray 5 is number", CharArray::isNumber('5'));
				i_result.assertTrue("CharArray 6 is number", CharArray::isNumber('6'));
				i_result.assertTrue("CharArray 7 is number", CharArray::isNumber('7'));
				i_result.assertTrue("CharArray 8 is number", CharArray::isNumber('8'));
				i_result.assertTrue("CharArray 9 is number", CharArray::isNumber('9'));

				i_result.assertTrue("CharArray a is not number", !CharArray::isNumber('a'));
				i_result.assertTrue("CharArray z is not number", !CharArray::isNumber('z'));
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_9(){
				TestResult<String> i_result;
				
				i_result.assertEqual("CharArray 0 is number", CharArray::getNumber('0'), 0);
				i_result.assertEqual("CharArray 1 is number", CharArray::getNumber('1'), 1);
				i_result.assertEqual("CharArray 2 is number", CharArray::getNumber('2'), 2);
				i_result.assertEqual("CharArray 3 is number", CharArray::getNumber('3'), 3);
				i_result.assertEqual("CharArray 4 is number", CharArray::getNumber('4'), 4);
				i_result.assertEqual("CharArray 5 is number", CharArray::getNumber('5'), 5);
				i_result.assertEqual("CharArray 6 is number", CharArray::getNumber('6'), 6);
				i_result.assertEqual("CharArray 7 is number", CharArray::getNumber('7'), 7);
				i_result.assertEqual("CharArray 8 is number", CharArray::getNumber('8'), 8);
				i_result.assertEqual("CharArray 9 is number", CharArray::getNumber('9'), 9);

				i_result.assertEqual("CharArray a is not number", CharArray::getNumber('a'), -1);
				i_result.assertEqual("CharArray z is not number", CharArray::getNumber('z'), -1);
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_10(){
				TestResult<String> i_result;
				
				i_result.assertTrue("CharArray should be a decimal point", CharArray::isDecimalPoint('.'));
				i_result.assertTrue("CharArray shouldnt be a decimal point", !CharArray::isDecimalPoint('1'));
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_11(){
				TestResult<String> i_result;

				CharArray i_int_1 = CharArray(12345);
				CharArray i_int_2 = CharArray(-12345);
				
				i_result.assertTrue("CharArray should be int", i_int_1.isInt());
				i_result.assertTrue("CharArray shouldnt be int", i_int_2.isInt());
				
				i_result.assertTrue("CharArray shouldnt be negative int", i_int_1.isPositiveInt());
				i_result.assertTrue("CharArray should be negative int", !i_int_2.isPositiveInt());
				
				i_result.assertTrue("CharArray shouldnt be negative int", !i_int_1.isNegativeInt());
				i_result.assertTrue("CharArray should be negative int", i_int_2.isNegativeInt());
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_12(){
				TestResult<String> i_result;

				CharArray i_int_1 = CharArray(12345);
				CharArray i_int_2 = CharArray(-12345);
				
				i_result.assertEqual("CharArray int should be 12345", i_int_1.toInt(), 12345);
				i_result.assertNotEqual("CharArray int shouldnt be 54321", i_int_1.toInt(), 54321);
				i_result.assertEqual("CharArray int should be -12345", i_int_2.toInt(), -12345);
				i_result.assertNotEqual("CharArray int should be -54321", i_int_2.toInt(), -54321);
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_13(){
				TestResult<String> i_result;

				CharArray i_str = "hellow";
				i_str.addCharPointer(" world");
				
				i_result.assertTrue("CharArray should be hellow world", i_str == "hellow world");
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_14(){
				TestResult<String> i_result;

				CharArray i_str_1 = "hellow";
				CharArray i_str_2 = i_str_1 + " world";
				
				i_result.assertTrue("CharArray should be hellow world", i_str_2 == "hellow world");
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_15(){
				TestResult<String> i_result;

				CharArray i_str_1 = "hellow";
				CharArray i_str_2 = " ";
				CharArray i_str_3 = "world";
				CharArray i_str_4 = i_str_1 + i_str_2 + i_str_3;
				
				i_result.assertTrue("CharArray should be hellow world", i_str_4 == "hellow world");
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_16(){
				TestResult<String> i_result;

				CharArray i_str_1 = "hellow world";
				CharPointer i_pointer = i_str_1.c_str();
				
				i_result.assertTrue("CharPointer should be hellow world", i_pointer == "hellow world");
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_17(){
				TestResult<String> i_result;

				CharArray i_str = CharArray('x');
				
				i_result.assertEqual("CharArray should be x", i_str.get(0), 'x');
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_18(){
				TestResult<String> i_result;
				
				i_result.assertEqual("CharArray long size should be 6", CharArray::longCharSize(123456l), 6);
				i_result.assertEqual("CharArray long size should be 10", CharArray::longCharSize(123456789l), 9);
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_19(){
				TestResult<String> i_result;

				CharArray i_long = CharArray(123456789l);
				
				i_result.assertEqual("CharArray length should be 10", i_long.length(), 9);
				i_result.assertEqual("CharArray at index 0 should be 1", i_long.get(0), '1');
				i_result.assertEqual("CharArray at index 8 should be 9", i_long.get(8), '9');
				i_result.assertTrue("CharArray should be a long", i_long.isLong());
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_20(){
				TestResult<String> i_result;
				
				i_result.assertEqual("Decimals should be 0.12f", CharArray::getDecimals(152.12f, 4, true), 0.12f);
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_21(){
				TestResult<String> i_result;

				CharArray i_float = CharArray(152.1234f);
				
				i_result.assertEqual("CharArray length should be 8", i_float.length(), 6);
				i_result.assertEqual("CharArray value at 0 should be 1", i_float.get(0), '1');
				i_result.assertEqual("CharArray value at 1 should be 5", i_float.get(1), '5');
				i_result.assertEqual("CharArray value at 2 should be 2", i_float.get(2), '2');
				i_result.assertEqual("CharArray value at 3 should be .", i_float.get(3), '.');
				i_result.assertEqual("CharArray value at 4 should be 1", i_float.get(4), '1');
				i_result.assertEqual("CharArray value at 5 should be 2", i_float.get(5), '2');
				
				return i_result;
			}
			
			TestResult<String> TR_CharArray_Testing_22(){
				TestResult<String> i_result;

				CharArray i_float = CharArray("float: ") + CharArray(15);
				
				i_result.assertTrue("CharArray should be float: 15", i_float == "float: 15");
				
				return i_result;
			}
			
			void TR_CharArray_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("CharArray Constructor(bool)", TR_CharArray_Testing_1);
				a_test_runner.add("CharArray setBool(bool,bool)", TR_CharArray_Testing_2);
				a_test_runner.add("CharArray setBool(bool)", TR_CharArray_Testing_3);
				a_test_runner.add("CharArray ==(CharArray)", TR_CharArray_Testing_4);
				a_test_runner.add("CharArray ==(char*)", TR_CharArray_Testing_5);
				a_test_runner.add("CharArray toBool", TR_CharArray_Testing_6);
				a_test_runner.add("CharArray intCharSize", TR_CharArray_Testing_7);
				a_test_runner.add("CharArray isNumber(char)", TR_CharArray_Testing_8);
				a_test_runner.add("CharArray getNumber(char)", TR_CharArray_Testing_9);
				a_test_runner.add("CharArray isDecimalPoint(char)", TR_CharArray_Testing_10);
				a_test_runner.add("CharArray setInt", TR_CharArray_Testing_11);
				a_test_runner.add("CharArray toInt", TR_CharArray_Testing_12);
				a_test_runner.add("CharArray addCharPointer", TR_CharArray_Testing_13);
				a_test_runner.add("CharArray +(char*)", TR_CharArray_Testing_14);
				a_test_runner.add("CharArray +(const CharArray&)", TR_CharArray_Testing_15);
				a_test_runner.add("CharArray c_str, CharPointer==", TR_CharArray_Testing_16);
				a_test_runner.add("CharArray Constructor(char)", TR_CharArray_Testing_17);
				a_test_runner.add("CharArray longCharSize", TR_CharArray_Testing_18);
				a_test_runner.add("CharArray Constructor(long)", TR_CharArray_Testing_19);
				a_test_runner.add("CharArray getDecimals", TR_CharArray_Testing_20);
				a_test_runner.add("CharArray setFloat", TR_CharArray_Testing_21);
				a_test_runner.add("CharArray operator+", TR_CharArray_Testing_22);
			}
		}
	}

#endif