#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

class Message;
#include <stdint.h>
#include <string.h>

class MessageParser
{
  public:
  static Message parse( char const * message );
  static bool parsePolo( char const * message, char * name, int nameSize, unsigned int& outPort);

  private:
  MessageParser();
};

#endif

