
#include "CharArray.hpp"

using namespace pankey;

void setup() {
  Serial.begin(9600);
}

void loop() {
  CharArray array = "example";

  Serial.println(array.pointer());
}