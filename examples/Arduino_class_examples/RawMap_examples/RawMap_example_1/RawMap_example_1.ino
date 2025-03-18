
#include "ArrayRawMap.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ArrayRawMap<int,int> map;

  map.add(1, 11);
  map.add(2, 12);
  map.add(3, 13);
  map.add(4, 14);
  map.add(5, 15);

  for(auto entry :  map){
    int key = entry.getKey();
    int value = entry.getValue();
    Serial.print("key: ");Serial.print(key);
    Serial.print("     value: ");Serial.println(value);
  }
}