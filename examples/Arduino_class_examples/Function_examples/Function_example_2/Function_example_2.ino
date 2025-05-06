
#include "InvokeFunction.hpp"

using namespace pankey::Base;

String Example() {
  return "Example";
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  InvokeFunctionReturn<String> method = Example;
  String r = method();
  Serial.println(r);
}