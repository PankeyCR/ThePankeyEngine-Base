
void Log(int a_status, const String& a_name, const String& a_method, const String& a_log){
  Serial.println("Log start");
  Serial.println(a_status);
  Serial.println(a_name);
  Serial.println(a_method);
  Serial.println(a_log);
  Serial.println("Log end");
}

#define pankey_Log(status,name,method,log) Log(status,name,method,log)

#define Array_LogApp
#include "Array.hpp"

using namespace pankey;

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