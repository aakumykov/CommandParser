#include "CommandParser.h"

// Как он обрабатывает 300-членную команду при максимальной длине 128?
CommandParser p(128, "|", "_", ':', 'Y');

void setup() {
  Serial.begin(9600);
  Serial.println(F("=CommandParser="));

  for (int k=0; k<3; k++) {

  Serial.print(F("free memory: ")); Serial.println(freeMemory());
  
  //char input_data[] = "1|N:0,0_Y:0,1000_Y:1000,1000_Y:1000,0_Y:0,0";
  
  //~ char input_data[] = "1|N:0,0_Y:0,1000";
  
  //~ char* input_data = new char[17];
  char* input_data = new char[16];
        input_data[0] = '1';
        input_data[1] = '|';
        input_data[2] = 'N';
        input_data[3] = ':';
        input_data[4] = '0';
        input_data[5] = ',';
        input_data[6] = '0';
        input_data[7] = '_';
        input_data[8] = 'Y';
        input_data[9] = ':';
        input_data[10] = '0';
        input_data[11] = ',';
        input_data[12] = '1';
        input_data[13] = '0';
        input_data[14] = '0';
        input_data[15] = '0';
        //input_data[16] = char(0);
  
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
  Serial.print(F(""));
  
  }
}

void loop() {
  
}
