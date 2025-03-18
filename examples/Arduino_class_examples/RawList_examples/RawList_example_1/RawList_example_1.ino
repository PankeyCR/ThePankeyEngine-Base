
#include "ArrayRawList.hpp"
//#include "LinkedRawList.hpp"

using namespace pankey::Base;

void setup() {
  Serial.begin(9600);
}

void loop() {
  ArrayRawList<int> list;
  //LinkedRawList<int> list;
  
  list.addPointer(new int(1));
  list.addPointer(new int(2));
  list.addPointer(new int(3));
  list.addPointer(new int(4));
  list.addPointer(new int(5));

  for(int x = 0; x < list.length(); x++){
    int* number = list.getPointerByIndex(x);
    if(number == nullptr){
      continue;
    }
    Serial.println(*number);
  }
}