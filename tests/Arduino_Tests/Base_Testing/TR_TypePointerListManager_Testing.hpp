
#ifndef TR_TypePointerListManager_Testing_hpp
	#define TR_TypePointerListManager_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "TypePointerListManager.hpp"

	namespace pankey{

		namespace Base{

			class TPLM_App{
				public:
			};

			CREATE_TYPE(TPLM_Example)
		
			TestResult<String> TR_TypePointerListManager_Testing_1(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				Type* i_type = i_manager.addTypePointer(new TPLM_Example());
				
				i_result.assertTrue("manager should contain TPLM_Example", i_manager.containByTypePointer(i_type));
				
				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_2(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				Type* i_type = i_manager.addTypePointer(new TPLM_Example());
				
				i_result.assertTrue("manager should contain TPLM_Example", i_manager.containByType(ClassCount<TPLM_Example>::get()));
				
				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_3(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				i_manager.addTypePointer(new TPLM_Example());
				Type* i_type = i_manager.getTypePointerByType(ClassCount<TPLM_Example>::get());
				
				i_result.assertTrue("manager should contain TPLM_Example", i_manager.containByTypePointer(i_type));
				
				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_4(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				Type* i_type = i_manager.addTypePointer(new TPLM_Example());
				Type* i_type_removed = i_manager.removeTypePointer(i_type);
				
				i_result.assertTrue("manager shouldnt contain TPLM_Example", !i_manager.containByTypePointer(i_type_removed));
				
				delete i_type_removed;

				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_5(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				i_manager.addTypePointer(new TPLM_Example());
				Type* i_type = i_manager.removeTypePointerByType(ClassCount<TPLM_Example>::get());
				
				i_result.assertTrue("manager shouldnt contain TPLM_Example", !i_manager.containByTypePointer(i_type));
				
				delete i_type;

				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_6(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				Type* i_type = i_manager.addTypePointer(new TPLM_Example());
				
				i_result.assertTrue("manager most delete TPLM_Example", i_manager.destroyByTypePointer(i_type));

				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_7(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				i_manager.addTypePointer(new TPLM_Example());
				
				i_result.assertTrue("manager most delete TPLM_Example", i_manager.destroyByType(ClassCount<TPLM_Example>::get()));

				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_8(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				i_manager.addTypePointer(new TPLM_Example());
				
				i_result.assertEqual("manager TypePointer_length should be 1", i_manager.TypePointer_length(), 1);
				i_result.assertEqual("manager length should be 1", i_manager.length(), 1);

				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_9(){
				TestResult<String> i_result;

				TypePointerListManager<TPLM_App> i_manager;
				i_manager.addTypePointer(new TPLM_Example());

				i_manager.clearTypePointer();
				
				i_result.assertEqual("manager length should be 1", i_manager.length(), 0);

				return i_result;
			}
		
			TestResult<String> TR_TypePointerListManager_Testing_10(){
				TestResult<String> i_result;

				TPLM_App i_app;

				TypePointerListManager<TPLM_App> i_manager;
				i_manager.addTypePointer(new TPLM_Example());

				i_manager.initialize(i_app);
				i_manager.update(i_app);
				
				i_result.assertEqual("manager length should be 1", i_manager.length(), 1);

				return i_result;
			}

			void TR_TypePointerListManager_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("TypePointerListManager addTypePointer, containByTypePointer", TR_TypePointerListManager_Testing_1);
				a_test_runner.add("TypePointerListManager addTypePointer, containByType", TR_TypePointerListManager_Testing_2);
				a_test_runner.add("TypePointerListManager addTypePointer, getTypePointerByType, containByTypePointer", TR_TypePointerListManager_Testing_3);
				a_test_runner.add("TypePointerListManager addTypePointer, removeTypePointer, containByTypePointer", TR_TypePointerListManager_Testing_4);
				a_test_runner.add("TypePointerListManager addTypePointer, removeTypePointerByType, containByTypePointer", TR_TypePointerListManager_Testing_5);
				a_test_runner.add("TypePointerListManager addTypePointer, destroyByTypePointer", TR_TypePointerListManager_Testing_6);
				a_test_runner.add("TypePointerListManager addTypePointer, destroyByType", TR_TypePointerListManager_Testing_7);
				a_test_runner.add("TypePointerListManager addTypePointer, TypePointer_length, length", TR_TypePointerListManager_Testing_8);
				a_test_runner.add("TypePointerListManager addTypePointer, clearTypePointer", TR_TypePointerListManager_Testing_9);
				a_test_runner.add("TypePointerListManager addTypePointer, initialize, update", TR_TypePointerListManager_Testing_10);
			}		

		}		

	}

#endif
