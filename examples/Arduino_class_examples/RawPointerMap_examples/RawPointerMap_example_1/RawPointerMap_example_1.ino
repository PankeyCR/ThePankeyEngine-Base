
#include "ArrayRawPointerMap.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ArrayRawPointerMap<int,int> map;

  map.addPointers(new int(1), new int(11));
  map.addPointers(new int(2), new int(12));
  map.addPointers(new int(3), new int(13));
  map.addPointers(new int(4), new int(14));
  map.addPointers(new int(5), new int(15));

  for(int x = 0; x < map.getLastIndex(); x++){
    RawMapEntry<int,int> entry = map.getRawMapEntryByIndex(x);
    if(entry.isNull()){
      continue;
    }
    int key = *entry.getKey();
    int value = *entry.getValue();
    Serial.print("key: ");Serial.print(key);
    Serial.print("     value: ");Serial.println(value);
  }
}