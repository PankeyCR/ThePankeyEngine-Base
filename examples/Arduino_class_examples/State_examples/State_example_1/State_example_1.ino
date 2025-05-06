
#include "State.hpp"

using namespace pankey::Base;

class Example{
  public:
  void initializeState(){
    Serial.println("initializeState");
  }
  void updateState(long a_tpc){
    Serial.println("updateState");
    Serial.println(a_tpc);
  }
};

void ExampleInit(void* a_state){
  static_cast<Example*>(a_state)->initializeState();
}

void ExampleUpdate(void* a_state, float a_tpc){
  static_cast<Example*>(a_state)->updateState(a_tpc);
}

//both Example and State needs to have the same scope for no error
Example example;
State<float> state = State<float>(&example, ExampleInit, ExampleUpdate);

void setup() {
  Serial.begin(9600);
  delay(3000);

  Serial.println("start");

  state.initialize();
}

void loop() {
  state.update(100l);
}
