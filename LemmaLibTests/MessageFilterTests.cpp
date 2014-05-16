//Copyright (c) 2014, IDEO 

#include <Arduino.h>
#include <arduinounit.h>
#include "Message.h"
#include "MessageFilter.h"

Message event;
void testHandler(Message const & e)
{
  event = e;
}

test( singleRegistrationBatch1 ) {
  MessageFilter filter;
  filter.add("speed", testHandler);
  Message speed("speed", "12");

  filter.handle( speed );
  assertTrue( strcmp( speed.topicName, event.topicName ) == 0 );
  assertTrue( strcmp( speed.stringValue, event.stringValue ) == 0 );
}

test( multipleRegistrationsBatch1 ) {
  MessageFilter filter;
  filter.add("speed", testHandler);
  filter.add("rpms", testHandler);

  Message speed("speed", "12");
  Message rpms("rpms", "3500");

  filter.handle( speed );
  assertTrue( strcmp( speed.topicName, event.topicName ) == 0 );
  assertTrue( strcmp( speed.stringValue, event.stringValue ) == 0 );

  filter.handle( rpms );
  assertTrue( strcmp( rpms.topicName, event.topicName ) == 0 );
  assertTrue( strcmp( rpms.stringValue, event.stringValue ) == 0 );
}

test( getsListOfEventsBatch1 ) {
  MessageFilter filter;
  filter.add("speed", testHandler);
  filter.add("rpms", testHandler);
  assertTrue(2 == filter.count());
  char const** events = filter.getTopicNames();
  assertTrue( strcmp( events[0], "speed" ) == 0 );
  assertTrue( strcmp( events[1], "rpms" ) == 0 );
}

