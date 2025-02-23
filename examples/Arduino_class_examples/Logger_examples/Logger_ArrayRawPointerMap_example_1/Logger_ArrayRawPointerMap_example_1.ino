
#include "MethodLogger.hpp"

#define ArrayRawPointerMap_LogApp
#include "ArrayRawPointerMap.hpp"

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
  ArrayRawPointerMap<int,int> array;
  array.addPointers(new int(1),new int(5));
  array.addPointers(new int(2),new int(6));
  array.addPointers(new int(3),new int(7));
  delay(3000);
}