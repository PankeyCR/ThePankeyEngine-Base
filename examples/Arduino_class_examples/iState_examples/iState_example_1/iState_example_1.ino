
#include "iState.hpp"

using namespace pankey::Base;

class Example : public iState<long>{
  virtual void initializeState(){
    Serial.println("initializeState");
  }
  virtual void updateState(long a_tpc){
    Serial.println("updateState");
    Serial.println(a_tpc);
  }
};

Example state;

void setup() {
  Serial.begin(9600);
  delay(3000);

  Serial.println("start");

  state.initialize();
}

void loop() {
  state.update(100l);
}