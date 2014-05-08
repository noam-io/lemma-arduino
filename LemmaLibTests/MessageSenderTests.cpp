#include <ArduinoUnit.h>
#include "MessageSender.h"
#include "MessageBuilder.h"
#include "MockClient_ForWriting.h"
#include "TcpProtocol.h"

static const char* SPALLA_ID = "some id";
static int LISTEN_PORT = 1030;

test( doesNothingWhenClientIsNotConnectedBatch1 )
{
  MockClient_ForWriting client;
  client.isConnected = false;
  MessageSender sender( SPALLA_ID, client );
  assertTrue(!sender.sendMessage( "a", "b" ));

  assertTrue( 0 == strcmp( "", client.buffer ));
}

test( sendsRegistrationMessagesBatch1 )
{
  MessageBuilder builder( SPALLA_ID );
  char const* hears[] = { "abc", "bobbo" };
  char* registrationMessage = builder.buildRegister( LISTEN_PORT, hears, 2, 0, 0 );
  char* expected = TcpProtocol::encode( registrationMessage );
  free( registrationMessage );

  MockClient_ForWriting client;
  client.isConnected = true;
  MessageSender sender( SPALLA_ID, client );
  bool result = sender.sendRegistration( LISTEN_PORT, hears, 2, 0, 0 );
  assertTrue(true == result);

  assertEqual( String(expected), String(client.buffer) );
  free( expected );
}

test( sendsStringMessagesBatch1 )
{
  char const * eventName = "some name";
  char const * eventValue = "some value";

  MockClient_ForWriting client;
  client.isConnected = true;

  MessageSender sender( SPALLA_ID, client );
  bool result = sender.sendMessage( eventName, eventValue );
  assertTrue(result);



  MessageBuilder builder( SPALLA_ID );
  char* eventMessage = builder.buildMessage( eventName, eventValue );
  char* expected = TcpProtocol::encode( eventMessage );
  free( eventMessage );

  assertTrue( 0 == strcmp( expected, client.buffer ));
  free( expected );
}

test( sendsIntMessagesBatch1 )
{
  char const * eventName = "some name";
  int eventValue = 20;

  MockClient_ForWriting client;
  client.isConnected = true;

  MessageSender sender( SPALLA_ID, client );
  bool result = sender.sendMessage( eventName, eventValue );
  assertTrue(true == result);

  MessageBuilder builder( SPALLA_ID );
  char* eventMessage = builder.buildMessage( eventName, eventValue );
  char* expected = TcpProtocol::encode( eventMessage );
  free( eventMessage );

  assertTrue( 0 == strcmp( expected, client.buffer ));
  free( expected );
}


test( sendsFloatMessagesBatch1 )
{
  char const * eventName = "some name";
  double eventValue = 38.022;

  MockClient_ForWriting client;
  client.isConnected = true;

  MessageSender sender( SPALLA_ID, client );
  bool result = sender.sendMessage( eventName, eventValue );
  assertTrue(true == result);

  MessageBuilder builder( SPALLA_ID );
  char* eventMessage = builder.buildMessage( eventName, eventValue );
  char* expected = TcpProtocol::encode( eventMessage );
  free( eventMessage );

  assertTrue( 0 == strcmp( expected, client.buffer ));
  free( expected );
}

