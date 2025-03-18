
#ifndef TestResult_hpp
	#define TestResult_hpp

	#include "ArrayRawList.hpp"
	#include "CharArray.hpp"

	#if defined(pankey_Log) && (defined(TestResult_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define TestResultLog(status,method,mns) pankey_Log(status,"TestResult",method,mns)
	#else
		#define TestResultLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{
		
			class TestResult{
				public:
					TestResult(){
						TestResultLog(pankey_Log_StartMethod, "Constructor", "");
						TestResultLog(pankey_Log_Statement, "Constructor", "Default Constructor");
						TestResultLog(pankey_Log_EndMethod, "Constructor", "");
					}
					TestResult(const TestResult& c_result){
						TestResultLog(pankey_Log_StartMethod, "Constructor", "");
						TestResultLog(pankey_Log_Statement, "Constructor", "const TestResult&");
						m_test_Error = c_result.m_test_Error;
						m_info = c_result.m_info;
						m_errors = c_result.m_errors;
						m_indexs = c_result.m_indexs;
						m_index  = c_result.m_index;
						m_expected_errors  = c_result.m_expected_errors;
						m_expected_indexs  = c_result.m_expected_indexs;
						m_expected_results  = c_result.m_expected_results;
						TestResultLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~TestResult(){
						TestResultLog(pankey_Log_StartMethod, "Destructor", "");
						TestResultLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					template<class... Args>
					void addInfo(Args... a_error){
						TestResultLog(pankey_Log_StartMethod, "addInfo", "");
						CharArray array[] = {CharArray(a_error)...};
						CharArray total;
						for(const CharArray& a : array){
							total.addLocalArray(a);
						}
						m_info.add(total);
						TestResultLog(pankey_Log_EndMethod, "addInfo", "");
					}
					
					virtual void catchError(int a_index, CharArray a_error){
						TestResultLog(pankey_Log_StartMethod, "catchError", "");
						m_test_Error = true;
						m_errors.add(a_error);
						m_indexs.add(a_index);
						TestResultLog(pankey_Log_EndMethod, "catchError", "");
					}
					
					virtual void catchError(CharArray a_error){
						TestResultLog(pankey_Log_StartMethod, "catchError", "");
						m_test_Error = true;
						m_errors.add(a_error);
						m_indexs.add(m_index);
						TestResultLog(pankey_Log_EndMethod, "catchError", "");
					}

					virtual void expecting(int a_index, CharArray a_error, bool a_result){
						TestResultLog(pankey_Log_StartMethod, "expecting", "");
						m_expected_indexs.add(a_index);
						m_expected_errors.add(a_error);
						m_expected_results.add(a_result);
						TestResultLog(pankey_Log_EndMethod, "expecting", "");
					}

					virtual void expecting(int a_index, CharArray a_error){
						TestResultLog(pankey_Log_StartMethod, "expecting", "");
						m_expected_indexs.add(a_index);
						m_expected_errors.add(a_error);
						m_expected_results.add(true);
						TestResultLog(pankey_Log_EndMethod, "expecting", "");
					}

					virtual void expecting(CharArray a_error){
						TestResultLog(pankey_Log_StartMethod, "expecting", "");
						m_expected_indexs.add(-1);
						m_expected_errors.add(a_error);
						m_expected_results.add(true);
						TestResultLog(pankey_Log_EndMethod, "expecting", "");
					}

					virtual void expecting(CharArray a_error, bool a_result){
						TestResultLog(pankey_Log_StartMethod, "expecting", "");
						m_expected_indexs.add(-1);
						m_expected_errors.add(a_error);
						m_expected_results.add(a_result);
						TestResultLog(pankey_Log_EndMethod, "expecting", "");
					}

					virtual void expectingTrue(int a_index, CharArray a_error, bool a_assert){
						TestResultLog(pankey_Log_StartMethod, "expectingTrue", "");
						this->expecting(a_index, a_error, a_assert);
						TestResultLog(pankey_Log_EndMethod, "expectingTrue", "");
					}

					virtual void expectingTrue(CharArray a_error, bool a_assert){
						TestResultLog(pankey_Log_StartMethod, "expectingTrue", "");
						this->expecting(a_error, a_assert);
						TestResultLog(pankey_Log_EndMethod, "expectingTrue", "");
					}

					virtual void assertExpectation(CharArray a_error){
						TestResultLog(pankey_Log_StartMethod, "assertExpectation", "");
						int i_list_index = m_expected_errors.getIndex(a_error);
						if(i_list_index == -1){
							this->catchError(CharArray("Error, no test registered: ") + a_error);
							return;
						}
						int i_index = m_expected_indexs.getByIndex(i_list_index);
						int i_assert = m_expected_results.getByIndex(i_list_index);
						if(!i_assert){
							if(i_index == -1){
								this->catchError(a_error);
							}else{
								this->catchError(i_index, a_error);
							}
						}
						TestResultLog(pankey_Log_EndMethod, "assertExpectation", "");
					}

					virtual void assertUnexpectation(CharArray a_error){
						TestResultLog(pankey_Log_StartMethod, "assertUnexpectation", "");
						int i_list_index = m_expected_errors.getIndex(a_error);
						if(i_list_index == -1){
							return;
						}
						int i_index = m_expected_indexs.getByIndex(i_list_index);
						int i_assert = m_expected_results.getByIndex(i_list_index);
						if(!i_assert){
							if(i_index == -1){
								this->catchError(CharArray("Error, test has been registered and it shouldnt: ") + a_error);
							}else{
								this->catchError(i_index, CharArray("Error, test has been registered and it shouldnt: ") + a_error);
							}
						}
						TestResultLog(pankey_Log_EndMethod, "assertUnexpectation", "");
					}

					template<class... Args>
					void assertExpectedSequence(Args... a_errors){
						TestResultLog(pankey_Log_StartMethod, "assertExpectedSequence", "");
						ArrayRawList<CharArray> i_sequence;
						i_sequence.addPack(a_errors...);
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", "i_sequence.length: ");
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", i_sequence.length());

						if(i_sequence.isEmpty()){
							this->catchError("Error, no sequence of test registered: ");
							TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
							return;
						}
						if(i_sequence.length() == 1){
							this->assertExpectation(i_sequence.getByIndex(0));
							TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
							return;
						}

						CharArray i_firts_error = i_sequence.getByIndex(0);
						int i_list_index = m_expected_errors.getIndex(i_firts_error);
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", "i_firts_error: ");
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", i_firts_error.pointer());
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", "i_list_index: ");
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", i_list_index);
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", "i_list_index + i_sequence.length(): ");
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", i_list_index + i_sequence.length());
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", "m_expected_errors.length(): ");
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", m_expected_errors.length());
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", "m_expected_errors.length() - i_list_index: ");
						TestResultLog(pankey_Log_Statement, "assertExpectedSequence", m_expected_errors.length() - i_list_index);

						if(i_list_index + i_sequence.length() <= m_expected_errors.length()){
							this->assertCharArrayEqual("Error, not enough test to check: sequence - errors found: ", i_sequence.length(), m_expected_errors.length() - i_list_index);
							TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
							return;
						}
						
						int s = 0;
						for(int x = i_list_index; x < i_sequence.length(); x++){
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
						TestResultLog(pankey_Log_EndMethod, "assertExpectedSequence", "");
					}

					virtual void assertTrue(int a_index, CharArray a_error, bool a_assert){
						TestResultLog(pankey_Log_StartMethod, "assertTrue", "");
						if(!a_assert){
							this->catchError(a_index, a_error);
						}
						TestResultLog(pankey_Log_EndMethod, "assertTrue", "");
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
						for(int x = 0; x < m_info.length(); x++){
							CharArray* f_info = m_info.getPointerByIndex(x);
							if(f_info == nullptr){
								continue;
							}
							i_info.addLocalArrayPointer("Info: ");
							i_info.addLocalCharArray(*f_info);
							if(x == m_info.length() - 1){
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
						for(int x = 0; x < m_errors.length(); x++){
							int* f_index = m_indexs.getPointerByIndex(x);
							CharArray* f_error = m_errors.getPointerByIndex(x);
							if(f_index == nullptr || f_error == nullptr){
								continue;
							}
							i_errors.addLocalArrayPointer("Index: ");
							i_errors.addLocalInt(*f_index);
							i_errors.addLocalValue('\n');
							i_errors.addLocalCharArray(*f_error);
							if(x != m_errors.length() - 1){
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

	}

#endif
