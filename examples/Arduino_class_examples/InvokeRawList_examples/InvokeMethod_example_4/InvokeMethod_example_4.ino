
#include "InvokeMethod.hpp"

using namespace pankey::Base;

class Example{
  public:
  String run() {
    return "Example";
  }
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  InvokeClassMethodReturn<Example,String> method = &Example::run;
  Example example;
  String r = invoke(example, method);
  Serial.println(r);
}