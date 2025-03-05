
#include "AppState.hpp"

using namespace pankey::Base;

class App{};

class Example : public AppState<App,long>{
  virtual void initializeState(App& a_app){
    Serial.println("initializeState");
  }
  virtual void updateState(App& a_app, long a_tpc){
    Serial.println("updateState");
    Serial.println(a_tpc);
  }
};

App app;
Example state;

void setup() {
  Serial.begin(9600);
  state.initialize(app);
}

void loop() {
  state.update(app, 100l);
}
