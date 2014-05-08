#ifndef TCP_READER_H
#define TCP_READER_H

class EthernetClient;

class TcpReader
{
private:
  EthernetClient& client;

public:
  TcpReader( EthernetClient& client );

  char* read();

private:
  int readPayloadLength();
  char* readPayload( int length );
  void readBlocked( char* destination, int length );
};

#endif

