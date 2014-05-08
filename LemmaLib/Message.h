#ifndef MESSAGE_H
#define MESSAGE_H

class Message {
  public:
  char topicName[128];
  char stringValue[128];
  int intValue;
  double floatValue;
  bool boolValue;

  Message();
  Message( char const * topicName, char const * value );
  Message( char const * topicName, int value );
  Message( char const * topicName, double value );
  Message( char const * topicName, bool value );
  Message( Message const & other);

  Message & operator=(Message const & other);
};

#endif

