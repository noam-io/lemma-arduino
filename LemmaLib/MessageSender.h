#ifndef MESSAGE_SENDER_H
#define MESSAGE_SENDER_H

#include "MessageBuilder.h"

class EthernetClient;

class MessageSender
{
  public:
    MessageSender( char const * guestName, EthernetClient& outboundClient );
    bool sendRegistration( int listenPort, char const ** hears, int hearsCount, char const ** speaks, int speaksCount );
    bool sendMessage( char const * topicName, char const * value );
    bool sendMessage( char const * topicName, int value );
    bool sendDoubleMessage( char const * topicName, double value );
    bool sendLongMessage( char const * topicName, long unsigned int value );    
    bool sendHeartbeat();

  private:
    bool sendMessage( char const * message );

    MessageBuilder messageBuilder;
    EthernetClient& outboundClient;
};

#endif

