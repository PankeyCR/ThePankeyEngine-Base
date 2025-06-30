
#ifndef TR_TypePointerList_Testing_hpp
	#define TR_TypePointerList_Testing_hpp
	
	#include "TestResult.hpp"
	#include "TestRunner.hpp"

	#include "TypePointerList.hpp"
	#include "ClassType.hpp"

	namespace pankey{

		namespace Base{

			CREATE_TYPE(TypePointer_rawtest, ClassType<TypePointer_rawtest>::getId())

			class TypePointer_test : public Type{
				public:
				void run(TestResult<String>& a_result){
					a_result.expecting("run_test");
				}
				TestResult<String> execute(bool a_bool){

				}
				TYPE_CLASS(ClassType<TypePointer_test>::getId())
			};
		
			TestResult<String> TR_TypePointerList_Testing_1(){
				TestResult<String> i_result;

				TypePointerList i_list;
			
				Type* i_type_1 = i_list.addPointer(new TypePointer_rawtest());
				Type* i_type_2 = i_list.addPointer(new TypePointer_test());

				Type* i_type_01 = getTypePointerByType(i_list, ClassType<TypePointer_rawtest>::getId());
				Type* i_type_02 = getTypePointerByType(i_list, ClassType<TypePointer_test>::getId());

				i_result.assertEqual("Type TypePointer_rawtest should be the same", i_type_1, i_type_01);
				i_result.assertEqual("Type TypePointer_test should be the same", i_type_2, i_type_02);
				
				return i_result;
			}
			
			TestResult<String> TR_TypePointerList_Testing_2(){
				TestResult<String> i_result;

				TypePointerList i_list;
			
				Type* i_type_1 = i_list.addPointer(new TypePointer_rawtest());
				Type* i_type_2 = i_list.addPointer(new TypePointer_test());

				invoke<TypePointer_test,TestResult<String>&>(i_list, &TypePointer_test::run, i_result);
				
				i_result.assertExpectation("run_test");

				return i_result;
			}

			void TR_TypePointerList_Testing(TestRunner<String>& a_test_runner){
				a_test_runner.add("TypePointerList getTypePointerByType", TR_TypePointerList_Testing_1);
				a_test_runner.add("TypePointerList addPointer", TR_TypePointerList_Testing_2);
			}		

		}		

	}

#endif
