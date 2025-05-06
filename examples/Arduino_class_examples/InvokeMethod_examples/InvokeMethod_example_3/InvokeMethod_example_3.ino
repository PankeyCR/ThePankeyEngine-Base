
#include "InvokeMethod.hpp"

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
  InvokeClassMethod<Example> method = &Example::run;
  Example example;
  invoke(example, method);
}