#include <Arduino.h>
#include <ArduinoUnit.h>
#include "MessageParser.h"
#include "Message.h"

//TODO:  Test parse Polo
test(parsingMessageMessageBatch1) {
  char * message = "[\"event\",\"some id\",\"a name\",\"a value\"]";
  const Message& event = MessageParser::parse( message );

  assertTrue( String("a name").equals( event.topicName ) );
  assertTrue( String("a value").equals( event.stringValue ) );
  assertTrue( 0 == event.intValue );
  assertTrue( 0 == event.floatValue );
}

test(parsingIntValueBatch1) {
  char * message = "[\"event\",\"some id\",\"a name\",142]";
  const Message& event = MessageParser::parse( message );

  assertTrue( String("a name").equals( event.topicName ) );
  assertTrue( 0 == strcmp( "142", event.stringValue ) );
  assertTrue( 142 == event.intValue );
  assertTrue( 142.0f == event.floatValue );
}

test(parsingFloatValueBatch1) {
  char * message = "[\"event\",\"some id\",\"a name\",14.10]";
  Message event = MessageParser::parse( message );

  assertTrue( String("a name").equals( event.topicName ) );
  assertTrue( 14 == event.intValue );
  assertTrue(abs(event.floatValue - 14.10) < 0.01 );
}

