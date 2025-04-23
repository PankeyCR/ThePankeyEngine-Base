
#ifndef TestRunnerState_hpp
	#define TestRunnerState_hpp

	#include "ArrayRawMap.hpp"
	#include "InvokeMethod.hpp"
	#include "InvokeRawMap.hpp"

	#include "TestResult.hpp"

	#if defined(pankey_Log) && (defined(TestRunner_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define TestRunnerLog(status,method,mns) pankey_Log(status,"TestRunner",method,mns)
	#else
		#define TestRunnerLog(status,method,mns)
	#endif

	namespace pankey{

		namespace Base{

			template<class S>
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

					virtual void add(S a_test, InvokeMethodReturn<TestResult<S>> a_method){
						map.add(a_test, a_method);
					}

					virtual void output(InvokeMethod<> a_start,
										InvokeMethod<> a_end,
										InvokeMethod<const S&, const TestResult<S>&> a_result,
										InvokeMethod<const S&, const S&> a_info,
										InvokeMethod<const S&, const S&> a_error,
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
										InvokeMethod<const S&, const S&> a_info,
										InvokeMethod<const S&, const S&> a_error,
										InvokeMethod<> a_succes){
						start = a_start;
						end = a_end;
						info = a_info;
						error = a_error;
						succes = a_succes;
					}

					virtual void output(InvokeMethod<> a_start,
										InvokeMethod<> a_end,
										InvokeMethod<const S&, const S&> a_info,
										InvokeMethod<const S&, const S&> a_error){
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
							S* f_note = map.getKeyPointerByIndex(x);
							InvokeMethodReturn<TestResult<S>>* f_method = map.getValuePointerByIndex(x);
							if(f_note == nullptr || f_method == nullptr){
								continue;
							}
							TestResult<S> f_result = invoke<TestResult<S>>(*f_method);

							invoke<const S&, const TestResult<S>&>(result, *f_note, f_result);
							
							if(!m_omit_info){
								if(f_result.hasInfo()){
									invoke<const S&, const S&>(info, *f_note, f_result.getInfo());
								}
							}

							if(!f_result.hasError()){
								continue;
							}
							t_res = false;

							invoke<const S&, const S&>(error, *f_note, f_result.getSResult());
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

					ArrayRawMap<S,InvokeMethodReturn<TestResult<S>>> map;
					
					InvokeMethod<> start;
					InvokeMethod<> end;
					InvokeMethod<const S&, const TestResult<S>&> result;
					InvokeMethod<const S&, const S&> info;
					InvokeMethod<const S&, const S&> error;
					InvokeMethod<> succes;
			};

		}

	}

#endif
