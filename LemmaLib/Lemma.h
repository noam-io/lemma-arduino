#ifndef LEMMA_H
#define LEMMA_H


#include <EthernetClient.h>
#include <EthernetUDP.h>
#include <EthernetServer.h>
#include "MessageBuilder.h"
#include "MessageSender.h"
#include "HostLocater.h"
#include "MessageFilter.h"
#include "Message.h"
#include "debug.h"
#include "Heartbeat.h"
#include "config.h"

class Lemma
{
  public:
    Lemma( const char * guestName, const char * desiredRoomName );

    void begin( unsigned char mac[] );
    void run();
    void hear( char * topicName, handler_t callback );
    bool speak( char const * topicName, char const * message );
    bool speak( char const * topicName, int message );
    bool speak( char const * topicName, unsigned long message );
    bool speak( char const * topicName, double message );
    bool isConnected();

  private:
    void tryConnectingWithHost();
    void handleIncomingConnections();
    void stopConnection();
    void updateConnectionStatus();
    bool postSendMessage();

    void sendHeartbeat();

    bool _connectedToHost;
    EthernetServer server;
    EthernetClient hostConnection;
    EthernetUDP udpClient;

    MessageFilter filter;
    MessageBuilder messageBuilder;
    MessageSender messageSender;
    HostLocater hostLocater;
    Heartbeat heartbeat;
};

#endif

