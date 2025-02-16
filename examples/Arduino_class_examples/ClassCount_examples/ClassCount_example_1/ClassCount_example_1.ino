
#include "ClassCount.hpp"

using namespace pankey;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ClassCount<int> int_count;
  ClassCount<char> char_count;
  
  Serial.println(int_count.get());
  Serial.println(char_count.get());
}
