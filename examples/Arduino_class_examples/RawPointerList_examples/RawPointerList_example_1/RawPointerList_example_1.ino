
#include "ArrayRawPointerList.hpp"
#include "LinkedRawPointerList.hpp"

using namespace pankey;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ArrayRawPointerList<int> list;
  //LinkedRawPointerList<int> list;
  
  list.addPointer(new int(1));
  list.addPointer(new int(2));
  list.addPointer(new int(3));
  list.addPointer(new int(4));
  list.addPointer(new int(5));

  for(int x = 0; x < list.getLastIndex(); x++){
    int* number = list.getByIndex(x);
    if(number == nullptr){
      continue;
    }
    Serial.println(*number);
  }
}