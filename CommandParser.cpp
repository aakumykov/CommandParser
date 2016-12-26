#include "CommandParser.h"

CommandParser::CommandParser(int max_input_len, char* command_delimiter, char* data_delimiter, char mode_delimiter, char mode_sign) {
	this->_data = new int[max_input_len];
	this->_command_delimiter = command_delimiter;
	this->_data_delimiter = data_delimiter;
	this->_mode_delimiter = mode_delimiter;
	this->_mode_sign = mode_sign;
}


void CommandParser::parse(char* str, bool debug=false) {
	this->debug = debug;
		
	if (this->debug) {
		  //~ Serial.println(F("CommandParser.parse()"));
		  Serial.println(F(""));
		  Serial.print(F("CommandParser.parse("));
		  Serial.print(str);
		  Serial.println(F(")"));
	}

	this->clear();

	char* raw_command = strtok(str, this->_command_delimiter);

		Serial.print(F("raw_command: ")); Serial.println(raw_command);
	
	this->_command = atoi(raw_command);
	  
	char* raw_data_piece = strtok(NULL, this->_data_delimiter);

	unsigned int data_piece = this->convertCoord(raw_data_piece);
		
	while (NULL != raw_data_piece) {
		if (debug) {
			Serial.println(F(""));
			Serial.print(F("raw_data_piece: ")); Serial.println(raw_data_piece);
			Serial.print(F("data_piece: ")); Serial.println(data_piece);
		}
		
		this->_data[this->_counter++] = data_piece;
		
		raw_data_piece = strtok(NULL, this->_data_delimiter);
		
		data_piece = this->convertCoord(raw_data_piece);
	}

	if (debug) {
		Serial.println(F(""));
		this->command();
		this->data();
		this->length();
	}
}


unsigned short* CommandParser::data() {
//      Serial.println(F("CommandParser.getData()"));

//      int* d = new int[this->_counter];
//      for (int i=0; i < this->_counter; i++) {
//        d[i] = this->_data[i];
//      }
//      return d;

	if (this->debug) {
		  Serial.print(F("data: "));
		  for (int i=0; i < this->_counter; i++)
		  {
		//Serial.print(i); Serial.print(F(":"));
		Serial.print(this->_data[i]);
		Serial.print(F("-"));
		  }
		  Serial.println(F(""));
	}

	return this->_data;
}

unsigned int CommandParser::command(){
	//Serial.println(F("CommandParser.getCommand()"));
	if (debug) {
		Serial.print(F("command: "));
		Serial.println(this->_command);
	}
	return this->_command;
}

int CommandParser::length() {
  //Serial.println(F("CommandParser.getDataCount()"));
	if (this->debug) {
		Serial.print(F("data count: "));
		Serial.println(this->_counter);
	}
	return this->_counter;
}


void CommandParser::clear() {
	//Serial.println(F("CommandParser.clear()"));
	this->_counter = 0;
}

unsigned short CommandParser::convertCoord(char* str) {
	char modeToken[2] = { this->_mode_sign, this->_mode_delimiter };
	bool switchON = ( 0 != strspn(str, modeToken) );

	char* data = strchr(str, ':') + 1;

	unsigned short num_data = this->a2us(data);

	if (debug) {
		//Serial.print(F("num_data: ")); Serial.print(num_data);
	}

	if (switchON) {
		num_data += 32768;
		//if (debug) Serial.print(F(", switchON, "));
	} else {
		//if (debug) Serial.print(F(", switchOFF, "));
	}

	if (debug) {
		//Serial.print(F("num_data: ")); Serial.println(num_data);
	}

	return num_data;
}

unsigned short CommandParser::a2us(char* str) {
	char* endPtr;
	unsigned long x = strtoul(str,&endPtr,10);
	return (unsigned short)x;
}
