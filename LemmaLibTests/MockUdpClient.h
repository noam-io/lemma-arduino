//Copyright (c) 2014, IDEO 

#ifndef MOCK_UDP_CLIENT_H
#define MOCK_UDP_CLIENT_H

#include <EthernetUdp.h>

class MockUdpClient : public EthernetUDP
{
public:
  char const * packet;
  IPAddress ip;

  MockUdpClient();

  virtual int parsePacket();
  virtual int read( char* buffer, size_t length );
  virtual IPAddress remoteIP();
};

#endif

