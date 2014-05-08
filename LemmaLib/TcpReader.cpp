#include "TcpReader.h"
#include "debug.h"

#include <EthernetClient.h>

#define TCP_READ_TIMEOUT 1000

TcpReader::TcpReader( EthernetClient& client ) :
    client( client )
{ }

char* TcpReader::read()
{
  int length = readPayloadLength();
  return readPayload( length );
}


int TcpReader::readPayloadLength()
{
  char lengthBuffer[7];
  readBlocked( lengthBuffer, 6 );
  lengthBuffer[6] = 0;
  int length = atoi( lengthBuffer );
  return length;
}

char* TcpReader::readPayload( int length )
{
  char* payload = (char*) malloc( length + 1 );
  if ( payload == 0 )
  {
    DEBUGWRAP(Serial.write("Could not allocated memory for the TCP Reader"));
    return 0;
  }
  readBlocked( payload, length );
  payload[ length ] = 0;

  return payload;
}


void TcpReader::readBlocked( char* destination, int length )
{
  int bytesRead = 0;
  unsigned long tcpTimeoutTimer = millis();

  while( bytesRead != length )
  {
    if( millis() - tcpTimeoutTimer > TCP_READ_TIMEOUT ){
      break;
    }
    int tempBytes = client.read( (uint8_t*) destination + bytesRead, length - bytesRead );
    if( tempBytes > 0 ){
      bytesRead += tempBytes;
    }
  }
}

