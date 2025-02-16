
void Log(int a_status, const String& a_name, const String& a_method, const String& a_log){
  Serial.println("Log start");
  Serial.println(a_status);
  Serial.println(a_name);
  Serial.println(a_method);
  Serial.println(a_log);
  Serial.println("Log end");
}

#define pankey_Log(status,name,method,log) Log(status,name,method,log)

#define InvokeMethod_LogApp
#include "InvokeMethod.hpp"

using namespace pankey;

void Function(){
  Serial.println("Function");
}

InvokeMethod<> method;

void setup() {
  Serial.begin(9600);

  method = Function;
}

void loop() {
  invoke(method);
  delay(3000);
}