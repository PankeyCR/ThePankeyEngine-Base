
#include "ArrayRawMap.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ArrayRawMap<int,int> map;

  map.addLValues(1, 11);
  map.addLValues(2, 12);
  map.addLValues(3, 13);
  map.addLValues(4, 14);
  map.addLValues(5, 15);

  for(auto entry :  map){
    int key = entry.getKey();
    int value = entry.getValue();
    Serial.print("key: ");Serial.print(key);
    Serial.print("     value: ");Serial.println(value);
  }
}