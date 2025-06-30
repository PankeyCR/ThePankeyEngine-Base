
#ifndef TR_TypeListManager_Testing_hpp
	#define TR_TypeListManager_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "TypeListManager.hpp"
	#include "iState.hpp"

	namespace pankey{

		namespace Base{

			class TLM_App{
				public:
			};

			class TLM_Example : public Type{
				public:
					void run(TestResult<String>& a_result){
						a_result.expecting("type running");
					}

					virtual long getType()const{
						return ClassType<TLM_Example>::getId();
					}

					virtual bool istype(long a_type)const{
						return ClassType<TLM_Example>::getId() == a_type;
					}
			};
		
			TestResult<String> TR_TypeListManager_Testing_1(){
				TestResult<String> i_result;

				TypeListManager<TLM_App> i_manager;
				iState<>& i_state = i_manager.addType<iState<>>();
				
				i_result.assertTrue("manager should contain iState<>", i_manager.containType<iState<>>());
				
				return i_result;
			}
		
			TestResult<String> TR_TypeListManager_Testing_2(){
				TestResult<String> i_result;

				TypeListManager<TLM_App> i_manager;
				iState<>& i_state = i_manager.addType<iState<>>();
				i_manager.putType<iState<>>();
				
				i_result.assertEqual("manager should contain only one iState<>", i_manager.length(), 1);
				i_result.assertTrue("manager should contain iState<>", i_manager.containType<iState<>>());
				
				return i_result;
			}
		
			TestResult<String> TR_TypeListManager_Testing_3(){
				TestResult<String> i_result;

				TypeListManager<TLM_App> i_manager;
				iState<>& i_state = i_manager.addType<iState<>>();
				
				i_result.assertTrue("manager should contain iState<>", i_manager.containIsType<iState<>>());
				
				return i_result;
			}
		
			TestResult<String> TR_TypeListManager_Testing_4(){
				TestResult<String> i_result;

				TypeListManager<TLM_App> i_manager;
				TLM_Example& i_example = i_manager.addType<TLM_Example>();

				i_manager.runTypeMethod<TLM_Example,TestResult<String>&>(&TLM_Example::run, i_result);
				
				i_result.assertTrue("manager should contain TLM_Example", i_manager.containIsType<TLM_Example>());
				i_result.assertExpectation("type running");
				
				return i_result;
			}

			void TR_TypeListManager_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("TR_TypeListManager_Testing addType, containType", TR_TypeListManager_Testing_1);
				a_test_runner.add("TR_TypeListManager_Testing addType, putType, containType", TR_TypeListManager_Testing_2);
				a_test_runner.add("TR_TypeListManager_Testing addType, containIsType", TR_TypeListManager_Testing_3);
				a_test_runner.add("TR_TypeListManager_Testing addType, runTypeMethod, containIsType", TR_TypeListManager_Testing_4);
			}		

		}		

	}

#endif
