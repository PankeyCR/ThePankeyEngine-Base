
#include "InvokeMethod.hpp"

using namespace pankey::Base;

String Example() {
  return "Example";
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  InvokeMethodReturn<String> method = Example;
  String r = invoke(method);
  Serial.println(r);
}