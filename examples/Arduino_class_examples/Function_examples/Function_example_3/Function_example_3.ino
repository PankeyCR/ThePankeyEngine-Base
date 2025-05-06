
#include "InvokeFunction.hpp"

using namespace pankey::Base;

class Example{
  public:
  void run() {
    Serial.println("Example");
  }
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  InvokeClassFunction<Example> method = &Example::run;
  Example example;
  method(example);
}