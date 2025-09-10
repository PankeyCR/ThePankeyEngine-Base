
#ifndef TR_ArrayPointer_Testing_hpp
	#define TR_ArrayPointer_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "ArrayPointer.hpp"
	#include "TemplateMemoryAllocator.hpp"

	namespace pankey{

		namespace Base{
			
			class ArrayPointerExample{
				public:
				int* m_int = nullptr;
				ArrayPointerExample(int x){m_int = new int(x);}
				ArrayPointerExample(){m_int = new int();}
				ArrayPointerExample(const ArrayPointerExample& a_example){
					m_int = new int();
					*m_int = *a_example.m_int;
				}
				ArrayPointerExample(ArrayPointerExample&& a_example){
					m_int = a_example.m_int;
					a_example.m_int = nullptr;
				}
				virtual ~ArrayPointerExample(){delete m_int;}
				void operator=(const ArrayPointerExample& a_example){
					m_int = new int();
					*m_int = *a_example.m_int;
				}
				void operator=(ArrayPointerExample&& a_example){
					if(m_int != nullptr){
						delete m_int;
					}
					m_int = a_example.m_int;
					a_example.m_int = nullptr;
				}
				bool operator==(const ArrayPointerExample& a_example){
					if(a_example.m_int == nullptr && m_int == nullptr){
						return true;
					}
					if(a_example.m_int == nullptr || m_int == nullptr){
						return false;
					}
					return *a_example.m_int == *m_int;
				}
				bool operator!=(const ArrayPointerExample& a_example){
					if(a_example.m_int == nullptr && m_int == nullptr){
						return false;
					}
					if(a_example.m_int == nullptr || m_int == nullptr){
						return true;
					}
					return *a_example.m_int != *m_int;
				}
				int get(){return *m_int;}
			};
			TestResult<String> TR_ArrayPointer_Testing_1(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.createArray(10);

				result.assertEqual("array size should be 10", array.getSize(), 10);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_2(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.createArrayFast(10);

				result.assertEqual("array size should be 10", array.getSize(), 10);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_3(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.expand(10);

				result.assertEqual("array size should be 10", array.getSize(), 10);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_4(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.expand(10);
				array.shrink(5);

				result.assertEqual("array size should be 5", array.getSize(), 5);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_5(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.expand(10);
				array.clear();

				result.assertEqual("array size should be 5", array.getSize(), 0);
				result.assertTrue("array should be empty", array.isEmpty());
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_6(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				int i_1 = 10;
				int i_2 = 20;
				int i_3 = 30;

				array.add(i_1);
				array.add(i_2);
				array.add(i_3);

				result.assertEqual("array last index should be 0", array.get(0), 10);
				result.assertEqual("array last index should be 0", array.get(1), 20);
				result.assertEqual("array last index should be 0", array.get(2), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 3);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_7(){
				TestResult<String> result;
				
				ArrayPointer<ArrayPointerExample> array;

				array.add(ArrayPointerExample(10));
				array.add(ArrayPointerExample(20));
				array.add(ArrayPointerExample(30));

				result.assertEqual("array last index should be 0", array.get(0).get(), 10);
				result.assertEqual("array last index should be 0", array.get(1).get(), 20);
				result.assertEqual("array last index should be 0", array.get(2).get(), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 3);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_8(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.createArrayFast(10);

				int i_1 = 10;
				int i_2 = 20;
				int i_3 = 30;

				array.addFast(i_1);
				array.addFast(i_2);
				array.addFast(i_3);

				result.assertEqual("array last index should be 0", array.get(0), 10);
				result.assertEqual("array last index should be 0", array.get(1), 20);
				result.assertEqual("array last index should be 0", array.get(2), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 3);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_9(){
				TestResult<String> result;
				
				ArrayPointer<ArrayPointerExample> array;

				array.createArrayFast(10);

				array.addFast(ArrayPointerExample(10));
				array.addFast(ArrayPointerExample(20));
				array.addFast(ArrayPointerExample(30));

				result.assertEqual("array last index should be 0", array.get(0).get(), 10);
				result.assertEqual("array last index should be 0", array.get(1).get(), 20);
				result.assertEqual("array last index should be 0", array.get(2).get(), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 3);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_10(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				int i_1 = 10;
				int i_2 = 20;
				int i_3 = 30;

				array.add(i_1);
				array.add(i_2);
				array.add(i_3);

				array.reset();
				
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_11(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.createArrayFast(10);

				int i_1 = 10;
				int i_2 = 20;
				int i_3 = 30;

				array.set(0, i_1);
				array.set(1, i_2);
				array.set(2, i_3);

				result.assertEqual("array last index should be 0", array.get(0), 10);
				result.assertEqual("array last index should be 0", array.get(1), 20);
				result.assertEqual("array last index should be 0", array.get(2), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 3);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_12(){
				TestResult<String> result;
				
				ArrayPointer<ArrayPointerExample> array;

				array.createArrayFast(10);

				array.set(0, ArrayPointerExample(10));
				array.set(1, ArrayPointerExample(20));
				array.set(2, ArrayPointerExample(30));

				result.assertEqual("array last index should be 0", array.get(0).get(), 10);
				result.assertEqual("array last index should be 0", array.get(1).get(), 20);
				result.assertEqual("array last index should be 0", array.get(2).get(), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 3);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_13(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.createArrayFast(10);

				int i_1 = 10;
				int i_2 = 20;
				int i_3 = 30;

				array.setFast(0, i_1);
				array.setFast(1, i_2);
				array.setFast(2, i_3);

				result.assertEqual("array value at index 0 should be 10", array.getFast(0), 10);
				result.assertEqual("array value at index 0 should be 20", array.getFast(1), 20);
				result.assertEqual("array value at index 0 should be 30", array.getFast(2), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_14(){
				TestResult<String> result;
				
				ArrayPointer<ArrayPointerExample> array;

				array.createArrayFast(10);

				array.setFast(0, ArrayPointerExample(10));
				array.setFast(1, ArrayPointerExample(20));
				array.setFast(2, ArrayPointerExample(30));

				result.assertEqual("array value at index 0 should be 10", array.getFast(0).get(), 10);
				result.assertEqual("array value at index 0 should be 20", array.getFast(1).get(), 20);
				result.assertEqual("array value at index 0 should be 30", array.getFast(2).get(), 30);
				result.assertEqual("array last index should be 0", array.getLastIndex(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_15(){
				TestResult<String> result;
				
				ArrayPointer<int> array;

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				array.shrink(5);
				
				result.assertEqual("array last index should be 0", array.getLastIndex(), 5);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_16(){
				TestResult<String> result;

				TemplateMemoryAllocator<int> i_allocator = true;
				
				ArrayPointer<int> array = &i_allocator;

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);
				
				result.assertEqual("array last index should be 0", array.getLastIndex(), 10);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_17(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				int num = 15;
				array.insert(5, num);
				
				result.assertEqual("array at index 4 should be 50", array.get(4), 50);
				result.assertEqual("array at index 5 should be 15", array.get(5), 15);
				result.assertEqual("array at index 6 should be 60", array.get(6), 60);
				result.assertEqual("array last index should be 11", array.length(), 11);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_18(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				array.insert(5, 15);
				
				result.assertEqual("array at index 4 should be 50", array.get(4), 50);
				result.assertEqual("array at index 5 should be 15", array.get(5), 15);
				result.assertEqual("array at index 6 should be 60", array.get(6), 60);
				result.assertEqual("array last index should be 11", array.length(), 11);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_19(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				int num = 15;
				array.insertFast(5, num);
				
				result.assertEqual("array at index 4 should be 50", array.get(4), 50);
				result.assertEqual("array at index 5 should be 15", array.get(5), 15);
				result.assertEqual("array at index 6 should be 60", array.get(6), 60);
				result.assertEqual("array last index should be 11", array.length(), 11);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_20(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				array.insertFast(5, 15);
				
				result.assertEqual("array at index 4 should be 50", array.get(4), 50);
				result.assertEqual("array at index 5 should be 15", array.get(5), 15);
				result.assertEqual("array at index 6 should be 60", array.get(6), 60);
				result.assertEqual("array last index should be 11", array.length(), 11);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_21(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);

				ArrayPointer<int> array_2 = array;
				
				result.assertEqualDebug("array_2 at index 2 should be 30", array_2.get(2), 30);
				result.assertEqualDebug("array_2 at index 3 should be 40", array_2.get(3), 40);
				result.assertEqualDebug("array_2 at index 4 should be 50", array_2.get(4), 50);
				result.assertEqualDebug("array_2 last index should be 5", array_2.length(), 5);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_22(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);

				ArrayPointer<int> array_2;
				array_2 = array;
				
				result.assertEqualDebug("array_2 at index 2 should be 30", array_2.get(2), 30);
				result.assertEqualDebug("array_2 at index 3 should be 40", array_2.get(3), 40);
				result.assertEqualDebug("array_2 at index 4 should be 50", array_2.get(4), 50);
				result.assertEqualDebug("array_2 last index should be 5", array_2.length(), 5);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_23(){
				TestResult<String> result;

				TemplateMemoryAllocator<int> i_allocator = true;
				
				ArrayPointer<int> array = &i_allocator;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);

				ArrayPointer<int> array_2;
				array_2 = array;
				
				result.assertEqualDebug("array_2 at index 2 should be 30", array_2.get(2), 30);
				result.assertEqualDebug("array_2 at index 3 should be 40", array_2.get(3), 40);
				result.assertEqualDebug("array_2 at index 4 should be 50", array_2.get(4), 50);
				result.assertEqualDebug("array_2 last index should be 5", array_2.length(), 5);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_24(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				int num = 15;
				array.insert(10, num);

				array.add(110);
				
				result.assertEqual("array at index 5 should be 15", array.get(9), 100);
				result.assertEqual("array at index 6 should be 60", array.get(10), 15);
				result.assertEqual("array at index 6 should be 60", array.get(11), 110);
				result.assertEqual("array last index should be 11", array.length(), 12);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_25(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				array.insert(10, 15);

				array.add(110);
				
				result.assertEqual("array at index 5 should be 15", array.get(9), 100);
				result.assertEqual("array at index 6 should be 60", array.get(10), 15);
				result.assertEqual("array at index 6 should be 60", array.get(11), 110);
				result.assertEqual("array last index should be 11", array.length(), 12);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_26(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				int num = 15;
				array.insertFast(10, num);

				array.add(110);
				
				result.assertEqual("array at index 5 should be 15", array.get(9), 100);
				result.assertEqual("array at index 6 should be 60", array.get(10), 15);
				result.assertEqual("array at index 6 should be 60", array.get(11), 110);
				result.assertEqual("array last index should be 11", array.length(), 12);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_27(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArray(20);

				array.add(10);
				array.add(20);
				array.add(30);
				array.add(40);
				array.add(50);
				array.add(60);
				array.add(70);
				array.add(80);
				array.add(90);
				array.add(100);

				array.insertFast(10, 15);

				array.add(110);
				
				result.assertEqual("array at index 5 should be 15", array.get(9), 100);
				result.assertEqual("array at index 6 should be 60", array.get(10), 15);
				result.assertEqual("array at index 6 should be 60", array.get(11), 110);
				result.assertEqual("array last index should be 11", array.length(), 12);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_28(){
				TestResult<String> result;

				ArrayPointer<int> array;

				array.createArrayFast(10);

				int num_1 = 15;
				int num_2 = 25;
				array.insert(3, num_1);
				array.insert(6, num_2);
				
				result.assertEqual("array at index 3 should be 15", array.getFast(3), 15);
				result.assertEqual("array at index 6 should be 25", array.getFast(6), 25);
				result.assertEqual("array last index should be 0", array.length(), 0);
				
				return result;
			}
			
			TestResult<String> TR_ArrayPointer_Testing_29(){
				TestResult<String> i_result;

				ArrayPointer<int> i_array_1;
				ArrayPointer<int> i_array_2;

				i_array_1.createArray(20);

				i_array_1.add(0);
				i_array_1.add(1);
				i_array_1.add(2);
				i_array_1.add(3);
				i_array_1.add(4);
				i_array_1.add(5);
				i_array_1.add(6);
				i_array_1.add(7);
				i_array_1.add(8);
				i_array_1.add(9);
				i_array_1.add(10);

				i_array_2.add(11);
				i_array_2.add(12);
				i_array_2.add(13);
				i_array_2.add(14);
				i_array_2.add(15);
				i_array_2.add(16);
				i_array_2.add(17);
				i_array_2.add(18);
				i_array_2.add(19);
				i_array_2.add(20);

				i_array_1.add(i_array_2);

				for(int x = 0; x < i_array_1.length(); x++){
					i_result.assertEqual(String("iteration x = ") + String(x), i_array_1.get(x), x);
				}
				
				i_result.assertEqual("array at index 5 should be 15", i_array_1.length(), 21);
				
				return i_result;
			}
			
			void TR_ArrayPointer_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("Array createArray", TR_ArrayPointer_Testing_1);
				a_test_runner.add("Array createArrayFast", TR_ArrayPointer_Testing_2);
				a_test_runner.add("Array expand", TR_ArrayPointer_Testing_3);
				a_test_runner.add("Array expand, shrink", TR_ArrayPointer_Testing_4);
				a_test_runner.add("Array expand, clear", TR_ArrayPointer_Testing_5);
				a_test_runner.add("Array add(const T&), get", TR_ArrayPointer_Testing_6);
				a_test_runner.add("Array add(T&&), get", TR_ArrayPointer_Testing_7);
				a_test_runner.add("Array createArrayFast, add(const T&), get", TR_ArrayPointer_Testing_8);
				a_test_runner.add("Array createArrayFast, add(T&&), get", TR_ArrayPointer_Testing_9);
				a_test_runner.add("Array add(const T&), reset", TR_ArrayPointer_Testing_10);
				a_test_runner.add("Array set(const T&), get", TR_ArrayPointer_Testing_11);
				a_test_runner.add("Array set(T&&), get", TR_ArrayPointer_Testing_12);
				a_test_runner.add("Array setFast(const T&), getFast", TR_ArrayPointer_Testing_13);
				a_test_runner.add("Array setFast(T&&), getFast", TR_ArrayPointer_Testing_14);
				a_test_runner.add("Array add, shrink", TR_ArrayPointer_Testing_15);
				a_test_runner.add("Array TemplateMemoryAllocator, add(T&&)", TR_ArrayPointer_Testing_16);
				a_test_runner.add("Array add(T&&), insert(const T&)", TR_ArrayPointer_Testing_17);
				a_test_runner.add("Array add(T&&), insert(T&&)", TR_ArrayPointer_Testing_18);
				a_test_runner.add("Array add(T&&), insertFast(const T&)", TR_ArrayPointer_Testing_19);
				a_test_runner.add("Array add(T&&), insertFast(T&&)", TR_ArrayPointer_Testing_20);
				a_test_runner.add("Array copyContructor", TR_ArrayPointer_Testing_21);
				a_test_runner.add("Array operator=", TR_ArrayPointer_Testing_22);
				a_test_runner.add("Array operator=, TemplateMemoryAllocator", TR_ArrayPointer_Testing_22);
				a_test_runner.add("Array insert(const T&) at the end", TR_ArrayPointer_Testing_24);
				a_test_runner.add("Array insert(T&&) at the end", TR_ArrayPointer_Testing_25);
				a_test_runner.add("Array insertFast(const T&) at the end", TR_ArrayPointer_Testing_26);
				a_test_runner.add("Array insertFast(T&&) at the end", TR_ArrayPointer_Testing_27);
				a_test_runner.add("Array insertFast(const T&) outside, getFast", TR_ArrayPointer_Testing_28);
				a_test_runner.add("Array add(const ArrayPointer<T>&)&", TR_ArrayPointer_Testing_29);
			}
		}
	}

#endif