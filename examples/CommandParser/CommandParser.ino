#include "CommandParser.h"

// Как он обрабатывает 300-членную команду при максимальной длине 128?
CommandParser p(128, "|", "_", ':', 'Y');

void setup() {
  Serial.begin(9600);
  Serial.println(F("=CommandParser="));

  Serial.print(F("free memory: ")); Serial.println(freeMemory());
  
  char input_data[] = "1|N:0,0_Y:0,1000_Y:1000,1000_Y:1000,0_Y:0,0";
  Serial.print(F("input_data: ")); Serial.println(input_data);
  p.parse(input_data, false);

  Serial.print(F("command: "));
  Serial.println(p.command());
  
  Serial.print(F("data ("));
  Serial.print(p.length());
  Serial.println(F("):"));

  unsigned short* data = p.data(false);
  for (int i=0; i<p.length(); i++) {
	  Serial.print(i);
	  Serial.print(F(": "));
	  Serial.println(data[i]);
  }
  
  Serial.print(F("free memory: ")); Serial.println(freeMemory());
}

void loop() {
  
}
