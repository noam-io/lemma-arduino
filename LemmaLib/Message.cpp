#include "Message.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Message::Message()
{
  this->topicName[0] = 0;
  this->stringValue[0] = 0;
  this->intValue = 0;
  this->floatValue = 0.0;
  this->boolValue = false;
}

Message::Message( char const * topicName, char const * value )
{
  strncpy( this->topicName, topicName, 128 );
  strncpy( this->stringValue, value, 128 );
  this->intValue = atoi( value );
  this->floatValue = atof( value );
  this->boolValue =  value;
}

Message::Message( char const * topicName, int value )
{
  strncpy( this->topicName, topicName, 128 );
  snprintf( this->stringValue, 128, "%d", value );
  this->intValue = value;
  this->floatValue = (double) value;
  this->boolValue =  value;
}

Message::Message( char const * topicName, double value )
{
  strncpy( this->topicName, topicName, 128 );
  this->stringValue[0] = 0;
  this->intValue = (int) value;
  this->floatValue =  value;
  this->boolValue =  value;
}

Message::Message( char const * topicName, bool value )
{
  strncpy( this->topicName, topicName, 128 );
  snprintf( this->stringValue, 128, "%d", value );
  this->intValue = (int) value;
  this->floatValue =  value;
  this->boolValue =  value;
}

Message::Message( Message const & other)
{
  strncpy( this->topicName, other.topicName, 128 );
  strncpy( this->stringValue, other.stringValue, 128 );
  this->intValue = other.intValue;
  this->floatValue = other.floatValue;
  this->boolValue =  other.boolValue;
}

Message & Message::operator=(Message const & other)
{
  strncpy( this->topicName, other.topicName, 128 );
  strncpy( this->stringValue, other.stringValue, 128 );
  this->intValue = other.intValue;
  this->floatValue = other.floatValue;
  this->floatValue = other.boolValue;
}
