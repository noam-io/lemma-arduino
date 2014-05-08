#include "MessageParser.h"
#include <aJSON.h>
#include "Message.h"
#include "Arduino.h"

bool MessageParser::parsePolo( char const * poloMessage, char * name, int nameSize, unsigned int& outPort) {
  aJsonObject* json = aJson.parse( (char *)poloMessage );

  if(json == NULL || json->type != aJson_Array) {
    aJson.deleteItem( json );
    return false;
  }

  aJsonObject* messageType = aJson.getArrayItem( json, 0 );
  aJsonObject* roomName = aJson.getArrayItem( json, 1 );
  if (roomName == NULL) {
    aJson.deleteItem( json );
    return false;
  }

  strncpy(name, roomName->valuestring, nameSize);

  aJsonObject* portNumber = aJson.getArrayItem( json, 2 );
  if (portNumber == NULL) {
    aJson.deleteItem( json );
    return false;
  }

  outPort = portNumber->valueint;
  aJson.deleteItem( json );
  return true;
}

Message MessageParser::parse( char const * message )
{
  aJsonObject* json = aJson.parse( (char *)message );
  aJsonObject* topicName = aJson.getArrayItem( json, 2 );
  aJsonObject* value = aJson.getArrayItem( json, 3 );
  switch(value->type)
  {
    case aJson_Int:
      {
        Message result( topicName->valuestring, value->valueint );
        aJson.deleteItem( json );
        return result;
      }

    case aJson_Float:
      {
        Message result( topicName->valuestring, value->valuefloat );
        aJson.deleteItem( json );
        return result;
      }
    default:
      {
        Message result( topicName->valuestring, value->valuestring );
        aJson.deleteItem( json );
        return result;
      }
  }
}

