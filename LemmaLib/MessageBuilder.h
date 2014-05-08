#ifndef MESSAGE_BUILDER_H
#define MESSAGE_BUILDER_H

class MessageBuilder
{
  private:
  char const * guestName;

  public:
  MessageBuilder( char const * guestName );
  char * buildMessage( char const * topicName, char const * value ) const;
  char * buildMessage( char const * topicName, int value ) const;
  char * buildLongMessage( char const * topicName, unsigned long value ) const;
  char * buildDoubleMessage( char const * topicName, double value ) const;
  char * buildRegister( int port, char const** hears, int hearsSize, char const** speaks, int speaksSize ) const;
  char * buildHeartbeat() const;
};

#endif

