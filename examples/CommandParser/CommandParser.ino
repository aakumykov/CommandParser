#include "CommandParser.h"

// Как он обрабатывает 300-членную команду при максимальной длине 128?
CommandParser p(128, "|", "_", ':', 'Y');

void setup() {
  Serial.begin(9600);
  Serial.println(F("=CommandParser="));

  Serial.print(F("free memory: ")); Serial.println(freeMemory());
  
  //p.parse("2|N:0,N:0,Y:0,Y:1000,Y:1000,Y:1000,Y:1000,Y:0,Y:0,Y:0", true);
  //p.parse("2|N:0,N:0,Y:0,Y:1000", true);
  
  // Как сделать такое?
  // 1|N:0,0_Y:0,1000_Y:1000,1000_Y:1000,0_Y:0,0;
  p.parse("1|N:0,0_Y:0,1000", true);
}

void loop() {
  
}
