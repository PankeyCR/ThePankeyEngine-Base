
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

#define CharArray_LogApp
#include "CharArray.hpp"

using namespace pankey;

void setup() {
  Serial.begin(9600);
}

void loop() {
  CharArray array = "hellow log";
  Serial.println(array.pointer());
  delay(3000);
}