#include "CommandParser.h"

// Как он обрабатывает 300-членную команду при максимальной длине 128?
CommandParser p(128, "|", ",", ':', 'Y');

void setup() {
  Serial.begin(9600);
  Serial.println(F("=CommandParser="));

  Serial.print(F("free memory: ")); Serial.println(freeMemory());
  
  p.parse("2|N:0,N:0,Y:0,Y:1000,Y:1000,Y:1000,Y:1000,Y:0,Y:0,Y:0", true);
}

void loop() {
  
}
