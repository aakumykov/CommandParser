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
			  Serial.println(F(""));
			  Serial.print(F("CommandParser.parse("));
			  Serial.print(str);
			  Serial.println(F(")"));
		}

	this->clear();

	char* raw_command = strtok(str, this->_command_delimiter);
	
		if (this->debug) {
			//~ Serial.print(F("raw_command: ")); Serial.println(raw_command);
		}
		
	this->_command = atoi(raw_command);
	  
	char* raw_data_piece = strtok(NULL, this->_data_delimiter);
	
		//~ Serial.print(F("raw_data_piece: |")); 
		//~ Serial.print(raw_data_piece);
		//~ Serial.print(F("| ("));
		//~ Serial.print(byte(raw_data_piece[0]));
		//~ Serial.print(F(") ("));
		//~ Serial.print(strlen(raw_data_piece));
		//~ Serial.println(F(")"));

	this->processCoordinate(raw_data_piece);
		
	while (NULL != raw_data_piece) {
		//if (strlen(raw_data_piece) < 5 ) continue;
		
		raw_data_piece = strtok(NULL, this->_data_delimiter);
		
			//~ Serial.print(F("raw_data_piece: |")); 
			//~ Serial.print(raw_data_piece);
			//~ Serial.print(F("| ("));
			//~ Serial.print(byte(raw_data_piece[0]));
			//~ Serial.print(F(") ("));
			//~ Serial.print(strlen(raw_data_piece));
			//~ Serial.println(F(")"));
		
		this->processCoordinate(raw_data_piece);
	}

	if (this->debug) {
		//Serial.println(F(""));
		this->command();
		this->data();
		this->length();
	}
}


unsigned short* CommandParser::data(bool debug=false) {
	
	if (debug) {
		Serial.print(F("data: "));
		for (int i=0; i < this->_counter; i++)
		{
			Serial.print(this->_data[i]);
			Serial.print(F("-"));
		}
		Serial.println(F(""));
	}

	return this->_data;
}

unsigned int CommandParser::command(){
	//Serial.println(F("CommandParser.getCommand()"));
	if (this->debug) {
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

void CommandParser::processCoordinate(char* str) {
	if (this->debug) {
		//~ Serial.print(F("CommandParser::processCoordinate("));
		 //~ Serial.print(str);
		 //~ Serial.print(F(" ("));
		 //~ Serial.print(strlen(str));
		 //~ Serial.print(F(")"));
		//~ Serial.println(F(")"));
	}
	
	// Костыльная защита от пустых данных на конце (откуда они появляются?).
	if (strlen(str) < 5) return;
	
	char modeToken[2] = { this->_mode_sign, this->_mode_delimiter };
	bool switchON = ( 0 != strspn(str, modeToken) );
	
		//if (this->debug) { Serial.print(F("switchON: ")); Serial.println(switchON); }

	char* xy_data = strchr(str, ':') + 1;
	
		//if (this->debug) { Serial.print(F("xy_data: ")); Serial.println(xy_data); }
	
	byte x_width = strcspn(xy_data,",");
		
		// if (this->debug) { Serial.print(F("x_width: ")); Serial.println(x_width); }
	
	char* raw_x = new char[x_width];
	strncpy(raw_x, xy_data, x_width);
	unsigned int x = this->a2us(raw_x);
		
		// if (this->debug) { Serial.print(F("raw_x: ")); Serial.println(raw_x); }
	
	char* raw_y = strchr(xy_data, ',') + 1;
	unsigned int y = this->a2us(raw_y);	
		
		//if (this->debug) { Serial.print(F("raw_y: ")); Serial.println(raw_y); }
		
		if (this->debug) { 
			//Serial.print(F("x and y: ")); Serial.print(x); Serial.print(F(" and ")); Serial.println(y);
		}

	delete xy_data, raw_x, raw_y;

	if (switchON) {
		x += 32768;
	}
	
	this->_data[this->_counter++] = x;
	this->_data[this->_counter++] = y;
}

unsigned short CommandParser::a2us(char* str) {
	char* endPtr;
	unsigned long x = strtoul(str,&endPtr,10);
	return (unsigned short)x;
}
