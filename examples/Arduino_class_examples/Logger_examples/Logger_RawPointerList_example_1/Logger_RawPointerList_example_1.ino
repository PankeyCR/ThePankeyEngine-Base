
#include "MethodLogger.hpp"

#define RawPointerList_LogApp
#include "ArrayRawList.hpp"

using namespace pankey;

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
  ArrayRawList<int> array;
  array.add(5);
  array.add(6);
  array.add(7);
  for(int x : array){
    Serial.println(x);
  }
  delay(3000);
}