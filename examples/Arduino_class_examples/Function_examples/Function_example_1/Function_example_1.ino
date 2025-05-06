
#include "InvokeFunction.hpp"

using namespace pankey::Base;

void Example() {
  Serial.println("Example");
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  InvokeFunction<> method = Example;
  method();
}