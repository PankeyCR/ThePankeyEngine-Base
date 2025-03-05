
template<class T>
void Log(int a_status, const String& a_name, const String& a_method, T a_log){
  Serial.println("Log start");
  Serial.println(a_status);
  Serial.println(a_name);
  Serial.println(a_method);
  Serial.println(a_log);
  Serial.println("Log end");
}

#define pankey_Log(status,name,method,log) Log(status,name,method,log)

#define InvokeRawMap_Log
//#define pankey_Global_Log
//#define pankey_Base_Log

#include "InvokeRawMap.hpp"

using namespace pankey::Base;

void Function(){
  Serial.println("Function");
}

MethodMap<int> methods;

void setup() {
  Serial.begin(9600);

  methods.add(7, Function);
}

void loop() {
  invokeAll(methods);
  delay(3000);
}