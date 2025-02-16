
#include "Logger.hpp"

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
  pankey_Log(0, "free function", "loop", "executing loop");
  delay(3000);
}