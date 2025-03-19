
//#include "MethodLogger.hpp"

//#define TestRunner_Log

#include "TestRunner.hpp"

#include "TR_Array_Testing.hpp"
#include "TR_CharArray_Testing.hpp"
#include "TR_InvokeMethod_Testing.hpp"
#include "TR_InvokeRawList_Testing.hpp"
#include "TR_InvokeRawMap_Testing.hpp"
#include "TR_RawPointerList_Testing.hpp"
#include "TR_GlobalEvents_Testing.hpp"
#include "TR_TPC_Testing.hpp"

using namespace pankey::Base;

void Start(){
  Serial.println("Start Test");
}

void End(){
  Serial.println("End Test");
}

void Info(const CharArray& a_test, const CharArray& a_info){
  Serial.print("Test: ");Serial.println(a_test.pointer());
  Serial.println(a_info.pointer());
}

void Error(const CharArray& a_test, const CharArray& a_error){
  Serial.print("Test: ");Serial.println(a_test.pointer());
  Serial.println(a_error.pointer());
}

void Succes(){
  Serial.println("Test Complete with no errors");
}

TestRunner tester;

void setup() {
  Serial.begin(9600);
  
//  pankey_Log_set(Log);

  TR_Array_Testing(tester);
  TR_CharArray_Testing(tester);
  TR_InvokeMethod_Testing(tester);
  TR_InvokeRawList_Testing(tester);
  TR_InvokeRawMap_Testing(tester);
//  TR_RawPointerList_Testing<LinkedRawPointerList<int>,int>("LinkedRawPointerList", tester);
  TR_RawPointerList_Testing<ArrayRawPointerList<int>,int>("ArrayRawPointerList", tester);
  TR_GlobalEvents_Testing(tester);
  TR_TPC_Testing(tester);
  
  tester.output(Start, End, Info, Error, Succes);
}

void loop() {
  tester.runTest();
  tester.run();
  delay(3000);
}