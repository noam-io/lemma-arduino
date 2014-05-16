//Copyright (c) 2014, IDEO 

#include <Arduino.h>
#include <ArduinoUnit.h>
#include "HeartBeat.h"
#include "config.h"
#include "MockClient_ForWriting.h"
#include "MessageSender.h"


static long unsigned int milliReturn = 0;
static long unsigned int fakeMillis()
{
  return milliReturn;
}

test(isNotReadyToSendBatch1) {
  Heartbeat heartbeat(&fakeMillis);
  heartbeat.reset();
  assertFalse(heartbeat.readyToBeat());
}

test(ReadyToSendBatch1) {
  Heartbeat heartbeat(&fakeMillis);
  milliReturn = HEARTBEAT_PERIOD_MS + 1;
  assertTrue(heartbeat.readyToBeat());
}

test(ResetsHeartbeatBatch1) {
  Heartbeat heartbeat(&fakeMillis);
  milliReturn = HEARTBEAT_PERIOD_MS;
  heartbeat.reset();
  milliReturn = HEARTBEAT_PERIOD_MS + 1;
  assertFalse(heartbeat.readyToBeat());
}

test(SendsMessageBatch1) {
  MockClient_ForWriting client;
  client.isConnected = true;
  MessageSender sender( "blah", client );
  milliReturn = HEARTBEAT_PERIOD_MS + 1;
  Heartbeat heartbeat(&fakeMillis, &sender);
  assertTrue(heartbeat.check());

  assertEqual("000020[\"heartbeat\",\"blah\"]", String(client.buffer) );
}
