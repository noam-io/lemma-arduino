#include <Arduino.h>
#include <ArduinoUnit.h>
#include "MessageBuilder.h"

test( createsStringMessageBatch1 ) {
  MessageBuilder builder("spallaId");

  String expected("[\"event\",\"spallaId\",\"speed\",\"65\"]");
  char * actual = builder.buildMessage("speed", "65");

  assertEqual(actual, expected);
  free(actual);
}

test( createsIntMessageBatch1 ) {
  MessageBuilder builder("spallaId");

  String expected("[\"event\",\"spallaId\",\"speed\",65]");
  char * actual = builder.buildMessage("speed", 65);

  assertEqual(actual, expected);
  free(actual);
}

/* float support removed */
test(createsFloatMessage) {
  MessageBuilder builder("spallaId");

  String expected("[\"event\",\"spallaId\",\"speed\",23.01000]");
  char * actual = builder.buildMessage("speed", 23.01);

  assertEqual(actual, expected);
  free(actual);
}

test( createRegistrationMessageBatch1 ) {
  MessageBuilder builder("spallaId");

  char const* hears[2] = {"event1", "event2"};
  char const* plays[3] = {"event3", "event4", "event5"};

  char* expected = "[\"register\",\"spallaId\",123,[\"event1\",\"event2\"],[\"event3\",\"event4\",\"event5\"],\"arduino\",\"0.3\",{\"heartbeat\":3.00300}]";
  char* actual = builder.buildRegister(123, hears, 2, plays, 3);

  assertEqual(String(expected), String(actual));
  free(actual);
}

