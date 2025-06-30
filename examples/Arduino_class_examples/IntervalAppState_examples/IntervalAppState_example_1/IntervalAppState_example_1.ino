
#include "IntervalAppState.hpp"
#include "TPC.hpp"

using namespace pankey::Base;

int app = 15;
IntervalAppState<int> intervals = 1000;
TPC tpc;

void setup() {
  Serial.begin(9600);
  delay(3000);

  Serial.println("start");

  intervals.add(run);

  intervals.initialize(app);
  intervals.onEnable();
  tpc.initialize(millis());
}

void loop() {
  long i_tpc = tpc.generateTpc(millis());
  intervals.update(app, i_tpc);
}

void run(){
  Serial.println("running");
}

