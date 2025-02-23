
#include "MethodLogger.hpp"
#include "CharArray.hpp"

using namespace pankey;

void Log(int a_status, const CharArray& a_name, const CharArray& a_method, int a_log){
  Serial.println("Log start");
  Serial.println(a_status);
  Serial.println(a_name.pointer());
  Serial.println(a_method.pointer());
  Serial.println(a_log);
  Serial.println("Log end");
}

void setup() {
  Serial.begin(9600);

  Logger<int>::set(Log);
}

void loop() {
  Logging<int>(0, "free function", "loop", 15);
  delay(3000);
}