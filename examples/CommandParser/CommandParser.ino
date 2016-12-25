#include "CommandParser.h"

// Как он обрабатывает 300-членную команду при максимальной длине 128?
CommandParser p(128, "|", "_", ":");

void setup() {
  Serial.begin(9600);
  Serial.println(F("=CommandParser="));

  Serial.print(F("free memory: ")); Serial.println(freeMemory());

  p.parse("1|0_0_0_1000_1000_1000_1000_0_0_0", true);
  
  //p.parse("2|0:0,0_1:0,1000_1:1000,1000_1:1000,0_1:0,0", true);
}

void loop() {
  
}
