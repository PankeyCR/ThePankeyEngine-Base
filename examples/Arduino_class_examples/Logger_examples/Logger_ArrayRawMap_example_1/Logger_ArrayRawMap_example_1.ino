
#include "MethodLogger.hpp"

#define ArrayRawMap_Log
//#define pankey_Global_Log
//#define pankey_Base_Log

#include "ArrayRawMap.hpp"

using namespace pankey::Base;

void Log(int a_status, const CharArray& a_name, const CharArray& a_method, const CharArray& a_log){
  Serial.println("Log start");
  Serial.println(a_status);
  Serial.println(a_name.pointer());
  Serial.println(a_method.pointer());
  Serial.println(a_log.pointer());
  Serial.println("Log end");
}

void setup() {
  Serial.begin(9600);

  pankey_Log_set(Log);
}

void loop() {
  ArrayRawMap<int,int> array;
  array.add(1,5);
  array.add(2,6);
  array.add(3,7);
  Serial.println(array.get(1));
  delay(3000);
}