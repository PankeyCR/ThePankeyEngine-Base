
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

#define ArrayPointer_Log
//#define pankey_Global_Log
//#define pankey_Base_Log

#include "ArrayPointer.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ArrayPointer<int> array;
  array.add(5);
  array.add(6);
  array.add(7);
  for(int x = 0; x < array.length(); x++){
    Serial.println(x);
  }
  delay(3000);
}