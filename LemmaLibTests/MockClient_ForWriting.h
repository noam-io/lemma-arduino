//Copyright (c) 2014, IDEO 

#ifndef MOCK_CLIENT_FOR_WRITING
#define MOCK_CLIENT_FOR_WRITING

#include <EthernetClient.h>

class MockClient_ForWriting : public EthernetClient {
public:
  char buffer[128];
  size_t bytesWritten;
  IPAddress connectedTo;
  uint16_t connectedOn;
  bool isConnected;

  MockClient_ForWriting();

  virtual size_t write( const uint8_t *buf, size_t size );
  virtual void flush();
  virtual int connect( IPAddress ip, uint16_t port );
  virtual uint8_t connected();

  void clearBuffer();
};

#endif

