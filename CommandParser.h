#include <Arduino.h>
#include <MemoryFree.h>

#ifndef CommandParser_h
#define CommandParser_h

class CommandParser
{
  public:
    CommandParser(int max_input_len, char* command_delimiter, char* data_delimiter, char mode_delimiter, char mode_sign);
    
    unsigned short* data(bool debug=false);
    unsigned int command();
    int length();
    
    void parse(char* str, bool debug=false);
    
  private:
    char* _command_delimiter;
    char* _data_delimiter;
    char _mode_sign;
    char _mode_delimiter;

    unsigned long _command;
    unsigned short* _data;
    int _counter = 0;

    bool debug = false;

    void clear();
    void CommandParser::processCoordinate(char* str);
    unsigned short CommandParser::a2us(char* str);
};

#endif
