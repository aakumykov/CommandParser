#include "CommandParser.h"

    CommandParser::CommandParser(int max_input_len, char* command_delimiter, char* data_delimiter) {
      this->_data = new int[max_input_len];
      this->_command_delimiter = command_delimiter;
      this->_data_delimiter = data_delimiter;
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
      //Serial.print(F("raw_command: ")); Serial.println(raw_command);
      this->_command = atoi(raw_command);
//      this->_command = (unsigned long)(raw_command);
      
      char* raw_data_piece = strtok(NULL, this->_data_delimiter);
      int data_piece = atoi(raw_data_piece);
      
      while (NULL != raw_data_piece) {
        this->_data[this->_counter++] = data_piece;
        //this->_counter += 1;
        
        raw_data_piece = strtok(NULL, this->_data_delimiter);
        data_piece = atoi(raw_data_piece);
      }

      if (debug) {
        this->command();
        this->data();
        this->length();
      }
    }

    byte CommandParser::command(){
      //Serial.println(F("CommandParser.getCommand()"));
      if (debug) {
	Serial.print(F("command: "));
	Serial.println(this->_command);
	}
      return this->_command;
    }

    int* CommandParser::data() {
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
