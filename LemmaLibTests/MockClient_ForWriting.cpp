#include "MockClient_ForWriting.h"

MockClient_ForWriting::MockClient_ForWriting() :
    bytesWritten(0)
  , connectedTo( 0, 0, 0, 0 )
  , connectedOn( 0 )
  , isConnected( false )
{
  clearBuffer();
}

size_t MockClient_ForWriting::write(const uint8_t *buf, size_t size)
{
  memcpy( buffer + bytesWritten, (const char*) buf, size );
  bytesWritten += size;
  return size;
}

void MockClient_ForWriting::flush()
{
  buffer[bytesWritten] = 0;
}

int MockClient_ForWriting::connect(IPAddress ip, uint16_t port)
{
  connectedTo = ip;
  connectedOn = port;
  isConnected = true;
}

void MockClient_ForWriting::clearBuffer()
{
  bytesWritten = 0;
  buffer[0] = 0;
}

uint8_t MockClient_ForWriting::connected()
{
  return isConnected ? 1 : 0;
}
