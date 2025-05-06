
namespace pankey{
  template<class T>
  String toString(const T& a_add){
    return String(a_add);
  }

  template<class T>
  String concat(const T& a_add){
    return String(a_add);
  }

  template<class T, class... Args>
  String concat(const T& a_string, const Args&... a_add){
    String i_string = String(a_string) + concat(a_add...);
    return i_string;
  }
}

#include "TestRunner.hpp"

#include "TR_Array_Testing.hpp"
// #include "TR_ArrayList_Testing.hpp"
#include "TR_ArrayPointer_Testing.hpp"
#include "TR_CharArray_Testing.hpp"
#include "TR_GlobalEvents_Testing.hpp"
#include "TR_InvokeMethod_Testing.hpp"
#include "TR_InvokeRawList_Testing.hpp"
#include "TR_InvokeRawMap_Testing.hpp"
#include "TR_MemoryAllocator_Testing.hpp"
#include "TR_MemorySize_Testing.hpp"
#include "TR_RawPointerList_Testing.hpp"
#include "TR_StaticAllocatorInstance_Testing.hpp"
#include "TR_TemplateMemoryAllocator_Testing.hpp"
#include "TR_TPC_Testing.hpp"
#include "TR_TypeListManager_Testing.hpp"
#include "TR_TypePointerListManager_Testing.hpp"

using namespace pankey::Base;

void Start() {
  Serial.println("Start Test");
}

void End() {
  Serial.println("End Test");
}

void Info(const String& a_test, const String& a_info) {
  Serial.print("Test: "); Serial.println(a_test);
  Serial.println(a_info);
}

void Error(const String& a_test, const String& a_error) {
  Serial.print("Test: "); Serial.println(a_test);
  Serial.println(a_error);
}

void Succes() {
  Serial.println("Test Complete with no errors");
}

TestRunner<String> tester;

void setup() {
  Serial.begin(9600);
  
  TR_Array_Testing(tester);
  // TR_ArrayList_Testing(tester);
  TR_ArrayPointer_Testing(tester);
  TR_CharArray_Testing(tester);
  TR_GlobalEvents_Testing(tester);
  TR_InvokeMethod_Testing(tester);
  TR_InvokeRawList_Testing(tester);
  TR_InvokeRawMap_Testing(tester);
  TR_MemoryAllocator_Testing(tester);
  TR_MemorySize_Testing(tester);
  // ////  TR_RawPointerList_Testing<LinkedRawPointerList<int>,int>("LinkedRawPointerList", tester);
  TR_RawPointerList_Testing<ArrayRawPointerList<int>,int>("ArrayRawPointerList", tester);
  TR_StaticAllocatorInstance_Testing(tester);
  TR_TemplateMemoryAllocator_Testing(tester);
  TR_TPC_Testing(tester);
  TR_TypeListManager_Testing(tester);
  TR_TypePointerListManager_Testing(tester);

  tester.output(Start, End, Info, Error, Succes);
}

void loop() {
  tester.runTest();
  tester.run();
  Serial.println(ESP.getFreeHeap());
  delay(3000);
}