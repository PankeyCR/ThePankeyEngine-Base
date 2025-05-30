
template<class T>
void concat(String& a_string, const T& a_add){
  a_string = a_string + a_add;
}

#include "MethodLogger.hpp"

//#define TestRunner_Log
//#define pankey_Global_Log
//#define pankey_Base_Log

#include "TestRunner.hpp"

using namespace pankey::Base;

void Log(int a_status, const CharArray& a_name, const CharArray& a_method, const CharArray& a_log){
  Serial.println("Log start");
  Serial.println(a_status);
  Serial.println(a_name.pointer());
  Serial.println(a_method.pointer());
  Serial.println(a_log.pointer());
  Serial.println("Log end");
}

TestResult<String> test(){
  TestResult<String> i_result;
  i_result.addInfo("Testing", " - ", "info");
  i_result.assertTrue("assert true == false", true);
  return i_result;
}

void Start(){
  Serial.println("Start Test");
}

void End(){
  Serial.println("End Test");
}

void Info(const String& a_test, const String& a_info){
  Serial.print("Test: ");Serial.println(a_test);
  Serial.println(a_info);
}

void Error(const String& a_test, const String& a_error){
  Serial.print("Test: ");Serial.println(a_test);
  Serial.println(a_error);
}

void Succes() {
  Serial.println("Test Complete with no errors");
}

TestRunner<String> tester;

void setup() {
  Serial.begin(9600);
  
  pankey_Log_set(Log);
  
  tester.add("test", test);
  tester.output(Start, End, Info, Error, Succes);
}

void loop() {
  tester.runTest();
  tester.run();
  delay(3000);
}