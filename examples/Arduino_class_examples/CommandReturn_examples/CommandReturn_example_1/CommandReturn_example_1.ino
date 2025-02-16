
#include "CommandReturn.hpp"

using namespace pankey;

class Example : public CommandReturn<float,int>{
  public:
    virtual float execute(int args){
      Serial.println("execute Example");
      Serial.println(args);
      return 9.6f;
    }
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  Example example;
  float value = example.execute(15);
  Serial.println(value);
}