
#ifndef TestRunnerState_hpp
	#define TestRunnerState_hpp

	#include "ArrayRawMap.hpp"
	#include "InvokeMethod.hpp"
	#include "InvokeRawMap.hpp"

	#include "TestResult.hpp"
	
	#include "CharArray.hpp"

	#if defined(pankey_Log) && (defined(TestRunner_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define TestRunnerLog(status,method,mns) pankey_Log(status,"TestRunner",method,mns)
	#else
		#define TestRunnerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			class TestRunner{
				public:
					TestRunner(){
						TestRunnerLog(pankey_Log_StartMethod, "Constructor", "");
						TestRunnerLog(pankey_Log_EndMethod, "Constructor", "");
					}
					virtual ~TestRunner(){
						TestRunnerLog(pankey_Log_StartMethod, "Destructor", "");
						TestRunnerLog(pankey_Log_EndMethod, "Destructor", "");
					}
					
					virtual void runTest(){m_running = true;}

					virtual void add(CharArray a_test, InvokeMethodReturn<TestResult> a_method){
						map.add(a_test, a_method);
					}

					virtual void output(InvokeMethod<> a_start,
										InvokeMethod<> a_end,
										InvokeMethod<const CharArray&, const TestResult&> a_result,
										InvokeMethod<const CharArray&, const CharArray&> a_info,
										InvokeMethod<const CharArray&, const CharArray&> a_error,
										InvokeMethod<> a_succes){
						start = a_start;
						end = a_end;
						result = a_result;
						info = a_info;
						error = a_error;
						succes = a_succes;
					}

					virtual void output(InvokeMethod<> a_start,
										InvokeMethod<> a_end,
										InvokeMethod<const CharArray&, const CharArray&> a_info,
										InvokeMethod<const CharArray&, const CharArray&> a_error,
										InvokeMethod<> a_succes){
						start = a_start;
						end = a_end;
						info = a_info;
						error = a_error;
						succes = a_succes;
					}

					virtual void output(InvokeMethod<> a_start,
										InvokeMethod<> a_end,
										InvokeMethod<const CharArray&, const CharArray&> a_info,
										InvokeMethod<const CharArray&, const CharArray&> a_error){
						start = a_start;
						end = a_end;
						info = a_info;
						error = a_error;
					}

					virtual void omitInfo(bool a_omit){
						m_omit_info = a_omit;
					}
					
					virtual void run(){
						TestRunnerLog(pankey_Log_StartMethod, "run", "");
						if(!m_running){
							TestRunnerLog(pankey_Log_EndMethod, "run", "");
							return;
						}
						TestRunnerLog(pankey_Log_Statement, "run", "start");
						invoke(start);

						bool t_res = true;
						for(int x = 0; x < map.length(); x++){
							CharArray* f_note = map.getKeyPointerByIndex(x);
							InvokeMethodReturn<TestResult>* f_method = map.getValuePointerByIndex(x);
							if(f_note == nullptr || f_method == nullptr){
								continue;
							}
							TestResult f_result = invoke<TestResult>(*f_method);

							invoke<const CharArray&, const TestResult&>(result, *f_note, f_result);
							
							if(!m_omit_info){
								if(f_result.hasInfo()){
									invoke<const CharArray&, const CharArray&>(info, *f_note, f_result.getInfo());
								}
							}

							if(!f_result.hasError()){
								continue;
							}
							t_res = false;

							invoke<const CharArray&, const CharArray&>(error, *f_note, f_result.getCharArrayResult());
						}
						if(t_res){
							invoke(succes);
						}

						invoke(end);
						m_running = false;
						TestRunnerLog(pankey_Log_EndMethod, "run", "");
					}

				protected:
					bool m_running = false;
					bool m_omit_info = false;

					ArrayRawMap<CharArray,InvokeMethodReturn<TestResult>> map;
					
					InvokeMethod<> start;
					InvokeMethod<> end;
					InvokeMethod<const CharArray&, const TestResult&> result;
					InvokeMethod<const CharArray&, const CharArray&> info;
					InvokeMethod<const CharArray&, const CharArray&> error;
					InvokeMethod<> succes;
			};

		}

	}

#endif
