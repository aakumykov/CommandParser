#include "CommandParser.h"

// Как он обрабатывает 300-членную команду при максимальной длине 128?
CommandParser cParser(128, "|", "_", ':', 'Y');

void setup() {
  Serial.begin(9600);
  Serial.println(F("=CommandParser="));

// Вариант 1
//  cParser.parse("1|N:0,0_Y:0,1000_Y:1000,1000_Y:1000,0_Y:0,0;", true);
//  cParser.parse("2|N:250,250_Y:250,750_Y:750,750_Y:750,250_Y:250,250;", true);
//  cParser.parse("3|N:100,100_Y:200,200", true);

// Вариант 2
//  char s1[] = "1|N:0,0_Y:0,1000_Y:1000,1000_Y:1000,0_Y:0,0;";
//  char s2[] = "2|N:250,250_Y:250,750_Y:750,750_Y:750,250_Y:250,250;";
//  char s3[] = "3|N:100,100_Y:200,200";
//
//  cParser.parse(s1, true);
//  cParser.parse(s2, true);
//  cParser.parse(s3, true);

// Вариант 3 (проблема)
//  char s1[] = "3|N:100,100_Y:200,200";
//  cParser.parse(s1, true);
//  cParser.parse(s1, true);
//  cParser.parse(s1, true);

// Вариант 4 (проблема)
// Причина: разбор строки разрушает её саму.
    char* s1 = new char[10];
        s1[0] = '5';
        s1[1] = '|';
        s1[2] = 'Y';
        s1[3] = ':';
        s1[4] = '2';
        s1[5] = '0';
        s1[6] = ',';
        s1[7] = '3';
        s1[8] = '0';
        s1[9] = char(0);
  cParser.parse(s1, true);
  cParser.parse(s1, true);
}

void loop() {
  
}
