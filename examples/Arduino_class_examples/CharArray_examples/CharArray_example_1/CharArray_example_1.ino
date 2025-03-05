
#include "CharArray.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  CharArray array = "example";

  Serial.println(array.pointer());
}