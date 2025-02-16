
#include "InvokeMethod.hpp"

using namespace pankey;

void Example() {
  Serial.println("Example");
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  InvokeMethod<> method = Example;
  invoke(method);
}