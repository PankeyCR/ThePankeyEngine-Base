
#ifndef TestResult_hpp
#define TestResult_hpp

#include "ArrayRawList.hpp"
#include "CharArray.hpp"

namespace pankey{
	
class TestResult{
	public:
		TestResult(){}
		TestResult(const TestResult& c_result){
			m_test_Error = c_result.m_test_Error;
			m_info = c_result.m_info;
			m_errors = c_result.m_errors;
			m_indexs = c_result.m_indexs;
			m_index  = c_result.m_index;
			m_expected_errors  = c_result.m_expected_errors;
			m_expected_indexs  = c_result.m_expected_indexs;
			m_expected_results  = c_result.m_expected_results;
		}
		
		TestResult(TestResult&& c_result){
			//m_test_Error = c_result.m_test_Error;
		}
		virtual ~TestResult(){}
		
		template<class... Args>
		void addInfo(Args... a_error){
			CharArray array[] = {CharArray(a_error)...};
			CharArray total;
			for(const CharArray& a : array){
				total.addLocalArray(a);
			}
			m_info.add(total);
		}
		
		virtual void catchError(int a_index, CharArray a_error){
			m_test_Error = true;
			m_errors.add(a_error);
			m_indexs.add(a_index);
		}
		
		virtual void catchError(CharArray a_error){
			m_test_Error = true;
			m_errors.add(a_error);
			m_indexs.add(m_index);
		}

		virtual void expecting(int a_index, CharArray a_error, bool a_result){
			m_expected_indexs.add(a_index);
			m_expected_errors.add(a_error);
			m_expected_results.add(a_result);
		}

		virtual void expecting(int a_index, CharArray a_error){
			m_expected_indexs.add(a_index);
			m_expected_errors.add(a_error);
			m_expected_results.add(true);
		}

		virtual void expecting(CharArray a_error){
			m_expected_indexs.add(-1);
			m_expected_errors.add(a_error);
			m_expected_results.add(true);
		}

		virtual void expecting(CharArray a_error, bool a_result){
			m_expected_indexs.add(-1);
			m_expected_errors.add(a_error);
			m_expected_results.add(a_result);
		}

		virtual void expectingTrue(int a_index, CharArray a_error, bool a_assert){
			this->expecting(a_index, a_error, a_assert);
		}

		virtual void expectingTrue(CharArray a_error, bool a_assert){
			this->expecting(a_error, a_assert);
		}

		virtual void assertExpectation(CharArray a_error){
			int i_list_index = m_expected_errors.getIndex(a_error);
			if(i_list_index == -1){
				this->catchError(CharArray("Error, no test registered: ") + a_error);
				return;
			}
			int i_index = m_expected_indexs.getValueByIndex(i_list_index);
			int i_assert = m_expected_results.getValueByIndex(i_list_index);
			if(!i_assert){
				if(i_index == -1){
					this->catchError(a_error);
				}else{
					this->catchError(i_index, a_error);
				}
			}
		}

		virtual void assertUnexpectation(CharArray a_error){
			int i_list_index = m_expected_errors.getIndex(a_error);
			if(i_list_index == -1){
				return;
			}
			int i_index = m_expected_indexs.getValueByIndex(i_list_index);
			int i_assert = m_expected_results.getValueByIndex(i_list_index);
			if(!i_assert){
				if(i_index == -1){
					this->catchError(CharArray("Error, test has been registered and it shouldnt: ") + a_error);
				}else{
					this->catchError(i_index, CharArray("Error, test has been registered and it shouldnt: ") + a_error);
				}
			}
		}

		template<class... Args>
		void assertExpectedSequence(Args... a_errors){
			ArrayRawList<CharArray> i_sequence;
			i_sequence.addPack(a_errors...);

			if(i_sequence.isEmpty()){
				this->catchError("Error, no sequence of test registered: ");
				return;
			}
			if(i_sequence.getLastIndex() == 1){
				this->assertExpectation(i_sequence.getByIndex(0));
				return;
			}

			CharArray i_firts_error = i_sequence.getByIndex(0);
			int i_list_index = m_expected_errors.getIndex(i_firts_error);

			if(i_list_index + i_sequence.getLastIndex() <= m_expected_errors.getLastIndex()){
				this->assertCharArrayEqual("Error, not enough test to check: sequence - errors found: ", i_sequence.getLastIndex(), m_expected_errors.getLastIndex() - i_list_index);
				return;
			}
			
			int s = 0;
			for(int x = i_list_index; x < i_sequence.getLastIndex(); x++){
				CharArray f_error = m_expected_errors.getByIndex(x);
				CharArray f_sequence_error = i_sequence.getByIndex(s);
				if(f_sequence_error != f_error){
					this->catchError(CharArray("Error, no test registered: ") + f_error);
					continue;
				}
				int i_index = m_expected_indexs.getByIndex(x);
				int i_assert = m_expected_results.getByIndex(x);
				if(!i_assert){
					if(i_index == -1){
						this->catchError(f_error);
					}else{
						this->catchError(i_index, f_error);
					}
				}
				s++;
			}
		}

		virtual void assertTrue(int a_index, CharArray a_error, bool a_assert){
			if(!a_assert){
				this->catchError(a_index, a_error);
			}
		}

		virtual void assertTrue(CharArray a_error, bool a_assert){
			if(!a_assert){
				this->catchError(a_error);
			}
			m_index++;
		}

		virtual void assertNull(CharArray a_error, void* a_assert){
			if(a_assert != nullptr){
				this->catchError(a_error);
			}
			m_index++;
		}

		virtual void assertNotNull(CharArray a_error, void* a_assert){
			if(a_assert == nullptr){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertLessThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 >= a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertLessThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 >= a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayLessThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 >= a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayLessThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 >= a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		template<class T>
		void assertGreaterThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 <= a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertGreaterThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 <= a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayGreaterThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 <= a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayGreaterThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 <= a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		template<class T>
		void assertLessEqualThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 > a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertLessEqualThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 > a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayLessEqualThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 > a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayLessEqualThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 > a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		template<class T>
		void assertGreaterEqualThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 < a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertGreaterEqualThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 < a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayGreaterEqualThen(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 < a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayGreaterEqualThen(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 < a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		template<class T>
		void assertInBetween(int a_index, CharArray a_error, T a_assert_1, T a_assert_inbetween_1, T a_assert_inbetween_2){
			if(a_assert_inbetween_1 > a_assert_1 || a_assert_inbetween_2 < a_assert_1){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertInBetween(CharArray a_error, T a_assert_1, T a_assert_inbetween_1, T a_assert_inbetween_2){
			if(a_assert_inbetween_1 > a_assert_1 || a_assert_inbetween_2 < a_assert_1){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayInBetween(int a_index, CharArray a_error, T a_assert_1, T a_assert_inbetween_1, T a_assert_inbetween_2){
			if(a_assert_inbetween_1 > a_assert_1 || a_assert_inbetween_2 < a_assert_1){
				CharArray i_CharArray = CharArray(" Min Value 1: ") + CharArray(a_assert_inbetween_1) + CharArray(" <-> Test Value: ") + CharArray(a_assert_1) + CharArray(" <-> Max Value 2: ") + CharArray(a_assert_inbetween_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayInBetween(CharArray a_error, T a_assert_1, T a_assert_inbetween_1, T a_assert_inbetween_2){
			if(a_assert_inbetween_1 > a_assert_1 || a_assert_inbetween_2 < a_assert_1){
				CharArray i_CharArray = CharArray(" Min Value 1: ") + CharArray(a_assert_inbetween_1) + CharArray(" <-> Test Value: ") + CharArray(a_assert_1) + CharArray(" <-> Max Value 2: ") + CharArray(a_assert_inbetween_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		template<class T>
		void assertEqual(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 != a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertEqual(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 != a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertNotEqual(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 == a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertNotEqual(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 == a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayqual(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 == a_assert_2){
				this->catchError(a_index, a_error);
			}
		}

		template<class T>
		void assertCharArrayqual(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 == a_assert_2){
				this->catchError(a_error);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayEqual(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 != a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayEqual(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 != a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		template<class T>
		void assertCharArrayCharArrayqual(int a_index, CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 == a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_index, a_error + i_CharArray);
			}
		}

		template<class T>
		void assertCharArrayCharArrayqual(CharArray a_error, T a_assert_1, T a_assert_2){
			if(a_assert_1 == a_assert_2){
				CharArray i_CharArray = CharArray(" Value 1: ") + CharArray(a_assert_1) + CharArray(" <-> Value 2: ") + CharArray(a_assert_2);
				this->catchError(a_error + i_CharArray);
			}
			m_index++;
		}

		virtual bool hasError(){return m_test_Error;}

		virtual bool hasInfo(){return !this->m_info.isEmpty();}
		
		virtual CharArray getInfo(){
			CharArray i_info;
			for(int x = 0; x < m_info.getLastIndex(); x++){
				CharArray* f_info = m_info.getByIndex(x);
				if(f_info == nullptr){
					continue;
				}
				i_info.addLocalArrayPointer("Info: ");
				i_info.addLocalCharArray(*f_info);
				if(x == m_info.getLastIndex() - 1){
					continue;
				}
				i_info.addLocalValue('\n');
			}
			return i_info;
		}
		
		virtual CharArray getCharArrayResult(){
			if(!m_test_Error){
				return CharArray("No Error Found");
			}
			CharArray i_errors = "Test Failed at:\n";
			for(int x = 0; x < m_errors.getLastIndex(); x++){
				int* f_index = m_indexs.getByIndex(x);
				CharArray* f_error = m_errors.getByIndex(x);
				if(f_index == nullptr || f_error == nullptr){
					continue;
				}
				i_errors.addLocalArrayPointer("Index: ");
				i_errors.addLocalInt(*f_index);
				i_errors.addLocalValue('\n');
				i_errors.addLocalCharArray(*f_error);
				if(x != m_errors.getLastIndex() - 1){
					i_errors.addLocalValue('\n');
				}
			}
			return i_errors;
		}
		
		virtual void operator=(const TestResult& c_result){
			m_test_Error = c_result.m_test_Error;
			m_info = c_result.m_info;
			m_errors = c_result.m_errors;
			m_indexs = c_result.m_indexs;
			m_index  = c_result.m_index;
			m_expected_errors  = c_result.m_expected_errors;
			m_expected_indexs  = c_result.m_expected_indexs;
			m_expected_results  = c_result.m_expected_results;
		}
		
		virtual void operator=(TestResult&& c_result){
			m_test_Error = c_result.m_test_Error;
		}
		
		virtual void clear(){
			m_test_Error = false;
			m_info.clear();
			m_errors.clear();
			m_indexs.clear();
			m_index = 0;
			
			m_expected_errors.clear();
			m_expected_indexs.clear();
			m_expected_results.clear();
		}
		
	protected:
		bool m_test_Error = false;
		ArrayRawList<CharArray> m_info;

		ArrayRawList<CharArray> m_errors;
		ArrayRawList<int> m_indexs;
		int m_index = 0;


		ArrayRawList<CharArray> m_expected_errors;
		ArrayRawList<int> m_expected_indexs;
		ArrayRawList<int> m_expected_results;
};

}

#endif
