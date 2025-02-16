
#include "Array.hpp"

using namespace pankey;

Array<int> array;

void setup() {
  Serial.begin(9600);
  array = {0,1,2,3};
}

void loop() {
  for(int x : array){
    Serial.println(x);
  }
}
