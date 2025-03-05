
#include "Command.hpp"

using namespace pankey::Base;

class Example : public Command<int>{
  public:
    virtual void execute(int args){
      Serial.println("execute Example");
      Serial.println(args);
    }
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  Example example;
  example.execute(15);
}
