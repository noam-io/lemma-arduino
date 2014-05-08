#include <ArduinoUnit.h>
#include "Message.h"
#include "string.h"
#include <Arduino.h>

test( stringsBatch1 ) {
  Message event("name", "string");
  assertTrue( 0 == strcmp("string", event.stringValue) );
  assertTrue( 0 == event.intValue);
  assertTrue( 0 == event.floatValue);
}

test( intFromStringBatch1 ) {
  Message event("name", "2");
  assertTrue( 0 == strcmp("2", event.stringValue) );
  assertTrue( 2 == event.intValue);
  assertTrue( 2.0 == event.floatValue);
}

test( intFromIntBatch1 ) {
  Message event("name", 2);
  assertTrue( 0 == strcmp("2", event.stringValue) );
  assertTrue( 2 == event.intValue);
  assertTrue( 2.0 == event.floatValue);
}

test( fromFloatBatch1 ) {
  Message event("name", 2.45f);
  assertTrue( 2 == event.intValue);
  assertTrue( 2.45 == event.floatValue);

  //Too Hard and we aren't needing it yet
  assertTrue( 0 == strcmp("", event.stringValue) );
  //assertTrue( 0 == strcmp("2.45", event.value) );
}

