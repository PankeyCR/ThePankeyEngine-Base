
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

#define ArrayIterator_Log
//#define pankey_Global_Log
//#define pankey_Base_Log

#include "Array.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Array<int> array;
  array.addLocalValue(5);
  array.addLocalValue(6);
  array.addLocalValue(7);
  for(int x : array){
    Serial.println(x);
  }
  delay(3000);
}