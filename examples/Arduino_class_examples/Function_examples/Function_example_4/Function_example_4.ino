
#include "InvokeFunction.hpp"

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
  InvokeClassFunctionReturn<Example,String> method = &Example::run;
  Example example;
  String r = method(example);
  Serial.println(r);
}