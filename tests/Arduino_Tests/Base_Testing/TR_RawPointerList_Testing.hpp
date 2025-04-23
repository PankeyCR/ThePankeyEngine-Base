
#ifndef TR_RawPointerList_Testing_hpp
	#define TR_RawPointerList_Testing_hpp

	#include "TestResult.hpp"
	#include "TestRunner.hpp"
	
	#include "CharArray.hpp"
	
	namespace pankey{

		namespace Base{
		
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_1(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				i_result.assertTrue(0, "list should be empty", i_list.isEmpty());

				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_2(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());

				i_result.assertEqual("list has 2 elements", i_list.length(), 2);

				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);

				i_result.assertNotNull("list int 0 not null", i_value_1);
				i_result.assertNotNull("list int 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_02, i_value_2);

				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_3(){
				TestResult<String> i_result;

				TRawPointerList list;
				TYPE* i_value_01 = list.addPointer(new TYPE());
				TYPE* i_value_02 = list.addPointer(new TYPE());
				
				list.replace(0,1);

				TYPE* i_value_1 = list.getPointerByIndex(0);
				TYPE* i_value_2 = list.getPointerByIndex(1);

				i_result.assertEqual("TYPE on position 0 should be the same as i_value_02", i_value_01, i_value_2);
				i_result.assertEqual("TYPE on position 1 should be the same as i_value_01", i_value_02, i_value_1);

				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_4(){
				TestResult<String> i_result;

				TRawPointerList i_list_1;
				TRawPointerList i_list_2;

				TYPE* i_value_01 = i_list_1.addPointer(new TYPE());
				TYPE* i_value_02 = i_list_1.addPointer(new TYPE());

				i_list_2.addMove(i_list_1);
				
				i_result.assertTrue("list_1 should be empty", i_list_1.isEmpty());
				i_result.assertEqual("list_2 has 2 elements", i_list_2.length(), 2);
				
				TYPE* i_value_1 = i_list_2.getPointerByIndex(0);
				TYPE* i_value_2 = i_list_2.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNotNull("list value 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_02, i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_5(){
				TestResult<String> i_result;

				TRawPointerList i_list_1;
				TRawPointerList i_list_2;

				i_list_2.setOwner(false);

				TYPE* i_value_01 = i_list_1.addPointer(new TYPE());
				TYPE* i_value_02 = i_list_1.addPointer(new TYPE());

				i_list_2.addDuplicate(i_list_1);
				
				i_result.assertEqual("list_1 has 2 elements", i_list_1.length(), 2);
				i_result.assertEqual("list_2 has 2 elements", i_list_2.length(), 2);
				
				TYPE* i_value_1 = i_list_2.getPointerByIndex(0);
				TYPE* i_value_2 = i_list_2.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNotNull("list value 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_02, i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_6(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_num = new TYPE();

				i_list.putPointer(i_num);
				i_list.putPointer(i_num);
				
				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);
				
				i_result.assertNotNull("list element in position 0 shouldnt be null", i_value_1);
				i_result.assertNull("list element in position 1 should be null", i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_7(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.setPointer(0, new TYPE());
				TYPE* i_value_02 = i_list.setPointer(1, new TYPE());

				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);
				
				i_result.assertNotNull("list element in position 0 shouldnt be null", i_value_1);
				i_result.assertNotNull("list element in position 1 shouldnt be null", i_value_2);

				i_result.assertEqual("should be the same", i_value_1, i_value_01);
				i_result.assertEqual("should be the same", i_value_2, i_value_02);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_8(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_03 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.insertPointer(1, new TYPE());

				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);
				TYPE* i_value_3 = i_list.getPointerByIndex(2);
				
				i_result.assertNotNull("list element in position 0 shouldnt be null", i_value_1);
				i_result.assertNotNull("list element in position 1 shouldnt be null", i_value_2);
				i_result.assertNotNull("list element in position 1 shouldnt be null", i_value_3);

				i_result.assertEqual("should be the same", i_value_1, i_value_01);
				i_result.assertEqual("should be the same", i_value_2, i_value_02);
				i_result.assertEqual("should be the same", i_value_3, i_value_03);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_9(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());

				TYPE* i_value_2 = i_list.getPointerByPointer(i_value_02);
				
				i_result.assertNotNull("list element in position 1 shouldnt be null", i_value_2);

				i_result.assertEqual("should be the same", i_value_2, i_value_02);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_10(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());
				
				i_result.assertTrue("list should contain pointer", i_list.containByPointer(i_value_02));
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_11(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());

				int i_index = i_list.getIndexByPointer(i_value_02);
				
				i_result.assertEqual("list index should be 1", i_index, 1);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_12(){
				TestResult<String> i_result;

				TRawPointerList i_list_1;
				TRawPointerList i_list_2;

				TYPE* i_value_01 = i_list_1.addPointer(new TYPE());
				TYPE* i_value_02 = i_list_1.addPointer(new TYPE());

				i_list_2.addDuplicate(i_list_1);

				i_list_1.reset();
				
				i_result.assertTrue("list_1 should be empty", i_list_1.isEmpty());
				i_result.assertEqual("list_2 has 2 elements", i_list_2.length(), 2);
				
				TYPE* i_value_1 = i_list_2.getPointerByIndex(0);
				TYPE* i_value_2 = i_list_2.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNotNull("list value 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_02, i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_13(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());

				i_list.clear();
				
				i_result.assertTrue("list should be empty", i_list.isEmpty());
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_14(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());
				TYPE* i_value_03 = i_list.addPointer(new TYPE());

				i_list.destroyByPointer(i_value_02);
				
				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNotNull("list value 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_03, i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_15(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());
				TYPE* i_value_03 = i_list.addPointer(new TYPE());

				i_list.destroyByIndex(1);
				
				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNotNull("list value 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_03, i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_16(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());
				TYPE* i_value_03 = i_list.addPointer(new TYPE());
				TYPE* i_value_04 = i_list.addPointer(new TYPE());
				TYPE* i_value_05 = i_list.addPointer(new TYPE());

				i_list.destroyFirstIndex(3);
				
				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNotNull("list value 1 not null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_04, i_value_1);
				i_result.assertEqual("TYPES on position 1 should be the same", i_value_05, i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_17(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());
				TYPE* i_value_03 = i_list.addPointer(new TYPE());
				TYPE* i_value_04 = i_list.addPointer(new TYPE());
				TYPE* i_value_05 = i_list.addPointer(new TYPE());

				i_list.destroyLastIndex(2);
				
				TYPE* i_value_1 = i_list.getPointerByIndex(3);
				TYPE* i_value_2 = i_list.getPointerByIndex(4);

				i_result.assertNull("list value 0 is null", i_value_1);
				i_result.assertNull("list value 1 is null", i_value_2);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_18(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());

				i_list.destroyFirst();
				
				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNull("list value 1 is null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_02, i_value_1);
				
				return i_result;
			}
			
			template<class TRawPointerList, class TYPE>
			TestResult<String> TR_RawPointerList_Testing_19(){
				TestResult<String> i_result;

				TRawPointerList i_list;

				TYPE* i_value_01 = i_list.addPointer(new TYPE());
				TYPE* i_value_02 = i_list.addPointer(new TYPE());

				i_list.destroyLast();
				
				TYPE* i_value_1 = i_list.getPointerByIndex(0);
				TYPE* i_value_2 = i_list.getPointerByIndex(1);

				i_result.assertNotNull("list value 0 not null", i_value_1);
				i_result.assertNull("list value 1 is null", i_value_2);

				i_result.assertEqual("TYPES on position 0 should be the same", i_value_01, i_value_1);
				
				return i_result;
			}

			template<class TRawPointerList, class TYPE>
			void TR_RawPointerList_Testing(const String& a_list_name, TestRunner<String>& a_test_runner){
				a_test_runner.add(a_list_name + " Simple Constructor", TR_RawPointerList_Testing_1<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " addPointer, getPointerByIndex", TR_RawPointerList_Testing_2<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " replace", TR_RawPointerList_Testing_3<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " addMove", TR_RawPointerList_Testing_4<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " addDuplicate", TR_RawPointerList_Testing_5<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " putPointer", TR_RawPointerList_Testing_6<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " setPointer", TR_RawPointerList_Testing_7<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " insertPointer", TR_RawPointerList_Testing_8<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " getPointerByPointer", TR_RawPointerList_Testing_9<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " containByPointer", TR_RawPointerList_Testing_10<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " getIndexByPointer", TR_RawPointerList_Testing_11<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " reset", TR_RawPointerList_Testing_12<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " clear", TR_RawPointerList_Testing_13<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " destroyByPointer", TR_RawPointerList_Testing_14<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " destroyByIndex", TR_RawPointerList_Testing_15<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " destroyFirstIndex", TR_RawPointerList_Testing_16<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " destroyLastIndex", TR_RawPointerList_Testing_17<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " destroyFirst", TR_RawPointerList_Testing_18<TRawPointerList,TYPE>);
				a_test_runner.add(a_list_name + " destroyLast", TR_RawPointerList_Testing_19<TRawPointerList,TYPE>);
			}

		}

	}

#endif
