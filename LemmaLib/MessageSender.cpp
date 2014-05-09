#include "MessageSender.h"
#include <Ethernet.h>
#include "MessageBuilder.h"
#include "TcpProtocol.h"

MessageSender::MessageSender( const char * guestName, EthernetClient& outboundClient ) :
    messageBuilder( guestName )
  , outboundClient( outboundClient )
{ }

bool MessageSender::sendRegistration( int listenPort, char const ** hears, int hearsCount, char const ** speaks, int speaksCount )
{
  char* registrationMessage = messageBuilder.buildRegister( listenPort, hears, hearsCount, speaks, speaksCount );
  bool result = sendMessage( registrationMessage );
  free( registrationMessage );
  return result;
}

bool MessageSender::sendMessage( char const * topicName, char const * value )
{
  char* eventMessage = messageBuilder.buildMessage( topicName, value );
  bool result = sendMessage( eventMessage );
  free( eventMessage );
  return result;
}

bool MessageSender::sendMessage( char const * topicName, int value )
{
  char* eventMessage = messageBuilder.buildMessage( topicName, value );
  bool result = sendMessage( eventMessage );
  free( eventMessage );
  return result;
}

bool MessageSender::sendLongMessage( char const * topicName, long unsigned int value )
{
  char* eventMessage = messageBuilder.buildLongMessage( topicName, value );
  bool result = sendMessage( eventMessage );
  free( eventMessage );
  return result;
}

bool MessageSender::sendDoubleMessage( char const * topicName, double value )
{
  char* eventMessage = messageBuilder.buildDoubleMessage( topicName, value );
  bool result = sendMessage( eventMessage );
  free( eventMessage );
  return result;
}

bool MessageSender::sendMessage( char const * message )
{
  bool result = false;
  if( outboundClient.connected() )
  {
    char* encoded = TcpProtocol::encode( message );

    int sent = outboundClient.print( encoded );
    outboundClient.flush();
    result = (sent == strlen(encoded));

    free( encoded );
  }
  return result;
}

bool MessageSender::sendHeartbeat(){
  char* heartbeatMessage = messageBuilder.buildHeartbeat();
  bool result = sendMessage( heartbeatMessage );
  free( heartbeatMessage );
  return result;
}

