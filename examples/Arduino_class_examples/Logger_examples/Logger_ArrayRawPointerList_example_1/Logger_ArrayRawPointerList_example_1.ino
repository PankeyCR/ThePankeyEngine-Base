
#include "MethodLogger.hpp"

#define ArrayRawPointerList_Log
//#define pankey_Global_Log
//#define pankey_Base_Log

#include "ArrayRawPointerList.hpp"

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
  ArrayRawPointerList<int> array;
  array.addPointer(new int(5));
  array.addPointer(new int(6));
  array.addPointer(new int(7));
  for(int x = 0; x < array.getLastIndex(); x++){
    Serial.println(*array.getByIndex(x));
  }
  delay(3000);
}